#ifndef AUTHHANDLER_H
#define AUTHHANDLER_H

#include <router.hpp>

class AuthHandler
{
  ROUTE_INIT
public:
  AuthHandler() = default;

  ROUTE_GET("/status", status)

  ROUTE_POST("/login", login)
  ROUTE_POST("/logout", logout)
};

#endif // AUTHHANDLER_H
