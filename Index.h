// index.h
#ifndef _INDEX_H
#define _INDEX_H
#include<string>
#include"Array.h"
using namespace std;
typedef signed long int Long;
class BusinessCard;

class Index {
public:
	Index(Long capacity = 256);
	Index(string name, Long capacity = 256);
	Index(const Index& source);
	Index& operator =(const Index& source);
	BusinessCard* operator [](Long subscript);
	~Index();
	Long Put(BusinessCard *index);
	Long Draw(Long subscript);
	Long Find(BusinessCard *index);
	BusinessCard* GetAt(Long subscript);
	string& GetName() const;
	Long GetCapacity() const;
	Long GetLength() const;
private:
	string name;
	Array<BusinessCard*> businessCards;
	Long capacity;
	Long length;
};

inline string& Index::GetName() const {
	return const_cast<string&>(this->name);
}
inline Long Index::GetCapacity() const {
	return this->capacity;
}
inline Long Index::GetLength() const {
	return this->length;
}

int ComparePointers(void *one, void * other);
#endif // _INDEX_H
