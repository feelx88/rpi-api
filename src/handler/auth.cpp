#include <handler/auth.hpp>

#include <iostream>

#include <json.hpp>
#include <jwt/jwt_all.h>

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

  HS256Validator signer("secret!");
  json payload = {{"sub", "subject"}, {"exp", -1}};
  auto token = JWT::Encode(signer, payload);

  response.cookies().add(Http::Cookie("token", token));

  response.send(returnCode, json{
    {"succes", success}
  }.dump(), jsonMimeType);

  return Rest::Route::Result::Ok;
}

ROUTE_POST_IMPL(AuthHandler, logout) {
  response.cookies().add(Http::Cookie("token", ""));

  response.send(Http::Code::Ok, json{
    {"succes", true}
  }.dump(), jsonMimeType);

  return Rest::Route::Result::Ok;
}
