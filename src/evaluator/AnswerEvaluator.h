#pragma once

#include "../question/Question.h"
#include "AnswerResult.h"

#include <string>

class AnswerEvaluator
{
public:
	AnswerResult Evaluate( // метод для проверки ответа
		const Question& question, // передаем вопрос по константной ссылке
		const std::string& userAnswer // также передаем ответ пользователя
	);
private:
	std::string NormalizeAnswer(
		const std::string& amswer,
		bool caseSensitive
	);
};