#include <string>
#include "request.hpp"
#include "json/json.hpp"

namespace smspva {
	namespace internal {
		auto get_request(std::string method = "", std::string country = "", std::string service = "", std::string id = "", std::string api_key = "", std::string op = "") {
			try {
				std::string url = "http://smspva.com/priemnik.php?";

				if (method != "") { url += "method=" + method; }
				if (country != "") { url += "&country=" + country; }
				if (service != "") { url += "&service=" + service; }
				if (id != "") { url += "&id=" + id; }
				if (api_key != "") { url += "&apikey=" + api_key; }
				if (op != "") { url += "&operator=" + op; }

				auto request = http::request(url);
				const auto response = request.send("GET");

				return std::string(response.body.begin(), response.body.end());
			}
			catch (const std::exception & e) { std::cout << "[-] failed to make request: " << e.what() << std::endl; return std::string(""); }
		}
	}

	namespace countries {
		enum country {
			country_russian_federation = 0,
			country_kazakhstan = 1,
			country_ukraine = 2,
			country_romania = 3,
			country_argentina = 4,
			country_belarus = 5,
			country_brazil = 6,
			country_cambodia = 7,
			country_china_virtual = 8,
			country_cote_d_lvoire = 9,
			country_croatia = 10,
			country_estonia = 11,
			country_finland = 12,
			country_france = 13,
			country_georgia = 14,
			country_ghana = 15,
			country_haiti = 16,
			country_indonesia = 17,
			country_israel = 18,
			country_kenya = 19,
			country_kyrgyzstan = 20,
			country_latvia = 21,
			country_lithuania = 22,
			country_macao = 23,
			country_netherlands = 24,
			country_new_zealand = 25,
			country_paraguay = 26,
			country_philippines = 27,
			country_poland = 28,
			country_serbia = 29,
			country_sweden = 30,
			country_uk_virtual = 31,
			country_united_kingdom = 32,
			country_united_states = 33,
			country_vietnam = 34
		};

		std::string get_string(country input) {
			std::string result;

			switch (input) {
			case country_russian_federation: result = "RU"; break;
			case country_kazakhstan: result = "KZ"; break;
			case country_ukraine: result = "UA"; break;
			case country_romania: result = "RO"; break;
			case country_argentina: result = "AR"; break;
			case country_belarus: result = "BY"; break;
			case country_brazil: result = "BR"; break;
			case country_cambodia: result = "KH"; break;
			case country_china_virtual: result = "CN2"; break;
			case country_cote_d_lvoire: result = "CI"; break;
			case country_croatia: result = "HR"; break;
			case country_estonia: result = "EE"; break;
			case country_finland: result = "FI"; break;
			case country_france: result = "FR"; break;
			case country_georgia: result = "GE"; break;
			case country_ghana: result = "GH"; break;
			case country_haiti: result = "HT"; break;
			case country_indonesia: result = "ID"; break;
			case country_israel: result = "IL"; break;
			case country_kenya: result = "KE"; break;
			case country_kyrgyzstan: result = "KG"; break;
			case country_latvia: result = "LV"; break;
			case country_lithuania: result = "LT"; break;
			case country_macao: result = "MO"; break;
			case country_netherlands: result = "NL"; break;
			case country_new_zealand: result = "NZ"; break;
			case country_paraguay: result = "PY"; break;
			case country_philippines: result = "PH"; break;
			case country_poland: result = "PL"; break;
			case country_serbia: result = "RS"; break;
			case country_sweden: result = "SE"; break;
			case country_uk_virtual: result = "UK_V"; break;
			case country_united_kingdom: result = "UK"; break;
			case country_united_states: result = "US"; break;
			case country_vietnam: result = "VN"; break;
			}

			return result;
		}
	}
	
