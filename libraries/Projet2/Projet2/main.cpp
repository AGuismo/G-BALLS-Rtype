#include	"UselessDLL.h"
#include	"DynamicAbstract.h"


int				main()
{
	Fptr		dll;
	UselessDll	*bot;
	MDynamicAbstract *loader;

	loader = new DynamicAbstract();

	if (loader->DynamicOpen("TestDll.dll") == false)
		std::cerr << "FUCK  open" << std::endl;

	if ((dll = (Fptr)loader->DynamicLoadSym("getInstance")) == NULL)
		std::cerr << "FUCK  load" << std::endl;

	bot = static_cast<UselessDll *>(dll());

	bot->Roar();
	loader->DynamicClose();
	
	system("pause");
	return 0;
}