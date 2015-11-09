//
//  SewerLevel.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/23.
//
//

#include "SewerLevel.hpp"
#include "GameFormula.hpp"
#include "RandomDungeon.hpp"
#include "StandardMonster.hpp"
#include "PickableItem.hpp"
#include "VoxelExplorer.h"
USING_NS_CC;

SewerLevel::SewerLevel()
{
}

bool SewerLevel::createMonsters()
{
    int monsterNum = calculateLevelMonsterCount();
    for (int i=0; i < monsterNum; i++) {
        BaseMonster::MonsterType type = (BaseMonster::MonsterType)cocos2d::random((int)BaseMonster::MT_RAT, (int)BaseMonster::MT_SLIME);
        StandardMonster* monster = StandardMonster::create(BaseMonster::MT_SLIME);
        if(!monster)
            return false;
        int tileIndex = -1;
        do {
             tileIndex = randomMonsterRespawnCell();
        } while (tileIndex == -1);
        
        monster->setPosition3D(Vec3(m_Map[tileIndex].m_nX*TerrainTile::CONTENT_SCALE, -0.5f*TerrainTile::CONTENT_SCALE, -m_Map[tileIndex].m_nY*TerrainTile::CONTENT_SCALE));
        monster->setVisited(m_Map[tileIndex].m_bVisited);
        monster->addTerrainTileFlag(TileInfo::ATTACKABLE);
        VoxelExplorer::getInstance()->getMonstersLayer()->addChild(monster);
        monster->setState(BaseMonster::MS_SLEEPING);
    }
    return true;
}
bool SewerLevel::createUseableItems()
{
    return true;
}
int SewerLevel::calculateLevelMonsterCount()
{
    int ret = m_nStandardAreaCount;
    if(m_Style == LS_STANDARD)
        ret = (int)(m_nStandardAreaCount*0.8f) + cocos2d::random(2, 5);
    else if (m_Style == LS_TUNNEL)
        ret = m_nStandardAreaCount + cocos2d::random(0, m_nStandardAreaCount);
    else if(m_Style == LS_PASSAGE)
        ret = (int)(m_nStandardAreaCount*0.5f) + m_nPassageAreaCount + cocos2d::random(2, 5);
    return ret;
}