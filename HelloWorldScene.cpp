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
    //123456
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
    onEnter();
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto anode=Node::create();
    //anode->setPosition(120,110);
    this->addChild(anode,0); //节点作为层的子 加到层上
    auto closeItem=MenuItemImage::create("chengjiu.png", "chengjiu1.png",CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    closeItem->setPosition(Vec2(Director::getInstance()->getWinSize().width, 50));
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    anode->addChild(menu, 1);
    
    Size s=Director::getInstance()->getWinSize();
    auto label00=Label::createWithSystemFont("一定要显示！", "Marker Felt.ttf", 20);
    label00->setPosition(Vec2(s.width/2, s.height-20));
    anode->addChild(label00,1);
    auto backSpri=Sprite::create("main_background.png");
    backSpri->setPosition(s.width/2, s.height/2);
    anode->addChild(backSpri,0);
    
    auto item1=MenuItemImage::create("select11.png", "select10.png");
    item1->setPosition(Vec2(350, 180));
    menu->addChild(item1);
    
    auto toggle=MenuItemToggle::create();
    toggle->setPosition(200, 200);
    auto item3=MenuItemLabel::create(Label::createWithSystemFont("TYL", "Marker Felt.ttf", 20));
    //item3->setPosition(Vec2(200,300));
    toggle->addSubItem(item3);
    menu->addChild(toggle);
    
    auto animationTest=MenuItemLabel::create(Label::createWithSystemFont("动画", "Maker Felt.ttf", 30), CC_CALLBACK_1(HelloWorld::animationCallBack,this));
    animationTest->setPosition(Vec2(300,200));
    menu->addChild(animationTest);
    animationTest->setColor(Color3B(230, 20, 20));
    
    
    toggle->setCallback( CC_CALLBACK_1(HelloWorld::itemCallback, this));
    toggle->setSelectedIndex(0);
    
    return true;
}

void HelloWorld::animationCallBack(Ref* sender)
{
    auto myScene=Scene::create();
    auto men=Menu::create();
    Director::getInstance()->pushScene(myScene);
    myScene->setPosition(Vec2::ZERO);
    auto alayer=LayerColor::create(Color4B(200, 100, 20, 255), 480, 320);
    myScene->addChild(alayer, 0);
    auto back=MenuItemLabel::create(Label::createWithSystemFont("返回", "Maker Felt.ttf", 30), CC_CALLBACK_1(HelloWorld::backto,this))
    ;
    alayer->addChild(men);
    alayer->setPosition(Vec2::ZERO);
    men->addChild(back);
    back->setPosition(Vec2(0,0));
    
    auto node=MenuItemLabel::create(Label::createWithSystemFont("BNode", "Maker Felt.ttf", 30), CC_CALLBACK_1(HelloWorld::nodeTest,this))
    ;
    node->setPosition(Vec2(0,20));
    men->addChild(node);
    auto spri=Sprite::create("s_hurt.png");
    spri->setPosition(100, 100);
    alayer->addChild(spri);
    
    auto sfc=SpriteFrameCache::getInstance(); //得到精灵帧的缓存
    sfc->addSpriteFramesWithFile("luoli3.plist", "photolist3.png");//将plist和多图片的文件加到精灵帧上
    alayer->addChild(Sprite::createWithSpriteFrame(sfc->getSpriteFrameByName("s_1.png")));//在层上加入一个精灵帧
    Vector<AnimationFrame*>vec;   //创建动画帧的一个容器
    for (int i=1; i<=8; i++) {
        float delay[]={1.0,1.0,0.1,0.1,0.1,0.1,0.1,0.1}; //设置间隔时间
        std::string str=StringUtils::format("s_%d.png",i);//用字符串来接收精灵的文件名
        ValueMap userInfo;  //不知道是什么作用
        auto spriteName=sfc->getSpriteFrameByName(str);  //从精灵帧缓存中取得精灵的名字
        auto frame=AnimationFrame::create(spriteName, delay[i], userInfo);//创建动画帧来接收一系列精灵的名字
        vec.pushBack(frame);  //将动画帧push 进容器栈中
    }
    auto animation=Animation::create(vec, 1.0f,10);
    animation->setRestoreOriginalFrame(true);   //设置回到初始位置
    animation->setDelayPerUnit(14.0f/14.0f);  //设置每一帧持续的时间
    auto anition22=Animate::create(animation);
    spri->runAction(anition22);
    
    
   
}

void HelloWorld::nodeTest(Ref * sender)
{
    auto myScene=Scene::create();
    //auto men=Menu::create();
    Director::getInstance()->pushScene(myScene);
    myScene->setPosition(Vec2::ZERO);
    auto alayer=LayerColor::create(Color4B(180, 100, 120, 255), 480, 320);
    myScene->addChild(alayer, 0);
    
    auto batchNode=SpriteBatchNode::create("shop1.png",1000);
    batchNode->setPosition(Vec2::ZERO);
    alayer->addChild(batchNode);
    for (int i=0; i<10; i++) {
        int x=arc4random()%960;
        int y=arc4random()%640;
        auto testIcon=Sprite::createWithTexture(batchNode->getTexture());
        testIcon->setPosition(x, y);
        batchNode->addChild(testIcon);
    }
}
void HelloWorld::backto(Ref* sender)
{
    Director::getInstance()->popToRootScene();
}
void HelloWorld::itemCallback(Ref * aSender)
{
    //auto rotate=RotateTo::create(1, 100, 90); //(时间，角度);
    auto spri=Sprite::create("s_hurt.png");
    spri->setPosition(100, 100);
    addChild(spri);
    //spri->runAction(rotate);
    auto blink=Blink::create(0.6, 5);
    auto jump=JumpTo::create(1.0f, Point(200,90), 20, 2);
    spri->runAction(jump);
    spri->runAction(blink);
    log("*****");
    ccBezierConfig berizer;
    berizer.controlPoint_1=Point(0,160);
    berizer.controlPoint_2=Point(300,240);
    berizer.endPosition=Point(300,100);
    auto be=BezierTo::create(2.0f, berizer);
    spri->runAction(be);
}

void HelloWorld::onEnter()
{
    Layer::onEnter();
    auto s=Director::getInstance()->getWinSize();
    auto layer=LayerColor::create(Color4B(200, 150, 0, 255), 200, 200);
    layer->ignoreAnchorPointForPosition(false);
    layer->setPosition(s.width/2, s.height/2);
    this->addChild(layer);
    layer->setVisible(false);
}

void HelloWorld::onExit()
{
    Layer::onExit();
    //auto moveTo=MoveTo::create(0.3f, Point(240,160)); //(时间，要移动到的点)
    //auto moveBy=MoveBy::create(0.3f, Vec2(240, 160));
    //auto rotate=RotateTo::create(0.3, 100, 90); //(时间，角度);
    auto spri=Sprite::create("s_hurt.png");
    //spri->runAction(rotate);
    
    auto jump=JumpTo::create(1.0f, Point(200,150), 20, 2);
    spri->runAction(jump);
    
}

void HelloWorld::menuCloseCallback(Ref* pSender)  //退出程序
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
