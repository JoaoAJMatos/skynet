//
// Created by João Matos on 29/09/2023.
//

/** Skynet includes */
#include <io/file.hpp>

/** Local includes */
#include "config_parser.hpp"


/** MACROS */
#define THROW_PARSE_ERROR(filename, lineNumber, line) \
        throw std::runtime_error("Error: Invalid configuration file format in " + \
        filename + " at line " + std::to_string(lineNumber) + " near: " + line);


/**
 * @brief Saves the given configuration into a file
 *
 * @param filename
 * @param config 
 * @return true on success, false otherwise
 */
bool io::config::Save(const std::string& filename, const ConfigMap& config) {
      std:string content;
      for (auto& [key, value] : config) {
            content += key + "=" + value + "\n";
      }
      return io::file::Write(filename, content) == io::file::Error::FILE_SUCCESS;
}

/**
 * @brief Loads the given configuration from a file
 *
 * @param filename
 * @return ConfigMap 
 */
ConfigMap io::config::Load(const std::string& filename) {
      ConfigMap config;
      std::string content = io::file::Read(filename);
      std::istringstream iss(content);

      std::string line;
      int lineNumber = 0;

      while (std::getline(iss, line)) {
            lineNumber++;

            /** Skip comments */
            size_t pos = line.find('#');
            if (pos != std::string::npos) line.erase(pos);

            /** Trim leading and trailing whitespaces */
            line = trim(line);

            /** Skip empty lines */
            if (line.empty()) continue;

            /** Split key and value */
            pos = line.find('=');
            if (pos == std::string::npos) {
                  THROW_PARSE_ERROR(filename, lineNumber, line);
            }

            std::string key = trim(line.substr(0, pos));
            std::string value = trim(line.substr(pos + 1));
            config[key] = value;
      }

      return config;
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
