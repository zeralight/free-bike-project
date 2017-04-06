ADD_CORE_FILES(CMakeLists.txt HeatMap.cpp)
INCLUDE_DIRECTORIES(${TulipCoreBuildInclude} ${TulipCoreInclude} ${TulipOGLInclude} ${TulipGUIInclude} ${CMAKE_CURRENT_BINARY_DIR} .)

##----------------------------------------------------------------------------------------------------------------------------


SET(HeatMap_SRCS
  HeatMap.cpp
)

ADD_LIBRARY(HeatMap-${TulipVersion} SHARED ${HeatMap_SRCS} ${HeatMap_UI_SRCS} ${HeatMap_MOC_SRCS})
TARGET_LINK_LIBRARIES(HeatMap-${TulipVersion} ${LibTulipCoreName} ${LibTulipGUIName})

##----------------------------------------------------------------------------------------------------------------------------
INSTALL_TULIP_PLUGIN(HeatMap-${TulipVersion} ${TulipPluginsInstallDir})
