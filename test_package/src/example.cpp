#include "slc-httplib.h"
#include <vector>
#include <string>
#include <format>

int main()
{
  slc_httplib::HttpServerWrapper server;

  long a = 0;
  server.Get("/tget", [&](const slc_httplib::Request &req, slc_httplib::Response &res)
        {
          int retCode = (a++%2)?200:404;
          res=std::format("{{\"hello\": \"world_{}\",\"retCode\":{} }}",a,retCode);
          return retCode; 
        });
  server.Post("/tpost", [&](const slc_httplib::Request &req, slc_httplib::Response &res)
        {
          int retCode = (a++%2)?200:404;
          res=std::format("{{\"hello\": \"world_{}\",\"retCode\":{} }}",a,retCode);
          return retCode; 
        });
  if (!server.startListen(18080))
    return -1;
  return 0;
}
