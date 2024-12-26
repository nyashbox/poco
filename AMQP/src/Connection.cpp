#include "Poco/AMQP/Networking/Connection.h"


namespace Poco {
namespace AMQP {


Connection::Connection() 
	: _socket()
{
}


Connection::Connection(const std::string &host, const Poco::UInt16 port)
{
	connect(host, port);
}


Connection::~Connection() 
{
}


void Connection::connect(const std::string &host, const Poco::UInt16 port) 
{
	_socket.connect({host, port});
}


void Connection::connect(const Net::SocketAddress &addr)
{
	_socket.connect(addr);
}


void Connection::disconnect() 
{
	_socket.close();
}


void Connection::write(const MarshalledFrame &frame) 
{
	Poco::Buffer<AMQP::Octet> frameBuffer = frame.getBuffer();

	_socket.sendBytes(frameBuffer.begin(), frameBuffer.sizeBytes());
}


void Connection::negotiate(void)
{
	const char protocolHeader[] = 
	{
		'A', 'M', 'Q', 'P', 0, 0, 9, 1
	};

	_socket.sendBytes(protocolHeader, sizeof(protocolHeader));
}


Poco::Buffer<AMQP::Octet> Connection::read(void) 
{
	size_t bytes = _socket.available();
	Poco::Buffer<AMQP::Octet> buf{bytes};

	// read data from the socket
	_socket.receiveBytes(buf.begin(), bytes);

	return buf;
}


const Net::SocketAddress Connection::address(void) const 
{
	return _socket.address();
}


const Net::StreamSocket &Connection::socket(void) const
{
	return _socket;
}


} } // namespace Poco::AMQP
