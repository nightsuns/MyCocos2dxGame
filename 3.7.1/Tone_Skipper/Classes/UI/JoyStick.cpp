//
//  JoyStick.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/27.
//
//

#include "JoyStick.h"
USING_NS_CC;

JoyStick* JoyStick::create()
{
    JoyStick *pRet = new(std::nothrow) JoyStick();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}
JoyStick::JoyStick()
{
    m_pLeftBtn = nullptr;
    m_pUpBtn = nullptr;
    m_pRightBtn = nullptr;
    m_pDownBtn = nullptr;
    m_pABtn = nullptr;
    m_pBBtn = nullptr;
}
JoyStick::~JoyStick()
{
}
bool JoyStick::init()
{
    if ( !Layer::init() )
        return false;
    
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height/320.0f;
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("joystick.plist");
    
    m_pLeftBtn = ui::Button::create("left_normal.png", "left_clicked.png", "", ui::TextureResType::PLIST);
    if(!m_pLeftBtn)
        return false;
    m_pLeftBtn->setScale(scale);
    m_pLeftBtn->setPosition(Vec2(m_pLeftBtn->getContentSize().width*scale, m_pLeftBtn->getContentSize().height*2*scale));
    m_pLeftBtn->addTouchEventListener(CC_CALLBACK_2(JoyStick::leftBtnTouchEvent, this));
    addChild(m_pLeftBtn);
    
    m_pUpBtn = ui::Button::create("up_normal.png", "up_clicked.png", "", ui::TextureResType::PLIST);
    if(!m_pUpBtn)
        return false;
    m_pUpBtn->setScale(scale);
    m_pUpBtn->setPosition(Vec2(m_pUpBtn->getContentSize().width*2*scale, m_pUpBtn->getContentSize().height*3*scale));
    m_pUpBtn->addTouchEventListener(CC_CALLBACK_2(JoyStick::upBtnTouchEvent, this));
    addChild(m_pUpBtn);
    
    m_pRightBtn = ui::Button::create("right_normal.png", "right_clicked.png", "", ui::TextureResType::PLIST);
    if(!m_pRightBtn)
        return false;
    m_pRightBtn->setScale(scale);
    m_pRightBtn->setPosition(Vec2(m_pRightBtn->getContentSize().width*3*scale, m_pRightBtn->getContentSize().height*2*scale));
    m_pRightBtn->addTouchEventListener(CC_CALLBACK_2(JoyStick::rightBtnTouchEvent, this));
    addChild(m_pRightBtn);
    
    m_pDownBtn = ui::Button::create("down_normal.png", "down_clicked.png", "", ui::TextureResType::PLIST);
    if(!m_pDownBtn)
        return false;
    m_pDownBtn->setScale(scale);
    m_pDownBtn->setPosition(Vec2(m_pDownBtn->getContentSize().width*2*scale, m_pDownBtn->getContentSize().height*scale));
    m_pDownBtn->addTouchEventListener(CC_CALLBACK_2(JoyStick::downBtnTouchEvent, this));
    addChild(m_pDownBtn);
    
    m_pABtn = ui::Button::create("a_normal.png", "a_clicked.png", "", ui::TextureResType::PLIST);
    if(!m_pABtn)
        return false;
    m_pABtn->setScale(scale);
    m_pABtn->setPosition(Vec2(size.width - m_pABtn->getContentSize().width*2.5*scale, m_pABtn->getContentSize().height*1.3*scale));
    m_pABtn->addTouchEventListener(CC_CALLBACK_2(JoyStick::aBtnTouchEvent, this));
    addChild(m_pABtn);
    
    m_pBBtn = ui::Button::create("b_normal.png", "b_clicked.png", "", ui::TextureResType::PLIST);
    if(!m_pBBtn)
        return false;
    m_pBBtn->setScale(scale);
    m_pBBtn->setPosition(Vec2(size.width - m_pBBtn->getContentSize().width*1.3*scale , m_pBBtn->getContentSize().height*2.5*scale));
    m_pBBtn->addTouchEventListener(CC_CALLBACK_2(JoyStick::bBtnTouchEvent, this));
    addChild(m_pBBtn);
    
    setCascadeOpacityEnabled(true);
    setOpacity(200);
    return true;
}
void JoyStick::addJoystickListener(JoystickListener* listener)
{
    if(listener == nullptr)
        return;
    auto iter = std::find(m_Listeners.begin(), m_Listeners.end(), listener);
    if(iter != m_Listeners.end())
    {
        CCLOG("addJoystickListener : this listener has already added!");
        return;
    }
    else
        m_Listeners.push_back(listener);
}
void JoyStick::removeJoyStickListener(JoystickListener* listener)
{
    auto iter = std::find(m_Listeners.begin(), m_Listeners.end(), listener);
    if (iter != m_Listeners.end())
        m_Listeners.erase(iter);
}
void JoyStick::removeAllJoyStickListener()
{
    m_Listeners.clear();
}

