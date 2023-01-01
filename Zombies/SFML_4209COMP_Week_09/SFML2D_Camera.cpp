#include "SFML2D_Camera.h"

SFML2D_Camera::SFML2D_Camera(int projectileWindowWidth, int projectileWindowHeight)//Constructor
	:m_cameraPosition(0,0)
	,m_cameraWindowSize(projectileWindowWidth, projectileWindowHeight)
	,m_cameraZoom(1)
{
}

SFML2D_Camera::~SFML2D_Camera() {//Deconstructor


}

void SFML2D_Camera::setPosition(sf::Vector2f target) {
	//Set the camera poisiton to the input
	m_cameraPosition = target;

}

sf::FloatRect SFML2D_Camera::getCameraWindow(float parallaxFactor) {
	//parallaxFactor should be larger than 0
	//if parallaxFactor is less than 1, the window will be smaller and appears to scroll faster
	//otherwise the window will e bigger and appears to scroll slower
	sf::FloatRect window;

	//Calculating the top left coordinate of the visible area
	window.left = m_cameraPosition.x - m_cameraWindowSize.x / 2 * m_cameraZoom * parallaxFactor;
	window.top = m_cameraPosition.y - m_cameraWindowSize.y / 2 * m_cameraZoom * parallaxFactor;

	//Width and height are the x and y attributes
	window.width = m_cameraWindowSize.x * m_cameraZoom * parallaxFactor;
	window.height = m_cameraWindowSize.y * m_cameraZoom * parallaxFactor;

	//Return the rectangle
	return window;

}

void SFML2D_Camera::zoomUp(float elapsedTime){
	float zoomSpeed = 60.0f;
	float zoomChange = m_cameraZoom * 0.1f * elapsedTime * zoomSpeed;
	m_cameraZoom = m_cameraZoom - zoomChange;

}

void SFML2D_Camera::zoomDown(float elapsedTime){
	float zoomSpeed = 60.0f;
	float zoomChange = m_cameraZoom * 0.1f * elapsedTime * zoomSpeed;
	m_cameraZoom = m_cameraZoom + zoomChange;

}

sf::Transform SFML2D_Camera::getViewTransform() const {
	//Transform the coordinate from WORLD space to CAMERA space
	//Centered at the middle of the visible window
	sf::Transform transform = sf::Transform::Identity;
	transform.translate(m_cameraPosition);
	return transform.getInverse();

}

sf::Transform SFML2D_Camera::getProjTransform() const {
	//Transfrom the coordinate from WORLD space to CAMERA space
	//SCREEN space origin point is at the top left corner
	sf::Transform transform = sf::Transform::Identity;
	transform.translate(m_cameraWindowSize.x / 2, m_cameraWindowSize.y / 2);
	transform.scale(1.0f / m_cameraZoom, 1.0f / m_cameraZoom);
	return transform;

}


