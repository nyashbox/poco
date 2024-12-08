#ifndef AMQP_Types_String_INCLUDED
#define AMQP_Types_String_INCLUDED


#include "Poco/AMQP/Types/Integers.h"
#include "Poco/ByteOrder.h"
#include "Poco/Buffer.h"
#include <limits>


namespace Poco {
namespace AMQP {


template<typename T>
class BaseStr;


using ShortStr = AMQP::BaseStr<Octet>;
using LongStr  = AMQP::BaseStr<Long>;


template <typename T> 
class BaseStr 
{
public:
	BaseStr(const std::string_view string);
	~BaseStr();

	const Poco::Buffer<AMQP::Octet> &getBuffer(void) const;
protected:
private:
	Poco::Buffer<AMQP::Octet> _data{0};

};


template<typename T>
BaseStr<T>::BaseStr(const std::string_view string)
{
	if (string.size() > std::numeric_limits<T>::max())
	{
		throw Poco::RuntimeException("Input string too long!");
	}

	_data.setCapacity(string.size()+sizeof(T));

	const T stringSize = Poco::ByteOrder::toNetwork(static_cast<T>(string.size()));

	_data.append(reinterpret_cast<const AMQP::Octet *>(&stringSize), sizeof(T));
	_data.append(reinterpret_cast<const AMQP::Octet *>(string.data()), string.size());
};


//
// inlines
//


template<typename T>
BaseStr<T>::~BaseStr()
{
}


template<typename T>
const Poco::Buffer<AMQP::Octet> &BaseStr<T>::getBuffer(void) const 
{
	return _data;
}


} } // namespace Poco::AMQP


#endif // AMQP_Types_String_INCLUDED
