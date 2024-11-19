#ifndef AMQP_MarshalledFrame_INCLUDED
#define AMQP_MarshalledFrame_INCLUDED

#include "Poco/AMQP/Types.h"

#include <memory>

namespace Poco {
namespace AMQP {

class MarshalledFrame {
public:
  MarshalledFrame(AMQP::Long size = 0);
  MarshalledFrame(AMQP::Octet type, AMQP::Short channel, AMQP::Long size);

  MarshalledFrame(const MarshalledFrame &other) = delete;
  MarshalledFrame &operator=(MarshalledFrame &other) = delete;

  MarshalledFrame(MarshalledFrame &&other) noexcept;
  MarshalledFrame &operator=(MarshalledFrame &&other) noexcept;

  ~MarshalledFrame() = default;

  void setChannel(const AMQP::Short channel);
  void setType(const AMQP::Octet type);
  void setSize(const AMQP::Long size);

  AMQP::Short getChannel(void) const;
  AMQP::Octet getType(void) const;
  AMQP::Long getSize(void) const;

  AMQP::Octet *getData(void) const;
  AMQP::Octet *getPayload(void) const;
  AMQP::Long getFrameSize(void) const;

protected:
private:
  std::unique_ptr<AMQP::Octet[]> _data;
  AMQP::Long _frameSize;
};

} // namespace AMQP
} // namespace Poco

#endif // AMQP_MarshalledFrame_INCLUDED
