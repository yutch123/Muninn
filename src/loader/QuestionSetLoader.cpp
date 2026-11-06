#include "../question/Question.h"
#include "../question/QuestionSet.h"
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include "../loader/QuestionSetLoader.h"

static_assert(sizeof(QuestionSet) > 0, "QuestionSet is incomplete");

/*#include "../question/QuestionSet.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include "../loader/QuestionSetLoader.h"
#include <iostream>
*/


bool QuestionSetLoader::LoadFromFile(
	const std::string& filePath,
	QuestionSet& questionSet,
	std::string& error)
{
	std::ifstream file(filePath); // открываем файл в отдельном потоке

	if (!file.is_open()) // проверяем, удалось ли открыть файл
	{
		error = "Failed to open JSON file: " + filePath; // считываем содержимое файла и преобразуем его в JSON-структуру
		return false;
	}

	nlohmann::json data;
	
	// обработка ошибок через try/catch  

	try
	{
		file >> data;

		questionSet.id = data["id"].get<int>();
		questionSet.title = data["title"].get<std::string>();
		questionSet.description = data["description"].get<std::string>();

		for (std::size_t i = 0; i < data["questions"].size(); i++)
		{
			Question question;

			question.id = data["questions"][i]["id"].get<int>();
			question.text = data["questions"][i]["text"].get<std::string>();
			question.expectedAnswer = data["questions"][i]["expectedAnswer"].get<std::string>();

			for (const auto& answer : data["questions"][i]["acceptedAnswers"])
			{
				question.acceptedAnswers.push_back(answer.get<std::string>());
			}

			question.rules.minLength =
				data["questions"][i]["rules"]["minLength"].get<std::size_t>();

			question.rules.caseSensitive =
				data["questions"][i]["rules"]["caseSensitive"].get<bool>();

			question.explanation =
				data["questions"][i]["explanation"].get<std::string>();

			std::string type = data["questions"][i]["type"].get<std::string>();

			if (type == "OpenText")
			{
				question.type = QuestionType::OpenText;
			}
			else if (type == "MultipleChoice")
			{
				question.type = QuestionType::MultipleChoice;
			}

			questionSet.questions.push_back(question);
		}

		std::cout << "Loaded questions: "
			<< questionSet.questions.size() << std::endl;
	}
	catch (const nlohmann::json::parse_error& e)
	{
		error = e.what();
		return false;
	}


	return true;
}