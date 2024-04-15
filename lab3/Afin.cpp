#include "Afin.h"

Afin::Afin() {
    alphabet = L"אבגדהוזחטיךכלםמןנסעףפץצקרשûü‎‏ÿ";
    // Map each letter to a number (0-based index)
    for (size_t i = 0; i < alphabet.size(); ++i) {
        alphabetIndex[alphabet[i]] = static_cast<int>(i);
    }
}

void Afin::CountBigrams(int step) {
    if (step != 1 && step != 2) {
        std::wcerr << L"Invalid step. Use 1 for overlapping bigrams or 2 for non-overlapping bigrams.\n";
        return;
    }
    inputFile.open("fortest.txt");

    inputFile.imbue(std::locale(inputFile.getloc(),
        new std::codecvt_utf8<wchar_t, 0x10ffff, std::little_endian>));
    if (!inputFile) {
        std::wcerr << L"Error: Unable to open the file for reading bigrams.\n";
        return;
    }

    std::wstring line;
    while (std::getline(inputFile, line)) {
        for (size_t i = 0; i < line.length() - 1; i += step) {
            std::wstring bigram = line.substr(i, 2);
            if (bigram.length() == 2) { 
                bigramCounts[bigram]++;
            }
        }
    }

    inputFile.close();

    this->bigramCounts = bigramCounts;
}


bool cmp(std::pair<std::wstring, int>& a, std::pair<std::wstring, int>& b){
    return a.second < b.second;
}

std::vector<std::pair<std::wstring, int>> sort(std::map<std::wstring, int>& M) {
    std::vector<std::pair<std::wstring, int>> sortedList;

    for (auto& item : M) {
        sortedList.push_back(item);
    }

    std::sort(sortedList.begin(), sortedList.end(), cmp);

    return sortedList;
}



int Afin::gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int Afin::inverseModulo(int a, int mod) {
    int r, q;
    int m0 = mod;
    int x0 = 0;
    int x1 = 1;
    if (mod == 1) {
        return 0;
    }
    while (a > 1) {
        q = a / mod;
        r = mod;
        mod = a % mod; 
           a = r;
        r = x0;
        x0 = x1 - q * x0;
        x1 = r;
    }

    if (x1 < 0) {
        x1 += m0;
    }

    return x1;
}

std::vector<int> Afin::solveLinearComparisons(int a, int b, int n) {
    std::vector<int> result;

    if (gcd(a, n) == 1) {
        int inverse = inverseModulo(a, n);
        result.push_back((inverse * b) % n);
        return result;
    }
    int d = gcd(a, n);
    if (b % d != 0) {
        return result;
    }
    else {
        int a1 = a / d;
        int b1 = b / d;
        int n1 = n / d;
        int x0 = solveLinearComparisons(a1, b1, n1)[0]; 
        for (int i = 0; i < d; ++i) {
            result.push_back(x0 + i * n1);
        }
        return result;
    }
}

int Afin::convertBigramToNumber(const std::wstring& bigram, int m) {
    if (bigram.size() != 2) {
        std::wcerr << L"Invalid bigram size." << std::endl;
        return -1; 
    }

    // Check if both characters are in the map
    auto find1 = alphabetIndex.find(bigram[0]);
    auto find2 = alphabetIndex.find(bigram[1]);
    if (find1 == alphabetIndex.end() || find2 == alphabetIndex.end()) {
        std::wcerr << L"Bigram contains characters not in the Russian alphabet." << std::endl;
        return -1; 
    }

    int x1 = find1->second;
    int x2 = find2->second;

    int X = (x1 * m + x2) % (m * m);
    
    return X;
}

std::vector<std::pair<int, int>> Afin::findKeyCandidates(int X, int Y, int X_star, int Y_star, int m) {
    std::vector<std::pair<int, int>> candidates;
    int m_squared = m * m;
    int deltaX = (X - X_star + m_squared) % m_squared;
    int deltaY = (Y - Y_star + m_squared) % m_squared;

    std::vector<int> possibleAs = solveLinearComparisons(deltaX, deltaY, m_squared);

    for (int a : possibleAs) {
        int b = (Y - (a * X) % m_squared + m_squared) % m_squared;
        candidates.push_back({ a, b });
    }

    return candidates;
}

void Afin::decodeFile(const std::string& inputFilePath, const std::string& outputFilePath, int a, int b, int m) {
    std::wifstream inputFile(inputFilePath);
    std::wofstream outputFile(outputFilePath);

    inputFile.imbue(std::locale(inputFile.getloc(), new std::codecvt_utf8<wchar_t>));
    outputFile.imbue(std::locale(outputFile.getloc(), new std::codecvt_utf8<wchar_t>));

    if (!inputFile) {
        std::wcerr << L"Error: Unable to open input file.\n";
        return;
    }

    if (!outputFile) {
        std::wcerr << L"Error: Unable to open output file.\n";
        return;
    }

    std::wstring line;
    while (std::getline(inputFile, line)) {
        for (size_t i = 0; i < line.length() - 1; i += 2) {  // Process by bigrams
            std::wstring bigram = line.substr(i, 2);
            int bigramNum = convertBigramToNumber(bigram, m);
            std::wstring decodedBigram = decodeBigram(bigramNum, a, b, m);
            outputFile << decodedBigram;
        }
        outputFile << std::endl; // Maintain line breaks
    }

    inputFile.close();
    outputFile.close();
}

std::wstring Afin::decodeBigram(int y, int a, int b, int m) {
    int a_inverse = inverseModulo(a, m * m);
    if (a_inverse == -1) {  // No inverse exists
        std::wcerr << L"No inverse exists for a=" << a << " under modulo " << m * m << std::endl;
        return L"";
    }
    int x = (a_inverse * (y - b + m * m)) % (m * m);
    return numberToBigram(x, m);
}

std::wstring Afin::numberToBigram(int num, int m) {
    int firstIndex = num / m;
    int secondIndex = num % m;
    if (firstIndex >= m || secondIndex >= m)
        return L"??";
    return std::wstring(1, alphabet[firstIndex]) + alphabet[secondIndex];
}
