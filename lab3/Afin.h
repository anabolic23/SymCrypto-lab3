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
	std::wstring alphabet;
	std::map<wchar_t, int> alphabetIndex;
	std::map<wchar_t, int> letterCounts;
	std::map<wchar_t, double> letterProbabilities;
	std::map<std::wstring, int> bigramCounts;
	std::map<std::wstring, double> bigramProbabilities;

public:
	Afin();
	void CountLetters(const std::string& inputFileName);
	const std::map<wchar_t, int>& getLetterCounts() const {
		return letterCounts;
	}

	const std::map<wchar_t, double>& getLetterProbabilities() const {
		return letterProbabilities;
	}
	void CalculateLetterProbabilities();

	void CountBigrams(int step); 
	const std::map<std::wstring, int>& getBigramsCounts() const {
		return bigramCounts;
	}
	const std::map<std::wstring, double>& getBigramsProbabilities() const {
		return bigramProbabilities;
	}
	void CalculateBigramsProbabilities();

	int gcd(int a, int b);
	int inverseModulo(int a, int mod);
	std::vector<int> solveLinearComparisons(int a, int b, int n);
	int convertBigramToNumber(const std::wstring& bigram, int m);

	std::vector<std::pair<int, int>> findKeyCandidates(int X, int Y, int X_star, int Y_star, int m);
	void findAndOutputKeyCandidates(Afin& afin, const std::vector<std::pair<std::wstring, int>>& plainBigrams, const std::vector<std::pair<std::wstring, int>>& cipherBigrams, int m);
	
	/*bool compareLetterProbabilities(const std::map<wchar_t, double>& actualProbabilities);
	bool isWithinMargin(double actual, double target, double margin);*/

	void decodeFile(const std::string& inputFilePath, const std::string& outputFilePath, int a, int b, int m);
	std::wstring decodeBigram(int y, int a, int b, int m);
	std::wstring numberToBigram(int num, int m);

	double CalculateI(const std::string& fileName);
	bool CalculateAndCompareI(const std::string& fileName, double margin);
};

bool cmp(std::pair<std::wstring, int>& a, std::pair<std::wstring, int>& b);
std::vector<std::pair<std::wstring, int>> sort(std::map<std::wstring, int>& M); 

