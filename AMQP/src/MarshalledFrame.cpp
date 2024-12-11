#include "Poco/AMQP/Frames/MarshalledFrame.h"
#include "Poco/AMQP/Types/Integers.h"
#include <cstring>


namespace Poco {
namespace AMQP {


constexpr AMQP::Octet TYPE_OFFSET    = 0x00;
constexpr AMQP::Octet CHANNEL_OFFSET = 0x01;
constexpr AMQP::Octet SIZE_OFFSET    = 0x03;


constexpr AMQP::Octet HEADER_SIZE    = 0x07;
constexpr AMQP::Octet FRAME_END      = 0xCE;


MarshalledFrame::MarshalledFrame(AMQP::Long size)
    : MarshalledFrame(0x00, 0, size, nullptr) 
{
}


MarshalledFrame::MarshalledFrame(AMQP::Octet type, AMQP::Short channel,
                                 AMQP::Long size, const AMQP::Octet *payload) 
{
	_data.resize(size + HEADER_SIZE + sizeof(FRAME_END));

	// Set frame data
	setType(type);
	setChannel(channel);
	setSize(size);

	// Frame end
	_data[size + HEADER_SIZE] = FRAME_END;

	if (payload)
	{
		Poco::Buffer<AMQP::Octet> payloadBuffer = getPayloadBuffer();
		payloadBuffer.assign(payload, size);
	}
}


MarshalledFrame::~MarshalledFrame() 
{
}


void MarshalledFrame::setChannel(const AMQP::Short channel) 
{
	AMQP::Octet *channelPtr = &_data[CHANNEL_OFFSET];
	AMQP::AMQPTypeTraits<AMQP::Short>::write(channel, channelPtr);
}


void MarshalledFrame::setType(const AMQP::Octet type) 
{
	AMQP::Octet *typePtr = &_data[TYPE_OFFSET];
	AMQP::AMQPTypeTraits<AMQP::Octet>::write(type, typePtr);
}


void MarshalledFrame::setSize(const AMQP::Long size) 
{
	AMQP::Octet *sizePtr = &_data[SIZE_OFFSET];
	AMQP::AMQPTypeTraits<AMQP::Long>::write(size, sizePtr);
}


AMQP::Short MarshalledFrame::getChannel(void) const 
{
	const AMQP::Octet *channel = &_data[CHANNEL_OFFSET];

#if POCO_ARCH_LITTLE_ENDIAN
	AMQP::Short ret = channel[1] << 0 | channel[0] << 8;
#else
	AMQP::Short ret = channel[0] << 0 | channel[1] << 8;
#endif

	return ret;
}


AMQP::Octet MarshalledFrame::getType(void) const 
{ 
	return _data[0]; 
}


AMQP::Long MarshalledFrame::getSize(void) const 
{
	const AMQP::Octet *size = &_data[SIZE_OFFSET];

#if POCO_ARCH_LITTLE_ENDIAN
	AMQP::Long ret = size[3] << 0 | size[2] << 8 | size[1] << 16 | size[0] << 24;
#else
	AMQP::Long ret = size[0] << 0 | size[1] << 8 | size[2] << 16 | size[3] << 24;
#endif

	return ret;
}


AMQP::Long MarshalledFrame::getFrameSize(void) const 
{
	return _data.sizeBytes();
}


const Poco::Buffer<AMQP::Octet> &MarshalledFrame::getBuffer(void) const 
{
	return _data;
}


Poco::Buffer<AMQP::Octet> MarshalledFrame::getPayloadBuffer(void) const 
{
	AMQP::Octet *payloadPtr = const_cast<AMQP::Octet *>(_data.begin() + HEADER_SIZE);
	const AMQP::Long payloadSize = _data.sizeBytes() - HEADER_SIZE - 1;

	return Poco::Buffer<AMQP::Octet>(payloadPtr, payloadSize);
}


} } // namespace Poco::AMQP
