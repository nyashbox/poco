#ifndef AMQP_Frames_BodyFrame_INCLUDED
#define AMQP_Frames_BodyFrame_INCLUDED


#include "Poco/AMQP/Frames/MarshalledFrame.h"


namespace Poco {
namespace AMQP {


class BodyFrame final : public MarshalledFrame 
{
public:
	BodyFrame(const AMQP::Octet *data, const AMQP::Long size);
	BodyFrame(const AMQP::Octet *data, const AMQP::Long size, const AMQP::Short channel);
protected:
private:
};


} } // namespace Poco::AMQP


#endif // AMQP_Frames_BodyFrame_INCLUDED
