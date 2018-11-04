class ISide : public IUnknown
{
public:
	virtual HRESULT __stdcall SidesOfTriangle(double, double, double, double, double, double, int*) = 0;
};

class IAngle : public IUnknown
{
public:
	virtual HRESULT __stdcall AngleOfTriangle(double, double, double, int *) = 0;
};


// {9EF21993-038B-4CDD-89CA-AC89B2AF1C3E}
const CLSID CLSID_SideAngle = { 0x9ef21993, 0x38b, 0x4cdd, 0x89, 0xca, 0xac, 0x89, 0xb2, 0xaf, 0x1c, 0x3e };

// {9435074F-DAA1-433C-ABCE-C2F75CEF334F}
const IID IID_ISide = { 0x9435074f, 0xdaa1, 0x433c, 0xab, 0xce, 0xc2, 0xf7, 0x5c, 0xef, 0x33, 0x4f };

// {428FB583-7004-48FD-A655-E508F23DC269}
const IID IID_IAngle = { 0x428fb583, 0x7004, 0x48fd, 0xa6, 0x55, 0xe5, 0x8, 0xf2, 0x3d, 0xc2, 0x69 };

