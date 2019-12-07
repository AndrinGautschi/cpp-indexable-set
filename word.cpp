#include <iostream>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include "word.h"

char readFromStream(std::istream & in) {
    const char readValue = in.get();
    if (in.bad()) {
        throw std::runtime_error("Somehow reading from stream failed");
    }
    return readValue;
}

std::istream & Word::read(std::istream & in) {
    if (in.fail()) return in;

    std::string readWord;
    while (!in.eof()) {
        const char current = readFromStream(in);
        const int isAlphabetic = std::isalpha(current);
        const int isSpace = std::isspace(current);

        // skip leading invalid chars
        if (readWord.length() == 0 && !isAlphabetic) {
            continue;
        }

        // end of word trigger by a non alphabetic char
        if (readWord.length() > 0 && (!isAlphabetic || isSpace)) {
            break;
        }

        if (readWord.length() >= 0 && isAlphabetic) {
            readWord += current;
        }
    }
    word = readWord;
    return in;
}

std::ostream & Word::write(std::ostream &out) const {
    return out << word;
}

std::string Word::value() const {
    return word;
}

Word::Word(const std::string & word) {
    std::istringstream stream{word};
    this->read(stream);
}

