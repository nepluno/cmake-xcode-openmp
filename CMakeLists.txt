cmake_minimum_required (VERSION 3.0.2)

project (TestOMP)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")

# Initialize the build type (Release, Debug, etc)
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Release CACHE STRING
    "Choose the type of build, options are: Debug Release."
    FORCE)
endif (NOT CMAKE_BUILD_TYPE)

add_definitions (-DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}")

if (CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions (-DDEBUG)
endif (CMAKE_BUILD_TYPE MATCHES Debug)

if (CMAKE_BUILD_TYPE MATCHES Release)
	add_definitions (-DNDEBUG)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")
endif (CMAKE_BUILD_TYPE MATCHES Release)

# Add directory with macros
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

if (CMAKE_GENERATOR STREQUAL Xcode)
	set (LLVM_ROOT_DIR "/usr/local/opt/llvm")
	find_package( LLVM )
	if( LLVM_FOUND )
		include_directories (${LLVM_LIBRARY_DIRS}/clang/${LLVM_VERSION_BASE_STRING}/include)
		set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp" )
		find_library(IOMP5LIB
			NAMES "iomp5" "iomp5md" "libiomp5" "libiomp5md"
			HINTS ${LLVM_LIBRARY_DIRS})
		set (TESTOMP_LIBRARIES ${TESTOMP_LIBRARIES} ${IOMP5LIB})
	endif( LLVM_FOUND )
else()
	find_package( OpenMP )
	if( OPENMP_FOUND )
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}" )
	endif( OPENMP_FOUND )
endif()

# finds all files with a given extension
macro (append_files files ext)
  foreach (dir ${ARGN})
    file (GLOB _files "${dir}/*.${ext}")
    list (APPEND ${files} ${_files})
  endforeach (dir)
endmacro (append_files)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

append_files (Headers "h" .)
append_files (Sources "cpp" .)

add_executable (TestOMP ${Headers} ${Templates} ${Sources})
target_link_libraries (TestOMP ${TESTOMP_LIBRARIES})

if (CMAKE_GENERATOR STREQUAL Xcode)
	set_target_properties(TestOMP PROPERTIES XCODE_ATTRIBUTE_CC ${LLVM_ROOT_DIR}/bin/clang)
	set_target_properties(TestOMP PROPERTIES XCODE_ATTRIBUTE_CXX ${LLVM_ROOT_DIR}/bin/clang)
	set_target_properties(TestOMP PROPERTIES XCODE_ATTRIBUTE_COMPILER_INDEX_STORE_ENABLE "No")
endif()

INSTALL_TARGETS(/bin TestOMP)
