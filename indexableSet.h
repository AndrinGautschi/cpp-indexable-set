#ifndef WORDS_INDEXABLESET_H
#define WORDS_INDEXABLESET_H

#include <functional>
#include <vector>
#include <set>
#include <stdexcept>
#include <iterator>

template<typename T, typename COMPARE=std::less<T>>
struct indexableSet : std::set<T, COMPARE> {
    using container = std::set<T, COMPARE>;
    using container::container;
    using size_type = typename container::size_type;
    using reference = typename container::reference;
    using const_reference = typename container::const_reference;

    T at(int index) {
        if (index < 0) index = this->size() + index;
        if (index >= this->size() || index < 0) throw std::out_of_range("Index too big");
        return *(std::next(this->begin(), index));
    }

    T front() {
        return this->at(0);
    }

    T back() {
        return this->at(-1);
    }

    T operator[](int index) {
        return this->at(index);
    }

    const T operator[](int index) const {
        return this->at(index);
    }
};

#endif //WORDS_INDEXABLESET_H
