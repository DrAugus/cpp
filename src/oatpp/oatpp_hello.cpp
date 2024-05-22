#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp_handler.h"

void run()
{
    // 为 HTTP 请求创建路由器
    auto router = oatpp::web::server::HttpRouter::createShared();

    // 路由 GET - "/hello" 请求到处理程序
    router->route("GET", "/hello", std::make_shared<Handler>());

    // 创建 HTTP 连接处理程序
    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

    // 创建 TCP 连接提供者
    auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", 8000, oatpp::network::Address::IP_4});

    // 创建服务器，它接受提供的 TCP 连接并将其传递给 HTTP 连接处理程序
    oatpp::network::Server server(connectionProvider, connectionHandler);

    // 打印服务器端口
    OATPP_LOGi("AUGUS OATPP: ", "Server running on port {}", connectionProvider->getAddress().port);

    // 运行服务器
    server.run();
}

int main()
{
    // 初始化 oatpp 环境
    oatpp::Environment::init();

    // 运行应用
    run();

    // 销毁 oatpp 环境
    oatpp::Environment::destroy();

    return 0;
}