	namespace services {
		enum service {
			service_1688 = 0,
			service_adidas_nike = 1,
			service_airbnb = 2,
			service_amazon = 3,
			service_amazon_incoming_call_voice = 4,
			service_aol = 5,
			service_auto_ru = 6,
			service_avito = 7,
			service_badoo = 8,
			service_betfair = 9,
			service_bittube = 10,
			service_bolt = 11,
			service_burgerking = 12,
			service_careem = 13,
			service_cdkeys_com = 14,
			service_citymobil = 15,
			service_craigslist = 16,
			service_dent = 17,
			service_didi = 18,
			service_discord = 19,
			service_dodopizza_papa_johns = 20,
			service_doordash = 21,
			service_drom_ru = 22,
			service_drug_vokrug = 23,
			service_dukascopy = 24,
			service_enjin_wallet = 25,
			service_facebook = 26,
			service_fastmail = 27,
			service_fiverr = 28,
			service_fotostrana = 29,
			service_g2a = 30,
			service_gameflip = 31,
			service_gettaxi = 32,
			service_gmail_youtube = 33,
			service_grabtaxi = 34,
			service_holvi = 35,
			service_hq_trivia = 36,
			service_icard = 37,
			service_instagram = 38,
			service_jd_com = 39,
			service_kakaotalk = 40,
			service_kriptomat_io = 41,
			service_lazada = 42,
			service_line_messenger = 43,
			service_linkedon = 44,
			service_livescore = 45,
			service_lyft = 46,
			service_mail_ru = 47,
			service_mail_ru_group = 48,
			service_mamba = 49,
			service_meetme = 50,
			service_michat = 51,
			service_ms_office = 52,
			service_ms_bing_hotmail = 53,
			service_naver = 54,
			service_netflix = 55,
			service_od = 56,
			service_olacabs = 57,
			service_olx_good_ru = 58,
			service_other = 59,
			service_payoal_ebay = 60,
			service_pof = 61,
			service_post_bank = 62,
			service_proton_mail = 63,
			service_rambler = 64,
			service_seosprint = 65,
			service_sipnet_ru = 66,
			service_snapchat = 67,
			service_spotify = 68,
			service_steam = 69,
			service_steemit = 70,
			service_suomi24 = 71,
			service_taobao = 72,
			service_taxi_maksim = 73,
			service_telegram = 74,
			service_tencent = 75,
			service_the_insiders = 76,
			service_tiktok = 77,
			service_tinder = 78,
			service_tinkoff_easypay = 79,
			service_twilio = 80,
			service_twitter = 81,
			service_ubank_ru = 82,
			service_uber = 83,
			service_venmo = 84,
			service_viber = 85,
			service_vk = 86,
			service_webmoney_enum = 87,
			service_wechat = 88,
			service_weebly = 89,
			service_whatsapp = 90,
			service_worldcore = 91,
			service_yahoo = 92,
			service_yandex = 93,
			service_zoho = 94
		};

		std::string get_string(service input) {
			std::string result;

			switch (input) {
			case service_1688: result = "opt28"; break;
			case service_adidas_nike: result = "opt86"; break;
			case service_airbnb: result = "opt46"; break;
			case service_amazon: result = "opt44"; break;
			case service_amazon_incoming_call_voice: result = "opt901"; break;
			case service_aol: result = "opt10"; break;
			case service_auto_ru: result = "opt38"; break;
			case service_avito: result = "opt59"; break;
			case service_badoo: result = "opt56"; break;
			case service_betfair: result = "opt25"; break;
			case service_bittube: result = "opt88"; break;
			case service_bolt: result = "opt81"; break;
			case service_burgerking: result = "opt3"; break;
			case service_careem: result = "opt89"; break;
			case service_cdkeys_com: result = "opt39"; break;
			case service_citymobil: result = "opt76"; break;
			case service_craigslist: result = "opt26"; break;
			case service_dent: result = "opt99"; break;
			case service_didi: result = "opt92"; break;
			case service_discord: result = "opt45"; break;
			case service_dodopizza_papa_johns: result = "opt27"; break;
			case service_doordash: result = "opt40"; break;
			case service_drom_ru: result = "opt32"; break;
			case service_drug_vokrug: result = "opt31"; break;
			case service_dukascopy: result = "opt48"; break;
			case service_enjin_wallet: result = "opt49"; break;
			case service_facebook: result = "opt2"; break;
			case service_fastmail: result = "opt43"; break;
			case service_fiverr: result = "opt6"; break;
			case service_fotostrana: result = "opt13"; break;
			case service_g2a: result = "opt68"; break;
			case service_gameflip: result = "opt77"; break;
			case service_gettaxi: result = "opt35"; break;
			case service_gmail_youtube: result = "opt1"; break;
			case service_grabtaxi: result = "opt30"; break;
			case service_holvi: result = "opt80"; break;
			case service_hq_trivia: result = "opt47"; break;
			case service_icard: result = "opt103"; break;
			case service_instagram: result = "opt16"; break;
			case service_jd_com: result = "opt94"; break;
			case service_kakaotalk: result = "opt71"; break;
			case service_kriptomat_io: result = "opt0"; break;
			case service_lazada: result = "opt60"; break;
			case service_line_messenger: result = "opt37"; break;
			case service_linkedon: result = "opt8"; break;
			case service_livescore: result = "opt42"; break;
			case service_lyft: result = "opt75"; break;
			case service_mail_ru: result = "opt33"; break;
			case service_mail_ru_group: result = "opt4"; break;
			case service_mamba: result = "opt100"; break;
			case service_meetme: result = "opt17"; break;
			case service_michat: result = "opt96"; break;
			case service_ms_office: result = "opt7"; break;
			case service_ms_bing_hotmail: result = "opt15"; break;
			case service_naver: result = "opt73"; break;
			case service_netflix: result = "opt101"; break;
			case service_od: result = "opt5"; break;
			case service_olacabs: result = "opt95"; break;
			case service_olx_good_ru: result = "opt70"; break;
			case service_other: result = "opt19"; break;
			case service_payoal_ebay: result = "opt83"; break;
			case service_pof: result = "opt84"; break;
			case service_post_bank: result = "opt97"; break;
			case service_proton_mail: result = "opt57"; break;
			case service_rambler: result = "opt53"; break;
			case service_seosprint: result = "opt22"; break;
			case service_sipnet_ru: result = "opt51"; break;
			case service_snapchat: result = "opt90"; break;
			case service_spotify: result = "opt98"; break;
			case service_steam: result = "opt58"; break;
			case service_steemit: result = "opt78"; break;
			case service_suomi24: result = "opt91"; break;
			case service_taobao: result = "opt61"; break;
			case service_taxi_maksim: result = "opt74"; break;
			case service_telegram: result = "opt29"; break;
			case service_tencent: result = "opt77"; break;
			case service_the_insiders: result = "opt14"; break;
			case service_tiktok: result = "opt104"; break;
			case service_tinder: result = "opt9"; break;
			case service_tinkoff_easypay: result = "opt21"; break;
			case service_twilio: result = "opt66"; break;
			case service_twitter: result = "opt41"; break;
			case service_ubank_ru: result = "opt52"; break;
			case service_uber: result = "opt72"; break;
			case service_venmo: result = "opt85"; break;
			case service_viber: result = "opt11"; break;
			case service_vk: result = "opt69"; break;
			case service_webmoney_enum: result = "opt24"; break;
			case service_wechat: result = "opt67"; break;
			case service_weebly: result = "opt54"; break;
			case service_whatsapp: result = "opt20"; break;
			case service_worldcore: result = "opt82"; break;
			case service_yahoo: result = "opt65"; break;
			case service_yandex: result = "opt23"; break;
			case service_zoho: result = "opt93"; break;
			}

			return result;
		}
	}

