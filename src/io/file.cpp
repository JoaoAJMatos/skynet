//
// Created by João Matos on 29/09/2023.
//

/** C++ includes */
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>

/** Local includes */
#include "file.hpp"

/**
 * @brief Checks if a file exists
 *
 * @param path The file to check
 * @return true if the file exists, false otherwise
 */
bool io::file::Exists(const std::string& path) {
      std::ifstream file(path);
      return file.good();
}

/**
 * @brief Checks if a file is open
 *
 * @param path The file to check
 * @return true if the file is open, false otherwise
 */
bool io::file::IsOpen(const std::string& path) {
      std::ifstream file(path);
      return file.is_open();
}

/**
 * @brief Checks if a file is empty
 *
 * @param path The file to check
 * @return true if the file is empty, false otherwise
 */
bool io::file::IsEmpty(const std::string& path) {
      std::ifstream file(path);
      return file.peek() == std::ifstream::traits_type::eof();
}

/**
 * @brief Returns the size of the file in bytes
 *
 * @param path The file to check
 * @return The size of the file in bytes
 */
uint32_t io::file::GetSize(const std::string& path) {
      std::ifstream file(path, std::ios::binary | std::ios::ate);
      return file.tellg();
}

/**
 * @brief Returns the extension of the file
 *
 * @param path The file to check
 * @return The extension of the file
 */
std::string io::file::GetExtension(const std::string& path) {
      return std::filesystem::path(path).extension().string();
}

/**
 * @brief Returns the path without the extension
 *
 * @param path The file to check
 * @return The path without the extension
 */
std::string io::file::GetPathWithoutFilename(const std::string& path) {
      return std::filesystem::path(path).filename().string();
}

/**
 * @brief Returns the absolute path of the file
 *
 * @param path The file to check
 * @return The absolute path of the file
 */
std::string io::file::GetAbsolutePath(const std::string& path) {
      return std::filesystem::absolute(path).string();
}

/**
 * @brief Builds a path string from path fragments
 *
 * @param args The path fragments
 * @return The built path (absolute path)
 */
template<typename... Args>
std::string io::file::BuildPath(const Args&... args) {
      std::string path = std::filesystem::path(args...).string();
      return GetAbsolutePath(path);
}

/**
 * @brief Returns the current working directory
 *
 * @return The current working directory
 */
std::string io::file::GetWorkingDirectory() {
      return std::filesystem::current_path().string();
}

/**
 * @brief Creates the directories in the path
 *
 * Creates the directories in the path all the way to the 
 * filename if they dont exist.
 */
static void io::file::CreateDirectories(const std::string& path) {
      std::string dir = "";
      for (const auto& c : path) {
            if (c == DIRECTORY_SEPARATOR) {
                  if (!std::filesystem::exists(dir)) {
                        std::filesystem::create_directory(dir);
                  }
            }
            dir += c;
      }
}

/**
 * @brief Reads the contents of a file in binary format
 *
 * @param path The file to read
 * @param data The data read from the file
 * @param size The size of the data read from the file
 *
 * @return Error code
 */
io::file::Error io::file::Read(const std::string& path, std::unique_ptr<byte[]>& data, uint32_t& size) {
      /** Check if the file exists */
      if (!Exists(path)) return io::file::Error::FILE_NOT_FOUND;
      if (IsEmpty(path)) return io::file::Error::FILE_EMPTY;

      /** Open the file */
      std::ifstream file(path, std::ios::binary | std::ios::ate);
      if (!file.is_open()) return io::file::Error::FILE_NOT_OPEN;

      /** Allocate memory for the data */
      size = static_cast<uint32_t>(io::file::GetSize(path));
      data = std::make_unique<byte[]>(size);

      /** Read file contents */
      file.seekg(0, std::ios::beg);
      if (!file.read(reinterpret_cast<char*>(data.get()), size)) {
            file.close();
            return io::file::Error::FILE_READ_ERROR;
      }

      file.close();
      return io::file::Error::FILE_SUCCESS;
}

/**
 * @brief Reads the contents of a file in text format
 *
 * @param path The file to read
 * @param data The data read from the file
 *
 * @return Error code
 */
