#pragma once // защита от повторного включения

#include <string>
#include <vector>
#include <cstddef> // тип std::size_t, который понадобится для ограничения длины ответа.

enum class QuestionType // возможные варианты вопроса
{
	OpenText, // пользователь самостоятельно вводит ответ
	MultipleChoice // пользователь выбирает ответ из предложенных вариантов
};

struct CheckingRules // проверка 
{
	std::size_t minLength = 0; // минимальная длина ответа
	bool caseSensitive = false; // учитывать ли регистр букв при сравнении
};

struct Question // основная структура
{
	int id; // уникальный идентификатор вопроса
	QuestionType type; // тип вопроса

	std::string text; // текст вопроса

	std::string expectedAnswer; // эталонный ответ
	std::vector<std::string> acceptedAnswers; // допустимые альтернативные варианты

	CheckingRules rules; // правила проверки

	std::string explanation; // пояснение к правильному ответу
};