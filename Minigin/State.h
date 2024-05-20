#pragma once

namespace dae
{
	class State
	{
	public:
		explicit State() = default;
		virtual ~State() = default;

		State(const State&) = delete;
		State(State&&) noexcept = delete;
		State operator=(const State&) = delete;
		State operator=(State&&) noexcept = delete;

		virtual void OnEnter() {}
		virtual void OnExit() {}
		virtual void Update() {}
	};
}
