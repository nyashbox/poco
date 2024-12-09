#include "Poco/AMQP/Frames/HeartbeatFrame.h"


namespace Poco {
namespace AMQP {


constexpr AMQP::Octet HEARTBEAT_FRAME = 0x08;


HeartbeatFrame::HeartbeatFrame() 
	: MarshalledFrame(HEARTBEAT_FRAME, 0, 0)
{
}


HeartbeatFrame::~HeartbeatFrame()
{
}


} } // namespace Poco::AMQP
