/**
 * @file   test_framework.hpp
 * @author JoaoAJMatos
 *
 * @brief Self-contained single header test framework
 *	    used by skynet to perform unit tests. Check
 *	    
 *
 * @version 0.1
 * @date 2023-02-01
 * @license MIT
 * @copyright Copyright (c) 2023
 */

// TODO: Add different logging levels for failed tests
// TODO: Maybe add support for custom test suites with custom setup and teardown functions

#ifndef UNIPP_TEST_FRAMEWORK_HPP
#define UNIPP_TEST_FRAMEWORK_HPP


/** C++ headers */
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <stdexcept>
#include <memory>

/** MACROS */
#define UNIPP_TEST_FRAMEWORK_VERSION "0.1.0"

#if defined(__APPLE__)
#define inline __attribute__((always_inline))
#endif // __APPLE__

/** Macros for creating and running tests */
#define TEST(name, description, testfunction) unipp::UnitTest(name, description, testfunction)
#define SUITE(name, description, ...) unipp::TestSuite(name, description, __VA_ARGS__)
#define RUN(...) unipp::TestRunner::RunAll(__VA_ARGS__)

/** Macros for benchmarking */
#define BENCHMARK(function, iterations) unipp::Benchmark(function, iterations)
#define SECONDS_TO_MILLISECONDS(seconds_count) std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds(seconds_count)).count()
#define MILLISECONDS(milliseconds_count) std::chrono::milliseconds(milliseconds_count)

/** Macros for assertions */
#define PASS_MESSAGE() std::cout << "      [√] PASSED" << std::endl << std::endl
#define FAIL_MESSAGE() std::cout << "      [X] FAILED: " << e.what() << std::endl
#define WARN_MESSAGE() std::cout << "      [!] WARNING: " << e.what() << std::endl

#define BEGIN_ASSERT try {
#define END_ASSERT                              \
      PASS_MESSAGE();                           \
      }                                         \
      catch (const std::exception& e)           \
      {                                         \
            FAIL_MESSAGE();                     \
            return;                             \
      }                                         \

#define BEGIN_EXPECT try {
#define END_EXPECT                              \
      PASS_MESSAGE();                           \
      }                                         \
      catch (const std::exception& e)           \
      {                                         \
            WARN_MESSAGE();                     \
      }                                         \

#define BASE_ASSERT(...) BEGIN_ASSERT __VA_ARGS__ END_ASSERT
#define BASE_EXPECT(...) BEGIN_EXPECT __VA_ARGS__ END_EXPECT

/** These stand out in your testing code */
#define ASSERT(condition, message) BASE_ASSERT(unipp::Assert(condition, message);)
#define ASSERT_EQUAL(a, b, msg) BASE_ASSERT(unipp::Equal(a, b, msg);)
#define ASSERT_NOT_EQUAL(a, b, msg) BASE_ASSERT(unipp::NotEqual(a, b, msg);)
#define ASSERT_GREATER(a, b, msg) BASE_ASSERT(unipp::Greater(a, b, msg);)
#define ASSERT_GREATER_EQUAL(a, b, msg) BASE_ASSERT(unipp::GreaterEqual(a, b, msg);)
#define ASSERT_LESS(a, b, msg) BASE_ASSERT(unipp::Less(a, b, msg);)
#define ASSERT_LESS_EQUAL(a, b, msg) BASE_ASSERT(unipp::LessEqual(a, b, msg);)
#define ASSERT_TRUE(a, msg) BASE_ASSERT(unipp::True(a, msg);)
#define ASSERT_FALSE(a, msg) BASE_ASSERT(unipp::False(a, msg);)
#define ASSERT_NULL(a, msg) BASE_ASSERT(unipp::Null(a, msg);)
#define ASSERT_NOT_NULL(a, msg) BASE_ASSERT(unipp::NotNull(a, msg);)
#define EXPECT(condition, message) BASE_BASE_EXPECT(unipp::Assert(condition, message);)
#define EXPECT_EQUAL(a, b, msg) BASE_EXPECT(unipp::Equal(a, b, msg);)
#define EXPECT_NOT_EQUAL(a, b, msg) BASE_EXPECT(unipp::NotEqual(a, b, msg);)
#define EXPECT_GREATER(a, b, msg) BASE_EXPECT(unipp::Greater(a, b, msg);)
#define EXPECT_GREATER_EQUAL(a, b, msg) BASE_EXPECT(unipp::GreaterEqual(a, b, msg);)
#define EXPECT_LESS(a, b, msg) BASE_EXPECT(unipp::Less(a, b, msg);)
#define EXPECT_LESS_EQUAL(a, b, msg) BASE_EXPECT(unipp::LessEqual(a, b, msg);)
#define EXPECT_TRUE(a, msg) BASE_EXPECT(unipp::True(a, msg);)
#define EXPECT_FALSE(a, msg) BASE_EXPECT(unipp::False(a, msg);)
#define EXPECT_NULL(a, msg) BASE_EXPECT(unipp::Null(a, msg);)
#define EXPECT_NOT_NULL(a, msg) BASE_EXPECT(unipp::NotNull(a, msg);)


namespace unipp
{
      /** Type definitions */
      typedef std::function<void()> TestFunction;

      /** Structs */
      struct BenchmarkResult 
      {
            std::chrono::milliseconds total;
            std::chrono::milliseconds average;

            BenchmarkResult(std::chrono::milliseconds total, std::chrono::milliseconds average)
                  : total(total), average(average) {}

            void Show() {
                  std::cout << "   [BENCHMARK] Total time: " << total.count() << "ms" << std::endl;
                  std::cout << "   [BENCHMARK] Average time: " << average.count() << "ms" << std::endl;
            }
      };

