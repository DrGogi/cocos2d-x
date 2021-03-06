// local import
#include "Texture2dTest.h"
#include "../testResource.h"

enum {
    kTagLabel = 1,
    kTagSprite1 = 2,
    kTagSprite2 = 3,
};

static std::function<Layer*()> createFunctions[] =
{
    CL(TexturePVRv3Premult),

    CL(TextureMemoryAlloc),
    CL(TextureAlias),
    CL(TexturePVRMipMap),
    CL(TexturePVRMipMap2),
    CL(TexturePVRNonSquare),
    CL(TexturePVRNPOT4444),
    CL(TexturePVRNPOT8888),
    CL(TexturePVRTest),
    CL(TexturePVR2BPP),
    CL(TexturePVR2BPPv3),
    CL(TexturePVR4BPP),
    CL(TexturePVR4BPPv3),
    CL(TexturePVRII4BPPv3),
    CL(TexturePVRRGBA8888),
    CL(TexturePVRRGBA8888v3),
    CL(TexturePVRBGRA8888),
    CL(TexturePVRBGRA8888v3),
    CL(TexturePVRRGBA4444),
    CL(TexturePVRRGBA4444v3),
    CL(TexturePVRRGBA4444GZ),
    CL(TexturePVRRGBA4444CCZ),
    CL(TexturePVRRGBA5551),
    CL(TexturePVRRGBA5551v3),
    CL(TexturePVRRGB565),
    CL(TexturePVRRGB565v3),
    CL(TexturePVRRGB888),
    CL(TexturePVRRGB888v3),
    CL(TexturePVRA8),
    CL(TexturePVRA8v3),
    CL(TexturePVRI8),
    CL(TexturePVRI8v3),
    CL(TexturePVRAI88),
    CL(TexturePVRAI88v3),
    
    CL(TexturePVRv3Premult),
    
    CL(TexturePVRBadEncoding),
    CL(TexturePNG),
    CL(TextureJPEG),
    CL(TextureTIFF),
    CL(TextureTGA),
    CL(TextureWEBP),
    CL(TexturePixelFormat),
    CL(TextureBlend),
    CL(TextureAsync),
    CL(TextureGlClamp),
    CL(TextureGlRepeat),
    CL(TextureSizeTest),
    CL(TextureCache1),
    CL(TextureDrawAtPoint),
    CL(TextureDrawInRect),
    
    CL(TextureETC1),
    
    CL(TextureS3TCDxt1),
    CL(TextureS3TCDxt3),
    CL(TextureS3TCDxt5),
    
    CL(TextureATITCRGB),
    CL(TextureATITCExplicit),
    CL(TextureATITCInterpolated),
    
    CL(TextureConvertRGB888),
    CL(TextureConvertRGBA8888),
    CL(TextureConvertI8),
    CL(TextureConvertAI88),
};

static unsigned int TEST_CASE_COUNT = sizeof(createFunctions) / sizeof(createFunctions[0]);

static int sceneIdx=-1;
Layer* createTextureTest(int index)
{
    auto layer = (createFunctions[index])();;
    return layer;
}

Layer* nextTextureTest();
Layer* backTextureTest();
Layer* restartTextureTest();

Layer* nextTextureTest()
{
    sceneIdx++;
    sceneIdx = sceneIdx % TEST_CASE_COUNT;

    return createTextureTest(sceneIdx);
}

Layer* backTextureTest()
{
    sceneIdx--;
    if( sceneIdx < 0 )
        sceneIdx = TEST_CASE_COUNT -1;    

    return createTextureTest(sceneIdx);
}

Layer* restartTextureTest()
{
    return createTextureTest(sceneIdx);
}

