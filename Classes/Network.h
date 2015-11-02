#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include "cocos2d.h"
using namespace boost::asio;


class Server {
public:
	Server(boost::asio::io_service& io_service, short port);

	void do_receive();
	void do_first_receive();
	void do_sent();
	void add_send_data(std::string str);
	std::string rtn_rec_data();
	bool get_connect_exist();

private:
	bool connect_exist = false;
	ip::udp::socket socket_;
	ip::udp::endpoint sender_endpoint_;
	enum { max_msg = 64 };
	char receive_data_[max_msg] = "";
	char send_data_[max_msg] = "";
	std::string rtn_data = "";
};


/*************************************************************/

class Client {
public:
	Client(boost::asio::io_service& io_service, short port);

	void do_receive();
	void do_first_sent();
	void do_sent();
	void add_send_data(std::string str);
	std::string rtn_rec_data();
	bool get_connect_exist();
private:
	bool connect_exist = false;
	ip::udp::socket socket_;
	ip::udp::endpoint receiver_endpoint_;
	ip::udp::endpoint sender_endpoint_;
	enum { max_msg = 64 };
	char send_data_[max_msg] = "";
	char receive_data_[max_msg] = "";
	std::string rtn_data = "";
};


/*************************************************************/


class Network {
public:
	Network(int mode);
	~Network();

	void set_sent_data(std::string str);
	std::string get_rec_data();
	boost::asio::io_service* getIOS();
	bool get_is_connect();
private:
	int m_mode;
	boost::asio::io_service* io_service;
	Server* server_;
	Client* client_;
	
	
};




#endif