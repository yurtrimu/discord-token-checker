#pragma once

#define CURL_STATICLIB
#include <curl/curl.h>

size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *buffer) {
    buffer->append((char *)contents, size * nmemb);
    return size * nmemb;
}

int curl_get(const std::string &url, const std::vector<std::string> &headers, std::string &response) {
    CURL *curl;
    CURLcode res;
    struct curl_slist *headerlist = NULL;

    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL" << std::endl;
        curl_global_cleanup();
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    for (const auto &header : headers) {
        headerlist = curl_slist_append(headerlist, header.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);

    res = curl_easy_perform(curl);

    curl_slist_free_all(headerlist);

    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }

    curl_easy_cleanup(curl);

    return (res == CURLE_OK);
}