cmake_minimum_required(VERSION 3.8)
project(ros_serial_c)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall-Wextra -Wpendantic)
endif()

# 필수 패키지 찾기
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# LibSerial 라이브러리 찾기 (PkgConfig 사용)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBSERIAL REQUIRED libserial)

# 헤더 파일 경로 포함
include_directories(${LIBSERIAL_INCLUDE_DIRS})

# 실행 파일 생성: serial_pub
add_executable(serial_pub src/serial_pub.cpp)
ament_target_dependencies(serial_pub rclcpp std_msgs)
# LibSerial 라이브러리 링크
target_link_libraries(serial_pub ${LIBSERIAL_LIBRARIES})
target_compile_options(serial_pub PRIVATE ${LIBSERIAL_CFLAGS_OTHER})

# 실행 파일 생성: serial_sub
add_executable(serial_sub src/serial_sub.cpp)
ament_target_dependencies(serial_sub rclcpp std_msgs)
target_link_libraries(serial_sub ${LIBSERIAL_LIBRARIES})
target_compile_options(serial_sub PRIVATE ${LIBSERIAL_CFLAGS_OTHER})

# 설치 경로 지정
install(
  TARGETS
  serial_pub
  serial_sub
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
