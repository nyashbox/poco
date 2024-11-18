#include "Poco/AMQP/Frames/MarshalledFrame.h"

#include <cstring>

constexpr size_t TYPE_OFFSET = 0x00;
constexpr size_t CHANNEL_OFFSET = 0x01;
constexpr size_t SIZE_OFFSET = 0x03;

constexpr size_t HEADER_SIZE = 0x07;
constexpr uint8_t FRAME_END = 0xCE;

namespace Poco {
namespace AMQP {

MarshalledFrame::MarshalledFrame(uint32_t size)
    : MarshalledFrame(0x00, 0, size) {};

MarshalledFrame::MarshalledFrame(uint8_t type, uint16_t channel,
                                 uint32_t size) {
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

void MarshalledFrame::setChannel(const uint16_t channel) {
  std::memcpy(&_data[CHANNEL_OFFSET], &channel, sizeof(channel));
}

void MarshalledFrame::setType(const uint8_t type) {
  std::memcpy(&_data[TYPE_OFFSET], &type, sizeof(type));
}

void MarshalledFrame::setSize(const uint32_t size) {
  std::memcpy(&_data[SIZE_OFFSET], &size, sizeof(size));
}

uint16_t MarshalledFrame::getChannel(void) const {
  std::byte *channel = &_data[CHANNEL_OFFSET];

  uint16_t ret = static_cast<uint8_t>(channel[0]) << 0 |
                 static_cast<uint8_t>(channel[1]) << 8;

  return ret;
}

uint8_t MarshalledFrame::getType(void) const {
  std::byte *type = &_data[TYPE_OFFSET];

  uint8_t ret = static_cast<uint8_t>(type[0]) << 0;

  return ret;
}

uint32_t MarshalledFrame::getSize(void) const {
  std::byte *size = &_data[SIZE_OFFSET];

  uint32_t ret =
      static_cast<uint8_t>(size[0]) << 0 | static_cast<uint8_t>(size[1]) << 8 |
      static_cast<uint8_t>(size[2]) << 16 | static_cast<uint8_t>(size[3]) << 24;

  return ret;
}

std::byte *MarshalledFrame::getPayload(void) const {
  auto framePointer = _data.get();

  return &framePointer[HEADER_SIZE];
}

std::byte *MarshalledFrame::getData(void) const {
  auto framePointer = _data.get();

  return framePointer;
}

size_t MarshalledFrame::getFrameSize(void) const { return _frameSize; }

} // namespace AMQP
} // namespace Poco
