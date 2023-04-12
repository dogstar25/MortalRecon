#include "PistolWeaponComponent.h"
#include "../GameConstants.h"

extern std::unique_ptr<Game> game;


PistolWeaponComponent::PistolWeaponComponent(Json::Value definitionJSON)
	: WeaponComponent(definitionJSON)
{

	auto chargeTimerTime = definitionJSON["secondaryFire"]["chargeTime"].asFloat();
	m_chargeTimer = { chargeTimerTime };
	m_secondaryFireRadius = definitionJSON["secondaryFire"]["radius"].asInt();
	m_secondaryFireBulletPoolId = definitionJSON["secondaryFire"]["bulletPoolId"].asString();
	m_secondaryFireColor = game->colorMap()->toSDLColor(definitionJSON["secondaryFire"]["color"].asString());
	m_secondaryFireForce = definitionJSON["secondaryFire"]["force"].asFloat();


}

void PistolWeaponComponent::checkLevelUp(const int scrapCount)
{

	if (scrapCount >= (m_currentLevel * m_levelUpIncrement)) {
		_levelUp();
		game->contextMananger()->setStatusItemValue(StatusItemId::PLAYER_WEAPON_LEVEL, (float)m_currentLevel);
	}

	//Update the accrual amount used by things like the hud
	//Only if we are NOT at the maz level already
	if (m_currentLevel < m_weaponLevelDetails.size()) {
		m_currentLevelUpAccrual = scrapCount - (m_levelUpIncrement * (m_currentLevel - 1));
	}
	else {
		m_currentLevelUpAccrual = 0;
	}

	game->contextMananger()->setStatusItemValue(StatusItemId::PLAYER_WEAPON_ACCRUAL, m_currentLevelUpAccrual);

}

void PistolWeaponComponent::charge(bool isCharging)
{

	game->contextMananger()->setStatusItemValue(StatusItemId::PLAYER_WEAPON_IS_CHARGED, m_isFullyCharged);
	game->contextMananger()->setStatusItemValue(StatusItemId::PLAYER_WEAPON_CHARGED_PERCENT, (float)0);


	//ImGui::Begin("weaponCharge");
	//ImGui::SetWindowPos(ImVec2(400, 0));
	//ImGui::Value("m_isFullyCharged", m_isFullyCharged);
	//ImGui::Value("percentTargetMet", m_chargeTimer.percentTargetMet()*100);
	//ImGui::Value("timeRemaining", m_chargeTimer.timeRemaining().count());
	////ImGui::Value("hasMet", m_chargeTimer.hasMetTargetDuration());
	//ImGui::End();


	//If the charging timer hasnt even been started, then just bail
	if (m_chargeTimer.isSet() == false) {
		return;
	}

	const auto& soundComponent = parent()->getComponent<SoundComponent>(ComponentTypes::SOUND_COMPONENT);

	//If we are fully charged, then stay that way and do noting
	if (m_isFullyCharged == false) {

		if (isCharging) {

			game->contextMananger()->setStatusItemValue(StatusItemId::PLAYER_WEAPON_CHARGED_PERCENT, m_chargeTimer.percentTargetMet() * 100);

			if (m_chargingSoundStarted == false) {
				soundComponent->playSound("PULSE_CHARGING_SOUND");
				m_chargingSoundStarted = true;
			}

			//If we have met the charging timer time, then set to fully charged
			//otherwise
			if (m_chargeTimer.hasMetTargetDuration()) {
				soundComponent->stopSound("PULSE_CHARGING_SOUND");
				soundComponent->playSound("PULSE_FULL_CHARGE_SOUND");
				m_isFullyCharged = true;
			}

			//update the contextManagers charge value

		}
		else {

			if (m_chargingSoundStarted == true) {
				soundComponent->stopSound("PULSE_CHARGING_SOUND");
			}
			m_chargeTimer.reset();
			m_chargingSoundStarted = false;

		}
	}
	else {
		game->contextMananger()->setStatusItemValue(StatusItemId::PLAYER_WEAPON_CHARGED_PERCENT, (float)100);
	}


}

void PistolWeaponComponent::fireSecondary(const b2Vec2& origin, const float& angle)
{

	const auto& soundComponent = parent()->getComponent<SoundComponent>(ComponentTypes::SOUND_COMPONENT);
	

	if (m_isFullyCharged) {

		soundComponent->playSound("PULSE_FIRE_SOUND");

		WeaponComponent::fire(origin, angle, m_secondaryFireBulletPoolId, m_secondaryFireForce, m_secondaryFireColor);
		m_isFullyCharged = false;
	}
	else {

		soundComponent->playSound("PULSE_FAIL_SOUND");

	}


}
