class IMyMath : public IDispatch
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

// {8FD1609B-35AF-4E51-9D6B-B8F17998AF3A}

// {42F63C60-8DDD-45DA-B7B8-1F9221651929}
const CLSID CLSID_MyMath = { 0x42f63c60, 0x8ddd, 0x45da, 0xb7, 0xb8, 0x1f, 0x92, 0x21, 0x65, 0x19, 0x29 };

// {27583FD0-2EED-4A94-BAF5-26E288B9D729}

// {0AE437A3-729B-4DB5-8B6F-1FB5CEC76927}
const IID IID_IMyMath = { 0xae437a3, 0x729b, 0x4db5, 0x8b, 0x6f, 0x1f, 0xb5, 0xce, 0xc7, 0x69, 0x27 };
