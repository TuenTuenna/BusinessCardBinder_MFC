//BusinessCardBinder.h
#ifndef _BUSINESSCARDBINDER_H
#define _BUSINESSCARDBINDER_H
#include "BusinessCard.h"
#include "LinkedList.h"
#include <string>
using namespace std;

class BusinessCardBinder {
public:
	BusinessCardBinder();
	BusinessCardBinder(const BusinessCardBinder& source);
	~BusinessCardBinder();
	BusinessCard* Put(BusinessCard businessCard);
	void Find(string name, BusinessCard**(*indexes), Long *count);
	BusinessCard Draw(BusinessCard *index);
	BusinessCard* FindByCompanyNmae(string companyName);
	BusinessCard* Move(BusinessCard *index);
	BusinessCard* First();
	BusinessCard* Previous();
	BusinessCard* Next();
	BusinessCard* Last();
	Long GetLength() const;
	BusinessCard* GetCurrent() const;
	BusinessCardBinder& operator=(const BusinessCardBinder& source);

private:
	LinkedList<BusinessCard> businessCards;
	Long length;
	BusinessCard* current;
}; //BusinessCardBinder class

inline Long BusinessCardBinder::GetLength() const {
	return this->length;
}

inline BusinessCard* BusinessCardBinder::GetCurrent() const {
	return const_cast<BusinessCard*>(this->current);
}

int CompareIndexes(void *one, void *other);
int CompareNames(void *one, void *other);
int CompareCompanyNames(void *one, void *other);

#endif //_BUSINESSCARDBINDER_H