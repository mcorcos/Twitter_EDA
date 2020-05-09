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
