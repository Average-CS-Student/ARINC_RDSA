cmake_minimum_required(VERSION 3.19)
project(ARINC_RDSA LANGUAGES CXX)

if(MSVC)
    add_compile_options(/bigobj)
endif()

find_path(Qt6_DIR REQUIRED)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Sql)
find_package(Qt6 6.5 REQUIRED COMPONENTS 3DCore)
find_package(Qt6 6.5 REQUIRED COMPONENTS 3DRender)
find_package(Qt6 6.5 REQUIRED COMPONENTS 3DExtras)
find_package(Qt6 6.5 REQUIRED COMPONENTS 3DInput)

find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
find_package(Armadillo CONFIG REQUIRED)

find_path(MLPACK_INCLUDE_DIRS "mlpack.hpp" REQUIRED)

find_path(MYSQL_INCLUDE_DIRS "mysql.h" REQUIRED)
find_library(MYSQL_LIBRARIES NAMES mysqlclient libmysql REQUIRED)

qt_standard_project_setup()

set(SOURCE_DIR source)

set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/mainwindow.cpp
    ${SOURCE_DIR}/mainwindow.h
    ${SOURCE_DIR}/mainwindow.ui
    ${SOURCE_DIR}/Arinc429.cpp
    ${SOURCE_DIR}/Arinc429.h
    ${SOURCE_DIR}/COMCon.cpp
    ${SOURCE_DIR}/COMCon.h
    ${SOURCE_DIR}/DataBaseConnection.cpp
    ${SOURCE_DIR}/DataBaseConnection.h
    ${SOURCE_DIR}/NeuralNetwork.cpp
    ${SOURCE_DIR}/NeuralNetwork.h
    ${SOURCE_DIR}/COMConQWrapper.h
    ${SOURCE_DIR}/COMConQWrapper.cpp
    ${SOURCE_DIR}/SharedBuffer.h
    ${SOURCE_DIR}/SharedBuffer.cpp
    ${SOURCE_DIR}/bodypryara.h
    ${SOURCE_DIR}/bodypryara.cpp
    ${SOURCE_DIR}/altitudeefi.h
    ${SOURCE_DIR}/altitudeefi.cpp
    ${SOURCE_DIR}/speedwidget.h
    ${SOURCE_DIR}/speedwidget.cpp
    ${SOURCE_DIR}/headingwidget.h
    ${SOURCE_DIR}/headingwidget.cpp
)

qt_add_executable(ARINC_RDSA
    WIN32 MACOSX_BUNDLE
    ${SOURCES}
)

target_include_directories(ARINC_RDSA
    PRIVATE
        ${MLPACK_INCLUDE_DIRS}
        ${MYSQL_INCLUDE_DIRS}
)

target_link_libraries(ARINC_RDSA
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
        Qt6::3DCore
        Qt6::3DRender
        Qt6::3DExtras
        Qt6::3DInput
        Ws2_32
        ${MYSQL_LIBRARIES}
        armadillo
        ${BLAS_LIBRARIES}
        ${LAPACK_LIBRARIES}
)

include(GNUInstallDirs)

install(TARGETS ARINC_RDSA
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ARINC_RDSA
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
