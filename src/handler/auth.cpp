#include <handler/auth.hpp>

#include <iostream>
#include <json.hpp>

#include <service/auth.hpp>

using namespace nlohmann;
using namespace Pistache;
using namespace boost;

struct AuthHandlerImpl
{
  Http::Mime::MediaType jsonMimeType = Http::Mime::MediaType(
    Http::Mime::Type::Application,
    Http::Mime::Subtype::Json
  );

  std::shared_ptr<AuthService> authService = AuthService::getInstance();
};

AuthHandler::AuthHandler()
  : impl(new AuthHandlerImpl)
{
}

ROUTE_GET_IMPL(AuthHandler, status)
{
  bool success = impl->authService->isAuthenticated(request.cookies().get("token").value);
  response.send(success ? Http::Code::Ok : Http::Code::Unauthorized, json{
    {"success", success}
  }.dump(), impl->jsonMimeType);
  return success ? Rest::Route::Result::Ok : Rest::Route::Result::Failure;
}

ROUTE_POST_IMPL(AuthHandler, login)
{
  json body(json::parse(request.body()));

  std::optional<std::string> token = impl->authService->authenticate(body["username"], body["password"]);
  bool success = token.has_value();
  Http::Code returnCode = success ? Http::Code::Ok : Http::Code::Forbidden;

  response.cookies().add(Http::Cookie("token", token.value_or("")));

  response.send(returnCode, json{
    {"succes", success}
  }.dump(), impl->jsonMimeType);

  return Rest::Route::Result::Ok;
}

ROUTE_POST_IMPL(AuthHandler, logout)
{
  response.cookies().add(Http::Cookie("token", ""));

  response.send(Http::Code::Ok, json{
    {"succes", true}
  }.dump(), impl->jsonMimeType);

  return Rest::Route::Result::Ok;
}