	class number {
	public:
		number(int id, std::string number, std::string country_code, countries::country country, services::service service) { this->id = id; this->num = number; this->country_code = country_code; this->service = service; this->country = country; }
		int id;
		std::string num;
		std::string country_code;
		services::service service;
		countries::country country;
	};

	class smspva {
	public:
		smspva(std::string api_key) { this->api_key = api_key; }
		double get_balance() {
			auto result = internal::get_request("get_balance", "", "opt4", "", this->api_key, "");
			if (result == "") { std::cout << "[-] failed to get account balance" << std::endl; }
			else if (result == "API KEY not received!") { std::cout << "[-] no api key provided" << std::endl; }
			else {
				try { std::string balance = nlohmann::json::parse(result)["balance"]; return strtof(balance.c_str(), 0); }
				catch (std::exception & ex) { std::cout << "[-] exception: " << ex.what() << std::endl; }
			}
			return -1.0;
		}

		int get_karma() {
			auto result = internal::get_request("get_userinfo", "", "opt4", "", this->api_key, "");
			if (result == "") { std::cout << "[-] failed to get account karma" << std::endl; }
			else if (result == "API KEY not received!") { std::cout << "[-] no api key provided" << std::endl; }
			else {
				try { std::string karma = nlohmann::json::parse(result)["karma"]; return std::stoi(karma.c_str(), 0); }
				catch (std::exception & ex) { std::cout << "[-] exception: " << ex.what() << std::endl; }
			}
			return -1;
		}
		int get_available_total(countries::country country, services::service service) {
			auto result = internal::get_request("get_count_new", countries::get_string(country), services::get_string(service), "", this->api_key, "");
			if (result == "") { std::cout << "[-] failed to get total available numbers" << std::endl; }
			else if (result == "API KEY not received!") { std::cout << "[-] no api key provided" << std::endl; }
			else {
				try { return nlohmann::json::parse(result)["total"]; }
				catch (std::exception & ex) { std::cout << "[-] exception: " << ex.what() << std::endl; }
			}
			return -1;
		}

