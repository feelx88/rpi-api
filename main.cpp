#include <pistache/http.h>
#include <pistache/net.h>
#include <pistache/endpoint.h>
#include <pistache/router.h>

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>

int main(int, char**)
{
  using namespace Pistache;

  Rest::Router router;
  Http::Mime::MediaType jsonMimeType = Http::Mime::MediaType(
        Http::Mime::Type::Application,
        Http::Mime::Subtype::Json
        );

  Rest::Routes::Get(router, "test/:arg", [jsonMimeType](
                    const Rest::Request &request,
                    Http::ResponseWriter response) -> Rest::Route::Result {

    bool success = (request.param(":arg").as<std::string>() == "moep");
    std::vector<int> values = (!success) ? std::vector<int>{} : std::vector<int>{
      1,
      42,
      17
    };


    auto jsonValues = bsoncxx::builder::stream::array{};

    for (int val : values) {
        jsonValues << val;
    }

    auto json = bsoncxx::builder::stream::document{} <<
      "success" << success <<
      "result" << jsonValues <<
      bsoncxx::builder::stream::finalize;

    response.send(Http::Code::Ok, bsoncxx::to_json(json.view()), jsonMimeType);
    return Rest::Route::Result::Ok;
  });

  Address addr(Ipv4::any(), Port(9080));

  auto opts = Http::Endpoint::options().threads(1);
  opts.flags(Tcp::Options::ReuseAddr);
  Http::Endpoint server(addr);
  server.init(opts);
  server.setHandler(router.handler());
  server.serve();
}
