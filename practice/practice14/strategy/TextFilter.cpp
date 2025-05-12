#include "TextFilter.h"
#include <algorithm>
#include <cctype>
#include <sstream>

// Helper to convert string to lowercase
std::string toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// ReverseFilter
std::string ReverseFilter::apply(const std::string& input) {
    std::string result = input;
    std::reverse(result.begin(), result.end());
    return result;
}

// UppercaseFilter
std::string UppercaseFilter::apply(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// RemoveVowelsFilter
std::string RemoveVowelsFilter::apply(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (std::string("aeiouAEIOU").find(c) == std::string::npos) {
            result += c;
        }
    }
    return result;
}

// CensorFilter
std::string CensorFilter::apply(const std::string& input) {
    std::istringstream iss(input);
    std::ostringstream oss;
    std::string word;

    while (iss >> word) {
        std::string cleaned = word;
        cleaned.erase(std::remove_if(cleaned.begin(), cleaned.end(), [](char c) {
            return std::ispunct(static_cast<unsigned char>(c));
            }), cleaned.end());

        std::string lowered = toLower(cleaned);
        auto it = std::find(this->badWords.begin(), this->badWords.end(), lowered);
        if (it != this->badWords.end()) {
            oss << "*** ";
        }
        else {
            oss << word << " ";
        }
    }

    return oss.str();
}
