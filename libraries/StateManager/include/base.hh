// -----------------------------------------------------------------------------
// BASE
// -----------------------------------------------------------------------------
// Last update Thu Jun  6 00:22:31 2013 jules baratoux

#pragma once

#define pragma(x) _Pragma (#x)

#define pragma_ignore(DIAGNOSTIC)               \
    pragma(GCC diagnostic push);                \
    pragma(GCC diagnostic ignored DIAGNOSTIC)

#define message(MSG)    pragma(message("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b" MSG))

#define IT(ctainer)   typeof((ctainer.end()))
// #define P(cond) P_( (cond), #cond)
// static inline bool P_(bool r, char * cond)
// {
//     std::cout << cond << ":" << (r ? "true" : "false") << std::endl;
//     return r;
// }

