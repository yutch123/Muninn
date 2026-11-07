#pragma once

#include "SessionAnswer.h"
#include <vector>

struct Session
{
    int questionSetId;
    std::vector<SessionAnswer> answers;

    bool AddAnswer(const SessionAnswer& answer);

    SessionAnswer* GetAnswer(int questionId);
};
