========================================================================
    BIBLIOTHÈQUE ATL : vue d'ensemble du projet tstlib
========================================================================

AppWizard a créé ce projet tstlib pour vous afin que vous l'utilisiez comme point de départ pour l'écriture
de votre DLL.
Ce projet est implémenté avec des attributs Visual C++.

Ce fichier contient un résumé du contenu de chacun des fichiers qui
constituent votre projet.

tstlib.vcproj
    Il s'agit du fichier projet principal pour les projets VC++ générés à l'aide d'un Assistant Application. 
    Il contient les informations sur la version de Visual C++ qui a généré le fichier et 
    des informations sur les plates-formes, configurations et fonctionnalités du projet sélectionnées avec
    l'Assistant Application.

_tstlib.idl
    Ce fichier sera généré par le compilateur lorsque le projet est généré. Il contiendra les définitions IDL 
    de la bibliothèque de types, les interfaces et les co-classes définies dans votre projet.
    Ce fichier sera traité par le compilateur MIDL pour générer :
        les définitions d'interface C++ et les déclarations GUID (_tstlib.h)
        Définitions GUID                                (_tstlib_i.c)
        Une bibliothèque de types                                  (_tstlib.tlb)
        Code de marshaling                                 (_tstlib_p.c et dlldata.c)
tstlib.cpp
    Ce fichier contient la table d'objets et l'implémentation des exportations de votre DLL.
tstlib.rc
    Il s'agit de la liste de toutes les ressources Microsoft Windows que le
    programme utilise.

tstlib.def
    Ce fichier de définition de module fournit à l'éditeur de liens des informations sur les exportations
    requises par votre DLL. Il contient les exportations pour :
        DllGetClassObject  
        DllCanUnloadNow    
        GetProxyDllInfo    
        DllRegisterServer	
        DllUnregisterServer

/////////////////////////////////////////////////////////////////////////////
Autres fichiers standard :

StdAfx.h, StdAfx.cpp
    Ces fichiers sont utilisés pour générer un fichier d'en-tête précompilé (PCH) 
    nommé tstlib.pch et un fichier de type précompilé nommé StdAfx.obj.

Resource.h
    Il s'agit du fichier d'en-tête standard qui définit les ID de ressources.

/////////////////////////////////////////////////////////////////////////////
Fichier de définition de module et projet de DLL proxy/stub :

tstlibps.vcproj
    Ce fichier est le fichier projet pour la génération d'une DLL proxy/stub DLL si nécessaire.
	Le fichier IDL du projet principal doit contenir au moins une interface et vous devez 
	compiler en premier le fichier IDL avant de générer la DLL proxy/stub.	Ce processus génère
	dlldata.c, tstlib_i.c et tstlib_p.c qui sont requis
	pour générer la DLL proxy/stub.

tstlibps.def
    Ce fichier de définition de module fournit à l'éditeur de liens les informations sur les exportations
    requises par proxy/stub.
/////////////////////////////////////////////////////////////////////////////
