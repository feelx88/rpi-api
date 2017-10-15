#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <functional>

#include <pistache/http.h>
#include <pistache/router.h>

#define ROUTE_INIT \
  private: \
    std::vector<std::function<void(Pistache::Rest::Router* router)>> routes; \
  public: \
    void initRoutes(Pistache::Rest::Router* router){ \
      for (auto route: routes) { \
        route(router); \
      } \
    }

#define ROUTE_POST(path, methodName) \
  ROUTE_INTERNAL(Post, path, methodName)

#define ROUTE_GET(path, methodName) \
  ROUTE_INTERNAL(Get, path, methodName)

#define ROUTE_INTERNAL(impl, path, methodName) \
  private: \
    const std::string methodName ## _path = path; \
    void register_ ## impl ## methodName(Pistache::Rest::Router* router) \
    { \
      Pistache::Rest::Routes::impl(*router, methodName ## _path, std::bind(&decltype(std::remove_pointer<decltype(this)>::type())::impl ## methodName, this, std::placeholders::_1, std::placeholders::_2)); \
    } \
    bool add_ ## impl ## methodName ## _route() \
    { \
      routes.push_back([this](Pistache::Rest::Router* router){register_ ## impl ## methodName(router);}); \
      return true; \
    } \
    bool impl ## methodName ## _dummy = add_ ## impl ## methodName ## _route(); \
  public: \
    Pistache::Rest::Route::Result impl ## methodName(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);

#define ROUTE_IMPL_INTERNAL(impl, className, methodName) \
  Pistache::Rest::Route::Result className::impl ## methodName(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response)

#define ROUTE_POST_IMPL(className, methodName) \
  ROUTE_IMPL_INTERNAL(Post, className, methodName)

#define ROUTE_GET_IMPL(className, methodName) \
  ROUTE_IMPL_INTERNAL(Get, className, methodName)

#define MIDDLEWARE(middleware) \
  std::optional<Pistache::Rest::Route::Result> res = middleware(request, response); \
  if(res.has_value()) {\
    return res.value();\
  }

#endif // ROUTER_HPP
