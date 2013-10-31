// Le bloc ifdef suivant est la fa�on standard de cr�er des macros qui facilitent l'exportation 
// � partir d'une DLL. Tous les fichiers contenus dans cette DLL sont compil�s avec le symbole ABS_SOCKET_EXPORTS
// d�fini sur la ligne de commande. Ce symbole ne doit pas �tre d�fini pour un projet
// qui utilisent cette DLL. De cette mani�re, les autres projets dont les fichiers sources comprennent ce fichier consid�rent les fonctions 
// ABS_SOCKET_API comme �tant import�es � partir d'une DLL, tandis que cette DLL consid�re les symboles
// d�finis avec cette macro comme �tant export�s.
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

// Cette classe est export�e de abs_socket.dll