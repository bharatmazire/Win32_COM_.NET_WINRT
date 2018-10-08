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

// {E192C26E-C964-4613-9069-0CF521E353CC}
const CLSID CLSID_MultiplicationDivision = { 0xe192c26e, 0xc964, 0x4613, 0x90, 0x69, 0xc, 0xf5, 0x21, 0xe3, 0x53, 0xcc };


// {9C6C9FE8-A61A-4700-A9A0-F81788FDD270}
const IID IID_IMultiplication = { 0x9c6c9fe8, 0xa61a, 0x4700, 0xa9, 0xa0, 0xf8, 0x17, 0x88, 0xfd, 0xd2, 0x70 };

// {04970151-3455-4225-AEF0-64421E154AB7}
const IID IID_IDivision = { 0x4970151, 0x3455, 0x4225, 0xae, 0xf0, 0x64, 0x42, 0x1e, 0x15, 0x4a, 0xb7 };

