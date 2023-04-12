#pragma once
#include "MobyDick.h"

class IMGuiLevelComplete : public IMGuiItem
{
public:
	IMGuiLevelComplete() = default;
	IMGuiLevelComplete(std::string gameObjectType, b2Vec2 padding, ImVec4 backgroundColor, ImVec4 textColor, ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor,
		bool autoSize);
	glm::vec2 render() override;

	ImFont* m_font{};

private:
	ImVec2 m_settingsModalSize{ 332,240 };
	//ImGuiWindowFlags m_SettingsModalflags{ ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings };
	ImGuiWindowFlags m_SettingsModalflags{ ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove };

	void _sendNextLevelEvent();

};
