#include<Windows.h>
#include<stdio.h>
#include"ClassFactoryDllServerWithRegFile.h"

ISum *pISum = NULL;
ISubtract *pISubtract = NULL;
IUnknown *pIUnknown1 = NULL;
IUnknown *pIUnknown2 = NULL;


int main(void)
{
	HRESULT hr;
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		printf("failed to initialize com");
		return (-1);
	}

	HRESULT hr1;
	
	hr1 = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);
	if (FAILED(hr1))
	{
		printf("failed to create instance isum");
		return (-1);
	}

	pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
	
	printf("Going to verify identity property ...\n");
	pISum->QueryInterface(IID_IUnknown, (void **)&pIUnknown1);
	pISubtract->QueryInterface(IID_IUnknown, (void **)&pIUnknown2);

	pISum->Release();
	pISubtract->Release();

	if (pIUnknown1 == pIUnknown2)
		printf("Identity proved\n");
	else
		printf("Identity failed\n");
	 
	pIUnknown1->Release();
	pIUnknown2->Release();

	return (0);
}