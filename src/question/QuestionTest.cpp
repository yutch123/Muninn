#include "Question.h"
#include <iostream>

int main()
{
	Question question;
	question.id = 1;
	question.type = QuestionType::OpenText;

	question.text = "What is Compliance?";

	question.expectedAnswer =
		"Compliance is the adherence to rules, regulations "
		"and requirements within an organization.";

	question.acceptedAnswers = {
		"Following established rules and regulations."
	};

	question.rules.minLength = 10;
	question.rules.caseSensitive = false;

	question.explanation =
		"Compliance means ensuring that an organization "
		"follows applicable laws, regulations and internal policies.";

	// выводим данные в консоль
	std::cout << "ID: " << question.id << '\n';
	std::cout << "Question: " << question.text << '\n';
	std::cout << "Expected answer: " << question.expectedAnswer << '\n';
	std::cout << "Explanation: " << question.explanation << '\n';

	std::cout << "Accepted answers:" << '\n';

	for (const std::string& answer : question.acceptedAnswers)
	{
		std::cout << "- " << answer << '\n';
	}

	std::cout << "Minimum length: "
		<< question.rules.minLength << '\n';

	std::cout << "Case sensitive: "
		<< question.rules.caseSensitive << '\n';

	return 0; // завершение программы
}