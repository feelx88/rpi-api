#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include <string>
#include <memory>
#include <optional>

struct AuthServiceImpl;

class AuthService
{
private:
  AuthService();

public:
  static std::shared_ptr<AuthService> getInstance();

  bool isAuthenticated(std::string token);

  std::optional<std::string> authenticate(std::string userName, std::string password);

private:
  static std::shared_ptr<AuthService> instance;
  std::shared_ptr<AuthServiceImpl> impl;
};

#endif // AUTH_SERVICE_H
