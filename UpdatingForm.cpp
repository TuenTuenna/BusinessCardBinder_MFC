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

//1.�����찡 ������ ��
BOOL UpdatingForm::OnInitDialog() {
	CDialog::OnInitDialog();//�ڵ������

	//1.1 ����ö�� �غ��Ѵ�.
	this->businessCardBinder = new BusinessCardBinder;

	// ����ö�� �غ��Ѵ�.
	this->indexBinder = new IndexBinder;

	//1.2 ����ö�� �����Ѵ�.
	this->Load();
	Long length = this->businessCardBinder->GetLength();
	if (length > 0) {

		//1.3 ����ö���� ��ó�� �������� �̵��Ѵ�.
		BusinessCard *index = this->businessCardBinder->First();
		BusinessCard *previous = NULL;
		while (previous != index) {
			this->indexBinder->Put(index);
			previous = index;
			index = this->businessCardBinder->Next();
		}
		HTREEITEM root = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem("ȸ���", NULL, TVI_ROOT);
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

//2.�ֱ��ư�� Ŭ������ ��
void UpdatingForm::OnPutButtonClicked() {
	PuttingForm puttingForm;

	//2.1 �ֱ������츦 �����Ѵ�.
	puttingForm.DoModal();
}

//3.ã���ư�� Ŭ������ ��
void UpdatingForm::OnFindButtonClicked() {
	FindingForm findingForm;

	//3.1 ã�������츦 �����Ѵ�.
	findingForm.DoModal();
}

//4.�������ư�� Ŭ������ ��
void UpdatingForm::OnDrawButtonClicked() {
	DrawingForm drawingForm;

	//4.1 �����������츦 �����Ѵ�.
	drawingForm.DoModal();
}

void UpdatingForm::OnArrangeButtonClicked() {
   //5.1 ����ö���� �����Ѵ�.
   this->indexBinder->Arrange();

   //5.2 ���� ����Ʈ�� �����.
   Index *indexLinks;
   Long count = 0;
   this->indexBinder->MakeList(&indexLinks, &count);

   //5.3 ����ö���� ù��° �������� �̵��Ѵ�.
   BusinessCard *index = this->businessCardBinder->First();

   //5.4 TreeControl�� ��� �׸��� ������.
   ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->DeleteAllItems();

   //5.5 TreeControl�� ȸ��� ��带 �����.
   HTREEITEM root = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem("ȸ���", NULL, TVI_ROOT);

   //5.6 ���� ������ŭ �ݺ��Ѵ�.
   Long i = 0;
   Long j = 0;
   HTREEITEM parent;
   Long length = 0;
   CString companyName;
   CString name;
   BusinessCard *businessCardLink;

   while (i < count) {
      //5.6.1 �ش� ������ ��ȣ��带 ȸ��� ����� �ڽĳ��� �����.
      parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem(indexLinks[i].GetName().c_str(), root, TVI_LAST);

      //5.6.2 �ش� ������ ��뷮 ��ŭ �ݺ��Ѵ�.
      length = indexLinks[i].GetLength();
      j = 0;
      while (j < length) {
         //5.6.2.1 �����带 �����.
         businessCardLink = indexLinks[i].GetAt(j);
         name = ((CString)businessCardLink->GetName().c_str());
         ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem(name, parent, TVI_LAST);
         j++;
      }
      i++;
   }

   //5.7 ����ö���� ��ó�� �������� �̵��Ѵ�.
   index = this->businessCardBinder->First();

   //5.8 ��ó�� ������ ����Ѵ�.
   (this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(index->GetName().c_str());
   (this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(index->GetPosition().c_str());
   (this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(index->GetCellphoneNumber().c_str());
   (this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(index->GetEmailAddress().c_str());
   (this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
   (this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
   (this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
   (this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
   (this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());

   //5.9 ����ö���� ���� ������ ������ ã�´�.
   Index *indexLink = this->indexBinder->Find(index->GetCompanyName());

   //5.10 ���ο��� ���� ������ ��ġ�� ã�´�.
   Long subscript = indexLink->Find(index);
   root = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
   parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);
   CString comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
   companyName = CString(index->GetCompanyName().c_str());
   //5.11 ã�� ������ ��ȣ�� TreeControl���� ��ȣ��带 ã�´�.
   while (companyName.Compare(comparison) != 0) {
      parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
      comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
   }

   //5.11 ��ȣ��忡�� ã�� ��ġ��°�� �ڽĳ�带 �̵��Ѵ�.
   HTREEITEM child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);
   i = 0;
   while (i < subscript) {
      child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
      i++;
   }

   //5.12 ��ũ�Ѵ�.
   ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->Expand(root, TVE_EXPAND);
   ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->Expand(parent, TVE_EXPAND);
   ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);
}

//6.��ó�� ��ư�� Ŭ������ ��
void UpdatingForm::OnFirstButtonClicked() {

	//6.1 ����ö���� ��ó�� �������� �̵��Ѵ�.
	BusinessCard* index = this->businessCardBinder->First();

	//6.2 ��ó�� ������ ����Ѵ�.
	(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(index->GetName().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(index->GetPosition().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(index->GetCellphoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(index->GetEmailAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());

	//6.3 ����ö���� ���� ������ ������ ã�´�.
	CString companyName = (LPCTSTR)(index->GetCompanyName().c_str());
	Index *indexLink = this->indexBinder->Find((LPCTSTR)companyName);

	//6.4 ���ο��� ���� ������ ��ġ�� ã�´�.
	Long subscript = indexLink->Find(index);

	//6.5 ã�� ������ ��ȣ�� TreeControl���� ��ȣ��带 ã�´�.
	HTREEITEM root = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
	HTREEITEM parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);
	CString comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	while (comparison.Compare(companyName) != 0) {
		parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
		comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	}
	//6.6 ��ȣ��忡�� ã�� ��ġ��°�� �ڽĳ��� �̵��Ѵ�.
	HTREEITEM child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);

	//6.7 ��ũ�Ѵ�.
	Long i = 0;
	while (i < subscript) {
		child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
		i++;
	}
	((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);
}

//7.���� ��ư�� Ŭ������ ��
void UpdatingForm::OnPreviousButtonClicked() {

	//7.1 ����ö���� ���� �������� �̵��Ѵ�.
	BusinessCard* index = this->businessCardBinder->Previous();

	//7.2 ���� ������ ����Ѵ�.
	(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(index->GetName().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(index->GetPosition().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(index->GetCellphoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(index->GetEmailAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());

	//7.3 ����ö���� ���� ������ ������ ã�´�.
	CString companyName = (LPCTSTR)(index->GetCompanyName().c_str());
	Index *indexLink = this->indexBinder->Find((LPCTSTR)companyName);

	//7.4 ���ο��� ���� ������ ��ġ�� ã�´�.
	Long subscript = indexLink->Find(index);

	//7.5 ã�� ������ ��ȣ�� TreeControl���� ��ȣ��带 ã�´�.
	HTREEITEM root = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
	HTREEITEM parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);
	CString comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	while (comparison.Compare(companyName) != 0) {
		parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
		comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	}
	//7.6 ��ȣ��忡�� ã�� ��ġ��°�� �ڽĳ��� �̵��Ѵ�.
	HTREEITEM child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);

	//7.7 ��ũ�Ѵ�.
	Long i = 0;
	while (i < subscript) {
		child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
		i++;
	}
	((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);
}

//8.���� ��ư�� Ŭ������ ��
void UpdatingForm::OnNextButtonClicked() {

	//8.1 ����ö���� ��ó�� �������� �̵��Ѵ�.
	BusinessCard* index = this->businessCardBinder->Next();

	//8.2 ���� ������ ����Ѵ�.
	(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(index->GetName().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(index->GetPosition().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(index->GetCellphoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(index->GetEmailAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());

	//8.3 ����ö���� ���� ������ ������ ã�´�.
	CString companyName = (LPCTSTR)(index->GetCompanyName().c_str());
	Index *indexLink = this->indexBinder->Find((LPCTSTR)companyName);

	//8.4 ���ο��� ���� ������ ��ġ�� ã�´�.
	Long subscript = indexLink->Find(index);

	//8.5 ã�� ������ ��ȣ�� TreeControl���� ��ȣ��带 ã�´�.
	HTREEITEM root = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
	HTREEITEM parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);
	CString comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	while (comparison.Compare(companyName) != 0) {
		parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
		comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	}
	//8.6 ��ȣ��忡�� ã�� ��ġ��°�� �ڽĳ��� �̵��Ѵ�.
	HTREEITEM child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);

	//8.7 ��ũ�Ѵ�.
	Long i = 0;
	while (i < subscript) {
		child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
		i++;
	}
	((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);
}

//9.�ǳ� ��ư�� Ŭ������ ��
void UpdatingForm::OnLastButtonClicked() {

	//9.1 ����ö���� ��ó�� �������� �̵��Ѵ�.
	BusinessCard* index = this->businessCardBinder->Last();

	//9.2 ���� ������ ����Ѵ�.
	(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(index->GetName().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(index->GetPosition().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(index->GetCellphoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(index->GetEmailAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());

	//9.3 ����ö���� ���� ������ ������ ã�´�.
	CString companyName = (LPCTSTR)(index->GetCompanyName().c_str());
	Index *indexLink = this->indexBinder->Find((LPCTSTR)companyName);

	//9.4 ���ο��� ���� ������ ��ġ�� ã�´�.
	Long subscript = indexLink->Find(index);

	//9.5 ã�� ������ ��ȣ�� TreeControl���� ��ȣ��带 ã�´�.
	HTREEITEM root = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
	HTREEITEM parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);
	CString comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	while (comparison.Compare(companyName) != 0) {
		parent = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
		comparison = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
	}
	//9.6 ��ȣ��忡�� ã�� ��ġ��°�� �ڽĳ��� �̵��Ѵ�.
	HTREEITEM child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);

	//9.7 ��ũ�Ѵ�.
	Long i = 0;
	while (i < subscript) {
		child = ((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
		i++;
	}
	((CTreeCtrl*)(this->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);
}


//10. Ʈ���� ��Ʈ���� ����Ŭ������ ��
void UpdatingForm::OnTreeControlItemDoubleClicked(NMHDR * pNotifyStruct, LRESULT * result) {
	//10.1 ��ũ�� ��带 �д´�.
	HTREEITEM tMark = ((CTreeCtrl*)(GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(NULL, TVGN_CARET);

	//10.2 ��ũ�� ����� �θ��带 ã�´�.
	HTREEITEM tParent = ((CTreeCtrl*)(GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(tMark, TVGN_PARENT);

	//10.3 �θ����� ������ ��ġ�� ����.
	HTREEITEM tChild = ((CTreeCtrl*)(GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(tParent, TVGN_CHILD);
	Long subscript = 0;
	while (tMark != tChild) {
		subscript++;
		tChild = /*(HTREEITEM)*/((CTreeCtrl*)(GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(tChild, TVGN_NEXT);
	}

	//10.4 �θ����� ��ȣ�� ����ö���� ã�´�.
	tParent = (HTREEITEM)((CTreeCtrl*)(GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(tChild, TVGN_PARENT);
	CString name = ((CTreeCtrl*)(GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(tParent);
	Index *indexLink = indexBinder->Find((LPCTSTR)name);

	//10.5 ã�� ���ο��� �� ��ġ��°�� ������ �д´�.
	BusinessCard *index = indexLink->GetAt(subscript);

	//10.6 ����ö�� ���Կ� ���� ������ ����Ѵ�.
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

//11. �ݱ��ư�� Ŭ������ ��
void UpdatingForm::OnClose() {

	if (this->businessCardBinder != NULL) {
		// 11.1 ����ö�� ������ ���̽��� �����Ѵ�.
		this->Save();

		// 11.2 ����ö�� �����.
		delete this->businessCardBinder;
	}
	// 11.3 ����ö�� �����
	if (indexBinder != NULL) {
		delete indexBinder;
	}
	// 11.4 �����츦 �ݴ´�.
	this->EndDialog(0);
}



//-----------------------�����ͺ��̽� �Լ� ����----------------------
void UpdatingForm::Load() {
	CDatabase db;
	CRecordset rs(&db); // SELECT �� ���� ���
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
		rsCode.GetFieldValue((short)0, code);//���� �д´�.
		rsCode.GetFieldValue((short)1, companyCode);//ȸ�縦 �д´�.
		sql.Format("SELECT Company.name FROM Company WHERE Company.companyCode = '%s';", (LPCTSTR)companyCode);
		rsCompany.Open(AFX_DB_USE_DEFAULT_TYPE, sql);//��ϵ� ȸ�� Ȯ��
		if (rsCompany.IsEOF()) { //��ϵ� ȸ�簡������ ȸ�縦 ����Ѵ�
			sql.Format("INSERT INTO Company VALUES('%s','%s','%s','%s','%s','%s');", it->GetCompanyName().c_str(), it->GetAddress().c_str(), it->GetTelephoneNumber().c_str(), it->GetFaxNumber().c_str(), it->GetUrl().c_str(), (LPCTSTR)companyCode);
			db.ExecuteSQL(sql);
		}
		//ȸ���ڵ�� ������ ����Ѵ�
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