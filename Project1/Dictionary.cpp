#include "Dictionary.h"
#include <iostream>
void Dictionary::InstallLibrary()
{
	std::ifstream is(source);
	
	json obj = json::parse(is);
	int num = 0;
	for (auto it : obj.items())
	{
		++num;
		if (num > numberOfWords) break;
		std::string word = it.key();
		std::vector<std::string> meanings = it.value();
		InsertNewWord(word, meanings);
	}

	is.close();

}

Dictionary::Dictionary(std::string source, int numberOfWords)
{
	root = new TrieNode();

	this->source = source;
	this->numberOfWords = numberOfWords;

	InstallLibrary();
}

Dictionary::~Dictionary()
{
	//TO DO
}

void Dictionary::InsertNewWord(std::string word, std::vector<std::string> meanings)
{
	for (int i = 0; i < word.size(); i++)
	{
		if (word[i] < 0 || word[i]>127) return;
	}
	TrieNode* tmp = root;
	for (int i = 0; i < word.size(); i++)
	{
		int idx = word[i];
		if (!tmp->child[idx])
		{
			tmp->child[idx] = TrieNode::makeNode();
		}
		tmp = tmp->child[idx];
	}
	tmp->setIsEndOfWord(true);
	tmp->setMeanings(meanings);
}

std::vector<std::string> Dictionary::Search(std::string word)
{
	std::vector<std::string> res;
	TrieNode* tmp = root;
	for (int i = 0; i < word.size(); i++)
	{
		int idx = word[i];
		if (!tmp->getChild(idx)) return res;
		tmp = tmp->getChild(idx);
	}
	
	for (int i = 0; i < tmp->getMeanings().size(); i++)
	{
		res.push_back(tmp->getMeanings()[i]);
	}
	return res;
}

void Dictionary::DeleteWord()
{
	// TO DO
}

std::vector<std::string> Dictionary::getSuggestion(std::string prefix)
{
	TrieNode* tmp = root;
	std::vector<std::string> res;
	if (prefix.empty()) return res;
	for (auto c : prefix)
	{
		if (tmp->child[c])
		{
			tmp = tmp->child[c];
		}
		else return res;
	}

	int count = 0;
	RecursiveSuggest(tmp, res, prefix, count);
	return res;
}

void Dictionary::RecursiveSuggest(TrieNode* root, std::vector<std::string>& res, std::string prefix, int &count)
{
	if (count == numberOfSuggestions) return;
	if (root->getIsEndOfWord())
	{
		res.push_back(prefix);
		++count;
	}
	for (int i = 0; i < 128; i++)
	{
		if (root->child[i])
		{
			RecursiveSuggest(root->child[i], res, prefix + (char)i, count);
		}
	}
}


