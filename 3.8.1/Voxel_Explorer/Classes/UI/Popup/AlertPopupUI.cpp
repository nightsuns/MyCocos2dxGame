//
//  AlertPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/10.
//
//

#include "AlertPopupUI.hpp"
#include "UtilityHelper.h"
USING_NS_CC;
AlertPopupUI::AlertPopupUI()
{
    m_nIsBlankClose     = false;
    m_pOk               = nullptr;
    m_pCancel           = nullptr;
    m_pTitle            = nullptr;
    m_pMessage          = nullptr;
    m_pNegativeFun      = nullptr;
    m_pPositiveFun      = nullptr;
    
}
AlertPopupUI::~AlertPopupUI()
{
    
}
bool AlertPopupUI::initUi()
{
    if(!PopupUILayer::initUi())
        return false;
    if(!load("alertLayer.csb",false))
        return false;
    return true;
}
bool AlertPopupUI::addEvents()
{
    if(!PopupUILayer::addEvents())
        return false;
    m_pOk = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "alert_layer_ok"));
    if (!m_pOk)
        return false;
    m_pCancel = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "alert_layer_cancel"));
    if (!m_pCancel)
        return false;
    m_pTitle = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "alert_layer_title_text"));
    if (!m_pTitle)
        return false;
    m_pMessage = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "alert_layer_message"));
    if (!m_pMessage)
        return false;
    
    m_pTitle->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pMessage->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pOk->getTitleRenderer()->setSystemFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pCancel->getTitleRenderer()->setSystemFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pOk->addClickEventListener(CC_CALLBACK_1(AlertPopupUI::onClickOk, this));
    m_pCancel->addClickEventListener(CC_CALLBACK_1(AlertPopupUI::onClickCancel,this));
    
    
    refreshUIView();
    
    return true;
}
void AlertPopupUI::onClickOk(cocos2d::Ref *ref)
{
    if (m_pPositiveFun) {
        m_pPositiveFun(this);
    }
    closePopup();
}
void AlertPopupUI::onClickCancel(cocos2d::Ref *ref)
{
    if (m_pNegativeFun) {
        m_pNegativeFun(this);
    }
    closePopup();
}
void AlertPopupUI::refreshUIView()
{
    if (m_pNegativeFun && m_pPositiveFun) {
        m_pOk->setVisible(true);
        m_pCancel->setVisible(true);
        m_pCancel->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.7,m_pCancel->getPositionY()));
        m_pOk->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.3,m_pOk->getPositionY()));
    }
    
    if (m_pNegativeFun&&!m_pPositiveFun) {
        m_pOk->setVisible(false);
        m_pCancel->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.5,m_pCancel->getPositionY()));
    }
    
    if (!m_pNegativeFun&&m_pPositiveFun) {
        m_pCancel->setVisible(false);
        m_pOk->setPosition(cocos2d::Vec2(m_pRootNode->getContentSize().width*0.5,m_pCancel->getPositionY()));
    }
}
void AlertPopupUI::setNegativeListerner(onClickListener listener,std::string str)
{
    m_pNegativeFun = listener;
    if (!str.empty()) {
        m_pCancel->setTitleText(str);
    }
    refreshUIView();
}
void AlertPopupUI::setPositiveListerner(onClickListener listener,std::string str)
{
    m_pPositiveFun = listener;
    if (!str.empty()) {
        m_pOk->setTitleText(str);
    }
    refreshUIView();
}
void AlertPopupUI::setTitle( std::string title)
{
    if (m_pTitle) {
        m_pTitle->setString(title);
    }
}
void AlertPopupUI::setMessage( std::string message)
{
    if (!m_pMessage)
        return;
    int charCount = 0;
    if(cocos2d::Application::getInstance()->getCurrentLanguage() ==cocos2d::LanguageType::CHINESE)
    {
        charCount =12;
    }else{
        charCount = 20;
    }
    UtilityHelper::getLineStr(message, charCount);
    m_pMessage->setString(message);
 }
