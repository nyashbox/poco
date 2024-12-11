#ifndef AMQP_Frames_HeartbeatFrame_INCLUDED
#define AMQP_Frames_HeartbeatFrame_INCLUDED


#include "Poco/AMQP/Frames/MarshalledFrame.h"


namespace Poco {
namespace AMQP {


constexpr AMQP::Octet HEARTBEAT_FRAME_TYPE = 0x08;


class HeartbeatFrame final : public MarshalledFrame 
{
public:
	HeartbeatFrame();
	~HeartbeatFrame();

protected:
private:
};


//
// inlines
//
inline HeartbeatFrame::HeartbeatFrame() 
	: MarshalledFrame(HEARTBEAT_FRAME_TYPE, 0, 0, nullptr)
{
}


inline HeartbeatFrame::~HeartbeatFrame()
{
}


} } // namespace Poco::AMQP


#endif // AMQP_Frames_HeartbeatFrame_INCLUDED
