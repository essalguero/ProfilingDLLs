#ifndef _CFG_DLLIMPRIMIR_H_
#define _CFG_DLLIMPRIMIR_H_

//see http://gcc.gnu.org/wiki/Visibility

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
#define DLLIMPRIMIR_HELPER_DLL_IMPORT __declspec(dllimport)
#define DLLIMPRIMIR_HELPER_DLL_EXPORT __declspec(dllexport)
#define DLLIMPRIMIR_HELPER_DLL_LOCAL
#else
#if __GNUC__ >= 4
#define DLLIMPRIMIR_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
#define DLLIMPRIMIR_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
#define DLLIMPRIMIR_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define DLLIMPRIMIR_HELPER_DLL_IMPORT
#define DLLIMPRIMIR_HELPER_DLL_EXPORT
#define DLLIMPRIMIR_HELPER_DLL_LOCAL
#endif
#endif

// Now we use the generic helper definitions above to define DLLIMPRIMIR_API and DLLIMPRIMIR_LOCAL.
// DLLIMPRIMIR_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// DLLIMPRIMIR_LOCAL is used for non-api symbols.

#ifdef _USRDLL // defined if FOX is compiled as a DLL
#ifdef DLLIMPRIMIR_EXPORTS // defined if we are building the FOX DLL (instead of using it)
#define DLLIMPRIMIR_API DLLIMPRIMIR_HELPER_DLL_EXPORT
#else
#define DLLIMPRIMIR_API DLLIMPRIMIR_HELPER_DLL_IMPORT
#endif // DLLIMPRIMIR_DLL_EXPORTS
#define DLLIMPRIMIR_LOCAL DLLIMPRIMIR_HELPER_DLL_LOCAL
#else // DLLIMPRIMIR_DLL is not defined: this means FOX is a static lib.
#define DLLIMPRIMIR_API
#define DLLIMPRIMIR_LOCAL
#endif // DLLIMPRIMIR_DLL

#endif