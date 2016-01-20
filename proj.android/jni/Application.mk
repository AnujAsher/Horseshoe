APP_STL := gnustl_static

APP_CPPFLAGS := -frtti -std=c++11 -fsigned-char -Wno-extern-c-compat -DCC_USE_PHYSICS=0 -DCC_USE_3D_PHYSICS=0 -DCC_ENABLE_BULLET_INTEGRATION=0 -DCC_ENABLE_BOX2D_INTEGRATION=0 -DCC_ENABLE_CHIPMUNK_INTEGRATION=0 -DCC_USE_NAVMESH=0 -DCC_USE_TIFF=0 -DCC_USE_WEBP=0 -DCC_ENABLE_SCRIPT_BINDING=0
APP_LDFLAGS := -latomic


ifeq ($(NDK_DEBUG),1)
  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif
