# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu> <abiryan@ryandnet>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

set(SOURCES
	QWiimoteWidget.cpp)

set(HEADERS)

#set(UIS QWiimoteWidget.ui)

set(MOCS
	QWiimoteWidget.h)

set(RESOURCES wiimotewidget.qrc)

# Let QT pre-process the files and add the generated files to the source list
#qt4_wrap_ui(GENERATED_SOURCES ${UIS})
qt4_add_resources(GENERATED_SOURCES ${RESOURCES})
qt4_wrap_cpp(GENERATED_SOURCES ${MOCS})


source_group("Generated Sources - Do Not Edit" FILES ${GENERATED_SOURCES})

# Make sure the compiler can find the pre-processed files from qt4_wrap_ui
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Build and link the app!
add_library(QWiimoteWidget STATIC
	${SOURCES}
	${GENERATED_SOURCES}
	${HEADERS}
	${UIS}
	${MOCS}
	${RESOURCES})

target_link_libraries(QWiimoteWidget ${EXTRA_LIBS})
