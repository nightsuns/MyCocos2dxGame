//
//  BossDoor.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/5.
//
//

#include "BossDoor.hpp"
#include "LevelResourceManager.h"
USING_NS_CC;
BossDoor* BossDoor::create(bool show)
{
    auto tile = new (std::nothrow) BossDoor();
    if (tile && tile->initWithFile("16x16x16.c3b"))
    {
        std::string tex = LevelResourceManager::getInstance()->getTerrainTileRes(TERRAIN_TILES_NAME[TerrainTile::TT_WALL]);
        if(!tex.empty())
            tile->setTexture(tex);
        tile->setCameraMask((unsigned int)CameraFlag::USER1);
        tile->setLightMask((unsigned int)LightFlag::LIGHT0);
        tile->setVisible(show);
        tile->autorelease();
        return tile;
    }
    CC_SAFE_DELETE(tile);
    return nullptr;
}
BossDoor::BossDoor()
{
    m_OpenType = DOT_BOSS;
}
BossDoor::~BossDoor()
{
}
bool BossDoor::createFakeDoor()
{
    std::string model = LevelResourceManager::getInstance()->getDoorRes(DOOR_MODEL_NAMES[m_OpenType]);
    m_pFakeDoor = Sprite3D::create(model);
    if(!m_pFakeDoor)
        return false;
    m_pFakeDoor->setCameraMask((unsigned int)CameraFlag::USER1);
    m_pFakeDoor->setLightMask((unsigned int)LightFlag::LIGHT0);
    m_pFakeDoor->setPosition3D(Vec3(getPositionX(), -TerrainTile::CONTENT_SCALE*0.95f, getPositionZ()));
    this->getParent()->addChild(m_pFakeDoor);
    return true;
}