		int get_available_now(countries::country country, services::service service) {
			auto result = internal::get_request("get_count_new", countries::get_string(country), services::get_string(service), "", this->api_key, "");
			if (result == "") { std::cout << "[-] failed to get now available numbers" << std::endl; }
			else if (result == "API KEY not received!") { std::cout << "[-] no api key provided" << std::endl; }
			else {
				try { return nlohmann::json::parse(result)["online"]; }
				catch (std::exception & ex) { std::cout << "[-] exception: " << ex.what() << std::endl; }
			}
			return -1;
		}

		int get_available_call_total(countries::country country, services::service service) {
			auto result = internal::get_request("get_count_new", countries::get_string(country), services::get_string(service), "", this->api_key, "");
			if (result == "") { std::cout << "[-] failed to get total available numbers for call forwarding" << std::endl; }
			else if (result == "API KEY not received!") { std::cout << "[-] no api key provided" << std::endl; }
			else {
				try { return nlohmann::json::parse(result)["forTotal"]; }
				catch (std::exception & ex) { std::cout << "[-] exception: " << ex.what() << std::endl; }
			}
			return -1;
		}

		int get_available_call_now(countries::country country, services::service service) {
			auto result = internal::get_request("get_count_new", countries::get_string(country), services::get_string(service), "", this->api_key, "");
			if (result == "") { std::cout << "[-] failed to get current available numbers for call forwarding" << std::endl; }
			else if (result == "API KEY not received!") { std::cout << "[-] no api key provided" << std::endl; }
			else {
				try { return nlohmann::json::parse(result)["forOnline"]; }
				catch (std::exception & ex) { std::cout << "[-] exception: " << ex.what() << std::endl; }
			}
			return -1;
		}

		double get_price(countries::country country, services::service service) {
			auto result = internal::get_request("get_service_price", countries::get_string(country), services::get_string(service), "", this->api_key, "");
			if (result == "") { std::cout << "[-] failed to get number price" << std::endl; }
			else if (result == "API KEY not received!") { std::cout << "[-] no api key provided" << std::endl; }
			else {
				try { std::string balance = nlohmann::json::parse(result)["price"]; return strtof(balance.c_str(), 0); }
				catch (std::exception & ex) { std::cout << "[-] exception: " << ex.what() << std::endl; }
			}
			return -1.0;
		}

		number* get_number(countries::country country, services::service service) {
			auto result = internal::get_request("get_number", countries::get_string(country), services::get_string(service), "", this->api_key, "");
			if (result == "") { std::cout << "[-] failed to get number" << std::endl; }
			else if (result == "API KEY not received!") { std::cout << "[-] no api key provided" << std::endl; }
			else {
				try { nlohmann::json target = nlohmann::json::parse(result); return new number(target["id"], target["number"], target["CountryCode"], country, service); }
				catch (std::exception & ex) { std::cout << "[-] exception: " << ex.what() << std::endl; }
			}
			return nullptr;
		}

		int report_number(number* num) {
			auto result = internal::get_request("ban", "", services::get_string(num->service), "", this->api_key, "");
			if (result == "") { std::cout << "[-] failed to report number" << std::endl; }
			else if (result == "API KEY not received!") { std::cout << "[-] no api key provided" << std::endl; }
			else {
				try { return nlohmann::json::parse(result)["id"]; }
				catch (std::exception & ex) { std::cout << "[-] exception: " << ex.what() << std::endl; }
			}
			return -1;
		}

		int get_code(number* num) {
			auto result = internal::get_request("get_sms", countries::get_string(num->country), services::get_string(num->service), std::to_string(num->id), this->api_key, "");
			if (result == "") { std::cout << "[-] failed to report number" << std::endl; }
			else if (result == "API KEY not received!") { std::cout << "[-] no api key provided" << std::endl; }
			else {
				try { nlohmann::json target = nlohmann::json::parse(result); if (target["sms"] == nullptr) { return 0; } else { return target["sms"]; } }
				catch (std::exception & ex) { std::cout << "[-] exception: " << ex.what() << std::endl; }
			}
			return -1;
		}

		int cancel_number(number* num) {
			auto result = internal::get_request("denial", countries::get_string(num->country), services::get_string(num->service), std::to_string(num->id), this->api_key, "");
			if (result == "") { std::cout << "[-] failed to cancel number" << std::endl; }
			else if (result == "API KEY not received!") { std::cout << "[-] no api key provided" << std::endl; }
			else {
				try { return nlohmann::json::parse(result)["id"]; }
				catch (std::exception & ex) { std::cout << "[-] exception: " << ex.what() << std::endl; }
			}
			return -1;
		}
	private:
		std::string api_key;
	};
}
