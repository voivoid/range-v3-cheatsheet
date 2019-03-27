add_executable(CheatSheet main.cpp views.cpp utils.h)
target_link_libraries(CheatSheet PRIVATE Boost::boost Boost::unit_test_framework range-v3)

add_test(NAME ViewTests
  COMMAND $<TARGET_FILE:CheatSheet> --run_test=RangeV3ViewsTests/*)
