#include "SFML_NPCSpriteObject.h"


SFML_NPCSpriteObject::SFML_NPCSpriteObject()
	: m_targetLocation(0, 0)
	, m_moveSpeed(100.0f)
	, m_state(IDLE)
	, m_idleAnimationID(-1)
	, m_walkingAnimationID(-1)
	, m_attackingAnimationID(-1)
	, m_visionConeAngle(90.0f)
	, m_visionRange(1200.0f)
{

}

SFML_NPCSpriteObject::~SFML_NPCSpriteObject()
{
}

int SFML_NPCSpriteObject::setIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_idleAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_idleAnimationID;
}

int	SFML_NPCSpriteObject::setWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_walkingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_walkingAnimationID;
}

int SFML_NPCSpriteObject::setAttackingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_attackingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_attackingAnimationID;
}

void SFML_NPCSpriteObject::toIdleState()
{
	m_state = IDLE;
	setCurrentAnimation(m_idleAnimationID);
}

void SFML_NPCSpriteObject::toWalkingState()
{
	m_state = WALKING;
	setCurrentAnimation(m_walkingAnimationID);
}

void SFML_NPCSpriteObject::toAttackingState()
{
	m_state = ATTACKING;
	setCurrentAnimation(m_attackingAnimationID);
}

void SFML_NPCSpriteObject::setTargetLocation(sf::Vector2f targetLocation)
{
	m_targetLocation = targetLocation;
}

void SFML_NPCSpriteObject::setMovementSpeed(float speed)
{
	m_moveSpeed = speed;
}

void SFML_NPCSpriteObject::update(float elapsedTime)
{
	const float PI = 3.1415f;

	//Get the npcs current location
	sf::Vector2f currentPosition = getPosition();

	//Calculate the vector from  the npcs current position to the target position
	sf::Vector2f faceDirection = m_targetLocation - currentPosition;

	//calculate the distance(L2-norm) between the current location and the target position
	float distance = sqrt(faceDirection.x * faceDirection.x + faceDirection.y * faceDirection.y);

	//If the distance is less than the displacement to cover in this frame
	if (distance < elapsedTime * m_moveSpeed) {
		//That means this npc has reached its desitination point
		setPosition(m_targetLocation);

		//set the animation to idle
		toIdleState();
	
	}else {
		//Otherwise it needs to keep going
		//Rotate the npc to face the target rotation
		float angle = atan2(faceDirection.y, faceDirection.x);
		setRotation(angle / PI * 180);

		//calculate the movement vector
		sf::Vector2f unitMoveVector = sf::Vector2f(cos(angle), sin(angle));
		sf::Vector2f totalMoveVector = unitMoveVector * elapsedTime * m_moveSpeed;
		move(totalMoveVector);

		//set the walking animation
		toWalkingState();
	
	}


	SFML_AnimatedSpriteObject::update(elapsedTime);
}

bool SFML_NPCSpriteObject::isInVision(sf::Vector2f targetPoint) {
	const float PI = 3.1415f;

	//Get the NPC's current location
	sf::Vector2f currentPosition = getPosition();

	//Calculate the vector from the NPC's current position to the target point
	sf::Vector2f vector = targetPoint - currentPosition;

	//Calculate the distance(L2-norm) between the the current location and the target position
	float distance = sqrt(vector.x * vector.x + vector.y * vector.y);

	//check if the distance is outside the vision range
	if (distance > m_visionRange)
		return false;

	//Get the NPC's ortientation.
	float faceAngle = getRotation();

	//calculate the angle of the vector
	float targetAngle = atan2(vector.y, vector.x);

	//convert to degree
	targetAngle = targetAngle * 180 / PI;

	while (targetAngle > 360)
		targetAngle = targetAngle - 360;

	while (targetAngle < 0)
		targetAngle = targetAngle + 360;

	//Calculate the absolute difference between targetangle and faceangle
	float angleDifference = fabs(targetAngle - faceAngle);

	//If within half of the vision come nagle then it is within the vision cone
	if (angleDifference <= m_visionConeAngle / 2)
		return true;
	else
		return false;

}
