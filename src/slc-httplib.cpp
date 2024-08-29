
#include "httplib.h"
#include <iostream>
#include "slc-httplib.h"
namespace slc_httplib
{
    HttpServerWrapper::HttpServerWrapper():HttpServerWrapper("unknown") 
    {


    };
    bool HttpServerWrapper::startListen(int _httpPort , int _webSocketPort)
    {
        return m_server->listen("0.0.0.0",_httpPort);
    }
    HttpServerWrapper::HttpServerWrapper(const std::string &moduleName, int httpPort, int webSocketPort )
    {
        m_server = new httplib::Server();

        m_server->Get("/", [&](const httplib::Request &req, httplib::Response &res)
                      {
					                     res.set_header("Access-Control-Allow-Origin", "*");
					                     res.set_content(getHttpHtml(), "text/html"); });

        if (httpPort != 0 && webSocketPort != 0)
        {
            char buff[1025];
            sprintf_s(buff, R"({"moduleName":"%s","httpPort":%d,"webSocketPort":%d })", moduleName.c_str(), httpPort, webSocketPort);
            m_getModuleInfo = buff;

            m_server->Get("/getModuleInfo", [&](const httplib::Request &req, httplib::Response &res)
                          {
						          res.set_header("Access-Control-Allow-Origin", "*");
						          res.set_content(m_getModuleInfo, "text/json"); });
        }
    }
    HttpServerWrapper &HttpServerWrapper::Get(const char *pattern, HttpServerWrapper::Handler handler)
    {
        MAKESTRING;
        get_handlers_.emplace(pattern, std::move(handler));
        m_server->Get(pattern,[&](const httplib::Request &req, httplib::Response &res){
            res.status = get_handlers_[req.path](req.body, res.body);
            res.set_content(res.body, "text/json");
        });
        
        return *this;
    }

    HttpServerWrapper &HttpServerWrapper::Post(const char *pattern, HttpServerWrapper::Handler handler)
    {
        MAKESTRING;
        post_handlers_.emplace(pattern, std::move(handler));
         m_server->Post(pattern,[&](const httplib::Request &req, httplib::Response &res){
            res.status =post_handlers_[req.path](req.body, res.body);
             
            res.set_content(res.body, "text/json");
        });
        return *this;
    }

}