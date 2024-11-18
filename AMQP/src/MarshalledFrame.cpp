#include "Poco/AMQP/Frames/MarshalledFrame.h"
#include "Poco/AMQP/Types.h"

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
  // Allocate frame memory
  _frameSize = size + HEADER_SIZE + sizeof(FRAME_END);
  _data = std::make_unique<std::byte[]>(_frameSize);

  // Set frame data
  setType(type);
  setChannel(channel);
  setSize(size);

  // Frame end
  _data[size + HEADER_SIZE] = static_cast<std::byte>(FRAME_END);
};

MarshalledFrame::MarshalledFrame(MarshalledFrame &&other) noexcept
    : _data(std::move(other._data)), _frameSize(other._frameSize) {};

MarshalledFrame &MarshalledFrame::operator=(MarshalledFrame &&other) noexcept {
  if (this != &other) {
    _frameSize = other._frameSize;
    _data = std::move(other._data);
  }

  return *this;
};

void MarshalledFrame::setChannel(const AMQP::Short channel) {
  std::memcpy(&_data[CHANNEL_OFFSET], &channel, sizeof(channel));
}

void MarshalledFrame::setType(const AMQP::Octet type) {
  std::memcpy(&_data[TYPE_OFFSET], &type, sizeof(type));
}

void MarshalledFrame::setSize(const AMQP::Long size) {
  std::memcpy(&_data[SIZE_OFFSET], &size, sizeof(size));
}

AMQP::Short MarshalledFrame::getChannel(void) const {
  std::byte *channel = &_data[CHANNEL_OFFSET];

  AMQP::Short ret = static_cast<AMQP::Octet>(channel[0]) << 0 |
                    static_cast<AMQP::Octet>(channel[1]) << 8;

  return ret;
}

AMQP::Octet MarshalledFrame::getType(void) const {
  std::byte *type = &_data[TYPE_OFFSET];

  AMQP::Octet ret = static_cast<AMQP::Octet>(type[0]) << 0;

  return ret;
}

AMQP::Long MarshalledFrame::getSize(void) const {
  std::byte *size = &_data[SIZE_OFFSET];

  AMQP::Long ret = static_cast<AMQP::Octet>(size[0]) << 0 |
                   static_cast<AMQP::Octet>(size[1]) << 8 |
                   static_cast<AMQP::Octet>(size[2]) << 16 |
                   static_cast<AMQP::Octet>(size[3]) << 24;

  return ret;
}

std::byte *MarshalledFrame::getPayload(void) const {
  auto framePointer = _data.get();

  return &framePointer[HEADER_SIZE];
}

std::byte *MarshalledFrame::getData(void) const {
  std::byte *framePointer = _data.get();

  return framePointer;
}

AMQP::Long MarshalledFrame::getFrameSize(void) const { return _frameSize; }

} // namespace AMQP
} // namespace Poco
