cmake_minimum_required(VERSION 3.5.1)

#set(CMAKE_BUILD_TYPE Release)
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

message(STATUS "SYMENGINE_LIBRARIES = ${SYMENGINE_LIBRARIES}")
message(STATUS "SYMENGINE_INCLUDE_DIRS = ${SYMENGINE_INCLUDE_DIRS}")

#Generate the shared library and the static llibary from the sources
add_library(tpsaShared SHARED ${SOURCES})
# Link SymEngine with your application
target_link_libraries(tpsaShared  ${SYMENGINE_LIBRARIES})
set_target_properties(tpsaShared PROPERTIES 
    OUTPUT_NAME "symtpsa"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    COMPILE_FLAGS ${RELEASE_COMPILE_OPTIONS}
)
add_library(tpsaStatic STATIC ${SOURCES})
target_link_libraries(tpsaStatic  ${SYMENGINE_LIBRARIES})
set_target_properties(tpsaStatic PROPERTIES 
    OUTPUT_NAME "symtpsa"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    COMPILE_FLAGS ${RELEASE_COMPILE_OPTIONS}
)

# Set the output directory for the binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find all example files in the examples directory
file(GLOB EXAMPLE_SOURCES ${CMAKE_SOURCE_DIR}/examples/*.cc)

# Custom target to build examples
add_custom_target(build_examples ALL DEPENDS tpsaStatic)

# Create an executable for each example file
foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
    # Get the file name without extension
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)

    # Add the executable
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})

    # Set a specific output directory for the debug executable
    set_target_properties(${EXAMPLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples)

    # Link against the static library
    target_link_libraries(${EXAMPLE_NAME} tpsaStatic)

    # Make the example depend on the custom target
    add_dependencies(build_examples ${EXAMPLE_NAME})
endforeach()

# Optionally, you can add a custom command to build examples separately
add_custom_target(examples
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target build_examples
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Building examples"
)


# Custom target to build the debug executable
add_custom_target(build_debug
    COMMENT "Building all debug executables"
)

set(DEBUG_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/include
    ${SYMENGINE_INCLUDE_DIRS}
)

set(DEBUG_COMPILE_OPTIONS "-g" "-O0" "-DDEBUG")
# Custom target to build the debug executable
file(GLOB DEBUG_SOURCES ${CMAKE_SOURCE_DIR}/debug/*.cc)

foreach(DEBUG_SOURCE ${DEBUG_SOURCES})
    # Get the file name without extension
    get_filename_component(DEBUG_NAME ${DEBUG_SOURCE} NAME_WE)

    # Add the executable
    add_executable(${DEBUG_NAME} ${DEBUG_SOURCE} ${SOURCES})

    # Set a specific output directory for the debug executable
    set_target_properties(${DEBUG_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/debug)

    # Set compile options for the debug executable
 #   target_compile_options(${DEBUG_NAME} PRIVATE ${DEBUG_COMPILE_OPTIONS})
    set_target_properties(${DEBUG_NAME} PROPERTIES COMPILE_FLAGS ${DEBUG_COMPILE_OPTIONS})

    # Include directories for the debug executable
    target_include_directories(${DEBUG_NAME} PRIVATE ${DEBUG_INCLUDE_DIRS})
 #   message(STATUS "Set include directories for ${DEBUG_EXECUTABLE_NAME} to: ${DEBUG_INCLUDE_DIRS}")

    target_link_libraries(${DEBUG_NAME} PRIVATE libsymengine.a libgmp.so)
   
     # Make the debug executable depend on the custom target
     add_dependencies(build_debug ${DEBUG_NAME})
endforeach()

# Optionally, you can add a custom command to build examples separately
add_custom_target(dbg
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target build_debug
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Building debug executable"
)


add_custom_target(build_tests
    COMMAND ${CMAKE_MAKE_PROGRAM} INSTALL_DIR=${CMAKE_INSTALL_PREFIX} all
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test
    COMMENT "Building tests using Makefile with custom INSTALL_DIR"
)

#Set the location for library installation -- i.e., /usr/local/lib in this case
#Use "sudo make install" to apply
install(TARGETS tpsaShared tpsaStatic DESTINATION)

#Install the header file
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/sda.h DESTINATION include)

