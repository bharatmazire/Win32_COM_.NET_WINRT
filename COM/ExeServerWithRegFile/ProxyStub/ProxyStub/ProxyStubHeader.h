

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 08:44:07 2038
 */
/* Compiler settings for C:\MyVisualStudio2017Projects\01-Win32\01-Window\IDE\bharat_mazire_win32_assignments\COM\ExeServerWithRegFile\ProxyStub\ProxyStub.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
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
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ProxyStubHeader_h__
#define __ProxyStubHeader_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAdd_FWD_DEFINED__
#define __IAdd_FWD_DEFINED__
typedef interface IAdd IAdd;

#endif 	/* __IAdd_FWD_DEFINED__ */


#ifndef __IMinus_FWD_DEFINED__
#define __IMinus_FWD_DEFINED__
typedef interface IMinus IMinus;

#endif 	/* __IMinus_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IAdd_INTERFACE_DEFINED__
#define __IAdd_INTERFACE_DEFINED__

/* interface IAdd */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAdd;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("722368AB-D500-432F-92C6-BA44D57C0FA2")
    IAdd : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SumOfTwoIntegers( 
            /* [in] */ int __MIDL__IAdd0000,
            /* [in] */ int __MIDL__IAdd0001,
            /* [out][in] */ int *__MIDL__IAdd0002) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAddVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAdd * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAdd * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAdd * This);
        
        HRESULT ( STDMETHODCALLTYPE *SumOfTwoIntegers )( 
            IAdd * This,
            /* [in] */ int __MIDL__IAdd0000,
            /* [in] */ int __MIDL__IAdd0001,
            /* [out][in] */ int *__MIDL__IAdd0002);
        
        END_INTERFACE
    } IAddVtbl;

    interface IAdd
    {
        CONST_VTBL struct IAddVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAdd_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAdd_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAdd_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAdd_SumOfTwoIntegers(This,__MIDL__IAdd0000,__MIDL__IAdd0001,__MIDL__IAdd0002)	\
    ( (This)->lpVtbl -> SumOfTwoIntegers(This,__MIDL__IAdd0000,__MIDL__IAdd0001,__MIDL__IAdd0002) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAdd_INTERFACE_DEFINED__ */


#ifndef __IMinus_INTERFACE_DEFINED__
#define __IMinus_INTERFACE_DEFINED__

/* interface IMinus */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMinus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AB7DCBF9-0A26-46E9-BDB3-5CE8809BBDA0")
    IMinus : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SubtractionOfTwoIntegers( 
            /* [in] */ int __MIDL__IMinus0000,
            /* [in] */ int __MIDL__IMinus0001,
            /* [out][in] */ int *__MIDL__IMinus0002) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMinusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMinus * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMinus * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMinus * This);
        
        HRESULT ( STDMETHODCALLTYPE *SubtractionOfTwoIntegers )( 
            IMinus * This,
            /* [in] */ int __MIDL__IMinus0000,
            /* [in] */ int __MIDL__IMinus0001,
            /* [out][in] */ int *__MIDL__IMinus0002);
        
        END_INTERFACE
    } IMinusVtbl;

    interface IMinus
    {
        CONST_VTBL struct IMinusVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMinus_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMinus_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMinus_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMinus_SubtractionOfTwoIntegers(This,__MIDL__IMinus0000,__MIDL__IMinus0001,__MIDL__IMinus0002)	\
    ( (This)->lpVtbl -> SubtractionOfTwoIntegers(This,__MIDL__IMinus0000,__MIDL__IMinus0001,__MIDL__IMinus0002) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMinus_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


