// This Inlcude 
#include "Component.h"

CComponent::CComponent() {}

CComponent::~CComponent() {}

void CComponent::SetOwner(std::shared_ptr<CGameObject> _gameObject)
{
	this->m_owner = _gameObject;
}

std::weak_ptr<CGameObject> CComponent::GetOwner() const
{
	return m_owner;
}

void CComponent::SetActive(bool _b)
{
	m_isActive = _b;
}

bool CComponent::IsActive() const
{
	return m_isActive;
}
