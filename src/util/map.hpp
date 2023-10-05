/**
 * @file    map.hpp
 * @author  JoaoAJMatos
 *
 * @brief   For some reason, C++'s std::map cannot f****** be included
 *          anywhere on this project without throwing a bunch of compiler
 *          errors regarding the standard namespace because of my MacOS
 *          development SDK. I have no idea why this happens, but I'm not
 *          going to waste time trying to figure it out. If you know why
 *          this happens, please let me know or contact me at joaoafonsoj2021@gmail.com.
 *
 *          Instead of trying to figure it out (which I might do later), I
 *          will just implement my own map class.
 *
 * @date    2023-10-03
 * 
 * @copyright Copyright (c) 2023
 * @license MIT
 */

#ifndef SKYNET_MAP_HPP
#define SKYNET_MAP_HPP

/* C++ includes */
#include <string>
#include <utility>
#include <iostream>
#include <vector>

namespace util
{
      template <typename K, typename V>
      class Map
      {
      public:
            Map() = default;
            ~Map() = default;

            /**
             * @brief   Inserts a new key-value pair into the map.
             *
             * @param   key
             * @param   value
             */
            void Insert(K key, V value) {
                  keys_.push_back(key);
                  values_.push_back(value);
            }

            /**
             * @brief   Returns the value associated with the given key.
             *
             * @param   key
             * @return  V
             */
            V& operator[](K key) {
                  for (int i = 0; i < keys_.size(); i++) {
                        if (keys_[i] == key) {
                              return values_[i];
                        }
                  }
                  return values_[0];
            }

            /**
             * @brief   Returns a vector containing all the keys in the map.
             *
             * @return  std::vector<K>
             */
            std::vector<K> Keys() {
                  return keys_;
            }

            /**
             * @brief   Returns a vector containing all the values in the map.
             *
             * @return  std::vector<V>
             */
            std::vector<V> Values() {
                  return values_;
            }

            /**
             * @brief   Returns the value associated with the given key.
             *
             * @param   key
             * @return  V
             */
            std::pair<K, V> At(int index) {
                  return std::make_pair(keys_[index], values_[index]);
            }

            /**
             * @brief   Returns the size of the map.
             * 
             * @return  int
             */
            int Size() {
                  return keys_.size();
            }

            /**
             * @brief   Returns true if the map is empty.
             * 
             * @return  bool
             */
            bool Empty() {
                  return keys_.empty();
            }

            /**
             * @brief   Clears the map.
             */
            void Clear() {
                  keys_.clear();
                  values_.clear();
            }

            /**
             * @brief   Removes the given key from the map.
             *
             * @param   key
             */
            void Remove(K key) {
                  for (int i = 0; i < keys_.size(); i++) {
                        if (keys_[i] == key) {
                              keys_.erase(keys_.begin() + i);
                              values_.erase(values_.begin() + i);
                        }
                  }
            }

            /**
             * @brief   Returns true if the map contains the given key.
             * 
             * @param   key
             * @return  bool
             */
            bool Contains(K key) {
                  for (int i = 0; i < keys_.size(); i++) {
                        if (keys_[i] == key) {
                              return true;
                        }
                  }
                  return false;
            }

            /**
             * @brief   Returns a string representation of the map.
             * 
             * @return  std::string
             */
            std::string ToString() {
                  std::string str = "{";
                  for (int i = 0; i < keys_.size(); i++) {
                        str += "\"" + keys_[i] + "\": \"" + values_[i] + "\"";
                        if (i != keys_.size() - 1) {
                              str += ", ";
                        }
                  }
                  str += "}";
                  return str;
            }
      private:
            std::vector<K> keys_;
            std::vector<V> values_;
      };
}

#endif // SKYNET_MAP_HPP
