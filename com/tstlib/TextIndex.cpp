// TextIndex.cpp : implémentation de CTextIndex

#include "stdafx.h"
#include "TextIndex.h"
#include ".\textindex.h"

#include <iostream>
#include <string>

// CTextIndex


STDMETHODIMP CTextIndex::AddWord(BSTR* word, BSTR* document)
{
    _textindex.put_word(std::wstring(*word),CComBSTR(*document));
    return S_OK;
}

STDMETHODIMP CTextIndex::AddText(BSTR* text, BSTR* document)
{
    _textindex.put_text(std::wstring(*text),CComBSTR(*document));
    return S_OK;
}

STDMETHODIMP CTextIndex::Pack(void)
{
    _textindex.pack();
    return S_OK;
}

STDMETHODIMP CTextIndex::FindWord(BSTR* word)
{
    index_type::p_entries entries(_textindex.find_word(std::wstring(*word)));
    for(index_type::p_entries::element_type::iterator s(entries->begin()),e(entries->end());s != e;s++) {
    }
    return S_OK;
}

STDMETHODIMP CTextIndex::FindText(BSTR* text, USHORT intersect)
{
    index_type::p_entries entries(_textindex.find_text(std::wstring(*text),intersect));
    for(index_type::p_entries::element_type::iterator s(entries->begin()),e(entries->end());s != e;s++) {
    }
    return S_OK;
}
