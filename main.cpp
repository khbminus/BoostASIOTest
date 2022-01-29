#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>

using boost::asio::ip::tcp;


int main() {
    try {
        boost::asio::io_context ioContext;
        tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 8088));
        for (;;) {
            tcp::socket socket(ioContext);
            acceptor.accept(socket);
            for (;;) {
                boost::system::error_code ignored_error;
                boost::array<char, 128> buf;
                boost::system::error_code read_error;

                size_t len = socket.read_some(boost::asio::buffer(buf), read_error);
                if (read_error == boost::asio::error::eof) {
                    break;
                } else if (read_error) {
                    throw boost::system::system_error(read_error);
                }
                boost::asio::write(socket, boost::asio::buffer(buf, len), ignored_error);

            }

        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
