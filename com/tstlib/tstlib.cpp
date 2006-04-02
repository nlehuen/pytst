// tstlib.cpp : implémentation des exportations de DLL.

#include "stdafx.h"
#include "resource.h"

// L'attribut du module a provoqué l'implémentation automatique de DllMain, DllRegisterServer et DllUnregisterServer
[ module(dll, uuid = "{013A8F97-F0CA-4F8E-BA0E-75B1FEB9DF79}", 
		 name = "tstlib", 
		 helpstring = "Bibliotheque de types tstlib 1.0",
		 resource_name = "IDR_TSTLIB") ]
class CtstlibModule
{
public:
// Se substitue aux membres CAtlDllModuleT
};
		 
