#include "IMGuiInteractiveMenuSurvivor.h"


extern std::unique_ptr<Game> game;

IMGuiInteractiveMenuSurvivor::IMGuiInteractiveMenuSurvivor(std::string gameObjectType, b2Vec2 padding, ImVec4 backgroundColor, ImVec4 textColor,
	ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor, bool autoSize) :
	IMGuiItem(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize)
{

	m_flags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize;

}

glm::vec2 IMGuiInteractiveMenuSurvivor::render()
{

	glm::vec2 windowSize{};

	const auto& baseGameObject = parent()->parent().value();
	const auto& baseObjectActionComponent = baseGameObject->getComponent<ActionComponent>(ComponentTypes::ACTION_COMPONENT);
	const auto& interactAction = baseObjectActionComponent->getAction(ACTION_INTERACTION);

	const auto& renderComponent = parent()->getComponent<RenderComponent>(ComponentTypes::RENDER_COMPONENT);
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	setWindowProperties(parent());

	//Set color
	ImGui::PushStyleColor(ImGuiCol_WindowBg, m_backgroundColor);
	ImGui::PushStyleColor(ImGuiCol_Button, m_buttonColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_buttonHoverColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_buttonActiveColor);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);


	ImGui::Begin(m_gameObjectType.c_str(), nullptr, m_flags);
	{
		ImGui::PushFont(m_smallFont);
		ImGui::SetWindowPos(ImVec2{ renderComponent->getRenderDestRect().x, renderComponent->getRenderDestRect().y });
		ImGui::SmallButton("E");
		ImGui::SameLine();
		ImGui::Text("Follow");
		ImGui::SmallButton("R");
		ImGui::SameLine();
		ImGui::Text("Stay");

		ImGui::PopFont();
		ImGui::SameLine();

		windowSize = { ImGui::GetWindowSize().x, ImGui::GetWindowSize().y };
	}
	ImGui::End();

	//pop color style
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();

	//if (ImGui::IsKeyPressed(ImGuiKey_E)) {
	//	interactAction->perform(interactingObject, parent()->parent().value(), SDL_SCANCODE_E);
	//}
	//if (ImGui::IsKeyPressed(ImGuiKey_R)) {
	//	interactAction->perform(interactingObject, parent()->parent().value(), SDL_SCANCODE_R);
	//}

	return windowSize;
}