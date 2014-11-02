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
	${PROJECT_SOURCE_DIR}/src/parser/AllSymbol.hpp
	${PROJECT_SOURCE_DIR}/src/parser/Symbol.hpp
	${PROJECT_SOURCE_DIR}/src/parser/Symbol.cpp
	${PROJECT_SOURCE_DIR}/src/parser/ConstantExpression.cpp
	${PROJECT_SOURCE_DIR}/src/parser/ConstantExpression.hpp
	${PROJECT_SOURCE_DIR}/src/parser/Expression.cpp
	${PROJECT_SOURCE_DIR}/src/parser/Expression.hpp
	${PROJECT_SOURCE_DIR}/src/parser/Belief.cpp
	${PROJECT_SOURCE_DIR}/src/parser/Belief.hpp
	${PROJECT_SOURCE_DIR}/src/parser/Functor.cpp
	${PROJECT_SOURCE_DIR}/src/parser/Functor.hpp
	${PROJECT_SOURCE_DIR}/src/parser/TriggerEvent.cpp
	${PROJECT_SOURCE_DIR}/src/parser/TriggerEvent.hpp
	${PROJECT_SOURCE_DIR}/src/parser/EventType.cpp
	${PROJECT_SOURCE_DIR}/src/parser/EventType.hpp
	${PROJECT_SOURCE_DIR}/src/parser/Plan.cpp
	${PROJECT_SOURCE_DIR}/src/parser/Plan.hpp
	${PROJECT_SOURCE_DIR}/src/parser/StackedSymbol.cpp
	${PROJECT_SOURCE_DIR}/src/parser/StackedSymbol.hpp
	${PROJECT_SOURCE_DIR}/src/parser/Parameter.cpp
	${PROJECT_SOURCE_DIR}/src/parser/Parameter.hpp
	${PROJECT_SOURCE_DIR}/src/parser/Array.cpp
	${PROJECT_SOURCE_DIR}/src/parser/Array.hpp
	${PROJECT_SOURCE_DIR}/src/parser/Action.cpp
	${PROJECT_SOURCE_DIR}/src/parser/Action.hpp
	${PROJECT_SOURCE_DIR}/src/parser/TableChain.hpp
	${PROJECT_SOURCE_DIR}/src/Utils.hpp
	${PROJECT_SOURCE_DIR}/src/Utils.cpp
	${BISON_aslanParser_OUTPUTS}
	${FLEX_aslanScanner_OUTPUTS}
	)

set (INCLUDES
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/src/parser
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_BINARY_DIR}
	)

if(COVERAGE)
	MESSAGE("Inserting coverage flags and library")
	SET(COVERAGE_FLAGS "-fprofile-arcs -ftest-coverage")
	SET(COVERAGE_LDFLAGS "-fprofile-arcs -ftest-coverage")
	SET(COVERAGE_LIBRARY "-lgcov")

endif(COVERAGE)

add_library(aslanparser STATIC ${SOURCES})
set_target_properties(aslanparser
						PROPERTIES
						COMPILE_FLAGS "-Wno-unused-parameter -Wno-conversion"
					)

include_directories(${INCLUDES})

add_executable(aslan
				${PROJECT_SOURCE_DIR}/src/main.cpp
				)
target_link_libraries(aslan aslanparser ${COVERAGE_LIBRARY})

