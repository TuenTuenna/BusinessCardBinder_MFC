//DrawingForm.cpp

#include"DrawingForm.h"
#include"UpdatingForm.h"
#include<afxcmn.h>
#include"BusinessCardBinder.h"
#include"IndexBinder.h"

BEGIN_MESSAGE_MAP(DrawingForm, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

DrawingForm::DrawingForm(CWnd * parent)
	:CDialog(DrawingForm::IDD, parent) {
}

//1. �����찡 �����Ǿ��� ��
BOOL DrawingForm::OnInitDialog() {
	CDialog::OnInitDialog();//�ڵ������

							//1.1 ����ö �����츦 ã�´�.
	UpdatingForm *updatingForm = (UpdatingForm*)CWnd::FindWindow("#32770", "����ö");

	//1.2 ����ö �������� ����ö���� ������ġ�� �д´�.
	BusinessCard *index = (BusinessCard*)updatingForm->businessCardBinder->GetCurrent();

	//1.3 ����ö �������� ����ö���� ������.
	BusinessCard businessCard = (BusinessCard)updatingForm->businessCardBinder->Draw(index);

	//1.4 ����ö �������� ����ö���� ������.
	Index *indexLink = updatingForm->indexBinder->Draw(index, businessCard.GetCompanyName().c_str());
	updatingForm->Delete(&businessCard);

	//1.5 ����ö �������� ����ö���� ���θ���Ʈ�� �����.
	Index(*indexLinks);
	Long count;
	updatingForm->indexBinder->MakeList(&indexLinks, &count);

	//1.6 ����ö �������� TreeControl�� ����� �����.
	((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->DeleteAllItems();

	//1.7 ����ö �������� TreeControl�� ȸ��� ��带 �����.
	HTREEITEM root = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem("ȸ���", NULL, TVI_ROOT);

	//1.8 ���� ������ŭ �ݺ��Ѵ�.
	HTREEITEM parent;
	HTREEITEM child;
	Long i = 0;
	while (i < count) {
		//1.8.1 �ش� ������ ��ȣ��带 ȸ��� ����� �ڽĳ��� �����.
		parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem(indexLinks[i].GetName().c_str(), root, TVI_LAST);

		//1.8.2 �ش������ ��뷮 ��ŭ �ݺ��Ѵ�.
		Long length = indexLinks[i].GetLength();
		Long j = 0;
		while (j < length) {
			index = indexLinks[i].GetAt(j);
			child = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem(index->GetName().c_str(), parent, TVI_LAST);
			j++;
		}
		i++;
	}

	(this->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(businessCard.GetName().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(businessCard.GetPosition().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(businessCard.GetCellphoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(businessCard.GetEmailAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(businessCard.GetCompanyName().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(businessCard.GetAddress().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(businessCard.GetTelephoneNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(businessCard.GetFaxNumber().c_str());
	(this->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(businessCard.GetUrl().c_str());

	index = (BusinessCard*)updatingForm->businessCardBinder->GetCurrent();

	if (index != NULL) {
		(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(index->GetName().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(index->GetPosition().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(index->GetCellphoneNumber().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(index->GetEmailAddress().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());
		CString companyName = ((CString)(index->GetCompanyName().c_str()));
		Index *indexLink = updatingForm->indexBinder->Find((LPCTSTR)companyName);
		Long subscript = indexLink->Find(index);
		root = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
		parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);
		CString comparison = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
		while (comparison.Compare(companyName) != 0) {
			parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
			comparison = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
		}
		child = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);
		i = 0;
		while (i < subscript) {
			child = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
			i++;
		}
		((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);
	}
	else {
		(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText("");
		(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText("");
		(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText("");
		(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText("");
		(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText("");
		(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText("");
		(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText("");
		(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText("");
		(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText("");
	}
	return FALSE;
}

//2. �ݱ��ư�� Ŭ������ ��
void DrawingForm::OnClose() {

	//2.1 �޽����ڽ��� ����Ѵ�.
	int confirm = AfxMessageBox("����ðڽ��ϱ�?", MB_YESNOCANCEL | MB_ICONINFORMATION);

	//2.2 "��" ��ư�� Ŭ������ ��
	if (confirm == IDYES) {
		//2.2.1 ������ �д´�.
		CString name; this->GetDlgItem(IDC_STATIC_PERSONAL_NAME)->GetWindowText(name);
		CString position; this->GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->GetWindowText(position);
		CString cellphoneNumber; this->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->GetWindowText(cellphoneNumber);
		CString emailAddress; this->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->GetWindowText(emailAddress);
		CString companyName; this->GetDlgItem(IDC_STATIC_COMPANY_NAME)->GetWindowText(companyName);
		CString address; this->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->GetWindowText(address);
		CString telephoneNumber; this->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
		CString faxNumber; this->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->GetWindowText(faxNumber);
		CString url; this->GetDlgItem(IDC_STATIC_COMPANY_URL)->GetWindowText(url);
		BusinessCard businessCard((LPCTSTR)name, (LPCTSTR)position, (LPCTSTR)cellphoneNumber, (LPCTSTR)emailAddress, (LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);

		//2.2.2 ����ö �����츦 ã�´�.
		UpdatingForm *updatingForm = (UpdatingForm*)CWnd::FindWindow("#32770", "����ö");

		//2.2.3 ����ö �������� ����ö�� ������ �ִ´�.
		BusinessCard *index = updatingForm->businessCardBinder->Put(businessCard);
		updatingForm->Insert(&businessCard);

		//2.2.4 ����ö �������� ����ö�� �ִ´�.
		Index *indexLink = updatingForm->indexBinder->Put(index);
		Index(*indexLinks);
		Long count;
		updatingForm->indexBinder->MakeList(&indexLinks, &count);
		((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->DeleteAllItems();
		HTREEITEM root = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem("ȸ���", NULL, TVI_ROOT);

		//2.2.5 ����ö �������� TreeControl�� ���� ������ ��ȣ�� ������ ��ȣ��带 ȸ��� ����� �ڽĳ��� �����.
		Long i = 0;
		BusinessCard getIndex;
		HTREEITEM parent;
		HTREEITEM child;
		while (i < count) {
			parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem(indexLinks[i].GetName().c_str(), root, TVI_LAST);
			Long length = indexLinks[i].GetLength();
			Long j = 0;
			while (j < length) {
				index = indexLinks[i].GetAt(j);
				child = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->InsertItem(index->GetName().c_str(), parent, TVI_LAST);
				j++;
			}
			i++;
		}

		//2.2.4 ����ö �������� ���Կ� ����Ѵ�.
		(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME))->SetWindowText(index->GetName().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION))->SetWindowText(index->GetPosition().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER))->SetWindowText(index->GetCellphoneNumber().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS))->SetWindowText(index->GetEmailAddress().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_NAME))->SetWindowText(index->GetCompanyName().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS))->SetWindowText(index->GetAddress().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER))->SetWindowText(index->GetTelephoneNumber().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER))->SetWindowText(index->GetFaxNumber().c_str());
		(updatingForm->GetDlgItem(IDC_STATIC_COMPANY_URL))->SetWindowText(index->GetUrl().c_str());

		indexLink = updatingForm->indexBinder->Find((LPCTSTR)companyName);
		Long subscript = indexLink->Find(index);
		root = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(0, TVGN_ROOT);
		parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(root, TVGN_CHILD);
		CString comparison = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
		while (comparison.Compare(companyName) != 0) {
			parent = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_NEXT);
			comparison = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetItemText(parent);
		}
		child = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(parent, TVGN_CHILD);
		i = 0;
		while (i < subscript) {
			child = ((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->GetNextItem(child, TVGN_NEXT);
			i++;
		}
		((CTreeCtrl*)(updatingForm->GetDlgItem(IDC_TREE_INDEXBINDER)))->SelectItem(child);

		//2.2.5 �����츦 �ݴ´�.
		this->EndDialog(0);
	}

	//2.3 "�ƴϿ�"��ư�� Ŭ������ ��
	else if (confirm == IDNO) {
		//2.3.1 �����츦 �ݴ´�.
		this->EndDialog(0);
	}
}