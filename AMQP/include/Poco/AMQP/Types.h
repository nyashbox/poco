#ifndef AMQP_Types_INCLUDED
#define AMQP_Types_INCLUDED

#include "Poco/Buffer.h"
#include "Poco/ByteOrder.h"
#include "Poco/Exception.h"
#include "Poco/Types.h"

#include <limits>

namespace Poco {
namespace AMQP {

using Octet = Poco::UInt8;
using Short = Poco::UInt16;
using Long = Poco::UInt32;
using LongLong = Poco::UInt64;

template <typename T> class BaseStr {
public:
  BaseStr(const std::string_view string) {
    if (string.size() > std::numeric_limits<T>::max())
      throw Poco::RuntimeException("Input string too long!");

    _data.resize(string.size());
    std::copy(string.begin(), string.end(), _data.begin());
  }

  void marshall(AMQP::Octet *dest) {
    T size = static_cast<T>(_data.sizeBytes());

    if (sizeof(T) > 1)
      size = Poco::ByteOrder::toNetwork(size);

    std::memcpy(dest, &size, sizeof(T));
    std::copy(_data.begin(), _data.end(), dest + sizeof(T));
  }

  const AMQP::LongLong getMarshalledSize(void) const {
    return sizeof(T) + _data.sizeBytes();
  }

  AMQP::Octet *begin() { return _data.begin(); };
  AMQP::Octet *end() { return _data.end(); };

  const AMQP::Octet *cbegin() { return _data.begin(); };
  const AMQP::Octet *cend() { return _data.end(); };

  ~BaseStr() = default;

protected:
private:
  Poco::Buffer<AMQP::Octet> _data{0};
};

using ShortStr = BaseStr<AMQP::Octet>;
using LongStr = BaseStr<AMQP::Long>;

} // namespace AMQP
} // namespace Poco

#endif // AMQP_Types_INCLUDED
