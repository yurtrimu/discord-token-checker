#include "discord.hpp"

int main()
{
    curl_global_init(CURL_GLOBAL_ALL);

    struct discord_user_data user_data;
    std::vector<struct discord_billing_data> billing_data;

    std::string token = "{ TOKEN HERE }";

    DiscordChecker::Collect(user_data, billing_data, token);

    DiscordChecker::print_discord_user_data(user_data);
    DiscordChecker::print_billing_data(billing_data);

    curl_global_cleanup();
}
