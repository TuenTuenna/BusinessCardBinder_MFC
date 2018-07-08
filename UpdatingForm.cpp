//UpdatingForm.cpp

#include "UpdatingForm.h"
#include "FindingForm.h"
#include "DrawingForm.h"
#include "PuttingForm.h"
#include "BusinessCardBinder.h"
#include "IndexBinder.h"
#include <afxcmn.h>
#include <afxdb.h>
#include <stdlib.h>

BEGIN_MESSAGE_MAP(UpdatingForm/*subclass*/, CDialog/*superclass*/)
	ON_BN_CLICKED(IDC_BUTTON_PUT, OnPutButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_DRAW, OnDrawButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnLastButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_INDEXBINDER,OnTreeControlItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

UpdatingForm::UpdatingForm(CWnd *parent)
	:CDialog(UpdatingForm::IDD, parent) {
	this->businessCardBinder = NULL;
}

//1.윈도우가 생성될 때
BOOL UpdatingForm::OnInitDialog() {
	CDialog::OnInitDialog();//코드재생성

	//1.1 명함철을 준비한다.
	this->businessCardBinder = new BusinessCardBinder;

	// 색인철을 준비한다.
	this->indexBinder = new IndexBinder;

	//1.2 명함철을 적재한다.
	this->Load();
	Long length = this->businessCardBinder->GetLength();
	if (length > 0) {

		//1.3 명함철에서 맨처음 명함으로 이동한다.
		BusinessCard *index = this->businessCardBinder->First();
		BusinessCard *previous = NULL;
		while (previous != index) {
			this->indexBinder->Put(index);
			previous = index;
			index = this->businessCardBinder->Next();
		}
		HTREEITEM root = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem("회사들", NULL, TVI_ROOT);
		Index(*indexLinks);
		Long count;
		this->indexBinder->MakeList(&indexLinks, &count);
		HTREEITEM parent;
		HTREEITEM child;
		Long i = 0;
		CString companyName;
		CString name;
		while (i < count) {
			parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem(indexLinks[i].GetName().c_str(), root, TVI_LAST);
			Long length = indexLinks[i].GetLength();
			Long j = 0;
			while (j < length) {
				index = indexLinks[i].GetAt(j);
				child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem(index->GetName().c_str(), parent, TVI_LAST);
				j++;
			}
			i++;
		}
		
		index = this->businessCardBinder->First();

		(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(index->GetName().c_str());
		(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(index->GetPosition().c_str());
		(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(index->GetCellphoneNumber().c_str());
		(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(index->GetEmailAddress().c_str());
		(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
		(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
		(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
		(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
		(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());
		
		companyName = index->GetCompanyName().c_str();
		
		Index *indexLink = this->indexBinder->Find((LPCTSTR)companyName);
		
		Long subscript = indexLink->Find(index);

		root = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
		parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);
		CString comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
		
		while (comparison.Compare(companyName) != 0) {
			parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
			comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
		}
		child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);
		i = 0;
		while (i < subscript) {
			child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
			i++;
		}
		((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->Expand(parent, TVE_EXPAND);
		((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->Expand(child, TVE_EXPAND);
		((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);
		
	}


	return FALSE;
}

//2.넣기버튼을 클릭했을 때
void UpdatingForm::OnPutButtonClicked() {
	PuttingForm puttingForm;

	//2.1 넣기윈도우를 생성한다.
	puttingForm.DoModal();
}

//3.찾기버튼을 클릭했을 때
void UpdatingForm::OnFindButtonClicked() {
	FindingForm findingForm;

	//3.1 찾기윈도우를 생성한다.
	findingForm.DoModal();
}

//4.꺼내기버튼을 클릭했을 때
void UpdatingForm::OnDrawButtonClicked() {
	DrawingForm drawingForm;

	//4.1 꺼내기윈도우를 생성한다.
	drawingForm.DoModal();
}

void UpdatingForm::OnArrangeButtonClicked() {
   //5.1 색인철에서 정리한다.
   this->indexBinder->Arrange();

   //5.2 색인 리스트를 만든다.
   Index *indexLinks;
   Long count = 0;
   this->indexBinder->MakeList(&indexLinks, &count);

   //5.3 명함철에서 첫번째 명함으로 이동한다.
   BusinessCard *index = this->businessCardBinder->First();

   //5.4 TreeControl에 모든 항목을 버린다.
   ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->DeleteAllItems();

   //5.5 TreeControl에 회사들 노드를 만든다.
   HTREEITEM root = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem("회사들", NULL, TVI_ROOT);

   //5.6 색인 개수만큼 반복한다.
   Long i = 0;
   Long j = 0;
   HTREEITEM parent;
   Long length = 0;
   CString companyName;
   CString name;
   BusinessCard *businessCardLink;

   while (i < count) {
      //5.6.1 해당 색인의 상호노드를 회사들 노드의 자식노드로 만든다.
      parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem(indexLinks[i].GetName().c_str(), root, TVI_LAST);

      //5.6.2 해당 색인의 사용량 만큼 반복한다.
      length = indexLinks[i].GetLength();
      j = 0;
      while (j < length) {
         //5.6.2.1 성명노드를 만든다.
         businessCardLink = indexLinks[i].GetAt(j);
         name = ((CString)businessCardLink->GetName().c_str());
         ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem(name, parent, TVI_LAST);
         j++;
      }
      i++;
   }

   //5.7 명함철에서 맨처음 명함으로 이동한다.
   index = this->businessCardBinder->First();

   //5.8 맨처음 명함을 출력한다.
   (this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(index->GetName().c_str());
   (this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(index->GetPosition().c_str());
   (this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(index->GetCellphoneNumber().c_str());
   (this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(index->GetEmailAddress().c_str());
   (this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
   (this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
   (this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
   (this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
   (this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());

   //5.9 색인철에서 현재 명함의 색인을 찾는다.
   Index *indexLink = this->indexBinder->Find(index->GetCompanyName());

   //5.10 색인에서 현재 명함의 위치를 찾는다.
   Long subscript = indexLink->Find(index);
   root = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
   parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);
   CString comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
   companyName = CString(index->GetCompanyName().c_str());
   //5.11 찾은 색인의 상호로 TreeControl에서 상호노드를 찾는다.
   while (companyName.Compare(comparison) != 0) {
      parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
      comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
   }

   //5.11 상호노드에서 찾은 위치번째의 자식노드를 이동한다.
   HTREEITEM child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);
   i = 0;
   while (i < subscript) {
      child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
      i++;
   }

   //5.12 마크한다.
   ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->Expand(root, TVE_EXPAND);
   ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->Expand(parent, TVE_EXPAND);
   ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);
}

//6.맨처음 버튼을 클릭했을 때
void UpdatingForm::OnFirstButtonClicked() {

	//6.1 명함철에서 맨처음 명함으로 이동한다.
	BusinessCard* index = this->businessCardBinder->First();

	//6.2 맨처음 명함을 출력한다.
	(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(index->GetName().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(index->GetPosition().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(index->GetCellphoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(index->GetEmailAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());

	//6.3 색인철에서 현재 명함의 색인을 찾는다.
	CString companyName = (LPCTSTR)(index->GetCompanyName().c_str());
	Index *indexLink = this->indexBinder->Find((LPCTSTR)companyName);

	//6.4 색인에서 현재 명함의 위치를 찾는다.
	Long subscript = indexLink->Find(index);

	//6.5 찾은 색인의 상호로 TreeControl에서 상호노드를 찾는다.
	HTREEITEM root = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
	HTREEITEM parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);
	CString comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	while (comparison.Compare(companyName) != 0) {
		parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
		comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	}
	//6.6 상호노드에서 찾은 위치번째의 자식노드로 이동한다.
	HTREEITEM child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);

	//6.7 마크한다.
	Long i = 0;
	while (i < subscript) {
		child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
		i++;
	}
	((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);
}

//7.이전 버튼을 클릭했을 때
void UpdatingForm::OnPreviousButtonClicked() {

	//7.1 명함철에서 이전 명함으로 이동한다.
	BusinessCard* index = this->businessCardBinder->Previous();

	//7.2 이전 명함을 출력한다.
	(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(index->GetName().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(index->GetPosition().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(index->GetCellphoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(index->GetEmailAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());

	//7.3 색인철에서 현재 명함의 색인을 찾는다.
	CString companyName = (LPCTSTR)(index->GetCompanyName().c_str());
	Index *indexLink = this->indexBinder->Find((LPCTSTR)companyName);

	//7.4 색인에서 현재 명함의 위치를 찾는다.
	Long subscript = indexLink->Find(index);

	//7.5 찾은 색인의 상호로 TreeControl에서 상호노드를 찾는다.
	HTREEITEM root = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
	HTREEITEM parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);
	CString comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	while (comparison.Compare(companyName) != 0) {
		parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
		comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	}
	//7.6 상호노드에서 찾은 위치번째의 자식노드로 이동한다.
	HTREEITEM child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);

	//7.7 마크한다.
	Long i = 0;
	while (i < subscript) {
		child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
		i++;
	}
	((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);
}

//8.다음 버튼을 클릭했을 때
void UpdatingForm::OnNextButtonClicked() {

	//8.1 명함철에서 맨처음 명함으로 이동한다.
	BusinessCard* index = this->businessCardBinder->Next();

	//8.2 이전 명함을 출력한다.
	(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(index->GetName().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(index->GetPosition().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(index->GetCellphoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(index->GetEmailAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());

	//8.3 색인철에서 현재 명함의 색인을 찾는다.
	CString companyName = (LPCTSTR)(index->GetCompanyName().c_str());
	Index *indexLink = this->indexBinder->Find((LPCTSTR)companyName);

	//8.4 색인에서 현재 명함의 위치를 찾는다.
	Long subscript = indexLink->Find(index);

	//8.5 찾은 색인의 상호로 TreeControl에서 상호노드를 찾는다.
	HTREEITEM root = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
	HTREEITEM parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);
	CString comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	while (comparison.Compare(companyName) != 0) {
		parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
		comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	}
	//8.6 상호노드에서 찾은 위치번째의 자식노드로 이동한다.
	HTREEITEM child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);

	//8.7 마크한다.
	Long i = 0;
	while (i < subscript) {
		child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
		i++;
	}
	((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);
}

//9.맨끝 버튼을 클릭했을 때
void UpdatingForm::OnLastButtonClicked() {

	//9.1 명함철에서 맨처음 명함으로 이동한다.
	BusinessCard* index = this->businessCardBinder->Last();

	//9.2 이전 명함을 출력한다.
	(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(index->GetName().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(index->GetPosition().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(index->GetCellphoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(index->GetEmailAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());

	//9.3 색인철에서 현재 명함의 색인을 찾는다.
	CString companyName = (LPCTSTR)(index->GetCompanyName().c_str());
	Index *indexLink = this->indexBinder->Find((LPCTSTR)companyName);

	//9.4 색인에서 현재 명함의 위치를 찾는다.
	Long subscript = indexLink->Find(index);

	//9.5 찾은 색인의 상호로 TreeControl에서 상호노드를 찾는다.
	HTREEITEM root = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
	HTREEITEM parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);
	CString comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	while (comparison.Compare(companyName) != 0) {
		parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
		comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	}
	//9.6 상호노드에서 찾은 위치번째의 자식노드로 이동한다.
	HTREEITEM child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);

	//9.7 마크한다.
	Long i = 0;
	while (i < subscript) {
		child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
		i++;
	}
	((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);
}


//10. 트리뷰 컨트롤을 더블클릭했을 때
void UpdatingForm::OnTreeControlItemDoubleClicked(NMHDR * pNotifyStruct, LRESULT * result) {
	//10.1 마크된 노드를 읽는다.
	HTREEITEM tMark = ((CTreeCtrl*)(GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(NULL, TVGN_CARET);

	//10.2 마크된 노드의 부모노드를 찾는다.
	HTREEITEM tParent = ((CTreeCtrl*)(GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(tMark, TVGN_PARENT);

	//10.3 부모노드의 노드까지 위치를 센다.
	HTREEITEM tChild = ((CTreeCtrl*)(GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(tParent, TVGN_CHILD);
	Long subscript = 0;
	while (tMark != tChild) {
		subscript++;
		tChild = /*(HTREEITEM)*/((CTreeCtrl*)(GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(tChild, TVGN_NEXT);
	}

	//10.4 부모노드의 상호로 색인철에서 찾는다.
	tParent = (HTREEITEM)((CTreeCtrl*)(GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(tChild, TVGN_PARENT);
	CString name = ((CTreeCtrl*)(GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(tParent);
	Index *indexLink = indexBinder->Find((LPCTSTR)name);

	//10.5 찾은 색인에서 센 위치번째의 명함을 읽는다.
	BusinessCard *index = indexLink->GetAt(subscript);

	//10.6 명함철의 명함에 현재 명함을 출력한다.
	businessCardBinder->Move(index);
	(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(index->GetName().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(index->GetPosition().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(index->GetCellphoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(index->GetEmailAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());
}

//11. 닫기버튼을 클릭했을 때
void UpdatingForm::OnClose() {

	if (this->businessCardBinder != NULL) {
		// 11.1 명함철을 데이터 베이스에 저장한다.
		this->Save();

		// 11.2 명함철을 지운다.
		delete this->businessCardBinder;
	}
	// 11.3 색인철을 지운다
	if (indexBinder != NULL) {
		delete indexBinder;
	}
	// 11.4 윈도우를 닫는다.
	this->EndDialog(0);
}



//-----------------------데이터베이스 함수 정의----------------------
void UpdatingForm::Load() {
	CDatabase db;
	CRecordset rs(&db); // SELECT 할 때만 사용
	CString sql = "select Personal.name, Personal.position, Personal.cellphoneNumber, Personal.emailAddress, Company.name, Company.address, Company.telephoneNumber, Company.faxNumber, Company.url From Personal inner join Company on Company.companyCode=Personal.companyCode;";
	db.OpenEx("DSN=BusinessCardBinder;UID=root;PWD=mysql"); // Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); // Request/ Response
	CString name;
	CString position;
	CString cellphoneNumber;
	CString emailAddress;
	CString companyName;
	CString address;
	CString telephoneNumber;
	CString faxNumber;
	CString url;

	while (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, name);
		rs.GetFieldValue((short)1, position);
		rs.GetFieldValue((short)2, cellphoneNumber);
		rs.GetFieldValue((short)3, emailAddress);
		rs.GetFieldValue((short)4, companyName);
		rs.GetFieldValue((short)5, address);
		rs.GetFieldValue((short)6, telephoneNumber);
		rs.GetFieldValue((short)7, faxNumber);
		rs.GetFieldValue((short)8, url);
		BusinessCard businessCard((LPCTSTR)name, (LPCTSTR)position, (LPCTSTR)cellphoneNumber, (LPCTSTR)emailAddress, (LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);
		this->businessCardBinder->Put(businessCard);
		rs.MoveNext();
	}
	rs.Close();  // Disconnection
	db.Close(); // Disconnection
}

void UpdatingForm::Save() {
	CDatabase db;
	CRecordset rsCode(&db);
	CRecordset rsCompany(&db);
	CString code;
	CString companyCode;
	CString sql = "SELECT Personal.code, Personal.companyCode from Personal;";
	db.OpenEx("DSN=BusinessCardBinder;UID=root;PWD=mysql"); // Request / Response
	rsCode.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	sql = "DELETE FROM Personal;";
	db.ExecuteSQL(sql);
	sql = "DELETE FROM Company;";
	db.ExecuteSQL(sql);

	BusinessCard *previous = NULL;
	BusinessCard *it = NULL;
	if (this->businessCardBinder->GetLength() > 0) {
		it = this->businessCardBinder->First();
	}
	while (it != previous) {
		rsCode.GetFieldValue((short)0, code);//개인 읽는다.
		rsCode.GetFieldValue((short)1, companyCode);//회사를 읽는다.
		sql.Format("SELECT Company.name FROM Company WHERE Company.companyCode = '%s';", (LPCTSTR)companyCode);
		rsCompany.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//등록된 회사 확인
		if (rsCompany.IsEOF()) { //등록된 회사가없으면 회사를 등록한다
			sql.Format("INSERT INTO Company VALUES('%s','%s','%s','%s','%s','%s');", it->GetCompanyName().c_str(), it->GetAddress().c_str(), it->GetTelephoneNumber().c_str(), it->GetFaxNumber().c_str(), it->GetUrl().c_str(), (LPCTSTR)companyCode);
			db.ExecuteSQL(sql);
		}
		//회사코드로 개인을 등록한다
		sql.Format("INSERT INTO PERSONAL VALUES('%s','%s','%s','%s','%s','%s');", it->GetName().c_str(), it->GetPosition().c_str(), it->GetCellphoneNumber().c_str(), it->GetEmailAddress().c_str(), (LPCTSTR)code, (LPCTSTR)companyCode);
		db.ExecuteSQL(sql);
		rsCode.MoveNext();
		rsCompany.Close();
		previous = it;
		it = this->businessCardBinder->Next();
	}
	rsCode.Close();
	db.Close();
}


void UpdatingForm::Insert(BusinessCard *businessCard) {
	CDatabase db;
	CRecordset rs(&db);
	CString sqlSelectCompany;
	CString sqlInsertPersonal;
	CString sqlInsertCompany;
	CString companyCode;
	CString code;

	db.OpenEx("DSN=BusinessCardBinder;UID=root;PWD=mysql");

	sqlSelectCompany.Format("SELECT Company.companyCode FROM Company WHERE Company.name='%s' AND Company.address='%s' "
		"AND Company.telephoneNumber='%s' AND Company.faxNumber='%s' AND Company.url='%s';"
		, businessCard->GetCompanyName().c_str(),businessCard->GetAddress().c_str(),businessCard->GetTelephoneNumber().c_str()
		,businessCard->GetFaxNumber().c_str(),businessCard->GetUrl().c_str());
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sqlSelectCompany);
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, companyCode);
	}
	else {
		companyCode = this->GetCompanyCode();
		sqlInsertCompany.Format("INSERT INTO Company(name,address,telephoneNumber,faxNumber,url,companyCode)"
			" VALUES('%s','%s','%s','%s','%s','%s');", businessCard->GetCompanyName().c_str(),
			businessCard->GetAddress().c_str(), businessCard->GetTelephoneNumber().c_str(),
			businessCard->GetFaxNumber().c_str(), businessCard->GetUrl().c_str(), companyCode);
		db.ExecuteSQL(sqlInsertCompany);
	}
	code = this->GetCode();
	sqlInsertPersonal.Format("INSERT INTO Personal(name,position,cellphoneNumber,emailAddress,code,companyCode)"
		" VALUES('%s','%s','%s','%s','%s','%s');", businessCard->GetName().c_str(),
		businessCard->GetPosition().c_str(), businessCard->GetCellphoneNumber().c_str(),
		businessCard->GetEmailAddress().c_str(), (LPCTSTR)code, (LPCTSTR)companyCode);
	db.ExecuteSQL(sqlInsertPersonal);
	rs.Close();
	db.Close();
}

void UpdatingForm::Delete(BusinessCard *businessCard) {	
	CDatabase db;
	CRecordset rs(&db);
	CString sql;
	CString code;
	CString companyCode;
	sql.Format("SELECT Personal.code, Personal.companyCode FROM Personal WHERE Personal.name='%s' AND Personal.position='%s' "
		"AND Personal.cellphoneNumber='%s' AND Personal.emailAddress='%s';", businessCard->GetName().c_str(), 
		businessCard->GetPosition().c_str(), businessCard->GetCellphoneNumber().c_str(), businessCard->GetEmailAddress().c_str());
	db.OpenEx("DSN=BusinessCardBinder;UID=root;PWD=mysql");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	rs.GetFieldValue((short)0, code);
	rs.GetFieldValue((short)1, companyCode);
	sql.Format("DELETE FROM Personal WHERE Personal.code='%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);
	sql.Format("SELECT * FROM Personal WHERE Personal.companyCode='%s';", (LPCTSTR)companyCode);
	rs.Close();
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	if (rs.IsEOF()) {
		sql.Format("DELETE FROM Company WHERE Company.companyCode='%s';", (LPCTSTR)companyCode);
		db.ExecuteSQL(sql);
	}
	rs.Close();
	db.Close();
}


CString UpdatingForm::GetCode() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code From Personal ORDER BY code DESC;";
	db.OpenEx("DSN=BusinessCardBinder;UID=root;PWD=mysql"); // Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); // Request
	CString code("P0000");
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, code);
	}
	int number = _ttoi(code.Right(4));
	code.Format("P%04d", number + 1);
	rs.Close();
	db.Close();
	return code;
}

CString UpdatingForm::GetCompanyCode() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Company.companyCode From Company ORDER BY companyCode DESC;";
	db.OpenEx("DSN=BusinessCardBinder;UID=root;PWD=mysql"); // Connection
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql); // Request
	CString companyCode("C0000");
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, companyCode);
	}
	int number = _ttoi(companyCode.Right(4));
	companyCode.Format("C%04d", number + 1);
	rs.Close();
	db.Close();
	return companyCode;
}