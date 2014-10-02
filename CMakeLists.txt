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
	${PROJECT_BINARY_DIR}
	)

add_library(aslanparser STATIC ${SOURCES})

include_directories(${INCLUDES})

add_executable(aslan
				${PROJECT_SOURCE_DIR}/src/main.cpp
				)
target_link_libraries(aslan aslanparser)

macro(CREATE_TEST_EXECUTABLE BIN PARENT)
	add_executable(${BIN}
					${PROJECT_SOURCE_DIR}/tests/${BIN}_lexer.cpp
					)
	target_link_libraries(${BIN} aslanparser)
	add_dependencies(${BIN} ${PARENT})
	string(TOUPPER ${BIN} BIN_NAME)
	add_test(${BIN_NAME} ${PROJECT_BINARY_DIR}/${BIN})
endmacro(CREATE_TEST_EXECUTABLE)

set(TEST_CASES
	empty_test
	commentary_test
	commentary_fail_eof_test
	char_string_test
	char_string_fail_eol_test
	char_string_fail_eof_test
	string_string_test
	string_fail_eol_test
	string_fail_eof_test
	dot_prefix_test
	pairp_fail_eof_test
	pairp_fail_forget_test
	pairb_fail_eof_test
	pairb_fail_forget_test
	pairk_fail_eof_test
	pairk_fail_forget_test
	token_tests
	variable_test
	identifier_test
	externalaction_test
	)
SET(PREVIOUS aslan)

foreach(BIN_TEST IN LISTS TEST_CASES)
	CREATE_TEST_EXECUTABLE(${BIN_TEST} ${PREVIOUS})
	set(PREVIOUS ${BIN_TEST})
endforeach(BIN_TEST)

enable_testing()

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
