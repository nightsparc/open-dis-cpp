cmake_minimum_required(VERSION 3.2)
project(OpenDIS)

## Set DIS protocol version
set(OPENDIS_PROTOCOL_VERSION "BOTH" CACHE STRING "Select the DIS protocol version to build the libraries for.")
set_property(CACHE OPENDIS_PROTOCOL_VERSION PROPERTY STRINGS "DIS6" "DIS7" "BOTH")

set(OPENDIS_LIBRARY_TYPE "SHARED" CACHE STRING "Select wether to build a shared or static library.")
set_property(CACHE OPENDIS_LIBRARY_TYPE PROPERTY STRINGS "SHARED" "STATIC")

option(OPENDIS_BUILD_EXAMPLES "Build the examples (only available for DIS6)" ON)
## Libraries

if(OPENDIS_PROTOCOL_VERSION STREQUAL "DIS6" OR OPENDIS_PROTOCOL_VERSION STREQUAL "BOTH")
    # create list of DIS6 source files
    file(GLOB DIS6_SOURCES
      "src/dis6/*.h"
      "src/dis6/*.cpp"
      "src/utils/*.h"
      "src/utils/*.cpp"
    )
    # Define ExampleSender Executable
    add_library(OpenDIS6 ${OPENDIS_LIBRARY_TYPE} ${DIS6_SOURCES})
    # Add src/ to the include directories to OpenDIS6
    target_include_directories(OpenDIS6 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> $<INSTALL_INTERFACE:> )
    # Add compile definition EXPORT_LIBRARY for DIS6 msLibMacro.h
    target_compile_definitions(OpenDIS6 PRIVATE EXPORT_LIBRARY)
    target_compile_definitions(OpenDIS6 PRIVATE DIS_VERSION=6)
endif()

if(OPENDIS_PROTOCOL_VERSION STREQUAL "DIS7" OR OPENDIS_PROTOCOL_VERSION STREQUAL "BOTH")
    # create list of DIS7 source files
    file(GLOB DIS7_SOURCES
      "src/dis7/*.h"
      "src/dis7/*.cpp"
      "src/utils/*.h"
      "src/utils/*.cpp"
    )
    # Define ExampleSender Executable
    add_library(OpenDIS7 ${OPENDIS_LIBRARY_TYPE} ${DIS7_SOURCES})
    # Add src/ to the include directories to OpenDIS6
    target_include_directories(OpenDIS7 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> $<INSTALL_INTERFACE:> )
    # Add compile definition EXPORT_LIBRARY for DIS7 msLibMacro.h
    target_compile_definitions(OpenDIS7 PRIVATE EXPORT_LIBRARY)
    target_compile_definitions(OpenDIS7 PRIVATE DIS_VERSION=7)
endif()


## Example Programs
include_directories(.)

# if Windows add M_PI definition
# - issues occurred during testing in Visual Studio
if(WIN32)
  add_definitions(/DM_PI=3.14159265358979323846)
endif (WIN32)

if(WIN32)
       set(SDL_LIBS SDL2main SDL2 SDL2_net)
else(WIN32)
       set(SDL_LIBS SDL2 SDL2_net)
endif(WIN32)

if(OPENDIS_BUILD_EXAMPLES AND OPENDIS_PROTOCOL_VERSION STREQUAL "DIS6" OR OPENDIS_PROTOCOL_VERSION STREQUAL "BOTH")
    # create list of ExampleSender source files
    file(GLOB EX_SENDER_SOURCES
      "examples/main.cpp"
      "examples/Connection.cpp"
      "examples/Utils.cpp"
      "examples/Timer.cpp"
    )

    # Define ExampleSender Executable
    add_executable(ExampleSender ${EX_SENDER_SOURCES})
    # Link OpenDIS into ExampleSender
    target_link_libraries(ExampleSender PRIVATE OpenDIS6)
    target_link_libraries(ExampleSender PRIVATE ${SDL_LIBS})
    # add src to ExampleSender include directories
    target_include_directories(ExampleSender PRIVATE src)
    target_compile_definitions(ExampleSender PRIVATE DIS_VERSION=6)

    # create list of ExampleReceiver source files
    file(GLOB EX_RECEIVER_SOURCES
      "examples/main_receive.cpp"
      "examples/Connection.cpp"
      "examples/Utils.cpp"
      "examples/Timer.cpp"
      "examples/EntityStatePduProcessor.cpp"
    )

    # Define ExampleReceiver Executable
    add_executable(ExampleReceiver ${EX_RECEIVER_SOURCES})
    # Link OpenDIS into ExampleReceiver
    target_link_libraries(ExampleReceiver PRIVATE OpenDIS6)
    target_link_libraries(ExampleReceiver PRIVATE ${SDL_LIBS})
    # add src to ExampleSender include directories
    target_include_directories(ExampleReceiver PRIVATE src)
    target_compile_definitions(ExampleReceiver PRIVATE DIS_VERSION=6)
endif()

# Configuring SDL2
#--------------------------------------------------------------------------------------

# If SDL_INC_DIR declared (by user via -D flag)
if(SDL_INC_DIR)
  # Inform the user we will use the their specified SDL_INC_DIR
  message("Using SDL2 include directory defined with -DSDL_INC_DIR")
  message("\tvalue: ${SDL_INC_DIR}")
  # Add SDL_INC_DIR to the include directories for both exampe apps
  target_include_directories(ExampleSender PUBLIC ${SDL_INC_DIR})
  target_include_directories(ExampleReceiver PUBLIC ${SDL_INC_DIR})
