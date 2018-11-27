class IChemCalculation : public IUnknown
{
public:
	virtual HRESULT __stdcall ChemistryCalculation(int, double, double, double *) = 0;
};

// {4023D09A-7FD7-4142-B73D-FD0878B3F3C2}
const CLSID CLSID_Chemistry = { 0x4023d09a, 0x7fd7, 0x4142, 0xb7, 0x3d, 0xfd, 0x8, 0x78, 0xb3, 0xf3, 0xc2 };


// {9AD45A65-0CFC-4E7B-B6F8-F0245C74C396}
const IID IID_IChemCalculation = { 0x9ad45a65, 0xcfc, 0x4e7b, 0xb6, 0xf8, 0xf0, 0x24, 0x5c, 0x74, 0xc3, 0x96 };

