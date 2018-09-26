#include<windows.h>
#include"PhysicsDll.h"

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

extern "C" int WeightCalculator(int iMass, int iPlanate)
{
	int iWeight;
	switch (iPlanate)
	{
	case 1:
		iWeight = iMass * 274;
		break;
	case 2:
		iWeight = iMass * 24.92;
		break;
	case 3:
		iWeight = iMass * 11.15;
		break;
	case 4:
		iWeight = iMass * 10.44;
		break;
	case 5:
		iWeight = iMass * 9.798;
		break;
	case 6:
		iWeight = iMass * 8.87;
		break;
	case 7:
		iWeight = iMass * 8.87;
		break;
	case 8:
		iWeight = iMass * 3.71;
		break;
	case 9:
		iWeight = iMass * 3.7;
		break;
	case 10:
		iWeight = iMass * 1.68;
		break;
	case 11:
		iWeight = iMass * 0.58;
		break;
	default:
		iWeight = iMass * 9.798;
		break;
	}
	return iWeight;
}
