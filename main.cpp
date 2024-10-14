#include "HttpRequestHandler/HttpRequestHandler.h"

int main() {
    try {
        auto ygoRequestHandler = HttpRequestHandler::HttpRequestHandler("https://db.ygoprodeck.com/api/v7/cardinfo.php");
        auto result = ygoRequestHandler.request();

        std::cout << "HTTP Response: " << std::endl << std::endl << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
