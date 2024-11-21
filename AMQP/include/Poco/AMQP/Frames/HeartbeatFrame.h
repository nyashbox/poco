#ifndef AMQP_HeartbeatFrame_INCLUDED
#define AMQP_HeartbeatFrame_INCLUDED

#include "Poco/AMQP/Frames/FrameBase.h"

namespace Poco {
namespace AMQP {

class HeartbeatFrame final : public FrameBase {
public:
  HeartbeatFrame() = default;
  ~HeartbeatFrame() = default;

  virtual MarshalledFrame marshall(void) override;

protected:
private:
};

} // namespace AMQP
} // namespace Poco

#endif // AMQP_HeartbeatFrame_INCLUDED
