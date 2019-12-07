#include <cstdlib>
#include <stdexcept>
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "../word.h"

void test_word_input_separation() {
    std::istringstream input{"compl33tely ~ weird !!?!! 4matted in_put"};
    Word word{};
    input >> word;
    ASSERT_EQUAL("compl", word.value());
    input >> word;
    ASSERT_EQUAL("tely", word.value());
    input >> word;
    ASSERT_EQUAL("weird", word.value());
    input >> word;
    ASSERT_EQUAL("matted", word.value());
    input >> word;
    ASSERT_EQUAL("in", word.value());
    input >> word;
    ASSERT_EQUAL("put", word.value());
    input >> word;
    // Now the stream should be in fail state and w should still contain "put"
    ASSERT_EQUAL("put", word.value());
}

bool runAllTests(int argc, char const *argv[]) {
    cute::suite s{};

    s.push_back(CUTE(test_word_input_separation));
    cute::xml_file_opener xmlfile(argc, argv);
    cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
    auto runner{cute::makeRunner(lis, argc, argv)};
    bool success = runner(s, "AllTests");
    return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
