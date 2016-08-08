

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Aug 08 15:48:48 2016
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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __MFCApp_h_h__
#define __MFCApp_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMFCApp_FWD_DEFINED__
#define __IMFCApp_FWD_DEFINED__
typedef interface IMFCApp IMFCApp;

#endif 	/* __IMFCApp_FWD_DEFINED__ */


#ifndef __MFCApp_FWD_DEFINED__
#define __MFCApp_FWD_DEFINED__

#ifdef __cplusplus
typedef class MFCApp MFCApp;
#else
typedef struct MFCApp MFCApp;
#endif /* __cplusplus */

#endif 	/* __MFCApp_FWD_DEFINED__ */


#ifndef __Idebugmodel_FWD_DEFINED__
#define __Idebugmodel_FWD_DEFINED__
typedef interface Idebugmodel Idebugmodel;

#endif 	/* __Idebugmodel_FWD_DEFINED__ */


#ifndef __debugmodel_FWD_DEFINED__
#define __debugmodel_FWD_DEFINED__

#ifdef __cplusplus
typedef class debugmodel debugmodel;
#else
typedef struct debugmodel debugmodel;
#endif /* __cplusplus */

#endif 	/* __debugmodel_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __MFCApp_LIBRARY_DEFINED__
#define __MFCApp_LIBRARY_DEFINED__

/* library MFCApp */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MFCApp;

#ifndef __IMFCApp_DISPINTERFACE_DEFINED__
#define __IMFCApp_DISPINTERFACE_DEFINED__

/* dispinterface IMFCApp */
/* [uuid] */ 


EXTERN_C const IID DIID_IMFCApp;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("55B8A36C-FA2F-42DC-B9DD-7CD5CA5A0C21")
    IMFCApp : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMFCAppVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMFCApp * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMFCApp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMFCApp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMFCApp * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMFCApp * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMFCApp * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMFCApp * This,
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
    } IMFCAppVtbl;

    interface IMFCApp
    {
        CONST_VTBL struct IMFCAppVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMFCApp_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMFCApp_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMFCApp_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMFCApp_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMFCApp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMFCApp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMFCApp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMFCApp_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MFCApp;

#ifdef __cplusplus

class DECLSPEC_UUID("20513BA5-74E9-424F-ADB7-89D528B9D441")
MFCApp;
#endif

#ifndef __Idebugmodel_DISPINTERFACE_DEFINED__
#define __Idebugmodel_DISPINTERFACE_DEFINED__

/* dispinterface Idebugmodel */
/* [uuid] */ 


EXTERN_C const IID DIID_Idebugmodel;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("ABBA8598-9C60-4A1F-90DF-ED4EB9BE8697")
    Idebugmodel : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IdebugmodelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            Idebugmodel * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            Idebugmodel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            Idebugmodel * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            Idebugmodel * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            Idebugmodel * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            Idebugmodel * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            Idebugmodel * This,
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
    } IdebugmodelVtbl;

    interface Idebugmodel
    {
        CONST_VTBL struct IdebugmodelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Idebugmodel_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define Idebugmodel_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define Idebugmodel_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define Idebugmodel_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define Idebugmodel_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define Idebugmodel_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define Idebugmodel_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __Idebugmodel_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_debugmodel;

#ifdef __cplusplus

class DECLSPEC_UUID("23A05A32-1319-4691-9ADB-8545B3EC348A")
debugmodel;
#endif
#endif /* __MFCApp_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


