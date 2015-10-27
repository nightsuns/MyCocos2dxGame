//
//  ArmorProperty.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#ifndef ArmorProperty_hpp
#define ArmorProperty_hpp

#include "PickableItemProperty.hpp"
class ArmorProperty : public PickableItemProperty
{
public:
    ArmorProperty(unsigned int instanceID, PickableItem::PickableItemType type, bool identified);
    
    virtual void adjustByDC();
    virtual void handleIdentify();
    
    bool hasEquiped() const { return m_bHasEquiped; }
    void setEquiped(bool equiped) { m_bHasEquiped = equiped; }
    
    CChaosNumber getAddedLightDistance() const { return m_nAddedLightDistance; }
    CChaosNumber getAddedSearchDistance() const { return m_nAddedSearchDistance; }
    CChaosNumber getAddedMaxHp() const { return m_nAddedMaxHP; }
    CChaosNumber getAddedMaxMp() const { return m_nAddedMaxMP; }
    
    CChaosNumber getAddedDefense();
    
    CChaosNumber getAddedArmorClass() const { return m_nAddedArmorClass; }
    CChaosNumber getAddedDodgeRate() const { return m_fAddedDodgeRate; }
    
    CChaosNumber getAddedMagicItemFindRate() const { return m_fAddedMagicItemFindRate; }
private:
    bool            m_bHasEquiped;
    
    CChaosNumber    m_nAddedLightDistance;       ///光照范围
    CChaosNumber    m_nAddedSearchDistance;      ///侦查范围
    CChaosNumber    m_nAddedMaxHP;               ///最大生命值
    CChaosNumber    m_nAddedMaxMP;               ///最大魔法值
    
    CChaosNumber    m_nAddedArmorClass;          ///防御等级
    CChaosNumber    m_fAddedDodgeRate;           ///闪避率

    CChaosNumber    m_fAddedMagicItemFindRate;  ///附加取魔率
};

#endif /* ArmorProperty_hpp */
