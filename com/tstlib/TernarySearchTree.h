// TernarySearchTree.h : déclaration de CTernarySearchTree

#pragma once
#include "resource.h"       // symboles principaux

#include "tst.h"
#include "comutil.h"

// ITernarySearchTree
[
	object,
	uuid("543BA9E0-60DF-42F8-9BDA-C573FB4EC091"),
	dual,	helpstring("Interface ITernarySearchTree"),
	pointer_default(unique)
]
__interface ITernarySearchTree : IDispatch
{
    [id(1), helpstring("method Set")] HRESULT Set([in] BSTR* key, [in] BSTR* value, [out,retval] BSTR* result);
    [id(2), helpstring("method Get")] HRESULT Get([in] BSTR* key, [out,retval] BSTR* result);
    [id(3), helpstring("method Pack")] HRESULT Pack(void);
};



// CTernarySearchTree

[
	coclass,
	threading("apartment"),
	vi_progid("tstlib.TernarySearchTree"),
	progid("tstlib.TernarySearchTree.1"),
	version(1.0),
	uuid("01757CCD-8F45-498E-B8BF-4E4F95A07CE7"),
	helpstring("TernarySearchTree Class")
]
class ATL_NO_VTABLE CTernarySearchTree : 
	public ITernarySearchTree
{
private:
    tst<wchar_t,_bstr_t> _tst;

public:
    CTernarySearchTree() : _tst()
	{
	}


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
    STDMETHOD(Set)(BSTR* key, BSTR* value, BSTR* result);
    STDMETHOD(Get)(BSTR* key,BSTR* result);
    STDMETHOD(Pack)(void);
};

