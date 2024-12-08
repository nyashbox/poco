#ifndef AMQP_Types_INCLUDED
#define AMQP_Types_INCLUDED


#include "Poco/Buffer.h"
#include "Poco/ByteOrder.h"
#include "Poco/Exception.h"
#include "Poco/Types.h"
#include <limits>


namespace Poco {
namespace AMQP {


template<typename T>
class BaseStr;


using Octet    = Poco::UInt8;
using Short    = Poco::UInt16;
using Long     = Poco::UInt32;
using LongLong = Poco::UInt64;
using ShortStr = AMQP::BaseStr<Octet>;
using LongStr  = AMQP::BaseStr<Long>;


template <typename T> 
class BaseStr 
{
public:
	BaseStr(const std::string_view string);
	~BaseStr();

	void marshall(AMQP::Octet *dest);

	const Poco::Buffer<AMQP::Octet> &getBuffer(void) const;
	const AMQP::LongLong getMarshalledSize(void) const;

	AMQP::Octet *begin();
	AMQP::Octet *end();

	const AMQP::Octet *cbegin();
	const AMQP::Octet *cend();


protected:
private:
	Poco::Buffer<AMQP::Octet> _data{0};

};


class FieldTable final
{
	public:
		FieldTable();
		~FieldTable();

		template<typename T>
		void insert(const AMQP::ShortStr &key, const T value);

		const Poco::Buffer<AMQP::Octet> &getBuffer(void) const;

	protected:
	private:
		template<typename T>
		void _insert(const AMQP::ShortStr &key, const T value, const AMQP::Octet type);

		Poco::Buffer<AMQP::Octet> _data{0};
};


//
// inlines
//


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
}


template<typename T>
BaseStr<T>::~BaseStr()
{
}


template<typename T>
void BaseStr<T>::marshall(AMQP::Octet *dest)
{
	std::memcpy(dest, _data.begin(), _data.sizeBytes());
}


template<typename T>
const Poco::Buffer<AMQP::Octet> &BaseStr<T>::getBuffer(void) const 
{
	return _data;
}


template<typename T>
const AMQP::LongLong BaseStr<T>::getMarshalledSize(void) const 
{
	return _data.sizeBytes();
}


template<typename T>
AMQP::Octet *BaseStr<T>::begin() 
{ 
	return _data.begin(); 
};


template<typename T>
AMQP::Octet *BaseStr<T>::end() 
{ 
	return _data.end(); 
};


template<typename T>
const AMQP::Octet *BaseStr<T>::cbegin() 
{ 
	return _data.begin(); 
};


template<typename T>
const AMQP::Octet *BaseStr<T>::cend() 
{ 
	return _data.end(); 
};


} } // namespace Poco::AMQP


#endif // AMQP_Types_INCLUDED
