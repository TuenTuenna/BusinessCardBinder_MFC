//UpdatingForm.h

#ifndef _UPDATINGFORM_H
#define _UPDATINGFORM_H
#include <afxwin.h>
#include "resource.h"

class BusinessCardBinder;
class BusinessCard;
class IndexBinder;
class UpdatingForm :public CDialog {
public:
	enum {IDD=IDD_UPDATINGFORM};
public:
	UpdatingForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
public:
	BusinessCardBinder *businessCardBinder;
	IndexBinder *indexBinder;
public:
	void Load();
	void Save();
	void Insert(BusinessCard *businessCard);
	void Delete(BusinessCard *businessCard);
	CString GetCode();
	CString GetCompanyCode();
protected:
	afx_msg void OnPutButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnDrawButtonClicked();
	afx_msg void OnArrangeButtonClicked();
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnTreeControlItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif // _UPDATINGFORM_H