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

// {4FAF8755-DD32-4A0C-98FC-FDE7BC2F7462}
const CLSID CLSID_SumSubtract = { 0x4faf8755, 0xdd32, 0x4a0c, 0x98, 0xfc, 0xfd, 0xe7, 0xbc, 0x2f, 0x74, 0x62 };


// {79EB8D9D-B119-40C3-895D-5F8E0FC8FA1A}
const IID IID_ISum = { 0x79eb8d9d, 0xb119, 0x40c3, 0x89, 0x5d, 0x5f, 0x8e, 0xf, 0xc8, 0xfa, 0x1a };


// {D7894427-749F-4381-96B6-71E4B3ADD282}
const IID IID_ISubtract = { 0xd7894427, 0x749f, 0x4381, 0x96, 0xb6, 0x71, 0xe4, 0xb3, 0xad, 0xd2, 0x82 };

// {9C6C9FE8-A61A-4700-A9A0-F81788FDD270}
const IID IID_IMultiplication = { 0x9c6c9fe8, 0xa61a, 0x4700, 0xa9, 0xa0, 0xf8, 0x17, 0x88, 0xfd, 0xd2, 0x70 };

// {04970151-3455-4225-AEF0-64421E154AB7}
const IID IID_IDivision = { 0x4970151, 0x3455, 0x4225, 0xae, 0xf0, 0x64, 0x42, 0x1e, 0x15, 0x4a, 0xb7 };

