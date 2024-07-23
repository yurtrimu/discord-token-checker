#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "json/json.hpp"

#include "utils/curlget.h"

using json = nlohmann::json;

struct discord_user_data {
	std::string user_id;
	std::string user_name;
	std::string discriminator;
	std::string global_name;
	std::string phone_number;
	std::string email;
	std::string bio;

	std::string locale;
	std::string nitro_type;

	std::string avatar_url;
	std::string banner_url;

	std::string verified;

	std::string mfa_enabled;

	std::string authenticator_types;
};

struct discord_connection_data {
	std::string id;
	std::string name;
	std::string type;
};

struct discord_gift_data {

	std::string title;
	std::string url;
	std::string code;
};

struct discord_billing_data {
	std::string id;
	std::string invalid;
	std::string brand;
	std::string last_4;
	std::string expires_month;
	std::string expires_year;
	std::string country;

	struct billing_address {
		std::string name;
		std::string line_1;
		std::string line_2;
		std::string city;
		std::string state;
		std::string country;
		std::string postal_code;
	} billing_address;
};

namespace DiscordChecker {

	std::string remove_quotes(const std::string &str) {

		std::string result;
		for (char c : str) {
			if (c != '"') {
				result += c;
			}
		}
		return result;
	}

	std::string get_billing_type(int type) {
		switch (type)
		{
		case 1: { return std::string("Credit card"); } break;
		case 2: { return std::string("Paypal"); } break;
		default: { return std::string("Unknown"); } break;
		}
	}

	std::string get_nitro_type(int type) {
		switch (type)
		{
		case 0: { return std::string("No Nitro"); } break;
		case 1: { return std::string("Nitro Classic"); } break;
		case 2: { return std::string("Nitro Boost"); } break;
		default: { return std::string("Unknown"); } break;
		}
	}

	std::string get_auth_type(int type) {
		switch (type)
		{
		case 1: { return std::string("WebAuthn"); } break;
		case 2: { return std::string("2FA"); } break;
		case 3: { return std::string("SMS"); } break;
		default: { return std::string("Unknown"); } break;
		}
	}

	std::string get_auth_types(json &j) {
		std::string result;

		int index = 0;
		for (json &element : j) {
			result += get_auth_type(std::stoi(remove_quotes(element.dump())));

			if (index != j.size() - 1) {
				result += ", ";
			}

			index++;
		}

		return result;
	}

	std::string cdn_image(std::string &id, std::string &image) {
		return std::string("https://cdn.discordapp.com/avatars/") + id + std::string("/") + image;
	}

	std::string cdn_banner(std::string &id, std::string &image) {
		return std::string("https://cdn.discordapp.com/banners/") + id + std::string("/") + image;
	}

	std::vector<std::string> discord_endpoints = {
		"https://discord.com/api/v9/users/@me",
		"https://discord.com/api/v9/users/@me/billing/payment-sources",
		"https://discord.com/api/v9/users/@me/connections",
		"https://discord.com/api/v9/users/@me/outbound-promotions/codes?locale=en-US"
	};

	void print_user_data(const discord_user_data &user) {
		std::cout << "\033[32mUSER INFORMATION\033[0m" << std::endl << "______________________________________" << std::endl << std::endl;
		std::cout << "User ID: " << user.user_id << std::endl;
		std::cout << "User Name: " << user.user_name << std::endl;
		std::cout << "Discriminator: " << user.discriminator << std::endl;
		std::cout << "Global Name: " << user.global_name << std::endl;
		std::cout << "Phone Number: " << user.phone_number << std::endl;
		std::cout << "Email: " << user.email << std::endl;
		std::cout << "Bio: " << user.bio << std::endl;
		std::cout << "Locale: " << user.locale << std::endl;
		std::cout << "Nitro Type: " << user.nitro_type << std::endl;
		std::cout << "Avatar URL: " << user.avatar_url << std::endl;
		std::cout << "Banner URL: " << user.banner_url << std::endl;
		std::cout << "Verified: " << user.verified << std::endl;
		std::cout << "MFA Enabled: " << user.mfa_enabled << std::endl;
		std::cout << "Authenticator Types: " << user.authenticator_types << std::endl;
		std::cout << "______________________________________" << std::endl << std::endl;
	}

