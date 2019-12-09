#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <set>
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "../word.h"
#include "../indexableSet.h"

struct caselessCompare {
    // is left smaller as right?
    bool operator()(const std::string &left, const std::string &right) const {
        return lexicographical_compare(
                begin(left), end(left),
                begin(right), end(right),
                [](char l, char r) {
                    return tolower(l) < tolower(r);
                });
    }
};

void test_constructors_availability() {
    std::set<int> plainInitialization{4, 2, 4};
    indexableSet<int> testSet{4, 2, 4};

    ASSERT_EQUAL(plainInitialization.size(), testSet.size());

    plainInitialization = std::set<int>{};
    testSet = indexableSet<int>{};

    ASSERT_EQUAL(plainInitialization.size(), testSet.size());
}

void test_accessibility_via_index() {
    indexableSet<int> testSet{2, 1, 4, 3};
    ASSERT_EQUAL(3, testSet[2]);
    ASSERT_EQUAL(3, testSet.at(2));
}

void test_negative_indexes() {
    indexableSet<int> testSet{2, 1, 4, 3};
    ASSERT_EQUAL(4, testSet[-1]);
}

void test_front() {
    indexableSet<int> testSet{2, 1, 4, 3};
    ASSERT_EQUAL(1, testSet.front());
}

void test_back() {
    indexableSet<int> testSet{2, 1, 4, 3};
    ASSERT_EQUAL(4, testSet.back());
}

void test_compare_function() {
    const auto randomString1 = "alpha";
    const auto randomString2 = "bravo";
    ASSERT_EQUAL(true, caselessCompare{}(randomString1, randomString2));
    ASSERT_EQUAL(false, caselessCompare{}(randomString2, randomString1));
    ASSERT_EQUAL(1, "alpha" < "beta");
}

void test_custom_sorting() {
    indexableSet<std::string, caselessCompare> testSet{"brudi", "hopfä", "ost", "west", "alpha"};
    ASSERT_EQUAL("alpha", testSet.front());
    ASSERT_EQUAL("brudi", testSet[1]);
}

bool runAllTests(int argc, char const *argv[]) {
    cute::suite s{};
    s.push_back(CUTE(test_constructors_availability));
    s.push_back(CUTE(test_accessibility_via_index));
    s.push_back(CUTE(test_negative_indexes));
    s.push_back(CUTE(test_front));
    s.push_back(CUTE(test_back));
    s.push_back(CUTE(test_compare_function));
    s.push_back(CUTE(test_custom_sorting));
    cute::xml_file_opener xmlfile(argc, argv);
    cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
    auto runner{cute::makeRunner(lis, argc, argv)};
    bool success = runner(s, "AllTests");
    return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
