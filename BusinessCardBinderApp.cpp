#include "BusinessCardBinderApp.h"
#include "UpdatingForm.h"

BOOL BusinessCardBinderApp::InitInstance()
{
	UpdatingForm updatingForm;
	this->m_pMainWnd = &updatingForm;
	updatingForm.DoModal();

	return TRUE;
}

BusinessCardBinderApp bussinessCardBinderApp;