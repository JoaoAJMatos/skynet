#ifndef SKYNET_PACKET_HPP
#define SKYNET_PACKET_HPP

/** C++ headers */
#include <cstdint>

/** Skynet headers */
#include <types.hpp>

namespace net::packet
{
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

		/** Serialization and deserialization */
		byte* Serialize() const;
		static Packet Deserialize(const byte* data);
		
		/** Getters */
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
