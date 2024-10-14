#include "HttpRequestHandler/HttpRequestHandler.h"
#include "json/json.h"

using namespace HttpRequestHandler;

int main() {
    Json::Value jsonData;
    Json::Reader jsonReader;
    auto  ygoRequestHandler = new CHttpRequestHandler("https://db.ygoprodeck.com/api/v7/cardinfo.php");
    std::string result = std::string("");

    try {
        result = ygoRequestHandler->Request();

        std::cout << "HTTP Request successful!" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    if (jsonReader.parse(result, jsonData)) {
        // std::cout << jsonData.toStyledString() << std::endl;
        std::cout << jsonData["data"].size() << std::endl;
        std::cout << jsonData["data"][0].toStyledString();
    }

    return 0;
}
