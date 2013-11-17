#define _CRT_SECURE_NO_WARNINGS
#include "MD5.hh"
#include <cstdio>
#include <cstring>
#include <stdexcept>

inline MD5::uint4	MD5::F(uint4 x, uint4 y, uint4 z)
{
    return (x & y) | (~x & z);
}

inline MD5::uint4	MD5::G(uint4 x, uint4 y, uint4 z)
{
    return (x & z) | (y & ~z);
}

inline MD5::uint4	MD5::H(uint4 x, uint4 y, uint4 z)
{
    return x ^ y ^ z;
}

inline MD5::uint4	MD5::I(uint4 x, uint4 y, uint4 z)
{
    return y ^ (x | ~z);
}

inline MD5::uint4	MD5::rotate_left(uint4 x, int n)
{
    return (x << n) | (x >> (32 - n));
}

inline void		MD5::FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
{
    a = rotate_left(a+ F(b, c, d) + x + ac, s) + b;
}

inline void		MD5::GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
{
    a = rotate_left(a + G(b, c, d) + x + ac, s) + b;
}

inline void		MD5::HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
{
    a = rotate_left(a + H(b, c, d) + x + ac, s) + b;
}

inline void		MD5::II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
{
    a = rotate_left(a + I(b, c, d) + x + ac, s) + b;
}

MD5::MD5()
{
    init();
}

MD5::MD5(const std::string &text)
{
    init();
    update(text.c_str(), text.length());
    final();
}

void			MD5::init()
{
    _finalized = false;

    _count[0] = 0;
    _count[1] = 0;

    _state[0] = 0x67452301;
    _state[1] = 0xefcdab89;
    _state[2] = 0x98badcfe;
    _state[3] = 0x10325476;
}

void			MD5::decode(uint4 output[], const uint1 input[], size_type len)
{
    for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
    {
	output[i] =  ((uint4)input[j])  | (((uint4)input[j+1]) << 8)  |
	    (((uint4)input[j+2]) << 16) | (((uint4)input[j+3]) << 24);
    }
}

void			MD5::encode(uint1 output[], const uint4 input[], size_type len)
{
    for (size_type i = 0, j = 0; j < len; i++, j += 4)
    {
	output[j] = input[i] & 0xff;
	output[j+1] = (input[i] >> 8) & 0xff;
	output[j+2] = (input[i] >> 16) & 0xff;
	output[j+3] = (input[i] >> 24) & 0xff;
    }
}

void			MD5::transform(const uint1 block[blocksize])
{
    uint4		a = _state[0];
    uint4		b = _state[1];
    uint4		c = _state[2];
    uint4		d = _state[3];
    uint4		x[16];

    decode(x, block, blocksize);

//  ROUND 1
    FF (a, b, c, d, x[ 0], S11, 0xd76aa478); // 01
    FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); // 02
    FF (c, d, a, b, x[ 2], S13, 0x242070db); // 03
    FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); // 04
    FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); // 05
    FF (d, a, b, c, x[ 5], S12, 0x4787c62a); // 06
    FF (c, d, a, b, x[ 6], S13, 0xa8304613); // 07
    FF (b, c, d, a, x[ 7], S14, 0xfd469501); // 08
    FF (a, b, c, d, x[ 8], S11, 0x698098d8); // 09
    FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); // 10
    FF (c, d, a, b, x[10], S13, 0xffff5bb1); // 11
    FF (b, c, d, a, x[11], S14, 0x895cd7be); // 12
    FF (a, b, c, d, x[12], S11, 0x6b901122); // 13
    FF (d, a, b, c, x[13], S12, 0xfd987193); // 14
    FF (c, d, a, b, x[14], S13, 0xa679438e); // 15
    FF (b, c, d, a, x[15], S14, 0x49b40821); // 16

//  ROUND 2
    GG (a, b, c, d, x[ 1], S21, 0xf61e2562); // 17
    GG (d, a, b, c, x[ 6], S22, 0xc040b340); // 18
    GG (c, d, a, b, x[11], S23, 0x265e5a51); // 19
    GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); // 20
    GG (a, b, c, d, x[ 5], S21, 0xd62f105d); // 21
    GG (d, a, b, c, x[10], S22,  0x2441453); // 22
    GG (c, d, a, b, x[15], S23, 0xd8a1e681); // 23
    GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); // 24
    GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); // 25
    GG (d, a, b, c, x[14], S22, 0xc33707d6); // 26
    GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); // 27
    GG (b, c, d, a, x[ 8], S24, 0x455a14ed); // 28
    GG (a, b, c, d, x[13], S21, 0xa9e3e905); // 29
    GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); // 30
    GG (c, d, a, b, x[ 7], S23, 0x676f02d9); // 31
    GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); // 32

