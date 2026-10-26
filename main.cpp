#include <ftxui/component/component.hpp> // Интерактивные элементы интерфейса
#include <ftxui/component/screen_interactive.hpp> // Интерактивный экран терминала
#include <ftxui/dom/elements.hpp> // Система построения визуальных элементов терминала

#include <string>

int main()
{
    using namespace ftxui;

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

}


