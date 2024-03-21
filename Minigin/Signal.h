#pragma once
#include <functional>

namespace dae
{
    // Implementation of Observer through sigslots: https://en.wikipedia.org/wiki/Signals_and_slots
	// As used in Godot (Signals), Unity (UnityActions/delegates), etc.
    template<typename... SignalArgs>
    class Signal final
    {
    public:
        typedef std::function<void(SignalArgs...)> FuncType;
        typedef size_t ConnectionId;
        typedef std::pair<ConnectionId, FuncType> Connection;

        Signal() = default;

        ConnectionId Connect(FuncType func)
        {
            ConnectionId idForThisConnect{ m_NextConnectionId++ };
            m_Connections.emplace_back(Connection{ idForThisConnect, func });
            return idForThisConnect;
        }

        void Disconnect(ConnectionId id)
        {
            std::erase_if(m_Connections, [id](const Connection& conn) { return conn.first == id; });
        }

        void Emit(SignalArgs... args)
        {
            for (const Connection& conn : m_Connections)
            {
                conn.second(args...);
            }
        }

    private:
        std::vector<Connection> m_Connections{};
        size_t m_NextConnectionId{ 0 };
    };

}