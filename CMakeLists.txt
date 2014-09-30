cmake_minimum_required(VERSION 2.8)

project(aslan)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set (LEX_FILE_IN ${PROJECT_SOURCE_DIR}/lexer/aslan.l)
set (LEX_FILE_OUT ${PROJECT_BINARY_DIR}/aslan_scanner.cpp)
set (GRAMMAR_FILE_IN ${PROJECT_SOURCE_DIR}/grammar/aslan.y)
set (GRAMMAR_FILE_OUT ${PROJECT_BINARY_DIR}/aslan_parser.cpp)

flex_target(aslanScanner ${LEX_FILE_IN} ${LEX_FILE_OUT})
bison_target(aslanParser ${GRAMMAR_FILE_IN} ${GRAMMAR_FILE_OUT})
add_flex_bison_dependency(aslanScanner aslanParser)


set (SOURCES
	${PROJECT_SOURCE_DIR}/src/Aslan_Context.hpp
	${PROJECT_SOURCE_DIR}/src/Aslan_Context.cpp
	${BISON_aslanParser_OUTPUTS}
	${FLEX_aslanScanner_OUTPUTS}
	)

set (INCLUDES
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/include
	)

include_directories(aslan ${INCLUDES})
add_executable(aslan
				${PROJECT_SOURCE_DIR}/src/main.cpp
				${SOURCES})

# Executable of Test
include_directories(empty_test ${INCLUDES} ${PROJECT_BINARY_DIR})
add_executable(empty_test
				${PROJECT_SOURCE_DIR}/tests/empty_lexer.cpp
				${SOURCES})
# To build empty_test always after aslan built
add_dependencies(empty_test aslan)

add_executable(commentary_test
				${PROJECT_SOURCE_DIR}/tests/commentary_lexer.cpp
				${SOURCES})
add_dependencies(commentary_test empty_test)

add_executable(commentary_fail_eof_test
				${PROJECT_SOURCE_DIR}/tests/commentary_fail_EOF_lexer.cpp
				${SOURCES})
add_dependencies(commentary_fail_eof_test commentary_test)

add_executable(cs_test
				${PROJECT_SOURCE_DIR}/tests/char_string_lexer.cpp
				${SOURCES})
add_dependencies(cs_test XXXX)

add_executable(char_string_fail_eol_test
				${PROJECT_SOURCE_DIR}/tests/char_string_fail_EOL_lexer.cpp
				${SOURCES})
add_dependencies(char_string_fail_eol_test cs_test)

add_executable(char_string_fail_eof_test
				${PROJECT_SOURCE_DIR}/tests/char_string_fail_EOF_lexer.cpp
				${SOURCES})
add_dependencies(char_string_fail_eof_test char_string_fail_eol_test)

add_executable(ss_test
				${PROJECT_SOURCE_DIR}/tests/string_lexer.cpp
				${SOURCES})
add_dependencies(ss_test char_string_fail_eof_test)

add_executable(string_fail_eol_test
				${PROJECT_SOURCE_DIR}/tests/string_fail_EOL_lexer.cpp
				${SOURCES})
add_dependencies(string_fail_eol_test ss_test)

add_executable(string_fail_eof_test
				${PROJECT_SOURCE_DIR}/tests/string_fail_EOF_lexer.cpp
				${SOURCES})
add_dependencies(string_fail_eof_test string_fail_eol_test)

add_executable(dot_prefix_test
				${PROJECT_SOURCE_DIR}/tests/dot_prefix_lexer.cpp
				${SOURCES})
add_dependencies(dot_prefix_test string_fail_eof_test)

add_executable(pairp_test
				${PROJECT_SOURCE_DIR}/tests/pairp_lexer.cpp
				${SOURCES})
add_dependencies(pairp_test dot_prefix_test)

add_executable(pairp_fail_eof_test
				${PROJECT_SOURCE_DIR}/tests/pairp_fail_eof_lexer.cpp
				${SOURCES})
add_dependencies(pairp_fail_eof_test pairp_test)

add_executable(pairp_fail_forget_test
				${PROJECT_SOURCE_DIR}/tests/pairp_fail_forget_lexer.cpp
				${SOURCES})
add_dependencies(pairp_fail_forget_test pairp_fail_eof_lexer)

add_executable(pairb_test
				${PROJECT_SOURCE_DIR}/tests/pairb_lexer.cpp
				${SOURCES})
add_dependencies(pairb_test pairp_fail_forget_test)

add_executable(pairb_fail_eof_test
				${PROJECT_SOURCE_DIR}/tests/pairb_fail_eof_lexer.cpp
				${SOURCES})
add_dependencies(pairb_fail_eof_test pairb_test)

add_executable(pairb_fail_forget_test
				${PROJECT_SOURCE_DIR}/tests/pairb_fail_forget_lexer.cpp
				${SOURCES})
