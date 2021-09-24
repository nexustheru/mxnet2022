#include "includes.h"
#include "Importer.h"
using namespace std;

#define GrannyImport_CLASS_ID Class_ID(0x2d4307f0, 0x44dc1e34)
class GrannyImport : public SceneImport
{
public:

	int			 ExtCount() { return 1; };
	const TCHAR* Ext(int n) { return _T("Gr2"); };
	const TCHAR* LongDesc() { return _T("Granny Importer,imports granny files"); };
	const TCHAR* ShortDesc() { return _T("Granny Importer"); };
	const TCHAR* AuthorName() { return _T("ApplesPie"); };
	const TCHAR* CopyrightMessage() { return _T("Free"); };
	const TCHAR* OtherMessage1() { return _T(""); };
	const TCHAR* OtherMessage2() { return _T(""); };
	unsigned int Version() { return 1; };
	void	     ShowAbout(HWND hWnd) {};
	int			 DoImport(const TCHAR* filename, ImpInterface* i, Interface* gi, BOOL suppressPrompts);

	//Constructor/Destructor
	GrannyImport() {};
	~GrannyImport() {};

};

int GrannyImport::DoImport(const TCHAR* filename, ImpInterface* i, Interface* gi, BOOL suppressPrompts)
{
	try
	{
	Importer* qmod = new Importer();
	ImpNode* impnode = i->CreateNode();
	std::wstring arr_w(filename);
	std::string arr_s(arr_w.begin(), arr_w.end());
	qmod->setmaxlobals(i, gi, impnode);
	qmod->setGlobals(&arr_s);

	return TRUE;
	}
	catch(exception* ex)
	{
		MessageBoxA(NULL, ex->what(), "Import Error", MB_OK);
		return FALSE;
	}	
	
};

class GrannyImportClassDesc : public ClassDesc2
{
public:
	virtual int IsPublic() { return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) { return new GrannyImport(); }
	virtual const TCHAR* ClassName() { return _T("GrannyImport"); }
	virtual SClass_ID SuperClassID() { return SCENE_IMPORT_CLASS_ID; }
	virtual Class_ID ClassID() { return GrannyImport_CLASS_ID; }
	virtual const TCHAR* Category() { return _T("GrannyImporter");}

	virtual const TCHAR* InternalName() { return _T("GrannyImport"); }	
	virtual HINSTANCE HInstance() { return hInstance; }					
	const wchar_t* NonLocalizedClassName() { return (wchar_t*)"GrannyImport"; }
};
ClassDesc2* GetGrannyImportDesc()
{
	static GrannyImportClassDesc GrannyImportDesc;
	return &GrannyImportDesc;
}