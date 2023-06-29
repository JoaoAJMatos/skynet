
#include "threadpool.hpp"

threading::ThreadPool::ThreadPool(const size_t thread_count)
{
      this->thread_count_ = thread_count;
      this->running_ = false;
}

inline threading::ThreadPool::~ThreadPool() { this->Stop(false); }


/**
 * @brief Start the thread pool.
 */
void threading::ThreadPool::Init()
{
      std::call_once(this->once_flag_, [this]() {
            LOCK_MUTEX_WRITE(this->mutex_);
            workers_.reserve(this->thread_count_);
            for (size_t i = 0; i < this->thread_count_; ++i) {
                  this->workers_.emplace_back(std::bind(&ThreadPool::Spawn, this));
            }
      });
}

/**
 * @brief Stop the thread pool.
 * @param wait | true, stops and processes all delegated tasks.
 *             | false, stops and drops all delegated tasks.
 */
void threading::ThreadPool::Stop(const bool wait)
{
      if (!running_) return;
      running_ = false;
      if (!wait) {
            tasks_.Clear(); 
      }
      condition_.notify_all();
      for (auto& worker : workers_) {
            worker.join();
      }
}

/**
 * @brief Spawn a thread to process tasks.
 */
void threading::ThreadPool::Spawn()
{
      for (;;) {
            bool pop_result = false;
            std::function<void()> task;
            
            {
                  LOCK_MUTEX_WRITE(mutex_);
                  condition_.wait(lock, [this, &pop_result, &task]() {
                        pop_result = tasks_.Pop(task);
                        return pop_result || !running_;
                  });
            }

            if (!pop_result) return;
            task();
      }
}

/**
 * @brief Enqueue a task to be processed by a thread.
 * @param f | The function to be processed.
 * @param args | The arguments to be passed to the function.
 * @return std::future | The result of the function.
 */
template <class F, class... Args>
auto threading::ThreadPool::Enqueue(F &&f, Args &&... args) const -> std::future<decltype(f(args...))>
{
      using return_type = decltype(f(args...));
      auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));
      std::future<return_type> result = task->get_future();
      {
            LOCK_MUTEX_WRITE(mutex_);
            tasks_.Push([task]() { (*task)(); });
      }
      condition_.notify_one();
      return result;
}

/* GETTERS AND OBSERVABLES */
bool threading::ThreadPool::IsRunning() const { return running_; }
size_t threading::ThreadPool::GetThreadCount() const { return thread_count_; }
size_t threading::ThreadPool::GetTaskCount() const { return tasks_.Size(); }

