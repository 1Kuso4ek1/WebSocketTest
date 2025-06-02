#include <Controllers/WSController.hpp>

Json::Value parseJson(const std::string& data)
{
    Json::Value root;
    std::string errors;

    const auto reader = Json::CharReaderBuilder().newCharReader();

    if(!reader->parse(data.c_str(), data.c_str() + data.size(), &root, &errors))
        return { errors };

    return root;
}

void WSController::handleNewMessage(
    const WebSocketConnectionPtr& connection,
    std::string&& message,
    const WebSocketMessageType& messageType
)
{
    if(messageType != WebSocketMessageType::Ping)
        connection->sendJson(parseJson(message));
}

void WSController::handleNewConnection(const HttpRequestPtr& req, const WebSocketConnectionPtr& connection)
{

}

void WSController::handleConnectionClosed(const WebSocketConnectionPtr& connection)
{
}
