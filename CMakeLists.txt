# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu> <abiryan@ryandnet>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

cmake_minimum_required(VERSION 2.6)

# Set package properties
project(wiimote-gui)

set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VERSION
	"${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

###
# Options
###

if(WIN32)
	set(INSTALL_WIIUSE_LIBRARY ON)
	set(RUNTIME_LIBRARY_INSTALL_DIR bin)
else()
	option(INSTALL_WIIUSE_LIBRARY "Whether we should install the WiiUse shared library despite being on a platform that should know better." OFF)
	set(RUNTIME_LIBRARY_INSTALL_DIR lib)
endif()

###
# Perform build configuration of dependencies
###

if(INSTALL_WIIUSE_LIBRARY)
	# Always point to WiiUse, for safety's sake
	set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${RUNTIME_LIBRARY_INSTALL_DIR}")
endif()

# Locally-developed modules dist'ed with this app - always have this first.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(UseBackportedModules)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED) #QtMain
include(${QT_USE_FILE})

find_package(VRPN REQUIRED)

if(NOT APPLE)
	find_package(WiiUse REQUIRED)
endif()

###
# Build the project
###
set(EXTRA_LIBS ${QT_LIBRARIES} ${VRPN_SERVER_LIBRARIES} ${WIIUSE_LIBRARIES})
include_directories(${VRPN_INCLUDE_DIRS})

add_subdirectory(QWiimoteWidget)

set(SOURCES
	main.cpp
	mainwindow.cpp
	wiimotewand.cpp
	WiimoteToolboxPanel.cpp
	vrpn_MainloopContainer.cpp
	vrpn_QMainloopContainer.cpp)

set(HEADERS
	vrpn_ConnectionPtr.h
	vrpn_MainloopContainer.h
	vrpn_MainloopObject.h)

set(UIS mainwindow.ui
	wiimotepanel.ui)

set(MOCS
	mainwindow.h
	vrpn_QMainloopContainer.h
	WiimoteToolboxPanel.h
	wiimotewand.h)

set(RESOURCES wiimoteresources.qrc)

# Let QT pre-process the files and add the generated files to the source list
qt4_wrap_ui(GENERATED_SOURCES ${UIS})
qt4_add_resources(GENERATED_SOURCES ${RESOURCES})
qt4_wrap_cpp(GENERATED_SOURCES ${MOCS})


source_group("Generated Sources - Do Not Edit" FILES ${GENERATED_SOURCES})

# Make sure the compiler can find the pre-processed files from qt4_wrap_ui
include_directories(${CMAKE_BINARY_DIR})

# Build and link the app!
add_executable(wiimote-wand-gui
	MACOSX_BUNDLE
	#WIN32
	${SOURCES}
	${GENERATED_SOURCES}
	${HEADERS}
	${UIS}
	${MOCS}
	${RESOURCES})

target_link_libraries(wiimote-wand-gui QWiimoteWidget ${EXTRA_LIBS})


if(INSTALL_WIIUSE_LIBRARY)
	# Install the WiiUse DLL
	install(FILES ${WIIUSE_RUNTIME_LIBRARY}
		DESTINATION ${RUNTIME_LIBRARY_INSTALL_DIR})
endif()

include(InstallRequiredSystemLibraries)
