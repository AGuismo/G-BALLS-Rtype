#pragma once

# include	<string>
# include	"RequestCode.hh"
# include	"ARequest.hh"

class ChatRecvRequest : public ARequest
{
public:
	ChatRecvRequest(const std::string &msg);
	~ChatRecvRequest();

public:
	ChatRecvRequest(ChatRecvRequest const&);
	ChatRecvRequest& operator=(ChatRecvRequest const&);

public:
	Protocol	&serialize(Protocol &) const;
	Protocol	&unserialize(Protocol &);
	ARequest	*clone();

	std::string msg() const;

private:
	std::string	_msg;
};