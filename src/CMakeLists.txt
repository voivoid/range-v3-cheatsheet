add_executable(CheatSheet main.cpp views.cpp utils.h)
target_link_libraries(CheatSheet PRIVATE Boost::boost Boost::unit_test_framework range-v3)
