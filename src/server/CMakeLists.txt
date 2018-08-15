add_library(server Server.cpp Server.h)

target_link_libraries(server ${Boost_LIBRARIES})
