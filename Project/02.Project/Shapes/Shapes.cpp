#include<windows.h>
#include"3D.h"


BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
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
	return TRUE;
}

extern "C" void Cube(LPSTATE State)

{
	State->Points[0] = POINTEX({ -1, -1, -1 });
	State->Points[1] = POINTEX({ -1, -1,  1 });
	State->Points[2] = POINTEX({ -1,  1, -1 });
	State->Points[3] = POINTEX({ -1,  1,  1 });
	State->Points[4] = POINTEX({ 1, -1, -1 });
	State->Points[5] = POINTEX({ 1, -1,  1 });
	State->Points[6] = POINTEX({ 1,  1, -1 });
	State->Points[7] = POINTEX({ 1,  1,  1 });


	State->Model.arrLine[0].ptStart = &State->Points[0];
	State->Model.arrLine[0].ptEnd = &State->Points[1];

	State->Model.arrLine[1].ptStart = &State->Points[1];
	State->Model.arrLine[1].ptEnd = &State->Points[5];

	State->Model.arrLine[2].ptStart = &State->Points[5];
	State->Model.arrLine[2].ptEnd = &State->Points[4];

	State->Model.arrLine[3].ptStart = &State->Points[4];
	State->Model.arrLine[3].ptEnd = &State->Points[0];

	State->Model.arrLine[4].ptStart = &State->Points[2];
	State->Model.arrLine[4].ptEnd = &State->Points[3];

	State->Model.arrLine[5].ptStart = &State->Points[3];
	State->Model.arrLine[5].ptEnd = &State->Points[7];

	State->Model.arrLine[6].ptStart = &State->Points[7];
	State->Model.arrLine[6].ptEnd = &State->Points[6];

	State->Model.arrLine[7].ptStart = &State->Points[6];
	State->Model.arrLine[7].ptEnd = &State->Points[2];

	State->Model.arrLine[8].ptStart = &State->Points[2];
	State->Model.arrLine[8].ptEnd = &State->Points[0];

	State->Model.arrLine[9].ptStart = &State->Points[3];
	State->Model.arrLine[9].ptEnd = &State->Points[1];

	State->Model.arrLine[10].ptStart = &State->Points[7];
	State->Model.arrLine[10].ptEnd = &State->Points[5];

	State->Model.arrLine[11].ptStart = &State->Points[6];
	State->Model.arrLine[11].ptEnd = &State->Points[4];

	State->Model.iNoOfPoints = 8;
	State->Model.iNoOfLines = 12;
}

