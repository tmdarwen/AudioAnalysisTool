# Do a debug build
mkdir DebugBuild
cd DebugBuild
/usr/local/bin/cmake -G "Xcode" -D CMAKE_PREFIX_PATH="${QtPath}" -DCMAKE_BUILD_TYPE=Debug ../Source
xcodebuild -project AudioAnalysisTool.xcodeproj -configuration Debug

cd ..

# Do a releaase build
mkdir ReleaseBuild
cd ReleaseBuild
/usr/local/bin/cmake -G "Xcode" -D CMAKE_PREFIX_PATH="${QtPath}" -DCMAKE_BUILD_TYPE=Release ../Source
xcodebuild -project AudioAnalysisTool.xcodeproj -configuration Release
