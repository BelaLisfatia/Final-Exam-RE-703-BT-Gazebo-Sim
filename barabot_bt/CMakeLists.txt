cmake_minimum_required(VERSION 3.8)
project(barabot_bt)

# =====================================================
# Compiler options
# =====================================================
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# =====================================================
# Find dependencies
# =====================================================
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(behaviortree_cpp_v3 REQUIRED)
find_package(nav_msgs REQUIRED)

# =====================================================
# Build executable
# =====================================================
add_executable(bt_main
  src/bt_main.cpp
)

# 🔴 INI YANG TADI HILANG
target_include_directories(bt_main PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(bt_main
  rclcpp
  geometry_msgs
  std_msgs
  behaviortree_cpp_v3
  nav_msgs
)

# =====================================================
# Install
# =====================================================
install(TARGETS bt_main
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include/
)

install(DIRECTORY trees
  DESTINATION share/${PROJECT_NAME}
)

# =====================================================
# Testing
# =====================================================
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