	void print_billing_data(const std::vector<discord_billing_data> &data_list) {

		std::cout << "\033[32mBILLING INFORMATION\033[0m" << std::endl << "______________________________________" << std::endl;

		int index = 1;
		for (discord_billing_data data : data_list) {
			std::cout << "\n\033[32mBilling " << std::to_string(index) << "\033[0m:" << std::endl;
			std::cout << "___________________" << std::endl << std::endl;

			std::cout << "ID: " << data.id << std::endl;
			std::cout << "Invalid: " << data.invalid << std::endl;
			std::cout << "Brand: " << data.brand << std::endl;
			std::cout << "Last 4: " << data.last_4 << std::endl;
			std::cout << "Expires Month: " << data.expires_month << std::endl;
			std::cout << "Expires Year: " << data.expires_year << std::endl;
			std::cout << "Country: " << data.country << std::endl << std::endl;

			std::cout << "\033[32mBilling Address\033[0m:" << std::endl;
			std::cout << "_________" << std::endl << std::endl;
			std::cout << "Name: " << data.billing_address.name << std::endl;
			std::cout << "Line 1: " << data.billing_address.line_1 << std::endl;
			std::cout << "Line 2: " << data.billing_address.line_2 << std::endl;
			std::cout << "City: " << data.billing_address.city << std::endl;
			std::cout << "State: " << data.billing_address.state << std::endl;
			std::cout << "Country: " << data.billing_address.country << std::endl;
			std::cout << "Postal Code: " << data.billing_address.postal_code << std::endl;
			std::cout << "_________" << std::endl;
			std::cout << "___________________" << std::endl;

			index++;
		}

		std::cout << "______________________________________" << std::endl << std::endl;
	}

	void print_connection_data(const std::vector<discord_connection_data> &data_list) {
		std::cout << "\033[32mCONNECTION INFORMATION\033[0m" << std::endl << "______________________________________" << std::endl;

		int index = 1;
		for (discord_connection_data data : data_list) {
			std::cout << "\n\033[32mConnection " << std::to_string(index) << "\033[0m:" << std::endl;
			std::cout << "___________________" << std::endl << std::endl;

			std::cout << "ID: " << data.id << std::endl;
			std::cout << "Name: " << data.name << std::endl;
			std::cout << "Type: " << data.type << std::endl;
			std::cout << "___________________" << std::endl;

			index++;
		}

		std::cout << "______________________________________" << std::endl << std::endl;
	}

	void print_gift_data(const std::vector<discord_gift_data> &data_list) {
		std::cout << "\033[32mGIFT INFORMATION\033[0m" << std::endl << "______________________________________" << std::endl;

		int index = 1;
		for (discord_gift_data data : data_list) {
			std::cout << "\n\033[32mGift " << std::to_string(index) << "\033[0m:" << std::endl;
			std::cout << "___________________" << std::endl << std::endl;

			std::cout << "Title: " << data.title << std::endl;
			std::cout << "Url Format: " << data.url << std::endl;
			std::cout << "Code: " << data.code << std::endl;
			std::cout << "___________________" << std::endl;

			index++;
		}

		std::cout << "______________________________________" << std::endl << std::endl;
	}
	
