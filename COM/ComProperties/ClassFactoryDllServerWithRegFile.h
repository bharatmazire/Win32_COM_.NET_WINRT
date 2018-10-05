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


// {C69F24AD-B0DC-49B8-B7EF-6C1C40E4D759}
const CLSID CLSID_SumSubtract = { 0xc69f24ad, 0xb0dc, 0x49b8, 0xb7, 0xef, 0x6c, 0x1c, 0x40, 0xe4, 0xd7, 0x59 };

// {B2100560-2CB9-4CC3-A006-1BCCB865F9B7}
const IID IID_ISum = { 0xb2100560, 0x2cb9, 0x4cc3, 0xa0, 0x6, 0x1b, 0xcc, 0xb8, 0x65, 0xf9, 0xb7 };

// {203639D4-307B-4BBA-8E00-475A5E2F56D4}
const IID IID_ISubtract = { 0x203639d4, 0x307b, 0x4bba, 0x8e, 0x0, 0x47, 0x5a, 0x5e, 0x2f, 0x56, 0xd4 };