extern "C" void ThreeCubes(LPSTATE State)
{

	POINTEX ptA, ptB, ptC, ptD, ptE, ptF, ptG, ptH;
	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			ptA = { -1, -1, -1 };
			ptB = { -1, -1,  1 };
			ptC = { -1,  1, -1 };
			ptD = { -1,  1,  1 };
			ptE = { 1, -1, -1 };
			ptF = { 1, -1,  1 };
			ptG = { 1,  1, -1 };
			ptH = { 1,  1,  1 };
			break;
		case 1:
			ptA = { -1 + 2, -1 + 2, -1 + 2 };
			ptB = { -1 + 2, -1 + 2,  1 + 2 };
			ptC = { -1 + 2,  1 + 2, -1 + 2 };
			ptD = { -1 + 2,  1 + 2,  1 + 2 };
			ptE = { 1 + 2, -1 + 2, -1 + 2 };
			ptF = { 1 + 2, -1 + 2,  1 + 2 };
			ptG = { 1 + 2,  1 + 2, -1 + 2 };
			ptH = { 1 + 2,  1 + 2,  1 + 2 };
			break;
		case 2:
			ptA = { -1 - 2, -1 - 2, -1 - 2 };
			ptB = { -1 - 2, -1 - 2,  1 - 2 };
			ptC = { -1 - 2,  1 - 2, -1 - 2 };
			ptD = { -1 - 2,  1 - 2,  1 - 2 };
			ptE = { 1 - 2, -1 - 2, -1 - 2 };
			ptF = { 1 - 2, -1 - 2,  1 - 2 };
			ptG = { 1 - 2,  1 - 2, -1 - 2 };
			ptH = { 1 - 2,  1 - 2,  1 - 2 };
			break;
		}

		State->Points[0 + (i * 8)] = ptA;
		State->Points[1 + (i * 8)] = ptB;
		State->Points[2 + (i * 8)] = ptC;
		State->Points[3 + (i * 8)] = ptD;
		State->Points[4 + (i * 8)] = ptE;
		State->Points[5 + (i * 8)] = ptF;
		State->Points[6 + (i * 8)] = ptG;
		State->Points[7 + (i * 8)] = ptH;

		State->Model.arrLine[0 + (i * 12)].ptStart = &State->Points[0 + (i * 8)];
		State->Model.arrLine[0 + (i * 12)].ptEnd = &State->Points[1 + (i * 8)];

		State->Model.arrLine[1 + (i * 12)].ptStart = &State->Points[1 + (i * 8)];
		State->Model.arrLine[1 + (i * 12)].ptEnd = &State->Points[5 + (i * 8)];

		State->Model.arrLine[2 + (i * 12)].ptStart = &State->Points[5 + (i * 8)];
		State->Model.arrLine[2 + (i * 12)].ptEnd = &State->Points[4 + (i * 8)];

		State->Model.arrLine[3 + (i * 12)].ptStart = &State->Points[4 + (i * 8)];
		State->Model.arrLine[3 + (i * 12)].ptEnd = &State->Points[0 + (i * 8)];

		State->Model.arrLine[4 + (i * 12)].ptStart = &State->Points[2 + (i * 8)];
		State->Model.arrLine[4 + (i * 12)].ptEnd = &State->Points[3 + (i * 8)];

		State->Model.arrLine[5 + (i * 12)].ptStart = &State->Points[3 + (i * 8)];
		State->Model.arrLine[5 + (i * 12)].ptEnd = &State->Points[7 + (i * 8)];

		State->Model.arrLine[6 + (i * 12)].ptStart = &State->Points[7 + (i * 8)];
		State->Model.arrLine[6 + (i * 12)].ptEnd = &State->Points[6 + (i * 8)];

		State->Model.arrLine[7 + (i * 12)].ptStart = &State->Points[6 + (i * 8)];
		State->Model.arrLine[7 + (i * 12)].ptEnd = &State->Points[2 + (i * 8)];

		State->Model.arrLine[8 + (i * 12)].ptStart = &State->Points[2 + (i * 8)];
		State->Model.arrLine[8 + (i * 12)].ptEnd = &State->Points[0 + (i * 8)];

		State->Model.arrLine[9 + (i * 12)].ptStart = &State->Points[3 + (i * 8)];
		State->Model.arrLine[9 + (i * 12)].ptEnd = &State->Points[1 + (i * 8)];

		State->Model.arrLine[10 + (i * 12)].ptStart = &State->Points[7 + (i * 8)];
		State->Model.arrLine[10 + (i * 12)].ptEnd = &State->Points[5 + (i * 8)];

		State->Model.arrLine[11 + (i * 12)].ptStart = &State->Points[6 + (i * 8)];
		State->Model.arrLine[11 + (i * 12)].ptEnd = &State->Points[4 + (i * 8)];
	}

	State->Model.iNoOfPoints = 24;
	State->Model.iNoOfLines = 36;
}

