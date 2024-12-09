#ifndef AMQP_Frames_HeartbeatFrame_INCLUDED
#define AMQP_Frames_HeartbeatFrame_INCLUDED


#include "Poco/AMQP/Frames/FrameBase.h"


namespace Poco {
namespace AMQP {


class HeartbeatFrame final : public FrameBase 
{
public:
	HeartbeatFrame();
	~HeartbeatFrame();

	virtual MarshalledFrame marshall(void) override;

protected:
private:
};


//
// inlines
//


inline HeartbeatFrame::HeartbeatFrame() 
{
}


inline HeartbeatFrame::~HeartbeatFrame()
{
}


} } // namespace Poco::AMQP


#endif // AMQP_Frames_HeartbeatFrame_INCLUDED
