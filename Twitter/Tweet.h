#pragma once
#include <string>
using namespace std;

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