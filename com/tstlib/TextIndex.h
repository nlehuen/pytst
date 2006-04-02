// TextIndex.h : déclaration de CTextIndex

#pragma once
#include "resource.h"       // symboles principaux

#include "comutil.h"
#include "../../textindex/textindex.h"

#include "DocumentsScore.h"

// ITextIndex
[
	object,
	uuid("3DF00A4D-6253-4D65-A586-6CE5E29B8980"),
	dual,	helpstring("Interface ITextIndex"),
	pointer_default(unique)
]
__interface ITextIndex : IDispatch
{
    [id(1), helpstring("method AddWord")] HRESULT AddWord([in] BSTR* word, [in] BSTR* document);
    [id(2), helpstring("method AddText")] HRESULT AddText([in] BSTR* text, [in] BSTR* document);
    [id(3), helpstring("method Pack")] HRESULT Pack(void);
    [id(4), helpstring("method FindWord")] HRESULT FindWord([in] BSTR* word,[out,retval] IDocumentsScore** result);
    [id(5), helpstring("method FindText")] HRESULT FindText([in] BSTR* text,[in] LONG intersect,[out,retval] IDocumentsScore** result);
    [propget, id(6), helpstring("property Version")] HRESULT Version([out, retval] BSTR* pVal);
    [id(7), helpstring("method Load")] HRESULT Load([in] BSTR* filename,[out,retval] LONG* result);
    [id(8), helpstring("method Save")] HRESULT Save([in] BSTR* filename,[out,retval] LONG* result);
    [id(9), helpstring("method RemoveDocument")] HRESULT RemoveDocument([in] BSTR* document);
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
public:
    typedef textindex<wchar_t,_bstr_t,_bstr_t_reader_writer> index_type;

private:
    index_type _textindex;

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

    STDMETHOD(AddWord)(BSTR* word, BSTR* document);
    STDMETHOD(AddText)(BSTR* text, BSTR* document);
    STDMETHOD(Pack)(void);
    STDMETHOD(FindWord)(BSTR* word, IDocumentsScore** result);
    STDMETHOD(FindText)(BSTR* text, LONG intersect, IDocumentsScore** result);
    STDMETHOD(get_Version)(BSTR* pVal);
    STDMETHOD(Load)(BSTR* filename,LONG* result);
    STDMETHOD(Save)(BSTR* filename,LONG* result);
    STDMETHOD(RemoveDocument)(BSTR* document);
};

