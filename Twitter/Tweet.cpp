#include "Tweet.h"

Tweet::Tweet(string user_, string date_, string text_)
{
	user = user_;
	date = date_;
	text = text_;
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
	char con_acento[] = { 'á' ,'é' ,'í','ó','ú' };
	char sin_acento[] = { 'a' ,'e' ,'i','o','u' };

	int found = 0;
	int i;
	char c, s;

	for (i = 0; i < 5; i++) {
		c = con_acento[i];
		s = sin_acento[i];

		while (found != std::string::npos) {
			found = text.find(c);
			text.replace(found, found, &s);
		}
		found = 0;
	}
	return text;
}
