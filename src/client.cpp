#include <drogon/HttpAppFramework.h>
#include <drogon/WebSocketClient.h>

#include <iostream>
#include <print>
#include <string>

using namespace drogon;
using namespace std::chrono_literals;

int main()
{
    const auto client = WebSocketClient::newWebSocketClient("ws://127.0.0.1:8080");
    const auto req = HttpRequest::newHttpRequest();

    req->setPath("/echo");

    client->setMessageHandler([](auto&& message, const auto& wsClient, const auto& type)
    {
        using enum WebSocketMessageType;

        switch(type)
        {
        case Pong: break;
        default: std::println("Message: {}", message);
        }
    });

    client->setConnectionClosedHandler([](const auto& wsClient)
    {
        std::println("Connection closed");
    });

    client->connectToServer(req, [](auto result, const auto& resp, const auto& wsClient)
    {
        if(result != ReqResult::Ok)
        {
            std::println("Connection failed");
            wsClient->stop();
            return;
        }

        std::println("Connected");

        wsClient->getConnection()->setPingMessage("Ping", 10s);
        wsClient->getConnection()->send("{ \"message\" : \"Hello world!\" }");
    });

    app().run();
}
