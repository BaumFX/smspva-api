#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <system_error>
#include <map>
#include <string>
#include <vector>
#include <cctype>
#include <cstddef>
#include <cstdint>
#pragma push_macro("WIN32_LEAN_AND_MEAN")
#pragma push_macro("NOMINMAX")
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#pragma pop_macro("WIN32_LEAN_AND_MEAN")
#pragma pop_macro("NOMINMAX")

namespace http {
	class rob_sock final {
	public:
		rob_sock() {
			WSADATA wsa_data;
			if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) { throw std::runtime_error("[-] failed to startup wsa"); }

			if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2) { WSACleanup(); throw std::runtime_error("[-] invalid winsock version"); }

			started = true;
		}

		~rob_sock() { if (started) { WSACleanup(); } }

		rob_sock(const rob_sock&) = delete;
		rob_sock& operator=(const rob_sock&) = delete;

		rob_sock(rob_sock&& other) noexcept : started(other.started) { other.started = false; }

		rob_sock& operator=(rob_sock&& other) noexcept { if (&other == this) { return *this; } if (started) { WSACleanup(); } started = other.started; other.started = false; return *this;
		}

	private:
		bool started = false;
	};

	enum class internet_protocol : uint8_t { v4, v6 };

	constexpr int get_address_family(internet_protocol inet_protoc) { return (inet_protoc == internet_protocol::v4) ? AF_INET : (inet_protoc == internet_protocol::v6) ? AF_INET6 : throw std::runtime_error("[-] unsupported protocol"); }

	class rob_socket final {
	public:
		explicit rob_socket(internet_protocol inet_protoc) : endpoint(socket(get_address_family(inet_protoc), SOCK_STREAM, IPPROTO_TCP)) { if (endpoint == INVALID_SOCKET) { throw std::runtime_error("[-] failed to create socket"); } }

		explicit rob_socket(SOCKET s) noexcept : endpoint(s) { }

		~rob_socket() { if (endpoint != INVALID_SOCKET) { closesocket(endpoint); } }

		rob_socket(const rob_socket&) = delete;
		rob_socket& operator=(const rob_socket&) = delete;

		rob_socket(rob_socket&& other) noexcept : endpoint(other.endpoint) { other.endpoint = INVALID_SOCKET; }

		rob_socket& operator=(rob_socket&& other) noexcept { if (&other == this) { return *this; } if (endpoint != INVALID_SOCKET) { closesocket(endpoint); } endpoint = other.endpoint; other.endpoint = INVALID_SOCKET; return *this; }

		inline operator SOCKET() const noexcept { return endpoint; }

	private:
		SOCKET endpoint = INVALID_SOCKET;
	};


	inline std::string url_encode(const std::string& str) {
		constexpr char hex_chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

		std::string result;

		for (auto i = str.begin(); i != str.end(); ++i) {
			const uint8_t cp = *i & 0xFF;

			if ((cp >= 0x30 && cp <= 0x39) || (cp >= 0x41 && cp <= 0x5A) || (cp >= 0x61 && cp <= 0x7A) || cp == 0x2D || cp == 0x2E || cp == 0x5F) { result += static_cast<char>(cp); }
			else if (cp <= 0x7F) { result += std::string("%") + hex_chars[(*i & 0xF0) >> 4] + hex_chars[*i & 0x0F]; }
			else if ((cp >> 5) == 0x06) { result += std::string("%") + hex_chars[(*i & 0xF0) >> 4] + hex_chars[*i & 0x0F]; if (++i == str.end()) { break; } result += std::string("%") + hex_chars[(*i & 0xF0) >> 4] + hex_chars[*i & 0x0F]; }
			else if ((cp >> 4) == 0x0E) { result += std::string("%") + hex_chars[(*i & 0xF0) >> 4] + hex_chars[*i & 0x0F]; if (++i == str.end()) { break; } result += std::string("%") + hex_chars[(*i & 0xF0) >> 4] + hex_chars[*i & 0x0F]; if (++i == str.end()) { break; } result += std::string("%") + hex_chars[(*i & 0xF0) >> 4] + hex_chars[*i & 0x0F]; }
			else if ((cp >> 3) == 0x1E) { result += std::string("%") + hex_chars[(*i & 0xF0) >> 4] + hex_chars[*i & 0x0F]; if (++i == str.end()) { break; } result += std::string("%") + hex_chars[(*i & 0xF0) >> 4] + hex_chars[*i & 0x0F]; if (++i == str.end()) { break; } result += std::string("%") + hex_chars[(*i & 0xF0) >> 4] + hex_chars[*i & 0x0F]; if (++i == str.end()) { break; } result += std::string("%") + hex_chars[(*i & 0xF0) >> 4] + hex_chars[*i & 0x0F]; }
		}

		return result;
	}

	struct response final {
		enum status {
			STATUS_CONTINUE = 100,
			STATUS_SWITCHINGPROTOCOLS = 101,
			STATUS_PROCESSING = 102,
			STATUS_EARLYHINTS = 103,

			STATUS_OK = 200,
			STATUS_CREATED = 201,
			STATUS_ACCEPTED = 202,
			STATUS_NONAUTHORITATIVEINFORMATION = 203,
			STATUS_NOCONTENT = 204,
			STATUS_RESETCONTENT = 205,
			STATUS_PARTIALCONTENT = 206,
			STATUS_MULTISTATUS = 207,
			STATUS_ALREADYREPORTED = 208,
			STATUS_IMUSED = 226,

			STATUS_MULTIPLECHOICES = 300,
			STATUS_MOVEDPERMANENTLY = 301,
			STATUS_FOUND = 302,
			STATUS_SEEOTHER = 303,
			STATUS_NOTMODIFIED = 304,
			STATUS_USEPROXY = 305,
			STATUS_TEMPORARYREDIRECT = 307,
			STATUS_PERMANENTREDIRECT = 308,

			STATUS_BADREQUEST = 400,
			STATUS_UNAUTHORIZED = 401,
			STATUS_PAYMENTREQUIRED = 402,
			STATUS_FORBIDDEN = 403,
			STATUS_NOTFOUND = 404,
			STATUS_METHODNOTALLOWED = 405,
			STATUS_NOTACCEPTABLE = 406,
			STATUS_PROXYAUTHENTICATIONREQUIRED = 407,
			STATUS_REQUESTTIMEOUT = 408,
			STATUS_CONFLICT = 409,
			STATUS_GONE = 410,
			STATUS_LENGTHREQUIRED = 411,
			STATUS_PRECONDITIONFAILED = 412,
			STATUS_PAYLOADTOOLARGE = 413,
			STATUS_URITOOLONG = 414,
			STATUS_UNSUPPORTEDMEDIATYPE = 415,
			STATUS_RANGENOTSATISFIABLE = 416,
			STATUS_EXPECTATIONFAILED = 417,
			STATUS_IMATEAPOT = 418,
			STATUS_MISDIRECTEDREQUEST = 421,
			STATUS_UNPROCESSABLEENTITY = 422,
			STATUS_LOCKED = 423,
			STATUS_FAILEDDEPENDENCY = 424,
			STATUS_TOOEARLY = 425,
			STATUS_UPGRADEREQUIRED = 426,
			STATUS_PRECONDITIONREQUIRED = 428,
			STATUS_TOOMANYREQUESTS = 429,
			STATUS_REQUESTHEADERFIELDSTOOLARGE = 431,
			STATUS_UNAVAILABLEFORLEGALREASONS = 451,

			STATUS_INTERNALSERVERERROR = 500,
			STATUS_NOTIMPLEMENTED = 501,
			STATUS_BADGATEWAY = 502,
			STATUS_SERVICEUNAVAILABLE = 503,
			STATUS_GATEWAYTIMEOUT = 504,
			STATUS_HTTPVERSIONNOTSUPPORTED = 505,
			STATUS_VARIANTALSONEGOTIATES = 506,
			STATUS_INSUFFICIENTSTORAGE = 507,
			STATUS_LOOPDETECTED = 508,
			STATUS_NOTEXTENDED = 510,
			STATUS_NETWORKAUTHENTICATIONREQUIRED = 511
		};

		int status = 0;
		std::vector<std::string> headers;
		std::vector<uint8_t> body;
	};

	class request final {
	public:
		explicit request(const std::string& url, internet_protocol protocol = internet_protocol::v4) : inet_protoc(protocol) {
			const auto end_position = url.find("://");

			if (end_position != std::string::npos) { scheme = url.substr(0, end_position); path = url.substr(end_position + 3); } else { scheme = "http"; path = url; }

			const auto fragment_position = path.find('#');

			if (fragment_position != std::string::npos) { path.resize(fragment_position); }

			const auto path_position = path.find('/');

			if (path_position == std::string::npos) { domain = path; path = "/"; } else { domain = path.substr(0, path_position); path = path.substr(path_position); }

			const auto port_position = domain.find(':');

			if (port_position != std::string::npos) { port = domain.substr(port_position + 1); domain.resize(port_position); } else { port = "80"; }
		}

		response send(const std::string& method, const std::map<std::string, std::string>& parameters, const std::vector<std::string>& headers = {}) {
			std::string body;
			bool first = true;

			for (const auto& parameter : parameters) {
				if (!first) { body += "&"; }
				first = false;

				body += url_encode(parameter.first) + "=" + url_encode(parameter.second);
			}

			return send(method, body, headers);
		}

		response send(const std::string& method = "GET", const std::string& body = "", const std::vector<std::string>& headers = {}) {
			response response;

			if (scheme != "http") { throw std::runtime_error("only the http scheme is supported"); }

			addrinfo hints = {};
			hints.ai_family = get_address_family(inet_protoc);
			hints.ai_socktype = SOCK_STREAM;

			addrinfo* info;
			if (getaddrinfo(domain.c_str(), port.c_str(), &hints, &info) != 0) { throw std::runtime_error("[-] failed to get address info of " + domain); }

			std::unique_ptr<addrinfo, decltype(&freeaddrinfo)> addressInfo(info, freeaddrinfo);

			rob_socket sock(inet_protoc);

			if (::connect(sock, addressInfo->ai_addr, addressInfo->ai_addrlen) < 0) { throw std::runtime_error("[-] failed to connect to " + domain + " on port " + port); }

			std::string request_data = method + " " + path + " HTTP/1.1\r\n";

			for (const std::string& header : headers) { request_data += header + "\r\n"; }

			request_data += "Host: " + domain + "\r\n";
			request_data += "Content-Length: " + std::to_string(body.size()) + "\r\n";

			request_data += "\r\n";
			request_data += body;

			constexpr int flags = 0;

			auto remaining = static_cast<int>(request_data.size());
			int sent = 0;

			while (remaining > 0) { const auto size = ::send(sock, request_data.data() + sent, static_cast<size_t>(remaining), flags); if (size < 0) { throw std::runtime_error("[-] failed to send data to " + domain + " on port " + port); } remaining -= size; sent += size; }

			uint8_t temp_buffer[4096];
			constexpr uint8_t crlf[] = { '\r', '\n' };
			std::vector<uint8_t> response_data;
			bool first_line = true;
			bool parsed_headers = false;
			bool content_length_received = false;
			unsigned long content_length = 0;
			bool chunked_response = false;
			size_t expected_chunk_size = 0;
			bool remove_ctlf_after_chunk = false;

			for (;;) {
				const auto size = recv(sock, reinterpret_cast<char*>(temp_buffer), sizeof(temp_buffer), flags);

				if (size < 0) { throw std::runtime_error("[-] failed to receive data from " + domain + " on port " + port); } else if (size == 0) { break; }

				response_data.insert(response_data.end(), temp_buffer, temp_buffer + size);

				if (!parsed_headers) {
					for (;;) {
						const auto i = std::search(response_data.begin(), response_data.end(), std::begin(crlf), std::end(crlf));
						if (i == response_data.end()) { break; }

						const std::string line(response_data.begin(), i);
						response_data.erase(response_data.begin(), i + 2);

						if (line.empty()) { parsed_headers = true; break; }
						else if (first_line) { 
							first_line = false;

							std::string::size_type last_pos = 0;
							const auto length = line.length();
							std::vector<std::string> parts;

							while (last_pos < length + 1) {
								auto pos = line.find(' ', last_pos);
								if (pos == std::string::npos) { pos = length; }
								if (pos != last_pos) { parts.emplace_back(line.data() + last_pos, static_cast<std::vector<std::string>::size_type>(pos) - last_pos); }
								last_pos = pos + 1;
							}
							if (parts.size() >= 2) { response.status = std::stoi(parts[1]); }
						}
						else {
							response.headers.push_back(line);

							const auto pos = line.find(':');

							if (pos != std::string::npos) {
								std::string header_name = line.substr(0, pos);
								std::string header_value = line.substr(pos + 1);

								header_value.erase(header_value.begin(), std::find_if(header_value.begin(), header_value.end(), [](int c) {return !std::isspace(c); }));

								header_value.erase(std::find_if(header_value.rbegin(), header_value.rend(), [](int c) {return !std::isspace(c); }).base(), header_value.end());

								if (header_name == "Content-Length") { content_length = std::stoul(header_value); content_length_received = true; response.body.reserve(content_length); }
								else if (header_name == "Transfer-Encoding") { if (header_value == "chunked") { chunked_response = true; } else { throw std::runtime_error("[-] unsupported transfer encoding: " + header_value); } }
							}
						}
					}
				}

				if (parsed_headers) {
					if (chunked_response) {
						bool data_received = false;
						for (;;) {
							if (expected_chunk_size > 0) {
								const auto to_write = std::min(expected_chunk_size, response_data.size());
								response.body.insert(response.body.end(), response_data.begin(), response_data.begin() + static_cast<ptrdiff_t>(to_write));
								response_data.erase(response_data.begin(), response_data.begin() + static_cast<ptrdiff_t>(to_write));
								expected_chunk_size -= to_write;

								if (expected_chunk_size == 0) remove_ctlf_after_chunk = true;
								if (response_data.empty()) break;
							}
							else {
								if (remove_ctlf_after_chunk) {
									if (response_data.size() >= 2) {
										remove_ctlf_after_chunk = false;
										response_data.erase(response_data.begin(), response_data.begin() + 2);
									}
									else break;
								}

								const auto i = std::search(response_data.begin(), response_data.end(), std::begin(crlf), std::end(crlf));

								if (i == response_data.end()) { break; }

								const std::string line(response_data.begin(), i);
								response_data.erase(response_data.begin(), i + 2);

								expected_chunk_size = std::stoul(line, nullptr, 16);

								if (expected_chunk_size == 0) { data_received = true; break; }
							}
						}

						if (data_received) { break; }
					}
					else {
						response.body.insert(response.body.end(), response_data.begin(), response_data.end());
						response_data.clear();

						if (content_length_received && response.body.size() >= content_length) { break; }
					}
				}
			}
			return response;
		}

	private:
		rob_sock win_sock;
		internet_protocol inet_protoc;
		std::string scheme;
		std::string domain;
		std::string port;
		std::string path;
	};
}

#endif
