#include "../question/Question.h"
#include "../question/QuestionSet.h"
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../loader/QuestionSetLoader.h"

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

		QuestionSet loadedQuestionSet;

		loadedQuestionSet.id = data["id"].get<int>();
		loadedQuestionSet.title = data["title"].get<std::string>();
		loadedQuestionSet.description = data["description"].get<std::string>();

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
			else
			{
				error = "Unknown question type: " + type;
				return false;
			}

			loadedQuestionSet.questions.push_back(question);
		}

		questionSet = loadedQuestionSet;
	}
	catch (const nlohmann::json::exception& e)
	{
		error = e.what();
		return false;
	}


	return true;
}