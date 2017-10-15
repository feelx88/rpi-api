#include <service/auth.hpp>

#include <jwt/jwt_all.h>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>

using namespace boost;

struct AuthServiceImpl
{
  std::shared_ptr<MessageSigner> signer =
    std::make_shared<HS256Validator>(uuids::to_string(uuids::random_generator()()));
};

std::shared_ptr<AuthService> AuthService::instance;

AuthService::AuthService()
  : impl(new AuthServiceImpl)
{
}

std::shared_ptr<AuthService> AuthService::getInstance()
{
  if (!instance) {
    instance.reset(new AuthService);
  }
  return instance;
}

bool AuthService::isAuthenticated(std::string token)
{
  try {
    JWT::Decode(token, impl->signer.get());
    return true;
  } catch (InvalidTokenError &) {
    return false;
  }
}

std::optional<std::string> AuthService::authenticate(std::string username, std::string password)
{
  if(username == "admin" && password == "admin")
  {
    json payload = {
      {"sub", "rpi-api"},
      {"exp", -1},
      {"username", username}
    };
    auto token = JWT::Encode(*impl->signer, payload);

    return token;
  }
  else
  {
    return {};
  }
}
