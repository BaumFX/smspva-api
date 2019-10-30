# smspva-api

an api wrapper for the smspva.com api.

## supported languages:
c++17

## supported (soon™):
python 3.8
c#.net
PHP 7.3

## getting started

these instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

depends on the language, visit the section accordingly


## c++
```
//make sure the header files (request.hpp, smspva.hpp, nlohmann/json/include folder) are present
//include the header file and create a new api object with your api key
#include "smspva.hpp"

smspva::smspva api = smspva::smspva("YOUR_KEY_HERE");
```
you can then use the following methods
```
//get the current account balance in USD
//returns -1 if something failed, returns a double of the balance if it worked
double balance = api.get_balance();
if (balance == -1) { std::cout << "[-] failed to get balance" << std::endl; }
else { std::cout << "[+] successfully got balance: " << balance << std::endl; }

//get the current karma of the account
//returns -1 if something failed, returns int with the karma if it worked
int karma = api.get_karma();
if (karma == -1) { std::cout << "[-] failed to get karma" << std::endl; }
else { std::cout << "[+] successfully got karma: " << karma << std::endl; }

//next 4 are for available numbers, pretty much useless except if you're collecting statistics

int available_total = api.get_available_total(smspva::countries::country::country_russian_federation, smspva::services::service::service_whatsapp);
if (available_total == -1) { std::cout << "[-] failed to get available total numbers" << std::endl; }
else { std::cout << "[+] successfully got available total numbers: " << available_total << std::endl; }

int available_now = api.get_available_now(smspva::countries::country::country_russian_federation, smspva::services::service::service_whatsapp);
if (available_now == -1) { std::cout << "[-] failed to get available total numbers" << std::endl; }
else { std::cout << "[+] successfully got available numbers now: " << available_now << std::endl; }

int available_call_total = api.get_available_call_total(smspva::countries::country::country_russian_federation, smspva::services::service::service_whatsapp);
if (available_call_total == -1) { std::cout << "[-] failed to get available total numbers for call forwarding" << std::endl; }
else { std::cout << "[+] successfully got available total numbers for call forwarding: " << available_call_total << std::endl; }

int available_call_now = api.get_available_call_now(smspva::countries::country::country_russian_federation, smspva::services::service::service_whatsapp);
if (available_call_now == -1) { std::cout << "[-] failed to get available numbers for call forwarding" << std::endl; }
else { std::cout << "[+] successfully got available numbers for call forwarding: " << available_call_now << std::endl; }

//gets the price of a single number for a service in a specific country
//returns -1 if something failed, returns the price as double if it worked
double price = api.get_price(smspva::countries::country::country_russian_federation, smspva::services::service::service_whatsapp);
if (price == -1) { std::cout << "[-] failed to get price" << std::endl; }
else { std::cout << "[+] successfully got price: " << price << std::endl; }

//gets a new number
//returns a nullptr if something failed, returns a smspva::number* if it worked, pass this into other functions
smspva::number* new_num = api.get_number(smspva::countries::country::country_russian_federation, smspva::services::service::service_whatsapp);
if (new_num == nullptr) { std::cout << "[-] failed to get number" << std::endl; }
else { std::cout << "[+] successfully got number with id " << new_num->id << " and number " << new_num->num << std::endl; }

//reports a number as banned
//pass in the number from above
int reported_number = api.report_number(new_num);
if (reported_number == -1) { std::cout << "[-] failed to report number" << std::endl; }
else { std::cout << "[+] successfully reported number with id: " << new_num->id << std::endl; }

//gets the sms code from a number
/pass the number object from above
//returns -1 if something failed
//returns 0 if the number hasn't been received yet, wait 20s then call again
//returns the int code if it worked
int sms = api.get_code(new_num);
if (sms == -1) { std::cout << "[-] failed to get sms from number" << std::endl; }
else if (sms == 0) { std::cout << "[-] sms not yet received, wait 20s and retry" << std::endl; }
else { std::cout << "[+] successfully received sms with code " << sms << std::endl; }

//cancels the number
//pass in the number object from above again
int cancel_number = api.cancel_number(new_num);
if (cancel_number == -1) { std::cout << "[-] failed to cancel number" << std::endl; }
else { std::cout << "[+] successfully cancelled number with id: " << new_num->id << std::endl; }

//delete our number object because #nomemleaks
delete new_num;
```

i only included the most widely used features since most people won't use the rest anyway

ports to python, c# and php coming soon : )

## features
handles all the annoying stuff for you, makes the api easier to use since you don't have to handle all of the web requests

## contributing
please be sure to make the http lib better, not really sure if this is a good solution, stole it from Mr. Sloan Kelly on YouTube

please create a pull request if you have ideas for new stuff.

## versioning

no versions but updates (sometimes)

## thanks to
Niels Lohmann [GitHub](https://github.com/nlohmann/) for his json library

## authors
* **Robert 'BaumFX'** - *made the stuff* - [website](https://rob.gg) - [GitHub](https://github.com/BaumFX)

## license

its like (insert current line amount) lines but dont say you made it, okay?
