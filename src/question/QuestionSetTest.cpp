#include "QuestionSet.h"
#include <iostream>

QuestionSet testSet
{
	1,
	"Basic Questions",
	"Basic information about our company",
	{}
};

int main()
{
	Question question1
	{
		1,
		QuestionType::OpenText,
		"What is Compliance?"
	};

	Question question2
	{
		2,
		QuestionType::OpenText,
		"What is Compliance too?"
	};


	testSet.questions.push_back(question1);
	testSet.questions.push_back(question2);

	std::cout << testSet.questions[0].text << '\n';
	std::cout << testSet.questions[1].text << '\n';

	testSet.questions.erase(testSet.questions.begin() + 1);

	std::cout << "Questions count: "
		<< testSet.questions.size() << '\n';

	std::cout << testSet.questions[0].text << '\n';
}
