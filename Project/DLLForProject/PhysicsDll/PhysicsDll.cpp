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

extern "C" double WeightCalculator(double dMass, int iPlanate)
{
	double dWeight;
	switch (iPlanate)
	{
	case 1:
		dWeight = dMass * 274;
		break;
	case 2:
		dWeight = dMass * 24.92;
		break;
	case 3:
		dWeight = dMass * 11.15;
		break;
	case 4:
		dWeight = dMass * 10.44;
		break;
	case 5:
		dWeight = dMass * 9.798;
		break;
	case 6:
		dWeight = dMass * 8.87;
		break;
	case 7:
		dWeight = dMass * 8.87;
		break;
	case 8:
		dWeight = dMass * 3.71;
		break;
	case 9:
		dWeight = dMass * 3.7;
		break;
	case 10:
		dWeight = dMass * 1.68;
		break;
	case 11:
		dWeight = dMass * 0.58;
		break;
	default:
		dWeight = dMass * 9.798;
		break;
	}
	return dWeight;
}