	bool Collect(discord_user_data &user_data, std::vector<discord_billing_data> &billing_data_list, std::vector<discord_connection_data> &connection_data_list, std::vector<discord_gift_data> &gift_data_list, std::string &discord_token) {

		std::string token = discord_token;
		std::vector<std::string> custom_headers = {
			"Authorization: " + token,
			"Content-Type: application/json",
			"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36"
		};

		std::string response;

		// /@me
		try
		{
			if (curl_get(discord_endpoints[0], custom_headers, response)) {
				json json_data = json::parse(response);

				user_data.user_id = remove_quotes(json_data["id"].dump());
				user_data.user_name = remove_quotes(json_data["username"].dump());
				user_data.discriminator = remove_quotes(json_data["discriminator"].dump());
				user_data.global_name = remove_quotes(json_data["global_name"].dump());
				user_data.phone_number = remove_quotes(json_data["phone"].dump());
				user_data.email = remove_quotes(json_data["email"].dump());
				user_data.locale = remove_quotes(json_data["locale"].dump());
				user_data.nitro_type = get_nitro_type(std::stoi(remove_quotes(json_data["premium_type"].dump())));
				user_data.bio = "{\n" + remove_quotes(json_data["bio"].dump()) + "\n}";
				user_data.avatar_url = remove_quotes(json_data["avatar"].dump());
				user_data.avatar_url = cdn_image(user_data.user_id, user_data.avatar_url);
				user_data.banner_url = remove_quotes(json_data["banner"].dump());
				user_data.banner_url = cdn_banner(user_data.user_id, user_data.banner_url);
				user_data.verified = remove_quotes(json_data["verified"].dump());
				user_data.mfa_enabled = remove_quotes(json_data["mfa_enabled"].dump());
				user_data.authenticator_types = get_auth_types(json_data["authenticator_types"]);
			}
			else { printf("Something went wrong.\n"); return ERROR; }
		}
		catch (const std::exception &ex)
		{
			printf("Error on user data, %s\n", ex.what()); return ERROR;
		}

		response.clear();

		// /@me/billing/payment-sources
		try
		{
			if (curl_get(discord_endpoints[1], custom_headers, response)) {
				json json_data = json::parse(response);

				for (const auto &data : json_data) {
					discord_billing_data billing_data;

					billing_data.id = remove_quotes(data["id"].dump());
					billing_data.invalid = remove_quotes(data["invalid"].dump());
					billing_data.brand = remove_quotes(data["brand"].dump());
					billing_data.last_4 = remove_quotes(data["last_4"].dump());
					billing_data.expires_month = remove_quotes(data["expires_month"].dump());
					billing_data.expires_year = remove_quotes(data["expires_year"].dump());
					billing_data.country = remove_quotes(data["country"].dump());

					if (data["billing_address"].is_array()) {
						// Billing address fields:
						billing_data.billing_address.name = remove_quotes(data["billing_address"]["name"].dump());
						billing_data.billing_address.line_1 = remove_quotes(data["billing_address"]["line_1"].dump());
						billing_data.billing_address.line_2 = remove_quotes(data["billing_address"]["line_2"].dump());
						billing_data.billing_address.city = remove_quotes(data["billing_address"]["city"].dump());
						billing_data.billing_address.state = remove_quotes(data["billing_address"]["state"].dump());
						billing_data.billing_address.country = remove_quotes(data["billing_address"]["country"].dump());
						billing_data.billing_address.postal_code = remove_quotes(data["billing_address"]["postal_code"].dump());
					}

					billing_data_list.push_back(billing_data);
				}
			}
		}
		catch (const std::exception &ex)
		{
			printf("Error on billing, %s\n", ex.what()); return ERROR;
		}

		response.clear();

		// /@me/connections
		try
		{
			if (curl_get(discord_endpoints[2], custom_headers, response)) {
				json json_data = json::parse(response);

				for (const auto &data : json_data) {
					discord_connection_data connection_data;

					connection_data.id = remove_quotes(data["id"].dump());
					connection_data.name = remove_quotes(data["name"].dump());
					connection_data.type = remove_quotes(data["type"].dump());

					connection_data_list.push_back(connection_data);
				}
			}
			else { printf("Something went wrong.\n"); return ERROR; }
		}
		catch (const std::exception &ex)
		{
			printf("Error on connections, %s\n", ex.what()); return ERROR;
		}

		response.clear();

		// /@me/outbound-promotions/codes?locale=en-US
		try
		{
			if (curl_get(discord_endpoints[3], custom_headers, response)) {
				json json_data = json::parse(response);

				for (const auto &data : json_data) {
					discord_gift_data gift_data;

					gift_data.code = remove_quotes(data["code"].dump());
					gift_data.title = remove_quotes(data["promotion"]["outbound_title"].dump());
					gift_data.url = remove_quotes(data["promotion"]["outbound_redemption_url_format"].dump());

					gift_data_list.push_back(gift_data);
				}
			}
			else { printf("Something went wrong.\n"); return ERROR; }
		}
		catch (const std::exception &ex)
		{
			printf("Error on promotions, %s\n", ex.what()); return ERROR;
		}

		response.clear();
	}

}
