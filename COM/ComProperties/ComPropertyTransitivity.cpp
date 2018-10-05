#include<Windows.h>
#include<stdio.h>
#include"ClassFactoryDllServerWithRegFile.h"

ISum *pISum1 = NULL;
ISubtract *pISubtract = NULL;
IUnknown *pIUnknown = NULL;

int main(void)
{
	HRESULT hr;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		printf("failed to initialize com");
		return (-1);
	}

	hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum1);
	if (FAILED(hr))
	{
		printf("failed to create instance isum");
		return (-1);
	}

	printf("Going to verify Transitivity property ...\n");

	
	pISum1->QueryInterface(IID_ISubtract, (void **)&pISubtract);
	pISubtract->QueryInterface(IID_ISum, (void **)&pIUnknown);

	if (pIUnknown != NULL)
		printf("Transitivity proved\n");
	else
		printf("Transitivity failed\n");

	pISum1->Release();
	pISubtract->Release();
	pIUnknown->Release();
	
	return (0);
}
