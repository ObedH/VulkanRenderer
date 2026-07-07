cmake_minimum_required(VERSION 3.22)
project(VulkanRenderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp
        src/VulkanRenderer.cpp
        src/VulkanInstance.cpp
        src/DebugMessenger.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Vulkan::Vulkan
        glfw
        glm::glm
)


#if(VULKAN_GLSLANG_VALIDATOR)
#    set(SHADER_SOURCES

