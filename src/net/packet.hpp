#ifndef SKYNET_PACKET_HPP
#define SKYNET_PACKET_HPP

/** C++ headers */
#include <cstdint>

/** Skynet headers */
#include <types.hpp>

namespace net::packet
{
      /** Packet constants */
	constexpr uint16_t MAX_PACKET_SIZE = 65535;
	constexpr uint16_t MAX_PACKET_DATA_SIZE = MAX_PACKET_SIZE - sizeof(SHeaders_t);

	/** Packet type = 1 byte (max 256 packet types) */
	enum class Type : uint8_t
	{
		Empty = 0,
		Ack = 1,
		Data = 2,
	};

	/** Packet headers */
	typedef struct SHeaders {
		Type type;
		uint16_t size;
		uint16_t id;
	} SHeaders_t;

	
	class Packet
	{
	public:
		Packet();
		Packet(Type type);
		~Packet();

            /** Serialize the packet to a byte array */
		byte* Serialize() const;
            /** Deserialize the given byte array to a packet */
		static Packet Deserialize(const byte* data);
		
		/** Getters */
            /** Returns the payload casted to the given type */
		template <typename T>
		T GetDataAs<T>() const;
		Type GetType() const;
		uint16_t GetSize() const;
		uint16_t GetId() const;
		
		/** Setters */
		void SetPayload(const byte* data, uint16_t size);
		void SetPayload(const std::string& data);
		void SetType(Type type);
		void SetId(uint16_t id);
	private:
		SHeaders_t headers_;
		byte data_[MAX_PACKET_DATA_SIZE];
	};
}

#endif //!SKYNET_PACKET_HPP


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
// SOFTWARE