extern "C" void FiveAngleStar(LPSTATE State)
{

	State->Points[0] = POINTEX({ 0, 15, 0 });

	State->Points[1] = POINTEX({ 15, 5, 0 });

	State->Points[2] = POINTEX({ 8, -12, 0 });

	State->Points[3] = POINTEX({ -8, -12, 0 });

	State->Points[4] = POINTEX({ -15, 5, 0 });



	State->Points[5] = POINTEX({ 3,5, 3 });

	State->Points[6] = POINTEX({ 3,5, -3 });



	State->Points[7] = POINTEX({ 5,-3, 3 });

	State->Points[8] = POINTEX({ 5,-3, -3 });



	State->Points[9] = POINTEX({ 0,-6, 3 });

	State->Points[10] = POINTEX({ 0,-6, -3 });



	State->Points[11] = POINTEX({ -5,-3, 3 });

	State->Points[12] = POINTEX({ -5,-3, -3 });



	State->Points[13] = POINTEX({ -3,5, 3 });

	State->Points[14] = POINTEX({ -3,5, -3 });



	// Lines From A Point

	State->Model.arrLine[0].ptStart = &State->Points[0];

	State->Model.arrLine[0].ptEnd = &State->Points[5];



	State->Model.arrLine[1].ptStart = &State->Points[0];

	State->Model.arrLine[1].ptEnd = &State->Points[6];



	State->Model.arrLine[2].ptStart = &State->Points[0];

	State->Model.arrLine[2].ptEnd = &State->Points[13];



	State->Model.arrLine[3].ptStart = &State->Points[0];

	State->Model.arrLine[3].ptEnd = &State->Points[14];



	// Lines From B Point

	State->Model.arrLine[4].ptStart = &State->Points[1];

	State->Model.arrLine[4].ptEnd = &State->Points[5];



	State->Model.arrLine[5].ptStart = &State->Points[1];

	State->Model.arrLine[5].ptEnd = &State->Points[6];



	State->Model.arrLine[6].ptStart = &State->Points[1];

	State->Model.arrLine[6].ptEnd = &State->Points[7];



	State->Model.arrLine[7].ptStart = &State->Points[1];

	State->Model.arrLine[7].ptEnd = &State->Points[8];



	// Lines From C Point

	State->Model.arrLine[8].ptStart = &State->Points[2];

	State->Model.arrLine[8].ptEnd = &State->Points[7];



	State->Model.arrLine[9].ptStart = &State->Points[2];

	State->Model.arrLine[9].ptEnd = &State->Points[8];



	State->Model.arrLine[10].ptStart = &State->Points[2];

	State->Model.arrLine[10].ptEnd = &State->Points[9];



	State->Model.arrLine[11].ptStart = &State->Points[2];

	State->Model.arrLine[11].ptEnd = &State->Points[10];



	// Lines From D Point

	State->Model.arrLine[12].ptStart = &State->Points[3];

	State->Model.arrLine[12].ptEnd = &State->Points[9];



	State->Model.arrLine[13].ptStart = &State->Points[3];

	State->Model.arrLine[13].ptEnd = &State->Points[10];



	State->Model.arrLine[14].ptStart = &State->Points[3];

	State->Model.arrLine[14].ptEnd = &State->Points[11];



	State->Model.arrLine[15].ptStart = &State->Points[3];

	State->Model.arrLine[15].ptEnd = &State->Points[12];



	// Lines From E Point

	State->Model.arrLine[16].ptStart = &State->Points[4];

	State->Model.arrLine[16].ptEnd = &State->Points[11];



	State->Model.arrLine[17].ptStart = &State->Points[4];

	State->Model.arrLine[17].ptEnd = &State->Points[12];



	State->Model.arrLine[18].ptStart = &State->Points[4];

	State->Model.arrLine[18].ptEnd = &State->Points[13];



	State->Model.arrLine[19].ptStart = &State->Points[4];

	State->Model.arrLine[19].ptEnd = &State->Points[14];



	// Upper Face

	State->Model.arrLine[20].ptStart = &State->Points[13];

	State->Model.arrLine[20].ptEnd = &State->Points[5];



	State->Model.arrLine[21].ptStart = &State->Points[5];

	State->Model.arrLine[21].ptEnd = &State->Points[7];



	State->Model.arrLine[22].ptStart = &State->Points[7];

	State->Model.arrLine[22].ptEnd = &State->Points[9];



	State->Model.arrLine[23].ptStart = &State->Points[9];

	State->Model.arrLine[23].ptEnd = &State->Points[11];



	State->Model.arrLine[24].ptStart = &State->Points[11];

	State->Model.arrLine[24].ptEnd = &State->Points[13];



	// Lower Face

	State->Model.arrLine[25].ptStart = &State->Points[14];

	State->Model.arrLine[25].ptEnd = &State->Points[6];



	State->Model.arrLine[26].ptStart = &State->Points[6];

	State->Model.arrLine[26].ptEnd = &State->Points[8];



	State->Model.arrLine[27].ptStart = &State->Points[8];

	State->Model.arrLine[27].ptEnd = &State->Points[10];



	State->Model.arrLine[28].ptStart = &State->Points[10];

	State->Model.arrLine[28].ptEnd = &State->Points[12];



	State->Model.arrLine[29].ptStart = &State->Points[12];

	State->Model.arrLine[29].ptEnd = &State->Points[14];



	// Two Face Connectors

	State->Model.arrLine[30].ptStart = &State->Points[5];

	State->Model.arrLine[30].ptEnd = &State->Points[6];



	State->Model.arrLine[31].ptStart = &State->Points[7];

	State->Model.arrLine[31].ptEnd = &State->Points[8];



	State->Model.arrLine[32].ptStart = &State->Points[9];

	State->Model.arrLine[32].ptEnd = &State->Points[10];



	State->Model.arrLine[33].ptStart = &State->Points[11];

	State->Model.arrLine[33].ptEnd = &State->Points[12];



	State->Model.arrLine[34].ptStart = &State->Points[13];

	State->Model.arrLine[34].ptEnd = &State->Points[14];



	State->Model.iNoOfPoints = 15;

	State->Model.iNoOfLines = 35;



}

