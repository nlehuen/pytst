// DocumentsScore.h : déclaration de CDocumentsScore

#pragma once
#include "resource.h"       // symboles principaux

#include "comutil.h"
#include "../../textindex/textindex.h"

class _bstr_t_reader_writer {
    public:
        void write(std::ostream& file, _bstr_t value) {
            int length=value.length();
            file.write((char*)(&length),sizeof(int));
            file.write((char*)((wchar_t*)(value)),length*sizeof(wchar_t));
        }
        
        _bstr_t read(std::istream& file) {
            int length;
            file.read((char*)(&length),sizeof(int));
            wchar_t* buffer=static_cast<wchar_t*>(tst_malloc(length*sizeof(wchar_t)));
            file.read((char*)(buffer),length*sizeof(wchar_t));
            BSTR result = SysAllocStringLen(buffer,length);
            tst_free(buffer);
            return _bstr_t(result,false);
        }
};

// IDocumentsScore
[
	object,
	uuid("1741BA73-3BC1-4CD0-BFF1-8CB5FA5C077A"),
	dual,	helpstring("Interface IDocumentsScore"),
	pointer_default(unique)
]
__interface IDocumentsScore : IDispatch
{
    [propget, id(1), helpstring("property Size")] HRESULT Size([out, retval] LONG* pVal);
    [id(2), helpstring("method GetDocument")] HRESULT GetDocument([in] LONG index, [out,retval] BSTR* document);
    [id(3), helpstring("method GetScore")] HRESULT GetScore([in] LONG index, [out,retval] LONG* score);
};



// CDocumentsScore

[
	coclass,
	threading("apartment"),
	vi_progid("tstlib.DocumentsScore"),
	progid("tstlib.DocumentsScore.1"),
	version(1.0),
	uuid("98F35214-F66B-4BBF-B039-1AA4CA344DCF"),
	helpstring("DocumentsScore Class")
]
class ATL_NO_VTABLE CDocumentsScore : 
	public IDocumentsScore
{
public:
	CDocumentsScore()
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
    textindex<wchar_t,_bstr_t,_bstr_t_reader_writer>::result_pointer entries;

    void set_entries(textindex<wchar_t,_bstr_t,_bstr_t_reader_writer>::result_pointer _entries);

    STDMETHOD(get_Size)(LONG* pVal);
    STDMETHOD(GetDocument)(LONG index, BSTR* document);
    STDMETHOD(GetScore)(LONG index, LONG* score);
};

