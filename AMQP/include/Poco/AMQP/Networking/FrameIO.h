#ifndef AMQP_Networking_FrameIO_INCLUDED
#define AMQP_Networking_FrameIO_INCLUDED


#include "Poco/AMQP/Frames/MarshalledFrame.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Net/SocketStream.h"


namespace Poco {
namespace AMQP {


class FrameIO final
{
	public:
		FrameIO();
		FrameIO(const std::string &host, const Poco::UInt16 port);

		~FrameIO();

		void connect(const std::string &host, const Poco::UInt16 port);
		void connect(const Net::SocketAddress &addr);

		void negotiate(void);

		void disconnect(void);

		void write(const MarshalledFrame &frame);
		Poco::Buffer<AMQP::Octet> read(void);

		const Net::SocketAddress address(void) const;
		const Net::StreamSocket &socket(void) const;

	protected:
	private:

		Net::StreamSocket _socket;
};


} } // namespace Poco::AMQP 


#endif // AMQP_Networking_FrameIO_INCLUDED
