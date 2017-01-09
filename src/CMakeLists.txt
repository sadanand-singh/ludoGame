configure_file(${CMAKE_CURRENT_SOURCE_DIR}/defines.h.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/defines.h)

# C++ sources files
file(GLOB_RECURSE CPP_SOURCES *.cpp)
set(RESOURCE_FILES ../resources/resources.qrc)

# Create executable
add_executable(${CMAKE_PROJECT_NAME} ${CPP_SOURCES} ${RESOURCE_FILES})

# Link qt libraries
target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Widgets)
