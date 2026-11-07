#include "Result.h"

void Result::Calculate(const Session& session)
{
	totalQuestions = 0;
	correctAnswers = 0;
	partiallyCorrectAnswers = 0;
	incorrectAnswers = 0;
	scorePercentage = 0;

	for (const SessionAnswer& answer : session.answers)
	{
		totalQuestions++;
		if (answer.result.status == AnswerStatus::Correct)
		{
			correctAnswers++;
		}
		else if (answer.result.status == AnswerStatus::PartiallyCorrect)
		{
			partiallyCorrectAnswers++;
		}
		else if (answer.result.status == AnswerStatus::Incorrect)
		{
			incorrectAnswers++;
		}
	}

	if (totalQuestions > 0)
	{
		scorePercentage = static_cast<double>(correctAnswers)
			/ totalQuestions * 100.0;
	}
}