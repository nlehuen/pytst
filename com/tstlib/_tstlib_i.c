

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IDocumentsScore,0x1741BA73,0x3BC1,0x4CD0,0xBF,0xF1,0x8C,0xB5,0xFA,0x5C,0x07,0x7A);


MIDL_DEFINE_GUID(IID, IID_ITextIndex,0x3DF00A4D,0x6253,0x4D65,0xA5,0x86,0x6C,0xE5,0xE2,0x9B,0x89,0x80);


MIDL_DEFINE_GUID(IID, LIBID_tstlib,0x013A8F97,0xF0CA,0x4F8E,0xBA,0x0E,0x75,0xB1,0xFE,0xB9,0xDF,0x79);


MIDL_DEFINE_GUID(CLSID, CLSID_CDocumentsScore,0x98F35214,0xF66B,0x4BBF,0xB0,0x39,0x1A,0xA4,0xCA,0x34,0x4D,0xCF);


MIDL_DEFINE_GUID(CLSID, CLSID_CTextIndex,0x8EC92961,0xCAB3,0x4CA6,0xA3,0x6E,0x46,0xC3,0x94,0x24,0xE8,0x0B);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

