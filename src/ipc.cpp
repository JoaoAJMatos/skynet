//
// Created by JoaoAJMatos on 10/11/2023.
//

/** C++ Includes */
#include <iostream>
#include <fstream>

/** Local Includes */
#include "ipc.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////

#define ASSERT_PIPE_OPENED(pipe) if (!pipe.is_open()) { throw skynet::IPCException("Pipe is not opened."); }

//////////////////////////////////////////////////////////////////////////////////////////////

/** Write a string to the pipe */
void skynet::IPC::WriteToPipe(const std::string& message) {
      std::ofstream pipe(pipe_name, std::ios::out | std::ios::binary);
      ASSERT_PIPE_OPENED(pipe);
      pipe << message;
      pipe.close();
}

/** Write bytes to the pipe */
void skynet::IPC::WriteToPipe(std::vector<byte> data) {
      std::ofstream pipe(pipe_name, std::ios::out | std::ios::binary);
      ASSERT_PIPE_OPENED(pipe);
      pipe.write((char*)data.data(), data.size());
      pipe.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////

/** Read a string from the pipe */
std::string skynet::IPC::ReadFromPipe() {
      std::ifstream pipe(pipe_name, std::ios::in | std::ios::binary);
      ASSERT_PIPE_OPENED(pipe);
      std::string message;
      std::getline(pipe, message);
      pipe.close();

      return message;
}

/** Read bytes from the pipe */
std::vector<byte> skynet::IPC::ReadFromPipeAsBytes() {
      std::ifstream pipe(pipe_name, std::ios::in | std::ios::binary);
      ASSERT_PIPE_OPENED(pipe);
      std::vector<byte> data;
      pipe.seekg(0, std::ios::end);
      data.resize(pipe.tellg());
      pipe.seekg(0, std::ios::beg);
      pipe.read((char*)data.data(), data.size());
      pipe.close();

      return data;
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

