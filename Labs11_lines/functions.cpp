#include "functions.hpp"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <set>
#include <sstream>
#include <map>

std::vector<std::string> splitIntoWords(const std::string& text) {
    std::vector<std::string> words;
    std::string word;
    for (char ch : text) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += ch;
        }
        else {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

int maxIdenticalLettersCount(const std::string& word) {
    if (word.empty()) return 0;
    std::map<char, int> freq;
    for (char ch : word) {
        freq[ch]++;
    }
    int maxCount = 0;
    for (auto& p : freq) {
        if (p.second > maxCount) {
            maxCount = p.second;
        }
    }
    return maxCount;
}

void solveTask1(const std::string& inputFilename, const std::string& outputFilename, int N) {
    std::ifstream inFile(inputFilename);
    std::string text((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    std::vector<std::string> allWords = splitIntoWords(text);
    std::map<std::string, int> uniqueWords;
    for (const auto& w : allWords) {
        uniqueWords[w] = maxIdenticalLettersCount(w);
    }

    std::vector<std::pair<std::string, int>> wordList(uniqueWords.begin(), uniqueWords.end());
    std::sort(wordList.begin(), wordList.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
        });

    std::ofstream outFile(outputFilename);
    for (int i = 0; i < N && i < (int)wordList.size(); ++i) {
        outFile << wordList[i].first << " " << wordList[i].second << std::endl;
    }
    outFile.close();
}

bool hasLongPalindrome(const std::vector<std::string>& words) {
    for (const auto& w : words) {
        if (w.length() > 1) {
            bool isPal = true;
            for (size_t i = 0; i < w.length() / 2; ++i) {
                if (w[i] != w[w.length() - 1 - i]) {
                    isPal = false;
                    break;
                }
            }
            if (isPal) return true;
        }
    }
    return false;
}

int countConsonants(const std::string& word) {
    std::string consonants = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
    int count = 0;
    for (char ch : word) {
        if (consonants.find(ch) != std::string::npos) {
            count++;
        }
    }
    return count;
}

std::string duplicateVowels(const std::string& word) {
    std::string vowels = "aeiouAEIOU";
    std::string result;
    for (char ch : word) {
        result += ch;
        if (vowels.find(ch) != std::string::npos) {
            result += ch;
        }
    }
    return result;
}

std::vector<std::string> processTask2(const std::string& text) {
    std::vector<std::string> words = splitIntoWords(text);
    std::vector<std::string> result;

    if (!hasLongPalindrome(words)) {
        std::vector<std::pair<std::string, int>> wordConsonants;
        for (const auto& w : words) {
            wordConsonants.push_back({ w, countConsonants(w) });
        }
        std::sort(wordConsonants.begin(), wordConsonants.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
            });
        for (const auto& p : wordConsonants) {
            result.push_back(p.first);
        }
    }
    else {
        for (const auto& w : words) {
            result.push_back(duplicateVowels(w));
        }
        std::sort(result.begin(), result.end(), std::greater<std::string>());
    }
    return result;
}

std::map<char, int> countLetterFrequency(const std::string& text) {
    std::map<char, int> freq;
    for (char ch : text) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            freq[std::tolower(ch)]++;
        }
    }
    return freq;
}

std::vector<char> getTop5Letters(const std::string& text) {
    std::map<char, int> freq = countLetterFrequency(text);
    std::vector<std::pair<char, int>> freqVec(freq.begin(), freq.end());
    std::sort(freqVec.begin(), freqVec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });
    std::vector<char> top5;
    for (int i = 0; i < 5 && i < (int)freqVec.size(); ++i) {
        top5.push_back(freqVec[i].first);
    }
    return top5;
}

bool containsAtLeastFourOf(const std::string& word, const std::vector<char>& topLetters) {
    std::set<char> uniqueTop(topLetters.begin(), topLetters.end());
    std::set<char> found;
    for (char ch : word) {
        char lower = std::tolower(ch);
        if (uniqueTop.count(lower)) {
            found.insert(lower);
        }
    }
    return found.size() >= 4;
}

std::string toUpper(const std::string& word) {
    std::string result = word;
    for (char& ch : result) {
        ch = std::toupper(ch);
    }
    return result;
}

void solveTask3(const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream inFile(inputFilename);
    std::string text((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    std::vector<char> top5 = getTop5Letters(text);
    std::set<char> topSet(top5.begin(), top5.end());

    std::string result;
    std::string word;
    bool inWord = false;

    for (size_t i = 0; i < text.length(); ++i) {
        char ch = text[i];
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += ch;
            inWord = true;
        }
        else {
            if (inWord) {
                std::vector<char> foundLetters;
                for (char c : word) {
                    char lower = std::tolower(c);
                    if (topSet.count(lower)) {
                        foundLetters.push_back(lower);
                    }
                }
                std::set<char> uniqueFound(foundLetters.begin(), foundLetters.end());
                if (uniqueFound.size() >= 4) {
                    result += toUpper(word);
                    result += "(";
                    for (char c : top5) {
                        if (uniqueFound.count(c)) {
                            result += c;
                        }
                    }
                    result += ")";
                }
                else {
                    result += word;
                }
                word.clear();
                inWord = false;
            }
            result += ch;
        }
    }

    if (inWord) {
        std::vector<char> foundLetters;
        for (char c : word) {
            char lower = std::tolower(c);
            if (topSet.count(lower)) {
                foundLetters.push_back(lower);
            }
        }
        std::set<char> uniqueFound(foundLetters.begin(), foundLetters.end());
        if (uniqueFound.size() >= 4) {
            result += toUpper(word);
            result += "(";
            for (char c : top5) {
                if (uniqueFound.count(c)) {
                    result += c;
                }
            }
            result += ")";
        }
        else {
            result += word;
        }
    }

    std::ofstream outFile(outputFilename);
    outFile << result;
    outFile.close();
}
