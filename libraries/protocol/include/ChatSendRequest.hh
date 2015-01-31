#pragma once

# include	<string>
# include	"RequestCode.hh"
# include	"ARequest.hh"

class ChatSendRequest : public ARequest
{
public:
	ChatSendRequest(const std::string &msg);
	ChatSendRequest();
	~ChatSendRequest();

public:
	ChatSendRequest(ChatSendRequest const&);
	ChatSendRequest& operator=(ChatSendRequest const&);

public:
	Protocol	&serialize(Protocol &) const;
	Protocol	&unserialize(Protocol &);
	ARequest	*clone() const;

	std::string msg() const;

private:
	std::string	_msg;
};