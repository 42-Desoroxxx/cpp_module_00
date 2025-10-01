#include "../includes/PhoneBook.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <sstream>

PhoneBook::PhoneBook() : size(0) {
}

/// Add a new contact to the phonebook.
///
/// If the phonebook is full,
/// get rid of the oldest entry (the first index).
void PhoneBook::add(const Contact& contact) {
	if (size < CAPACITY) {
		contacts[size++] = contact;
		contacts[size - 1].setIndex(size - 1);
		return;
	}

	for (short i = 0; i < size - 1; i++) {
		contacts[i] = contacts[i + 1];
		contacts[i].setIndex(i);
	}
	contacts[size - 1] = contact;
	contacts[size - 1].setIndex(size - 1);
}

const Contact& PhoneBook::get(const short index) const {
	return contacts[index];
}

short PhoneBook::getSize() const {
	return size;
}

/// Returns a 10-character wide string with right-aligned text.
/// If the input string is longer than 10 characters, it is truncated and the 10th character will be `.`
static std::string formatColumn(const std::string& string) {
	std::string formatted;

	if (string.length() > 10) {
		formatted = string.substr(0, 9);
		formatted += ".";
	} else {
		formatted += std::string(10 - string.length(), ' ');
		formatted += string;
	}

	return formatted;
}

void PhoneBook::print() const {
	std::cout << "┌───────────────────────────────────────────┐" << std::endl;
	std::cout << "│     Index|First name| Last name|  Nickname│" << std::endl;
	for (short i = 0; i < size; i++) {
		std::cout << "│";
		std::cout << "         " << contacts[i].getIndex() << "|";
		std::cout << formatColumn(contacts[i].getFirstName()) << "|";
		std::cout << formatColumn(contacts[i].getLastName()) << "|";
		std::cout << formatColumn(contacts[i].getNickname()) << "│";
		std::cout << std::endl;
	}
	std::cout << "└───────────────────────────────────────────┘" << std::endl;
}

static void clearScreen() {
	std::cout << "\033[2J\033[3J\033[H";
}

static void printError(const std::string& error) {
	std::cout << "\033[31m" << error << "\033[0m" << std::endl;
}

static bool parseIndex(const std::string& input, short& index, short maxSize) {
	std::istringstream iss(input);
	long value = 0;
	iss >> value;

	if (iss.fail() || !iss.eof()) {
		printError("Invalid index (not a number)!");
		return false;
	}
	if (value < 0) {
		printError("Invalid index (under 0)!");
		return false;
	}
	if (value >= maxSize) {
		std::ostringstream msg;
		msg << "Invalid index (over " << maxSize - 1 << ")!";
		printError(msg.str());
		return false;
	}

	index = value;
	return true;
}

static bool ask(const std::string& label, std::string& out) {
	std::cout << "\033[36m" << label.c_str()[0] << &label.c_str()[1] << ":\033[0m ";

	if (!std::getline(std::cin, out))
		return false;
	if (out.empty()) {
		printError("Invalid " + label + " (empty)!");
		return false;
	}

	return true;
}

static std::string stringToUpper(std::string string) {
	for (std::string::iterator it = string.begin(); it != string.end(); ++it)
		*it = static_cast<char>(std::toupper(*it));

	return string;
}

int main(const int argc, const char* argv[]) {
	const bool prouveurMode = argc == 2 && std::string(argv[1]) == "--prouveur";
	PhoneBook phoneBook;

	clearScreen();
	while (true) {
		std::cout << "\033[36mPhoneBook:\033[0m ";

		std::string input;
		if (!std::getline(std::cin, input) || input == "EXIT" || (prouveurMode && input == "exit"))
			break;

		if (input.empty())
			continue;

		if (prouveurMode)
			input = stringToUpper(input);

		if (input == "ADD") {
			std::string firstName, lastName, nickname, phoneNumber, darkestSecret;

			if (!ask("First name", firstName) ||
				!ask("Last name", lastName) ||
				!ask("Nickname", nickname) ||
				!ask("Phone number", phoneNumber) ||
				!ask("Darkest secret", darkestSecret))
				continue;

			phoneBook.add(Contact(0, firstName, lastName, nickname, phoneNumber, darkestSecret));
		} else if (input == "SEARCH") {
			phoneBook.print();
			if (phoneBook.getSize() == 0)
				continue;

			short index;
			while (true) {
				std::cout << "\033[36mIndex:\033[0m ";

				if (!std::getline(std::cin, input))
					break;

				if (input.empty())
					continue;
				if (parseIndex(input, index, phoneBook.getSize()))
					break;
			}

			phoneBook.get(index).print();
		} else if (!prouveurMode) {
		} else if (input == "LIST") {
			phoneBook.print();
		} else if (input == "CLEAR") {
			clearScreen();
		} else {
			printError("Invalid command (" + input + ")!");
		}
	}

	std::cout << "Bye!" << std::endl;
}