macro(CREATE_TEST BIN)
	string(TOUPPER ${BIN} BIN_NAME)
	set(BIN_EXEC ${PROJECT_BINARY_DIR}/${BIN})
	set(OPT_ARGS ${ARGN})
	list(LENGTH OPT_ARGS NUM_OPT_ARGS)
	if (${NUM_OPT_ARGS} EQUAL 3)
		list(GET OPT_ARGS 0 PREFIX_NAME)
		set(BIN_TMP ${PREFIX_NAME}${BIN})
		string(TOUPPER ${BIN_TMP} BIN_NAME)

		list(GET OPT_ARGS 1 INPUT)
		list(GET OPT_ARGS 2 OUTPUT)
		set(BIN_EXEC
			bash -c "${PROJECT_BINARY_DIR}/${BIN} < ${INPUT} 2>&1 | diff -- ${OUTPUT} - 2>&1 > /dev/null")
	endif(${NUM_OPT_ARGS} EQUAL 3)

	add_test(${BIN_NAME} ${BIN_EXEC})
	if(VALGRIND)
		add_test(${BIN_NAME}_VALGRIND
				valgrind --error-exitcode=1 --leak-check=full ${BIN_EXEC})
		set_tests_properties(${BIN_NAME}_VALGRIND
						PROPERTIES
						PASS_REGULAR_EXPRESSION "no leaks are possible")
	endif(VALGRIND)
endmacro(CREATE_TEST)

macro(CREATE_TEST_EXECUTABLE BIN PARENT LEVEL)
	add_executable(${BIN}
					${PROJECT_SOURCE_DIR}/tests/${BIN}_${LEVEL}.cpp
					)
	target_link_libraries(${BIN} aslanparser ${COVERAGE_LIBRARY})
	add_dependencies(${BIN} ${PARENT})
	CREATE_TEST(${BIN})
endmacro(CREATE_TEST_EXECUTABLE)

set(TEST_CASES
	empty_test
	commentary_test
	commentary_fail_eof_test
	char_string_test
	char_string_fail_eol_tst
	char_string_fail_eof_tst
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
	CREATE_TEST_EXECUTABLE(${BIN_TEST} ${PREVIOUS} "lexer")
	set(PREVIOUS ${BIN_TEST})
endforeach(BIN_TEST)

SET(TEST_CASES_INT
	utils_test
	symbol_test
	tablechain_test
	empty_grammar_test
	constant_expression_test
	event_type_test
	trigger_event_test
	stacked_symbol_test
	parameter_test
	array_test
	action_test
	functor_test
	belief_test
	plan_test
	)

foreach(BIN_TEST IN LISTS TEST_CASES_INT)
	CREATE_TEST_EXECUTABLE(${BIN_TEST} ${PREVIOUS} "int")
	set(PREVIOUS ${BIN_TEST})
endforeach(BIN_TEST)

CREATE_TEST(aslan "empty_" "<(echo)" "<(printf \"\")")

SET(GRAMMAR_TEST_CASES
	)

foreach(BIN_TEST IN LISTS GRAMMAR_TEST_CASES)
	# Why it's here and not inside CREATE_TEST?
	# It is not tested inside CREATE_TEST because it
	# would prevent use stuff like "<(echo)"
	set(INPUT "${PROJECT_SOURCE_DIR}/tests/${BIN_TEST}.asl")
	set(OUTPUT "${PROJECT_SOURCE_DIR}/tests/${BIN_TEST}.asl.checked")

	IF (NOT EXISTS ${INPUT})
		MESSAGE(SEND_ERROR
				"Could not locate file \"${INPUT}\"")
	ENDIF (NOT EXISTS ${INPUT})

	IF (NOT EXISTS ${OUTPUT})
		MESSAGE(SEND_ERROR
				"Could not locate file \"${OUTPUT}\"")
	ENDIF (NOT EXISTS ${OUTPUT})

	CREATE_TEST(aslan "grammar_${BIN_TEST}_" ${INPUT} ${OUTPUT})
endforeach(BIN_TEST)


enable_testing()

#PASS_REGULAR_EXPRESSION is divided by ';'
set_tests_properties(CHAR_STRING_FAIL_EOL_TST STRING_FAIL_EOL_TEST
					PROPERTIES
					PASS_REGULAR_EXPRESSION "Unexpected end of line")
set_tests_properties(CHAR_STRING_FAIL_EOF_TST STRING_FAIL_EOF_TEST
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
			${COVERAGE_FLAGS}
		)
set(CMAKE_EXE_LINKER_FLAGS "${COVERAGE_LDFLAGS}")
