//BusinessCardBinder.cpp

#include "BusinessCardBinder.h"
#include "IndexBinder.h"
#include <iostream>
using namespace std;

BusinessCardBinder::BusinessCardBinder(){
	this->length = 0;
	this->current = 0;
}

BusinessCardBinder::BusinessCardBinder(const BusinessCardBinder& source) : businessCards(source.businessCards){
	this->length = source.length;
	this->current=&(this->businessCards.GetCurrent()->GetObject());
}

BusinessCardBinder::~BusinessCardBinder() {
}

BusinessCard* BusinessCardBinder::Put(BusinessCard businessCard) {
	LinkedList<BusinessCard>::Node *node = this->businessCards.AppendFromTail(businessCard);
	this->current = &node->GetObject();
	this->length++;
	return this->current;
}

void BusinessCardBinder::Find(string name, BusinessCard**(*indexes), Long *count) {
	LinkedList<BusinessCard>::Node *(*nodes);
	*indexes = new BusinessCard*[this->length];
	this->businessCards.LinearSearchDuplicate(&name, &nodes, count, CompareNames);
	Long i = 0;
	while (i < *count) {
		(*indexes)[i] = &(nodes[i]->GetObject());
		i++;
	}
	if (nodes != 0) {
		delete[] nodes;
	}
}

BusinessCard BusinessCardBinder::Draw(BusinessCard* index) {
	LinkedList<BusinessCard>::Node *node;
	node = this->businessCards.LinearSearchUnique(index, CompareIndexes);
	BusinessCard businessCard = node->GetObject();
	this->businessCards.Delete(node);
	if (this->businessCards.GetLength() > 0) {
		this->current = &(this->businessCards.GetCurrent()->GetObject());
	}
	else {
		this->current = 0;
	}
	this->length--;
	return businessCard;
}

BusinessCard* BusinessCardBinder::FindByCompanyNmae(string companyName) {
	BusinessCard *index = 0;
	LinkedList<BusinessCard>::Node *node = this->businessCards.LinearSearchUnique(&companyName, CompareCompanyNames);
	if (node != 0) {
		index = &(node->GetObject());
	}
	return index;
}


BusinessCard* BusinessCardBinder::First() {
	LinkedList<BusinessCard>::Node *node = this->businessCards.First();
	this->current = &(node->GetObject());

	return this->current;
}

BusinessCard* BusinessCardBinder::Previous() {
	LinkedList<BusinessCard>::Node *node = this->businessCards.Previous();
	this->current = &(node->GetObject());

	return this->current;
}

BusinessCard* BusinessCardBinder::Next() {
	LinkedList<BusinessCard>::Node *node = this->businessCards.Next();
	this->current = &(node->GetObject());

	return this->current;
}

BusinessCard* BusinessCardBinder::Last() {
	LinkedList<BusinessCard>::Node *node = this->businessCards.Last();
	this->current = &(node->GetObject());

	return this->current;
}

BusinessCard* BusinessCardBinder::Move(BusinessCard *index) {
	LinkedList<BusinessCard>::Node *node = this->businessCards.LinearSearchUnique(index,CompareIndexes);
	node = this->businessCards.Move(node);
	this->current = &(node->GetObject());

	return this->current;
}

BusinessCardBinder& BusinessCardBinder::operator=(const BusinessCardBinder& source) {
	this->businessCards = source.businessCards;
	this->length = source.length;
	this->current = &(this->businessCards.GetCurrent()->GetObject());
	return *this;
}


//main

/*
main �ó�����
1. ����ö�� �����.
2. "ȫ�浿","ȸ��","02","hong@","����","�����","021","022","park.com"������ �����.
3. ����ö�� �ִ´�.
4. "��浿","����","03","kim@","����","�����","021","022","park.com"������ �����.
5. ����ö�� �ִ´�.
6. "ȫ�浿","���","04","dong@","����","�����","021","022","park.com"������ �����.
7. ����ö�� �ִ´�.
8. "ȫ�浿"�� ã�´�.
9. ù ��° ī�带 �̴´�.
10. ����ö�� �ִ´�.
11. ó�� ������ ��ġ�� Ȯ���Ѵ�.
12. ���� ������ ��ġ�� Ȯ���Ѵ�. //underflow Ȯ��
13. ������ ������ ��ġ�� Ȯ���Ѵ�.
14. ���� ������ ��ġ�� Ȯ���Ѵ�. //overflowȮ��
15.����ö�� ���ش�.
*/


