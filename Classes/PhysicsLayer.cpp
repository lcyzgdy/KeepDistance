#include "PhysicsLayer.h"
#include "GameOverScene.h"
#include "PlaneSprite.h"

void PhysicsLayer::RemoveObject(SpriteWithPhysicsAndAnimation* object)
{
	if (object == nullptr) return;
	/*object->unscheduleAllSelectors();
	object->unscheduleAllCallbacks();
	object->unscheduleUpdate();
	object->removeFromParentAndCleanup(true);
	object->autorelease();*/
	object->SetCanRemove();
	object->Remove();
}

cocos2d::Layer * PhysicsLayer::createLayer()
{
	return PhysicsLayer::create();
}

bool PhysicsLayer::init()
{
	this->scheduleUpdate();
	return true;
}

void PhysicsLayer::update(float dt)
{
	if (m_castObject.size() >= 2)
	{
		for (int i = 0; i < m_castObject.size() - 1; i++)
		{
			if (i >= m_castObject.size()) break;
			if (m_castObject[i]->CanRemove() || m_castObject[i]->Died())
			{
				RemoveObject(m_castObject[i]);
				m_castObject.erase(m_castObject.begin() + i);
				continue;
			}
			//if (m_castObject[i]->getName() == "tool1") continue;
			for (int j = i + 1; j < m_castObject.size(); j++)
			{
				if (j >= m_castObject.size()) break;
				//if (m_castObject[j]->getName() == "tool1") continue;
				if (m_castObject[j]->CanRemove() || m_castObject[j]->Died())
				{
					RemoveObject(m_castObject[j]);
					m_castObject.erase(m_castObject.begin() + j);
					continue;
				}
				if (m_castObject[i]->getParent() == m_castObject[j]->getParent()) continue;
				if (CastEnemyAndBullet(i, j)) continue;
				if (CastEnemyAndPlayer(m_castObject[i], m_castObject[j])) continue;
				if (m_castObject[i]->getName().find("tool") != string::npos && m_castObject[j]->getName().find("player") != string::npos)
				{
					CastToolAndPlayer(m_castObject[i], i, m_castObject[j]);
					continue;
				}
				else if (m_castObject[j]->getName().find("tool") != string::npos && m_castObject[i]->getName().find("player") != string::npos)
				{
					CastToolAndPlayer(m_castObject[j], j, m_castObject[i]);
					continue;
				}
			}
		}
	}

	var player = dynamic_cast<PlaneSprite*>(getParent()->getChildByName("player")->getChildByName("player"));
	if (player == nullptr) return;
	if (player->IsShooting())
	{
		for (int i = 0; i < m_castObject.size(); i++)
		{
			if (m_castObject[i]->getName().find("nemy") == string::npos) continue;
			if (Vec2::angle(m_castObject[i]->getPosition() - player->getPosition(), Vec2(0, 1)) < 30 * 3.1415927 / 180)
			{
				m_castObject[i]->Hit();
				if (m_castObject[i]->CanRemove() || m_castObject[i]->Died())
				{
					RemoveObject(m_castObject[i]);
					m_castObject.erase(m_castObject.begin() + i);
				}
			}
		}
	}
}

bool PhysicsLayer::CastEnemyAndBullet(int i, int j)
{
	if (!((m_castObject[i]->getName().find("bullet") != string::npos
		&& m_castObject[j]->getName().find("Enemy") != string::npos)
		|| (m_castObject[j]->getName().find("bullet") != string::npos
			&& m_castObject[i]->getName().find("Enemy") != string::npos)))
	{
		return false;
	}
	if (m_castObject[i]->getBoundingBox().intersectsRect(m_castObject[j]->getBoundingBox()))
	{
		m_castObject[i]->Hit();
		m_castObject[j]->Hit();
		//var player = dynamic_cast<PlaneSprite*>(getParent()->getChildByName("player")->getChildByName("player"));
		if (m_castObject[i]->CanRemove() || m_castObject[i]->Died())
		{
			RemoveObject(m_castObject[i]);
			m_castObject.erase(m_castObject.begin() + i);
			if (m_castObject[j - 1]->CanRemove() || m_castObject[j - 1]->Died())
			{
				RemoveObject(m_castObject[j - 1]);
				m_castObject.erase(m_castObject.begin() + j - 1);
			}
		}
		else if (m_castObject[j]->CanRemove() || m_castObject[j]->Died())
		{
			RemoveObject(m_castObject[j]);
			m_castObject.erase(m_castObject.begin() + j);
		}
	}
	return true;
}

bool PhysicsLayer::CastToolAndPlayer(SpriteWithPhysicsAndAnimation * tool, int a, SpriteWithPhysicsAndAnimation * player)
{
	if (player->getBoundingBox().intersectsRect(tool->getBoundingBox()))
	{
		if (tool->getName().find("1") != string::npos) dynamic_cast<PlaneSprite*>(player)->ChangeBullet();
		else
		{
			var player = dynamic_cast<PlaneSprite*>(getParent()->getChildByName("player")->getChildByName("player"));
			player->AddDazhaoCount();
		}
		RemoveObject(tool);
		m_castObject.erase(m_castObject.begin() + a);
		return true;
	}
	return false;
}

bool PhysicsLayer::CastEnemyAndPlayer(SpriteWithPhysicsAndAnimation * a, SpriteWithPhysicsAndAnimation * b)
{
	/*
	if (a->getName().find("player") != string::npos && b->getName().find("nemy") != string::npos)
	{
		if (a->getBoundingBox().intersectsRect(b->getBoundingBox()))
		{
			var gameover = GameOverScene::createScene(dynamic_cast<PlaneSprite*>(a)->GetTotalScore());
			Director::getInstance()->replaceScene(gameover);
			return true;
		}
	}
	if (b->getName().find("player") != string::npos && a->getName().find("nemy") != string::npos)
	{
		if (a->getBoundingBox().intersectsRect(b->getBoundingBox()))
		{
			var gameover = GameOverScene::createScene(dynamic_cast<PlaneSprite*>(b)->GetTotalScore());
			//Director::getInstance()->popScene();
			Director::getInstance()->replaceScene(gameover);
			return true;
		}
	}*/
	return false;
}

void PhysicsLayer::Add(int n, ...)
{
	va_list obj;
	va_start(obj, n);
	SpriteWithPhysicsAndAnimation* temp;
	while (temp = va_arg(obj, SpriteWithPhysicsAndAnimation*))
	{
		m_castObject.push_back(temp);
	}
	va_end(obj);
}

void PhysicsLayer::Add(SpriteWithPhysicsAndAnimation* obj)
{
	m_castObject.push_back(obj);
}
