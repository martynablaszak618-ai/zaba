cmake_minimum_required(VERSION 3.20)
project(ZabaNaUlicy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(zaba_na_ulicy
    src/main.cpp
    src/Pozycja.cpp
    src/UstawieniaTrudnosci.cpp
    src/ScenariuszRuchu.cpp
    src/Zaba.cpp
    src/Samochod.cpp
    src/PasRuchu.cpp
    src/Droga.cpp
    src/WykrywaczKolizji.cpp
    src/ZegarGry.cpp
    src/InterfejsGraficzny.cpp
    src/Gra.cpp
)

target_include_directories(zaba_na_ulicy PRIVATE include)
target_link_libraries(zaba_na_ulicy PRIVATE Qt6::Widgets)

if(MSVC)
    target_compile_options(zaba_na_ulicy PRIVATE /utf-8)
else()
    target_compile_options(zaba_na_ulicy PRIVATE -finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

enable_testing()

add_executable(testy_logiki
    tests/TestyLogiki.cpp
    src/Pozycja.cpp
    src/UstawieniaTrudnosci.cpp
    src/ScenariuszRuchu.cpp
    src/Zaba.cpp
    src/Samochod.cpp
    src/PasRuchu.cpp
    src/Droga.cpp
    src/WykrywaczKolizji.cpp
    src/ZegarGry.cpp
    src/Gra.cpp
)
target_include_directories(testy_logiki PRIVATE include)
add_test(NAME testy_logiki COMMAND testy_logiki)
