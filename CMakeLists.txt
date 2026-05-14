cmake_minimum_required(VERSION 3.10)
project(VulkanTest)

# 최신 C++17 이상 사용 권장
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 1. Vulkan SDK 찾기
find_package(Vulkan REQUIRED)

include(FetchContent)

# 2. GLFW 다운로드 설정
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8 # 혹은 최신 버전
)

FetchContent_MakeAvailable(glfw)

#GLM가져오기
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG master 
)
# GLM은 헤더 전용이므로 빌드 옵션을 끕니다 (빌드 시간 단축)
set(GLM_TEST_ENABLE OFF CACHE BOOL "Enable GLM tests")
FetchContent_MakeAvailable(glm)

# 실행 파일 생성 (src 폴더 안의 main.cpp 기준)
add_executable(${PROJECT_NAME} src/main.cpp)

# 4. 찾은 라이브러리들을 내 실행 파일과 링크(연결)하기
target_link_libraries(${PROJECT_NAME} PRIVATE
    Vulkan::Vulkan
    glfw
    glm::glm
)
