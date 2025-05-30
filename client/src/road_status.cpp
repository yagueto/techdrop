#include "road_status.h"
#include "Socket.h"
#include "rapidxml.hpp"
#include <iostream>

using namespace rapidxml;

std::string query_api() {
  if (!Socket::initializeWinSock()) {
    std::cerr << "¡Error inicializando el cliente!" << std::endl;
    return nullptr;
  }

  Socket socket;
  if (!socket.create(Socket::CLIENT)) {
    std::cerr << "¡Error inicializando el socket!" << std::endl;
    return nullptr;
  };
  if (!socket.connect_to_server("194.30.81.20", 80)) {
    std::cerr << "¡Error conectando al servidor!" << std::endl;
    return nullptr;
  }
  auto result = socket.send_message(
      "GET "
      "/cs/Satellite?language=es&pageid=3000075248&pagename=Bilbaonet/Page/"
      "BIO_suscripcionRSS&tipoSus=Avisos&idSec=3000003828 HTTP/1.1\r\nHost: "
      "www.bilbao.eus\r\nConnection: close\r\n\r\n");

  std::string message;
  Socket::MessageResult result_message = {Socket::MessageResult::SUCESS};
  while (result_message.status == Socket::MessageResult::SUCESS) {
    result_message = socket.receive_message();
    message += result_message.message;
  }

  int i = message.find("<rss");
  std::string message2 = message.substr(i, message.size() - i - 7);

  socket.close();
  return message2;
}

std::vector<StatusEntry> get_road_status() {
  std::vector<StatusEntry> entries;
  const std::string query_result = query_api();

  xml_document<> doc;
  doc.parse<0>(const_cast<char *>(query_result.c_str()));
  const xml_node<> *node = doc.first_node()->first_node();
  for (const xml_node<> *item_node = node->first_node("item"); item_node;
       item_node = item_node->next_sibling("item")) {
    entries.push_back(
        {item_node->first_node("title")->first_node()->value(),
         item_node->first_node("description")->first_node()->value()});
  }

  return entries;
}