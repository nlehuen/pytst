// DocumentsScore.cpp : implémentation de CDocumentsScore

#include "stdafx.h"
#include "DocumentsScore.h"
#include ".\documentsscore.h"


// CDocumentsScore


STDMETHODIMP CDocumentsScore::get_Size(LONG* pVal)
{
    *pVal = static_cast<LONG>(entries->size());
    return S_OK;
}

void CDocumentsScore::set_entries(textindex<wchar_t,_bstr_t,_bstr_t_reader_writer>::documents_scores_pointer _entries) {
    entries = _entries;
}

STDMETHODIMP CDocumentsScore::GetDocument(LONG index, BSTR* document)
{
    if(index>=0 && static_cast<size_t>(index)<entries->size()) {
        *document = entries->get_document(index).copy();
    }
    else {
        *document = _bstr_t("???");
    }
    return S_OK;
}

STDMETHODIMP CDocumentsScore::GetScore(LONG index, LONG* score)
{
    if(index>=0 && static_cast<size_t>(index)<entries->size()) {
        *score = entries->get_score(index);
    }
    else {
        *score = 0;
    }
    return S_OK;
}
