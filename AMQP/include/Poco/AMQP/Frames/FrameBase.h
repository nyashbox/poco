#ifndef AMQP_Frames_FrameBase_INCLUDED
#define AMQP_Frames_FrameBase_INCLUDED


#include "Poco/AMQP/Frames/MarshalledFrame.h"
#include "Poco/AMQP/Types/Integers.h"


namespace Poco {
namespace AMQP {


class FrameBase 
{
public:
	virtual MarshalledFrame marshall(void) = 0;

	void setChannel(const AMQP::Short channel);
	AMQP::Short getChannel(void) const;

protected:
private:
	AMQP::Short _channel = 0x00;
};


// 
// inlines
//


inline void FrameBase::setChannel(const AMQP::Short channel) 
{
	_channel = channel;
}


inline AMQP::Short FrameBase::getChannel(void) const 
{ 
	return _channel; 
}


} } // namespace Poco::AMQP 


#endif // AMQP_Frames_FrameBase_INCLUDED
