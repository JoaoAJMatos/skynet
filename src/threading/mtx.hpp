/**
 * @file    mtx.hpp
 * @author  JoaoAJMatos
 * @brief   Mutexes for multithreading
 * @date    2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * @license MIT
 */

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