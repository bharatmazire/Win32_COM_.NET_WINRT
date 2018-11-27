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

// {5D349A8F-AE19-4F92-8D87-406B0032AE45}
const CLSID CLSID_SumSubtract = { 0x5d349a8f, 0xae19, 0x4f92, 0x8d, 0x87, 0x40, 0x6b, 0x0, 0x32, 0xae, 0x45 };

// {722368AB-D500-432F-92C6-BA44D57C0FA2}
const IID IID_ISum = { 0x722368ab, 0xd500, 0x432f, 0x92, 0xc6, 0xba, 0x44, 0xd5, 0x7c, 0xf, 0xa2 };

// {AB7DCBF9-0A26-46E9-BDB3-5CE8809BBDA0}
const IID IID_ISubtract = { 0xab7dcbf9, 0xa26, 0x46e9, 0xbd, 0xb3, 0x5c, 0xe8, 0x80, 0x9b, 0xbd, 0xa0 };

