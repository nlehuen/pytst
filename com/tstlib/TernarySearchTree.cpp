// TernarySearchTree.cpp : implémentation de CTernarySearchTree

#include "stdafx.h"
#include "TernarySearchTree.h"
#include ".\ternarysearchtree.h"


// CTernarySearchTree


STDMETHODIMP CTernarySearchTree::Set(BSTR* key, BSTR* value, BSTR* result)
{
    CComBSTR _key(*key);
    CComBSTR _value(*value);
    *result = CComBSTR(_tst.put(_key.m_str,_key.Length(),_value));
    return S_OK;
}

STDMETHODIMP CTernarySearchTree::Get(BSTR* key, BSTR* result)
{
    CComBSTR _key(*key);
    *result = CComBSTR(_tst.get(_key.m_str,_key.Length()));
    return S_OK;
}

STDMETHODIMP CTernarySearchTree::Pack(void)
{
    _tst.pack();
    return S_OK;
}
