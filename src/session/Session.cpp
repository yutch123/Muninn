#include "Session.h"

bool Session::AddAnswer(const SessionAnswer& answer)
{
    if (GetAnswer(answer.questionId) != nullptr)
    {
        return false;
    }

    answers.push_back(answer);

    return true;
}

SessionAnswer* Session::GetAnswer(int questionId)
{
    for (SessionAnswer& sessionAnswer : answers)
    {
        if (sessionAnswer.questionId == questionId)
        {
            return &sessionAnswer;
        }
    }

    return nullptr;
}