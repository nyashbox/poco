#ifndef AMQP_Types_FieldTable_INCLUDED
#define AMQP_Types_FieldTable_INCLUDED


#include "Poco/AMQP/Types/Integers.h"
#include "Poco/AMQP/Types/Strings.h"

namespace Poco {
namespace AMQP {


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


template<>
inline void FieldTable::insert(const AMQP::ShortStr &key, const AMQP::Octet value) 
{
	_insert(key, value, 'B');
}


template<>
inline void FieldTable::insert(const AMQP::ShortStr &key, const AMQP::Short value)
{
	_insert(key, value, 'u');
}


template<>
inline void FieldTable::insert(const AMQP::ShortStr &key, const AMQP::Long value)
{
	_insert(key, value, 'i');
}


template<>
inline void FieldTable::insert(const AMQP::ShortStr &key, const AMQP::LongLong value)
{
	_insert(key, value, 'l');
}


template<>
inline void FieldTable::insert(const AMQP::ShortStr &key, const AMQP::ShortStr value)
{
	_insert(key, value, 's');
}


template<>
inline void FieldTable::insert(const AMQP::ShortStr &key, const AMQP::LongStr value)
{
	_insert(key, value, 'S');
}


template<typename T>
inline void FieldTable::_insert(const AMQP::ShortStr &key, const T value, const AMQP::Octet type)
{
	_data.append(key.getBuffer());
	_data.append(type);

	if constexpr (std::is_unsigned_v<T>)
		_data.append(reinterpret_cast<const AMQP::Octet *>(&value), sizeof(T));
	else
		_data.append(value.getBuffer());
}


} } // namespace Poco::AMQP


#endif // AMQP_Types_FieldTable_INCLUDED
