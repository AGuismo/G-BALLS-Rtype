// -*- mode: c++ -*-
// -----------------------------------------------------------------------------
// CBUFFER
// -----------------------------------------------------------------------------
// Last update Tue Jun 11 22:05:14 2013 jules baratoux

#include "cBuffer.h"

namespace net
{
    template <typename T>
    T			cBuffer::push(const T val, size_type count)
    {
	const Byte*		buffer = reinterpret_cast<const Byte*>(&val);

	for (size_t size = 0; size < sizeof(val) * count; size += sizeof(Byte))
	{
	    _buf.push_back(buffer[size]);
	}
	return val;
    }

    template <typename T>
    T&			cBuffer::pop(T& val)
    {
	Byte*		buffer = reinterpret_cast<Byte*>(&val);


	for (size_t size = 0; size < sizeof(val); size += sizeof(Byte) )
	{
	    buffer[size] = _buf.front();
	    _buf.erase(_buf.begin());
	}
	return val;
    }
}
