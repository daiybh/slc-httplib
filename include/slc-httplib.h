#pragma once
#include <string>
#include <functional>
#include <map>
namespace httplib{
	
	class Server;
}
namespace slc_httplib
{
	using Request = std::string;
	using Response = std::string;
	class HttpServerWrapper
	{
	public:
		HttpServerWrapper();

		static void makeString(const char* pattern, const char* Method, std::string& result)
		{
			result += R"(<li> <button onclick="return UserAction( ')" + std::string(pattern) + R"(' ); ">..</button>)" + std::string(Method) + " --->    <a href = '" + std::string(pattern) + "'> " + std::string(pattern) + "</a></li>";
		}

		HttpServerWrapper(const std::string& moduleName, int httpPort = 0, int webSocketPort = 0);

#define MAKESTRING makeString(pattern,__FUNCTION__,m_httpHTML);

  	using Handler = std::function<int(const Request &, Response &)>;

		HttpServerWrapper& Get(const char* pattern, Handler handler);
		

		HttpServerWrapper& Post(const char* pattern, Handler handler);

		std::string& getHttpHtml()
		{
			return m_httpHTML;
		}
		bool startListen(int _httpPort = 0, int _webSocketPort = 0);

	private:
		httplib::Server* m_server = nullptr;
		
  using Handlers =
      std::map< std::string, Handler>;
	Handlers get_handlers_;
	Handlers post_handlers_;
		std::string m_getModuleInfo;
		std::string m_httpHTML = R"(<script>
function UserAction(url) {
console.log(url);
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {           
			 document.getElementById('result').innerHTML=this.responseText;         
		}
	};
    xhttp.open("GET",url);    
    xhttp.send();
}

window.onload = (event)=>{
	var childNode = document.createElement('p');
childNode.setAttribute('id',"result");
document.getElementsByTagName('body')[0].appendChild(childNode);
};
</script>
)";
	};
};
