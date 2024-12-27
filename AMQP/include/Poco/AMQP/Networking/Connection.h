#ifndef AMQP_Networking_Connection_INCLUDED
#define AMQP_Networking_Connection_INCLUDED


#include "Poco/AMQP/Frames/MarshalledFrame.h"
#include "Poco/Net/StreamSocket.h"


namespace Poco {
namespace AMQP {


class Connection final
{
	public:
		Connection();
		Connection(const std::string &host, const Poco::UInt16 port);

		~Connection();

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


#endif // AMQP_Networking_Connection_INCLUDED
