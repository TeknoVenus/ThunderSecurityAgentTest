cmake_minimum_required(VERSION 3.5)

project(SecurityAgentTest)

set( CMAKE_CXX_STANDARD          14  )
set( CMAKE_CXX_STANDARD_REQUIRED ON  )
set( CMAKE_CXX_EXTENSIONS        OFF )

add_executable(${PROJECT_NAME}
    main.cpp
)

add_library(SecurityAgentTestLib
    SHARED
    secagent.cpp
)

find_package(securityagent CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
    securityagent::securityagent
    ${CMAKE_DL_LIBS}
)

target_link_libraries(SecurityAgentTestLib
    securityagent::securityagent
)


install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(TARGETS SecurityAgentTestLib RUNTIME DESTINATION lib)