
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <curl/curl.h>
#include <cstring>

using namespace std;

// 此代码使用socket API发出HTTP GET请求，并输出服务器响应。
int use_socket()
{
    // 设置要访问的URL和端口号
    char server_address[] = "www.example.com";
    int port_number = 80;

    struct sockaddr_in server;
    int sock;

    // 创建socket
    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        perror("Socket creation failed");
        return 1;
    }

    // 获取服务器地址信息
    struct hostent *host;
    if ((host = gethostbyname(server_address)) == NULL)
    {
        perror("Host resolution failed");
        return 1;
    }

    // 配置服务器地址sin_family、sin_port和sin_addr字段
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port_number);
    server.sin_addr.s_addr = *((unsigned long *)host->h_addr);

    // 连接服务器
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Connection failed");
        return 1;
    }

    // 构造HTTP GET请求
    const char *request = "GET / HTTP/1.1\r\n"
                          "Host: www.example.com\r\n"
                          "Connection: close\r\n\r\n";

    // 发送HTTP请求
    if (send(sock, request, strlen(request), 0) < 0)
    {
        perror("Send failed");
        return 1;
    }

    // 接收服务器响应
    char response_buffer[4096];
    int response_length;
    while ((response_length = recv(sock, response_buffer, 4096, 0)) > 0)
    {
        // 输出服务器响应内容
        fwrite(response_buffer, sizeof(char), response_length, stdout);
    }

    // 关闭socket
    close(sock);
    return 0;
}

// 内存回调函数，将HTTP响应内容保存至字符串指针response中
static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    string *response = (string *)userdata;
    response->append(ptr, size * nmemb);
    return size * nmemb;
}

// 此代码使用libcurl库发出HTTP请求，将响应内容保存至字符串中，并输出该字符串。
// 相较于基本的socket代码，使用第三方库能够更方便地使用更多高级的HTTP功能，
// 如认证、重定向和多线程操作等。
int use_curl()
{
    CURL *curl;
    CURLcode res;
    string response;

    // 初始化libcurl
    curl = curl_easy_init();
    if (curl == NULL)
    {
        perror("Curl initialization failed");
        return 1;
    }

    // 设置要访问的URL
    curl_easy_setopt(curl, CURLOPT_URL, "http://www.example.com");

    // 指定回调函数以及响应内容保存的字符串指针
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // 发送HTTP请求
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        perror("Curl perform failed");
        return 1;
    }

    // 输出HTTP响应内容
    cout << response << endl;

    // 清理libcurl资源
    curl_easy_cleanup(curl);
    return 0;
}

int main()
{
    std::cout << "use socket get http" << std::endl;
    use_socket();
    std::cout << "use curl get http" << std::endl;
    use_curl();
    return 0;
}
