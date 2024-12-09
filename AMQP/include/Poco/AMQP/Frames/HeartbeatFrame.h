#ifndef AMQP_Frames_HeartbeatFrame_INCLUDED
#define AMQP_Frames_HeartbeatFrame_INCLUDED


#include "Poco/AMQP/Frames/MarshalledFrame.h"


namespace Poco {
namespace AMQP {


class HeartbeatFrame final : public MarshalledFrame 
{
public:
	HeartbeatFrame();
	~HeartbeatFrame();

protected:
private:
};


} } // namespace Poco::AMQP


#endif // AMQP_Frames_HeartbeatFrame_INCLUDED
