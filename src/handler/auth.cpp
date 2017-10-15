#include <handler/auth.hpp>

#include <iostream>

#include <json.hpp>
#include <jwt/jwt_all.h>

using namespace nlohmann;
using namespace Pistache;

struct AuthHandlerImpl
{
  std::shared_ptr<HS256Validator> signer =
    std::make_shared<HS256Validator>(boost::uuids::to_string(boost::uuids::random_generator()()));

  Http::Mime::MediaType jsonMimeType = Http::Mime::MediaType(
    Http::Mime::Type::Application,
    Http::Mime::Subtype::Json
  );
};

AuthHandler::AuthHandler()
  : impl(new AuthHandlerImpl)
{
}

ROUTE_GET_IMPL(AuthHandler, status) {
  try {
    JWT::Decode(request.cookies().get("token").value, impl->signer.get());

    response.send(Http::Code::Ok, json{
      {"success", true}
    }.dump(), impl->jsonMimeType);
  } catch (InvalidTokenError &) {
    response.send(Http::Code::Unauthorized, json{
      {"success", false}
    }.dump(), impl->jsonMimeType);
  }
  return Rest::Route::Result::Ok;
}

ROUTE_POST_IMPL(AuthHandler, login)
{
  json body(json::parse(request.body()));

  bool success = body["username"] == "admin" && body["password"] == "admin";
  Http::Code returnCode = success ? Http::Code::Ok : Http::Code::Forbidden;

  json payload = {{"sub", "subject"}, {"exp", -1}};
  auto token = JWT::Encode(*impl->signer, payload);

  response.cookies().add(Http::Cookie("token", token));

  response.send(returnCode, json{
    {"succes", success}
  }.dump(), impl->jsonMimeType);

  return Rest::Route::Result::Ok;
}

ROUTE_POST_IMPL(AuthHandler, logout) {
  response.cookies().add(Http::Cookie("token", ""));

  response.send(Http::Code::Ok, json{
    {"succes", true}
  }.dump(), impl->jsonMimeType);

  return Rest::Route::Result::Ok;
}
