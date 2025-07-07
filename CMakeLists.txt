cmake_minimum_required(VERSION 3.15.1)

# set(CMAKE_C_COMPILER "gcc")
# set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INSTALL_PREFIX /usr/local)
project(tpsa_sym)

# Find SymEngine
find_package(SymEngine REQUIRED CONFIG)

#Bring the headers into the project
include_directories(include)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cc")

# Include SymEngine headers
include_directories(${SYMENGINE_INCLUDE_DIRS})
link_directories(${SYMENGINE_LIBRARY_DIRS})

set(RELEASE_COMPILE_OPTIONS "-O3" "-DNDEBUG" "-Wall")

# Loop through each library in SYMENGINE_LIBRARIES
foreach(LIB ${SYMENGINE_LIBRARIES})
    # Extract the directory name from the library path
    get_filename_component(LIB_DIR ${LIB} DIRECTORY)

    # Only process non-empty directory values (this avoids issues with entries like "symengine")
    if (LIB_DIR)
        # Check if the directory has already been added to SYMENGINE_LIBRARY_DIRS
        list(FIND SYMENGINE_LIBRARY_DIRS ${LIB_DIR} DIR_INDEX)
        
        # Add the directory to the list if it's not already present
        if (DIR_INDEX EQUAL -1)
            list(APPEND SYMENGINE_LIBRARY_DIRS ${LIB_DIR})
        endif()
    endif()
endforeach()

message(STATUS "SYMENGINE_LIBRARIES = ${SYMENGINE_LIBRARIES}")
message(STATUS "SYMENGINE_INCLUDE_DIRS = ${SYMENGINE_INCLUDE_DIRS}")
message(STATUS "SYMENGINE_LIBRARY_DIRS = ${SYMENGINE_LIBRARY_DIRS}")

#Generate the shared library and the static llibary from the sources
add_library(symtpsaShared SHARED ${SOURCES})
# Link SymEngine with your application
target_link_libraries(symtpsaShared  ${SYMENGINE_LIBRARIES})
set_target_properties(symtpsaShared PROPERTIES 
    OUTPUT_NAME "symtpsa"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    COMPILE_FLAGS ${RELEASE_COMPILE_OPTIONS}
)
add_library(symtpsaStatic STATIC ${SOURCES})
target_link_libraries(symtpsaStatic  ${SYMENGINE_LIBRARIES})
set_target_properties(symtpsaStatic PROPERTIES 
    OUTPUT_NAME "symtpsa"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    COMPILE_FLAGS ${RELEASE_COMPILE_OPTIONS}
)

# Set the output directory for the binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ----------------------------------------------------------------------------------
# Create a custom target for examples (NOT built by default)
# ----------------------------------------------------------------------------------

