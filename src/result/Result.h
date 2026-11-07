#pragma once

#include "../session/Session.h"
#include <cstddef>

struct Result
{
    std::size_t totalQuestions = 0;
    std::size_t correctAnswers = 0;
    std::size_t partiallyCorrectAnswers = 0;
    std::size_t incorrectAnswers = 0;

    double scorePercentage = 0.0;

    void Calculate(const Session& session);
};
