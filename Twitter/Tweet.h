#pragma once
#include <string>
using namespace std;

string find_chars(std::string text);
std::string month_tonum(const std::string monthName);

class Tweet
{
public:
	Tweet(string user_, string date_, string text_);
	~Tweet();

	string getUser(void);
	string getDate(void);
	string getText(void);

private:
	string user, date, text;
};