int main(int argc, char *argv[]) {
	BusinessCardBinder businessCardBinder;
	IndexBinder indexBinder;

	cout << "ȫ�浿 ���� �Է�/���" << endl;
	BusinessCard hong("ȫ�浿", "ȸ��", "02", "hong@", "����", "�����", "021", "022", "park.com");
	BusinessCard *link = businessCardBinder.Put(hong);
	cout << link->GetName() <<"	"<< link->GetPosition() <<"	"<< link->GetCellphoneNumber() <<"	"<< link->GetEmailAddress() <<"	"<< link->GetCompanyName() <<"	"<< link->GetAddress() <<"	"<< link->GetTelephoneNumber() <<"	"<< link->GetFaxNumber() <<"	"<< link->GetUrl() << endl;


	cout << "ȫ�浿 ���� ����" << endl;
	Index *indexLink = indexBinder.Put(link);
	cout << indexLink->GetName() << endl;
	BusinessCard *businessCardLink;
	businessCardLink = indexLink->GetAt(0);
	cout << businessCardLink->GetName() << endl;

	BusinessCard kim("��浿", "����", "03", "kim@", "����", "�����", "021", "022", "park.com");
	link = businessCardBinder.Put(kim);
	cout << link->GetName() << "	" << link->GetPosition() << "	" << link->GetCellphoneNumber() << "	" << link->GetEmailAddress() << "	" << link->GetCompanyName() << "	" << link->GetAddress() << "	" << link->GetTelephoneNumber() << "	" << link->GetFaxNumber() << "	" << link->GetUrl() << endl;
	
	cout << "��浿 ���� ����" << endl;
	indexLink = indexBinder.Put(link);
	cout << indexLink->GetName() << endl;

	BusinessCard hong2("ȫ�浿", "���", "04", "dong@", "�Ｚ", "�����", "021", "022", "park.com");
	link = businessCardBinder.Put(hong2);
	cout << link->GetName() << "	" << link->GetPosition() << "	" << link->GetCellphoneNumber() << "	" << link->GetEmailAddress() << "	" << link->GetCompanyName() << "	" << link->GetAddress() << "	" << link->GetTelephoneNumber() << "	" << link->GetFaxNumber() << "	" << link->GetUrl() << endl;

	cout << "ȫ�浿2 ���� ����" << endl;
	indexLink = indexBinder.Put(link);
	cout << indexLink->GetName() << endl;

	BusinessCard park("�ڱ浿", "����", "062", "park@", "����", "���", "0521", "0522", "hcom");
	link = businessCardBinder.Put(park);
	cout << link->GetName() << "	" << link->GetPosition() << "	" << link->GetCellphoneNumber() << "	" << link->GetEmailAddress() << "	" << link->GetCompanyName() << "	" << link->GetAddress() << "	" << link->GetTelephoneNumber() << "	" << link->GetFaxNumber() << "	" << link->GetUrl() << endl;
	
	cout << "�ڱ浿 ���� ����" << endl;
	indexLink = indexBinder.Put(link);
	cout << indexLink->GetName() << endl;

	cout << "ȫ�浿�� ã�´�" << endl;
	BusinessCard **(indexes);
	Long count;
	businessCardBinder.Find("ȫ�浿", &indexes, &count);
	Long i = 0;
	while (i < count) {
		cout << indexes[i]->GetName() << "	" << indexes[i]->GetPosition() << "	" << indexes[i]->GetCellphoneNumber() << "	" << indexes[i]->GetEmailAddress() << "	" << indexes[i]->GetCompanyName() << "	" << indexes[i]->GetAddress() << "	" << indexes[i]->GetTelephoneNumber() << "	" << indexes[i]->GetFaxNumber() << "	" << indexes[i]->GetUrl() << endl;
		i++;
	}

	if (indexes != 0) {
		delete[] indexes;
		indexes = 0;

	}

	cout << "������ ã�´�" << endl;
	indexLink = indexBinder.Find("����");
	cout << indexLink->GetLength() << endl;
	i = 0;
	while (i < indexLink->GetLength()) {
		BusinessCard *index = indexLink->GetAt(i);
		cout << i + 1 << index->GetName() << index->GetCompanyName() << endl;
		i++;
	}

	BusinessCard *index = businessCardBinder.Last();
	BusinessCard businessCard = businessCardBinder.Draw(index);
	cout << "���������� Draw" << endl;
	cout << businessCard.GetName() << "," << businessCard.GetCompanyName() << endl;

	indexLink = indexBinder.Draw(index, businessCard.GetCompanyName());
	if (indexLink == 0) {
		cout << "������ ���������ϴ�." << endl;
	}

	cout << "����ö�� �ִ´�" << endl;
	index = businessCardBinder.Put(businessCard);
	cout << index->GetName() << "," << index->GetCompanyName() << endl;

	cout << "����ö�� �ִ´�" << endl;
	indexLink = indexBinder.Put(index);
	cout << indexLink->GetName() << endl;

	cout << "����ö�� �����Ѵ�" << endl;
	indexBinder.Arrange();

	Index (*indexLinks);
	Long indexLinkCount;
	indexBinder.MakeList(&indexLinks, &indexLinkCount);

	i = 0;
	while (i < indexLinkCount) {
		cout << i + 1 << " " << indexLinks[i].GetName() << endl;
		i++;
	}

	if (indexLinks != 0) {
		delete[] indexLinks;
		indexLinks = 0;
	}
	
	index = businessCardBinder.First();
	cout << index->GetName() << ", " << index->GetCompanyName() << endl;
	cout << "����ö���� Ȯ���Ѵ�" << endl;
	indexLink = indexBinder.Find(index->GetCompanyName());
	Long subscript = indexLink->Find(index);
	cout << index->GetName() << "," << index->GetCompanyName() << endl;

	/*
	businessCardBinder.Find("ȫ�浿", &indexes, &count);
	Long i = 0;
	while (i < count) {
		cout << indexes[i]->GetName() << "	" << indexes[i]->GetPosition() << "	" << indexes[i]->GetCellphoneNumber() << "	" << indexes[i]->GetEmailAddress() << "	" << indexes[i]->GetCompanyName() << "	" << indexes[i]->GetAddress() << "	" << indexes[i]->GetTelephoneNumber() << "	" << indexes[i]->GetFaxNumber() << "	" << indexes[i]->GetUrl() << endl;
		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
		indexes = 0;
	}

	link = businessCardBinder.First();

	BusinessCard businessCard = businessCardBinder.Draw(link);
	cout << businessCard.GetName() <<"	"<< businessCard.GetPosition() <<"	"<< businessCard.GetCellphoneNumber() <<"	"<< businessCard.GetEmailAddress() <<"	"<< businessCard.GetCompanyName() <<"	"<< businessCard.GetAddress() <<"	"<< businessCard.GetFaxNumber() <<"	"<< businessCard.GetUrl() << endl;

	link = businessCardBinder.Put(businessCard);
	cout << link->GetName() << "	" << link->GetPosition() << "	" << link->GetCellphoneNumber() << "	" << link->GetEmailAddress() << "	" << link->GetCompanyName() << "	" << link->GetAddress() << "	" << link->GetTelephoneNumber() << "	" << link->GetFaxNumber() << "	" << link->GetUrl() << endl;

	link = businessCardBinder.First();
	cout << link->GetName() << "	" << link->GetPosition() << "	" << link->GetCellphoneNumber() << "	" << link->GetEmailAddress() << "	" << link->GetCompanyName() << "	" << link->GetAddress() << "	" << link->GetTelephoneNumber() << "	" << link->GetFaxNumber() << "	" << link->GetUrl() << endl;

	link = businessCardBinder.Previous();
	cout << link->GetName() << "	" << link->GetPosition() << "	" << link->GetCellphoneNumber() << "	" << link->GetEmailAddress() << "	" << link->GetCompanyName() << "	" << link->GetAddress() << "	" << link->GetTelephoneNumber() << "	" << link->GetFaxNumber() << "	" << link->GetUrl() << endl;

	link = businessCardBinder.Last();
	cout << link->GetName() << "	" << link->GetPosition() << "	" << link->GetCellphoneNumber() << "	" << link->GetEmailAddress() << "	" << link->GetCompanyName() << "	" << link->GetAddress() << "	" << link->GetTelephoneNumber() << "	" << link->GetFaxNumber() << "	" << link->GetUrl() << endl;

	link = businessCardBinder.Next();
	cout << link->GetName() << "	" << link->GetPosition() << "	" << link->GetCellphoneNumber() << "	" << link->GetEmailAddress() << "	" << link->GetCompanyName() << "	" << link->GetAddress() << "	" << link->GetTelephoneNumber() << "	" << link->GetFaxNumber() << "	" << link->GetUrl() << endl;
	*/
	return 0;
}

int CompareNames(void *one, void *other) {
	return((static_cast<BusinessCard*>(one))->GetName().compare(*(static_cast<string*>(other))));
}

int CompareCompanyNames(void *one, void *other) {
	return ((static_cast<BusinessCard*>(one))->GetCompanyName().compare(*(static_cast<string*>(other))));
}

int CompareIndexes(void *one, void *other) {
	int ret;
	if (one == other) {
		ret = 0;
	}
	else if (one > other) {
		ret = 1;
	}
	else if (one < other) {
		ret = -1;
	}
	return ret;
}