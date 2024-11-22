#include "Poco/AMQP/Frames/MarshalledFrame.h"
#include "Poco/AMQP/Types.h"
#include "Poco/ByteOrder.h"

#include <cstring>
#include <memory>

namespace Poco {
namespace AMQP {

constexpr AMQP::Octet TYPE_OFFSET = 0x00;
constexpr AMQP::Octet CHANNEL_OFFSET = 0x01;
constexpr AMQP::Octet SIZE_OFFSET = 0x03;

constexpr AMQP::Octet HEADER_SIZE = 0x07;
constexpr AMQP::Octet FRAME_END = 0xCE;

MarshalledFrame::MarshalledFrame(AMQP::Long size)
    : MarshalledFrame(0x00, 0, size) {};

MarshalledFrame::MarshalledFrame(AMQP::Octet type, AMQP::Short channel,
                                 AMQP::Long size) {
  _data.resize(size + HEADER_SIZE + sizeof(FRAME_END));

  // Set frame data
  setType(type);
  setChannel(channel);
  setSize(size);

  // Frame end
  _data[size + HEADER_SIZE] = FRAME_END;
};

MarshalledFrame::MarshalledFrame(MarshalledFrame &&other) noexcept
    : _data(std::move(other._data)) {};

MarshalledFrame &MarshalledFrame::operator=(MarshalledFrame &&other) noexcept {
  if (this != &other)
    _data = std::move(other._data);

  return *this;
};

void MarshalledFrame::setChannel(const AMQP::Short channel) {
  AMQP::Octet *channelPtr = &_data[CHANNEL_OFFSET];
  AMQP::Short convertedChannel = Poco::ByteOrder::toNetwork(channel);

  std::memcpy(channelPtr, &convertedChannel, sizeof(channel));
}

void MarshalledFrame::setType(const AMQP::Octet type) {
  _data[TYPE_OFFSET] = type;
}

void MarshalledFrame::setSize(const AMQP::Long size) {
  AMQP::Octet *sizePtr = &_data[SIZE_OFFSET];

  AMQP::Long convertedSize = Poco::ByteOrder::toNetwork(size);

  std::memcpy(sizePtr, &convertedSize, sizeof(size));
}

AMQP::Short MarshalledFrame::getChannel(void) const {
  const AMQP::Octet *channel = &_data[CHANNEL_OFFSET];

#if POCO_ARCH_LITTLE_ENDIAN
  AMQP::Short ret = channel[1] << 0 | channel[0] << 8;
#else
  AMQP::Short ret = channel[0] << 0 | channel[1] << 8;
#endif

  return ret;
}

AMQP::Octet MarshalledFrame::getType(void) const { return _data[0]; }

AMQP::Long MarshalledFrame::getSize(void) const {
  const AMQP::Octet *size = &_data[SIZE_OFFSET];

#if POCO_ARCH_LITTLE_ENDIAN
  AMQP::Long ret = size[3] << 0 | size[2] << 8 | size[1] << 16 | size[0] << 24;
#else
  AMQP::Long ret = size[0] << 0 | size[1] << 8 | size[2] << 16 | size[3] << 24;
#endif

  return ret;
}

const AMQP::Octet *MarshalledFrame::getPayload(void) const {
  return &_data[HEADER_SIZE];
}

AMQP::Octet *MarshalledFrame::begin() { return _data.begin(); };
AMQP::Octet *MarshalledFrame::end() { return _data.end(); };

const AMQP::Octet *MarshalledFrame::cbegin() const { return _data.begin(); };
const AMQP::Octet *MarshalledFrame::cend() const { return _data.end(); };

AMQP::Long MarshalledFrame::getFrameSize(void) const {
  return _data.sizeBytes();
}

} // namespace AMQP
} // namespace Poco
