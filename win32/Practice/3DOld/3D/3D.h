// RESOURCES

#define MYICON 100

//
#define DATAENTRY 101
#define DATAENTRY1 102
#define IDSUBMIT 103

#define IDRESET 104
#define ID_ETALNUM 105
#define IDSUBMIT1 106

#define ID_LISTBOX 107
//


// Constants

#define PI 3.14159265358979323846



#define XAXIS 1

#define YAXIS 2

#define ZAXIS 3



// Types

typedef struct tagPOINTEX {

	double x;

	double y;

	double z;

} POINTEX, *LPPOINTEX;



typedef struct tagLINE {

	LPPOINTEX ptStart;

	LPPOINTEX ptEnd;

} LINE, *LPLINE;



typedef struct tagCAMERA {

	int xAngle;

	int yAngle;

	int zAngle;

	int iScale;

} CAMERA, *LPCAMERA;



typedef struct tagMODEL {

	int iNoOfPoints;

	int iNoOfLines;

	LINE arrLine[5000];

} MODEL, *LPMODEL;



typedef struct tagSTATE {

	BOOL fAxis;

	int iAnimate;

	int Offset[2];

	int Origin[2];

	int Directions[3];

	HWND hwnd;

	MODEL Model;

	CAMERA Camera;

	POINTEX Points[1000];

} STATE, *LPSTATE;


