// ----------------------------------------------------------------------------
//  MD5
// ----------------------------------------------------------------------------
//
// usage:
//	- MD5 md5;
//	- md5.update(...)
//      - md5.final()
//      - md5.digest() → string
// or
//      - MD5(std::string).digest()
// or
//      - md5(string) → string

#pragma once
#include <string>
#include <iostream>

class MD5
{
    public:
    typedef unsigned int size_type;

    MD5();
    MD5(const std::string & text);

    void			update(const void * buf, size_type length);
    void			update(const unsigned char * buf, size_type length);
    MD5 &			final();
    std::string			digest() const;

    friend std::ostream &	operator<<(std::ostream&, MD5 md5);

    enum {length = 32};

    private:
    typedef unsigned char uint1;
    typedef unsigned int uint4;

    enum
    {
	blocksize = 64,
	S11 = 7, S12 = 12, S13 = 17, S14 = 22,
	S21 = 5, S22 =  9, S23 = 14, S24 = 20,
	S31 = 4, S32 = 11, S33 = 16, S34 = 23,
	S41 = 6, S42 = 10, S43 = 15, S44 = 21,
    };

    void	init();
    void	transform(const uint1 block[blocksize]);
    static void	decode(uint4 output[], const uint1 input[], size_type len);
    static void	encode(uint1 output[], const uint4 input[], size_type len);

    bool	_finalized;
    uint1	_buffer[blocksize];
    uint4	_count[2];
    uint4	_state[4];
    uint1	_digest[16];

    static inline uint4 F(uint4 x, uint4 y, uint4 z);
    static inline uint4 G(uint4 x, uint4 y, uint4 z);
    static inline uint4 H(uint4 x, uint4 y, uint4 z);
    static inline uint4 I(uint4 x, uint4 y, uint4 z);
    static inline uint4	rotate_left(uint4 x, int n);
    static inline void	FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    static inline void	GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    static inline void	HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    static inline void	II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
};

std::string md5(const std::string str);
