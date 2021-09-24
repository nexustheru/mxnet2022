#include "includes.h"
using namespace std;

#define GrannyExport_CLASS_ID Class_ID(0x3a575310, 0x3877003d)

class GrannyExport :public SceneExport
{
public:
	const wchar_t* AuthorName() { return _T("Apple"); }
	const wchar_t* Ext(int n) { return _T("Gr2"); }
	const wchar_t* LongDesc() { return _T("GrannyExport for granny files"); }
	const wchar_t* ShortDesc() { return _T("GrannyImport"); }
	const wchar_t* CopyrightMessage() { return _T(""); }
	const wchar_t* OtherMessage1() { return _T(""); }
	const wchar_t* OtherMessage2() { return _T(""); }
	unsigned Version() { return 1; }
	void ShowAbout(HWND hWnd){}
	int DoExport(const wchar_t* name, ExpInterface* ei, Interface* i, BOOL suppressPrompts, DWORD options) override;
	int ExtCount() { return 1; } 
};
int GrannyExport::DoExport(const wchar_t* name, ExpInterface* ei, Interface* i, BOOL suppressPrompts, DWORD options)
{
	bool ok = true;
	try
	{
		return 1;
	}
	catch (const std::exception&)
	{
		return  0;
	}

};

class GrannyExportClassDesc : public ClassDesc2
{
public:
	virtual int IsPublic() { return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) { return new GrannyExport(); }
	virtual const TCHAR* ClassName() { return _T("GrannyExport"); }
	virtual SClass_ID SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() { return GrannyExport_CLASS_ID; }
	virtual const TCHAR* Category() { return _T("GrannyExporter"); }

	virtual const TCHAR* InternalName() { return _T("GrannyExporter"); }
	virtual HINSTANCE HInstance() { return hInstance; }
	const wchar_t* NonLocalizedClassName() { return (wchar_t*)"GrannyExport"; }
};
ClassDesc2* GetGrannyExportDesc()
{
	static GrannyExportClassDesc GrannyExportDesc;
	return &GrannyExportDesc;
}