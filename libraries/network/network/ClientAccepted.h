#pragma once

#include <exception>
#include "AMonitorable.h"
#include "cBuffer.h"
#include "abs_sockets.h"
#include "state.h"
#if defined(WIN32)
#include <WinSock2.h>
#include "WinInit.h"
#pragma comment(lib, "WS2_32.lib")
#elif defined(linux)
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

namespace net
{
	class ABS_SOCKET_API ClientAccepted: public AMonitorable
	{
	public:
		ClientAccepted();
		ClientAccepted(SOCKET sock, struct sockaddr_in addr);
		~ClientAccepted();

		void recv();
		void send();
		void close();
		void readFromBuffer(std::string &);
		void writeIntoBuffer(const std::string &str);
		cBuffer::size_type lookRead(std::vector<cBuffer::Byte> &buf, cBuffer::size_type count);
		cBuffer::size_type lookWrite(std::vector<cBuffer::Byte> &buf, cBuffer::size_type count);
		struct sockaddr_in _addr;
		
	protected:
		SOCKET		getSocket()const;
		SOCKET		_sock;
		State		_state;
		cBuffer		_read;
		cBuffer		_write;
		//struct sockaddr_in _addr;
	};
}