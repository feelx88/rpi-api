#include <authhandler.hpp>

#include <iostream>

#include <json.hpp>

using namespace nlohmann;
using namespace Pistache;

static Http::Mime::MediaType jsonMimeType = Http::Mime::MediaType(
  Http::Mime::Type::Application,
  Http::Mime::Subtype::Json
);

ROUTE_POST_IMPL(AuthHandler, login)
{
  json body(json::parse(request.body()));

  bool success = body["username"] == "admin" && body["password"] == "admin";
  Http::Code returnCode = success ? Http::Code::Ok : Http::Code::Forbidden;

  response.send(returnCode, json{
    {"succes", success}
  }.dump(), jsonMimeType);

  return Rest::Route::Result::Ok;
}

ROUTE_POST_IMPL(AuthHandler, logout) {
  response.send(Http::Code::Ok, json{
    {"succes", true}
  }.dump(), jsonMimeType);

  return Rest::Route::Result::Ok;
}
