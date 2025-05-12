#pragma once
#include <string>
#include <vector>

// Abstract Strategy Interface
class TextFilter {
public:
    virtual std::string apply(const std::string& input) = 0;
    virtual ~TextFilter() = default;
};

// Concrete Strategy: Reverses the input
class ReverseFilter : public TextFilter {
public:
    std::string apply(const std::string& input) override;
};

// Concrete Strategy: Converts input to uppercase
class UppercaseFilter : public TextFilter {
public:
    std::string apply(const std::string& input) override;
};

// Concrete Strategy: Removes vowels
class RemoveVowelsFilter : public TextFilter {
public:
    std::string apply(const std::string& input) override;
};

// Concrete Strategy: Censors bad words (case-insensitive match)
class CensorFilter : public TextFilter {
public:
    std::string apply(const std::string& input) override;

private:
    // ⚠️ Disclaimer:
    // The following list of words was generated using AI assistance and is meant
    // solely for demonstration purposes in a text filtering example.
    // These words are commonly flagged in public profanity filters.
    // Their inclusion does not reflect the beliefs, values, or intent of the user.
    std::vector<std::string> badWords = {
        "bad", "ugly", "stupid", // placeholder insults
        "fuck", "shit", "ass", "asshole", "bitch", "bastard",
        "dick", "piss", "crap", "damn", "cock", "cunt",
        "motherfucker", "slut", "whore", "retard", "nigger"
    };
};
