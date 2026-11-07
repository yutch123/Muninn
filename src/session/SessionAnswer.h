#pragma once

#include <string>
#include "../evaluator/AnswerResult.h"

struct SessionAnswer
{
    int questionId;
    std::string userAnswer;
    AnswerResult result;
};