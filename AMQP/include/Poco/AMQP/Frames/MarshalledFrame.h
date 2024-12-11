#ifndef AMQP_Frames_MarshalledFrame_INCLUDED
#define AMQP_Frames_MarshalledFrame_INCLUDED


#include "Poco/AMQP/Types/Integers.h"
#include "Poco/Buffer.h"


namespace Poco {
namespace AMQP {


class MarshalledFrame 
{
public:
	MarshalledFrame(AMQP::Long size = 0);
	MarshalledFrame(AMQP::Octet type, AMQP::Short channel, AMQP::Long size, const AMQP::Octet *payload);

	~MarshalledFrame();

	void setChannel(const AMQP::Short channel);
	void setType(const AMQP::Octet type);
	void setSize(const AMQP::Long size);

	AMQP::Short getChannel(void) const;
	AMQP::Octet getType(void) const;
	AMQP::Long getSize(void) const;

	AMQP::Long getFrameSize(void) const;

	const Poco::Buffer<AMQP::Octet> &getBuffer(void) const;
	Poco::Buffer<AMQP::Octet> getPayloadBuffer(void) const;

protected:
private:
	Poco::Buffer<AMQP::Octet> _data{0};
};


} } // namespace Poco::AMQP


#endif // AMQP_Frames_MarshalledFrame_INCLUDED
