// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the MYLIBRARY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// MYLIBRARY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#if defined(WIN32)
#ifdef MYLIBRARY_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)
#else
#define MYLIBRARY_API __declspec(dllimport)
#endif
#elif defined(linux)
#define MYLIBRARY_API
#endif
// This class is exported from the myLibrary.dll
class MYLIBRARY_API CmyLibrary {
public:
	CmyLibrary(void);
	void	foo();
	// TODO: add your methods here.
};

#if defined(__cplusplus)
extern "C"
{
#endif
MYLIBRARY_API CmyLibrary	*getInstance();
#if defined(__cplusplus)
}
#endif
