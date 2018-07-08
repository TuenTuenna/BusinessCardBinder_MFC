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

// 생성자
FindingForm::FindingForm(CWnd *parent)
	:CDialog(FindingForm::IDD, parent) {
	this->count = 0;
	this->current = 0;
}

//1. 찾기 버튼을 클릭했을 때
void FindingForm::OnFindButtonClicked() {

	//1.1 성명을 읽는다.
	CString name;
	(this->GetDlgItem(IDC_EDIT_PERSONAL_NAME))->GetWindowText(name);

	//1.2 명함철 윈도우를 찾는다.
	UpdatingForm *updatingForm = (UpdatingForm*)CWnd::FindWindow("#32770", "명함철");

	//1.3 명함철 윈도우의 명함철에서 찾는다.
	if (this->indexes != NULL) {
		delete[] indexes;
		indexes = NULL;
	}
	updatingForm->businessCardBinder->Find((LPCTSTR)name, &indexes, &count);

	//1.4 찾은명함이 있으면 첫번째 명함을 출력한다.
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


//2. 선택하기 버튼을 클릭했을 때
void FindingForm::OnSelectButtonClicked() {

	//2.1 명함의 위치를 읽는다.
	//2.2 명함철 윈도우를 찾는다.
	UpdatingForm *updatingForm = (UpdatingForm*)CWnd::FindWindow("#32770", "명함철");

	//2.3 명함철 윈도우의 명함철에서 특정 명함으로 이동한다.
	BusinessCard *index = updatingForm->businessCardBinder->Move(indexes[current]);

	//2.4 명함철 윈도우의 색인철에서 현재명함의 색인을 찾는다.
	CString companyName = ((CString)index->GetCompanyName().c_str());
	Index *indexLink = updatingForm->indexBinder->Find((LPCTSTR)companyName);

	//2.5 명함철 윈도우의 색인에서 현재명함의 위치를 찾는다.
	Long subscript = indexLink->Find(this->indexes[current]);

	//2.6 찾은 색인의 상호로 TreeControl에서 상호노드를 찾는다.
	HTREEITEM root = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
	HTREEITEM parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);
	CString comparison = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);

	while (comparison.Compare(companyName) != 0) {
		parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
		comparison = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	}

	//2.7 찾은 상호노드에서 찾은 위치번째의 자식노드를 이동한다.
	HTREEITEM child = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);
	Long i = 0;
	while (i < subscript) {
		child = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
		i++;
	}

	//2.8 명함철 윈도우에서 해당 노드를 마크한다
	((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->Expand(root, TVE_EXPAND);
	((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->Expand(parent, TVE_EXPAND);

	((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);

	//2.9 명함철 윈도우의 명함에 출력한다.
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText((index->GetName()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText((index->GetPosition()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText((index->GetCellphoneNumber()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText((index->GetEmailAddress()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText((index->GetCompanyName()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText((index->GetAddress()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText((index->GetTelephoneNumber()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText((index->GetFaxNumber()).c_str());
	(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText((index->GetUrl()).c_str());

	// 2.10 윈도우를 닫는다.
	if (indexes != NULL) {
		delete[] indexes;
		indexes = NULL;
	}
	this->EndDialog(0);
}

//3. 맨처음 버튼을 클릭했을 때
void FindingForm::OnFirstButtonClicked() {

	//3.1 찾은 명함들에서 맨 처음 명함으로 이동한다.
	current = 0;

	//3.2 맨처음 명함을 출력한다.
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

//4. 이전 버튼을 클릭했을 때
void FindingForm::OnPreviousButtonClicked() {

	//4.1 찾은 명함들에서 이전명함으로 이동한다.
	current--;

	if (current < 0) {
		current = 0;
	}
	//4.2 이전 명함을 출력한다.
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

//5. 다음 버튼을 클릭했을 때
void FindingForm::OnNextButtonClicked() {

	//5.1 찾은 명함들에서 다음 명함으로 이동한다.
	current++;

	if (current >= count ) {
		current = count - 1;
	}

	//5.2 다음 명함을 출력한다.
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

//6. 맨끝 버튼을 클릭했을 때
void FindingForm::OnLastButtonClicked() {

	//6.1 찾은 명함들 중에서 마지막 명함으로 이동한다.
	current = count - 1;

	//6.2 마지막 명함을 출력한다.
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

//7. 닫기버튼을 클릭했을 떄
void FindingForm::OnClose() {

	// 7.1 윈도우를 닫는다.
	if (indexes != NULL) {
		delete[] indexes;
		indexes = NULL;
	}
	this->EndDialog(0);
}