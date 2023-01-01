#include "Camera.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Game/GameStates/GameStateTest.h"

Camera::Camera()
{

}

Camera::~Camera()
{
	RemoveCamera();
}

void Camera::Initialise()
{
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	m_View = pWindowManager->GetWindow()->getDefaultView();
	m_View.setSize(1080, 720);
}

void Camera::Update()
{
	if (m_Active)
	{
		WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
		pWindowManager->GetWindow()->setView(m_View);
		
	}
}

sf::Vector2f Camera::GetPosition()
{
	return m_View.getCenter();
}

void Camera::GetPosition(float& x, float& y)
{
	m_View.getCenter();
}

void Camera::SetPosition(float px, float py)
{
	m_View.setCenter(px, py);
}

void Camera::SetPosition(sf::Vector2f ppos)
{
	m_View.setCenter(ppos);
}

void Camera::SetAsCurrentCamera()
{
	m_Active = true;
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	pWindowManager->GetWindow()->setView(m_View);
}

void Camera::RemoveCamera()
{
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
	pWindowManager->GetWindow()->setView(pWindowManager->GetWindow()->getDefaultView());

	m_Active = false;
}