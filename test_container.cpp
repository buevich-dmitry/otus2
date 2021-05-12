#define BOOST_TEST_MODULE test_container

#include "container.h"
#include "allocator.h"

#include <boost/test/unit_test.hpp>

namespace otus {

template <class Allocator>
void TestContainer(List<int, Allocator>& list, size_t size) {
    BOOST_CHECK(list.Empty());
    for (const auto elem : list) {
        BOOST_FAIL("no elements expected here, but got element " << elem);
    }
    for (size_t i = 0; i < size; ++i) {
        list.PushBack(i);
    }
    int cur = 0;
    for (const auto elem : list) {
        BOOST_CHECK(elem == cur);
        ++cur;
    }
    BOOST_CHECK_EQUAL(cur, size);
}

BOOST_AUTO_TEST_SUITE(test_container)

    BOOST_AUTO_TEST_CASE(test_container) {
        List<int> list;
        TestContainer(list, 10);
    }

    BOOST_AUTO_TEST_CASE(test_container_with_custom_allocator) {
        List<int, otus::Allocator<int, 10>> list;
        TestContainer(list, 10);
    }

}

} // namespace otus

