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
typedef enum { ERROR_FREE, TWEET_NUMBER_ERROR, INVALID_USERNAME, JSON_ERROR, CURL_ERROR, CURL_EASY_ERROR, CURL_MULTI_ERROR } errorCode_n;

#define MAXTWEETNUMBER 1000
#define DEFAULT_TWEET_NUMBER 20

class Client
{
public:
	Client();
	Client(string user_, int numberofTweets_);
	~Client();

	bool getBearerToken(void);
	bool getTweets(void);
	vector<Tweet>& getTweetList(void);
	errorCode_n getErrorCode(void);

	void setUser(string user_);
	void set_numberofTweets(int numberofTweets_);
	int getvectorsize(void);
	void setErrorMessage();

private:
	void setTokenOptions(void);
	void setTwitterOptions(void);

	CURL *easyHandler, *multiHandle;
	CURLcode easyError;
	CURLMcode multiError;
	string token, user, query, readString;
	int numberofTweets;
	int stillRunning;
	errorCode_n errorCode;

	vector<Tweet> tweetList;
};



