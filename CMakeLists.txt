cmake_minimum_required(VERSION 3.27)

project(Wechat-Server VERSION 0.1 LANGUAGES CXX)


include_directories("/usr/include/mysql/")  #add include directories

LINK_DIRECTORIES("/usr/lib/")  #add lib directories
LINK_LIBRARIES(libmysqlpp.so.3.3.0)  #add lib

add_executable(appWechat-Server
)

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

    Message.cpp         Message.h
    MessageBroker.cpp   MessageBroker.h
    MessageInterface.h
    MessageProxy.cpp    MessageProxy.h

    RelationalBroker.h  RelationalBroker.cpp

    Server.cpp          Server.h
    netWork.cpp         netWork.h
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
)
