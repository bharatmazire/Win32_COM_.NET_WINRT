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


// {4FAF8755-DD32-4A0C-98FC-FDE7BC2F7462}
const CLSID CLSID_SumSubtract = { 0x4faf8755, 0xdd32, 0x4a0c, 0x98, 0xfc, 0xfd, 0xe7, 0xbc, 0x2f, 0x74, 0x62 };


// {79EB8D9D-B119-40C3-895D-5F8E0FC8FA1A}
const IID IID_ISum = { 0x79eb8d9d, 0xb119, 0x40c3, 0x89, 0x5d, 0x5f, 0x8e, 0xf, 0xc8, 0xfa, 0x1a };


// {D7894427-749F-4381-96B6-71E4B3ADD282}
const IID IID_ISubtract = { 0xd7894427, 0x749f, 0x4381, 0x96, 0xb6, 0x71, 0xe4, 0xb3, 0xad, 0xd2, 0x82 };

