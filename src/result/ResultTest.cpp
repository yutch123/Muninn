#include "Result.h"

#include <iostream>

int main()
{
	Session session;
	Result result;

	SessionAnswer firstAnswer;

	firstAnswer.questionId = 1;
	firstAnswer.userAnswer = "C++ is a programming language";
	firstAnswer.result.status = AnswerStatus::Correct;
	firstAnswer.result.feedback = "Correct answer!";

	session.AddAnswer(firstAnswer);

	SessionAnswer secondAnswer;

	secondAnswer.questionId = 2;
	secondAnswer.userAnswer = "A pointer is a variable";

	secondAnswer.result.status = AnswerStatus::Incorrect;
	secondAnswer.result.feedback = "Incorrect answer.";

	session.AddAnswer(secondAnswer);

	result.Calculate(session);

	std::cout << "Total questions: " << result.totalQuestions << std::endl;
	std::cout << "Correct answers: " << result.correctAnswers << std::endl;
	std::cout << "Partially correct: " << result.partiallyCorrectAnswers << std::endl;
	std::cout << "Incorrect answers: " << result.incorrectAnswers << std::endl;
	std::cout << "Score: " << result.scorePercentage << "%" << std::endl;

	return 0;
}