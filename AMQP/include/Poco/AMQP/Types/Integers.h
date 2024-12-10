#ifndef AMQP_Types_Integers_INCLUDED
#define AMQP_Types_Integers_INCLUDED


#include "Poco/AMQP/Types/TypeTraits.h"
#include "Poco/Types.h"
#include "Poco/ByteOrder.h"
#include <cstring>


namespace Poco {
namespace AMQP {


using Octet    = Poco::UInt8;
using Short    = Poco::UInt16;
using Long     = Poco::UInt32;
using LongLong = Poco::UInt64;


template<typename T>
struct isAMQPInteger 
	: std::disjunction<
		std::is_same<T, AMQP::Octet>, 
		std::is_same<T, AMQP::Short>,
		std::is_same<T, AMQP::Long>, 
		std::is_same<T, AMQP::LongLong>>
{
};


template<typename T>
inline constexpr bool isAMQPInteger_v = isAMQPInteger<T>::value;


template<typename T>
struct AMQPIntegerTypeTraits 
{
	static void *write(const T value, void *dest)
	{
		const T networkValue = ByteOrder::toNetwork(value);
		return std::memcpy(dest, &networkValue, sizeof(T));
	}
};


template<>
struct AMQPTypeTraits<AMQP::Octet> 
	: AMQPIntegerTypeTraits<AMQP::Octet>
{
	static constexpr AMQP::Octet FIELD_VALUE = 'B';
};


template<>
struct AMQPTypeTraits<AMQP::Short>
	: AMQPIntegerTypeTraits<AMQP::Short>
{
	static constexpr AMQP::Octet FIELD_VALUE = 'u';
};


template<>
struct AMQPTypeTraits<AMQP::Long>
	: AMQPIntegerTypeTraits<AMQP::Long>
{
	static constexpr AMQP::Octet FIELD_VALUE = 'i';
};


template<>
struct AMQPTypeTraits<AMQP::LongLong>
	: AMQPIntegerTypeTraits<AMQP::LongLong>
{
	static constexpr AMQP::Octet FIELD_VALUE = 'l';
};


template<>
struct isAMQPType<AMQP::Octet>
	: std::true_type 
{
};


template<>
struct isAMQPType<AMQP::Short>
	: std::true_type 
{
};


template<>
struct isAMQPType<AMQP::Long>
	: std::true_type 
{
};


template<>
struct isAMQPType<AMQP::LongLong>
	: std::true_type 
{
};


} } // namespace Poco::AMQP


#endif // AMQP_Types_Integers_INCLUDED