add_dependencies(pairb_fail_forget_test pairb_fail_eof_lexer)

add_executable(pairk_test
				${PROJECT_SOURCE_DIR}/tests/pairk_lexer.cpp
				${SOURCES})
add_dependencies(pairk_test pairb_fail_forget_test)

add_executable(pairk_fail_eof_test
				${PROJECT_SOURCE_DIR}/tests/pairk_fail_eof_lexer.cpp
				${SOURCES})
add_dependencies(pairk_fail_eof_test pairk_test)

add_executable(pairk_fail_forget_test
				${PROJECT_SOURCE_DIR}/tests/pairk_fail_forget_lexer.cpp
				${SOURCES})
add_dependencies(pairk_fail_forget_test pairk_fail_eof_lexer)

add_executable(token_tests
				${PROJECT_SOURCE_DIR}/tests/token_test_lexer.cpp
				${SOURCES})
add_dependencies(token_tests pairk_fail_forget_test)

enable_testing()
add_test(EMPTY_TEST ${PROJECT_BINARY_DIR}/empty_test)
add_test(COMMENTARY_TEST ${PROJECT_BINARY_DIR}/commentary_test)
add_test(COMMENTARY_FAIL_EOF_TEST ${PROJECT_BINARY_DIR}/commentary_fail_eof_test)
add_test(CHAR_STRING_TEST ${PROJECT_BINARY_DIR}/cs_test)
add_test(CHAR_STRING_FAIL_EOL_TEST ${PROJECT_BINARY_DIR}/char_string_fail_eol_test)
add_test(CHAR_STRING_FAIL_EOF_TEST ${PROJECT_BINARY_DIR}/char_string_fail_eof_test)
add_test(STRING_TEST ${PROJECT_BINARY_DIR}/ss_test)
add_test(STRING_FAIL_EOL_TEST ${PROJECT_BINARY_DIR}/string_fail_eol_test)
add_test(STRING_FAIL_EOF_TEST ${PROJECT_BINARY_DIR}/string_fail_eof_test)
add_test(DOT_PREFIX_TEST ${PROJECT_BINARY_DIR}/dot_prefix_test)
add_test(PAIRP_TEST ${PROJECT_BINARY_DIR}/pairp_test)
add_test(PAIRP_FAIL_EOF_TEST ${PROJECT_BINARY_DIR}/pairp_fail_eof_test)
add_test(PAIRP_FAIL_FORGET_TEST ${PROJECT_BINARY_DIR}/pairp_fail_forget_test)
add_test(PAIRB_TEST ${PROJECT_BINARY_DIR}/pairb_test)
add_test(PAIRB_FAIL_EOF_TEST ${PROJECT_BINARY_DIR}/pairb_fail_eof_test)
add_test(PAIRB_FAIL_FORGET_TEST ${PROJECT_BINARY_DIR}/pairb_fail_forget_test)
add_test(PAIRK_TEST ${PROJECT_BINARY_DIR}/pairk_test)
add_test(PAIRK_FAIL_EOF_TEST ${PROJECT_BINARY_DIR}/pairk_fail_eof_test)
add_test(PAIRK_FAIL_FORGET_TEST ${PROJECT_BINARY_DIR}/pairk_fail_forget_test)
add_test(TOKEN_TESTS ${PROJECT_BINARY_DIR}/token_tests)

#PASS_REGULAR_EXPRESSION is divided by ';'
set_tests_properties(CHAR_STRING_FAIL_EOL_TEST STRING_FAIL_EOL_TEST
					PROPERTIES
					PASS_REGULAR_EXPRESSION "Unexpected end of line")
set_tests_properties(CHAR_STRING_FAIL_EOF_TEST STRING_FAIL_EOF_TEST
					COMMENTARY_FAIL_EOF_TEST PAIRP_FAIL_EOF_TEST
					PAIRB_FAIL_EOF_TEST PAIRK_FAIL_EOF_TEST
					PROPERTIES
					PASS_REGULAR_EXPRESSION "Unexpected end of file")
set_tests_properties(PAIRP_FAIL_FORGET_TEST
					PROPERTIES
					PASS_REGULAR_EXPRESSION "Did you forget to open '\\('?")
set_tests_properties(PAIRB_FAIL_FORGET_TEST
					PROPERTIES
					PASS_REGULAR_EXPRESSION "Did you forget to open '\\['?")
set_tests_properties(PAIRK_FAIL_FORGET_TEST
					PROPERTIES
					PASS_REGULAR_EXPRESSION "Did you forget to open '{'?")

SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_BUILD_TYPE Release)

add_definitions(
			-W
			-Wall
			-Winline
			-Wshadow
			-fno-rtti
			-Wcast-qual
			-Wconversion
			-Wpointer-arith
			-Wnon-virtual-dtor
		)
