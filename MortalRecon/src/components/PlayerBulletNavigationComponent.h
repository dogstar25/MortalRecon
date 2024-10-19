#pragma once
#include "MobyDick.h"

class PlayerBulletNavigationComponent : public NavigationComponent
{
	public:
		PlayerBulletNavigationComponent();
		PlayerBulletNavigationComponent(Json::Value componentJSON);
		~PlayerBulletNavigationComponent();

		void update() override;
		void reset() override;

	private:
		std::optional<float> m_closestDistance{};
};
