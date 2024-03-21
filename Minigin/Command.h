#pragma once

namespace dae
{
	class GameObject;

	class Command
	{
	public:
		Command() = default;
		explicit Command(GameObject* pObject) : m_pGameObject{ pObject } {}
		virtual ~Command() = default;

		Command(const Command&) = delete;
		Command(Command&&) noexcept = delete;
		Command& operator=(const Command&) = delete;
		Command& operator=(Command&&) noexcept = delete;

		virtual void Execute() = 0;

	protected:
		GameObject* m_pGameObject{};
	};
}