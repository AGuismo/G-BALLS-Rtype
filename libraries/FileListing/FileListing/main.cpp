#include	"checkFileAbstract.h"

int												main(void)
{
	int i = 0;
	ACheckFileAbstract							*listing;
	std::string									dName("AU BON C");
	std::map<std::string, UPDATE>				*list;

	listing = new checkFileAbstract(dName);

	while (i < 10)
	{
		list = listing->refreshFile();
		for (std::map<std::string, UPDATE>::iterator it = list->begin(); it != list->end(); ++it)
			std::cout << "[" << it->first.c_str() << "] [" << it->second << "]" << std::endl;
		system("pause");
		++i;
	}
	return 1;
}