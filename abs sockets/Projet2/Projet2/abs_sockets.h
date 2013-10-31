// Le bloc ifdef suivant est la façon standard de créer des macros qui facilitent l'exportation 
// à partir d'une DLL. Tous les fichiers contenus dans cette DLL sont compilés avec le symbole ABS_SOCKET_EXPORTS
// défini sur la ligne de commande. Ce symbole ne doit pas être défini pour un projet
// qui utilisent cette DLL. De cette manière, les autres projets dont les fichiers sources comprennent ce fichier considèrent les fonctions 
// ABS_SOCKET_API comme étant importées à partir d'une DLL, tandis que cette DLL considère les symboles
// définis avec cette macro comme étant exportés.
#if defined(WIN32)
# if defined(ABS_SOCKET_EXPORTS)
#  define ABS_SOCKET_API __declspec(dllexport)
#  define EXMP
# else
#  define ABS_SOCKET_API __declspec(dllimport)
#  define EXMP	extern
# endif
#elif defined(linux)
# define ABS_SOCKET_API
#else
# error "Unsupported Operating System"
#endif

// Cette classe est exportée de abs_socket.dll