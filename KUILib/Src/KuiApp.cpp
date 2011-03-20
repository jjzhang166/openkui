#include "StdAfx.h"
#include "..\include\kuiapp.h"

CKuiApp::CKuiApp(void)
{
}

CKuiApp::~CKuiApp(void)
{
}

KUILIB_API void InitUIResource()
{
	KAppRes& appRes = KAppRes::Instance();
	std::string strXml;

	KuiFontPool::SetDefaultFont( _T("ËÎÌו"), -12);

	appRes.GetXmlData("IDR_KSC_SKIN", strXml);
	KuiSkin::LoadSkins(strXml);

	appRes.GetXmlData("IDR_KSC_STYLE", strXml);
	KuiStyle::LoadStyles(strXml);
}

HRESULT CKuiApp::Init(HINSTANCE hInstance)
{
	DWORD dwRet = 1;
	HRESULT hRet;
	CRegKey reg;
	
	hRet = __super::Init(NULL, hInstance);
	if (FAILED(hRet))
		return hRet;
	
	//Get install path
	DWORD dwRet1 = ::GetModuleFileName(NULL, m_strAppFileName.GetBuffer(MAX_PATH + 1), MAX_PATH);
	if (0 == dwRet1)
	{
		m_strAppFileName.ReleaseBuffer(0);

		hRet = E_FAIL;
	}
	else
	{
		m_strAppFileName.ReleaseBuffer();

		m_strAppPath = m_strAppFileName;
		m_strAppPath = m_strAppPath.Left(m_strAppPath.ReverseFind(L'\\'));
	}

    InitUIResource();

	return hRet;
}

VOID CKuiApp::UnInit()
{
}

UINT_PTR CKuiApp::Main()
{
    /*CMessageLoop theLoop;
    CMainWnd mainwnd;

    _Module.AddMessageLoop(&theLoop);

	RECT rt = {0, 0, 600, 470};
	if (mainwnd.Create(::GetActiveWindow(), &rt) == NULL) 
    {
        return 0;
    }

    mainwnd.ShowWindow(SW_SHOW);

    int nRet = theLoop.Run();

    _Module.RemoveMessageLoop();*/
int nRet=0;
    return nRet;
}