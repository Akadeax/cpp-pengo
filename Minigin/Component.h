#pragma once
class Component
{
public:
	virtual void Update();
	virtual void Render() const;

	virtual ~Component();

	Component(Component&& rhs) = delete;
	Component(const Component& rhs) = delete;
	Component& operator=(Component&& rhs) = delete;
	Component& operator=(const Component& rhs) = delete;
};
