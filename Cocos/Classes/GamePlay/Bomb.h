#ifndef _BOMB_H_
#define _BOMB_H_


#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <string>
USING_NS_CC;

class cBomb:public cocos2d::Layer
{
private:
	int m_IdleTime;
	int m_BombRange;
	float m_CurrentTime;
	bool m_Dropped;
	CCPoint m_BombPosition;
	CCPoint m_TBombPosition;
	cocos2d::CCTMXTiledMap* m_Map;
	cocos2d::CCSprite* m_Role1;
	enum dire {
		UP = 0,
		RIGHT,
		DOWN,
		LEFT,
	};
	CCPoint points[4] = { ccp(0,-1),ccp(1,0),ccp(0,1),ccp(-1,0) };
	Vector<Sprite*> m_AllSprites;
public:
	cBomb(int bombRange = 1, int idleTime = 3) :m_IdleTime(idleTime),
		m_BombRange(bombRange), m_CurrentTime(0.0), m_Dropped(false),m_Map(nullptr),m_Role1(nullptr)
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
	bool droppedOrNot()
	{
		return m_Dropped;
	}

	//递增炸弹的爆炸范围
	void addBombRange() { ++m_BombRange; }
	//获取炸弹放置点的坐标
	CCPoint getBombPosition();
	//获取炸弹所在瓦片的坐标
	CCPoint getGrid();
	//获得炸弹爆炸前的动画
	Animation* creatBombAnimation();
	//放置炸弹
	void dropBomb();
	//获得爆炸四周水柱的动画
	//dire: 水柱方向
	Animation* creatExplodeAnimation(dire drection);
	//获得爆炸中心的动画
	Animation* creatCenterAnimation();
	//炸弹向dire所指定的方向爆炸
	void explosion(dire direction);
	//炸弹整体引爆
	void explode();
	//爆炸计时器
	void idleUpdate(float dt);
	void explodeUpdate(float dt);
	//删去被炸的瓦片
	void removeTile(dire direction);
};

#endif;