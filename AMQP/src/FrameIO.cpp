#include "Poco/AMQP/Networking/FrameIO.h"


namespace Poco {
namespace AMQP {


FrameIO::FrameIO() : _socket()
{
}


FrameIO::FrameIO(const std::string &host, const Poco::UInt16 port)
{
	connect(host, port);
}


FrameIO::~FrameIO() 
{
}


void FrameIO::connect(const std::string &host, const Poco::UInt16 port) 
{
	_socket.connect({host, port});
}


void FrameIO::connect(const Net::SocketAddress &addr)
{
	_socket.connect(addr);
}


void FrameIO::disconnect() 
{
	_socket.close();
}


void FrameIO::write(const MarshalledFrame &frame) 
{
	Poco::Buffer<AMQP::Octet> frameBuffer = frame.getBuffer();

	_socket.sendBytes(frameBuffer.begin(), frameBuffer.sizeBytes());
}


void FrameIO::negotiate(void)
{
	const char protocolHeader[] = 
	{
		'A', 'M', 'Q', 'P', 0, 0, 9, 1
	};

	_socket.sendBytes(protocolHeader, sizeof(protocolHeader));
}


Poco::Buffer<AMQP::Octet> FrameIO::read(void) 
{
	size_t bytes = _socket.available();
	Poco::Buffer<AMQP::Octet> buf{bytes};

	// read data from the socket
	_socket.receiveBytes(buf.begin(), bytes);

	return buf;
}


const Net::SocketAddress FrameIO::address(void) const 
{
	return _socket.address();
}


const Net::StreamSocket &FrameIO::socket(void) const
{
	return _socket;
}


} } // namespace Poco::AMQP
