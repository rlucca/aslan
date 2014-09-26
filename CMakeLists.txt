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
add_executable(empty_test
				${PROJECT_SOURCE_DIR}/tests/empty_lexer.cpp
				${SOURCES})
# To build empty_test always after aslan built
add_dependencies(empty_test aslan)

add_executable(comentary_test
				${PROJECT_SOURCE_DIR}/tests/comentary_lexer.cpp
				${SOURCES})
add_dependencies(comentary_test empty_test)


enable_testing()
add_test(EMPTY_TEST ${PROJECT_BINARY_DIR}/empty_test)
add_test(COMMENTARY_TEST ${PROJECT_BINARY_DIR}/comentary_test)

#g++ src/Aslan_Context.cpp tests/empty.cpp bin/aslan_scanner.cpp -Isrc -Ibin -lfl

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
