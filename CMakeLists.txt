cmake_minimum_required(VERSION 3.15) ## версия CMake

project(Muninn LANGUAGES CXX) ## объявляем проект и язык C++

set(CMAKE_CXX_STANDARD 17) ## Выбираем C++ 17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent) ## Скачиваем библеотеку

FetchContent_Declare(
	ftxui
	GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
	GIT_TAG v5.0.0
)

FetchContent_Declare(
	nlohmann_json
	GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)

FetchContent_MakeAvailable(ftxui nlohmann_json) ## Подключаем её к сборке
add_executable(Muninn main.cpp "src/question/Question.h") ## Указываем, что из main.cpp нужно собирать исполняемый файл

target_link_libraries(Muninn PRIVATE ## Связываем наш исполняемый файл с трёмя модулями 
	ftxui::screen ## отрисовка терминала
	ftxui::dom ## построение терминала
	ftxui::component ## интерактивный компонент
	nlohmann_json::nlohmann_json
)

add_executable(QuestionTest src/question/QuestionTest.cpp)

add_executable(QuestionSet src/question/QuestionSetTest.cpp)