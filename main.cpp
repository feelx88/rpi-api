#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/endpoint.h>
#include <pistache/router.h>

int main(int argc, char** argv)
{
  using namespace Pistache;

  Rest::Router router;
  Http::Mime::MediaType jsonMimeType = Http::Mime::MediaType(
        Http::Mime::Type::Application,
        Http::Mime::Subtype::Json
        );

  Rest::Routes::Get(router, "test/:ppp", [jsonMimeType](
                    const Rest::Request &request,
                    Http::ResponseWriter response) -> Rest::Route::Result {
    if (request.param(":ppp").as<std::string>() == "moep")
    {
      response.send(Http::Code::Ok, "moep", jsonMimeType);
      return Rest::Route::Result::Ok;
    }
    else
    {
      response.send(Http::Code::Bad_Request, "not moep!", jsonMimeType);
      return Rest::Route::Result::Failure;
    }
  });

  Address addr(Ipv4::any(), Port(9080));

  auto opts = Http::Endpoint::options().threads(1);
  opts.flags(Tcp::Options::ReuseAddr);
  Http::Endpoint server(addr);
  server.init(opts);
  server.setHandler(router.handler());
  server.serve();
}