extern "C" void Pyramid(LPSTATE State)
{

	State->Points[0] = POINTEX({ 0, 0, 5 });

	State->Points[1] = POINTEX({ 2, 2, 0 });

	State->Points[2] = POINTEX({ 2, -2, 0 });

	State->Points[3] = POINTEX({ -2, -2, 0 });

	State->Points[4] = POINTEX({ -2, 2, 0 });



	State->Model.arrLine[0].ptStart = &State->Points[0];

	State->Model.arrLine[0].ptEnd = &State->Points[1];



	State->Model.arrLine[1].ptStart = &State->Points[0];

	State->Model.arrLine[1].ptEnd = &State->Points[2];



	State->Model.arrLine[2].ptStart = &State->Points[0];

	State->Model.arrLine[2].ptEnd = &State->Points[3];



	State->Model.arrLine[3].ptStart = &State->Points[0];

	State->Model.arrLine[3].ptEnd = &State->Points[4];



	State->Model.arrLine[4].ptStart = &State->Points[1];

	State->Model.arrLine[4].ptEnd = &State->Points[2];



	State->Model.arrLine[5].ptStart = &State->Points[2];

	State->Model.arrLine[5].ptEnd = &State->Points[3];



	State->Model.arrLine[6].ptStart = &State->Points[3];

	State->Model.arrLine[6].ptEnd = &State->Points[4];



	State->Model.arrLine[7].ptStart = &State->Points[4];

	State->Model.arrLine[7].ptEnd = &State->Points[1];



	State->Model.iNoOfPoints = 5;

	State->Model.iNoOfLines = 8;



}

extern "C" void Diamond(LPSTATE State)
{

	State->Points[0] = POINTEX({ 0, 0, 5 });

	State->Points[1] = POINTEX({ 2, 2, 0 });

	State->Points[2] = POINTEX({ 2, -2, 0 });

	State->Points[3] = POINTEX({ -2, -2, 0 });

	State->Points[4] = POINTEX({ -2, 2, 0 });

	State->Points[5] = POINTEX({ 0, 0, -5 });



	State->Model.arrLine[0].ptStart = &State->Points[0];

	State->Model.arrLine[0].ptEnd = &State->Points[1];



	State->Model.arrLine[1].ptStart = &State->Points[0];

	State->Model.arrLine[1].ptEnd = &State->Points[2];



	State->Model.arrLine[2].ptStart = &State->Points[0];

	State->Model.arrLine[2].ptEnd = &State->Points[3];



	State->Model.arrLine[3].ptStart = &State->Points[0];

	State->Model.arrLine[3].ptEnd = &State->Points[4];



	State->Model.arrLine[4].ptStart = &State->Points[1];

	State->Model.arrLine[4].ptEnd = &State->Points[2];



	State->Model.arrLine[5].ptStart = &State->Points[2];

	State->Model.arrLine[5].ptEnd = &State->Points[3];



	State->Model.arrLine[6].ptStart = &State->Points[3];

	State->Model.arrLine[6].ptEnd = &State->Points[4];



	State->Model.arrLine[7].ptStart = &State->Points[4];

	State->Model.arrLine[7].ptEnd = &State->Points[1];



	State->Model.arrLine[8].ptStart = &State->Points[5];

	State->Model.arrLine[8].ptEnd = &State->Points[1];



	State->Model.arrLine[9].ptStart = &State->Points[5];

	State->Model.arrLine[9].ptEnd = &State->Points[2];



	State->Model.arrLine[10].ptStart = &State->Points[5];

	State->Model.arrLine[10].ptEnd = &State->Points[3];



	State->Model.arrLine[11].ptStart = &State->Points[5];

	State->Model.arrLine[11].ptEnd = &State->Points[4];



	State->Model.iNoOfPoints = 6;

	State->Model.iNoOfLines = 12;

}