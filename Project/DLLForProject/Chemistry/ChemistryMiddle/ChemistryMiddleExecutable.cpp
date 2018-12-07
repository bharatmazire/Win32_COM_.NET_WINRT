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

	/*typedef void(*pfnComIn)();
	static pfnComIn pfnIn = NULL;

	typedef void(*pfnComUn)();
	static pfnComUn pfnUn = NULL;*/

	typedef HRESULT(*pfnChemistryCalculation) (int, double, double, double*); // i guess here return type should be int, instead of HRESULT
	static pfnChemistryCalculation pfnChem = NULL;

	//pfnIn = (pfnComIn)GetProcAddress(hLibChem, "ComInitialize");
	//if (pfnIn == NULL)
	//{
	//	printf("Com Initialization LOADING FAILS !!");
	//}

	pfnChem = (pfnChemistryCalculation)GetProcAddress(hLibChem, "ChemistryCalculation");
	if (pfnChem == NULL)
	{
		printf("pfnChemistryCalculation LOADING FAILS !!");
	}
	double ret;
	pfnChem(1, 100, 200, &ret);
	printf("RESULT Is %f", ret);

	/*pfnUn = (pfnComUn)GetProcAddress(hLibChem, "ComUninitialize");
	if (pfnUn == NULL)
	{
		printf("Com uninitialization LOADING FAILS !!");
	}*/
	FreeLibrary(hLibChem);
	return (0);
}
