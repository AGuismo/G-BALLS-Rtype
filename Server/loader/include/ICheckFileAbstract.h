#ifndef ACHECK_FILE_ABSTRACT
# define	ACHECK_FILE_ABSTRACT

#include	<iostream>
#include	<map>

enum UPDATE
{
	NEW = 1,
	UPDATED,
	UNCHANGED,
	DELETED
};


class								ICheckFileAbstract
{
public:
	virtual std::map<std::string, UPDATE>			*refreshFile(void) = 0;
	virtual ~ICheckFileAbstract() {}
};

#endif // !ACHECK_FILE_ABSTRACT
