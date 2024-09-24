#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include <string>
#include <memory.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <random>
#include <atomic>
#include <csignal>
#include <unordered_map>

#define BUFFER_SIZE 50


std::pair<std::string, sockaddr_in> GetMessage(int socket)
{
    sockaddr_in clientAddress;
    // int length = 50;
    int clientAddressLen = sizeof(clientAddress);

    std::string msg(BUFFER_SIZE, ' ');
    auto messageSize = recvfrom(socket, &msg[0], BUFFER_SIZE, 0,
                                reinterpret_cast<sockaddr *>(&clientAddress), reinterpret_cast<socklen_t *>(&clientAddressLen));
    if (messageSize <= 0)
        return {};

    return {msg, clientAddress};
}

void ConfirmReceiving(int socket, const sockaddr_in &clientAddress, std::string msg)
{
    // if (sendto(socket, &ConfirmationMessage[0], ConfirmationMessage.size(), 0,
    if (sendto(socket, &msg[0], msg.size(), 0,
               reinterpret_cast<const sockaddr *>(&clientAddress), sizeof(clientAddress)) < 0)
    {
        std::cout << "Проблемы с sendto.\n";
        return;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Server <NumberOfLostPackage>\n";
        return 1;
    }

    int sockMain;
    if (sockMain = socket(AF_INET, SOCK_DGRAM, 0); sockMain < 0)
    {
        std::cout << "Сервер не может открыть socket для UDP.\n";
        return 1;
    }

    sockaddr_in servAddr;
    memset(static_cast<void *>(&servAddr), 0, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = 0;

    if (bind(sockMain, reinterpret_cast<const sockaddr *>(&servAddr), sizeof(servAddr)) != 0)
    {
        std::cout << "Связывание сервера неудачно.\n";
        return 1;
    }

    int length = sizeof(servAddr);
    if (getsockname(sockMain, reinterpret_cast<sockaddr *>(&servAddr),
                    reinterpret_cast<socklen_t *>(&length)) != 0)
    {
        std::cout << "Вызов getsockname неудачен.\n";
        return 1;
    }

    std::cout << "SERVER: номер порта: " << ntohs(servAddr.sin_port) << std::endl;

    int i = 0;
    while (true)
    {
        i++;
        auto [msg, clientAddr] = GetMessage(sockMain);

        if (msg.size() == 0)
            continue;

        if (i % std::atoi(argv[1]) == 0)
        {
            // std::cout << "Потеря данных от клиента\nIP-адрес: " << inet_ntoa(clientAddr.sin_addr) << " || порт: " << ntohs(clientAddr.sin_port) << "\n\n";
            continue;
        }

        std::cout << "Получение данных от клиента\nIP-адрес: " << inet_ntoa(clientAddr.sin_addr) << " || порт: " << ntohs(clientAddr.sin_port) << "\n";
        std::cout << "Полученный символ: " << msg << "\n\n";

        ConfirmReceiving(sockMain, clientAddr, msg);

    }

    return 0;
}
