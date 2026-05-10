#pragma once

#include <string>
#include <vector>
#include <map>

std::vector<std::string> splitIntoWords(const std::string& text);
int maxIdenticalLettersCount(const std::string& word);
void solveTask1(const std::string& inputFilename, const std::string& outputFilename, int N);

bool hasLongPalindrome(const std::vector<std::string>& words);
int countConsonants(const std::string& word);
std::string duplicateVowels(const std::string& word);
std::vector<std::string> processTask2(const std::string& text);

std::map<char, int> countLetterFrequency(const std::string& text);
std::vector<char> getTop5Letters(const std::string& text);
bool containsAtLeastFourOf(const std::string& word, const std::vector<char>& topLetters);
std::string toUpper(const std::string& word);
void solveTask3(const std::string& inputFilename, const std::string& outputFilename);
