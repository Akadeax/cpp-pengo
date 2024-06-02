#pragma once
#include <functional>

namespace dae
{
    using ConnectionID = size_t;

    // Implementation of Observer through sigslots: https://en.wikipedia.org/wiki/Signals_and_slots
	// As used in Godot (Signals), Unity (UnityActions/delegates), etc.
    template<typename... SignalArgs>
    class Signal final
    {
    public:
        typedef std::function<void(SignalArgs...)> FuncType;
        typedef std::pair<ConnectionID, FuncType> Connection;

        Signal() = default;

        ConnectionID Connect(FuncType func)
        {
            ConnectionID idForThisConnect{ m_NextConnectionID++ };
            m_Connections.emplace_back(Connection{ idForThisConnect, func });
            return idForThisConnect;
        }

        void Disconnect(ConnectionID id)
        {
            std::erase_if(m_Connections, [id](const Connection& conn) { return conn.first == id; });
        }

        void DisconnectAll()
        {
            m_Connections.clear();
        }

        void Emit(SignalArgs... args) const
        {
            for (const Connection& conn : m_Connections)
            {
                conn.second(args...);
            }
        }

    private:
        std::vector<Connection> m_Connections{};
        size_t m_NextConnectionID{ 0 };
    };

}