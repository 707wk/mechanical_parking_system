

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Aug 12 16:49:55 2016
 */
/* Compiler settings for MFCApp.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

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

MIDL_DEFINE_GUID(IID, LIBID_MFCApp,0x66B0105E,0xC748,0x4017,0xAB,0xF1,0x11,0xC9,0x5E,0x6A,0xF2,0xBE);


MIDL_DEFINE_GUID(IID, DIID_IMFCApp,0x55B8A36C,0xFA2F,0x42DC,0xB9,0xDD,0x7C,0xD5,0xCA,0x5A,0x0C,0x21);


MIDL_DEFINE_GUID(CLSID, CLSID_MFCApp,0x20513BA5,0x74E9,0x424F,0xAD,0xB7,0x89,0xD5,0x28,0xB9,0xD4,0x41);


MIDL_DEFINE_GUID(IID, DIID_Idebugmodel,0xABBA8598,0x9C60,0x4A1F,0x90,0xDF,0xED,0x4E,0xB9,0xBE,0x86,0x97);


MIDL_DEFINE_GUID(CLSID, CLSID_debugmodel,0x23A05A32,0x1319,0x4691,0x9A,0xDB,0x85,0x45,0xB3,0xEC,0x34,0x8A);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



