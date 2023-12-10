#pragma once
#include "TrieNode.h"
#include "json.hpp"
#include <fstream>
// This class defines a basic dictionary

using json = nlohmann::json;

class Dictionary
{
private:
	TrieNode* root;
	std::string source; // This is the source from which the dictionary gets data
	
	int numberOfWords;
	const int numberOfSuggestions = 10;

	void InstallLibrary();
	void RecursiveSuggest(TrieNode* root, std::vector<std::string>& res, std::string prefix, int& count);
public:
	Dictionary(std::string source,int numberOfWords);
	virtual ~Dictionary();

	void InsertNewWord(std::string word, std::vector<std::string> meanings);
	
	std::vector<std::string> Search(std::string word);

	void DeleteWord();

	std::vector<std::string> getSuggestion(std::string);

	
};

