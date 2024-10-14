#include "HttpRequestHandler/HttpRequestHandler.h"
#include "json/json.h"

using namespace HttpRequestHandler;

int main() {
    Json::Value jsonData;
    Json::Reader jsonReader;
    auto  ygoRequestHandler = new CHttpRequestHandler("https://db.ygoprodeck.com/api/v7/cardinfo.php");
    std::string result = std::string("");

    std::cout << "1223" << std::endl;

    try {
        result = ygoRequestHandler->Request();

        std::cout << "HTTP Response: " << std::endl << std::endl << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    // if (jsonReader.parse(result, jsonData))

    return 0;
}
