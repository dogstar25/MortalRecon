#include "HudStatusText.h"
#include "../StatusManager.h"
#include "../DynamicTextManager.h"
#include "../game.h"

#include <algorithm>

extern std::unique_ptr<Game> game;

HudStatusText::HudStatusText(std::string labelObjectId, std::string statusObjectId, float labelPadding, Scene* parentScene)
{

	m_label = std::make_shared<GameObject>(labelObjectId, -50.0f, -50.0f, 0.0f, parentScene, LAYER_MAIN);
	const auto& labelTransformComponent = m_label.value()->getComponent<TransformComponent>(ComponentTypes::TRANSFORM_COMPONENT);
	labelTransformComponent->setAbsolutePositioning(true);

	m_statusObject = std::make_shared<GameObject>(statusObjectId, -50.0f, -50.0f, 0.0f, parentScene, LAYER_MAIN);
	const auto& statusTransformComponent = m_statusObject->getComponent<TransformComponent>(ComponentTypes::TRANSFORM_COMPONENT);
	statusTransformComponent->setAbsolutePositioning(true);

	m_labelPadding = labelPadding;
	m_statusValue = game->statusMananger()->hudValueMap()[statusObjectId].get();


}

void HudStatusText::update(GameObject* parentGameObject)
{

	float labelPositionXAdjustment{};
	float labelHeight{};
	float labelWidth{};

	const auto& statusTransformComponent = m_statusObject->getComponent<TransformComponent>(ComponentTypes::TRANSFORM_COMPONENT);
	auto statusObjectWidth = statusTransformComponent->getPositionRect().w;
	auto statusObjectHeight = statusTransformComponent->getPositionRect().h;

	//If we have a lable object then update its position based on its parent and 
	//also call its normal update 
	if (m_label.has_value()) {

		SDL_FPoint labelPosition;
		m_label.value()->update();

		const auto& labelTransformComponent = m_label.value()->getComponent<TransformComponent>(ComponentTypes::TRANSFORM_COMPONENT);
		labelWidth = labelTransformComponent->getPositionRect().w;
		labelHeight = labelTransformComponent->getPositionRect().h;

		float maxheight = std::max(labelHeight, statusObjectHeight);

		labelPosition.x = parentGameObject->getTopLeftPosition().x + (labelWidth / 2);
		labelPosition.y = parentGameObject->getTopLeftPosition().y + (maxheight / 2);
		m_label.value()->setPosition(labelPosition);

		labelPositionXAdjustment = labelWidth + m_labelPadding;

	}

	//Update the dynamic text item that is used by this TextObject
	std::stringstream ss;
	ss << static_cast<float>(*m_statusValue);
	DynamicTextManager::instance().updateText(m_statusObject->id(), ss.str());

	m_statusObject->update();

	//Update the position of the status object
	auto parentPosition = parentGameObject->getTopLeftPosition();

	float maxheight = std::max(labelHeight, statusObjectHeight);
	SDL_FPoint statusPosition{};
	statusPosition.x = parentPosition.x + labelPositionXAdjustment;
	statusPosition.y = parentPosition.y + maxheight / 2;
	m_statusObject->setPosition(statusPosition);

	//Calculate the size of the hud item
	float hudHeight{ maxheight };
	float hudWidth{};

	//Width
	hudWidth = labelWidth + statusObjectWidth;


	const auto& parentTransformComponent = parentGameObject->getComponent<TransformComponent>(ComponentTypes::TRANSFORM_COMPONENT);
	parentTransformComponent->setSize(hudWidth, hudHeight);



}

void HudStatusText::render(GameObject* parentGameObject)
{

	if (m_label.has_value()) {
		m_label.value()->render();
	}

	m_statusObject->render();

}