// TextIndex.cpp : implémentation de CTextIndex

#include "stdafx.h"
#include "TextIndex.h"
#include ".\textindex.h"

#include <iostream>
#include <fstream>
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
    try {
        FILE* fin=_wfopen(*filename, L"rb");
        if(!fin) throw TSTException("Could not open file");
        std::ifstream in(fin);
        in.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
        _textindex.read(in);
        in.close();
        *result = 1;
    }
    catch(exception) {
        *result = 0;
    }
    return S_OK;
}

STDMETHODIMP CTextIndex::Save(BSTR* filename,LONG* result)
{
    _textindex.pack();
    try {
        FILE* fout=_wfopen(*filename, L"wb");
        if(!fout) throw TSTException("Could not open file");
        std::ofstream out(fout);
        out.exceptions(std::ofstream::eofbit | std::ofstream::failbit | std::ofstream::badbit);
        _textindex.write(out);
        out.flush();
        out.close();
        *result = 1;
    }
    catch(exception) {
        *result = 0;
    }
    return S_OK;
}

STDMETHODIMP CTextIndex::RemoveDocument(BSTR* document)
{
    _textindex.remove_document(_bstr_t(*document,true));
    return S_OK;
}
