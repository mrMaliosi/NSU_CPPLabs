# CMake generated Testfile for 
# Source directory: C:/Users/Владимир/Desktop/Универ/2 курс/ООП/Malinovskiy_nachalo/lab2_game_of_life_v1.0
# Build directory: C:/Users/Владимир/Desktop/Универ/2 курс/ООП/Malinovskiy_nachalo/lab2_game_of_life_v1.0/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Testfield "Tests")
set_tests_properties(Testfield PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Владимир/Desktop/Универ/2 курс/ООП/Malinovskiy_nachalo/lab2_game_of_life_v1.0/CMakeLists.txt;27;add_test;C:/Users/Владимир/Desktop/Универ/2 курс/ООП/Malinovskiy_nachalo/lab2_game_of_life_v1.0/CMakeLists.txt;0;")
subdirs("Tests")
subdirs("field")
subdirs("UI")
subdirs("MagicWord")
subdirs("googletest")
