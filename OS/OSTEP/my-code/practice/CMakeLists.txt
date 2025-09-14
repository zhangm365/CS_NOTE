cmake_minimum_required(VERSION 3.15)

# Prefer Homebrew LLVM clang/clang++ by default on macOS, if available.
# Must be set BEFORE project() so CMake picks these as the compilers.
if(NOT DEFINED CMAKE_C_COMPILER AND NOT DEFINED CMAKE_CXX_COMPILER)
	if(EXISTS "/opt/homebrew/opt/llvm/bin/clang")
		set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
		set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")
	elseif(EXISTS "/usr/local/opt/llvm/bin/clang")
		set(CMAKE_C_COMPILER "/usr/local/opt/llvm/bin/clang")
		set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++")
	endif()
endif()

project(ostep_practice LANGUAGES C CXX)

# Language standards (disable GNU extensions for portability)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile_commands.json from the build directory
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Warnings (per-language); Werror optional
option(ENABLE_STRICT "Enable warnings (-Wall)" ON)
option(ENABLE_WERROR "Treat warnings as errors (-Werror)" OFF)
if(ENABLE_STRICT)
	add_compile_options(
		$<$<COMPILE_LANGUAGE:C>:-Wall>
		$<$<COMPILE_LANGUAGE:CXX>:-Wall>
	)
endif()
if(ENABLE_WERROR)
	add_compile_options(
		$<$<COMPILE_LANGUAGE:C>:-Werror>
		$<$<COMPILE_LANGUAGE:CXX>:-Werror>
	)
endif()

# Unified output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Common settings as an INTERFACE target (includes + threads)
add_library(practice_common INTERFACE)
target_include_directories(practice_common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(practice_common INTERFACE Threads::Threads)

# List subdirectories to scan (append more as needed)
set(PRACTICE_DIRS
	ch30-threads-cv
  ch05
)

foreach(dir ${PRACTICE_DIRS})
	set(abs "${CMAKE_CURRENT_SOURCE_DIR}/${dir}")
	file(GLOB SRCS CONFIGURE_DEPENDS
		"${abs}/*.c" "${abs}/*.cc" "${abs}/*.cpp")
	foreach(src ${SRCS})
		get_filename_component(name ${src} NAME_WE)
		add_executable(${name} ${src})
		target_link_libraries(${name} PRIVATE practice_common)
	endforeach()
endforeach()

# Symlink compile_commands.json to source dir and parent for clangd
add_custom_target(ccdb ALL
	COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_SOURCE_DIR}/compile_commands.json
	COMMAND ${CMAKE_COMMAND} -E create_symlink
					${CMAKE_BINARY_DIR}/compile_commands.json
					${CMAKE_SOURCE_DIR}/compile_commands.json
	COMMENT "Updating compile_commands.json symlink at source root"
)
