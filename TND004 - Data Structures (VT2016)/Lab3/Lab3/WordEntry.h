#ifndef WORDENTRY_H
#define WORDENTRY_H

#include <string>
#include <ostream>
#include <iomanip>

struct WordEntry
{
    const std::string word;
    unsigned counter;

    WordEntry(std::string _word) : word(_word), counter(0) {}

    bool operator<(const WordEntry &other) const
    {
        return word < other.word;
    }
};

ostream &operator<<(ostream &os, const WordEntry &entry)
{
    os << std::setw(16) << std::left << entry.word << ": " << std::setw(2) << std::right << entry.counter;
    return os;
}

#endif // WORDENTRY_H
