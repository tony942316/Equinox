/*
 * Copyright (C) 2024 Anthony H. Grasso
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */





#ifndef EQX_Server_Server_123
#define EQX_Server_Server_123


#include <stdh.hpp>
#include <osh.hpp>
#include <Equinox/Misc/Misc.hpp>
#include <Equinox/Client/Client.hpp>

namespace eqx
{
    class Server
    {
    public:
        Server() = default;

        explicit inline Server(const std::uint16_t port) noexcept;

        Server(Server&& other) = default;
        Server& operator= (Server&& other) = default;
        ~Server() = default;

        Server(const Server& other) = delete;
        Server& operator= (const Server& other) = delete;

        inline void start(const std::uint16_t port) noexcept;
        [[nodiscard]] inline eqx::Client getConnection() noexcept;

    private:
        std::optional<eqx::Socket> m_Socket;
    };
}

// Implementations

namespace eqx
{
    inline Server::Server(const std::uint16_t port) noexcept
    {
        start(port);
    }

    inline void Server::start(const std::uint16_t port) noexcept
    {
        m_Socket.emplace();

        auto error_code = osm::socket::setsockopt(m_Socket->get(),
            osm::socket::level::socket, osm::socket::option::reuseaddr);

        eqx::ENSURE_HARD(error_code == 0, "Error Setting Socket Option!"sv);

        error_code = osm::socket::bind(m_Socket->get(), port);

        eqx::ENSURE_HARD(error_code != -1, "Error Binding Socket!"sv);

        error_code = osm::socket::listen(m_Socket->get());
        eqx::ENSURE_HARD(error_code != -1, "Error Listening On Socket!"sv);
    }

    [[nodiscard]] inline eqx::Client Server::getConnection() noexcept
    {
        auto client_socket = osm::socket::accept(m_Socket->get(),
            osm::socket::flag::cloexec);
        eqx::ENSURE_HARD(client_socket != -1, "Error Accepting Connection!"sv);

        return Client(eqx::Socket(client_socket));
    }
}

#endif // EQX_Server_Server_123