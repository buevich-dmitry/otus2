#define BOOST_TEST_MODULE test_allocator

#include "allocator.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_allocator)

    BOOST_AUTO_TEST_CASE(test_allocate) {
        static constexpr size_t kSize = 10;
        using Allocator = otus::Allocator<int, kSize>;
        Allocator allocator;
        int* ptr = std::allocator_traits<Allocator>::allocate(allocator, kSize);
        BOOST_CHECK(ptr != nullptr);
        for (size_t i = 0; i < kSize; ++i) {
            std::allocator_traits<Allocator>::construct(allocator, ptr + i, i);
            BOOST_CHECK_EQUAL(ptr[i], i);
        }
        BOOST_CHECK_THROW(allocator.allocate(1), std::runtime_error);
    }

}
