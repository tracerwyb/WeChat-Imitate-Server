cmake_minimum_required(VERSION 3.26)

project(WeChat-Imitate-Server LANGUAGES CXX)

include_directories("/usr/include/mysql/")  #add include directories
link_directories("/usr/lib/")  #add lib directories
LINK_LIBRARIES(libmysqlpp.so.3.3.0)  #add lib

#find_package(OpenCV REQUIRED)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(/usr/include/)
#include_directories("/usr/include")
link_directories("/usr/include")

link_libraries(/usr/lib/)


add_executable(WeChat-Imitate-Server
    main.cpp
    user.cpp        user.h
    userbroker.cpp  userbroker.h
    userinterface.h
    userproxy.cpp   userproxy.h

    controller.h
    controllerfactory.cpp    controllerfactory.h
    friendcontroller.cpp    friendcontroller.h
    messagecontroller.cpp   messagecontroller.h
    pushcontroller.cpp      pushcontroller.h
    initcontroller.h        initcontroller.cpp

    message.cpp         message.h
    messagebroker.cpp   messagebroker.h
    messageinterface.h
    messageproxy.cpp    messageproxy.h

    relationalbroker.h  relationalbroker.cpp

    server.cpp          server.h
    network.cpp         network.h
    task.cpp   task.h

)

target_compile_features( WeChat-Imitate-Server PRIVATE cxx_std_20 )
#配置OpenCV库

add_subdirectory(json)

#链接库
target_link_libraries(WeChat-Imitate-Server
    PRIVATE
        nlohmann_json
        opencv_imgcodecs
        opencv_highgui
        Qt6::Widgets
)



include(GNUInstallDirs)
install(TARGETS WeChat-Imitate-Server
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


# Define target properties for Android with Qt 6 as:
#    set_property(TARGET WeChat-Imitate-Server APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation


































































# include(GNUInstallDirs)
# install(TARGETS WeChat-Imitate-Server
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

# target_sources( WeChat-Imitate-Server 
#     PRIVATE
#         main.cpp
#         
#     PUBLIC
#         
# )









    
#target_compile_options( WeChat-Imitate-Server PRIVATE -fmodules-ts )

#target_include_directories( WeChat-Imitate-Server PRIVATE /usr/include )

#target_link_directories( WeChat-Imitate-Server PRIVATE /usr/lib )

#target_link_libraries( WeChat-Imitate-Server PRIVATE m )

#set_target_properties( WeChat-Imitate-Server PROPERTIES
            #CXX_STANDARD 20
            #CXX_EXTENSIONS OFF
            #etc..
            #)
# 设置指定的C++编译器版本是必须的，如果不设置，或者为OFF，则指定版本不可用时，会使用上一版本。
#set_target_properties(WeChat-Imitate-Server PROPERTIES  CXX_STANDARD_REQUIRED on)

## --------------------------------------------------------------------------
## Adding build-requirements
## 源文件列表
#target_sources( <target> PRIVATE <source-file>... )
#
#target_precompile_headers( <target> PRIVATE <header-file>... )
#
## 预处理头文件搜索路径列表，等价参数：-I
#target_include_directories( <target> PRIVATE <include-search-dir>... )  
#
## 预编译宏 自动在指定的宏前添加，等价参数：-D
#target_compile_definitions( <target> PRIVATE <macro-definitions>... )  
#
## 编译选项和特性
#target_compile_options( <target> PRIVATE <compiler-option>... )
#target_compile_features( <target> PRIVATE <feature>... )
#
## 链接库
#target_link_libraries( <target> PRIVATE <dependency>... )
#
## 链接选项
#target_link_options( <target> PRIVATE <linker-option>... )
#
## 链接库搜索路径，等价参数：-L
#target_link_directories( <target> PRIVATE <linker-search-dir>... )

#execute_process(COMMAND ln -s /opt/gcc/gcm.cache  ./)

## Modern Cmake建议围绕Target和Property进行项目配置，竭力避免出现下面变量variable的set定义。
## Variable横行是典型CMake2.8时期的风格, Modern CMake则遵循了OO方法。其中，target表示待构建的对象，
## target相关的语句用于定义来约束link、compile等相关属性的scope。
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)    


# cmake_minimum_required(VERSION 3.5)
# 
# project(WeChat-Imitate-Server VERSION 0.1 LANGUAGES CXX)
# 
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# 
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 
# @if false
# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
# 
# set(TS_FILES )
# @else
# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
# @endif
# 
# set(PROJECT_SOURCES
#         main.cpp
#         mainwindow.cpp
#         mainwindow.h
#     @if true
#         mainwindow.ui
#     @endif
#     @if false
#         ${TS_FILES}
#     @endif
# )
# 
# if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#     qt_add_executable(WeChat-Imitate-Server
#         MANUAL_FINALIZATION
#         ${PROJECT_SOURCES}
#     )
# # Define target properties for Android with Qt 6 as:
# #    set_property(TARGET WeChat-Imitate-Server APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
# @if false
# 
#     qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
# @endif
# else()
#     if(ANDROID)
#         add_library(WeChat-Imitate-Server SHARED
#             ${PROJECT_SOURCES}
#         )
# # Define properties for Android with Qt 5 after find_package() calls as:
# #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#     else()
#         add_executable(WeChat-Imitate-Server
#             ${PROJECT_SOURCES}
#         )
#     endif()
# @if false
# 
#     qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
# @endif
# endif()
# 
# target_link_libraries(WeChat-Imitate-Server PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
# 
# # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# # If you are developing for iOS or macOS you should consider setting an
# # explicit, fixed bundle identifier manually though.
# if(${QT_VERSION} VERSION_LESS 6.1.0)
#   set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.WeChat-Imitate-Server)
# endif()
# set_target_properties(WeChat-Imitate-Server PROPERTIES
#     ${BUNDLE_ID_OPTION}
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )
# 
# include(GNUInstallDirs)
# install(TARGETS WeChat-Imitate-Server
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
# 
# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(WeChat-Imitate-Server)
# endif()

###完整的project命令
#project( WeChat-Imitate-Server LANGUAGES CXX )
         # DESCRIPTION "Description of project" HOMEPAGE_URL "http://www.abc.com" VERSION 0.1.0 )
#execute_process(COMMAND g++ -std=c++20 -xc++-system-header -fmodules-ts # 如何要使用modules,该命令应该放在project命令之后
#                iostream
#                string )

