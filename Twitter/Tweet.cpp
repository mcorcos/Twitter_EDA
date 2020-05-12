#include "Tweet.h"
#include <vector>

Tweet::Tweet(string user_, string date_, string text_)
{
	user = user_;
	date = date_;
	text = find_chars(text_);
}

Tweet::~Tweet()
{
}

string Tweet::getUser(void)
{
	return user;
}

string Tweet::getDate(void)
{
	return date;
}

string Tweet::getText(void)
{
	return text;
}



string find_chars(std::string text) {
	char con_acento[] = { 'á' ,'é' ,'í','ó','ú','ñ' };
	char sin_acento[] = { 'a' ,'e' ,'i','o','u','n' };

	int found = 0;
	int i;
	char c, s;

	for (i = 0; i < 6; i++) {
		c = con_acento[i];
		s = sin_acento[i];

		found = text.find(c);

		while (found != std::string::npos) {
			
			text[found] = s;

			found = text.find(c);

		}
		found = 0;
	}
	return text;
}
std::string month_tonum(const std::string monthName)
{
	static const vector<std::string> months
	{
		{ "Jan"},
		{ "Feb"},
		{ "Mar"},
		{ "Apr" },
		{ "May"},
		{ "Jun"},
		{ "Jul"},
		{ "Aug"},
		{ "Sep"},
		{ "Oct" },
		{ "Nov"},
		{ "Dec"}
	};

	std::string name = monthName;
	int i;
	for (i = 0; name.compare(months.at(i)) != 0;i++) {}

	if (i < 10) {
		string result = '0' + to_string(i);
		return result;
	}

	else {
		return to_string(i);
	}
}