//------------------------------------------------------------------
//
// TextureDemo
//
//------------------------------------------------------------------
void TextureDemo::onEnter()
{
    BaseTest::onEnter();

    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();

    auto col = LayerColor::create(Color4B(128,128,128,255));
    addChild(col, -10);
    
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

TextureDemo::~TextureDemo()
{
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

void TextureDemo::restartCallback(Object* sender)
{
    auto s = TextureTestScene::create();
    s->addChild(restartTextureTest());
    Director::getInstance()->replaceScene(s);
}

void TextureDemo::nextCallback(Object* sender)
{
    auto s = TextureTestScene::create();
    s->addChild(nextTextureTest());
    Director::getInstance()->replaceScene(s);
}

void TextureDemo::backCallback(Object* sender)
{
    auto s = TextureTestScene::create();
    s->addChild(backTextureTest());
    Director::getInstance()->replaceScene(s);
}

std::string TextureDemo::title()
{
    return "No title";
}

std::string TextureDemo::subtitle()
{
    return "";
}

//------------------------------------------------------------------
//
// TextureTIFF
//
//------------------------------------------------------------------

void TextureTIFF::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image.tiff");
    img->setPosition(Point( s.width/2.0f, s.height/2.0f));
    this->addChild(img);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TextureTIFF::title()
{
    return "TIFF Test";
}


//------------------------------------------------------------------
//
// TextureTGA
//
//------------------------------------------------------------------

void TextureTGA::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("TileMaps/levelmap.tga");
    img->setPosition(Point( s.width/2.0f, s.height/2.0f));
    this->addChild(img);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TextureTGA::title()
{
    return "TGA Test";
}

//------------------------------------------------------------------
//
// TexturePNG
//
//------------------------------------------------------------------
void TexturePNG::onEnter()
{
    TextureDemo::onEnter();    

    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image.png");
    img->setPosition(Point( s.width/2.0f, s.height/2.0f));
    addChild(img);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePNG::title()
{
    return "PNG Test";
}

//------------------------------------------------------------------
//
// TextureJPEG
//
//------------------------------------------------------------------
void TextureJPEG::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image.jpeg");
    img->setPosition(Point( s.width/2.0f, s.height/2.0f));
    addChild(img);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TextureJPEG::title()
{
    return "JPEG Test";
}

//------------------------------------------------------------------
//
// TextureWEBP
//
//------------------------------------------------------------------
void TextureWEBP::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image.webp");
    img->setPosition(Point( s.width/2.0f, s.height/2.0f));
    addChild(img);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TextureWEBP::title()
{
    return "WEBP Test";
}

//------------------------------------------------------------------
//
// TextureMipMap
//
//------------------------------------------------------------------
void TextureMipMap::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto texture0 = Director::getInstance()->getTextureCache()->addImage("Images/grossini_dance_atlas.png");
    texture0->generateMipmap();
    Texture2D::TexParams texParams = { GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
    texture0->setTexParameters(texParams);

    auto texture1 = Director::getInstance()->getTextureCache()->addImage("Images/grossini_dance_atlas_nomipmap.png");

    auto img0 = Sprite::createWithTexture(texture0);
    img0->setTextureRect(Rect(85, 121, 85, 121));
    img0->setPosition(Point( s.width/3.0f, s.height/2.0f));
    addChild(img0);

    auto img1 = Sprite::createWithTexture(texture1);
    img1->setTextureRect(Rect(85, 121, 85, 121));
    img1->setPosition(Point( 2*s.width/3.0f, s.height/2.0f));
    addChild(img1);
    
    
    auto scale1 = EaseOut::create(ScaleBy::create(4, 0.01f), 3);
    auto sc_back = scale1->reverse();
    
    auto scale2 = scale1->clone();
    auto sc_back2 = scale2->reverse();

    img0->runAction(RepeatForever::create(Sequence::create(scale1, sc_back, NULL)));
    img1->runAction(RepeatForever::create(Sequence::create(scale2, sc_back2, NULL)));
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TextureMipMap::title()
{
    return "Texture Mipmap";
}

std::string TextureMipMap::subtitle()
{
    return "Left image uses mipmap. Right image doesn't";
}

//------------------------------------------------------------------
//
// TexturePVRMipMap
// To generate PVR images read this article:
// http://developer.apple.com/iphone/library/qa/qa2008/qa1611.html
//
//------------------------------------------------------------------
void TexturePVRMipMap::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto imgMipMap = Sprite::create("Images/logo-mipmap.pvr");
    if( imgMipMap )
    {
        imgMipMap->setPosition(Point( s.width/2.0f-100, s.height/2.0f));
        addChild(imgMipMap);

        // support mipmap filtering
        Texture2D::TexParams texParams = { GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
        imgMipMap->getTexture()->setTexParameters(texParams);
    }

    auto img = Sprite::create("Images/logo-nomipmap.pvr");
    if( img )
    {
        img->setPosition(Point( s.width/2.0f+100, s.height/2.0f));
        addChild(img);

        auto scale1 = EaseOut::create(ScaleBy::create(4, 0.01f), 3);
        auto sc_back = scale1->reverse();

        auto scale2 = scale1->clone();
        auto sc_back2 = scale2->reverse();
        
        imgMipMap->runAction(RepeatForever::create(Sequence::create(scale1, sc_back, NULL)));
        img->runAction(RepeatForever::create(Sequence::create(scale2, sc_back2, NULL)));
    }
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVRMipMap::title()
{
    return "PVRTC MipMap Test";
}
std::string TexturePVRMipMap::subtitle()
{
    return "Left image uses mipmap. Right image doesn't";
}

//------------------------------------------------------------------
//
// TexturePVRMipMap2
//
//------------------------------------------------------------------
void TexturePVRMipMap2::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto imgMipMap = Sprite::create("Images/test_image_rgba4444_mipmap.pvr");
    imgMipMap->setPosition(Point( s.width/2.0f-100, s.height/2.0f));
    addChild(imgMipMap);
    
    // support mipmap filtering
    Texture2D::TexParams texParams = { GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
    imgMipMap->getTexture()->setTexParameters(texParams);

    auto img = Sprite::create("Images/test_image.png");
    img->setPosition(Point( s.width/2.0f+100, s.height/2.0f));
    addChild(img);
    
    auto scale1 = EaseOut::create(ScaleBy::create(4, 0.01f), 3);
    auto sc_back = scale1->reverse();

    auto scale2 = scale1->clone();
    auto sc_back2 = scale2->reverse();
    
    imgMipMap->runAction(RepeatForever::create(Sequence::create(scale1, sc_back, NULL)));
    img->runAction(RepeatForever::create(Sequence::create(scale2, sc_back2, NULL)));
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVRMipMap2::title()
{
    return "PVR MipMap Test #2";
}

std::string TexturePVRMipMap2::subtitle()
{
    return "Left image uses mipmap. Right image doesn't";
}

//------------------------------------------------------------------
//
// TexturePVR2BPP
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVR2BPP::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image_pvrtc2bpp.pvr");
    
    if( img )
    {
        img->setPosition(Point( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVR2BPP::title()
{
    return "PVR TC 2bpp Test";
}

//------------------------------------------------------------------
//
// TexturePVR
// To generate PVR images read this article:
// http://developer.apple.com/iphone/library/qa/qa2008/qa1611.html
//
//------------------------------------------------------------------
void TexturePVRTest::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image.pvr");
    
    if( img )
    {
        img->setPosition(Point( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    else
    {
        log("This test is not supported.");
    }
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
    
}

std::string TexturePVRTest::title()
{
    return "PVR TC 4bpp Test #2";
}

//------------------------------------------------------------------
//
// TexturePVR4BPP
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVR4BPP::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image_pvrtc4bpp.pvr");
    
    if( img )
    {
        img->setPosition(Point( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    else
    {
        log("This test is not supported in cocos2d-mac");
    }
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVR4BPP::title()
{
    return "PVR TC 4bpp Test #3";
}

//------------------------------------------------------------------
//
// TexturePVRRGBA8888
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRRGBA8888::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image_rgba8888.pvr");
    img->setPosition(Point( s.width/2.0f, s.height/2.0f));
    addChild(img);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVRRGBA8888::title()
{
    return "PVR + RGBA  8888 Test";
}

//------------------------------------------------------------------
//
// TexturePVRBGRA8888
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRBGRA8888::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_bgra8888.pvr");
    if( img )
    {
        img->setPosition(Point( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    else
    {
        log("BGRA8888 images are not supported");
    }
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVRBGRA8888::title()
{
    return "PVR + BGRA 8888 Test";
}

//------------------------------------------------------------------
//
// TexturePVRRGBA5551
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRRGBA5551::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgba5551.pvr");
    img->setPosition(Point( s.width/2.0f, s.height/2.0f));
    addChild(img);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVRRGBA5551::title()
{
    return "PVR + RGBA 5551 Test";
}

//------------------------------------------------------------------
//
// TexturePVRRGBA4444
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRRGBA4444::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgba4444.pvr");
    img->setPosition(Point( s.width/2.0f, s.height/2.0f));
    addChild(img);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVRRGBA4444::title()
{
    return "PVR + RGBA 4444 Test";
}

//------------------------------------------------------------------
//
// TexturePVRRGBA4444GZ
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRRGBA4444GZ::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // android can not pack .gz file into apk file
    auto img = Sprite::create("Images/test_image_rgba4444.pvr");
#else
    auto img = Sprite::create("Images/test_image_rgba4444.pvr.gz");
#endif
    img->setPosition(Point( s.width/2.0f, s.height/2.0f));
    addChild(img);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVRRGBA4444GZ::title()
{
    return "PVR + RGBA 4444 + GZ Test";
}

std::string TexturePVRRGBA4444GZ::subtitle()
{
    return "This is a gzip PVR image";
}

//------------------------------------------------------------------
//
// TexturePVRRGBA4444CCZ
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRRGBA4444CCZ::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image_rgba4444.pvr.ccz");
    img->setPosition(Point( s.width/2.0f, s.height/2.0f));
    addChild(img);    
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVRRGBA4444CCZ::title()
{
    return "PVR + RGBA 4444 + CCZ Test";
}

std::string TexturePVRRGBA4444CCZ::subtitle()
{
    return "This is a ccz PVR image";
}

//------------------------------------------------------------------
//
// TexturePVRRGB565
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRRGB565::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgb565.pvr");
    img->setPosition(Point( s.width/2.0f, s.height/2.0f));
    addChild(img);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVRRGB565::title()
{
    return "PVR + RGB 565 Test";
}

// TexturePVR RGB888
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
void TexturePVRRGB888::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image_rgb888.pvr");
    if (img != NULL)
    {
        img->setPosition(Point( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }

    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();

}
std::string TexturePVRRGB888::title()
{
    return "PVR + RGB 888 Test";
}

//------------------------------------------------------------------
//
// TexturePVRA8
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRA8::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_a8.pvr");
    img->setPosition(Point( s.width/2.0f, s.height/2.0f));
    addChild(img);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();

}

std::string TexturePVRA8::title()
{
    return "PVR + A8 Test";
}

//------------------------------------------------------------------
//
// TexturePVRI8
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRI8::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image_i8.pvr");
    img->setPosition(Point( s.width/2.0f, s.height/2.0f));
    addChild(img);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVRI8::title()
{
    return "PVR + I8 Test";
}

//------------------------------------------------------------------
//
// TexturePVRAI88
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRAI88::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_ai88.pvr");
    img->setPosition(Point( s.width/2.0f, s.height/2.0f));
    addChild(img);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVRAI88::title()
{
    return "PVR + AI88 Test";
}

// TexturePVR2BPPv3
void TexturePVR2BPPv3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_pvrtc2bpp_v3.pvr");
    
    if (img)
    {
        img->setPosition(Point(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

string TexturePVR2BPPv3::title()
{
    return "PVR TC 2bpp Test";
}

string TexturePVR2BPPv3::subtitle()
{
    return "Testing PVR File Format v3";
}

// TexturePVRII2BPPv3
void TexturePVRII2BPPv3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_pvrtcii2bpp_v3.pvr");
    
    if (img)
    {
        img->setPosition(Point(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

string TexturePVRII2BPPv3::title()
{
    return "PVR TC II 2bpp Test";
}

string TexturePVRII2BPPv3::subtitle()
{
    return "Testing PVR File Format v3";
}

// TexturePVR4BPPv3
void TexturePVR4BPPv3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_pvrtc4bpp_v3.pvr");
    
    if (img)
    {
        img->setPosition(Point(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    else
    {
        log("This test is not supported");
    }
    
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

string TexturePVR4BPPv3::title()
{
    return "PVR TC 4bpp Test";
}

string TexturePVR4BPPv3::subtitle()
{
    return "Testing PVR File Format v3";
}

// TexturePVRII4BPPv3

// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp

void TexturePVRII4BPPv3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_pvrtcii4bpp_v3.pvr");
    
    if (img)
    {
        img->setPosition(Point(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    else
    {
        log("This test is not supported");
    }
    
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

string TexturePVRII4BPPv3::title()
{
    return "PVR TC II 4bpp Test";
}

string TexturePVRII4BPPv3::subtitle()
{
    return "Testing PVR File Format v3";
}

// TexturePVRRGBA8888v3
void TexturePVRRGBA8888v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgba8888_v3.pvr");
    
    if (img)
    {
        img->setPosition(Point(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

string TexturePVRRGBA8888v3::title()
{
    return "PVR + RGBA  8888 Test";
}

string TexturePVRRGBA8888v3::subtitle()
{
    return "Testing PVR File Format v3";
}

// TexturePVRBGRA8888v3
void TexturePVRBGRA8888v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_bgra8888_v3.pvr");
    
    if (img)
    {
        img->setPosition(Point(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    else
    {
        log("BGRA images are not supported");
    }
    
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

string TexturePVRBGRA8888v3::title()
{
    return "PVR + BGRA 8888 Test";
}

string TexturePVRBGRA8888v3::subtitle()
{
    return "Testing PVR File Format v3";
}

// TexturePVRRGBA5551v3
void TexturePVRRGBA5551v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgba5551_v3.pvr");
    
    if (img)
    {
        img->setPosition(Point(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

string TexturePVRRGBA5551v3::title()
{
    return "PVR + RGBA 5551 Test";
}

string TexturePVRRGBA5551v3::subtitle()
{
    return "Testing PVR File Format v3";
}

// TexturePVRRGBA4444v3
void TexturePVRRGBA4444v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgba4444_v3.pvr");
    
    if (img)
    {
        img->setPosition(Point(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

string TexturePVRRGBA4444v3::title()
{
    return "PVR + RGBA 4444 Test";
}

string TexturePVRRGBA4444v3::subtitle()
{
    return "Testing PVR File Format v3";
}

// TexturePVRRGB565v3
void TexturePVRRGB565v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgb565_v3.pvr");
    
    if (img)
    {
        img->setPosition(Point(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

string TexturePVRRGB565v3::title()
{
    return "PVR + RGB 565 Test";
}

string TexturePVRRGB565v3::subtitle()
{
    return "Testing PVR File Format v3";
}

// TexturePVRRGB888v3
void TexturePVRRGB888v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_rgb888_v3.pvr");
    
    if (img)
    {
        img->setPosition(Point(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

string TexturePVRRGB888v3::title()
{
    return "PVR + RGB 888 Test";
}

string TexturePVRRGB888v3::subtitle()
{
    return "Testing PVR File Format v3";
}

// TexturePVRA8v3
void TexturePVRA8v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_a8_v3.pvr");
    
    if (img)
    {
        img->setPosition(Point(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

string TexturePVRA8v3::title()
{
    return "PVR + A8 Test";
}

string TexturePVRA8v3::subtitle()
{
    return "Testing PVR File Format v3";
}

// TexturePVRI8v3
void TexturePVRI8v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_i8_v3.pvr");
    
    if (img)
    {
        img->setPosition(Point(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

string TexturePVRI8v3::title()
{
    return "PVR + I8 Test";
}

string TexturePVRI8v3::subtitle()
{
    return "Testing PVR File Format v3";
}

// TexturePVRAI88v3
void TexturePVRAI88v3::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/test_image_ai88_v3.pvr");
    
    if (img)
    {
        img->setPosition(Point(s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

string TexturePVRAI88v3::title()
{
    return "PVR + AI88 Test";
}

string TexturePVRAI88v3::subtitle()
{
    return "Testing PVR File Format v3";
}

//------------------------------------------------------------------
//
// TexturePVRBadEncoding
// Image generated using PVRTexTool:
// http://www.imgtec.com/powervr/insider/powervr-pvrtextool.asp
//
//------------------------------------------------------------------
void TexturePVRBadEncoding::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/test_image-bad_encoding.pvr");
    if( img )
    {
        img->setPosition(Point( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
}

std::string TexturePVRBadEncoding::title()
{
    return "PVR Unsupported encoding";
}

std::string TexturePVRBadEncoding::subtitle()
{
    return "You should not see any image";
}

//------------------------------------------------------------------
//
// TexturePVRNonSquare
//
//------------------------------------------------------------------
void TexturePVRNonSquare::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/grossini_128x256_mipmap.pvr");
    img->setPosition(Point( s.width/2.0f, s.height/2.0f));
    addChild(img);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVRNonSquare::title()
{
    return "PVR + Non square texture";
}

std::string TexturePVRNonSquare::subtitle()
{
    return "Loading a 128x256 texture";
}

//------------------------------------------------------------------
//
// TexturePVRNPOT4444
//
//------------------------------------------------------------------
void TexturePVRNPOT4444::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();

    auto img = Sprite::create("Images/grossini_pvr_rgba4444.pvr");
    if ( img )
    {
        img->setPosition(Point( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVRNPOT4444::title()
{
    return "PVR RGBA4 + NPOT texture";
}

std::string TexturePVRNPOT4444::subtitle()
{
    return "Loading a 81x121 RGBA4444 texture.";
}

//------------------------------------------------------------------
//
// TexturePVRNPOT8888
//
//------------------------------------------------------------------
void TexturePVRNPOT8888::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    auto img = Sprite::create("Images/grossini_pvr_rgba8888.pvr");
    if( img )
    {
        img->setPosition(Point( s.width/2.0f, s.height/2.0f));
        addChild(img);
    }
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePVRNPOT8888::title()
{
    return "PVR RGBA8 + NPOT texture";
}

std::string TexturePVRNPOT8888::subtitle()
{
    return "Loading a 81x121 RGBA8888 texture.";
}

//------------------------------------------------------------------
//
// TextureAlias
//
//------------------------------------------------------------------
void TextureAlias::onEnter()
{
    TextureDemo::onEnter();
    auto s = Director::getInstance()->getWinSize();
    
    //
    // Sprite 1: GL_LINEAR
    //
    // Default filter is GL_LINEAR
    
    auto sprite = Sprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(Point( s.width/3.0f, s.height/2.0f));
    addChild(sprite);
    
    // this is the default filterting
    sprite->getTexture()->setAntiAliasTexParameters();
    
    //
    // Sprite 1: GL_NEAREST
    //    
    
    auto sprite2 = Sprite::create("Images/grossinis_sister2.png");
    sprite2->setPosition(Point( 2*s.width/3.0f, s.height/2.0f));
    addChild(sprite2);
    
    // Use Nearest in this one
    sprite2->getTexture()->setAliasTexParameters();
        
    // scale them to show
    auto sc = ScaleBy::create(3, 8.0f);
    auto sc_back = sc->reverse();
    auto scaleforever = RepeatForever::create(Sequence::create(sc, sc_back, NULL));
    auto scaleToo = scaleforever->clone();

    sprite2->runAction(scaleforever);
    sprite->runAction(scaleToo);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TextureAlias::title()
{
    return "AntiAlias / Alias textures";
}

std::string TextureAlias::subtitle()
{
    return "Left image is antialiased. Right image is aliases";
}

//------------------------------------------------------------------
//
// TexturePixelFormat
//
//------------------------------------------------------------------
void TexturePixelFormat::onEnter()
{
    //
    // This example displays 1 png images 4 times.
    // Each time the image is generated using:
    // 1- 32-bit RGBA8
    // 2- 16-bit RGBA4
    // 3- 16-bit RGB5A1
    // 4- 16-bit RGB565
    TextureDemo::onEnter();
        
    auto s = Director::getInstance()->getWinSize();

    auto background = LayerColor::create(Color4B(128,128,128,255), s.width, s.height);
    addChild(background, -1);
    
    // RGBA 8888 image (32-bit)
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
    auto sprite1 = Sprite::create("Images/test-rgba1.png");
    sprite1->setPosition(Point(1*s.width/7, s.height/2+32));
    addChild(sprite1, 0);

    // remove texture from texture manager    
    Director::getInstance()->getTextureCache()->removeTexture(sprite1->getTexture());

    // RGBA 4444 image (16-bit)
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
    auto sprite2 = Sprite::create("Images/test-rgba1.png");
    sprite2->setPosition(Point(2*s.width/7, s.height/2-32));
    addChild(sprite2, 0);

    // remove texture from texture manager    
    Director::getInstance()->getTextureCache()->removeTexture(sprite2->getTexture());

    // RGB5A1 image (16-bit)
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB5A1);
    auto sprite3 = Sprite::create("Images/test-rgba1.png");
    sprite3->setPosition(Point(3*s.width/7, s.height/2+32));
    addChild(sprite3, 0);

    // remove texture from texture manager    
    Director::getInstance()->getTextureCache()->removeTexture(sprite3->getTexture());

    // RGB888 image
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB888);
    auto sprite4 = Sprite::create("Images/test-rgba1.png");
    sprite4->setPosition(Point(4*s.width/7, s.height/2-32));
    addChild(sprite4, 0);

    // remove texture from texture manager    
    Director::getInstance()->getTextureCache()->removeTexture(sprite4->getTexture());

    // RGB565 image (16-bit)
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB565);
    auto sprite5 = Sprite::create("Images/test-rgba1.png");
    sprite5->setPosition(Point(5*s.width/7, s.height/2+32));
    addChild(sprite5, 0);

    // remove texture from texture manager    
    Director::getInstance()->getTextureCache()->removeTexture(sprite5->getTexture());

    // A8 image (8-bit)
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::A8);
    auto sprite6 = Sprite::create("Images/test-rgba1.png");
    sprite6->setPosition(Point(6*s.width/7, s.height/2-32));
    addChild(sprite6, 0);
    
    // remove texture from texture manager    
    Director::getInstance()->getTextureCache()->removeTexture(sprite6->getTexture());

    auto fadeout = FadeOut::create(2);
    auto fadein  = FadeIn::create(2);
    auto seq = Sequence::create(DelayTime::create(2), fadeout, fadein, NULL);
    auto seq_4ever = RepeatForever::create(seq);
    auto seq_4ever2 = seq_4ever->clone();
    auto seq_4ever3 = seq_4ever->clone();
    auto seq_4ever4 = seq_4ever->clone();
    auto seq_4ever5 = seq_4ever->clone();
    
    sprite1->runAction(seq_4ever);
    sprite2->runAction(seq_4ever2);
    sprite3->runAction(seq_4ever3);
    sprite4->runAction(seq_4ever4);
    sprite5->runAction(seq_4ever5);

    // restore default
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TexturePixelFormat::title()
{
    return "Texture Pixel Formats";
}

std::string TexturePixelFormat::subtitle()
{
    return "Textures: RGBA8888, RGBA4444, RGB5A1, RGB888, RGB565, A8";
}

//------------------------------------------------------------------
//
// TextureBlend
//
//------------------------------------------------------------------
void TextureBlend::onEnter()
{
    TextureDemo::onEnter();

    for( int i=0;i < 15;i++ )
    {
        // BOTTOM sprites have alpha pre-multiplied
        // they use by default GL_ONE, GL_ONE_MINUS_SRC_ALPHA
        auto cloud = Sprite::create("Images/test_blend.png");
        addChild(cloud, i+1, 100+i);
        cloud->setPosition(Point(50+25*i, 80));
        cloud->setBlendFunc( BlendFunc::ALPHA_PREMULTIPLIED );

        // CENTER sprites have also alpha pre-multiplied
        // they use by default GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA
        cloud = Sprite::create("Images/test_blend.png");
        addChild(cloud, i+1, 200+i);
        cloud->setPosition(Point(50+25*i, 160));
        BlendFunc blendFunc2 = { GL_ONE_MINUS_DST_COLOR, GL_ZERO };
        cloud->setBlendFunc(blendFunc2);

        // UPPER sprites are using custom blending function
        // You can set any blend function to your sprites
        cloud = Sprite::create("Images/test_blend.png");
        addChild(cloud, i+1, 200+i);
        cloud->setPosition(Point(50+25*i, 320-80));
        BlendFunc blendFunc3 = { GL_SRC_ALPHA, GL_ONE };
        cloud->setBlendFunc(blendFunc3);  // additive blending
    }
}

std::string TextureBlend::title()
{
    return "Texture Blending";
}

std::string TextureBlend::subtitle()
{
    return "Testing 3 different blending modes";
}


//------------------------------------------------------------------
//
// TextureAsync
//
//------------------------------------------------------------------

void TextureAsync::onEnter()
{
    TextureDemo::onEnter();

    _imageOffset = 0;

    auto size = Director::getInstance()->getWinSize();

    auto label = LabelTTF::create("Loading...", "Marker Felt", 32);
    label->setPosition(Point( size.width/2, size.height/2));
    addChild(label, 10);

    auto scale = ScaleBy::create(0.3f, 2);
    auto scale_back = scale->reverse();
    auto seq = Sequence::create(scale, scale_back, NULL);
    label->runAction(RepeatForever::create(seq));

    scheduleOnce(schedule_selector(TextureAsync::loadImages), 1.0f);
}

TextureAsync::~TextureAsync()
{
    Director::getInstance()->getTextureCache()->removeAllTextures();
}

void TextureAsync::loadImages(float dt)
{
    for( int i=0;i < 8;i++) {
        for( int j=0;j < 8; j++) {
            char szSpriteName[100] = {0};
            sprintf(szSpriteName, "Images/sprites_test/sprite-%d-%d.png", i, j);
            Director::getInstance()->getTextureCache()->addImageAsync(szSpriteName,this, callfuncO_selector(TextureAsync::imageLoaded));
        }
    }

    Director::getInstance()->getTextureCache()->addImageAsync("Images/background1.jpg",this, callfuncO_selector(TextureAsync::imageLoaded));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/background2.jpg",this, callfuncO_selector(TextureAsync::imageLoaded));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/background.png",this, callfuncO_selector(TextureAsync::imageLoaded));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/atlastest.png",this, callfuncO_selector(TextureAsync::imageLoaded));
    Director::getInstance()->getTextureCache()->addImageAsync("Images/grossini_dance_atlas.png",this, callfuncO_selector(TextureAsync::imageLoaded));
}


void TextureAsync::imageLoaded(Object* pObj)
{
    auto tex = static_cast<Texture2D*>(pObj);
    auto director = Director::getInstance();

    //CCASSERT( [NSThread currentThread] == [director runningThread], @"FAIL. Callback should be on cocos2d thread");

    // IMPORTANT: The order on the callback is not guaranteed. Don't depend on the callback

    // This test just creates a sprite based on the Texture

    auto sprite = Sprite::createWithTexture(tex);
    sprite->setAnchorPoint(Point(0,0));
    addChild(sprite, -1);

    auto size = director->getWinSize();
    int i = _imageOffset * 32;
    sprite->setPosition(Point( i % (int)size.width, (i / (int)size.width) * 32 ));

    _imageOffset++;

    log("Image loaded: %p", tex);
}

std::string TextureAsync::title()
{
    return "Texture Async Load";
}

std::string TextureAsync::subtitle()
{
    return "Textures should load while an animation is being run";
}


//------------------------------------------------------------------
//
// TextureGlClamp
//
//------------------------------------------------------------------
void TextureGlClamp::onEnter()
{
    TextureDemo::onEnter();

    auto size = Director::getInstance()->getWinSize();

    // The .png image MUST be power of 2 in order to create a continue effect.
    // eg: 32x64, 512x128, 256x1024, 64x64, etc..
    auto sprite = Sprite::create("Images/pattern1.png", Rect(0,0,512,256));
    addChild(sprite, -1, kTagSprite1);
    sprite->setPosition(Point(size.width/2,size.height/2));
    Texture2D::TexParams params = {GL_LINEAR,GL_LINEAR,GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
    sprite->getTexture()->setTexParameters(params);

    auto rotate = RotateBy::create(4, 360);
    sprite->runAction(rotate);
    auto scale = ScaleBy::create(2, 0.04f);
    auto scaleBack = scale->reverse();
    auto seq = Sequence::create(scale, scaleBack, NULL);
    sprite->runAction(seq);
}

std::string TextureGlClamp::title()
{
    return "Texture GL_CLAMP";
}

TextureGlClamp::~TextureGlClamp()
{
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

//------------------------------------------------------------------
//
// TextureGlRepeat
//
//------------------------------------------------------------------
void TextureGlRepeat::onEnter()
{
    TextureDemo::onEnter();

    auto size = Director::getInstance()->getWinSize();
    
    // The .png image MUST be power of 2 in order to create a continue effect.
    // eg: 32x64, 512x128, 256x1024, 64x64, etc..
    auto sprite = Sprite::create("Images/pattern1.png", Rect(0, 0, 4096, 4096));
    addChild(sprite, -1, kTagSprite1);
    sprite->setPosition(Point(size.width/2,size.height/2));
    Texture2D::TexParams params = {GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
    sprite->getTexture()->setTexParameters(params);
    
    auto rotate = RotateBy::create(4, 360);
    sprite->runAction(rotate);
    auto scale = ScaleBy::create(2, 0.04f);
    auto scaleBack = scale->reverse();
    auto seq = Sequence::create(scale, scaleBack, NULL);
    sprite->runAction(seq);
}

std::string TextureGlRepeat::title()
{
    return "Texture GL_REPEAT";
}

TextureGlRepeat::~TextureGlRepeat()
{
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

//------------------------------------------------------------------
//
// TextureSizeTest
//
//------------------------------------------------------------------
void TextureSizeTest::onEnter()
{
    TextureDemo::onEnter();
    Sprite *sprite = NULL;
    
    log("Loading 512x512 image...");
    sprite = Sprite::create("Images/texture512x512.png");
    if( sprite )
        log("OK");
    else
        log("Error");

    log("Loading 1024x1024 image...");
    sprite = Sprite::create("Images/texture1024x1024.png");
    if( sprite )
        log("OK");
    else
        log("Error");
//     @todo
//     log("Loading 2048x2048 image...");
//     sprite = Sprite::create("Images/texture2048x2048.png");
//     if( sprite )
//         log("OK");
//     else
//         log("Error");
//     
//     log("Loading 4096x4096 image...");
//     sprite = Sprite::create("Images/texture4096x4096.png");
//     if( sprite )
//         log("OK");
//     else
//         log("Error");
}

std::string TextureSizeTest::title()
{
    return "Different Texture Sizes";
}

std::string TextureSizeTest::subtitle()
{
    return "512x512, 1024x1024. See the console.";
}

//------------------------------------------------------------------
//
// TextureCache1
//
//------------------------------------------------------------------
void TextureCache1::onEnter()
{
    TextureDemo::onEnter();

    auto s = Director::getInstance()->getWinSize();
    
    Sprite *sprite;

    sprite = Sprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(Point(s.width/5*1, s.height/2));
    sprite->getTexture()->setAliasTexParameters();
    sprite->setScale(2);
    addChild(sprite);

    Director::getInstance()->getTextureCache()->removeTexture(sprite->getTexture());
    
    sprite = Sprite::create("Images/grossinis_sister1.png");
    sprite->setPosition(Point(s.width/5*2, s.height/2));
    sprite->getTexture()->setAntiAliasTexParameters();
    sprite->setScale(2);
    addChild(sprite);

    // 2nd set of sprites
    
    sprite = Sprite::create("Images/grossinis_sister2.png");
    sprite->setPosition(Point(s.width/5*3, s.height/2));
    sprite->getTexture()->setAliasTexParameters();
    sprite->setScale(2);
    addChild(sprite);
    
    Director::getInstance()->getTextureCache()->removeTextureForKey("Images/grossinis_sister2.png");

    sprite = Sprite::create("Images/grossinis_sister2.png");
    sprite->setPosition(Point(s.width/5*4, s.height/2));
    sprite->getTexture()->setAntiAliasTexParameters();
    sprite->setScale(2);
    addChild(sprite);
}

std::string TextureCache1::title()
{
    return "CCTextureCache: remove";
}

std::string TextureCache1::subtitle()
{
    return "4 images should appear: alias, antialias, alias, antilias";
}

// TextureDrawAtPoint
void TextureDrawAtPoint::onEnter()
{
    TextureDemo::onEnter();

    _tex1 = Director::getInstance()->getTextureCache()->addImage("Images/grossinis_sister1.png");
    _Tex2F = Director::getInstance()->getTextureCache()->addImage("Images/grossinis_sister2.png");

    _tex1->retain();
    _Tex2F->retain();
}

TextureDrawAtPoint::~TextureDrawAtPoint()
{
    _tex1->release();
    _Tex2F->release();
}

std::string TextureDrawAtPoint::title()
{
    return "CCTexture2D: drawAtPoint";
}

std::string TextureDrawAtPoint::subtitle()
{
    return "draws 2 textures using drawAtPoint";
}

void TextureDrawAtPoint::draw()
{
    TextureDemo::draw();

    auto s = Director::getInstance()->getWinSize();

    _tex1->drawAtPoint(Point(s.width/2-50, s.height/2 - 50));
    _Tex2F->drawAtPoint(Point(s.width/2+50, s.height/2 - 50));

}

// TextureDrawInRect

void TextureDrawInRect::onEnter()
{
    TextureDemo::onEnter();
    _tex1 = Director::getInstance()->getTextureCache()->addImage("Images/grossinis_sister1.png");
    _Tex2F = Director::getInstance()->getTextureCache()->addImage("Images/grossinis_sister2.png");

    _tex1->retain();
    _Tex2F->retain();
}

TextureDrawInRect::~TextureDrawInRect()
{
    _tex1->release();
    _Tex2F->release();
}

void TextureDrawInRect::draw()
{
    TextureDemo::draw();

    auto s = Director::getInstance()->getWinSize();

    auto rect1 = Rect( s.width/2 - 80, 20, _tex1->getContentSize().width * 0.5f, _tex1->getContentSize().height *2 );
    auto rect2 = Rect( s.width/2 + 80, s.height/2, _tex1->getContentSize().width * 2, _tex1->getContentSize().height * 0.5f );

    _tex1->drawInRect(rect1);
    _Tex2F->drawInRect(rect2);

}

std::string TextureDrawInRect::title()
{
    return "CCTexture2D: drawInRect";
}

std::string TextureDrawInRect::subtitle()
{
    return "draws 2 textures using drawInRect";
}

//------------------------------------------------------------------
//
// TextureTestScene
//
//------------------------------------------------------------------
void TextureTestScene::runThisTest()
{
    auto layer = nextTextureTest();
    addChild(layer);
    Director::getInstance()->replaceScene(this);
}

//------------------------------------------------------------------
//
// TextureMemoryAlloc
//
//------------------------------------------------------------------
void TextureMemoryAlloc::onEnter()
{
    TextureDemo::onEnter();
    _background = NULL;
    
    MenuItemFont::setFontSize(24);
    
    auto item1 = MenuItemFont::create("PNG", CC_CALLBACK_1(TextureMemoryAlloc::updateImage, this));
    item1->setTag(0);
    
    auto item2 = MenuItemFont::create("RGBA8", CC_CALLBACK_1(TextureMemoryAlloc::updateImage, this));
    item2->setTag(1);
    
    auto item3 = MenuItemFont::create("RGB8", CC_CALLBACK_1(TextureMemoryAlloc::updateImage, this));
    item3->setTag(2);
    
    auto item4 = MenuItemFont::create("RGBA4", CC_CALLBACK_1(TextureMemoryAlloc::updateImage, this));
    item4->setTag(3);
    
    auto item5 = MenuItemFont::create("A8", CC_CALLBACK_1(TextureMemoryAlloc::updateImage, this));
    item5->setTag(4);
    
    auto menu = Menu::create(item1, item2, item3, item4, item5, NULL);
    menu->alignItemsHorizontally();
    
    addChild(menu);
    
    auto warmup = MenuItemFont::create("warm up texture", CC_CALLBACK_1(TextureMemoryAlloc::changeBackgroundVisible, this));
    
    auto menu2 = Menu::create(warmup, NULL);

    menu2->alignItemsHorizontally();
    
    addChild(menu2);
    auto s = Director::getInstance()->getWinSize();
    
    menu2->setPosition(Point(s.width/2, s.height/4));
}

void TextureMemoryAlloc::changeBackgroundVisible(cocos2d::Object *sender)
{
    if (_background)
    {
        _background->setVisible(true);
    }
}

void TextureMemoryAlloc::updateImage(cocos2d::Object *sender)
{
    if (_background)
    {
        _background->removeFromParentAndCleanup(true);
    }
    
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
	
    int tag = ((Node*)sender)->getTag();
	string file;
	switch (tag) 
    {
		case 0:
			file = "Images/test_1021x1024.png";
			break;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            // android can not pack .gz file into apk file
        case 1:
            file = "Images/test_1021x1024_rgba8888.pvr";
            break;
        case 2:
            file = "Images/test_1021x1024_rgb888.pvr";
            break;
        case 3:
            file = "Images/test_1021x1024_rgba4444.pvr";
            break;
        case 4:
            file = "Images/test_1021x1024_a8.pvr";
            break;
#else
		case 1:
			file = "Images/test_1021x1024_rgba8888.pvr.gz";
			break;
		case 2:
			file = "Images/test_1021x1024_rgb888.pvr.gz";
			break;
		case 3:
			file = "Images/test_1021x1024_rgba4444.pvr.gz";
			break;
		case 4:
			file = "Images/test_1021x1024_a8.pvr.gz";
			break;
#endif
	}

    _background = Sprite::create(file.c_str());
    addChild(_background, -10);
	
    _background->setVisible(false);
    
    auto s = Director::getInstance()->getWinSize();
    _background->setPosition(Point(s.width/2, s.height/2));
}

string TextureMemoryAlloc::title()
{
    return "Texture memory";
}

string TextureMemoryAlloc::subtitle()
{
    return "Testing Texture Memory allocation. Use Instruments + VM Tracker";
}

// TexturePVRv3Premult
TexturePVRv3Premult::TexturePVRv3Premult()
{
    auto size = Director::getInstance()->getWinSize();
        
    auto background = LayerColor::create(Color4B(128,128,128,255), size.width, size.height);
    addChild(background, -1);
    
    
    // PVR premultiplied
    auto pvr1 = Sprite::create("Images/grossinis_sister1-testalpha_premult.pvr");
    addChild(pvr1, 0);
    pvr1->setPosition(Point(size.width/4*1, size.height/2));
    transformSprite(pvr1);
    
    // PVR non-premultiplied
    auto pvr2 = Sprite::create("Images/grossinis_sister1-testalpha_nopremult.pvr");
    addChild(pvr2, 0);
    pvr2->setPosition(Point(size.width/4*2, size.height/2));
    transformSprite(pvr2);
    
    // PNG
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
    Director::getInstance()->getTextureCache()->removeTextureForKey("Images/grossinis_sister1-testalpha.png");
    auto png = Sprite::create("Images/grossinis_sister1-testalpha.png");
    addChild(png, 0);
    png->setPosition(Point(size.width/4*3, size.height/2));
    transformSprite(png);
}

std::string TexturePVRv3Premult::title()
{
    return "PVRv3 Premult Flag";
}

std::string TexturePVRv3Premult::subtitle()
{
    return "All images should look exactly the same";
}

void TexturePVRv3Premult::transformSprite(cocos2d::Sprite *sprite)
{
    auto fade = FadeOut::create(2);
    auto dl = DelayTime::create(2);
    auto fadein = fade->reverse();
    auto seq = Sequence::create(fade, fadein, dl, NULL);
    auto repeat = RepeatForever::create(seq);
    sprite->runAction(repeat);
}

// Implementation of ETC1

/*
class TextureETC1 : public TextureDemo
{
public:
    TextureETC1();
    
    virtual std::string title();
    virtual std::string subtitle();
};
 */

TextureETC1::TextureETC1()
{
    auto sprite = Sprite::create("Images/ETC1.pkm");
    
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Point(size.width/2, size.height/2));
    
    addChild(sprite);
}

std::string TextureETC1::title()
{
    return "ETC1 texture";
}

std::string TextureETC1::subtitle()
{
    return "only supported on android";
}

//Implement of S3TC Dxt1
TextureS3TCDxt1::TextureS3TCDxt1()
{
    auto sprite = Sprite::create("Images/test_256x256_s3tc_dxt1_mipmaps.dds");
    //auto sprite = Sprite::create("Images/water_2_dxt1.dds");
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Point(size.width / 2, size.height / 2));
    
    addChild(sprite);
}
std::string TextureS3TCDxt1::title()
{
    return "S3TC texture test#1";
}
std::string TextureS3TCDxt1::subtitle()
{
    return "S3TC dxt1 decode,one bit for Alpha";
}

//Implement of S3TC Dxt3
TextureS3TCDxt3::TextureS3TCDxt3()
{
    auto sprite = Sprite::create("Images/test_256x256_s3tc_dxt3_mipmaps.dds");
    //auto sprite = Sprite::create("Images/water_2_dxt3.dds");
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Point(size.width / 2, size.height / 2));
    
    addChild(sprite);
}
std::string TextureS3TCDxt3::title()
{
    return "S3TC texture test#2";
}
std::string TextureS3TCDxt3::subtitle()
{
    return "S3TC dxt3 decode";
}

//Implement of S3TC Dxt5
TextureS3TCDxt5::TextureS3TCDxt5()
{
    auto sprite = Sprite::create("Images/test_256x256_s3tc_dxt5_mipmaps.dds");
    //auto sprite = Sprite::create("Images/water_2_dxt5.dds");
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Point(size.width / 2, size.height / 2));
    
    addChild(sprite);
}
std::string TextureS3TCDxt5::title()
{
    return "S3TC texture test#3";
}
std::string TextureS3TCDxt5::subtitle()
{
    return "S3TC dxt5 decode";    
}

//Implement of ATITC
TextureATITCRGB::TextureATITCRGB()
{
    auto sprite = Sprite::create("Images/test_256x256_ATC_RGB_mipmaps.ktx");
    
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Point(size.width / 2, size.height / 2));

    addChild(sprite);
}
std::string TextureATITCRGB::title()
{
    return "ATITC texture (*.ktx file) test#1";
}
std::string TextureATITCRGB::subtitle()
{
    return "ATITC RGB (no Alpha channel) compressed texture test";
}

TextureATITCExplicit::TextureATITCExplicit()
{
    auto sprite = Sprite::create("Images/test_256x256_ATC_RGBA_Explicit_mipmaps.ktx");
    
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Point(size.width / 2, size.height / 2));
    
    addChild(sprite);
}
std::string TextureATITCExplicit::title()
{
    return "ATITC texture (*.ktx file) test#2";
}
std::string TextureATITCExplicit::subtitle()
{
    return "ATITC RGBA explicit Alpha compressed texture test";
}

TextureATITCInterpolated::TextureATITCInterpolated()
{
    auto sprite = Sprite::create("Images/test_256x256_ATC_RGBA_Interpolated_mipmaps.ktx");
    
    auto size = Director::getInstance()->getWinSize();
    sprite->setPosition(Point(size.width / 2, size.height /2));

    addChild(sprite);
}
std::string TextureATITCInterpolated::title()
{
    return "ATITC texture (*.ktx file) test#3";
}
std::string TextureATITCInterpolated::subtitle()
{
    return "ATITC RGBA Interpolated Alpha comrpessed texture test";
}

static void addImageToDemo(TextureDemo& demo, float x, float y, const char* path, Texture2D::PixelFormat format)
{
    Texture2D::setDefaultAlphaPixelFormat(format);
    auto sprite = Sprite::create(path);
    sprite->setPosition(Point(x, y));
    demo.addChild(sprite, 0);
    
    //remove texture from texture manager
    Director::getInstance()->getTextureCache()->removeTexture(sprite->getTexture());
}

//TextureConvertRGB888
void TextureConvertRGB888::onEnter()
{
    TextureDemo::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    
    auto background = LayerColor::create(Color4B(255,0,0,255), s.width, s.height);
    addChild(background, -1);
    
    const char* img = "Images/test_image_rgb888.png";
    addImageToDemo(*this, 1*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA8888);
    addImageToDemo(*this, 2*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB888);
    addImageToDemo(*this, 3*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGB565);
    addImageToDemo(*this, 4*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::A8);
    addImageToDemo(*this, 5*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::I8);
    addImageToDemo(*this, 6*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::AI88);
    addImageToDemo(*this, 7*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA4444);
    addImageToDemo(*this, 8*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB5A1);
    
    // restore default
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TextureConvertRGB888::title()
{
    return "RGB888 convert test";
}

std::string TextureConvertRGB888::subtitle()
{
    return "RGBA8888,RGB888,RGB565,A8,I8,AI88,RGBA4444,RGB5A1";
}
//TextureConvertRGBA8888
void TextureConvertRGBA8888::onEnter()
{
    TextureDemo::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    
    auto background = LayerColor::create(Color4B(255,0,0,255), s.width, s.height);
    addChild(background, -1);
    
    const char* img = "Images/test_image_rgba8888.png";
    addImageToDemo(*this, 1*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA8888);
    addImageToDemo(*this, 2*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB888);
    addImageToDemo(*this, 3*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGB565);
    addImageToDemo(*this, 4*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::A8);
    addImageToDemo(*this, 5*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::I8);
    addImageToDemo(*this, 6*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::AI88);
    addImageToDemo(*this, 7*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA4444);
    addImageToDemo(*this, 8*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB5A1);
    
    // restore default
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TextureConvertRGBA8888::title()
{
    return "RGBA8888 convert test";
}

std::string TextureConvertRGBA8888::subtitle()
{
    return "RGBA8888,RGB888,RGB565,A8,I8,AI88,RGBA4444,RGB5A1";
}
//TextureConvertI8
void TextureConvertI8::onEnter()
{
    TextureDemo::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    
    auto background = LayerColor::create(Color4B(255,0,0,255), s.width, s.height);
    addChild(background, -1);
    
    const char* img = "Images/test_image_i8.png";
    addImageToDemo(*this, 1*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA8888);
    addImageToDemo(*this, 2*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB888);
    addImageToDemo(*this, 3*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGB565);
    addImageToDemo(*this, 4*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::A8);
    addImageToDemo(*this, 5*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::I8);
    addImageToDemo(*this, 6*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::AI88);
    addImageToDemo(*this, 7*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA4444);
    addImageToDemo(*this, 8*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB5A1);
    
    // restore default
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TextureConvertI8::title()
{
    return "I8 convert test";
}

std::string TextureConvertI8::subtitle()
{
    return "RGBA8888,RGB888,RGB565,A8,I8,AI88,RGBA4444,RGB5A1";
}
//TextureConvertAI88
void TextureConvertAI88::onEnter()
{
    TextureDemo::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    
    auto background = LayerColor::create(Color4B(255,0,0,255), s.width, s.height);
    addChild(background, -1);
    
    const char* img = "Images/test_image_ai88.png";
    addImageToDemo(*this, 1*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA8888);
    addImageToDemo(*this, 2*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB888);
    addImageToDemo(*this, 3*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGB565);
    addImageToDemo(*this, 4*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::A8);
    addImageToDemo(*this, 5*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::I8);
    addImageToDemo(*this, 6*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::AI88);
    addImageToDemo(*this, 7*s.width/9, s.height/2+32, img, Texture2D::PixelFormat::RGBA4444);
    addImageToDemo(*this, 8*s.width/9, s.height/2-32, img, Texture2D::PixelFormat::RGB5A1);
    
    // restore default
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);
    Director::getInstance()->getTextureCache()->dumpCachedTextureInfo();
}

std::string TextureConvertAI88::title()
{
    return "AI88 convert test";
}

std::string TextureConvertAI88::subtitle()
{
    return "RGBA8888,RGB888,RGB565,A8,I8,AI88,RGBA4444,RGB5A1";
}