void JoyStick::leftBtnTouchEvent(Ref *ref, ui::Widget::TouchEventType touchType)
{
    for (JoystickListener* listener : m_Listeners) {
        if (touchType == ui::Widget::TouchEventType::BEGAN)
            listener->onLeftBtnPressed();
        else if(touchType == ui::Widget::TouchEventType::MOVED)
        {
            if(m_pLeftBtn)
            {
                Vec2 pos = m_pLeftBtn->getTouchMovePosition();
                bool hit = m_pLeftBtn->hitTest(pos);
                if(!hit)
                    listener->onLeftBtnReleased();
            }
        }
        else if (touchType == ui::Widget::TouchEventType::ENDED)
            listener->onLeftBtnReleased();
        else if(touchType == ui::Widget::TouchEventType::CANCELED)
            listener->onLeftBtnReleased();
    }
}
void JoyStick::upBtnTouchEvent(Ref *ref, ui::Widget::TouchEventType touchType)
{
    for (JoystickListener* listener : m_Listeners) {
        if (touchType == ui::Widget::TouchEventType::BEGAN)
            listener->onUpBtnPressed();
        else if(touchType == ui::Widget::TouchEventType::MOVED)
        {
            if(m_pUpBtn)
            {
                Vec2 pos = m_pUpBtn->getTouchMovePosition();
                bool hit = m_pUpBtn->hitTest(pos);
                if(!hit)
                    listener->onUpBtnReleased();
            }
        }
        else if (touchType == ui::Widget::TouchEventType::ENDED)
            listener->onUpBtnReleased();
        else if (touchType == ui::Widget::TouchEventType::CANCELED)
            listener->onUpBtnReleased();
    }
}
void JoyStick::rightBtnTouchEvent(Ref *ref, ui::Widget::TouchEventType touchType)
{
    for (JoystickListener* listener : m_Listeners) {
        if (touchType == ui::Widget::TouchEventType::BEGAN)
            listener->onRightBtnPressed();
        else if(touchType == ui::Widget::TouchEventType::MOVED)
        {
            if(m_pRightBtn)
            {
                Vec2 pos = m_pRightBtn->getTouchMovePosition();
                bool hit = m_pRightBtn->hitTest(pos);
                if(!hit)
                    listener->onRightBtnReleased();
            }
        }
        else if (touchType == ui::Widget::TouchEventType::ENDED)
            listener->onRightBtnReleased();
        else if (touchType == ui::Widget::TouchEventType::CANCELED)
            listener->onRightBtnReleased();
    }
}
void JoyStick::downBtnTouchEvent(Ref *ref, ui::Widget::TouchEventType touchType)
{
    for (JoystickListener* listener : m_Listeners) {
        if (touchType == ui::Widget::TouchEventType::BEGAN)
            listener->onDownBtnPressed();
        else if(touchType == ui::Widget::TouchEventType::MOVED)
        {
            if(m_pDownBtn)
            {
                Vec2 pos = m_pDownBtn->getTouchMovePosition();
                bool hit = m_pDownBtn->hitTest(pos);
                if(!hit)
                    listener->onDownBtnReleased();
            }
        }
        else if (touchType == ui::Widget::TouchEventType::ENDED)
            listener->onDownBtnReleased();
        else if (touchType == ui::Widget::TouchEventType::CANCELED)
            listener->onDownBtnReleased();
    }
}
void JoyStick::aBtnTouchEvent(Ref *ref, ui::Widget::TouchEventType touchType)
{
    for (JoystickListener* listener : m_Listeners) {
        if (touchType == ui::Widget::TouchEventType::BEGAN)
            listener->onABtnPressed();
        else if(touchType == ui::Widget::TouchEventType::MOVED)
        {
            if(m_pABtn)
            {
                Vec2 pos = m_pABtn->getTouchMovePosition();
                bool hit = m_pABtn->hitTest(pos);
                if(!hit)
                    listener->onABtnReleased();
            }
        }
        else if (touchType == ui::Widget::TouchEventType::ENDED)
            listener->onABtnReleased();
        else if (touchType == ui::Widget::TouchEventType::CANCELED)
            listener->onABtnReleased();
    }
}
void JoyStick::bBtnTouchEvent(Ref *ref, ui::Widget::TouchEventType touchType)
{
    for (JoystickListener* listener : m_Listeners) {
        if (touchType == ui::Widget::TouchEventType::BEGAN)
            listener->onBBtnPressed();
        else if(touchType == ui::Widget::TouchEventType::MOVED)
        {
            if(m_pBBtn)
            {
                Vec2 pos = m_pBBtn->getTouchMovePosition();
                bool hit = m_pBBtn->hitTest(pos);
                if(!hit)
                    listener->onBBtnReleased();
            }
        }
        else if (touchType == ui::Widget::TouchEventType::ENDED)
            listener->onBBtnReleased();
        else if (touchType == ui::Widget::TouchEventType::CANCELED)
            listener->onBBtnReleased();
    }
}