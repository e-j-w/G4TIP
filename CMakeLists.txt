# $Id: CMakeLists.txt 86065 2014-11-07 08:51:15Z gcosmo $

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(TIP_FE_RDM)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# For ROOT
# Make sure $ROOTSYS is defined.
# May need to edit FindROOT.cmake line 51 to say 'include(CMakeParseArguments)' 
# rather than 'include(CMakeMacroParseArguments)' if an error occurs
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{ROOTSYS}/etc/cmake)
find_package(ROOT REQUIRED)
include_directories(SYSTEM $ENV{ROOTINC})

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/include)
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 and ROOT libraries
#
add_executable(TIP_FE_RDM TIP_FE_RDM.cc ${sources} ${headers})
target_link_libraries(TIP_FE_RDM ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build TIP_FE_RDM
#
set(TIPFUSEVAP_SCRIPTS
  1274level_rdm.mac
  gui/vis.mac
  gui/gui.mac
  )

foreach(_script ${TIPFUSEVAP_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
#add_custom_target(B1 DEPENDS exampleB1)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS TIP_FE_RDM DESTINATION bin)


