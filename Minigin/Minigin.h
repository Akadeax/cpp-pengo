#pragma once
#include <string>
#include <functional>

namespace dae
{
	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();

		void Run(const std::function<void()>& load);

		Minigin(Minigin&& rhs) = delete;
		Minigin(const Minigin& rhs) = delete;
		Minigin& operator=(Minigin&& rhs) = delete;
		Minigin& operator=(const Minigin& rhs) = delete;

		static constexpr int WINDOW_WIDTH { 640 };
		static constexpr int WINDOW_HEIGHT{ 480 };

	private:
		std::string m_DataPath;
	};
}