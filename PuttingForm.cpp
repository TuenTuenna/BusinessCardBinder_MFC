//PuttingForm.cpp

#include"PuttingForm.h"
#include"UpdatingForm.h"
#include"BusinessCardBinder.h"
#include "IndexBinder.h"
#include<afxcmn.h>

BEGIN_MESSAGE_MAP(PuttingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PUT, OnPutButtonClicked)
	ON_EN_KILLFOCUS(IDC_EDIT_COMPANY_NAME, OnCompanyNameEditKillFocus)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

PuttingForm::PuttingForm(CWnd * parent)
	:CDialog(PuttingForm::IDD, parent) {
}

//1. �����찡 ������ ��
BOOL PuttingForm::OnInitDialog()
{
	CDialog::OnInitDialog();//�ڵ������

							//1.1 ���� �޺��ڽ��� ����� �����.
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_POSITION)))->AddString("ȸ��");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_POSITION)))->AddString("����");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_POSITION)))->AddString("����");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_POSITION)))->AddString("����");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_POSITION)))->AddString("����");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_POSITION)))->AddString("�븮");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_POSITION)))->AddString("���");

	//1.2 �̸����ּ� �޺��ڽ��� ����� �����.
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS)))->AddString("naver.com");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS)))->AddString("nate.com");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS)))->AddString("daum.net");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS)))->AddString("gmail.com");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS)))->AddString("�����Է�");

	return FALSE;
}

