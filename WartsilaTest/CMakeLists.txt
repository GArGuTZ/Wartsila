project(WartsilaTest LANGUAGES CXX)
cmake_minimum_required(VERSION 3.0)

add_executable(detector WartsilaTest/Finder.h WartsilaTest/Finder.cpp WartsilaTest/main.cpp)
if(TARGET detector)
    message("The detector was defined!")
else()
    message("The detector was not defined!")
endif()

if(CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_CONFIGURATION_TYPES Debug Release)
  set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "" FORCE)
endif()

set(DETECTOR_TIMEOUT 1)

enable_testing()
include(CTest)

add_test(Test01 detector 2)
add_test(Test02 detector "H:/ABECEDA")
add_test(Test03 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/00.txt")
add_test(Test04 detector)
add_test(Test05 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/00.txt" 6 814335)

add_test(Square01 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/Square01.txt")
add_test(Square02 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/Square02.txt")
add_test(Square03 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/Square03.txt")
add_test(Square04 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/Square04.txt")
add_test(Square05 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/Square05.txt")
add_test(Square06 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/Square06.txt")

add_test(SquareBorder01 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareBorder01.txt")
add_test(SquareBorder02 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareBorder02.txt")
add_test(SquareBorder03 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareBorder03.txt")
add_test(SquareBorder04 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareBorder04.txt")
add_test(SquareBorder05 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareBorder05.txt")

add_test(SquareOuter01 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareOuter01.txt")
add_test(SquareOuter02 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareOuter02.txt")
add_test(SquareOuter03 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareOuter03.txt")
add_test(SquareOuter04 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareOuter04.txt")
add_test(SquareOuter05 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareOuter05.txt")

add_test(SquareInner01 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareInner01.txt")
add_test(SquareInner02 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareInner02.txt")
add_test(SquareInner03 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareInner03.txt")
add_test(SquareInner04 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareInner04.txt")
add_test(SquareInner05 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareInner05.txt")
add_test(SquareInner041 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareInner04.txt" 1)
add_test(SquareInner051 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareInner05.txt" 1)
add_test(SquareInner011 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareInner01.txt" 1)
add_test(SquareInner021 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareInner02.txt" 1)
add_test(SquareInner031 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareInner03.txt" 1)
add_test(SquareInner042 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareInner04.txt" 2)
add_test(SquareInner052 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/SquareInner05.txt" 2)

add_test(Round01 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/Round01.txt")
add_test(Round02 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/Round02.txt")
add_test(Round03 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/Round03.txt")
add_test(Round04 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/Round04.txt")
add_test(Round05 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/Round05.txt")
add_test(Round06 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/Round06.txt")

add_test(RoundBad01 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/RoundBad01.txt")
add_test(RoundBad02 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/RoundBad02.txt")
add_test(RoundBad03 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/RoundBad03.txt")
add_test(RoundBad04 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/RoundBad04.txt")
add_test(RoundBad05 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/RoundBad05.txt")
add_test(RoundBad06 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/RoundBad06.txt")

add_test(RoundOuter01 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/RoundOuter01.txt")
add_test(RoundOuter02 detector "${CMAKE_CURRENT_SOURCE_DIR}/Test_figures/RoundOuter02.txt")

set_tests_properties(Test01 Test02 Test03 Test04 Test05
Square01 Square02 Square03 Square04 Square05 Square06
SquareBorder01 SquareBorder02 SquareBorder03 SquareBorder04 SquareBorder05
SquareOuter01 SquareOuter02 SquareOuter03 SquareOuter04 SquareOuter05
SquareInner01 SquareInner02 SquareInner03 SquareInner04 SquareInner05 SquareInner041 SquareInner051 SquareInner011 SquareInner021 SquareInner031 SquareInner042 SquareInner052
Round01 Round02 Round03 Round04 Round05 Round06 
RoundBad01 RoundBad02 RoundBad03 RoundBad04 RoundBad05 RoundBad06 
RoundOuter01 RoundOuter02 PROPERTIES TIMEOUT ${DETECTOR_TIMEOUT})

set_tests_properties(Test01 PROPERTIES PASS_REGULAR_EXPRESSION "Error opening file")
set_tests_properties(Test02 PROPERTIES PASS_REGULAR_EXPRESSION "Error opening file")
set_tests_properties(Test03 PROPERTIES PASS_REGULAR_EXPRESSION "Image is empty" FAIL_REGULAR_EXPRESSION "Error opening file")
set_tests_properties(Test04 PROPERTIES PASS_REGULAR_EXPRESSION "Too few arguments")
set_tests_properties(Test05 PROPERTIES PASS_REGULAR_EXPRESSION "Too many arguments")

set_tests_properties(Square01 PROPERTIES PASS_REGULAR_EXPRESSION "Square, edge length = 5, 4,7")
set_tests_properties(Square02 PROPERTIES PASS_REGULAR_EXPRESSION "Square, edge length = 6, 4,6")
set_tests_properties(Square03 PROPERTIES PASS_REGULAR_EXPRESSION "Square, edge length = 7, 3,5")
set_tests_properties(Square04 PROPERTIES PASS_REGULAR_EXPRESSION "Square, edge length = 8, 3,4")
set_tests_properties(Square05 PROPERTIES PASS_REGULAR_EXPRESSION "Square, edge length = 9, 3,4")
set_tests_properties(Square06 PROPERTIES PASS_REGULAR_EXPRESSION "Square, edge length = 10, 2,3")

set_tests_properties(SquareBorder01 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(SquareBorder02 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(SquareBorder03 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(SquareBorder04 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(SquareBorder05 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")

set_tests_properties(SquareOuter01 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(SquareOuter02 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(SquareOuter03 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(SquareOuter04 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(SquareOuter05 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")

set_tests_properties(SquareInner01 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(SquareInner02 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(SquareInner03 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(SquareInner04 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(SquareInner05 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(SquareInner041 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(SquareInner051 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(SquareInner011 PROPERTIES PASS_REGULAR_EXPRESSION "Square, edge length = 7, 3,5")
set_tests_properties(SquareInner021 PROPERTIES PASS_REGULAR_EXPRESSION "Square, edge length = 7, 3,5")
set_tests_properties(SquareInner031 PROPERTIES PASS_REGULAR_EXPRESSION "Square, edge length = 7, 3,5")
set_tests_properties(SquareInner042 PROPERTIES PASS_REGULAR_EXPRESSION "Square, edge length = 7, 3,5")
set_tests_properties(SquareInner052 PROPERTIES PASS_REGULAR_EXPRESSION "Square, edge length = 7, 3,5")

set_tests_properties(Round01 PROPERTIES PASS_REGULAR_EXPRESSION "Round, diameter = 5, 9,6")
set_tests_properties(Round02 PROPERTIES PASS_REGULAR_EXPRESSION "Round, diameter = 6, 10,6")
set_tests_properties(Round03 PROPERTIES PASS_REGULAR_EXPRESSION "Round, diameter = 7, 9,7")
set_tests_properties(Round04 PROPERTIES PASS_REGULAR_EXPRESSION "Round, diameter = 8, 9,7")
set_tests_properties(Round05 PROPERTIES PASS_REGULAR_EXPRESSION "Round, diameter = 9, 8,7")
set_tests_properties(Round06 PROPERTIES PASS_REGULAR_EXPRESSION "Round, diameter = 10, 8,7")

set_tests_properties(RoundBad01 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(RoundBad02 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(RoundBad03 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(RoundBad04 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(RoundBad05 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(RoundBad06 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")

set_tests_properties(RoundOuter01 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")
set_tests_properties(RoundOuter02 PROPERTIES PASS_REGULAR_EXPRESSION "Unknown figure")

install(TARGETS detector DESTINATION bin)