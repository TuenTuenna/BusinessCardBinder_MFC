//DrawingForm.h

#ifndef _DRAWINGFORM_H
#define _DRAWINGFORM_H
#include <afxwin.h>
#include "resource.h"

class DrawingForm :public CDialog {
public:
	enum { IDD = IDD_DRAWINGFORM };
public:
	DrawingForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
protected:
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif // _DRAWINGFORM_H