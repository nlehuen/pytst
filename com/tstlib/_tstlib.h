

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sun Jul 16 11:58:43 2006
 */
/* Compiler settings for _tstlib.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef ___tstlib_h__
#define ___tstlib_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDocumentsScore_FWD_DEFINED__
#define __IDocumentsScore_FWD_DEFINED__
typedef interface IDocumentsScore IDocumentsScore;
#endif 	/* __IDocumentsScore_FWD_DEFINED__ */


#ifndef __ITextIndex_FWD_DEFINED__
#define __ITextIndex_FWD_DEFINED__
typedef interface ITextIndex ITextIndex;
#endif 	/* __ITextIndex_FWD_DEFINED__ */


#ifndef __CDocumentsScore_FWD_DEFINED__
#define __CDocumentsScore_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDocumentsScore CDocumentsScore;
#else
typedef struct CDocumentsScore CDocumentsScore;
#endif /* __cplusplus */

#endif 	/* __CDocumentsScore_FWD_DEFINED__ */


#ifndef __CTextIndex_FWD_DEFINED__
#define __CTextIndex_FWD_DEFINED__

#ifdef __cplusplus
typedef class CTextIndex CTextIndex;
#else
typedef struct CTextIndex CTextIndex;
#endif /* __cplusplus */

#endif 	/* __CTextIndex_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IDocumentsScore_INTERFACE_DEFINED__
#define __IDocumentsScore_INTERFACE_DEFINED__

