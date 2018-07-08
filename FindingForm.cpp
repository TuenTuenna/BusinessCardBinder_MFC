// FindingForm.cpp

#include"FindingForm.h"
#include"UpdatingForm.h"
#include"BusinessCardBinder.h"
#include "IndexBinder.h"
#include<afxcmn.h>

BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, OnSelectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnLastButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// ������
FindingForm::FindingForm(CWnd *parent)
	:CDialog(FindingForm::IDD, parent) {
	this->count = 0;
	this->current = 0;
}

//1. ã�� ��ư�� Ŭ������ ��
void FindingForm::OnFindButtonClicked() {

	//1.1 ������ �д´�.
	CString name;
	(this->GetDlgItem(IDC_EDIT_PERSONAL_NAME))->GetWindowText(name);

	//1.2 ����ö �����츦 ã�´�.
	UpdatingForm *updatingForm = (UpdatingForm*)CWnd::FindWindow("#32770", "����ö");

	//1.3 ����ö �������� ����ö���� ã�´�.
	if (this->indexes != NULL) {
		delete[] indexes;
		indexes = NULL;
	}
	updatingForm->businessCardBinder->Find((LPCTSTR)name, &indexes, &count);

	//1.4 ã�������� ������ ù��° ������ ����Ѵ�.
	if (count > 0) {
		current = 0;
		(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText((indexes[current]->GetName()).c_str());
		(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText((indexes[current]->GetPosition()).c_str());
		(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText((indexes[current]->GetCellphoneNumber()).c_str());
		(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText((indexes[current]->GetEmailAddress()).c_str());
		(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText((indexes[current]->GetCompanyName()).c_str());
		(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText((indexes[current]->GetAddress()).c_str());
		(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText((indexes[current]->GetTelephoneNumber()).c_str());
		(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText((indexes[current]->GetFaxNumber()).c_str());
		(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText((indexes[current]->GetUrl()).c_str());
	}
	else {
		(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText("");
	}
}


//2. �����ϱ� ��ư�� Ŭ������ ��
void FindingForm::OnSelectButtonClicked() {

	//2.1 ������ ��ġ�� �д´�.
	//2.2 ����ö �����츦 ã�´�.
	UpdatingForm *updatingForm = (UpdatingForm*)CWnd::FindWindow("#32770", "����ö");

	//2.3 ����ö �������� ����ö���� Ư�� �������� �̵��Ѵ�.
	BusinessCard *index = updatingForm->businessCardBinder->Move(indexes[current]);

	//2.4 ����ö �������� ����ö���� ��������� ������ ã�´�.
	CString companyName = ((CString)index->GetCompanyName().c_str());
	Index *indexLink = updatingForm->indexBinder->Find((LPCTSTR)companyName);

	//2.5 ����ö �������� ���ο��� ��������� ��ġ�� ã�´�.
	Long subscript = indexLink->Find(this->indexes[current]);

	//2.6 ã�� ������ ��ȣ�� TreeControl���� ��ȣ��带 ã�´�.
	HTREEITEM root = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
	HTREEITEM parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);
	CString comparison = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);

	while (comparison.Compare(companyName) != 0) {
		parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
		comparison = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	}

	//2.7 ã�� ��ȣ��忡�� ã�� ��ġ��°�� �ڽĳ�带 �̵��Ѵ�.
	HTREEITEM child = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);
	Long i = 0;
	while (i < subscript) {
		child = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
		i++;
	}

	//2.8 ����ö �����쿡�� �ش� ��带 ��ũ�Ѵ�
	((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->Expand(root, TVE_EXPAND);
	((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->Expand(parent, TVE_EXPAND);

	((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);

	//2.9 ����ö �������� ���Կ� ����Ѵ�.
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText((index->GetName()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText((index->GetPosition()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText((index->GetCellphoneNumber()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText((index->GetEmailAddress()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText((index->GetCompanyName()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText((index->GetAddress()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText((index->GetTelephoneNumber()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText((index->GetFaxNumber()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText((index->GetUrl()).c_str());

	// 2.10 �����츦 �ݴ´�.
	if (indexes != NULL) {
		delete[] indexes;
		indexes = NULL;
	}
	this->EndDialog(0);
}

//3. ��ó�� ��ư�� Ŭ������ ��
void FindingForm::OnFirstButtonClicked() {

	//3.1 ã�� ���Ե鿡�� �� ó�� �������� �̵��Ѵ�.
	current = 0;

	//3.2 ��ó�� ������ ����Ѵ�.
	if (this->count > 0) {
		(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText((indexes[current]->GetName()).c_str());
		(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText((indexes[current]->GetPosition()).c_str());
		(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText((indexes[current]->GetCellphoneNumber()).c_str());
		(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText((indexes[current]->GetEmailAddress()).c_str());
		(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText((indexes[current]->GetCompanyName()).c_str());
		(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText((indexes[current]->GetAddress()).c_str());
		(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText((indexes[current]->GetTelephoneNumber()).c_str());
		(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText((indexes[current]->GetFaxNumber()).c_str());
		(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText((indexes[current]->GetUrl()).c_str());
	}
	else {
		(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText("");
		(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText("");
	}
}

//4. ���� ��ư�� Ŭ������ ��
void FindingForm::OnPreviousButtonClicked() {

	//4.1 ã�� ���Ե鿡�� ������������ �̵��Ѵ�.
	current--;

	if (current < 0) {
		current = 0;
	}
	//4.2 ���� ������ ����Ѵ�.
	(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText((indexes[current]->GetName()).c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText((indexes[current]->GetPosition()).c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText((indexes[current]->GetCellphoneNumber()).c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText((indexes[current]->GetEmailAddress()).c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText((indexes[current]->GetCompanyName()).c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText((indexes[current]->GetAddress()).c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText((indexes[current]->GetTelephoneNumber()).c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText((indexes[current]->GetFaxNumber()).c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText((indexes[current]->GetUrl()).c_str());
}

//5. ���� ��ư�� Ŭ������ ��
void FindingForm::OnNextButtonClicked() {

	//5.1 ã�� ���Ե鿡�� ���� �������� �̵��Ѵ�.
	current++;

	if (current >= count ) {
		current = count - 1;
	}

	//5.2 ���� ������ ����Ѵ�.
	(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText((indexes[current]->GetName()).c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText((indexes[current]->GetPosition()).c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText((indexes[current]->GetCellphoneNumber()).c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText((indexes[current]->GetEmailAddress()).c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText((indexes[current]->GetCompanyName()).c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText((indexes[current]->GetAddress()).c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText((indexes[current]->GetTelephoneNumber()).c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText((indexes[current]->GetFaxNumber()).c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText((indexes[current]->GetUrl()).c_str());
}

//6. �ǳ� ��ư�� Ŭ������ ��
void FindingForm::OnLastButtonClicked() {

	//6.1 ã�� ���Ե� �߿��� ������ �������� �̵��Ѵ�.
	current = count - 1;

	//6.2 ������ ������ ����Ѵ�.
	(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText((indexes[current]->GetName()).c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText((indexes[current]->GetPosition()).c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText((indexes[current]->GetCellphoneNumber()).c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText((indexes[current]->GetEmailAddress()).c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText((indexes[current]->GetCompanyName()).c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText((indexes[current]->GetAddress()).c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText((indexes[current]->GetTelephoneNumber()).c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText((indexes[current]->GetFaxNumber()).c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText((indexes[current]->GetUrl()).c_str());
}

//7. �ݱ��ư�� Ŭ������ ��
void FindingForm::OnClose() {

	// 7.1 �����츦 �ݴ´�.
	if (indexes != NULL) {
		delete[] indexes;
		indexes = NULL;
	}
	this->EndDialog(0);
}