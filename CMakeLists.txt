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
	${PROJECT_SOURCE_DIR}/src/main.cpp
	)

set (INCLUDES
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/include
	)
include_directories(demo ${INCLUDES})
add_executable(demo ${SOURCES})
#target_link_libraries (demo ${PROJECT_NAME})

#add_custom_command(TARGET demo
#		COMMENT "Compile and Run Tests"
#		POST_BUILD
#		COMMAND g++ -g -o teste1 ${PROJECT_SOURCE_DIR}/tests/test1.cpp -DTEST=1
#		COMMAND make test)

enable_testing()
#add_test(EMPTY_TEST ${PROJECT_SOURCE_DIR}/tests/teste1)

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
