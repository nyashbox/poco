#ifndef AMQP_FrameBase_INCLUDED
#define AMQP_FrameBase_INCLUDED

#include "Poco/AMQP/Frames/MarshalledFrame.h"
#include "Poco/AMQP/Types.h"

namespace Poco {
namespace AMQP {

class FrameBase {
public:
  virtual MarshalledFrame marshall(void) = 0;

  void setChannel(const AMQP::Short channel) { _channel = channel; };
  AMQP::Short getChannel(void) const { return _channel; };

protected:
private:
  AMQP::Short _channel = 0x00;
};

} // namespace AMQP
} // namespace Poco

#endif // AMQP_Frame_INCLUDED
