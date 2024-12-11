#ifndef AMQP_Frames_BodyFrame_INCLUDED
#define AMQP_Frames_BodyFrame_INCLUDED


#include "Poco/AMQP/Frames/MarshalledFrame.h"


namespace Poco {
namespace AMQP {


constexpr AMQP::Octet BODY_FRAME_TYPE = 0x03;


class BodyFrame final : public MarshalledFrame 
{
public:
	BodyFrame(const AMQP::Octet *data, const AMQP::Long size);
	BodyFrame(const AMQP::Octet *data, const AMQP::Long size, const AMQP::Short channel);
protected:
private:
};


//
// inlines
//
inline BodyFrame::BodyFrame(const AMQP::Octet *data, const AMQP::Long size, const AMQP::Short channel)
	: MarshalledFrame(BODY_FRAME_TYPE, channel, size, nullptr)
{
	Poco::Buffer<AMQP::Octet> payloadBuf = getPayloadBuffer();
	payloadBuf.assign(data, size);
}


inline BodyFrame::BodyFrame(const AMQP::Octet *data, const AMQP::Long size) 
	: BodyFrame(data, size, 0)
{
}


} } // namespace Poco::AMQP


#endif // AMQP_Frames_BodyFrame_INCLUDED
