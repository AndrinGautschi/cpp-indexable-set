#ifndef TESTAT2_WORD_H
#define TESTAT2_WORD_H

#include <string>
#include <iostream>
#include <utility>

struct Word {
    explicit Word(const std::string & word);
    Word() : word{""} {};

    std::istream &read(std::istream &in);

    std::ostream &write(std::ostream &out) const;

    [[nodiscard]] std::string value() const;

private:
    std::string word;
};

inline std::istream & operator>>(std::istream &in, Word & word) {
    return word.read(in);
}

inline std::ostream & operator<<(std::ostream & in, Word &word) {
    return word.write(in);
}

#endif //TESTAT2_WORD_H