else(SDL_INC_DIR)
  # Otherwise, try get SDL2 Compiler Flags from sdl2-config
  execute_process(
    COMMAND sdl2-config --cflags
    RESULT_VARIABLE SDL_CERR
    OUTPUT_VARIABLE SDL_CFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  # if sdl2-config errors
  if(SDL_CERR)
    # warn user that they may have to define the SDL2 include
    #  directory with the -DSDL_INC_DIR flag
    # Most linux systems will probably be fine
    message(WARNING "Unable to detect SDL2 include flags")
    message("You may need to specify the SDL include manually")
    message(" with -DSDL_INC_DIR=<SDL2 include path>")
  else(SDL_CERR)
    # otherwise split the output of sdl2-config and add to compiler flags to examples
    if(WIN32)
      separate_arguments(SDL_CFLAGS UNIX_COMMAND "${SDL_CFLAGS}")
    else(WIN32)
      separate_arguments(SDL_CFLAGS WINDOWS_COMMAND "${SDL_CFLAGS}")
    endif(WIN32)
    if(OPENDIS_BUILD_EXAMPLES AND OPENDIS_PROTOCOL_VERSION STREQUAL "DIS6" OR OPENDIS_PROTOCOL_VERSION STREQUAL "BOTH")
        target_compile_options(ExampleSender PRIVATE "${SDL_CFLAGS}")
        target_compile_options(ExampleReceiver PRIVATE "${SDL_CFLAGS}")
    endif()
  endif(SDL_CERR)
endif(SDL_INC_DIR)

# If SDL_LIB_DIR declared (by user via -D flag)
if(SDL_LIB_DIR)
  message("Using SDL2 include directory defined with -DSDL_LIB_DIR")
  message("\tvalue: ${SDL_LIB_DIR}")
  target_link_directories(ExampleSender PUBLIC ${SDL_LIB_DIR})
  target_link_directories(ExampleReceiver PUBLIC ${SDL_LIB_DIR})
else(SDL_LIB_DIR)
  # Otherwise, try get SDL2 Library Flags from sdl2-config
  execute_process(
    COMMAND sdl2-config --libs
    RESULT_VARIABLE SDL_LERR
    OUTPUT_VARIABLE SDL_LFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  # if sdl2-config errors
  if(SDL_LERR)
    # warn user that they may have to define the SDL2 include
    #  directory with the -DSDL_LIB_DIR flag
    # Most linux systems will probably be fine
    message(WARNING "Unable to detect SDL2 library flags using defaults")
    message("You may need to specify the SDL library manually with")
    message(" -DSDL_LIB_DIR=<SDL2 include path>, especially for Windows users")
  else(SDL_LERR)
    # otherwise split the output of sdl2-config and add to library flags to examples
    if(WIN32)
      separate_arguments(SDL_LFLAGS UNIX_COMMAND "${SDL_LFLAGS}")
    else(WIN32)
      separate_arguments(SDL_LFLAGS WINDOWS_COMMAND "${SDL_LFLAGS}")
    endif(WIN32)
    if(OPENDIS_BUILD_EXAMPLES AND OPENDIS_PROTOCOL_VERSION STREQUAL "DIS6" OR OPENDIS_PROTOCOL_VERSION STREQUAL "BOTH")
        target_link_libraries(ExampleSender PRIVATE "${SDL_LFLAGS}")
        target_link_libraries(ExampleReceiver PRIVATE "${SDL_LFLAGS}")
    endif()
  endif(SDL_LERR)
endif(SDL_LIB_DIR)

#--------------------------------------------------------------------------------------

# include GNUInstallDirs Module to get more generic directory handling
include(GNUInstallDirs)
IF(NOT DEFINED LIBDIR)
  set(LIBDIR "lib")   # Was not defined on Travis CI
ENDIF(NOT DEFINED LIBDIR)
# Configure install target (i.e. what files to install)
if(OPENDIS_PROTOCOL_VERSION STREQUAL "DIS6" OR OPENDIS_PROTOCOL_VERSION STREQUAL "BOTH")
    install(TARGETS OpenDIS6 EXPORT OpenDIS6Config DESTINATION "${LIBDIR}")
    install(EXPORT OpenDIS6Config DESTINATION "lib/cmake/OpenDIS6")
endif()
if(OPENDIS_PROTOCOL_VERSION STREQUAL "DIS7" OR OPENDIS_PROTOCOL_VERSION STREQUAL "BOTH")
    install(TARGETS OpenDIS7 EXPORT OpenDIS7Config DESTINATION "${LIBDIR}")
    install(EXPORT OpenDIS7Config DESTINATION "lib/cmake/OpenDIS7")
endif()
if(OPENDIS_BUILD_EXAMPLES AND OPENDIS_PROTOCOL_VERSION STREQUAL "DIS6" OR OPENDIS_PROTOCOL_VERSION STREQUAL "BOTH")
    install(TARGETS ExampleReceiver ExampleSender DESTINATION "bin")
endif()
install(DIRECTORY src/ DESTINATION "include"
        FILES_MATCHING PATTERN "*.h"
)

# configure package target (i.e. Package Types, and meta data)
set(CPACK_GENERATOR "DEB" "RPM" "TXZ" "TGZ")
set(CPACK_PACKAGE_VERSION 1.0.0)
set(CPACK_PACKAGE_NAME "OpenDis")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The open DIS cpp library")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}.${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_PACKAGE_RPM_DIR "${CMAKE_CURRENT_BINARY_DIR}/_CPack_Packages/Linux/RPM")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Leif Gruenwoldt <leifer@gmail.com>")
set(CPACK_PACKAGE_PACKAGER $ENV{USER})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The open DIS cpp library")
include(CPack)
