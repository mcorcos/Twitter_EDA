#include "Client.h"
string text_, date_;
using json = nlohmann::json;

const char* API_key = "HCB39Q15wIoH61KIkY5faRDf6";
const char*  API_SecretKey = "7s8uvgQnJqjJDqA6JsLIFp90FcOaoR5Ic41LWyHOic0Ht3SRJ6";

list<string> tweet_text;

Client::Client(string user_, int numberofTweets_)
{
	user = user_;
	numberofTweets = numberofTweets_;
	query = "https://api.twitter.com/1.1/statuses/user_timeline.json?screen_name=" + user + "&count=" + to_string(numberofTweets);
	easyHandler = nullptr;
	multiHandle = nullptr;

}

Client::~Client()
{
}



bool Client::getBearerToken(void)
{
	json j;
	easyHandler = curl_easy_init();
	if (easyHandler)
	{
		//Configuro el handler con las opciones necesarias para recuperar el token
		setTokenOptions();
		//Check for errors.
		if (easyError != CURLE_OK)
		{
			cerr << "curl_easy_perform() failed: " << curl_easy_strerror(easyError) << std::endl;
			//Hacemos un clean up de curl antes de salir.
			curl_easy_cleanup(easyHandler);
			return false;
		}

		// Si no hubo errores hago un clean up antes de realizar un nuevo query.
		curl_easy_cleanup(easyHandler);

		//Si el request de CURL fue exitoso entonces twitter devuelve un JSON
		//Abajo busco el token en el JSON para luego acceder a los twits.
		j = json::parse(readString);

		//Se encierra el parseo en un bloque try-catch porque la libreria maneja errores por excepciones.
		//Pueden tambien parsear usando iteradores o la forma que quieras, buscar en la documentacion las diferentes formas.
		try
		{
			//Tratamos de acceder al campo acces_token del JSON
			std::string aux = j["access_token"];
			token = aux;
			cout << "Bearer Token get from Twitter API: \n" << token << std::endl;
		}
		catch (std::exception& e)
		{
			//Si hubo algun error, se muestra el error que devuelve la libreria
			cerr << e.what() << std::endl;
			return false;
		}
		return true;
	}
	else
	{
		std::cout << "Cannot download tweets. Unable to start cURL" << std::endl;
		return false;
	}
}

bool Client::getTweets(void)
{
	static bool firstTime = true;	//Para inicializar easy y multi handler una sola vez.
	if (firstTime)
	{
		easyHandler = curl_easy_init();
		multiHandle = curl_multi_init();
		setTwitterOptions();
		readString = "";
		stillRunning = 0;
		firstTime = false;
	}
	bool processState = true;
	if ((easyHandler) && (multiHandle))
	{
		//Realizamos ahora un perform no bloqueante
		curl_multi_perform(multiHandle, &stillRunning);
		if (stillRunning)
		{
			//Debemos hacer polling de la transferencia hasta que haya terminado
			multiError = curl_multi_perform(multiHandle, &stillRunning);
			if (multiError != CURLE_OK)
			{
				curl_easy_cleanup(easyHandler);
				curl_multi_cleanup(multiHandle);
				cout << "Error al intentar recuperar tweets." << endl;
				cerr << "curl_multi_perform() failed: " << curl_multi_strerror(multiError) << endl;
				return 0;
			}
			processState = true;
		}

		//Checkeamos errores
		else
		{
			if (easyError != CURLE_OK)
			{
				cerr << "curl_easy_perform() failed: " << curl_easy_strerror(easyError) << endl;
				//Hacemos un clean up de curl antes de salir.
				curl_easy_cleanup(easyHandler);
				curl_multi_cleanup(multiHandle);
				return 0;
			}
			//Siempre realizamos el cleanup al final
			curl_easy_cleanup(easyHandler);
			curl_multi_cleanup(multiHandle);
			firstTime = true;

			//Si el request de CURL fue exitoso entonces twitter devuelve un JSON
			//con toda la informacion de los tweets que le pedimos
			json j = json::parse(readString);

			//Busco errores en el archivo json recuperado de twitter.
			if (j.find("errors") != j.end())
			{
				for (auto codes : j["errors"])
				{
					if (codes["code"] == 34)
					{
						cout << "Usuario no v�lido" << endl;
						return 0;
					}
				}
				cout << "Error de json" << endl;
				return 0;
			}

			//Guardo los campos del json que me interesan en mi vector de Tweets.
			try
			{
				//Al ser el JSON un arreglo de objetos JSON se busca el campo text para cada elemento
				/*for (auto element : j)
					tweet_text.push_back(element["text"]);
				printNames(tweet_text);*/

				for (auto element : j)
				{
					text_ = element["text"];
					date_ = element["created_at"];
					int extended = text_.find("https");
					text_ = text_.substr(0, extended);
					text_.append("...");
					/*text_ = element["text"].get<string>();
					date_ = element["created at"].get<string>();*/
					tweetList.emplace_back(Tweet(user, date_, text_));
				}
				/*cout << "Tweets retrieved from Twitter account: " << user << endl;*/
			}
			catch (std::exception& e)
			{
				//Muestro si hubo un error de la libreria
				std::cerr << e.what() << std::endl;
			}
			processState = false;
		}
		return processState;
	}
	else
		std::cout << "Cannot download tweets. Unable to start cURL" << std::endl;

	return 0;
}