# Find all example files in the examples directory
file(GLOB EXAMPLE_SOURCES ${CMAKE_SOURCE_DIR}/examples/*.cc)

# Custom target to build examples
# add_custom_target(build_examples ALL DEPENDS symtpsaStatic)
add_custom_target(build_examples
    COMMENT "Building examples"
)

# Create an executable for each example file
foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
    # Get the file name without extension
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)

    # Add the executable
    add_executable(${EXAMPLE_NAME} EXCLUDE_FROM_ALL ${EXAMPLE_SOURCE})

    # Set a specific output directory for the debug executable
    set_target_properties(${EXAMPLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples)

    # Link against the static library
    target_link_libraries(${EXAMPLE_NAME} symtpsaStatic)

    # Make the example depend on the custom target
    add_dependencies(build_examples ${EXAMPLE_NAME})
endforeach()


# ----------------------------------------------------------------------------------
# Create a custom target for tests (NOT built by default)
# ----------------------------------------------------------------------------------

# Find all example files in the tests directory
file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/*.cc)

# Custom target to build examples
# add_custom_target(build_examples ALL DEPENDS symtpsaStatic)
add_custom_target(build_tests
    COMMENT "Building tests"
)

# Add the executable
add_executable(run_tests EXCLUDE_FROM_ALL ${TEST_SOURCES})

# Set a specific output directory for the debug executable
set_target_properties(run_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)

# Link against the static library
target_link_libraries(run_tests symtpsaStatic)

# Make the example depend on the custom target
add_dependencies(build_tests run_tests)

# # Create an executable for each example file
# foreach(TEST_SOURCE ${TEST_SOURCES})
#     # Get the file name without extension
#     get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

#     # Add the executable
#     add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${TEST_SOURCE})

#     # Set a specific output directory for the debug executable
#     set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)

#     # Link against the static library
#     target_link_libraries(${TEST_NAME} symtpsaStatic)

#     # Make the example depend on the custom target
#     add_dependencies(build_tests ${TEST_NAME})
# endforeach()



# ----------------------------------------------------------------------------------
# Create a custom target for debug (NOT built by default)
# ----------------------------------------------------------------------------------

# Custom target to build the debug executable
add_custom_target(build_debug
    COMMENT "Building all debug executables"
)

set(DEBUG_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/include
    ${SYMENGINE_INCLUDE_DIRS}
)

#set(DEBUG_COMPILE_OPTIONS "-g -O0 -DDEBUG -fsanitize=address -Wall -Wextra") 
set(DEBUG_COMPILE_OPTIONS "-g -O0 -DDEBUG") 
# Custom target to build the debug executable
file(GLOB DEBUG_SOURCES ${CMAKE_SOURCE_DIR}/debug/*.cc)

# Ensure linker directories are set for the debug build
link_directories(${SYMENGINE_LIBRARY_DIRS})

foreach(DEBUG_SOURCE ${DEBUG_SOURCES})
    # Get the file name without extension
    get_filename_component(DEBUG_NAME ${DEBUG_SOURCE} NAME_WE)

    # Add the executable
    add_executable(${DEBUG_NAME} EXCLUDE_FROM_ALL ${DEBUG_SOURCE} ${SOURCES})

    # Set a specific output directory for the debug executable
    set_target_properties(${DEBUG_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/debug)

    # Set compile options for the debug executable
 #   target_compile_options(${DEBUG_NAME} PRIVATE ${DEBUG_COMPILE_OPTIONS})
    set_target_properties(${DEBUG_NAME} PROPERTIES COMPILE_FLAGS ${DEBUG_COMPILE_OPTIONS})


    # Include directories for the debug executable
    target_include_directories(${DEBUG_NAME} PRIVATE ${DEBUG_INCLUDE_DIRS})
 #   message(STATUS "Set include directories for ${DEBUG_EXECUTABLE_NAME} to: ${DEBUG_INCLUDE_DIRS}")

    target_link_libraries(${DEBUG_NAME} PRIVATE symengine flint gmp mpfr)

    target_link_options(${DEBUG_NAME} PRIVATE -fsanitize=address)
   
     # Make the debug executable depend on the custom target
     add_dependencies(build_debug ${DEBUG_NAME})
endforeach()

if(WIN32)
    set(CMAKE_INSTALL_PREFIX "C:/msys64/mingw64")
endif()


# Optionally, you can add a custom command to build examples separately
add_custom_target(examples
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target build_examples
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Building examples"
)

# Target to clean examples
add_custom_target(clean_examples
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning examples"
)

# Optionally, you can add a custom command to build examples separately
add_custom_target(dbg
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target build_debug
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Building debug executable"
)

add_custom_target(tests
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target build_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Building tests"
)

# Target to clean tests
add_custom_target(clean_tests
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning tests"
)

# Target to clean tests, including removing catch_main.o
add_custom_target(clean_tests_all
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_SOURCE_DIR}/tests/catch_main.o
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning tests and removing catch_main.o"
)

#Set the location for library installation -- i.e., /usr/local/lib in this case
#Use "sudo make install" to apply
install(TARGETS symtpsaShared symtpsaStatic DESTINATION)

#Install the header file
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/sda.h DESTINATION include)

