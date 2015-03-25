#ifndef BONEFISH_WEBSOCKET_WEBSOCKET_SERVER_HPP
#define BONEFISH_WEBSOCKET_WEBSOCKET_SERVER_HPP

#include <bonefish/common/wamp_message_processor.hpp>
#include <bonefish/websocket/websocket_config.hpp>

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/address.hpp>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <websocketpp/server.hpp>

namespace bonefish {

class wamp_session_id_generator;
class wamp_routers;
class wamp_serializers;

class websocket_server
{
public:
    websocket_server(boost::asio::io_service& io_service,
            const std::shared_ptr<wamp_routers>& routers,
            const std::shared_ptr<wamp_serializers>& serializers,
            const std::shared_ptr<wamp_session_id_generator>& generator);
    ~websocket_server();

    void start(const boost::asio::ip::address& ip_address, uint16_t port);
    void shutdown();

private:
    void on_open(websocketpp::connection_hdl handle);
    void on_close(websocketpp::connection_hdl handle);
    void on_fail(websocketpp::connection_hdl handle);
    bool on_validate(websocketpp::connection_hdl handle);
    void on_message(websocketpp::connection_hdl handle,
            websocketpp::server<websocket_config>::message_ptr message);

private:
    boost::asio::io_service& m_io_service;
    std::shared_ptr<websocketpp::server<websocket_config>> m_server;
    std::shared_ptr<wamp_routers> m_routers;
    std::shared_ptr<wamp_serializers> m_serializers;
    wamp_message_processor m_message_processor;
};

} // namespace bonefish

#endif // BONEFISH_WEBSOCKET_WEBSOCKET_SERVER_HPP