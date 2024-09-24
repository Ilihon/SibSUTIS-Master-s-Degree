#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <vector>
#include <memory.h>
#include <fstream>
#include <filesystem>
#include <thread>
#include <sstream>

constexpr timeval RecvTimeout{1, 0};
std::string msg = "POSTAVTE ZACHET";

void SendDataToServerWithConfirmation(int socket, std::string &GetMsg, const sockaddr_in &serverAddress)
{
    std::cout << '\n';
    while (true)
    {
        std::cout << "Отправляемый символ: " << "|"<< GetMsg << "|\n";
        if (sendto(socket, &GetMsg.front(), GetMsg.size(), 0,
                   reinterpret_cast<const sockaddr *>(&serverAddress), sizeof(serverAddress)) < 0)
        {
            std::cout << "Проблемы с sendto.\n";
            return;
        }

        std::vector<char> buffer(2);
        socklen_t length = sizeof(serverAddress);

        ssize_t msgLength = recvfrom(socket, &buffer.front(), buffer.size(), 0, (sockaddr *)&serverAddress, &length);

        // ////////////
        // for (int i = 0; i < msg.size(); ++i)
        // {
        //     std::string submsg = msg.substr(i, 1);
        //     std::string s = std::string(buffer.begin(), buffer.end());
        //     std::cout << "Сообщение принято. Сообщение: " << s << std::endl;
        //     break;
        // }
        // ////////////

        //if (msgLength > 0 && std::string(buffer.begin(), std::next(buffer.begin() + msgLength - 1)) == "ok")

        std::string s = std::string(buffer.begin(), buffer.end()).substr(0,1);
        if(msgLength > 0) // && s == GetMsg)
        {
            std::cout << "Принятый символ: " << "|" << s << "|" << std::endl;
            break;
        }
        else{
            std::cout << "Пакет не дошёл до сервера, повторная отправка" << '\n';
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cout << "Client: sleepTime; hostName; port \n";
        return 1;
    }

    int sock;
    if (sock = socket(AF_INET, SOCK_DGRAM, 0); sock < 0)
    {
        std::cout << "Клиент не может открыть socket для UDP.\n";
        return 1;
    }

    sockaddr_in servAddr;
    memset(static_cast<void *>(&servAddr), 0, sizeof(servAddr));

    auto *hostName = gethostbyname(argv[2]);
    memcpy(hostName->h_addr, &servAddr.sin_addr, hostName->h_length);
    servAddr.sin_port = htons(std::atoi(argv[3]));

    sockaddr_in clientAddr;
    memset(static_cast<void *>(&clientAddr), 0, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    clientAddr.sin_port = 0;

    if (bind(sock, reinterpret_cast<const sockaddr *>(&clientAddr), sizeof(clientAddr)) != 0)
    {
        std::cout << "Связывание клиента неудачно.\n";
        return 1;
    }

    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &RecvTimeout, sizeof(RecvTimeout)) != 0)
    {
        std::cout << "Установка timeout для recv неудачна.\n";
        return 1;
    }

    const std::chrono::seconds delay(std::atoi(argv[1]));

    //std::string msg = "Hello";
    std::cout << "Сообщение: " << msg << std::endl;
    // for (int i = 0; i < n; ++i)
    // {
    //     SendDataToServerWithConfirmation(sock, submsg1, servAddr);
    //     std::this_thread::sleep_for(delay);
    // }

    for (int i = 0; i < msg.size(); ++i)
    {

        std::string submsg = msg.substr(i, 1);
        SendDataToServerWithConfirmation(sock, submsg, servAddr);
        std::this_thread::sleep_for(delay);
    }

    return 0;
}
