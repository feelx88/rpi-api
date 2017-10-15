#ifndef AUTH_MIDDLEWARE_H
#define AUTH_MIDDLEWARE_H

#include <optional>
#include <memory>
#include <router.hpp>

struct AuthMiddlewareImpl;

class AuthMiddleware
{
public:
  AuthMiddleware();

  std::optional<Pistache::Rest::Route::Result> operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &response);

private:
  std::shared_ptr<AuthMiddlewareImpl> impl;
};

#endif // AUTH_MIDDLEWARE_H
