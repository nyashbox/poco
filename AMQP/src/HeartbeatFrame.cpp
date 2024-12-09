#include "Poco/AMQP/Frames/HeartbeatFrame.h"


namespace Poco {
namespace AMQP {


constexpr AMQP::Octet HEARTBEAT_FRAME = 0x08;


MarshalledFrame HeartbeatFrame::marshall(void) 
{
	MarshalledFrame frame{HEARTBEAT_FRAME, 0, 0};

	return frame;
};


} } // namespace Poco::AMQP
