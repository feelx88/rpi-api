#ifndef AUTHHANDLER_H
#define AUTHHANDLER_H

#include <router.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

class AuthHandler
{
  ROUTE_INIT
public:
  AuthHandler() = default;

  ROUTE_GET("/status", status)

  ROUTE_POST("/login", login)
  ROUTE_POST("/logout", logout)

private:
  boost::uuids::random_generator uuidgen;
  std::string secret = boost::uuids::to_string(uuidgen());
};

#endif // AUTHHANDLER_H
