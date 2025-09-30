#include "../includes/PhoneBook.hpp"
#include <iostream>
#include <ostream>
#include <string>

PhoneBook::PhoneBook() {
	size = 0;
}

/// Add a new contact to the phonebook.
///
/// If the phonebook is full (size of 8),
/// get rid of the oldest entry (the first index).
void PhoneBook::add(const Contact& contact) {
	if (size < 8) {
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
static std::string _formatColumn(const std::string& string) {
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
		std::cout << _formatColumn(contacts[i].getFirstName()) << "|";
		std::cout << _formatColumn(contacts[i].getLastName()) << "|";
		std::cout << _formatColumn(contacts[i].getNickname()) << "│";
		std::cout << std::endl;
	}
	std::cout << "└───────────────────────────────────────────┘" << std::endl;
}

static void clearScreen() {
	std::cout << "\033[2J\033[3J\033[H" << std::flush;
}

static void printError(const std::string& error) {
	std::cout << "\033[31m" << error << "\033[0m" << std::endl;
}

int main(const int argc, const char *argv[]) {
	const bool prouveur = argc == 2 && std::string(argv[1]) == "--prouveur";
	PhoneBook phoneBook;

	clearScreen();
	while (true) {
		std::cout << "\033[36mPhoneBook:\033[0m ";

		std::string input;
		if (!std::getline(std::cin, input) || input == "EXIT")
			break;

		if (input == "ADD") {
			std::string firstName, lastName, nickname, phoneNumber, darkestSecret;

			std::cout << "First name: ";
			if (!std::getline(std::cin, firstName))
				break;
			if (firstName.empty()) {
				printError("Invalid first name (empty)!");
				continue;
			}

			std::cout << "Last name: ";
			if (!std::getline(std::cin, lastName))
				break;
			if (lastName.empty()) {
				printError("Invalid last name (empty)!");
				continue;
			}

			std::cout << "Nickname: ";
			if (!std::getline(std::cin, nickname))
				break;
			if (nickname.empty()) {
				printError("Invalid nickname (empty)!");
				continue;
			}

			std::cout << "Phone number: ";
			if (!std::getline(std::cin, phoneNumber))
				break;
			if (phoneNumber.empty()) {
				printError("Invalid phone number (empty)!");
				continue;
			}

			std::cout << "Darkest secret: ";
			if (!std::getline(std::cin, darkestSecret))
				break;
			if (darkestSecret.empty()) {
				printError("Invalid darkest secret (empty)!");
				continue;
			}

			phoneBook.add(Contact(0, firstName, lastName, nickname, phoneNumber, darkestSecret));
		} else if (input == "SEARCH") {
			phoneBook.print();
			if (phoneBook.getSize() == 0)
				continue;

			std::cout << "Search: ";
			if (!std::getline(std::cin, input)) {
				std::cout << std::endl << "Bye!" << std::endl;
				break;
			}
			if (input.empty()) {
				printError("Invalid index (empty)!");
				continue;
			}
			if (input.length() > 1) {
				printError("Invalid index (too many characters)!");
				continue;
			}
			if (!isdigit(input[0])) {
				printError("Invalid index (not a number)!");
				continue;
			}
			const short index = input[0] - '0';
			if (index < 0) {
				printError("Invalid index (under 0)!");
				continue;
			}
			if (index >= phoneBook.getSize()) {
				const char c = '0' + phoneBook.getSize();
				const char str[1] = {c};
				printError("Invalid index (over " + std::string(str) + ")!");
				continue;
			}

			phoneBook.get(index).print();
		} else if (!prouveur) {
		} else if (input == "CLEAR") {
			clearScreen();
		} else {
			printError("Invalid command (" + input + ")!");
		}
	}

	std::cout << std::endl << "Bye!" << std::endl;
}
