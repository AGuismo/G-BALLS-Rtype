#pragma once

#include	<SFML/Window.hpp>
#include	<map>

class EventManager
{
public:
	template <typename Ev>
	class	ICallback
	{
	public:
		virtual ~ICallback() {};
		virtual void	operator()(const Ev e) = 0;
	};

	template <typename Ev, class C>
	class	Callback : public ICallback<Ev>
	{
	public:
		Callback(void(*cb)(const Ev, C), C self) : _cb(cb), _self(self)
		{

		}
		~Callback() {}
		Callback(): _cb(0), _self(0) {}

		Callback(const Callback &src) : _cb(src._cb), _self(src._self)
		{

		}

		Callback	&operator=(const Callback &src)
		{
			if (&src != this)
			{
				_cb = src._cb;
				_self = src._self;
			}
			return (*this);
		}

		void	operator()(const Ev e)
		{
			_cb(e, _self);
		}

	private:
		void	(*_cb)(const Ev, C);
		C		_self;
	};

public:
	EventManager(sf::Event &e);
	~EventManager();

public:
	void	registerKey(sf::Keyboard::Key key, ICallback<sf::Keyboard::Key> *c, const sf::Time &repeatDelay);
	void	registerKey(sf::Keyboard::Key key, ICallback<sf::Keyboard::Key> *c);
	bool	unregisterKey(sf::Keyboard::Key key);

	void	update();

private:
	template <typename Ev>
	struct State
	{
		State(): event(0), active(false), repeated(false) {};
		State(ICallback<Ev> *ev, bool repeated, const sf::Time &delay) : event(ev), active(false), repeated(repeated), delay(delay) {}

		ICallback<Ev>	*event;
		bool			active;
		bool			repeated;
		sf::Clock		lastPress;
		sf::Time		delay;
	};

	typedef std::map <sf::Keyboard::Key, State<sf::Keyboard::Key> >	keyboard_callback_map;

private:
	sf::Event				&_e;
	keyboard_callback_map	_keyCallbacks;
};