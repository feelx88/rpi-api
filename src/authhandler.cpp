#include <authhandler.hpp>

#include <iostream>

using namespace nlohmann;
using namespace Pistache;

static Http::Mime::MediaType jsonMimeType = Http::Mime::MediaType(
  Http::Mime::Type::Application,
  Http::Mime::Subtype::Json
);

Pistache::Rest::Route::Result AuthHandler::login(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response)
{
  json body(json::parse(request.body()));

  bool success = body["username"] == "admin" && body["password"] == "admin";
  Http::Code returnCode = success ? Http::Code::Ok : Http::Code::Forbidden;

  response.send(returnCode, json{
    {"succes", success}
  }.dump(), jsonMimeType);

  return Rest::Route::Result::Ok;
}