io::file::Error io::file::Read(const std::string& path, std::string& data) {
      /** Check if the file exists */
      if (!Exists(path)) return io::file::Error::FILE_NOT_FOUND;
      if (IsEmpty(path)) return io::file::Error::FILE_EMPTY;

      /** Open the file */
      std::ifstream file(path, std::ios::in);
      if (!file.is_open()) return io::file::Error::FILE_NOT_OPEN;

      /** Read file contents */
      std::stringstream buffer;
      buffer << file.rdbuf();
      data = buffer.str();

      file.close();
      return io::file::Error::FILE_SUCCESS;
}

/**
 * @brief Appends data to a file in binary format
 *
 * If the file does not exist, and the path contains directories
 * that do not exist, they will be created.
 *
 * @param path The file to append to
 * @param data The data to append to the file
 * @param size The size of the data to append to the file
 *
 * @return Error code
 */
io::file::Error io::file::Append(const std::string& path, std::unique_ptr<byte[]>& data, uint32_t& size) {
      /** Create all the directories if they don't exist */
      CreateDirectories(path);

      /** Open the file */
      std::ofstream file(path, std::ios::binary | std::ios::app);
      if (!file.is_open()) return io::file::Error::FILE_NOT_OPEN;

      /** Write the data to the file */
      file.write(reinterpret_cast<char*>(data.get()), size);

      file.close();
      return io::file::Error::FILE_SUCCESS;
}

/**
 * @brief Appends data to a file in text format
 *
 * If the file does not exist, and the path contains directories
 * that do not exist, they will be created.
 *
 * @param path The file to append to
 * @param data The data to append to the file
 *
 * @return Error code
 */
io::file::Error io::file::Append(const std::string& path, const std::string& data) {
      /** Create all the directories if they don't exist */
      CreateDirectories(path);

      /** Open the file */
      std::ofstream file(path, std::ios::app);
      if (!file.is_open()) return io::file::Error::FILE_NOT_OPEN;

      /** Write the data to the file */
      file << data;

      file.close();
      return io::file::Error::FILE_SUCCESS;
}

/**
 * @brief Writes data to a file in binary format
 *
 * If the file does not exist, and the path contains directories
 * that do not exist, they will be created.
 *
 * @param path The file to write to
 * @param data The data to write to the file
 * @param size The size of the data to write to the file
 *
 * @return Error code
 */
io::file::Error io::file::Write(const std::string& path, const std::unique_ptr<byte[]>& data, const uint32_t size) {
      /** Create all the directories if they don't exist */
      CreateDirectories(path);

      /** Open the file */
      std::ofstream file(path, std::ios::binary);
      if (!file.is_open()) return io::file::Error::FILE_NOT_OPEN;

      /** Write the data to the file */
      file.write(reinterpret_cast<const char*>(data.get()), size);

      file.close();
      return io::file::Error::FILE_SUCCESS;
}

/**
 * @brief Writes data to a file in text format
 *
 * If the file does not exist, and the path contains directories
 * that do not exist, they will be created.
 *
 * @param path The file to write to
 * @param data The data to write to the file
 *
 * @return Error code
 */
io::file::Error io::file::Write(const std::string& path, const std::string& data) {
      /** Create all the directories if they don't exist */
      CreateDirectories(path);

      /** Open the file */
      std::ofstream file(path);
      if (!file.is_open()) return io::file::Error::FILE_NOT_OPEN;

      /** Write the data to the file */
      file << data;

      file.close();
      return io::file::Error::FILE_SUCCESS;
}

/**
 * @brief Deletes a file
 *
 * @param path The file to delete
 */
void io::file::Delete(const std::string& path) {
      std::remove(path.c_str());
}

/**
 * @brief Returns the error message for the given error code
 */
std::string io::file::ErrorToString(io::file::Error error) {
      switch (error) {
            case io::file::Error::FILE_SUCCESS: return "Success";
            case io::file::Error::FILE_NOT_FOUND: return "File not found";
            case io::file::Error::FILE_ALREADY_OPEN: return "File already open";
            case io::file::Error::FILE_EMPTY: return "File is empty";
            case io::file::Error::FILE_NOT_OPEN: return "File not open";
            case io::file::Error::FILE_READ_ERROR: return "File read error";
            case io::file::Error::FILE_WRITE_ERROR: return "File write error";
            case io::file::Error::FILE_ALREADY_EXISTS: return "File already exists";
      } // no default case to force compiler warning

      return "Unknown error";
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
