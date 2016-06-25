

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sat Jun 25 19:51:22 2016
 */
/* Compiler settings for MFCAppclient.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

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


#ifndef __MFCAppclient_h_h__
#define __MFCAppclient_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMFCAppclient_FWD_DEFINED__
#define __IMFCAppclient_FWD_DEFINED__
typedef interface IMFCAppclient IMFCAppclient;

#endif 	/* __IMFCAppclient_FWD_DEFINED__ */


#ifndef __MFCAppclient_FWD_DEFINED__
#define __MFCAppclient_FWD_DEFINED__

#ifdef __cplusplus
typedef class MFCAppclient MFCAppclient;
#else
typedef struct MFCAppclient MFCAppclient;
#endif /* __cplusplus */

#endif 	/* __MFCAppclient_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __MFCAppclient_LIBRARY_DEFINED__
#define __MFCAppclient_LIBRARY_DEFINED__

/* library MFCAppclient */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MFCAppclient;

#ifndef __IMFCAppclient_DISPINTERFACE_DEFINED__
#define __IMFCAppclient_DISPINTERFACE_DEFINED__

/* dispinterface IMFCAppclient */
/* [uuid] */ 


EXTERN_C const IID DIID_IMFCAppclient;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2F6BAF5A-4C1D-4790-AD7C-67C8922B14D0")
    IMFCAppclient : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMFCAppclientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMFCAppclient * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMFCAppclient * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMFCAppclient * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMFCAppclient * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMFCAppclient * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMFCAppclient * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMFCAppclient * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IMFCAppclientVtbl;

    interface IMFCAppclient
    {
        CONST_VTBL struct IMFCAppclientVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMFCAppclient_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMFCAppclient_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMFCAppclient_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMFCAppclient_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMFCAppclient_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMFCAppclient_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMFCAppclient_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMFCAppclient_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MFCAppclient;

#ifdef __cplusplus

class DECLSPEC_UUID("ACCD5739-C80D-4EE4-A07B-DF737ACE53C5")
MFCAppclient;
#endif
#endif /* __MFCAppclient_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


