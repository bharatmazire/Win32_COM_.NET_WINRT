#pragma once
class ISum :public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract :public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

// {5D349A8F-AE19-4F92-8D87-406B0032AE45} old

// {CFC4A33F-E1E4-47F0-81BC-EA496E5C99E1}
const CLSID CLSID_SumSubtract = { 0xcfc4a33f, 0xe1e4, 0x47f0, 0x81, 0xbc, 0xea, 0x49, 0x6e, 0x5c, 0x99, 0xe1 };

// {722368AB-D500-432F-92C6-BA44D57C0FA2} old

// {09749A69-D03E-4165-BF6D-5A09EB3FD046}
const IID IID_ISum = { 0x9749a69, 0xd03e, 0x4165, 0xbf, 0x6d, 0x5a, 0x9, 0xeb, 0x3f, 0xd0, 0x46 };

// {AB7DCBF9-0A26-46E9-BDB3-5CE8809BBDA0} old

// {AFD72FA6-4C74-4AF1-97C0-7A8595011597}
const IID IID_ISubtract = { 0xafd72fa6, 0x4c74, 0x4af1, 0x97, 0xc0, 0x7a, 0x85, 0x95, 0x1, 0x15, 0x97 };

