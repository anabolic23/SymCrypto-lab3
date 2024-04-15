#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <cctype> 
#include <locale>
#include <codecvt>
#include <map>
#include <regex>
#include <vector>
#include <cassert>

class Afin {
private:
	std::wifstream inputFile;
	std::wofstream outputFile;
	std::string inputFileName;
	std::map<std::wstring, int> bigramCounts;
	std::wstring alphabet;
	std::map<wchar_t, int> alphabetIndex;

public:
	Afin();
	void CountBigrams(int step); 
	const std::map<std::wstring, int>& getBigramsCounts() const {
		return bigramCounts;
	}
	int gcd(int a, int b);
	int inverseModulo(int a, int mod);
	std::vector<int> solveLinearComparisons(int a, int b, int n);
	int convertBigramToNumber(const std::wstring& bigram, int m);
	std::vector<std::pair<int, int>> findKeyCandidates(int X, int Y, int X_star, int Y_star, int m);

	void decodeFile(const std::string& inputFilePath, const std::string& outputFilePath, int a, int b, int m);
	std::wstring decodeBigram(int y, int a, int b, int m);
	std::wstring numberToBigram(int num, int m);

};

bool cmp(std::pair<std::wstring, int>& a, std::pair<std::wstring, int>& b);
std::vector<std::pair<std::wstring, int>> sort(std::map<std::wstring, int>& M); 

