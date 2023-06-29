#ifndef SKYNET_THREADING_MTX_HPP 
#define SKYNET_THREADING_MTX_HPP

#define LOCK_MUTEX_WRITE(mutex) write_lock lock(mutex)
#define LOCK_MUTEX_READ(mutex) read_lock lock(mutex)

namespace threading
{
      using write_lock = std::unique_lock<std::shared_mutex>;
      using read_lock = std::shared_lock<std::shared_mutex>;
}

#endif //!SKYNET_THREADING_MTX_HPP
