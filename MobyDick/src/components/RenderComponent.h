#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include <memory>
#include <SDL2/SDL.h>
#include <json/json.h>

#include "../Texture.h"
#include "TransformComponent.h"
#include "AnimationComponent.h"

class AnimationComponent;
class PhysicsComponent;
class TransformComponent;


struct RenderComponent
{
	std::shared_ptr<Texture> m_texture;
	SDL_Color m_color;
	float m_xRenderAdjustment;
	float m_yRenderAdjustment;
	bool m_renderOutline;
	std::string m_textureId;

	RenderComponent();
	RenderComponent(Json::Value definitionJSON);
};


#endif

