#ifndef AMQP_MarshalledFrame_INCLUDED
#define AMQP_MarshalledFrame_INCLUDED

#include <cstddef>
#include <cstdint>

#include <memory>

namespace Poco {
namespace AMQP {

class MarshalledFrame {
public:
  MarshalledFrame(uint32_t size = 0);
  MarshalledFrame(uint8_t type, uint16_t channel, uint32_t size);

  MarshalledFrame(const MarshalledFrame &other) = delete;
  MarshalledFrame &operator=(MarshalledFrame &other) = delete;

  MarshalledFrame(MarshalledFrame &&other) noexcept;
  MarshalledFrame &operator=(MarshalledFrame &&other) noexcept;

  ~MarshalledFrame() = default;

  void setChannel(const uint16_t channel);
  void setType(const uint8_t type);
  void setSize(const uint32_t size);

  uint16_t getChannel(void) const;
  uint8_t getType(void) const;
  uint32_t getSize(void) const;

  std::byte *getData(void) const;
  std::byte *getPayload(void) const;
  size_t getFrameSize(void) const;

protected:
private:
  std::unique_ptr<std::byte[]> _data;
  size_t _frameSize;
};

} // namespace AMQP
} // namespace Poco

#endif // AMQP_MarshalledFrame_INCLUDED
