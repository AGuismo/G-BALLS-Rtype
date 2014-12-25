// myLibrary.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "myLibrary.h"
#include <iostream>

CmyLibrary::CmyLibrary()
{

}

void	CmyLibrary::foo()
{
	std::cout << "I'm in CmyLibrary::foo() function!" << std::endl;
}

CmyLibrary	*getInstance()
{
	return (new CmyLibrary);
}