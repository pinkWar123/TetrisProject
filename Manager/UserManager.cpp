#include "UserManager.h"

std::string UserManager::getUserName() const
{
	return userName;
}

std::string UserManager::getPassword() const
{
	return password;
}

void UserManager::setUserName(std::string userName)
{
	this->userName = userName;
}

void UserManager::setPassword(std::string password)
{
	this->password = password;
}

UserManager& UserManager::getInstance()
{
	static UserManager userManager;
	return userManager;
}

UserManager::UserManager()
{

}