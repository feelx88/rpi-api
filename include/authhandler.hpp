#ifndef AUTHHANDLER_H
#define AUTHHANDLER_H

#include <json.hpp>
#include <pistache/http.h>
#include <pistache/router.h>

class AuthHandler
{
public:
  AuthHandler() = default;

  Pistache::Rest::Route::Result login(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
};

#endif // AUTHHANDLER_H
