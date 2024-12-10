#ifndef AMQP_Types_TypeTraits_INCLUDED
#define AMQP_Types_TypeTraits_INCLUDED


#include "Poco/AMQP/Types/Integers.h"
#include "Poco/AMQP/Types/Strings.h"
#include "Poco/AMQP/Types/FieldTable.h"
#include <cstring>
#include <type_traits>


namespace Poco {
namespace AMQP {


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
struct isAMQPString
	: std::disjunction<
		std::is_same<T, AMQP::ShortStr>,
		std::is_same<T, AMQP::LongStr>>
{
};


template<typename T>
inline constexpr bool isAMQPString_v = isAMQPString<T>::value;


template<typename T>
struct isAMQPType 
	: std::disjunction<
		std::is_same<T, AMQP::FieldTable>,
		AMQP::isAMQPInteger<T>,
		AMQP::isAMQPString<T>>
{
};


template<typename T>
struct AMQPTypeTraits 
	: std::false_type
{
};


template<typename T>
struct AMQPIntegerTypeTraits 
{
	void *write(const T value, void *dest)
	{
		const T networkValue = Poco::ByteOrder::toNetwork(value);
		return std::memcpy(dest, &value, sizeof(T));
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
struct AMQPTypeTraits<AMQP::ShortStr>
{
	static constexpr AMQP::Octet FIELD_VALUE = 's';
};


template<>
struct AMQPTypeTraits<AMQP::LongStr>
{
	static constexpr AMQP::Octet FIELD_VALUE = 'S';
};


template<>
struct AMQPTypeTraits<AMQP::FieldTable>
{
	static constexpr AMQP::Octet FIELD_VALUE = 'F';
};


} } // namespace Poco::AMQP


#endif // AMQP_Types_TypeTraits_INCLUDED
