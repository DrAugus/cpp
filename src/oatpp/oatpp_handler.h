// 默认情况下，Oat++ 会对客户端请求响应 404，除此之外什么都不做。

// 若要添加自定义响应，必须实现 HttpRequestHandler：

// oatpp_handler.h
#ifndef OATPP_HANDLER_H
#define OATPP_HANDLER_H

#include "oatpp/web/server/HttpRequestHandler.hpp"

#define O_UNUSED(x) (void)x;

// 自定义请求处理程序
class Handler : public oatpp::web::server::HttpRequestHandler {
 public:
  // 处理传入的请求，并返回响应
  std::shared_ptr<OutgoingResponse> handle(
      const std::shared_ptr<IncomingRequest>& request) override {
    O_UNUSED(request);

    return ResponseFactory::createResponse(Status::CODE_200, "Hello, World!");
  }
};

#endif  // OATPP_HANDLER_H
