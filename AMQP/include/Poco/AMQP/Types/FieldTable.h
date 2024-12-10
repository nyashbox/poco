#ifndef AMQP_Types_FieldTable_INCLUDED
#define AMQP_Types_FieldTable_INCLUDED


#include "Poco/AMQP/Types/Integers.h"
#include "Poco/AMQP/Types/Strings.h"
#include "Poco/AMQP/Types/TypeTraits.h"


namespace Poco {
namespace AMQP {


class FieldTable final
{
	public:
		FieldTable();
		~FieldTable();

		template<typename T>
		typename std::enable_if_t<isAMQPType<T>::value, void>
		insert(const AMQP::ShortStr &key, const T value);

		const Poco::Buffer<AMQP::Octet> &getBuffer(void) const;

	protected:
	private:
		Poco::Buffer<AMQP::Octet> _data{0};
};


//
// inlines
//


inline FieldTable::FieldTable()
{
};


inline FieldTable::~FieldTable()
{
};


inline const Poco::Buffer<AMQP::Octet> &FieldTable::getBuffer() const 
{
	return _data;
}


template<typename T>
typename std::enable_if_t<isAMQPType<T>::value, void>
FieldTable::insert(const AMQP::ShortStr &key, const T value) 
{
	_data.append(key.getBuffer());
	_data.append(AMQP::AMQPTypeTraits<T>::FIELD_VALUE);

	if constexpr (AMQP::isAMQPInteger_v<T>)
		_data.append(reinterpret_cast<const AMQP::Octet *>(&value), sizeof(T));
	else
		_data.append(value.getBuffer());
}


} } // namespace Poco::AMQP


#endif // AMQP_Types_FieldTable_INCLUDED
