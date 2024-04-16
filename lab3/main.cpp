#include "Afin.h"
#include <windows.h>

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "");

    Afin afin;
    int m = 31;
    afin.CountBigrams(1);
    auto bigrams = afin.getBigramsCounts();
    auto sortedBigrams = sort(bigrams);
    size_t numBigrams = sortedBigrams.size();
    size_t start = numBigrams > 5 ? numBigrams - 5 : 0; 

    /*std::wcout << L"\nLast Five Bigram Frequencies:\n";
    for (size_t i = start; i < numBigrams; ++i) {
        int bigramNumber = afin.convertBigramToNumber(sortedBigrams[i].first, m);
        std::wcout << sortedBigrams[i].first << L": " << sortedBigrams[i].second
            << L" (Number: " << bigramNumber << L")\n";
    }*/

    //std::vector<std::wstring> specificBigrams = { L"ст", L"но", L"то", L"на", L"ен" };

    //std::wcout << L"\nSpecific Bigram Numerical Values:\n";
    //for (const auto& bigram : specificBigrams) {
    //    int bigramNumber = afin.convertBigramToNumber(bigram, m);
    //    std::wcout << L"Bigram '" << bigram << L"': " << bigramNumber << L"\n";
    //}

    //Example
    //std::wstring bigram = L"вб"; // Example bigram
    //int number = afin.convertBigramToNumber(bigram, m);
    //std::wcout << L"The number corresponding to bigram \"" << bigram << L"\" is " << number << std::endl;

   // Last five most frequent bigrams with their corresponding numerical values
    std::vector<std::pair<std::wstring, int>> cipherBigrams = {
        {L"оц", 456}, {L"нц", 425}, {L"жц", 208}, {L"цэ", 710}, {L"дэ", 152}
    };

    // Specific bigrams with their numerical values
    std::vector<std::pair<std::wstring, int>> plainBigrams = {
        {L"ст", 545}, {L"но", 417}, {L"то", 572}, {L"на", 403}, {L"ен", 168}
    };

    afin.CountLetters("input.txt");
    afin.CalculateLetterProbabilities();

    afin.findAndOutputKeyCandidates(afin, plainBigrams, cipherBigrams, m);

    int a = 17;
    int b = 94;

    afin.decodeFile("input.txt", "decoded.txt", a, b, m);

    std::cout << "Decoding completed." << std::endl;

    /*std::wcout << L"\nLetter Frequencies:\n";
    for (const auto& pair : afin.getLetterCounts()) {
        std::wcout << pair.first << L": " << pair.second << L"\n";
    }*/

    /*afin.CountBigrams(2);
    afin.CalculateBigramsProbabilities();

    std::wcout << L"\nBigram Frequencies:\n";
    for (const auto& pair : afin.getBigramsCounts()) {
        std::wcout << pair.first << L": " << pair.second << L"\n";
    }

    std::wcout << L"\nBigram Probabilities:\n";
    for (const auto& pair : afin.getBigramsProbabilities()) {
        std::wcout << pair.first << L": " << pair.second << L"\n";
    }*/

    return 0;
}