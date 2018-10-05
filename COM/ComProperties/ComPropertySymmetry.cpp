#include<Windows.h>
#include<stdio.h>
#include"ClassFactoryDllServerWithRegFile.h"

ISum *pISum1 = NULL;
ISum *pISum2 = NULL;
ISubtract *pISubtract = NULL;

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

	pISum1->QueryInterface(IID_ISubtract, (void **)&pISubtract);
	pISubtract->QueryInterface(IID_ISum, (void **)&pISum2);


	printf("Going to verify symmetry property ...\n");
	
	int r1, r2;

	pISum1->SumOfTwoIntegers(1, 2, &r1);
	pISum2->SumOfTwoIntegers(1, 2, &r2);

	if ( r1== r2)
		printf("symmertry proved\n");
	else
		printf("symmertry failed\n");

	pISum1->Release();
	pISum2->Release();
	pISubtract->Release();

	return (0);
}
