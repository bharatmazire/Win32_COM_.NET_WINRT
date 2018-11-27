#include<windows.h>
#include<stdio.h>
#include"ChemistryServerLoader.h"

int main()
{
	static HMODULE hLibChem = NULL;
	hLibChem = LoadLibrary(TEXT("ChemistryServerLoader.dll"));
	if (hLibChem == NULL)
	{
		printf("Error \n Chemistry Dll loading falis\n");
		return (0);
	}

	typedef HRESULT(*pfnChemistryCalculation) (int, double, double, double*); // i guess here return type should be int, instead of HRESULT
	static pfnChemistryCalculation pfnChem = NULL;

	pfnChem = (pfnChemistryCalculation)GetProcAddress(hLibChem, "ChemistryCalculation");
	if (pfnChem == NULL)
	{
		printf("pfnChemistryCalculation LOADING FAILS !!");
	}
	double ret;
	pfnChem(1, 100, 200, &ret);
	printf("RESULT Is %f", ret);


	FreeLibrary(hLibChem);
	return (0);
}
