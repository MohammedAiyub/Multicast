#include <iostream>
#include <boost/asio/io_service.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/beast/core.hpp>
#include <boost/asio.hpp>



enum { max_length = 1024 };
char m_data[max_length];



int main(int argc, char **argv)
{

  std::string m_address = argv[1];  //"222.233.188.246";
  int m_port = std::stoi(argv[2]); //25530;
  
  
  boost::asio::io_context ioc;
  boost::array<char, 1024> recv_buffer;
  boost::asio::ip::udp::socket m_socket(ioc);
      
  auto address = boost::asio::ip::address::from_string(m_address);

  boost::asio::ip::udp::endpoint listen_endpoint(address, m_port);
  m_socket.open(listen_endpoint.protocol());
  m_socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
  m_socket.bind(listen_endpoint);

  m_socket.set_option(boost::asio::ip::multicast::join_group(address));
  while(1)
  { 
    size_t m_size = m_socket.receive_from(boost::asio::buffer(m_data, max_length), listen_endpoint);
    std::cout << "Received: '" << std::string(m_data)<<std::endl;
  }
  return 0;
}
