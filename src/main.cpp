#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/endpoint.h>
#include <pistache/router.h>

#include <handler/auth.hpp>

int main(int, char**)
{
  using namespace Pistache;

  Rest::Router router;

  AuthHandler authHandler;
  authHandler.initRoutes(&router);

  Address addr(Ipv4::any(), Port(9080));

  auto opts = Http::Endpoint::options().threads(1);
  opts.flags(Tcp::Options::ReuseAddr);
  Http::Endpoint server(addr);
  server.init(opts);
  server.setHandler(router.handler());
  server.serve();
}
