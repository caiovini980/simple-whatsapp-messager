#include <iostream>
#include <cstdlib>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

int main() {
    std::cout << "\n\nSystem initializing...\n";
    std::cout << "Checking CURL...\n";
    
    CURL* curl = curl_easy_init();
    if(!curl) {
        std::cerr << "Curl instance not found!\n";
        return 1;
    }

    std::cout << "Curl instance created!\n";

    std::cout << "Configuring credentials...\n";
    std::string baseUrl = "https://api.green-api.com/waInstance";
    std::string idInstance = std::getenv("ID_INSTANCE"); 
    std::string apiToken = std::getenv("TOKEN");
    std::string fullUrl = baseUrl + idInstance + "/sendMessage/" + apiToken;

    std::string message = std::getenv("MESSAGE");
    std::string senderNumber = std::getenv("SENDER_NUMBER");
    std::string receiverId = senderNumber + "@c.us";

    std::cout << "\n\n[SENDER]: " << senderNumber << "\n";
    std::cout << "[MESSAGE]: " << message << "\n\n\n";

    std::cout << "Making the message body...\n";
    nlohmann::json data;
    data["chatId"] = receiverId;
    data["message"] = message;
    std::string requestBody = data.dump();

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestBody.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    // curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36");
    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); - Only enable if debugging

    std::cout << "Executing the requisition...\n";
    CURLcode res = curl_easy_perform(curl);
    
    if(res != CURLE_OK)
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(res));
    else
        std::cout << "\nMessage sent successfully" << std::endl;

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    return 0;
}
