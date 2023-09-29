/**
 * @file   io_test.hpp
 * @author JoaoAJMatos
 *
 * @brief Test the io module. From file utilities to logging.
 *
 * @version 0.1
 * @date 2023-02-01
 * @license MIT
 * @copyright Copyright (c) 2023
 */

/** Skynet includes */
#include <io/file.hpp>

/** Helper functions */
static bool StringsEqual(const std::string& a, const std::string& b) {
      return a.compare(b) == 0;
}

/**
 * Write to a file. (must be called first in order for the other tests to work)
 *
 * The file should be created and the data should be written to it.
 */
void WriteFileTest() {
      io::file::Error err;
      std::string filename = "test.txt";
      std::string content = "Hello World!";
      err = io::file::Write(filename, content);
      ASSERT_EQUAL(err, io::file::Error::FILE_SUCCESS, "Failed to write to file (" + io::file::ErrorToString(err) + ")");
}

/**
 * Read from a file.
 *
 * Ensure the data is correctly retrieved from the file.
 * The data should match what we wrote in the previous test.
 */
void ReadFileTest() {
      io::file::Error err;
      std::string filename = "test.txt";
      std::string content;
      err = io::file::Read(filename, content);
      ASSERT_EQUAL(err, io::file::Error::FILE_SUCCESS, "Failed to read from file (" + io::file::ErrorToString(err) + ")");
      ASSERT_EQUAL(StringsEqual(content, "Hello World!"), true, "Failed to read from file");
}

/**
 * Append to a file.
 *
 * Append a line to a file, read it's contents and see if the line was appended.
 */
void AppendFileTest() {
      io::file::Error err;
      std::string filename = "test.txt";
      std::string content = "Hello World!";
      err = io::file::Append(filename, content);
      ASSERT_EQUAL(err, io::file::Error::FILE_SUCCESS, "Failed to append to file (" + io::file::ErrorToString(err) + ")");
      err = io::file::Read(filename, content);
      ASSERT_EQUAL(err, io::file::Error::FILE_SUCCESS, "Failed to read from file (" + io::file::ErrorToString(err) + ")");
      ASSERT_EQUAL(StringsEqual(content, "Hello World!Hello World!"), true, "Failed to append to file");
}

/**
 * Delete a file.
 *
 * Delete the file created in the first test.
 */
void DeleteFileTest() {
      std::string filename = "test.txt";
      io::file::Delete(filename);
      ASSERT_EQUAL(io::file::Exists(filename), false, "Failed to delete file");
}

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
