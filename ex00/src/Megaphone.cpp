#include <iostream>

static std::string stringToUpper(std::string string) {
	for (std::string::iterator it = string.begin(); it != string.end(); ++it)
		*it = static_cast<char>(std::toupper(*it));

	return string;
}

int main(const int argc, const char *argv[]) {
	if (argc < 2)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";

	for (int i = 1; i < argc; i++)
		std::cout << stringToUpper(argv[i]);

	std::cout << std::endl;
}
