// ProfilingDLLs.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <Windows.h>


#include "../DllImprimir/DllImprimir.h"


typedef int(*importFunction)(int, int);

using namespace std;

int main()
{
	// funcion cargada
	importFunction operation;

	// puntero a la libreria
	HINSTANCE hinstLib = NULL;

	int selectedNum;

	cout << "Selecciona la operacion: \n  (0: Mult) \n (1: Sum) " << endl;

	cin >> selectedNum;


	switch (selectedNum)
	{
	case 0:
		hinstLib = LoadLibrary(TEXT("DLLMult_d.dll"));
		break;
	case 1:
		hinstLib = LoadLibrary(TEXT("DLLSuma_d.dll"));
		break;
	default:
		cout << "Opcion no valida" << endl;
	}

	// Cargar la libreria
	

	if (hinstLib == NULL) {
		cout << "No se ha cargado la DLL: " << GetLastError() << endl;

		return 1;
	}


	//Buscar la funcion
	

	// El nombre de la funcion lo hemos copiado desde Dependency Walker
	operation = (importFunction)GetProcAddress(hinstLib, "?makeOperation@@YAHHH@Z");
	
	if (operation == NULL)
	{
		cout << "No se ha encontrado la funcion: " << GetLastError() << endl;
		FreeLibrary(hinstLib);
		return 1;
	}

	cout << "Ejecutando Codigo" << endl;

	while (1)
	{
		cout << "El resultado es: " << (*operation)(3, 4) << endl;
		Sleep(1000);
	}


    return 0;
}

