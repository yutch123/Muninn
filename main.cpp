#include "src/loader/QuestionSetLoader.h"
#include "src/question/QuestionSet.h"
#include "src/evaluator/AnswerEvaluator.h"

#include <iostream>
#include <string>

int main()
{
    QuestionSet questionSet;
    QuestionSetLoader loader;
    std::string error;

    if (loader.LoadFromFile("../../../data/basic_questions.json", questionSet, error))
    {
        std::cout << "Question Set ID: " << questionSet.id << std::endl;
        std::cout << "Title: " << questionSet.title << std::endl;
        std::cout << "Description: " << questionSet.description << std::endl;

        std::cout << "Number of questions: "
            << questionSet.questions.size() << std::endl;

        AnswerEvaluator evaluator;

        for (const Question& question : questionSet.questions)
        {
            std::cout << "Question ID: " << question.id << std::endl;
            std::cout << "Question text: " << question.text << std::endl;
            // ввод ответа
            std::string userAnswer;

            std::cout << "Your answer: ";
            std::getline(std::cin, userAnswer);

            std::cout << "You answered: " << userAnswer << std::endl;
            AnswerResult result = evaluator.Evaluate(question, userAnswer); // функция оценивает ответ
            std::cout << "Feedback: " << result.feedback << std::endl; // вывод Feedback

            std::cout << "Expected answer: " << question.expectedAnswer << std::endl;
            std::cout << "Accepted answers: "
                << question.acceptedAnswers.size() << std::endl;

            std::cout << "Minimum answer length: "
                << question.rules.minLength << std::endl;

            std::cout << "Case sensitive: "
                << question.rules.caseSensitive << std::endl;

            std::cout << "Explanation: "
                << question.explanation << std::endl;

            for (const std::string& answer : question.acceptedAnswers)
            {
                std::cout << " - " << answer << std::endl;
            }

            if (question.type == QuestionType::OpenText)
            {
                std::cout << "Type: OpenText" << std::endl;
            }
            else if (question.type == QuestionType::MultipleChoice)
            {
                std::cout << "Type: MultipleChoice" << std::endl;
            }
        }
    }
    else
    {
        std::cout << "Error: " << error << std::endl;
    }

    return 0;
}


