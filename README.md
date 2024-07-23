# 🟩 Discord Token Checker 🟩 <a href="https://github.com/yurtrimu/discord-token-checker/actions/workflows/main.yml"><img src="https://github.com/yurtrimu/discord-token-checker/actions/workflows/main.yml/badge.svg" alt="Working"></a>

## **Discord Token Checker project is for getting the user & billing information.**

# Questions?
### - **I gladly answer your questions on the [discord server](https://discord.gg/QBhFd2aK4r).**

## Usage

```c++
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
```

## Example.png
![alt text](https://github.com/yurtrimu/discord-token-checker/blob/main/Example.png?raw=true)

## Operating System
- **Below Windows 7 - 🟦 Untested**
- **Windows 7 - 🟦 Untested**
- **Windows 10 - 🟩 Working**
- **Windows 11 - 🟦 Untested**
- **Mac OS - 🟦 Untested**
- **Linux - 🟦 Untested**

## Requirements

**You need to have the OpenSSL library installed and linked to your compiler.**

- You could download the OpenSSL library from [OpenSSL website](https://www.openssl.org/source/).

**You need to have the CURL library installed and linked to your compiler ( _ STATIC _).**

- You could download the CURL library from [CURL website](https://curl.se/download.html).

## Linker

- **libcrypto.lib**
- **libssl.lib**
- **openssl.lib**
- **libcurl_a.lib**
- **crypt32.lib**
- **ws2_32.lib**
- **wldap32.lib**
- **normaliz.lib**

## Compiling

- **Build - 🟦 Untested**
- **Release - 🟩 Working**
- **C++11  - 🟦 Untested**
- **C++14  - 🟩 Working**
- **C++17 - 🟩 Working**
- **C++20 - 🟩 Working**

## Contributing

**Pull requests are welcome.**

## Legal Disclaimer
🟥 **The content provided is for educational and informational purposes only.** 🟥
