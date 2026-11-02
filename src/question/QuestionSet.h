#include "Question.h"
#include <vector>
#include <string> // теперь структура самостоятельно использует std::string

struct QuestionSet // основная струкутра
{
	int id; // идентифицирует набор
	std::string title; // хранит его название
	std::string description; // хранит описание
	std::vector<Question> questions; // содержит вопросы Question
};