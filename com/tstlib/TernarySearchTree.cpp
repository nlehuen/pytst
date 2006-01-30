// TernarySearchTree.cpp : implémentation de CTernarySearchTree

#include "stdafx.h"
#include "TernarySearchTree.h"
#include ".\ternarysearchtree.h"


// CTernarySearchTree


STDMETHODIMP CTernarySearchTree::Set(BSTR* key, BSTR* value, BSTR* result)
{
    *result = _tst.put(*key,SysStringLen(*key),_bstr_t(*value,true)).copy();
    return S_OK;
}

STDMETHODIMP CTernarySearchTree::Get(BSTR* key, BSTR* result)
{
    *result = _tst.get(*key,SysStringLen(*key)).copy();
    return S_OK;
}

STDMETHODIMP CTernarySearchTree::Pack(void)
{
    _tst.pack();
    return S_OK;
}

STDMETHODIMP CTernarySearchTree::get_Version(BSTR* pVal)
{
    *pVal = _bstr_t(TST_VERSION).Detach();
    return S_OK;
}
