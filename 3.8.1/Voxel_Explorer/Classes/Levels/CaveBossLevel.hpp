//
//  CaveBossLevel.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/3.
//
//

#ifndef CaveBossLevel_hpp
#define CaveBossLevel_hpp

#include "StandardLevel.h"
class CaveBossLevel : public StandardLevel
{
public:
    CaveBossLevel();
    
    virtual bool build();
    virtual bool createMonsters();
    virtual bool createSummoningMonsters(const cocos2d::Vec2& mapPos);
    
    virtual bool createEliteMonster(int tileIndex);
    virtual void createSiegeMonsters(const cocos2d::Vec2& pos);
    
    virtual bool createBoss(const cocos2d::Vec2& pos);
    
    virtual bool createTrapsByGiant(const cocos2d::Vec2& mapPos, int skillStage);
    
    virtual void clearBossRoom();
    
    virtual bool createPickableItems();
private:
    std::vector<int> getTilesOnEdge(int m = 1);
private:
    int m_nHallRadius;
    int m_nChamberWidth;
    int m_nChamberHeight;
    
    int m_nLeft;
    int m_nCenter;
    
    int m_nIndexEntrance;
    int m_nIndexExit;
    int m_nArenaDoor;
    
    cocos2d::Vec2       m_BossPosition;
    
    cocos2d::Rect       m_AreaExitRect;
    cocos2d::Vec2       m_AreaExitCenter;
};

#endif /* CaveBossLevel_hpp */
