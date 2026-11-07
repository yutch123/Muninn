#pragma once 

#include <string>
#include "../evaluator/AnswerResult.h"

enum class AnswerStatus // enum class - перечисление, которое задает ограниченный набор значений
{
	Correct, // правильнй ответ
	PartiallyCorrect, // ответ частично правильный
	Incorrect // ответ неправильный
};

struct AnswerResult
{
	AnswerStatus status;
	std::string feedback;
};

