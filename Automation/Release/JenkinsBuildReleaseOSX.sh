echo "Version number is ${Version}"
echo "Build number is ${BUILD_NUMBER}"

git checkout tags/v${Version}
if [ $? -ne 0 ]
then
	echo "Failed to checkout tag"
	exit 1
fi

mkdir ReleaseBuild
if [ $? -ne 0 ]
then
	echo "Failed to make ReleaseBuild directory"
	exit 1
fi

cd ReleaseBuild
if [ $? -ne 0 ]
then
	echo "Failed to change dir into ReleaseBuild"
	exit 1
fi

/usr/local/bin/cmake -D CMAKE_BUILD_TYPE=Release -D VERSION_NUMBER=${Version} -D BUILD_NUMBER=${BUILD_NUMBER} -D CMAKE_BUILD_TYPE=Release -D CMAKE_PREFIX_PATH="${QtPath}" -G "Xcode" ../Source
if [ $? -ne 0 ]
then
	echo "Executing cmake failed"
	exit 1
fi

xcodebuild -project AudioAnalysisTool.configuration Release
if [ $? -ne 0 ]
then
	echo "xcode build failed"
	exit 1
fi

zip -j AudioAnalysisTool.zip "${WORKSPACE}/ReleaseBuild/Release/AudioAnalysisTool"
if [ $? -ne 0 ]
then
	echo "Failed to zip AudioAnalysisTool"
	exit 1
fi

cp AudioAnalysisTool.zip "${ReleaseDestination}/AudioAnalysisTool-OSXIntel64-${Version}-${BUILD_NUMBER}.zip"
if [ $? -ne 0 ]
then
	echo "Failed to copy AudioAnalysisTool.zip to release directory"
	exit 1
fi

exit 0
