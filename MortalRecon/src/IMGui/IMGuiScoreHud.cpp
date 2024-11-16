#include "IMGuiScoreHud.h"
#include "../GameConstants.h"

extern std::unique_ptr<Game> game;

IMGuiScoreHud::IMGuiScoreHud(std::string gameObjectType, b2Vec2 padding, Scene* parentScene, ImVec4 backgroundColor, ImVec4 textColor,
	ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor, bool autoSize) :
	IMGuiItem(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize)
{

	m_flags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

	//Define some colors for HuD Elements
	SDL_Color red = Colors::RED;
	util::colorApplyAlpha(red, 255);
	m_hudRed = util::SDLColorToImVec4(red);

	SDL_Color white = Colors::WHITE;
	util::colorApplyAlpha(white, 255);
	m_hudWhite = util::SDLColorToImVec4(white);

	SDL_Color green = Colors::EMERALD;
	util::colorApplyAlpha(green, 255);
	m_hudGreen = util::SDLColorToImVec4(green);

	SDL_Color blue = Colors::BLUE;
	util::colorApplyAlpha(blue, 255);
	m_hudBlue = util::SDLColorToImVec4(blue);

	SDL_Color yellow = Colors::YELLOW;
	util::colorApplyAlpha(yellow, 255);
	m_hudYellow = util::SDLColorToImVec4(yellow);

	SDL_Color orange = Colors::ORANGE;
	util::colorApplyAlpha(yellow, 255);
	m_hudOrange = util::SDLColorToImVec4(orange);

}

glm::vec2 IMGuiScoreHud::render()
{

	glm::vec2 windowSize{};

	const auto& renderComponent = parent()->getComponent<RenderComponent>(ComponentTypes::RENDER_COMPONENT);
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	setWindowProperties(parent());

	//Set Color

	ImGui::PushStyleColor(ImGuiCol_WindowBg, m_backgroundColor);

	ImGui::Begin(m_gameObjectType.c_str(), nullptr, m_flags);
	{

		//hudScore();

		ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();


	}
	ImGui::End();

	//pop color style
	ImGui::PopStyleColor();

	return windowSize;

}

void IMGuiScoreHud::hudScore()
{

	auto survivorsTotal = game->contextMananger()->getStatusItem(StatusItemId::SURVIVORS).maxValue();
	auto survivorsSaved = game->contextMananger()->getStatusItem(StatusItemId::SURVIVORS).value();

	std::stringstream levelTxtSS;
	std::string levelTxt;
	levelTxtSS << survivorsSaved << "/" << survivorsTotal;
	levelTxt = levelTxtSS.str();
	ImGui::SameLine();
	ImGui::PushFont(m_largeFont);
	ImGui::Text(levelTxt.c_str());
	ImGui::PopFont();
	ImGui::NewLine();

}


