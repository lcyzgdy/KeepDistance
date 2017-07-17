LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/AirPlaneScene.cpp \
                   ../../Classes/BackgroundLayer.cpp \
                   ../../Classes/BackgroundSprite.cpp \
                   ../../Classes/Background.cpp \
                   ../../Classes/Bomb.cpp \
                   ../../Classes/BallSprite.cpp \
                   ../../Classes/BulletSprite.cpp \
                   ../../Classes/CastScene.cpp \
                   ../../Classes/EnemyLayer.cpp \
                   ../../Classes/EnemyPlaneSprite.cpp \
                   ../../Classes/EnemySprite.cpp \
                   ../../Classes/GameOverScene.cpp \
                   ../../Classes/LoadingScene.cpp \
                   ../../Classes/NetworkLayer.cpp \
                   ../../Classes/PauseScene.cpp \
                   ../../Classes/PhysicsLayer.cpp \
                   ../../Classes/PlaneSprite.cpp \
                   ../../Classes/PlayerLayer.cpp \
                   ../../Classes/RobotAnim.cpp \
                   ../../Classes/SpriteWithPhysicsAndAnimation.cpp \
                   ../../Classes/ToolLayer.cpp \
                   ../../Classes/ToolSprite.cpp \
                   ../../Classes/UILayer.cpp \
                   ../../Classes/Welcome_Scene.cpp \
                   ../../Classes/Background_end.cpp \
                   ../../Classes/Closing_item.cpp \
                   ../../Classes/Begining_item.cpp \
                   ../../Classes/HighScore_Scene.cpp \
                   ../../Classes/HighScore_item.cpp \
                   ../../Classes/Switch_Scene.cpp \
                   ../../Classes/Switch_item.cpp \
                   ../../Classes/SingleCastScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
