#ifndef AUTH_HANDLER_H
#define AUTH_HANDLER_H

#include <memory>

#include <router.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

struct AuthHandlerImpl;

class AuthHandler
{
  ROUTE_INIT
public:
  AuthHandler();

  ROUTE_GET("/auth/status", status)

  ROUTE_POST("/auth/login", login)
  ROUTE_POST("/auth/logout", logout)

private:
  std::shared_ptr<AuthHandlerImpl> impl;
};

#endif // AUTH_HANDLER_H
