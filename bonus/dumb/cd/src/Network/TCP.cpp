#include "Network/TCP.hpp"

namespace Network
{
    TCP::TCP(asio::io_context &io_context, const std::string &ip, int port, bool is_sender)
        : _io_context(io_context), _socket(io_context), _acceptor(io_context), _is_sender(is_sender)
    {
        if (is_sender) {
            // Client (Sender Mode) connects
            asio::ip::tcp::endpoint endpoint(asio::ip::make_address(ip), port);
            _socket.connect(endpoint);
            startRead(); // Start reading responses from the receiver
        } else {
            // Server (Receiver Mode)
            asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);
            _acceptor.open(asio::ip::tcp::v4());
            _acceptor.set_option(asio::socket_base::reuse_address(true));
            _acceptor.bind(endpoint);
            _acceptor.listen();

            // Accept connections in a separate thread
            _server_thread = std::make_shared<std::thread>([this]() { startAccept(); });
        }
    }

    TCP::~TCP()
    {
        if (!_is_sender && _server_thread && _server_thread->joinable()) {
            _server_thread->join();
        }
        _socket.close();
        _acceptor.close();
    }

    void TCP::sendTo(const std::string &message)
    {
        if (_socket.is_open()) {
            asio::write(_socket, asio::buffer(message));
        }
    }

    void TCP::startAccept()
    {
        _acceptor.async_accept([this](std::error_code ec, asio::ip::tcp::socket new_socket)
            {
                if (!ec) {
                    _socket = std::move(new_socket);
                    startRead(); // Start reading messages after connection is established
                }
            });

        _io_context.run();
    }

    void TCP::startRead()
    {
        auto buffer = std::make_shared<std::vector<char>>(1024);
        _socket.async_read_some(asio::buffer(*buffer),
            [this, buffer](std::error_code ec, std::size_t length)
            {
                if (!ec) {
                    _received_packets.push(std::string(buffer->data(), length));
                    startRead();  // Continue reading more messages
                }
            }
        );
    }

    std::string TCP::receive()
    {
        if (_received_packets.empty()) {
            return "";
        }
        std::string packet = _received_packets.front();
        _received_packets.pop();
        return packet;
    }

    bool TCP::isConnectionAlive()
    {
        return _socket.is_open();
    }

    std::string TCP::fetchPacket()
    {
        return receive();
    }
}
