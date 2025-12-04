cmake_minimum_required(VERSION 3.15)
project(CppAuthApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Fetch Dependencies ---
include(FetchContent)

message(STATUS "Fetching nlohmann/json...")
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG        v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

message(STATUS "Fetching cpp-httplib...")
FetchContent_Declare(
        cpp-httplib
        GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
        GIT_TAG        v0.15.3
)
FetchContent_MakeAvailable(cpp-httplib)

# --- Define Executable ---
add_executable(CppAuthApp main.cpp)

# --- Pass the source directory path to the C++ code ---
# This is the key fix for serving files from the correct location.
target_compile_definitions(CppAuthApp PRIVATE WWW_ROOT_PATH="${CMAKE_SOURCE_DIR}")

# --- Explicitly add include directories for the IDE ---
# THIS IS THE CRITICAL FIX. It tells the compiler where to find the headers.
target_include_directories(CppAuthApp PRIVATE
        ${nlohmann_json_SOURCE_DIR}/include
        ${cpp-httplib_SOURCE_DIR}
)

# --- Link Libraries ---
find_package(Threads REQUIRED)
target_link_libraries(CppAuthApp PRIVATE nlohmann_json::nlohmann_json Threads::Threads)

# On Windows, we must also link the Winsock and Crypto libraries.
if(WIN32)
    target_link_libraries(CppAuthApp PRIVATE ws2_32 crypt32)
endif()