void Client::displayTweets(void)
{
	for (auto tweet_ : tweetList)
	{
		cout << tweet_.getUser() << endl;
		cout << tweet_.getDate() << endl;
		cout << tweet_.getText() << endl;
		std::cout << "-----------------------------------------" << std::endl;
	}
	cout << "Tweets retrieved from Twitter account: " << user << endl;
}

//void Client::printNames(list<string> names)
//{
//	for (auto c : names)
//	{
//		//Eliminamos el URL al final para mostrar
//		int extended = c.find("https");
//		c = c.substr(0, extended);
//		c.append("...");
//		std::cout << c << std::endl;
//		std::cout << "-----------------------------------------" << std::endl;
//	}
//}


void Client::setTokenOptions(void)
{
	//Seteamos primero la pagina donde nos vamos a conectar. Para buscar el token es siempre la misma
	curl_easy_setopt(easyHandler, CURLOPT_URL, "https://api.twitter.com/oauth2/token");

	// Si la p�gina nos redirije a alg�n lado, le decimos a curl que siga dicha redirecci�n.
	curl_easy_setopt(easyHandler, CURLOPT_FOLLOWLOCATION, 1L);

	// Le decimos a CURL que trabaje tanto con HTTP como HTTPS, Autenticaci�n por HTTP en modo b�sico.
	curl_easy_setopt(easyHandler, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);
	curl_easy_setopt(easyHandler, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);

	//Preparamos el password para la autenticaci�n
	string userPwd = API_key + (string)":" + API_SecretKey;
	//Se lo seteamos a CURL.
	curl_easy_setopt(easyHandler, CURLOPT_USERPWD, userPwd.c_str());

	struct curl_slist *list = NULL;
	//Pueden setear el Header con la linea de abajo, pero necesitan codificar las claves en Base64
	//list = curl_slist_append(list, "Authorization: Basic YlB5alk1bWRMR2V4TlhPTHhSUjd3MUVjUzpkR2liU3FIcURrektQMUtPbzFJTjRBd21tZGI1Tnl5ZjBFQTZkTDBLWlpmZDE0ZnhQQw==");

	//Le decimos a CURL que vamos a mandar URLs codificadas y adem�s en formato UTF8.
	list = curl_slist_append(list, "Content-Type: application/x-www-form-urlencoded;charset=UTF-8");
	curl_easy_setopt(easyHandler, CURLOPT_HTTPHEADER, list);

	//Le decimos a CURL que trabaje con credentials.
	string data = "grant_type=client_credentials";
	curl_easy_setopt(easyHandler, CURLOPT_POSTFIELDSIZE, data.size());
	curl_easy_setopt(easyHandler, CURLOPT_POSTFIELDS, data.c_str());

	//Le decimos a curl que cuando haya que escribir llame a myCallback
	//y que use al string readString como user data.
	curl_easy_setopt(easyHandler, CURLOPT_WRITEFUNCTION, myCallback);
	curl_easy_setopt(easyHandler, CURLOPT_WRITEDATA, &readString);

	// Perform the request, res will get the return code
	// Con lo de abajo le decimos a curl que intente conectarse a la p�gina (recordemos que la idea es
	// obtener la autenticaci�n as� luego Twitter nos deja conectarnos a cualquier usuario p�blico)
	//Recordar que easy_perform es bloqueante, en este caso es correcto asi al ser inicializacion y no tardar mucho tiempo.
	easyError = curl_easy_perform(easyHandler);
}

void Client::setTwitterOptions(void)
{
	//Attacheo el easy handle para manejar una coneccion no bloqueante.
	curl_multi_add_handle(multiHandle, easyHandler);

	//Seteamos URL FOLLOWLOCATION y los protocolos a utilizar igual que antes.
	curl_easy_setopt(easyHandler, CURLOPT_URL, query.c_str());
	curl_easy_setopt(easyHandler, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(easyHandler, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);
	//Construimos el Header de autenticacion como lo especifica la API
	//usando el token que obtuvimos antes
	struct curl_slist *list = NULL;
	string aux = "Authorization: Bearer ";
	aux = aux + token;
	list = curl_slist_append(list, aux.c_str());
	curl_easy_setopt(easyHandler, CURLOPT_HTTPHEADER, list);

	//Seteamos los callback igual que antes
	curl_easy_setopt(easyHandler, CURLOPT_WRITEFUNCTION, myCallback);
	curl_easy_setopt(easyHandler, CURLOPT_WRITEDATA, &readString);

}

size_t myCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	char* data = (char *)contents;
	//fprintf(stdout, "%s",data);
	string* s = (string*)userp;
	s->append(data, realsize);
	return realsize;						//recordar siempre devolver realsize
}