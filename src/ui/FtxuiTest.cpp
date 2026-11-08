#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

#include "../loader/QuestionSetLoader.h"
#include "../question/QuestionSet.h"

#include <string>

int main()
{
    auto screen = ftxui::ScreenInteractive::Fullscreen();

    int selectedItem = 0;

    int currentScreen = 0;

    int selectedSet = 0;

    QuestionSet questionSet;
    QuestionSetLoader loader;
    std::string error;

    bool isLoaded = loader.LoadFromFile(
        "../../../data/LogicPuzzles.json",
        questionSet,
        error
    );

    ftxui::Component component = ftxui::Renderer([&]() -> ftxui::Element {

        if (currentScreen == 0)
        {
            auto title = ftxui::text("KNOWLEDGE TRAINER")
                | ftxui::bold
                | ftxui::color(ftxui::Color::White);

            auto subtitle = ftxui::text("LEARN | PRACTICE | IMPROVE")
                | ftxui::color(ftxui::Color::RGB(145, 145, 145))
                | ftxui::dim;

            auto header = ftxui::vbox({
                title | ftxui::center,
                ftxui::hbox({
                    ftxui::text(" "),
                    subtitle
                })
                }) | ftxui::center;

            auto menuItem = [](const std::string& label, bool selected) -> ftxui::Element {
                if (selected) {
                    return ftxui::text("  > " + label + "  ")
                        | ftxui::bold
                        | ftxui::color(ftxui::Color::White)
                        | ftxui::bgcolor(ftxui::Color::RGB(110, 25, 30));
                }

                return ftxui::text("    " + label)
                    | ftxui::color(ftxui::Color::RGB(180, 180, 180));
            };

            auto menu = ftxui::vbox({
                menuItem("Start learning", selectedItem == 0),
                menuItem("Question sets", selectedItem == 1),
                ftxui::filler(),
                menuItem("Statistics", selectedItem == 2),
                ftxui::filler(),
                menuItem("Settings", selectedItem == 3),
                ftxui::filler(),
                menuItem("Exit", selectedItem == 4)
                }) | ftxui::border;

            return ftxui::vbox({
                header,
                ftxui::separator(),
                menu,
                ftxui::separator(),
                ftxui::text("Developed by Dmitry Ivanov | Suggestions: WeLink")
                })
                | ftxui::border;
        }

        else if (currentScreen == 1)
        {
            auto learningTitle = ftxui::text("LEARNING MODE")
                | ftxui::bold
                | ftxui::color(ftxui::Color::White);

            auto learningSubtitle = ftxui::text("Choose a question set and start learning.")
                | ftxui::color(ftxui::Color::RGB(200, 200, 200));

            auto backText = ftxui::text("< Back [ESC]")
                | ftxui::color(ftxui::Color::RGB(180, 180, 180));

            return ftxui::vbox({
                learningTitle | ftxui::center,
                learningSubtitle | ftxui::center,
                ftxui::filler(),
                backText
            }) | ftxui::border;
        }

        else if (currentScreen == 2)
        {
            auto setsTitle = ftxui::text("QUESTION SETS")
                | ftxui::bold
                | ftxui::color(ftxui::Color::White);

            auto setsSubtitle = ftxui::text("Browse and manage your question sets.")
                | ftxui::color(ftxui::Color::RGB(200, 200, 200));

            auto backText = ftxui::text("< Back  [ESC]")
                | ftxui::color(ftxui::Color::RGB(180, 180, 180));

            if (isLoaded)
            {
                auto questionSetInfo = ftxui::vbox({
                    ftxui::text(questionSet.title)
                        | ftxui::bold
                        | ftxui::color(ftxui::Color::White),

                    ftxui::text(questionSet.description)
                        | ftxui::color(ftxui::Color::RGB(180, 180, 180)),

                    ftxui::text(
                        "Questions: " + std::to_string(questionSet.questions.size())
                    )
                        | ftxui::color(ftxui::Color::RGB(145, 145, 145))
                    }) | ftxui::border;

                return ftxui::vbox({
                    setsTitle | ftxui::center,
                    setsSubtitle | ftxui::center,
                    ftxui::filler(),
                    questionSetInfo | ftxui::center,
                    backText
                    }) | ftxui::border;
            }
            else
            {
                return ftxui::vbox({
                    setsTitle | ftxui::center,
                    setsSubtitle | ftxui::center,
                    ftxui::filler(),
                    ftxui::text("Error loading question set: " + error)
                        | ftxui::color(ftxui::Color::Red)
                        | ftxui::center,
                    backText
                    }) | ftxui::border;
            }
        }

        return ftxui::text("Unknown screen");
    })

    | ftxui::CatchEvent([&](ftxui::Event event) { // Обработка событий клавиатуры

        if (event == ftxui::Event::Escape) {
            if (currentScreen == 1 || currentScreen == 2) {
                currentScreen = 0;
                selectedItem = 0;
            }

            return true;
        }

        if (event == ftxui::Event::ArrowUp) {

            if (currentScreen == 2) {
                if (selectedSet > 0) {
                    selectedSet--;
                }
            }
            else if (selectedItem > 0) {
                selectedItem--;
            }

            return true;
        }

        if (event == ftxui::Event::ArrowDown) {

            if (currentScreen == 2) {
                selectedSet++;
            }
            else if (selectedItem < 4) {
                selectedItem++;
            }

            return true;
        }

        if (event == ftxui::Event::Return)
        {
            if (selectedItem == 0) {
                currentScreen = 1;
            }

            if (selectedItem == 1)
            {
                currentScreen = 2;
            }

            if (selectedItem == 4) {
                screen.Exit();
            }

            return true;
        }

        return false;
        });

    screen.Loop(component); // запуск интерфейса
}