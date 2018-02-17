// dllmain.cpp : Defines the entry point for the DLL application.

#include <Windows.h>
#include <iostream>

using namespace std;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		cout << "Te he hackeado" << endl << endl;
		break;
	case DLL_THREAD_ATTACH:
		cout << "Te he hackeado DLL_THREAD_ATTACH" << endl << endl;
		break;
	case DLL_THREAD_DETACH:
		cout << "Te he hackeado DLL_THREAD_DETACH" << endl << endl;
		break;
	case DLL_PROCESS_DETACH:
		cout << "Te he hackeado DLL_PROCESS_DETACH" << endl << endl;
		break;
	}
	return TRUE;
}

