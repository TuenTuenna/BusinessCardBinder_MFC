#ifndef _BUSINESSCARD_H
#define _BUSINESSCARD_H
#include "Personal.h"
#include "Company.h"
#include<string>
using namespace std;

class BusinessCard {
public:
	BusinessCard();
	BusinessCard(string name, string position, string cellphoneNumber, string emailAddress, string companyName, string address, string telephoneNumber, string faxNumber, string url);
	BusinessCard(const BusinessCard& source);
	~BusinessCard();
	bool IsEqual(const BusinessCard& other);
	bool IsNotEqual(const BusinessCard& other);
	BusinessCard& operator = (const BusinessCard& source);
	bool operator == (const BusinessCard& other);
	bool operator !=(const BusinessCard& other);
	string& GetName() const;
	string& GetPosition() const;
	string& GetCellphoneNumber() const;
	string& GetEmailAddress() const;
	string& GetCompanyName() const;
	string& GetAddress() const;
	string& GetTelephoneNumber() const;
	string& GetFaxNumber() const;
	string& GetUrl() const;
private:
	Personal personal;
	Company company;
};
inline string& BusinessCard::GetName() const {
	return const_cast<string&> (personal.GetName());
}
inline string& BusinessCard::GetPosition() const {
	return const_cast<string&> (personal.GetPosition());
}
inline string& BusinessCard::GetCellphoneNumber() const {
	return const_cast<string&> (personal.GetCellphoneNumber());
}
inline string& BusinessCard::GetEmailAddress() const {
	return const_cast<string&> (personal.GetEmailAddress());
}
inline string& BusinessCard::GetCompanyName() const {
	return const_cast<string&> (company.GetName());
}
inline string& BusinessCard::GetAddress() const {
	return const_cast<string&> (company.GetAddress());
}
inline string& BusinessCard::GetTelephoneNumber() const {
	return const_cast<string&> (company.GetTelephoneNumber());
}
inline string& BusinessCard::GetFaxNumber() const {
	return const_cast<string&> (company.GetFaxNumber());
}
inline string& BusinessCard::GetUrl() const {
	return const_cast<string&> (company.GetUrl());
}

#endif // _BUSINESSCARD_H
