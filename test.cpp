#include <string>
#include <iostream>
#include <thread>

#include "smspva.hpp"

int main() {
	smspva::smspva api = smspva::smspva("YOUR_KEY_HERE");

	double balance = api.get_balance();
	if (balance == -1) { std::cout << "[-] failed to get balance" << std::endl; }
	else { std::cout << "[+] successfully got balance: " << balance << std::endl; }

	int karma = api.get_karma();
	if (karma == -1) { std::cout << "[-] failed to get karma" << std::endl; }
	else { std::cout << "[+] successfully got karma: " << karma << std::endl; }

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

	double price = api.get_price(smspva::countries::country::country_russian_federation, smspva::services::service::service_whatsapp);
	if (price == -1) { std::cout << "[-] failed to get price" << std::endl; }
	else { std::cout << "[+] successfully got price: " << price << std::endl; }

	smspva::number* new_num = api.get_number(smspva::countries::country::country_russian_federation, smspva::services::service::service_whatsapp);
	if (new_num == nullptr) { std::cout << "[-] failed to get number" << std::endl; }
	else { std::cout << "[+] successfully got number with id " << new_num->id << " and number " << new_num->num << std::endl; }

	int reported_number = api.report_number(new_num);
	if (reported_number == -1) { std::cout << "[-] failed to report number" << std::endl; }
	else { std::cout << "[+] successfully reported number with id: " << new_num->id << std::endl; }

	int sms = api.get_code(new_num);
	if (sms == -1) { std::cout << "[-] failed to get sms from number" << std::endl; }
	else if (sms == 0) { std::cout << "[-] sms not yet received, wait 20s and retry" << std::endl; }
	else { std::cout << "[+] successfully received sms with code " << sms << std::endl; }

	int cancel_number = api.cancel_number(new_num);
	if (cancel_number == -1) { std::cout << "[-] failed to cancel number" << std::endl; }
	else { std::cout << "[+] successfully cancelled number with id: " << new_num->id << std::endl; }

	delete new_num;

	std::this_thread::sleep_for(std::chrono::seconds(1000));
	return 0;
}
