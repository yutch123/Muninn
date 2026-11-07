#pragma once

#include "../question/QuestionSet.h"
#include <string>

class QuestionSetLoader
{
public:
	bool LoadFromFile( // метод возвращает результат операции
		const std::string& filePath, // путь к JSON
		QuestionSet& questionSet, // ссылка на объект, куда загрузчик запишет результат работы
		std::string& error // сюда загрузчик сможет записать описанные ошибки
	);
};
