#include "Session.h"

#include <iostream>

int main()
{
    Session session;

    SessionAnswer answer;

    answer.questionId = 1;
    answer.userAnswer = "C++ is a programming language";

    answer.result.status = AnswerStatus::Correct;
    answer.result.feedback = "Correct answer!";

    bool firstResult = session.AddAnswer(answer);
    bool secondResult = session.AddAnswer(answer);

    std::cout << "First add: " << firstResult << std::endl;
    std::cout << "Second add: " << secondResult << std::endl;

    SessionAnswer secondAnswer;

    secondAnswer.questionId = 2;
    secondAnswer.userAnswer = "A pointer stores a memory address";

    secondAnswer.result.status = AnswerStatus::Correct;
    secondAnswer.result.feedback = "Correct answer!";

    session.AddAnswer(secondAnswer);

    SessionAnswer* foundAnswer = session.GetAnswer(2);

    if (foundAnswer != nullptr)
    {
        std::cout << "Found answer: " << foundAnswer->userAnswer << std::endl;
        std::cout << "Feedback: " << foundAnswer->result.feedback << std::endl;
    }
    else
    {
        std::cout << "Answer not found" << std::endl;
    }

    std::cout << "Answers count: " << session.answers.size() << std::endl;

    return 0;
}