//IndexBinder.cpp
#include "IndexBinder.h"
#include "BusinessCard.h"

IndexBinder::IndexBinder() {
	this->length = 0;
}
IndexBinder::IndexBinder(const IndexBinder& source)
	:indexes(source.indexes) {
	this->length = source.length;
}
IndexBinder& IndexBinder::operator = (const IndexBinder& source) {
	this->indexes = source.indexes;
	this->length = source.length;
	return *this;
}

IndexBinder::~IndexBinder() {

}

Index* IndexBinder::Put(BusinessCard *index) {  //if문, 세미콜론 수정
	
	Index key(index->GetCompanyName(), 256);
	BinaryTree<Index>::Node* nodeLink = this->indexes.Search(key, CompareKeys);
	if (nodeLink == 0) {
		nodeLink = this->indexes.Insert(key, CompareKeys);
	}
	Index *indexLink = &(nodeLink->GetKey());
	indexLink->Put(index);
	return indexLink;
}

Index* IndexBinder::Draw(BusinessCard *index, string companyName) {
	Index key(companyName);
	BinaryTree<Index>::Node* nodeLink = this->indexes.Search(key, CompareKeys);
	Index* indexLink = &(nodeLink->GetKey());
	Long subscript = indexLink->Find(index);
	Long temp = indexLink->Draw(subscript);
	Long length = indexLink->GetLength();
	if (length == 0) {
		nodeLink = this->indexes.Delete(key, CompareKeys);
		this->length--;
		indexLink = 0;
	}
	return indexLink;
}

void IndexBinder::Arrange() {
	this->indexes.MakeBalance();
}

void IndexBinder::MakeList(Index* (*keys), Long *count) {
	this->indexes.MakeKeys(keys, count);
}

Index* IndexBinder::Find(string companyName) {
	Index *indexLink = 0;
	Index key(companyName, 256);
	BinaryTree<Index>::Node *nodeLink = this->indexes.Search(key, CompareKeys);
	if (nodeLink != 0) {
		indexLink = &(nodeLink->GetKey());

	}
	return indexLink;
}

int CompareKeys(void *one, void *other) {
	return (static_cast<Index*>(one))->GetName().compare(static_cast<Index*>(other)->GetName());
}