//  ROUND 3
    HH (a, b, c, d, x[ 5], S31, 0xfffa3942); // 33
    HH (d, a, b, c, x[ 8], S32, 0x8771f681); // 34
    HH (c, d, a, b, x[11], S33, 0x6d9d6122); // 35
    HH (b, c, d, a, x[14], S34, 0xfde5380c); // 36
    HH (a, b, c, d, x[ 1], S31, 0xa4beea44); // 37
    HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); // 38
    HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); // 39
    HH (b, c, d, a, x[10], S34, 0xbebfbc70); // 40
    HH (a, b, c, d, x[13], S31, 0x289b7ec6); // 41
    HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); // 42
    HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); // 43
    HH (b, c, d, a, x[ 6], S34,  0x4881d05); // 44
    HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); // 45
    HH (d, a, b, c, x[12], S32, 0xe6db99e5); // 46
    HH (c, d, a, b, x[15], S33, 0x1fa27cf8); // 47
    HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); // 48

//  ROUND 4
    II (a, b, c, d, x[ 0], S41, 0xf4292244); // 49
    II (d, a, b, c, x[ 7], S42, 0x432aff97); // 50
    II (c, d, a, b, x[14], S43, 0xab9423a7); // 51
    II (b, c, d, a, x[ 5], S44, 0xfc93a039); // 52
    II (a, b, c, d, x[12], S41, 0x655b59c3); // 53
    II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); // 54
    II (c, d, a, b, x[10], S43, 0xffeff47d); // 55
    II (b, c, d, a, x[ 1], S44, 0x85845dd1); // 56
    II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); // 57
    II (d, a, b, c, x[15], S42, 0xfe2ce6e0); // 58
    II (c, d, a, b, x[ 6], S43, 0xa3014314); // 59
    II (b, c, d, a, x[13], S44, 0x4e0811a1); // 60
    II (a, b, c, d, x[ 4], S41, 0xf7537e82); // 61
    II (d, a, b, c, x[11], S42, 0xbd3af235); // 62
    II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); // 63
    II (b, c, d, a, x[ 9], S44, 0xeb86d391); // 64

    _state[0] += a;
    _state[1] += b;
    _state[2] += c;
    _state[3] += d;

    memset(x, 0, sizeof x);
}

void			MD5::update(const unsigned char input[], size_type length)
{
    size_type index = _count[0] / 8 % blocksize;

    if ((_count[0] += (length << 3)) < (length << 3))
	_count[1]++;
    _count[1] += (length >> 29);

    size_type firstpart = 64 - index;
    size_type i;

    if (length >= firstpart)
    {
	memcpy(&_buffer[index], input, firstpart);
	transform(_buffer);
	for (i = firstpart; i + blocksize <= length; i += blocksize)
	    transform(&input[i]);
	index = 0;
    }
    else
    {
	i = 0;
    }
    memcpy(&_buffer[index], &input[i], length-i);
}

void			MD5::update(const void *input, size_type length)
{
    update( (const unsigned char*) input, length);
}

MD5&			MD5::final()
{
    static unsigned char padding[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    if (!_finalized)
    {
	unsigned char bits[8];
	encode(bits, _count, 8);

	size_type index = _count[0] / 8 % 64;
	size_type padLen = (index < 56) ? (56 - index) : (120 - index);
	update(padding, padLen);
	update(bits, 8);
	encode(_digest, _state, 16);
	memset(_buffer, 0, sizeof _buffer);
	memset(_count, 0, sizeof _count);
	_finalized = true;
    }

    return *this;
}

std::string		MD5::digest() const
{
    if (!_finalized)
	throw std::logic_error("Please call MD5::final before MD5::hash");

    char buf[MD5::length + 1];
    for (int i = 0; i < 16; ++i)
		sprintf(buf + i * 2, "%02x", _digest[i]);
    buf[MD5::length] = 0;

    return std::string(buf);
}

std::ostream& operator<<(std::ostream& out, MD5 md5)
{
    return out << md5.digest();
}

std::string		md5(const std::string str)
{
    MD5 md5 = MD5(str);

    return md5.digest();
}
