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
main 시나리오
1. 명함철을 만든다.
2. "홍길동","회장","02","hong@","박컴","서울시","021","022","park.com"명함을 만든다.
3. 명함철에 넣는다.
4. "김길동","과장","03","kim@","박컴","서울시","021","022","park.com"명함을 만든다.
5. 명함철에 넣는다.
6. "홍길동","사원","04","dong@","박컴","서울시","021","022","park.com"명함을 만든다.
7. 명함철에 넣는다.
8. "홍길동"을 찾는다.
9. 첫 번째 카드를 뽑는다.
10. 명함철에 넣는다.
11. 처음 명함의 위치를 확인한다.
12. 이전 명함의 위치를 확인한다. //underflow 확인
13. 마지막 명함의 위치를 확인한다.
14. 다음 명함의 위치를 확인한다. //overflow확인
15.명함철을 없앤다.
*/


int main(int argc, char *argv[]) {
	BusinessCardBinder businessCardBinder;
	IndexBinder indexBinder;

	cout << "홍길동 명함 입력/출력" << endl;
	BusinessCard hong("홍길동", "회장", "02", "hong@", "박컴", "서울시", "021", "022", "park.com");
	BusinessCard *link = businessCardBinder.Put(hong);
	cout << link->GetName() <<"	"<< link->GetPosition() <<"	"<< link->GetCellphoneNumber() <<"	"<< link->GetEmailAddress() <<"	"<< link->GetCompanyName() <<"	"<< link->GetAddress() <<"	"<< link->GetTelephoneNumber() <<"	"<< link->GetFaxNumber() <<"	"<< link->GetUrl() << endl;


	cout << "홍길동 명함 색인" << endl;
	Index *indexLink = indexBinder.Put(link);
	cout << indexLink->GetName() << endl;
	BusinessCard *businessCardLink;
	businessCardLink = indexLink->GetAt(0);
	cout << businessCardLink->GetName() << endl;

	BusinessCard kim("김길동", "과장", "03", "kim@", "박컴", "서울시", "021", "022", "park.com");
	link = businessCardBinder.Put(kim);
	cout << link->GetName() << "	" << link->GetPosition() << "	" << link->GetCellphoneNumber() << "	" << link->GetEmailAddress() << "	" << link->GetCompanyName() << "	" << link->GetAddress() << "	" << link->GetTelephoneNumber() << "	" << link->GetFaxNumber() << "	" << link->GetUrl() << endl;
	
	cout << "김길동 명함 색인" << endl;
	indexLink = indexBinder.Put(link);
	cout << indexLink->GetName() << endl;

	BusinessCard hong2("홍길동", "사원", "04", "dong@", "삼성", "서울시", "021", "022", "park.com");
	link = businessCardBinder.Put(hong2);
	cout << link->GetName() << "	" << link->GetPosition() << "	" << link->GetCellphoneNumber() << "	" << link->GetEmailAddress() << "	" << link->GetCompanyName() << "	" << link->GetAddress() << "	" << link->GetTelephoneNumber() << "	" << link->GetFaxNumber() << "	" << link->GetUrl() << endl;

	cout << "홍길동2 명함 색인" << endl;
	indexLink = indexBinder.Put(link);
	cout << indexLink->GetName() << endl;

	BusinessCard park("박길동", "사장", "062", "park@", "현대", "울산", "0521", "0522", "hcom");
	link = businessCardBinder.Put(park);
	cout << link->GetName() << "	" << link->GetPosition() << "	" << link->GetCellphoneNumber() << "	" << link->GetEmailAddress() << "	" << link->GetCompanyName() << "	" << link->GetAddress() << "	" << link->GetTelephoneNumber() << "	" << link->GetFaxNumber() << "	" << link->GetUrl() << endl;
	
	cout << "박길동 명함 색인" << endl;
	indexLink = indexBinder.Put(link);
	cout << indexLink->GetName() << endl;

	cout << "홍길동을 찾는다" << endl;
	BusinessCard **(indexes);
	Long count;
	businessCardBinder.Find("홍길동", &indexes, &count);
	Long i = 0;
	while (i < count) {
		cout << indexes[i]->GetName() << "	" << indexes[i]->GetPosition() << "	" << indexes[i]->GetCellphoneNumber() << "	" << indexes[i]->GetEmailAddress() << "	" << indexes[i]->GetCompanyName() << "	" << indexes[i]->GetAddress() << "	" << indexes[i]->GetTelephoneNumber() << "	" << indexes[i]->GetFaxNumber() << "	" << indexes[i]->GetUrl() << endl;
		i++;
	}

	if (indexes != 0) {
		delete[] indexes;
		indexes = 0;

	}

	cout << "박컴을 찾는다" << endl;
	indexLink = indexBinder.Find("박컴");
	cout << indexLink->GetLength() << endl;
	i = 0;
	while (i < indexLink->GetLength()) {
		BusinessCard *index = indexLink->GetAt(i);
		cout << i + 1 << index->GetName() << index->GetCompanyName() << endl;
		i++;
	}

	BusinessCard *index = businessCardBinder.Last();
	BusinessCard businessCard = businessCardBinder.Draw(index);
	cout << "마지막명함 Draw" << endl;
	cout << businessCard.GetName() << "," << businessCard.GetCompanyName() << endl;

	indexLink = indexBinder.Draw(index, businessCard.GetCompanyName());
	if (indexLink == 0) {
		cout << "색인이 지워졋습니다." << endl;
	}

	cout << "명함철에 넣는다" << endl;
	index = businessCardBinder.Put(businessCard);
	cout << index->GetName() << "," << index->GetCompanyName() << endl;

	cout << "색인철에 넣는다" << endl;
	indexLink = indexBinder.Put(index);
	cout << indexLink->GetName() << endl;

	cout << "색인철을 정리한다" << endl;
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
	cout << "색인철에서 확인한다" << endl;
	indexLink = indexBinder.Find(index->GetCompanyName());
	Long subscript = indexLink->Find(index);
	cout << index->GetName() << "," << index->GetCompanyName() << endl;

	/*
	businessCardBinder.Find("홍길동", &indexes, &count);
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