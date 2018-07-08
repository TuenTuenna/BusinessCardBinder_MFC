#pragma once
//IndexBinder.h
#ifndef _INDEXBINDER_H
#define _INDEXBINDER_H
#include <string>
#include "BinaryTree.h"
#include "Index.h"
using namespace std;
typedef signed long int Long;

class BusinessCard;
class IndexBinder {
public:
	IndexBinder();
	IndexBinder(const IndexBinder& source);
	~IndexBinder();
	Index* Put(BusinessCard *index);
	Index* Draw(BusinessCard *index, string companyName);
	void Arrange();
	Index* Find(string companyName);
	void MakeList(Index* (*keys), Long *count);
	IndexBinder& operator = (const IndexBinder& source);
	Long GetLength() const;
private:
	BinaryTree<Index> indexes;
	Long length;
};
inline Long IndexBinder::GetLength() const {
	return this->length;
}
int CompareKeys(void* one, void* other);
#endif //_INDEXBINDER_H
