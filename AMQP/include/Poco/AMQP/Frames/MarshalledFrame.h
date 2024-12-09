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
	MarshalledFrame(AMQP::Octet type, AMQP::Short channel, AMQP::Long size);

	MarshalledFrame(const MarshalledFrame &other) = delete;
	MarshalledFrame &operator=(MarshalledFrame &other) = delete;

	MarshalledFrame(MarshalledFrame &&other) noexcept;
	MarshalledFrame &operator=(MarshalledFrame &&other) noexcept;

	~MarshalledFrame() = default;

	void setChannel(const AMQP::Short channel);
	void setType(const AMQP::Octet type);
	void setSize(const AMQP::Long size);

	AMQP::Short getChannel(void) const;
	AMQP::Octet getType(void) const;
	AMQP::Long getSize(void) const;

	AMQP::Long getFrameSize(void) const;

	AMQP::Octet *begin();
	AMQP::Octet *end();

	const AMQP::Octet *cbegin() const;
	const AMQP::Octet *cend() const;

	AMQP::Octet *pbegin();
	AMQP::Octet *pend();

	const AMQP::Octet *cpbegin() const;
	const AMQP::Octet *cpend() const;

protected:
private:
	Poco::Buffer<AMQP::Octet> _data{0};
};


} } // namespace Poco::AMQP


#endif // AMQP_Frames_MarshalledFrame_INCLUDED
