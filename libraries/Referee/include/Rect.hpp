#pragma once

template <typename T = unsigned short>
class Rect
{
public:
	Rect(T x, T y, T width, T height):
		m_x(x), m_y(y), m_height(height), m_width(width)
	{

	}

	~Rect() {};

	void	topLeft(T &x, T &y) const
	{
		x = m_x;
		y = m_y;
	}

	void	topRight(T &x, T &y) const
	{
		x = m_x + m_width;
		y = m_y;
	}

	void	bottomRight(T &x, T &y) const
	{
		x = m_x + m_width;
		y = m_y + m_height;
	}

	void	bottomLeft(T &x, T &y) const
	{
		x = m_x;
		y = m_y + m_height;
	}

public:
	T	m_x;
	T	m_y;
	T	m_height;
	T	m_width;
};
