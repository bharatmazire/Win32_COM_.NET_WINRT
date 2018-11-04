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

extern "C" double WeightCalculator(double dMass, double iGravity)
{
	double dWeight;
	dWeight = dMass * iGravity;
	return dWeight;
}
