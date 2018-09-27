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

// {EE0923BA-B4CA-4013-875C-D2F21485A9C0}
const CLSID CLSID_MultiplicationDivision = { 0xee0923ba, 0xb4ca, 0x4013, 0x87, 0x5c, 0xd2, 0xf2, 0x14, 0x85, 0xa9, 0xc0 };

// {C5D34B33-ADC6-46B4-9D96-5C36657F8764}
const IID IID_IMultiplication = { 0xc5d34b33, 0xadc6, 0x46b4, 0x9d, 0x96, 0x5c, 0x36, 0x65, 0x7f, 0x87, 0x64 };

// {53C38DAA-9C53-4FCC-8EF0-46BEFF944D69}
const IID IID_IDivision = { 0x53c38daa, 0x9c53, 0x4fcc, 0x8e, 0xf0, 0x46, 0xbe, 0xff, 0x94, 0x4d, 0x69 };

