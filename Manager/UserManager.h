#pragma once
#include <string>
class UserManager
{
public:
	std::string getUserName() const;
	std::string getPassword() const;
	void setUserName(std::string userName);
	void setPassword(std::string password);
	static UserManager& getInstance();
	
private:
	UserManager();
	std::string userName;
	std::string password;
};

