cmake_minimum_required(VERSION 3.10)
project(custom_allocator VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -pedantic -Werror)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_library(allocator INTERFACE)
target_sources(allocator INTERFACE ${CMAKE_SOURCE_DIR}/allocator.h)

add_library(container INTERFACE)
target_sources(container INTERFACE ${CMAKE_SOURCE_DIR}/container.h)

add_executable(test_allocator test_allocator.cpp)
set_target_properties(test_allocator PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)
target_link_libraries(test_allocator ${Boost_LIBRARIES} allocator)

add_executable(test_container test_container.cpp)
set_target_properties(test_container PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
        )
target_link_libraries(test_container ${Boost_LIBRARIES} container)

add_executable(custom_allocator main.cpp)
target_link_libraries(custom_allocator allocator container)

enable_testing()
add_test(test_allocator test_allocator)
add_test(test_container test_container)

install(TARGETS custom_allocator RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEB_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${custom_allocator_VERSION})
set(CPACK_PACKAGE_CONTACT buevichd@yandex-team.ru)
include(CPack)
