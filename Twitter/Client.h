#pragma once
#include <iostream>
#include "Tweet.h"
#include <curl/curl.h>
#include <list>
#include "json.hpp"
#include <string>
#include <vector>

using namespace std;

size_t myCallback(void *contents, size_t size, size_t nmemb, void *userp);

class Client
{
public:
	Client();
	Client(string user_, int numberofTweets_);
	~Client();

	bool getBearerToken(void);
	bool getTweets(void);
	vector<Tweet>& getTweetList(void);
	void setUser(string user_);
	void set_numberofTweets(int numberofTweets_);
	int getvectorsize(void);
	void displayTweets(void);
	/*void printNames(list<string> names);*/

private:
	void setTokenOptions(void);
	void setTwitterOptions(void);

	CURL *easyHandler, *multiHandle;
	CURLcode easyError;
	CURLMcode multiError;
	string token, user, query, readString;
	int numberofTweets;
	int stillRunning;

	vector<Tweet> tweetList;
};



