// TextIndex.h : déclaration de CTextIndex

#pragma once
#include "resource.h"       // symboles principaux

#include "../../textindex/textindex.h"

// ITextIndex
[
	object,
	uuid("3DF00A4D-6253-4D65-A586-6CE5E29B8980"),
	dual,	helpstring("Interface ITextIndex"),
	pointer_default(unique)
]
__interface ITextIndex : IDispatch
{
};



// CTextIndex

[
	coclass,
	threading("apartment"),
	vi_progid("tstlib.TextIndex"),
	progid("tstlib.TextIndex.1"),
	version(1.0),
	uuid("8EC92961-CAB3-4CA6-A36E-46C39424E80B"),
	helpstring("TextIndex Class")
]
class ATL_NO_VTABLE CTextIndex : 
	public ITextIndex
{
private:
    textindex<wchar_t,CComBSTR> _textindex;

public:
    CTextIndex() : _textindex()
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

};

