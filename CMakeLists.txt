cmake_minimum_required(VERSION 3.0)
project(Basalt)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt5 REQUIRED Widgets)
find_package(OpenCV 3 REQUIRED)
find_package(yaml-cpp)
find_package(Eigen3)

include_directories(${YAML_CPP_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIR})
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/interface/createNewProject
                    ${PROJECT_SOURCE_DIR}/interface/createProjectFile
                    ${PROJECT_SOURCE_DIR}/interface/loadProject
                    ${PROJECT_SOURCE_DIR}/interface/MainWindow
                    ${PROJECT_SOURCE_DIR}/interface/newProject
                    ${PROJECT_SOURCE_DIR}/methods/FLDAPanel
                    ${PROJECT_SOURCE_DIR}/methods/KFDAPanel
                    ${PROJECT_SOURCE_DIR}/methods/include
                    )



add_library(common ${PROJECT_SOURCE_DIR}/methods/src/common.cpp)
target_link_libraries(common ${OpenCV_LIBS} Qt5::Widgets)

add_library(dataLoader ${PROJECT_SOURCE_DIR}/methods/src/dataloader.cpp)
target_link_libraries(dataLoader common ${OpenCV_LIBS})

add_library(FLDA ${PROJECT_SOURCE_DIR}/methods/src/flda.cpp)
target_link_libraries(FLDA common)

add_library(kernel ${PROJECT_SOURCE_DIR}/methods/src/kernel.cpp)

add_library(KFDA ${PROJECT_SOURCE_DIR}/methods/src/kfda.cpp)
target_link_libraries(KFDA common kernel)

add_library(FLDAPanel ${PROJECT_SOURCE_DIR}/methods/FLDAPanel/fldapanel.cpp )
target_link_libraries(FLDAPanel FLDA dataLoader common Qt5::Widgets ${YAML_CPP_LIBRARIES} ${OpenCV_LIBS})


add_library(KFDAPanel ${PROJECT_SOURCE_DIR}/methods/KFDAPanel/kfdapanel.cpp)
target_link_libraries(KFDAPanel KFDA dataLoader common Qt5::Widgets ${YAML_CPP_LIBRARIES} ${OpenCV_LIBS})


add_library(loadProject ${PROJECT_SOURCE_DIR}/interface/loadProject/loadproject.cpp)
target_link_libraries(loadProject Qt5::Widgets)

add_library(createProjectFile ${PROJECT_SOURCE_DIR}/interface/createProjectFile/createprojectfile.cpp)
target_link_libraries(createProjectFile ${YAML_CPP_LIBRARIES} Qt5::Widgets)

add_library(createNewProject ${PROJECT_SOURCE_DIR}/interface/createNewProject/createnewproject.cpp)
target_link_libraries(createNewProject createProjectFile Qt5::Widgets)

add_library(newProject ${PROJECT_SOURCE_DIR}/interface/newProject/newproject.cpp)
target_link_libraries(newProject createNewProject Qt5::Widgets)

add_library(MainWindow ${PROJECT_SOURCE_DIR}/interface/MainWindow/mainwindow.cpp)
target_link_libraries(MainWindow common KFDAPanel FLDAPanel loadProject newProject ${YAML_CPP_LIBRARIES} Qt5::Widgets)

add_executable(main main.cpp)
target_link_libraries(main Qt5::Widgets MainWindow)



