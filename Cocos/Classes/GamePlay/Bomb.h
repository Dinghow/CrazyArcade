#ifndef _BOMB_H_
#define _BOMB_H_


#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <string>
USING_NS_CC;
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

class cBomb:public cocos2d::Layer
{
private:
	int m_IdleTime;            
	int m_BombRange;
	float m_CurrentTime;
	bool m_Dropped;
	bool m_Exploded;
	CCPoint m_BombPosition;            //the opengl coordinate
	CCPoint m_TBombPosition;           //the tile coordinate
	cocos2d::CCTMXTiledMap* m_Map;
	cocos2d::CCSprite* m_Role1;
	enum dire {
		UP = 0,
		RIGHT,
		DOWN,
		LEFT,
	};
	Vector<Sprite*> m_AllSprites;
public:
	CCPoint points[4] = { ccp(0,-1),ccp(1,0),ccp(0,1),ccp(-1,0) };
	int m_Board[4];
	cBomb(int bombRange = 1, int idleTime = 3) :m_IdleTime(idleTime),
		m_BombRange(bombRange), m_CurrentTime(0.0), m_Dropped(false),m_Map(nullptr),m_Role1(nullptr),
		m_Exploded(false)
	{
		cocos2d::Layer::onEnter();
	}
	void getMap(cocos2d::CCTMXTiledMap* map)
	{
		m_Map = map;
	}
	void getRole(cocos2d::CCSprite* role)
	{
		m_Role1 = role;
	}
	cocos2d::CCTMXTiledMap* returnMap()
	{
		return m_Map;
	}
	cocos2d::CCSprite* returnRole()
	{
		return m_Role1;
	}
	bool droppedOrNot()
	{
		return m_Dropped;
	}
	CCPoint bombOpenglCoord()
	{
		return m_BombPosition;
	}
	void detonate()
	{
		m_CurrentTime = 4.0f;
	}

	//increase the bomb power
	void addBombRange() { ++m_BombRange; }
	//get the bomb's opengl coordinate
	//the center of tile
	CCPoint getBombPosition();
	//get the role's Tile coordinate
	CCPoint getGrid();
	//create the animation of bomb before explosion
	Animation* creatBombAnimation();
	//drop the bomb
	void dropBomb();
	//create the animation around the explosion center
	//divided into four directions
	Animation* creatExplodeAnimation(dire drection);
	//create the animation of explosion center
	Animation* creatCenterAnimation();
	//the explosion in one direction
	void explosion(dire direction);
	//the complete explosion process
	void explode();
	//Timer before explosion
	void idleUpdate(float dt);
	//Timer during the explosion
	void explodeUpdate(float dt);
	//remove the tile in m_Map destroied by explosion
	void removeTile(dire direction);

	bool explodedOrNot()
	{
		return m_Exploded;
	}
	CCPoint showBombPosition()
	{
		return m_BombPosition;
	}
	void setBombRange(int bombRange)
	{
		m_BombRange = bombRange;
	}
};

#endif;