      /**
       * @brief Defines a unit test
       */
      struct UnitTest
      {
            std::string name;         
            std::string description;
            TestFunction test;

            UnitTest(std::string name, std::string description, TestFunction test)
                  : name(name), description(description), test(test) {}

            /**
             * @brief Runs the test
             */
            void Run() {
                  std::cout << "   [TEST] Running test: " << name << std::endl;
                  std::cout << "   [+] Description: " << description << std::endl;
                  test();
            }
      };


      /** Classes */
      class TestSuite
      {
      public:
            /**
             * @brief Construct a new Test Suite object
             *
             *        SUITE("My Suite", "This is a suite description", PER_TEST,
             *              TEST("My Test", "This is a test description", []() { ... }),
             *              TEST("My Test 2", "This is a test description", []() { ... }),
             *              TEST("My Test 3", "This is a test description", []() { ... })
             *        );
             *
             * @tparam Tests
             * @param name
             * @param description
             * @param tests
             */
            template<typename... Tests>
            TestSuite(std::string name, std::string description, Tests... tests)
                      : name_(name), description_(description) {
                  AddTests(tests...);
            }


            /**
             * @brief Adds tests to the suite.
             */
            template<typename... Tests>
            void AddTests(Tests... tests) {
                  (tests_.push_back(tests), ...);
            }


            /**
             * @brief Run the tests in the suite.
             */
            void Run() {
                  std::cout << "[SUITE | " << this->name_ << " | " << this->description_ << "]" << std::endl;
                  for (auto test : tests_) {
                        test.Run();
                  }
                  std::cout << "[END SUITE]" << std::endl << std::endl;
            }
      private:
            std::string name_;
            std::string description_;
            std::vector<UnitTest> tests_;
      };


      /**
       * @brief TestRunner class.
       *        Runs the tests in the test suites.
       */
      class TestRunner
      {
      public:
            /** Base case for the recursive variadic template */
            static void RunAll() { }

            /**
             * @brief Variadic template for running SUITES.
             *
             *        RUN(
             *              SUITE("My Suite", "This is a suite description",
             *                    TEST("My Test", "This is a test description", []() { ... }),
             *                    TEST("My Test 2", "This is a test description", []() { ... }),
             *                    TEST("My Test 3", "This is a test description", []() { ... })
             *              ),
             *              SUITE("My Suite 2", "This is a suite description",
             *                    TEST("My Test", "This is a test description", []() { ... }),
             *                    TEST("My Test 2", "This is a test description", []() { ... }),
             *                    TEST("My Test 3", "This is a test description", []() { ... })
             *              )
             *        );
             *
             * @tparam TestSuites
             * @param suites
             */
            template<typename... TestSuites>
            static void RunAll(TestSuite suite, TestSuites... suites) {
                  suite.Run();
                  RunAll(suites...);
            }

            /**
             * @brief Variadic template for running TESTS.
             *
             *        RUN(
             *              TEST("My Test", "This is a test description", []() { ... }),
             *              TEST("My Test 2", "This is a test description", []() { ... })
             *        );
             *
             * @tparam Tests
             * @param suites
             */
            template<typename... Tests>
            static void RunAll(UnitTest test, Tests... tests) {
                  test.Run();
                  RunAll(tests...);
            }
            
      private:
            TestRunner() {}
      };


      /**
       * @brief Benchmark a function.
       *        Returns the average execution time of the function.
       *
       * @param function
       * @param iterations
       * @return BenchmarkResult
       */
      BenchmarkResult Benchmark(TestFunction test, int iterations) {
            std::chrono::milliseconds total_time = std::chrono::milliseconds(0);

            for (int i = 0; i < iterations; i++) {
                  auto start = std::chrono::high_resolution_clock::now();
                  test();
                  auto end = std::chrono::high_resolution_clock::now();
                  total_time += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            }

            BenchmarkResult result(total_time, total_time / iterations);
            return result;
      }

      /** Inline functions */
      inline void Assert(bool condition, std::string message = "") {
            if (!condition) {
                  throw std::runtime_error(message);
            }
      }

      template<typename T>
      inline void Equal(T a, T b, std::string message = "") {
            if (a != b) {
                  throw std::runtime_error(message);
            }
      }

      template<typename T>
      inline void NotEqual(T a, T b, std::string message = "") {
            if (a == b) {
                  throw std::runtime_error(message);
            }
      }

      template<typename T>
      inline void Greater(T a, T b, std::string message = "") {
            if (a <= b) {
                  throw std::runtime_error(message);
            }
      }

      template<typename T>
      inline void GreaterEqual(T a, T b, std::string message = "") {
            if (a < b) {
                  throw std::runtime_error(message);
            }
      }

      template<typename T>
      inline void Less(T a, T b, std::string message = "") {
            if (a >= b) {
                  throw std::runtime_error(message);
            }
      }

      template<typename T>
      inline void LessEqual(T a, T b, std::string message = "") {
            if (a > b) {
                  throw std::runtime_error(message);
            }
      }

      template<typename T>
      inline void Null(T a, std::string message = "") {
            if (a != nullptr) {
                  throw std::runtime_error(message);
            }
      }

      template<typename T>
      inline void NotNull(T a, std::string message = "") {
            if (a == nullptr) {
                  throw std::runtime_error(message);
            }
      }

      inline void True(bool a, std::string message = "") {
            if (!a) {
                  throw std::runtime_error(message);
            }
      }

      inline void False(bool a, std::string message = "") {
            if (a) {
                  throw std::runtime_error(message);
            }
      }
}


#endif // UNIPP_TEST_FRAMEWORK_HPP

// MIT License
// 
// Copyright (c) 2023 João Matos
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
