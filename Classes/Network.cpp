#include "Network.h"



Server::Server(boost::asio::io_service& io_service, short port)
	:socket_(io_service, ip::udp::endpoint(ip::udp::v4(), 2333)) {
	
	do_first_receive();
}

void Server::do_first_receive() {
	//cocos2d::log("do_first_receive");
	socket_.async_receive_from(
		boost::asio::buffer(receive_data_, max_msg), sender_endpoint_,
		[this](boost::system::error_code ec, std::size_t bytes)
	{
		//cocos2d::log("callback");
		if (!ec && bytes > 0)
		{
			//cocos2d::log("getdata");
			//cocos2d::log("%s", receive_data_);
			do_sent();
			do_receive();
			connect_exist = true;
		}
		else {
			do_first_receive();
		}
	});
}

void Server::do_receive() {
	//cocos2d::log("start receive");
	socket_.async_receive_from(
		boost::asio::buffer(receive_data_, max_msg), sender_endpoint_,
		[this](boost::system::error_code ec, std::size_t bytes_recvd) 
	{
		//cocos2d::log("get!%s", receive_data_);
		if (!ec && bytes_recvd > 0)
		{
			rtn_data = receive_data_;
		}
		do_receive();
	});
}

void Server::do_sent() {
	socket_.async_send_to(
		boost::asio::buffer(send_data_, max_msg), sender_endpoint_,
		[this](boost::system::error_code ec, std::size_t bytes_sent)
	{
		do_sent();
	});
}

void Server::add_send_data(std::string str) {
	strcpy(send_data_, str.c_str());
}

std::string Server::rtn_rec_data() {
	return rtn_data;
}

bool Server::get_connect_exist() {
	return connect_exist;
}


/*********************************************************************/


Client::Client(boost::asio::io_service& io_service, short port)
	:socket_(io_service, ip::udp::endpoint(ip::udp::v4(), 0)) {

	//TODO: localhost for test
	receiver_endpoint_.address(ip::address::from_string("127.0.0.1"));
	receiver_endpoint_.port(2333);
	do_first_sent();
}

void Client::do_first_sent() {
	socket_.async_send_to(boost::asio::buffer("1", 10), receiver_endpoint_,
		[this](boost::system::error_code ec, std::size_t bytes)
	{
		if (!ec && bytes > 0) {
			do_sent();
			do_receive();
			connect_exist = true;
		}
		else {
			do_first_sent();
		}
	});
}

void Client::do_sent() {
	socket_.async_send_to(boost::asio::buffer(send_data_, max_msg), receiver_endpoint_,
		[this](boost::system::error_code ec, std::size_t bytes)
	{
		do_sent();
	});
}

void Client::do_receive() {
	socket_.async_receive_from(
		boost::asio::buffer(receive_data_, max_msg), sender_endpoint_,
		[this](boost::system::error_code ec, std::size_t bytes_recvd) 
	{
		if (!ec && bytes_recvd > 0) {
			rtn_data = receive_data_;
		}
		do_receive();
	});
}

void Client::add_send_data(std::string str) {
	strcpy(send_data_, str.c_str());
}

std::string Client::rtn_rec_data() {
	return rtn_data;
}

bool Client::get_connect_exist() {
	return connect_exist;
}


/****************************************************************/

Network::Network(int mode) :m_mode(mode){
	io_service = new boost::asio::io_service();
	if (mode == 0) {
		server_ = new Server(*io_service, 2333);
	}
	else {
		client_ = new Client(*io_service, 2333);
	}
}

Network::~Network() {

}

void Network::set_sent_data(std::string str){
	if (m_mode == 0){
		server_->add_send_data(str);
	}
	else {
		client_->add_send_data(str);
	}
}

std::string Network::get_rec_data() {
	if (m_mode == 0) {
		return server_->rtn_rec_data();
	}
	else{
		return client_->rtn_rec_data();
	}
}

boost::asio::io_service* Network::getIOS() {
	return io_service;
}

bool Network::get_is_connect() {
	if (m_mode == 0) {
		return server_->get_connect_exist();
	}
	else {
		return client_->get_connect_exist();
	}
}