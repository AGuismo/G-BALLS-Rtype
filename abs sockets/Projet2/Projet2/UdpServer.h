#pragma once

#if defined(WIN32)
#include <Winsock2.h>
#include "WinInit.h"
#elif defined(linux)
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include "ClientAccepted.h"
#include "AMonitorable.h"
#include "abs_sockets.h"
#include "cBuffer.h"

namespace net
{
	class ABS_SOCKET_API UdpServer : public AMonitorable
	{
	public:
		UdpServer(void);
		~UdpServer(void);
		void initialize(int port, int nbClients = 10);
		ClientAccepted *recv();
		void send();
		void close();
		void readFromBuffer(std::string &);
		void writeIntoBuffer(const std::string &str);
		cBuffer::size_type lookRead(std::vector<cBuffer::Byte> &buf, cBuffer::size_type count);
		cBuffer::size_type lookWrite(std::vector<cBuffer::Byte> &buf, cBuffer::size_type count);

	private:
		SOCKET	getSocket() const;
		SOCKET	_sock;
		State	_state;
		cBuffer	_read;
		cBuffer	_write;
		struct sockaddr_in _addr;
	};
}