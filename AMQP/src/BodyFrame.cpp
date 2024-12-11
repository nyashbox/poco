#include "Poco/AMQP/Frames/BodyFrame.h"
#include "Poco/AMQP/Frames/MarshalledFrame.h"


namespace Poco {
namespace AMQP {


constexpr AMQP::Octet BODY_FRAME = 0x03;


BodyFrame::BodyFrame(const AMQP::Octet *data, const AMQP::Long size, const AMQP::Short channel)
	: MarshalledFrame(BODY_FRAME, channel, size, nullptr)
{
	Poco::Buffer<AMQP::Octet> payloadBuf = getPayloadBuffer();
	payloadBuf.assign(data, size);
}


BodyFrame::BodyFrame(const AMQP::Octet *data, const AMQP::Long size) 
	: BodyFrame(data, size, 0)
{
}


} } // namespace Poco::AMQP
