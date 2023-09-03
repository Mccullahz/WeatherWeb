#include <iostream>
#include <string>
#include <curl/curl.h> // libcurl4-gnutls-dev package

// Ensure that your API key is correct and has the necessary permissions
const std::string API_KEY = "dae73f060544e37ba56e18d7edc507cd";
const std::string API_URL = "http://api.openweathermap.org/data/2.5/weather?q=";

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    std::string city;
    std::cout << "Enter city name: ";
    std::cin >> city;

    if (city.empty()) {
        std::cerr << "City name cannot be empty." << std::endl;
        return 1; // Return an error code
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize libcurl." << std::endl;
        return 1;
    }

    std::string fullUrl = API_URL + city + "&appid=" + API_KEY;
    CURLcode res;
    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Failed to fetch weather data: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        return 1;
    }

    long response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    if (response_code != 200) {
        std::cerr << "HTTP error code: " << response_code << std::endl;
        if (response_code == 401) {
            std::cerr << "Unauthorized - Your API key may be incorrect or lack the necessary permissions." << std::endl;
        }
        curl_easy_cleanup(curl);
        return 1;
    }

    curl_easy_cleanup(curl);

    // Parse and display the weather data (you can use a JSON library for this)
    std::cout << "Weather Data for " << city << ":\n" << response << std::endl;

    return 0;
}
