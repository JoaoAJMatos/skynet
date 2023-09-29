/**
 * @file file.hpp
 * @author JoaoAJMatos
 * @brief This file contains a series of utility functions to work with files
 * @date 2023-09-29
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef IO_FILE_HPP
#define IO_FILE_HPP

/** Skynet includes */
#include <macros.hpp>
#include <types.hpp>

/** Platform specific macros for directory separators */
#if defined(_WIN32) || defined(_WIN64)
#define DIRECTORY_SEPARATOR '\\'
#else
#define DIRECTORY_SEPARATOR '/'
#endif // defined(_WIN32) || defined(_WIN64)


namespace io::file
{
      /** Error codes */
      enum class Error : uint8_t {
            FILE_SUCCESS = 0,
            FILE_NOT_FOUND = 1,
            FILE_NOT_OPEN = 2,
            FILE_ALREADY_OPEN = 3,
            FILE_ALREADY_EXISTS = 4,
            FILE_EMPTY = 5,
            FILE_READ_ERROR = 7,
            FILE_WRITE_ERROR = 8,
      };

      /** Gets the error message */
      inline std::string ErrorToString(Error error);

      /** Read the contents of a file in binary format */
      Error Read(const std::string& path, std::unique_ptr<byte[]>& data, uint32_t& size);
      /** Read the contents of a file in text format */
      Error Read(const std::string& path, std::string& data);
      /** Append data to the end of a file in binary format */
      Error Append(const std::string& path, std::unique_ptr<byte[]>& data, uint32_t& size);
      /** Append data to the end of a file in text format */
      Error Append(const std::string& path, const std::string& data);
      /** Write the contents of a file in binary format */
      Error Write(const std::string& path, const std::unique_ptr<byte[]>& data, const uint32_t size);
      /** Write the contents of a file in text format */
      Error Write(const std::string& path, const std::string& data);

      /** Check if a file exists */
      inline bool Exists(const std::string& path);
      /** Check if a file is open */
      inline bool IsOpen(const std::string& path);
      /** Check if a file is empty */
      inline bool IsEmpty(const std::string& path);

      /** Get the size of a file in bytes */
      inline uint32_t GetSize(const std::string& path);
      /** Get the extension of a file */
      inline std::string GetExtension(const std::string& path);
      /** Get the filename without the extension */
      inline std::string GetFilename(const std::string& path);
      /** Get the path without the filename */
      inline std::string GetPathWithoutFilename(const std::string& path);
      /** Convert relative path to absolute path */
      inline std::string GetAbsolutePath(const std::string& path);
      /** Builds a path string from path fragments */
      template<typename... Args>
      inline std::string BuildPath(const Args&... args);
      /** Get the current working directory */
      inline std::string GetWorkingDirectory();
      /** Deletes a file */
      inline void Delete(const std::string& path);

      /** Creates all the needed directories in a path if they do not exist */
      static void CreateDirectories(const std::string& path);
}

#endif // IO_FILE_HPP

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
