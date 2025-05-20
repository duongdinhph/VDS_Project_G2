add_subdirectory(test)
add_subdirectory(bench)
add_subdirectory(verify)

add_library(Node Node.cpp Node.h)
add_library(Manager Manager.cpp Manager.h)

# Link Node into Manager
target_link_libraries(Manager PRIVATE Node)