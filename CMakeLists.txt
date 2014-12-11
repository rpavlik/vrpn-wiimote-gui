# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu> <abiryan@ryandnet>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

cmake_minimum_required(VERSION 2.6)

# Set package properties
project(wiimote-gui)

# Define executable name as a CMake variable
set(EXECUTABLE_NAME "wiimote-wand-gui")

set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VERSION
	"${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")


###
# Perform build configuration of dependencies
###

# Build Wiiuse statically as a subproject
set(BUILD_WIIUSE_SHARED_LIB FALSE CACHE INTERNAL "" FORCE)
add_subdirectory(wiiuse)

# Build VRPN as subproject
set(WIIUSE_RUNTIME_LIBRARY ${WIIUSE_LIBRARY} CACHE INTERNAL "" FORCE)
add_definitions(-DWIIUSE_STATIC)
set(VRPN_USE_WIIUSE TRUE CACHE INTERNAL "" FORCE)
set(VRPN_GPL_SERVER TRUE CACHE INTERNAL "" FORCE)
set(VRPN_BUILD_SERVER_LIBRARY TRUE CACHE INTERNAL "" FORCE)
add_subdirectory(vrpn)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(UseBackportedModules)

find_package(Qt4 COMPONENTS QtMain QtCore QtGui QtSVG REQUIRED)
include(${QT_USE_FILE})

###
# Build the project
###

set(EXTRA_LIBS ${QT_LIBRARIES} ${VRPN_SERVER_LIBRARY})
include_directories(${VRPN_INCLUDE_DIRS})
add_definitions(${VRPN_DEFINITIONS})
set(VRPN_FOUND TRUE)

add_subdirectory(QWiimoteWidget)
add_subdirectory(qvrpn)
include_directories(${QVRPN_INCLUDE_DIRS})

set(SOURCES
	main.cpp
	mainwindow.cpp
	wiimotewand.cpp
	WiimoteToolboxPanel.cpp)

set(HEADERS)

set(UIS mainwindow.ui
	wiimotepanel.ui)

set(MOCS
	mainwindow.h
	WiimoteToolboxPanel.h
	wiimotewand.h)

set(RESOURCES wiimoteresources.qrc)

# Let QT pre-process the files and add the generated files to the source list
qt4_wrap_ui(GENERATED_SOURCES ${UIS})
qt4_add_resources(GENERATED_SOURCES ${RESOURCES})
qt4_wrap_cpp(GENERATED_SOURCES ${MOCS})


source_group("Generated Sources - Do Not Edit" FILES ${GENERATED_SOURCES})

# Make sure the compiler can find the pre-processed files from qt4_wrap_ui
include_directories(${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

# Build and link the app!
add_executable(${EXECUTABLE_NAME}
	MACOSX_BUNDLE
	WIN32
	${SOURCES}
	${GENERATED_SOURCES}
	${HEADERS}
	${UIS}
	${MOCS}
	${RESOURCES})

target_link_libraries(${EXECUTABLE_NAME} QWiimoteWidget ${QVRPN_LIBRARIES} ${EXTRA_LIBS})


include(InstallRequiredSystemLibraries)

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
