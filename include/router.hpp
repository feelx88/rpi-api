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
  private: \
    const std::string methodName ## _path = path; \
    void register_ ## methodName(Pistache::Rest::Router* router) \
    { \
      Pistache::Rest::Routes::Post(*router, methodName ## _path, std::bind(&decltype(std::remove_pointer<decltype(this)>::type())::methodName, this, std::placeholders::_1, std::placeholders::_2)); \
    } \
    bool add_ ## methodName ## _route() \
    { \
      routes.push_back([this](Pistache::Rest::Router* router){register_ ## methodName(router);}); \
      return true; \
    } \
    bool methodName ## _dummy = add_ ## methodName ## _route(); \
  public: \
    Pistache::Rest::Route::Result methodName(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);

#define ROUTE_POST_IMPL(className, methodName) \
  Pistache::Rest::Route::Result className::methodName(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response)

#endif // ROUTER_HPP
