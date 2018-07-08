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

//1. 윈도우가 생성될 떄
BOOL PuttingForm::OnInitDialog()
{
	CDialog::OnInitDialog();//코드재생성

							//1.1 직급 콤보박스에 목록을 만든다.
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_POSITION)))->AddString("회장");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_POSITION)))->AddString("사장");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_POSITION)))->AddString("부장");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_POSITION)))->AddString("차장");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_POSITION)))->AddString("과장");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_POSITION)))->AddString("대리");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_POSITION)))->AddString("사원");

	//1.2 이메일주소 콤보박스에 목록을 만든다.
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS)))->AddString("naver.com");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS)))->AddString("nate.com");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS)))->AddString("daum.net");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS)))->AddString("gmail.com");
	((CComboBox*)(this->GetDlgItem(IDC_COMBO_PERSONAL_EMAILADDRESS)))->AddString("직접입력");

	return FALSE;
}

//2. 상호에디트가 포커스를 잃었을 때
void PuttingForm::OnCompanyNameEditKillFocus() {

	//2.1 상호를 읽는다.
	CString companyName;
	this->GetDlgItem(IDC_EDIT_COMPANY_NAME)->GetWindowText(companyName);

	//2.2 명함철 윈도우를 찾는다.
	UpdatingForm *updatingForm = (UpdatingForm*)CWnd::FindWindow("#32770", "명함철");

	//2.3 명함철윈도우의 명함철에서 상호를 찾는다.
	BusinessCard* index = updatingForm->businessCardBinder->FindByCompanyNmae((LPCTSTR)companyName);

	//2.4 명함이 있으면 회사를 출력한다.
	if (index != NULL) {
		(this->GetDlgItem(IDC_EDIT_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
		(this->GetDlgItem(IDC_EDIT_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
		(this->GetDlgItem(IDC_EDIT_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
		(this->GetDlgItem(IDC_EDIT_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
		(this->GetDlgItem(IDC_EDIT_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());
	}

}

//3. 넣기 버튼을 클릭했을 때
void PuttingForm::OnPutButtonClicked() {
	//3.1 명함을 읽는다.
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


	//3.2 명함철 윈도우를 찾는다.
	UpdatingForm *updatingForm = (UpdatingForm*)CWnd::FindWindow("#32770", "명함철");

	//3.3 명함철 윈도우의 명함철에 넣는다.
	BusinessCard businessCard((LPCTSTR)name, (LPCTSTR)position, (LPCTSTR)cellphoneNumber, (LPCTSTR)emailAddress, (LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);
	BusinessCard *businessCardLink = updatingForm->businessCardBinder->Put(businessCard);

	//3.4 ----------------명함철을 DB에 적는다. -----------------------
	updatingForm->Insert(businessCardLink);


	//3.5 명함철 윈도우의 색인철에 끼운다.
	Index *indexLink = updatingForm->indexBinder->Put(businessCardLink);

	//3.6 명함철 윈도우의 TreeControl의 목록을 지운다.
	((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->DeleteAllItems();

	//3.7 명함철 윈도우의 색인철에서 색안 리스트를 만든다.
	Index(*indexLinks);
	Long count;
	updatingForm->indexBinder->MakeList(&indexLinks, &count);

	//3.8 명함철 윈도우의 TreeControl에 회사들 노드를 만든다.
	HTREEITEM root = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem("회사들", NULL, TVI_ROOT);

	//3.9 색인 개수만큼 반복한다.
	Long i = 0;
	Long length;
	Long j = 0;
	BusinessCard *index;
	HTREEITEM parent;
	while (i < count) {
		//3.9.1 해당 색인의 상호 노드를 명함철 윈도우의 TreeControl의 회사들 노드의 자식노드로 만든다,
		companyName = (CString)(indexLinks[i].GetName().c_str());
		parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem(companyName, root, TVI_LAST);
		length = indexLinks[i].GetLength();
		j = 0;
		//3.9.2 해당 색인의 사용량만큼 반복한다.
		while (j < length) {
			//3.9.2.1 성명 노드를 명함철 윈도우의 TreeControl의 상호노드의 자식노드로 만든다.
			index = indexLinks[i].GetAt(j);
			name = (CString)(index->GetName().c_str());
			((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem(name, parent, TVI_LAST);
			j++;
		}
		i++;
	}

	//3.9 명함철 윈도우에 명함을 출력한다.
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(businessCardLink->GetName().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(businessCardLink->GetPosition().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(businessCardLink->GetCellphoneNumber().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(businessCardLink->GetEmailAddress().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(businessCardLink->GetCompanyName().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(businessCardLink->GetAddress().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(businessCardLink->GetTelephoneNumber().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(businessCardLink->GetFaxNumber().c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(businessCardLink->GetUrl().c_str());

	//3.10 명함철 윈도우의 색인철에서 넣은 명함의 색인을 찾는다.
	Long subscript = indexLink->Find(businessCardLink);

	//3.11 명함철 윈도우의 색인철에서 찾은 색인에서 넣은 명함의 위치를 찾는다.
	companyName = (CString)(indexLink->GetName().c_str());
	root = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
	parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);

	//3.12 찾은 색인의 상호로 명함철 윈도우의 TreeControl에서 상호노드를 찾는다.
	CString comparison = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	while (companyName.Compare(comparison) != 0 && parent != NULL) {
		parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
		comparison = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	}

	//3.13 명함철 윈도우의 상호노드에서 찾은 위치 번째의 자식 노드로 이동한다,
	HTREEITEM child = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);
	i = 0;
	while (i < subscript) {
		child = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
		i++;
	}

	//3.14 마크한다.
	((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->Expand(parent, TVE_EXPAND);
	((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->Expand(child, TVE_EXPAND);
	((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);


	//3.15 윈도우를 닫는다.
	this->EndDialog(0);
}



//4. 닫기버튼을 클릭했을 때
void PuttingForm::OnClose() {
	//4.1 윈도우를 닫는다.
	this->EndDialog(0);
}