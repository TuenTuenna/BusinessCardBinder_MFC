// Personal.cpp

#include "Personal.h"

Personal::Personal()
	:name(""), position(""), cellphoneNumber(""), emailAddress("") {
}
Personal::Personal(string name, string position, string cellphoneNumber, string emailAddress)
	: name(name), position(position), cellphoneNumber(cellphoneNumber), emailAddress(emailAddress) {
}
Personal::Personal(const Personal& source):name(source.name),position(source.position),cellphoneNumber(source.cellphoneNumber),emailAddress(source.emailAddress){
}
Personal::~Personal() {
}
bool Personal::IsEqual(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) == 0 && this->position.compare(other.position) == 0 &&
		this->cellphoneNumber.compare(other.cellphoneNumber) == 0 && this->emailAddress.compare(other.emailAddress) == 0) {
		ret = true;
	}
	return ret;
}
bool Personal::IsNotEqual(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) != 0 || this->position.compare(other.position) != 0 ||
		this->cellphoneNumber.compare(other.cellphoneNumber) != 0 || this->emailAddress.compare(other.emailAddress) != 0) {
		ret = true;
	}
	return ret;
}
Personal& Personal::operator =(const Personal& source) {
	this->name = source.name;
	this->position = source.position;
	this->cellphoneNumber = source.cellphoneNumber;
	this->emailAddress = source.emailAddress;
	return *this;
}
bool Personal::operator ==(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) == 0 && this->position.compare(other.position) == 0 &&
		this->cellphoneNumber.compare(other.cellphoneNumber) == 0 && this->emailAddress.compare(other.emailAddress) == 0) {
		ret = true;
	}
	return ret;
}
bool Personal::operator !=(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) != 0 || this->position.compare(other.position) != 0 ||
		this->cellphoneNumber.compare(other.cellphoneNumber) != 0 || this->emailAddress.compare(other.emailAddress) != 0) {
		ret = true;
	}
	return ret;
}