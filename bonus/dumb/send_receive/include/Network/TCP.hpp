#pragma once

#include <string>
#include <iostream>
#include <asio.hpp>
#include <queue>
#include <thread>
#include <memory>

namespace Network
{
    class TCP {
        public:
        TCP(asio::io_context &io_context, const std::string &ip, int port, bool is_sender);
        ~TCP();

        void sendTo(const std::string &message);
        std::string receive();
        bool isConnectionAlive();
        std::string fetchPacket();

        private:
        void startAccept();  // Accepts connections (for receiver mode)
        void startRead();    // Reads data asynchronously (for both sender and receiver)

        asio::io_context &_io_context;
        asio::ip::tcp::socket _socket;
        asio::ip::tcp::acceptor _acceptor;
        bool _is_sender;
        std::queue<std::string> _received_packets;
        std::shared_ptr<std::thread> _server_thread;
    };
}
