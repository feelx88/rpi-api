#include <functional>

#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/endpoint.h>
#include <pistache/router.h>

#include <authhandler.hpp>

#define POST(path, object, member) \
  Pistache::Rest::Routes::Post( \
    router, \
    path, \
    std::bind(&decltype(object)::member, &object, std::placeholders::_1, std::placeholders::_2) \
  );

int main(int, char**)
{
  using namespace Pistache;

  Rest::Router router;

  AuthHandler authHandler;
  POST("/login", authHandler, login);

  Address addr(Ipv4::any(), Port(9080));

  auto opts = Http::Endpoint::options().threads(1);
  opts.flags(Tcp::Options::ReuseAddr);
  Http::Endpoint server(addr);
  server.init(opts);
  server.setHandler(router.handler());
  server.serve();
}