//2. ��ȣ����Ʈ�� ��Ŀ���� �Ҿ��� ��
void PuttingForm::OnCompanyNameEditKillFocus() {

	//2.1 ��ȣ�� �д´�.
	CString companyName;
	this->GetDlgItem(IDC_EDIT_COMPANY_NAME)->GetWindowText(companyName);

	//2.2 ����ö �����츦 ã�´�.
	UpdatingForm *updatingForm = (UpdatingForm*)CWnd::FindWindow("#32770", "����ö");

	//2.3 ����ö�������� ����ö���� ��ȣ�� ã�´�.
	BusinessCard* index = updatingForm->businessCardBinder->FindByCompanyNmae((LPCTSTR)companyName);

	//2.4 ������ ������ ȸ�縦 ����Ѵ�.
	if (index != NULL) {
		(this->GetDlgItem(IDC_EDIT_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
		(this->GetDlgItem(IDC_EDIT_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
		(this->GetDlgItem(IDC_EDIT_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
		(this->GetDlgItem(IDC_EDIT_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
		(this->GetDlgItem(IDC_EDIT_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());
	}

}

//3. �ֱ� ��ư�� Ŭ������ ��
void PuttingForm::OnPutButtonClicked() {
	//3.1 ������ �д´�.
	CString name; (this->GetDlgItem(IDC_EDIT_PERSONAL_NAME))->GetWindowText(name);
	CString position; (this->GetDlgItem(IDC_COMBO_PERSONAL_POSITION))->GetWindowText(position);
	CString cellphoneNumber; (this->GetDlgItem(IDC_EDIT_PERSONAL_CELLPHONENUMBER))->GetWindowText(cellphoneNumber);
	CString emailAddress; (this->GetDlgItem(IDC_EDIT_PERSONAL_EMAILADDRESS))->GetWindowText(emailAddress);
	CString domain; (this->GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS))->GetWindowText(domain);
	emailAddress.Format("%s@%s", (LPCTSTR)emailAddress, (LPCTSTR)domain);

	CString companyName; (this->GetDlgItem(IDC_EDIT_COMPANY_NAME))->GetWindowText(companyName);
	CString address; (this->GetDlgItem(IDC_EDIT_COMPANY_ADDRESS))->GetWindowText(address);
	CString telephoneNumber; (this->GetDlgItem(IDC_EDIT_COMPANY_TELEPHONENUMBER))->GetWindowText(telephoneNumber);
	CString faxNumber; (this->GetDlgItem(IDC_EDIT_COMPANY_FAXNUMBER))->GetWindowText(faxNumber);
	CString url; (this->GetDlgItem(IDC_EDIT_COMPANY_URL))->GetWindowText(url);


	//3.2 ����ö �����츦 ã�´�.
	UpdatingForm *updatingForm = (UpdatingForm*)CWnd::FindWindow("#32770", "����ö");

	//3.3 ����ö �������� ����ö�� �ִ´�.
	BusinessCard businessCard((LPCTSTR)name, (LPCTSTR)position, (LPCTSTR)cellphoneNumber, (LPCTSTR)emailAddress, (LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);
	BusinessCard *businessCardLink = updatingForm->businessCardBinder->Put(businessCard);

	//3.4 ----------------����ö�� DB�� ���´�. -----------------------
	updatingForm->Insert(businessCardLink);


	//3.5 ����ö �������� ����ö�� �����.
	Index *indexLink = updatingForm->indexBinder->Put(businessCardLink);

	//3.6 ����ö �������� TreeControl�� ����� �����.
	((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->DeleteAllItems();

	//3.7 ����ö �������� ����ö���� ���� ����Ʈ�� �����.
	Index(*indexLinks);
	Long count;
	updatingForm->indexBinder->MakeList(&indexLinks, &count);

	//3.8 ����ö �������� TreeControl�� ȸ��� ��带 �����.
	HTREEITEM root = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem("ȸ���", NULL, TVI_ROOT);

	//3.9 ���� ������ŭ �ݺ��Ѵ�.
	Long i = 0;
	Long length;
	Long j = 0;
	BusinessCard *index;
	HTREEITEM parent;
	while (i < count) {
		//3.9.1 �ش� ������ ��ȣ ��带 ����ö �������� TreeControl�� ȸ��� ����� �ڽĳ��� �����,
		companyName = (CString)(indexLinks[i].GetName().c_str());
		parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem(companyName, root, TVI_LAST);
		length = indexLinks[i].GetLength();
		j = 0;
		//3.9.2 �ش� ������ ��뷮��ŭ �ݺ��Ѵ�.
		while (j < length) {
			//3.9.2.1 ���� ��带 ����ö �������� TreeControl�� ��ȣ����� �ڽĳ��� �����.
			index = indexLinks[i].GetAt(j);
			name = (CString)(index->GetName().c_str());
			((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem(name, parent, TVI_LAST);
			j++;
		}
		i++;
	}

	//3.9 ����ö �����쿡 ������ ����Ѵ�.
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(businessCardLink->GetName().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(businessCardLink->GetPosition().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(businessCardLink->GetCellphoneNumber().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(businessCardLink->GetEmailAddress().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(businessCardLink->GetCompanyName().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(businessCardLink->GetAddress().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(businessCardLink->GetTelephoneNumber().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(businessCardLink->GetFaxNumber().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(businessCardLink->GetUrl().c_str());

	//3.10 ����ö �������� ����ö���� ���� ������ ������ ã�´�.
	Long subscript = indexLink->Find(businessCardLink);

	//3.11 ����ö �������� ����ö���� ã�� ���ο��� ���� ������ ��ġ�� ã�´�.
	companyName = (CString)(indexLink->GetName().c_str());
	root = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
	parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);

	//3.12 ã�� ������ ��ȣ�� ����ö �������� TreeControl���� ��ȣ��带 ã�´�.
	CString comparison = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	while (companyName.Compare(comparison) != 0 && parent != NULL) {
		parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
		comparison = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	}

	//3.13 ����ö �������� ��ȣ��忡�� ã�� ��ġ ��°�� �ڽ� ���� �̵��Ѵ�,
	HTREEITEM child = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);
	i = 0;
	while (i < subscript) {
		child = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
		i++;
	}

	//3.14 ��ũ�Ѵ�.
	((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->Expand(parent, TVE_EXPAND);
	((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->Expand(child, TVE_EXPAND);
	((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);


	//3.15 �����츦 �ݴ´�.
	this->EndDialog(0);
}



//4. �ݱ��ư�� Ŭ������ ��
void PuttingForm::OnClose() {
	//4.1 �����츦 �ݴ´�.
	this->EndDialog(0);
}