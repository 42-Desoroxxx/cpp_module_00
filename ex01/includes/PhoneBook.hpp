#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook {
public:
	PhoneBook();
	void add(const Contact& contact);
	const Contact& get(short index) const;
	short getSize() const;
	void print() const;

private:
	Contact contacts[8];
	short size;
};

#endif
