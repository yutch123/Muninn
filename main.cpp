#include "src/question/Question.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <filesystem>

#include <ftxui/component/component.hpp> // Интерактивные элементы интерфейса
#include <ftxui/component/screen_interactive.hpp> // Интерактивный экран терминала
#include <ftxui/dom/elements.hpp> // Система построения визуальных элементов терминала

#include <string>

int main()
{
    nlohmann::json data;

    std::cout << std::filesystem::current_path() << std::endl;

    std::ifstream file("../../../data/basic_questions.json");

    if (file.is_open())
    {
        std::cout << "File opened successfully!" << std::endl;
        file >> data;

        file.close();
    }

    else
    {
        std::cout << "Failed to open file!" << std::endl;
        return 1;
    }

    std::cout << "Title: " << data["title"] << std::endl;
    std::cout << "Description: " << data["description"] << std::endl;

    std::cout << "Number of questions: "
        << data["questions"].size() << std::endl;

    std::cout << "Right answer: "
        << data["questions"][0]["expectedAnswer"];

    return 0;

    /*using namespace ftxui;

    auto screen = ScreenInteractive::Fullscreen();

    std::string answer; // Переменная вопроса
    std::string message = "Enter your answer and press Check."; // Переменная ответа

    auto input = Input(&answer, "Type your answer...");
    auto check_button = Button("Check", [&] {
        if (answer == "Muninn") {
            message = "Correct! The raven remembers.";
        }
        else {
            message = "Not quite. Try again!";
        }

        });

    auto component = Container::Vertical({
        input,
        check_button,
        });

    auto renderer = Renderer(component, [&] {
        return vbox({
            text("MUNINN") | bold | center,
            separator(),
            text("Welcome to your knowledge trainer.") | center,
            text(""),
            hbox({
                text("Answer: "),
                input->Render(),
            }),
            text(""),
            hbox({
                filler(),
                check_button->Render(),
                filler(),
            }),
            text(""),
            text(message) | center,
            }) | border | size(WIDTH, GREATER_THAN, 50) | center;
        });

    screen.Loop(renderer);
    */

}


