#include "TrieNode.h"

TrieNode::TrieNode()
{
	isEndOfWord = false;
	for (int i = 0; i < 128; i++)
	{
		child[i] = NULL;
	}
}

TrieNode::~TrieNode()
{
	for (int i = 0; i < 128; i++)
	{
		delete child[i];
	}
	delete this;
}

TrieNode* TrieNode::getChild(int idx)
{
	return child[idx];
}

void TrieNode::setChild(int idx)
{
	child[idx] = makeNode();
}

bool TrieNode::getIsEndOfWord()
{
	return isEndOfWord;
}

void TrieNode::setIsEndOfWord(bool b)
{
	isEndOfWord = b;
}

std::vector<std::string> TrieNode::getMeanings()
{
	return meanings;
}

void TrieNode::setMeanings(std::vector<std::string> meanings)
{
	this->meanings = meanings;
}

TrieNode* TrieNode::makeNode()
{
	TrieNode* t = new TrieNode();
	return t;
}
