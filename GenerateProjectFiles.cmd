
rmdir /s /q _cmake
mkdir _cmake
cd _cmake

cmake .. -Wno-dev -G "Visual Studio 16 2019"^
 -DBISON_EXECUTABLE="C:/dev/winflexbison/_cmake/bison/Release/win_bison.exe"^
 -DFLEX_EXECUTABLE="C:/dev/winflexbison/_cmake/flex/Release/win_flex.exe"^
 -DFLEX_INCLUDE_DIR="C:/dev/winflexbison/flex/src/"^
 -DFL_LIBRARY="C:/dev/winflexbison/_cmake/flex/Release/fl.lib"^
 -DBOOST_ROOT="C:/dev/boost_1_80_0"^
 -DBoost_INCLUDE_DIR="C:/dev/boost_1_80_0/"^
 -DBoost_LIBRARY_DIR_RELEASE="C:/dev/boost_1_80_0/stage/lib"^
 -DBoost_FILESYSTEM_LIBRARY_RELEASE="C:/dev/boost_1_80_0/stage/lib/libboost_filesystem-vc142-mt-x64-1_80.lib"^
 -DSDL2_DIR="C:/_ProjectD/SDL2-2.0.22"^
 -DSDL2_INCLUDE_DIR="C:/_ProjectD/SDL2-2.0.22/include/"^
 -DSDL2_LIBRARY="C:/_ProjectD/SDL2-2.0.22/lib/x64/SDL2.lib"^
 -DSDL2MAIN_LIBRARY="C:/_ProjectD/SDL2-2.0.22/lib/x64/SDL2main.lib"^
 -DSDL2_IMAGE_INCLUDE_DIR="C:/_ProjectD/SDL2-2.0.22/include"^
 -DSDL2_IMAGE_LIBRARY="C:/_ProjectD/SDL2-2.0.22/lib/x64/SDL2_image.lib"

cd ..
