// RESOURCES

#define MYICON 100



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


