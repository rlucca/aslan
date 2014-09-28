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

#PASS_REGULAR_EXPRESSION is divided by ';'
set_tests_properties(CHAR_STRING_FAIL_EOL_TEST STRING_FAIL_EOL_TEST
					PROPERTIES
					PASS_REGULAR_EXPRESSION "Unexpected end of line")
set_tests_properties(CHAR_STRING_FAIL_EOF_TEST STRING_FAIL_EOF_TEST
					COMMENTARY_FAIL_EOF_TEST
					PROPERTIES
					PASS_REGULAR_EXPRESSION "Unexpected end of file")

SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_BUILD_TYPE Release)

add_definitions(
			-W
			-Wall
			-Werror
			-Winline
			-Wshadow
			-fno-rtti
			-Wcast-qual
			-Wconversion
			-Wpointer-arith
			-Wnon-virtual-dtor
			-Wno-unused-parameter
			-Wno-sign-compare
		)
