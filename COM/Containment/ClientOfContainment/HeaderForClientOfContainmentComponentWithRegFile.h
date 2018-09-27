class ISum : public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract : public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;
};

class IMultiplication : public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *) = 0;
};

class IDivision : public IUnknown
{
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *) = 0;
};


// {B8371E09-A61B-48BC-9B93-9AB27D33C393}
const CLSID CLSID_SumSubtract = { 0xb8371e09, 0xa61b, 0x48bc, 0x9b, 0x93, 0x9a, 0xb2, 0x7d, 0x33, 0xc3, 0x93 };

// {3C8EBD0D-3D27-4291-9B99-2E4DFFDCD7D1}
const IID IID_ISum = { 0x3c8ebd0d, 0x3d27, 0x4291, 0x9b, 0x99, 0x2e, 0x4d, 0xff, 0xdc, 0xd7, 0xd1 };

// {3FC23EF3-53DA-4449-8957-25874237CA19}
const IID IID_ISubtract = { 0x3fc23ef3, 0x53da, 0x4449, 0x89, 0x57, 0x25, 0x87, 0x42, 0x37, 0xca, 0x19 };

// {C5D34B33-ADC6-46B4-9D96-5C36657F8764}
const IID IID_IMultiplication = { 0xc5d34b33, 0xadc6, 0x46b4, 0x9d, 0x96, 0x5c, 0x36, 0x65, 0x7f, 0x87, 0x64 };

// {53C38DAA-9C53-4FCC-8EF0-46BEFF944D69}
const IID IID_IDivision = { 0x53c38daa, 0x9c53, 0x4fcc, 0x8e, 0xf0, 0x46, 0xbe, 0xff, 0x94, 0x4d, 0x69 };

