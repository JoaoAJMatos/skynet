/**
 * @file   main.cpp
 * @author JoaoAJMatos
 *
 * @brief Entry point of the unit tests
 *
 * @version 0.1
 * @date 2023-02-01
 * @license MIT
 * @copyright Copyright (c) 2023
 */

/* Skynet includes */
#include <io/stdout.hpp>

/* Test Imports */
#include "sha256_test.hpp"
#include "ecdsa_test.hpp"
#include "io_test.hpp"

/* UNIPP test framework */
#include "unipp.hpp"

/**
 * This is the entry point of the unit tests.
 *
 * Here is where all the tests are defined and run.
 */
int main(void) {
      io::stdout::WriteLine(COLORED(GREEN, "Running unit tests..."));


      RUN(
            SUITE("Cryptography Interface", "Tests Skynet's cryptography interface",
                  TEST("Sha-256 Test", "Tests the SHA256 hash function", HashTest),
                  TEST("ECDSA Test", "Tests the ECDSA signature algorithm", EcdsaTest)
            ),
            SUITE("Input/Output Interface", "Tests Skynet's I/O interface",
                  TEST("Write to file", "Tests the filesystem interface for writing to files", WriteFileTest),
                  TEST("Read from file", "Tests the filesystem interface for reading from files", ReadFileTest),
                  TEST("Append to file", "Tests the filesystem interface for appending to files", AppendFileTest),
                  TEST("Delete file", "Tests the filesystem interface for deleting files", DeleteFileTest),
                  TEST("Save Config", "Tests the config parser for saving config files", ConfigParserSaveTest),
                  TEST("Load Config", "Tests the config parser for loading config files", ConfigParserLoadTest)
            )
      );

      return 0;
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
