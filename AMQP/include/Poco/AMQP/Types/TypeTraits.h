#ifndef AMQP_Types_TypeTraits_INCLUDED
#define AMQP_Types_TypeTraits_INCLUDED


#include <cstring>
#include <type_traits>


namespace Poco {
namespace AMQP {


template<typename T>
struct isAMQPType
	: std::false_type
{
};


template<typename T>
struct AMQPTypeTraits 
	: std::false_type
{
};


} } // namespace Poco::AMQP


#endif // AMQP_Types_TypeTraits_INCLUDED
