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

    //std::wcout << L"\nLast Five Bigram Frequencies:\n";
    //for (size_t i = start; i < numBigrams; ++i) {
    //    int bigramNumber = afin.convertBigramToNumber(sortedBigrams[i].first, m);
    //    std::wcout << sortedBigrams[i].first << L": " << sortedBigrams[i].second
    //        << L" (Number: " << bigramNumber << L")\n";
    //}

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

    int totalKeys = 0;

    // Check combinations avoiding (X, Y) = (X*, Y*)
    for (size_t i = 0; i < plainBigrams.size(); ++i) {
        for (size_t j = 0; j < cipherBigrams.size(); ++j) {
            for (size_t k = i + 1; k < plainBigrams.size(); ++k) {
                for (size_t l = j + 1; l < cipherBigrams.size(); ++l) {
                    // X, Y and X*, Y* must be different
                    auto candidates = afin.findKeyCandidates(
                        plainBigrams[i].second, cipherBigrams[j].second,
                        plainBigrams[k].second, cipherBigrams[l].second, m);

                    totalKeys += candidates.size();
                    // Output the key candidates
                    for (const auto& candidate : candidates) {
                        std::wcout << L"From " << plainBigrams[i].first << L"->" << cipherBigrams[j].first
                            << L" and " << plainBigrams[k].first << L"->" << cipherBigrams[l].first
                            << L" Possible Key: a=" << candidate.first << L", b=" << candidate.second << std::endl;
                    }
                }
            }
        }
    }
    std::cout << "Total key candidates generated: " << totalKeys << std::endl;

    return 0;
}