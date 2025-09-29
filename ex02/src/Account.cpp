#include "../includes/Account.hpp"

#include <ctime>
#include <iostream>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account() : _accountIndex(0), _amount(0), _nbDeposits(0), _nbWithdrawals(0) {
}

Account::Account(int initial_deposit) : _accountIndex(_nbAccounts), _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0) {
	_totalAmount += initial_deposit;
	_nbAccounts++;

	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << checkAmount() << ";created" << std::endl;
}

Account::~Account() {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << checkAmount() << ";closed" << std::endl;
}

void Account::displayStatus() const {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << checkAmount() << ";deposits:" << _nbDeposits << ";withdrawals:" << _nbWithdrawals << std::endl;
}

void Account::makeDeposit(int deposit) {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";p_amount:" << _amount << ";deposit:" << deposit << ";";

	_amount += deposit;
	_nbDeposits++;
	_totalAmount += deposit;
	_totalNbDeposits++;

	std::cout << "amount:" << _amount << ";nb_deposits:" << _nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal) {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";p_amount:" << _amount << ";withdrawal:";

	if (_amount < withdrawal) {
		std::cout << "refused" << std::endl;
		return (false);
	}

	_amount -= withdrawal;
	_totalAmount -= withdrawal;
	_nbWithdrawals++;
	_totalNbWithdrawals++;

	std::cout << withdrawal << ";amount:" << _amount << ";nb_withdrawals:" << _nbWithdrawals << std::endl;
	return (true);
}


// region Getters

int Account::getNbAccounts() {
	return _nbAccounts;
}

int Account::getTotalAmount() {
	return _totalAmount;
}


int Account::getNbDeposits() {
	return _totalNbDeposits;
}

int Account::getNbWithdrawals() {
	return _totalNbWithdrawals;
}

int Account::checkAmount() const {
	return _amount;
}

// endregion

void Account::displayAccountsInfos() {
	_displayTimestamp();
	std::cout << "accounts:" << _nbAccounts << ";total:" << _totalAmount << ";deposits:" << _totalNbDeposits << ";withdrawals:" << _totalNbWithdrawals << std::endl;
}

void Account::_displayTimestamp() {
	const time_t now = std::time(NULL);
	const tm* localTime = std::localtime(&now);
	char buffer[20];

	std::strftime(buffer, sizeof(buffer), "[%Y%m%d_%H%M%S] ", localTime);
	std::cout << buffer;
}
