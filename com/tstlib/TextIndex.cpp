// TextIndex.cpp : implémentation de CTextIndex

#include "stdafx.h"
#include "TextIndex.h"
#include ".\textindex.h"

#include <iostream>
#include <string>

// CTextIndex


STDMETHODIMP CTextIndex::AddWord(BSTR* word, BSTR* document)
{
    _textindex.put_word(std::wstring(*word),_bstr_t(*document,true));
    return S_OK;
}

STDMETHODIMP CTextIndex::AddText(BSTR* text, BSTR* document)
{
    _textindex.put_text(std::wstring(*text),_bstr_t(*document,true));
    return S_OK;
}

STDMETHODIMP CTextIndex::Pack(void)
{
    _textindex.pack();
    return S_OK;
}

STDMETHODIMP CTextIndex::FindWord(BSTR* word,IDocumentsScore** result)
{
    CDocumentsScore::CreateInstance(result);
    static_cast<CDocumentsScore*>(*result)->set_entries(_textindex.find_word(std::wstring(*word)));
    return S_OK;
}

STDMETHODIMP CTextIndex::FindText(BSTR* text, LONG intersect,IDocumentsScore** result)
{
    CDocumentsScore::CreateInstance(result);
    static_cast<CDocumentsScore*>(*result)->set_entries(_textindex.find_text(std::wstring(*text),intersect));
    return S_OK;
}

STDMETHODIMP CTextIndex::get_Version(BSTR* pVal)
{
    *pVal = _bstr_t(TST_VERSION).Detach();
    return S_OK;
}
STDMETHODIMP CTextIndex::Load(BSTR* filename,LONG* result)
{
    *result = 0;
    FILE* file = _wfopen(*filename,L"rb");
    if(file == 0) {
        *result = 0;
    }
    else {
        try {
            _textindex.read(file);
            fclose(file);
            *result = 1;
        }
        catch(exception) {
            *result = 0;
        }
    }
    return S_OK;
}

STDMETHODIMP CTextIndex::Save(BSTR* filename,LONG* result)
{
    _textindex.pack();
    FILE* file = _wfopen(*filename,L"wb");
    if(file == 0) {
        *result = 0;
    }
    else {
        try {
            _textindex.write(file);
            fflush(file);
            fclose(file);
            *result = 1;
        }
        catch(exception) {
            *result = 0;
        }
    }
    return S_OK;
}
