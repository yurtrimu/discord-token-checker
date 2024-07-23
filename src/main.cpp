#include "discord.hpp"

int main()
{
    curl_global_init(CURL_GLOBAL_ALL);

    struct discord_user_data user_data;
    std::vector<struct discord_billing_data> billing_data;
    std::vector<struct discord_connection_data> connection_data;
    std::vector<struct discord_gift_data> gift_data;

    std::string discord_token = "{ PASTE YOUR TOKEN }";

    DiscordChecker::Collect(user_data, billing_data, connection_data, gift_data, discord_token);

    DiscordChecker::print_user_data(user_data);
    DiscordChecker::print_billing_data(billing_data);
    DiscordChecker::print_gift_data(gift_data);
    DiscordChecker::print_connection_data(connection_data);

    curl_global_cleanup();
}
