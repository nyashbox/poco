# Sources 
file(GLOB SRCS_G "src/*.cpp")
POCO_SOURCES_AUTO(TEST_SRCS ${SRCS_G})

# Headers
file(GLOB_RECURSE HDRS_G "src/*.h")
POCO_HEADERS_AUTO(TEST_SRCS ${HDRS_G})

POCO_SOURCES_AUTO_PLAT(TEST_SRCS OFF
	src/WinDriver.cpp
)

add_executable(AMQP-testrunner ${TEST_SRCS})

add_test(
    NAME AMQP
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND AMQP-testrunner -all
)
set_tests_properties(AMQP PROPERTIES ENVIRONMENT POCO_BASE=${CMAKE_SOURCE_DIR})

target_link_libraries(AMQP-testrunner 
    PUBLIC 
        ${CMAKE_THREAD_LIBS_INIT} 
        Poco::AMQP 
        CppUnit
)
