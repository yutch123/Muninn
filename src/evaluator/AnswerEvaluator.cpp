#include "AnswerEvaluator.h"
#include <algorithm>
#include <cctype>

std::string AnswerEvaluator::NormalizeAnswer( // Нормализация - удаление пробелов по краям
	const std::string& answer,
	bool caseSensitive)
{
	std::size_t start = answer.find_first_not_of(" \t\n\r");

	if (start == std::string::npos)
	{
		return "";
	}

	std::size_t end = answer.find_last_not_of(" \t\n\r");
	std::string normalized = answer.substr(start, end - start + 1);

	std::string result;

	for (char ch : normalized)
	{
		if (std::isspace(static_cast<unsigned char>(ch)))
		{
			if (!result.empty() && result.back() != ' ') // проверяет, пуста ли результирующая строка и возвращает последний символ строки.
			{
				result += ' '; // добавляет один пробел.
			}
		}

		else if ( std::ispunct(static_cast<unsigned char>(ch)) && ch != '+' && ch != '#') // Проврека на знаки препинания
		{
			if (!result.empty() && result.back() != ' ')
			{
				result += ' ';
			}
		}

		else
		{
			result += ch;
		}
	}

	if (!result.empty() && result.back() == ' ')
	{
		result.pop_back();
	}

	if (!caseSensitive) // выполняем преобразование, только если регистр учитывать не нужно
	{
		std::transform( // применяет операцию к каждому символу диапазона
			result.begin(), // начало строки
			result.end(), // конец строки
			result.begin(),
			[](unsigned char ch)
			{
				return std::tolower(ch); // переводит символ в нижний регистр
			}
		);
	}

	return result;
}

AnswerResult AnswerEvaluator::Evaluate(
	const Question& question,
	const std::string& userAnswer)
{
	std::string normalizedUserAnswer =
		NormalizeAnswer(userAnswer, question.rules.caseSensitive);

	if (normalizedUserAnswer.empty()) // проверка на пустое значение
	{
		return {
			AnswerStatus::Incorrect,
			"Answer cannot be empty."
		};
	}

	if (normalizedUserAnswer.size() < question.rules.minLength) // проверка на минимальную длину
	{
		return {
			AnswerStatus::Incorrect,
			"Answer is too short."
		};
	}

	std::string normalizedExpectedAnswer =
		NormalizeAnswer(question.expectedAnswer, question.rules.caseSensitive);

	if (normalizedUserAnswer == normalizedExpectedAnswer)
	{
		return {
			AnswerStatus::Correct,
			"Correct answer!"
		};
	}

	for (const std::string& acceptedAnswer : question.acceptedAnswers)
	{
		std::string normalizedAcceptedAnswer =
			NormalizeAnswer(acceptedAnswer, question.rules.caseSensitive);

		if (normalizedUserAnswer == normalizedAcceptedAnswer)
		{
			return {
				AnswerStatus::Correct,
				"Correct answer!"
			};
		}

	}

	return {
	AnswerStatus::Incorrect,
	"Incorrect answer."
	};
}