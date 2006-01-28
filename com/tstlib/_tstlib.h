

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Fri Jan 27 21:30:11 2006
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

#ifndef __ITernarySearchTree_FWD_DEFINED__
#define __ITernarySearchTree_FWD_DEFINED__
typedef interface ITernarySearchTree ITernarySearchTree;
#endif 	/* __ITernarySearchTree_FWD_DEFINED__ */


#ifndef __CTernarySearchTree_FWD_DEFINED__
#define __CTernarySearchTree_FWD_DEFINED__

#ifdef __cplusplus
typedef class CTernarySearchTree CTernarySearchTree;
#else
typedef struct CTernarySearchTree CTernarySearchTree;
#endif /* __cplusplus */

#endif 	/* __CTernarySearchTree_FWD_DEFINED__ */


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

#ifndef __ITernarySearchTree_INTERFACE_DEFINED__
#define __ITernarySearchTree_INTERFACE_DEFINED__

/* interface ITernarySearchTree */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITernarySearchTree;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("543BA9E0-60DF-42F8-9BDA-C573FB4EC091")
    ITernarySearchTree : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Set( 
            /* [in] */ BSTR *key,
            /* [in] */ BSTR *value,
            /* [retval][out] */ BSTR *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Get( 
            /* [in] */ BSTR *key,
            /* [retval][out] */ BSTR *result) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITernarySearchTreeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITernarySearchTree * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITernarySearchTree * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITernarySearchTree * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITernarySearchTree * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITernarySearchTree * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITernarySearchTree * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITernarySearchTree * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Set )( 
            ITernarySearchTree * This,
            /* [in] */ BSTR *key,
            /* [in] */ BSTR *value,
            /* [retval][out] */ BSTR *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Get )( 
            ITernarySearchTree * This,
            /* [in] */ BSTR *key,
            /* [retval][out] */ BSTR *result);
        
        END_INTERFACE
    } ITernarySearchTreeVtbl;

    interface ITernarySearchTree
    {
        CONST_VTBL struct ITernarySearchTreeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITernarySearchTree_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITernarySearchTree_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITernarySearchTree_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITernarySearchTree_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITernarySearchTree_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITernarySearchTree_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITernarySearchTree_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITernarySearchTree_Set(This,key,value,result)	\
    (This)->lpVtbl -> Set(This,key,value,result)

#define ITernarySearchTree_Get(This,key,result)	\
    (This)->lpVtbl -> Get(This,key,result)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITernarySearchTree_Set_Proxy( 
    ITernarySearchTree * This,
    /* [in] */ BSTR *key,
    /* [in] */ BSTR *value,
    /* [retval][out] */ BSTR *result);


void __RPC_STUB ITernarySearchTree_Set_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITernarySearchTree_Get_Proxy( 
    ITernarySearchTree * This,
    /* [in] */ BSTR *key,
    /* [retval][out] */ BSTR *result);


void __RPC_STUB ITernarySearchTree_Get_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITernarySearchTree_INTERFACE_DEFINED__ */



#ifndef __tstlib_LIBRARY_DEFINED__
#define __tstlib_LIBRARY_DEFINED__

/* library tstlib */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_tstlib;

EXTERN_C const CLSID CLSID_CTernarySearchTree;

#ifdef __cplusplus

class DECLSPEC_UUID("01757CCD-8F45-498E-B8BF-4E4F95A07CE7")
CTernarySearchTree;
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

