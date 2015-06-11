#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    //testSlider();
   // testSwitch();
   // testColorPicker();
    //testEditBox();
   // testControlBtn();
    return true;
}

void HelloWorld::testSlider()
{
	auto slider=ControlSlider::create("xuetiao1.png", "xuetiao2.png", "xuetiao3.png");
    slider->setAnchorPoint(Point(0.5, 0.5));
    slider->setMinimumValue(0);
    slider->setMaximumValue(100);
	//slider->setMaximumAllowedValue();
    slider->setPosition(Point(240, 160));
    slider->setTag(1);
    slider->addTargetWithActionForControlEvents(this,cccontrol_selector(HelloWorld::sliderValueChanged),Control::EventType::VALUE_CHANGED);
    slider->setScale(2);
    this->addChild(slider);
}
void HelloWorld::sliderValueChanged(Ref *sender, Control::EventType controlEvent)
{
    auto slider=(ControlSlider*)sender;
    log("%.2f",slider->getValue());
}

void HelloWorld::testSwitch()
{
    auto switchControl = ControlSwitch::create
    (
     Sprite::create("switch-mask.png"),
     Sprite::create("switch-on.png"),
     Sprite::create("switch-off.png"),
     Sprite::create("switch-thumb.png"),
     Label::create("On", "Arial", 16),
     Label::create("Off", "Arial", 16)
     );
    
    //设置位置
    switchControl->setPosition(Point(240, 160));
    //注册事件
    switchControl->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::switchValueChanged), Control::EventType::VALUE_CHANGED);
    switchControl->setScale(2, 2);
    this->addChild(switchControl);
}
//回调函数，判断当前状态
void HelloWorld::switchValueChanged(Ref* sender, Control::EventType controlEvent)
{
    auto pSwitch = (ControlSwitch*)sender;
    if (pSwitch->isOn()) {
        log("pSwitch = ON\n");
    }else
    {
        log("pSwitch = OFF\n");
    }
}

//测试颜色选择器
void HelloWorld::testColorPicker()
{
    auto colourPicker = ControlColourPicker::create();
    colourPicker->setColor(Color3B(37, 46, 252));
    colourPicker->setPosition(Point (colourPicker->getContentSize().width /2,100));
    //注册事件
    colourPicker->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::colourPickerValueChanged), Control::EventType::VALUE_CHANGED);
    
    auto label=LabelTTF::create("TESTCOLOR", "Arial", 40);
    label->setPosition(Point(300,150));
    label->setTag(19);
    this->addChild(label);
    // 添加到当前层
    this->addChild(colourPicker);
}

void HelloWorld::colourPickerValueChanged(Ref *sender, Control::EventType controlEvent)
{
    auto  picker=(ControlColourPicker *)sender;
    auto str=__String::createWithFormat("#%02X%02X%02X",
                                        picker->getColor().r, picker->getColor().g,picker->getColor().b);
    log("str is %s",(str->getCString()));
    auto label=(Label *)this->getChildByTag(19);
    label->setColor(Color3B(picker->getColor().r, picker->getColor().g, picker->getColor().b));
}


void HelloWorld::testEditBox()
{
    auto sp = Scale9Sprite::create("textField.png");
    //设置大小
    sp->setPreferredSize(Size(255, 40));
    sp->setAnchorPoint(Point(0.5, 0.5));
    
    
    auto editBox=EditBox::create(Size(255, 40), sp);
    editBox->setPlaceHolder("请输入内容");
    editBox->setFontColor(Color3B(255, 0, 255));
    editBox->setPosition(Point(240, 60));
    editBox->setInputMode(EditBox::InputMode::ANY);
    editBox->setMaxLength(10);
    editBox->setReturnType(EditBox::KeyboardReturnType::DONE);
    editBox->setDelegate(this);
    editBox->setInputFlag(EditBox::InputFlag::PASSWORD);
    this->addChild(editBox);
}
void HelloWorld::editBoxReturn(EditBox* editBox)
{
    
    
}
void HelloWorld::editBoxEditingDidBegin(EditBox* editBox)
{}
void HelloWorld::editBoxEditingDidEnd(EditBox* editBox)
{}
void HelloWorld::editBoxTextChanged(EditBox* editBox, const std::string& text)
{}

void HelloWorld::testControlBtn()
{
    //创建正常状态下九宫格精灵
    auto btnNormal = Scale9Sprite::create("switch-on.png");
    
    //创建点击状态下九宫格精灵
    auto  btnSelected = Scale9Sprite::create("switch-off.png");
    
    /*创建标题*/
    auto title = LabelTTF::create("", "Marker Felt", 30);
    
    
    /* 根据标题和九宫格图片创建按钮 */
    auto  controlBtn = ControlButton::create(title, btnNormal);
    //setPreferredSize 设置大小*/
    controlBtn->setPreferredSize(Size(128, 128));
    
    /* 设置点击时候显示的图片 */
    controlBtn->setBackgroundSpriteForState(btnSelected, Control::State::HIGH_LIGHTED);
    
    controlBtn->setPosition(Point(200, 200));
    //注册事件
    controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::btnClicked), Control::EventType::TOUCH_UP_INSIDE);
    controlBtn->setTag(10);
    this->addChild(controlBtn);
}
void HelloWorld::btnClicked(Ref* sender, Control::EventType controlEvent)
{
    log("Button Clicked");
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
