#ifndef AMQP_Frames_MethodFrame_INCLUDED
#define AMQP_Frames_MethodFrame_INCLUDED


#include "Poco/AMQP/Frames/MarshalledFrame.h"


namespace Poco {
namespace AMQP {


constexpr AMQP::Octet METHOD_FRAME_TYPE = 0x01;


class MethodFrame final : public MarshalledFrame 
{
public:
	template<typename... Args, typename=std::enable_if_t<(isAMQPType<Args>::value && ...)>>
	MethodFrame(const AMQP::Short classId, const AMQP::Short methodId, Args... arguments);

	~MethodFrame();
protected:
private:
};


//
// inlines
//


template<typename... Args, typename>
inline MethodFrame::MethodFrame(const AMQP::Short classId, const AMQP::Short methodId, Args... arguments)
	: MarshalledFrame(METHOD_FRAME_TYPE, 0x00, classId, methodId, arguments...)
{
}


inline MethodFrame::~MethodFrame()
{
}


} } // namespace Poco::AMQP


#endif // AMQP_Frames_MethodFrame_INCLUDED
