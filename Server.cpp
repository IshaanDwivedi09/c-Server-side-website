#include <iostream>
#include <string>
#include <sstream>
#include <map>

// Simple HTTP request and response classes
class HttpRequest
{
public:
    std::string method;
    std::string path;
    std::map<std::string, std::string> headers;
    std::string body;
};

class HttpResponse
{
public:
    int status_code;
    std::map<std::string, std::string> headers;
    std::string body;

    // Convert the response to a string representation
    std::string toString() const
    {
        std::ostringstream oss;
        oss << "HTTP/1.1 " << status_code << " OK\r\n";
        for (const auto &header : headers)
        {
            oss << header.first << ": " << header.second << "\r\n";
        }
        oss << "\r\n"
            << body;
        return oss.str();
    }
};

// Simple web server class
class WebServer
{
public:
    void handleRequest(const HttpRequest &request, HttpResponse &response)
    {
        if (request.method == "GET" && request.path == "/")
        {
            response.status_code = 200;
            response.body = "<h1>Welcome to My Website!</h1>";
        }
        else if (request.method == "GET" && request.path == "/about")
        {
            response.status_code = 200;
            response.body = "<h2>About Us</h2>";
        }
        else if (request.method == "POST" && request.path == "/submit")
        {
            response.status_code = 200;
            response.body = "<h3>Thank you for submitting the form!</h3>";
        }
        else
        {
            response.status_code = 404;
            response.body = "<h3>Page Not Found</h3>";
        }
    }
};

int main()
{
    WebServer server;

    // Simple example of handling multiple requests based on user input
    while (true)
    {
        std::string userInput;
        std::cout << "Enter a command: ";
        std::cin >> userInput;

        HttpRequest request;
        request.method = "GET";

        if (userInput == "/about")
        {
            request.path = "/about";
        }
        else if (userInput == "/submit")
        {
            request.method = "POST";
            request.path = "/submit";
        }
        else
        {
            std::cout << "Invalid command!" << std::endl;
            continue;
        }

        HttpResponse response;
        server.handleRequest(request, response);

        std::cout << response.toString() << std::endl;
    }

    return 0;
}
