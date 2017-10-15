#include <middleware/auth.hpp>

#include <json.hpp>

#include <service/auth.hpp>

using namespace Pistache;
using namespace nlohmann;

struct AuthMiddlewareImpl
{
  std::shared_ptr<AuthService> authService = AuthService::getInstance();

  Http::Mime::MediaType jsonMimeType = Http::Mime::MediaType(
    Http::Mime::Type::Application,
    Http::Mime::Subtype::Json
  );
};

AuthMiddleware::AuthMiddleware()
  : impl(new AuthMiddlewareImpl)
{
}

std::optional<Rest::Route::Result> AuthMiddleware::operator()(const Rest::Request &request, Http::ResponseWriter &response)
{
  if(!impl->authService->isAuthenticated(request.cookies().get("token").value))
  {
    response.send(Http::Code::Unauthorized, json{
      {"success", false}
    }.dump(), impl->jsonMimeType);

    return Rest::Route::Result::Failure;
  }
  return std::nullopt;
}
