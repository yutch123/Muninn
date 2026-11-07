#include "src/loader/QuestionSetLoader.h"
#include "src/question/QuestionSet.h"
#include "src/evaluator/AnswerEvaluator.h"
#include "src/session/Session.h"
#include "src/result/Result.h"

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
        Session session;
        session.questionSetId = questionSet.id;

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

            SessionAnswer sessionAnswer;

            sessionAnswer.questionId = question.id;
            sessionAnswer.userAnswer = userAnswer;
            sessionAnswer.result = result;

            session.AddAnswer(sessionAnswer);

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

        std::cout << "\nSession answers: "
            << session.answers.size() << std::endl;

        Result result;
        result.Calculate(session);

        std::cout << "\nTest results:" << std::endl;
        std::cout << "Total questions: " << result.totalQuestions << std::endl;
        std::cout << "Correct answers: " << result.correctAnswers << std::endl;
        std::cout << "Partially correct: " << result.partiallyCorrectAnswers << std::endl;
        std::cout << "Incorrect answers: " << result.incorrectAnswers << std::endl;
        std::cout << "Score: " << result.scorePercentage << "%" << std::endl;

        for (const SessionAnswer& answer : session.answers)
        {
            std::cout << "Question ID: " << answer.questionId << std::endl;
            std::cout << "User answer: " << answer.userAnswer << std::endl;

            if (answer.result.status == AnswerStatus::Correct)
            {
                std::cout << "Status: Correct" << std::endl;
            }
            else if (answer.result.status == AnswerStatus::PartiallyCorrect)
            {
                std::cout << "Status: Partially correct" << std::endl;
            }
            else if (answer.result.status == AnswerStatus::Incorrect)
            {
                std::cout << "Status: Incorrect" << std::endl;
            }

            std::cout << "Feedback: " << answer.result.feedback << std::endl;
        }
    }
    else
    {
        std::cout << "Error: " << error << std::endl;
    }

    return 0;
}


