//#include <Windows.h>

class ISum : public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntergers(int, int, int *) = 0;
};

class ISubtract : public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;
};

// {DC8F0D18-1800-40A4-97E5-5E1954EBC48F}
const CLSID CLSID_SumSubtract = { 0xdc8f0d18, 0x1800, 0x40a4, 0x97, 0xe5, 0x5e, 0x19, 0x54, 0xeb, 0xc4, 0x8f };

// {40E04104-5208-4911-B4F0-D73DB1C2D166}
const IID IID_ISum = { 0x40e04104, 0x5208, 0x4911, 0xb4, 0xf0, 0xd7, 0x3d, 0xb1, 0xc2, 0xd1, 0x66 };

// {80EE3C10-9EB2-44B1-BD02-2582A3735DC0}
const IID IID_ISubtract = { 0x80ee3c10, 0x9eb2, 0x44b1, 0xbd, 0x2, 0x25, 0x82, 0xa3, 0x73, 0x5d, 0xc0 };
