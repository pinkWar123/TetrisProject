#pragma once
#include <vector>
#include <string>
// This is the class that defines a basic TrieNode

class TrieNode
{
private:
	bool isEndOfWord;
	std::vector<std::string> meanings;
	
public:
	TrieNode* child[128];
	// Constructor

	TrieNode();
	virtual ~TrieNode();

	TrieNode* getChild(int idx);
	void setChild(int idx);

	bool getIsEndOfWord();
	void setIsEndOfWord(bool b);

	std::vector<std::string> getMeanings();

	void setMeanings(std::vector<std::string> meanings);

	static TrieNode* makeNode();
};

