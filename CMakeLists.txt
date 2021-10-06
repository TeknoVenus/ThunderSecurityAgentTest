cmake_minimum_required(VERSION 3.5)

project(SecurityAgentTest)

add_executable(${PROJECT_NAME}
    main.cpp
)

find_package(securityagent CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
    securityagent::securityagent
)


install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)