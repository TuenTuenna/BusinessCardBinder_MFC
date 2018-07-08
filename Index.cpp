// Index.cpp
#include "Index.h"

// Default ������
Index::Index(Long capacity)
	:businessCards(capacity), name("") {
	this->capacity = capacity;
	this->length = 0;
}

// �Ű������� ���� ������
Index::Index(string name, Long capacity)
	:businessCards(capacity), name(name) {
	this->capacity = capacity;
	this->length = 0;
}

// ���� ������
Index::Index(const Index& source)
	:businessCards(source.businessCards), name(source.name) {
	this->capacity = source.capacity;
	this->length = source.length;
}

// ġȯ ������
Index& Index::operator =(const Index& source) {
	this->businessCards = source.businessCards;
	this->length = source.length;
	this->capacity = source.capacity;
	this->name = source.name;
	return *this;
}

// ġȯ ������
BusinessCard* Index::operator [](Long subscript) {
	return this->businessCards[subscript];
}

// �Ҹ���
Index::~Index() {
}

// Put
Long Index::Put(BusinessCard *index) {
	Long subscript;
	if (this->length < this->capacity) {
		subscript = this->businessCards.Store(this->length, index);
	}
	else {
		subscript = this->businessCards.AppendFromRear(index);
		this->capacity++;
	}
	this->length++;
	return subscript;
}

// Draw
Long Index::Draw(Long subscript) {
	subscript = this->businessCards.Delete(subscript);
	this->capacity--;
	this->length--;
	return subscript;
}

// Find
Long Index::Find(BusinessCard *index) {
	Long subscript = this->businessCards.LinearSearchUnique(index, ComparePointers);
	return subscript;
}
// GetAt
BusinessCard* Index::GetAt(Long subscript) {
	return this->businessCards.GetAt(subscript);
}

// ���Լ�
int ComparePointers(void *one, void *other) {
	int ret;
	if (*(static_cast<BusinessCard**>(one)) == other) {
		ret = 0;
	}
	else if (*(static_cast<BusinessCard**>(one)) > other) {
		ret = 1;
	}
	else if (*(static_cast<BusinessCard**>(one)) < other) {
		ret = -1;
	}
	return ret;
}