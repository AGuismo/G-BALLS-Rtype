#include "MD5.hh"
#include "Salt.hpp"

void			Salt::update(const void * buf, size_type length)
{
    md5.update(buf, length);
}

Salt&			Salt::final(void)
{
    const unsigned char		salt = static_cast<unsigned char>(SALT);

    md5.update(&salt, sizeof(salt));
    md5.final();
    return *this;
}

std::string		Salt::digest(void) const
{
    return md5.digest();
}

bool			Salt::operator==(const std::string& rhs) const
{
    return (digest() == rhs);
}

bool			Salt::operator!=(const std::string& rhs) const
{
    return !(*this == rhs);
}
