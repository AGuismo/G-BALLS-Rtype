#ifndef NETWORK_
# define	NETWORK_

# include <SFML/System.hpp>
# include <deque>
# include <iostream>

class Network
{
private:
	sf::Mutex				 mutex;

private:
	void					Roar(void)
	{
		std::cout << "GROARRRRRRR" << std::endl;
	}

private:
	std::deque<std::string>			outRequest;
	std::deque<std::string>			inRequest;

public:
	void									pushOutRequest(std::string &request)
	{
		mutex.lock();
		outRequest.push_back(request);
		mutex.unlock();
	}

	std::string								*popOutRequest(void)
	{
		mutex.lock();
		while (outRequest.size() != 0)
		{
			std::cout << "[" << outRequest.front().c_str() << "]" << std::endl;
			std::string *reqTmp = new std::string(outRequest.front());
			outRequest.pop_front();
			mutex.unlock();
			return (reqTmp);
		}
		mutex.unlock();
		return (NULL);
	}

	void									pushInRequest(std::string &request)
	{
		mutex.lock();
		outRequest.push_back(request);
		mutex.unlock();
	}

	std::string								*popInRequest(void)
	{
		mutex.lock();
		while (inRequest.size() != 0)
		{
			std::cout << "[" << inRequest.front().c_str() << "]" << std::endl;
			std::string *reqTmp = new std::string(inRequest.front());
			inRequest.pop_front();
			mutex.unlock();
			return (reqTmp);
		}
		mutex.unlock();
		return (NULL);
	}

public:
	void Run()
	{
		while (42)
		{
			//reseau
			sf::sleep(sf::seconds(2));
			popOutRequest();
		}
	}
};

#endif // !NETWORK_