/* interface IDocumentsScore */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDocumentsScore;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1741BA73-3BC1-4CD0-BFF1-8CB5FA5C077A")
    IDocumentsScore : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDocument( 
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *document) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetScore( 
            /* [in] */ LONG index,
            /* [retval][out] */ LONG *score) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDocumentsScoreVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDocumentsScore * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDocumentsScore * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDocumentsScore * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDocumentsScore * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDocumentsScore * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDocumentsScore * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDocumentsScore * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            IDocumentsScore * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDocument )( 
            IDocumentsScore * This,
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *document);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetScore )( 
            IDocumentsScore * This,
            /* [in] */ LONG index,
            /* [retval][out] */ LONG *score);
        
        END_INTERFACE
    } IDocumentsScoreVtbl;

    interface IDocumentsScore
    {
        CONST_VTBL struct IDocumentsScoreVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDocumentsScore_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDocumentsScore_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDocumentsScore_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDocumentsScore_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDocumentsScore_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDocumentsScore_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDocumentsScore_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDocumentsScore_get_Size(This,pVal)	\
    (This)->lpVtbl -> get_Size(This,pVal)

#define IDocumentsScore_GetDocument(This,index,document)	\
    (This)->lpVtbl -> GetDocument(This,index,document)

#define IDocumentsScore_GetScore(This,index,score)	\
    (This)->lpVtbl -> GetScore(This,index,score)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDocumentsScore_get_Size_Proxy( 
    IDocumentsScore * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IDocumentsScore_get_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDocumentsScore_GetDocument_Proxy( 
    IDocumentsScore * This,
    /* [in] */ LONG index,
    /* [retval][out] */ BSTR *document);


void __RPC_STUB IDocumentsScore_GetDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDocumentsScore_GetScore_Proxy( 
    IDocumentsScore * This,
    /* [in] */ LONG index,
    /* [retval][out] */ LONG *score);


void __RPC_STUB IDocumentsScore_GetScore_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDocumentsScore_INTERFACE_DEFINED__ */


#ifndef __ITextIndex_INTERFACE_DEFINED__
#define __ITextIndex_INTERFACE_DEFINED__

/* interface ITextIndex */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITextIndex;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3DF00A4D-6253-4D65-A586-6CE5E29B8980")
    ITextIndex : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddWord( 
            /* [in] */ BSTR *word,
            /* [in] */ BSTR *document) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddText( 
            /* [in] */ BSTR *text,
            /* [in] */ BSTR *document) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pack( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindWord( 
            /* [in] */ BSTR *word,
            /* [retval][out] */ IDocumentsScore **result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindTextA( 
            /* [in] */ BSTR *text,
            /* [in] */ LONG intersect,
            /* [retval][out] */ IDocumentsScore **result) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveDocument( 
            /* [in] */ BSTR *document) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITextIndexVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITextIndex * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITextIndex * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITextIndex * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITextIndex * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITextIndex * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITextIndex * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITextIndex * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddWord )( 
            ITextIndex * This,
            /* [in] */ BSTR *word,
            /* [in] */ BSTR *document);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddText )( 
            ITextIndex * This,
            /* [in] */ BSTR *text,
            /* [in] */ BSTR *document);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Pack )( 
            ITextIndex * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindWord )( 
            ITextIndex * This,
            /* [in] */ BSTR *word,
            /* [retval][out] */ IDocumentsScore **result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindTextA )( 
            ITextIndex * This,
            /* [in] */ BSTR *text,
            /* [in] */ LONG intersect,
            /* [retval][out] */ IDocumentsScore **result);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            ITextIndex * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            ITextIndex * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ LONG *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            ITextIndex * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ LONG *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveDocument )( 
            ITextIndex * This,
            /* [in] */ BSTR *document);
        
        END_INTERFACE
    } ITextIndexVtbl;

    interface ITextIndex
    {
        CONST_VTBL struct ITextIndexVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITextIndex_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITextIndex_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITextIndex_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITextIndex_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITextIndex_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITextIndex_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITextIndex_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITextIndex_AddWord(This,word,document)	\
    (This)->lpVtbl -> AddWord(This,word,document)

#define ITextIndex_AddText(This,text,document)	\
    (This)->lpVtbl -> AddText(This,text,document)

#define ITextIndex_Pack(This)	\
    (This)->lpVtbl -> Pack(This)

#define ITextIndex_FindWord(This,word,result)	\
    (This)->lpVtbl -> FindWord(This,word,result)

#define ITextIndex_FindTextA(This,text,intersect,result)	\
    (This)->lpVtbl -> FindTextA(This,text,intersect,result)

#define ITextIndex_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define ITextIndex_Load(This,filename,result)	\
    (This)->lpVtbl -> Load(This,filename,result)

#define ITextIndex_Save(This,filename,result)	\
    (This)->lpVtbl -> Save(This,filename,result)

#define ITextIndex_RemoveDocument(This,document)	\
    (This)->lpVtbl -> RemoveDocument(This,document)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextIndex_AddWord_Proxy( 
    ITextIndex * This,
    /* [in] */ BSTR *word,
    /* [in] */ BSTR *document);


void __RPC_STUB ITextIndex_AddWord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextIndex_AddText_Proxy( 
    ITextIndex * This,
    /* [in] */ BSTR *text,
    /* [in] */ BSTR *document);


void __RPC_STUB ITextIndex_AddText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextIndex_Pack_Proxy( 
    ITextIndex * This);


void __RPC_STUB ITextIndex_Pack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextIndex_FindWord_Proxy( 
    ITextIndex * This,
    /* [in] */ BSTR *word,
    /* [retval][out] */ IDocumentsScore **result);


void __RPC_STUB ITextIndex_FindWord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextIndex_FindTextA_Proxy( 
    ITextIndex * This,
    /* [in] */ BSTR *text,
    /* [in] */ LONG intersect,
    /* [retval][out] */ IDocumentsScore **result);


void __RPC_STUB ITextIndex_FindTextA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITextIndex_get_Version_Proxy( 
    ITextIndex * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITextIndex_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextIndex_Load_Proxy( 
    ITextIndex * This,
    /* [in] */ BSTR *filename,
    /* [retval][out] */ LONG *result);


void __RPC_STUB ITextIndex_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextIndex_Save_Proxy( 
    ITextIndex * This,
    /* [in] */ BSTR *filename,
    /* [retval][out] */ LONG *result);


void __RPC_STUB ITextIndex_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITextIndex_RemoveDocument_Proxy( 
    ITextIndex * This,
    /* [in] */ BSTR *document);


void __RPC_STUB ITextIndex_RemoveDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITextIndex_INTERFACE_DEFINED__ */



#ifndef __tstlib_LIBRARY_DEFINED__
#define __tstlib_LIBRARY_DEFINED__

/* library tstlib */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_tstlib;

EXTERN_C const CLSID CLSID_CDocumentsScore;

#ifdef __cplusplus

class DECLSPEC_UUID("98F35214-F66B-4BBF-B039-1AA4CA344DCF")
CDocumentsScore;
#endif

EXTERN_C const CLSID CLSID_CTextIndex;

#ifdef __cplusplus

class DECLSPEC_UUID("8EC92961-CAB3-4CA6-A36E-46C39424E80B")
CTextIndex;
#endif
#endif /* __tstlib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


