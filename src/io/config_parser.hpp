/**
 * @file config_parser.hpp
 * @author JoaoAJMatos
 * @brief This file contains a series of utility functions to work with configuration files
 * @date 2023-10-01
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef IO_CONFIG_PARSER_HPP
#define IO_CONFIG_PARSER_HPP

/** C++ includes */
#include <map>

/** Local includes */
#include "file.hpp"


/** Configuration map */
typedef std::map<std::string, std::string> ConfigMap;

namespace io::config
{
      /** Saves the given configuration into a file */
      bool Save(const std::string& filename, const ConfigMap& config);
      /** Loads the given configuration from a file */
      ConfigMap Load(const std::string& filename);
}

#endif // IO_CONFIG_PARSER_HPP

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
