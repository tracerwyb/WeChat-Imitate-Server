cmake_minimum_required(VERSION 3.27)

project(Wechat-Server VERSION 0.1 LANGUAGES CXX)


include_directories("/usr/include/mysql/")  #add include directories

LINK_DIRECTORIES("/usr/lib/")  #add lib directories
LINK_LIBRARIES(libmysqlpp.so.3.3.0)  #add lib

add_executable(appWechat-Server
)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

target_sources( appWechat-Server PRIVATE
    PRIVATE
    main.cpp
    User.cpp        User.h
    UserBroker.cpp  UserBroker.h
    UserInterface.h
    UserProxy.cpp   UserProxy.h

    Controller.h
    ControllerFactory.cpp    ControllerFactory.h
    FriendController.cpp    FriendController.h
    MessageController.cpp   MessageController.h
    PushController.cpp      PushController.h
    InitController.h        InitController.cpp

    message.cpp         message.h
    MessageBroker.cpp   MessageBroker.h
    MessageInterface.h
    MessageProxy.cpp    MessageProxy.h

    RelationalBroker.h  RelationalBroker.cpp

    Server.cpp          Server.h
    network.cpp         network.h
    threadpool.cpp        threadpool.h

)

target_compile_features( appWechat-Server PRIVATE cxx_std_20 )

add_subdirectory(json)

#链接库
target_link_libraries(appWechat-Server
    PRIVATE
    mariadbcpp
    pthread
    nlohmann_json
    Qt6::Widgets
)

#######
set_target_properties(appWechat-Server PROPERTIES
    AUTORCC TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
include(GNUInstallDirs)
install(TARGETS appWechat-Server
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
qt_finalize_executable(appWechat-Server)














































# target_sources(server-network
#     PRIVATE
#         main.cpp
#         mainwindow.cpp
#         mainwindow.h
#     @if true
#         mainwindow.ui
#     @endif
#     @if false
#         
#     @endif
#         
#     PUBLIC
#         
# )

# qt_standard_project_setup()     #set(CMAKE_AUTOUIC ON)  set(CMAKE_AUTOMOC ON)
# set_target_properties(server-network PROPERTIES
#     MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )
# 
# install(TARGETS server-network
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
# 
# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(server-network)
# endif()





#qt_add_executable(server-network)  //Creates and finalizes an application target of a platform-specific type.
#This command performs the following tasks:

#    1. Create a CMake target of the appropriate type for the target platform.
#    2. Link the target to the Qt::Core library.
#    3. Handle finalization of the CMake target.












# cmake_minimum_required(VERSION 3.5)
# 
# project(server-network VERSION 0.1 LANGUAGES CXX)
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
#     qt_add_executable(server-network
#         MANUAL_FINALIZATION
#         ${PROJECT_SOURCES}
#     )
# # Define target properties for Android with Qt 6 as:
# #    set_property(TARGET server-network APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
# @if false
# 
#     qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
# @endif
# else()
#     if(ANDROID)
#         add_library(server-network SHARED
#             ${PROJECT_SOURCES}
#         )
# # Define properties for Android with Qt 5 after find_package() calls as:
# #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#     else()
#         add_executable(server-network
#             ${PROJECT_SOURCES}
#         )
#     endif()
# @if false
# 
#     qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
# @endif
# endif()
# 
# target_link_libraries(server-network PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
# 
# # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# # If you are developing for iOS or macOS you should consider setting an
# # explicit, fixed bundle identifier manually though.
# if(${QT_VERSION} VERSION_LESS 6.1.0)
#   set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.server-network)
# endif()
# set_target_properties(server-network PROPERTIES
#     ${BUNDLE_ID_OPTION}
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )
# 
# include(GNUInstallDirs)
# install(TARGETS server-network
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
# 
# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(server-network)
# endif()
>>>>>>> origin/sendmsg-network
