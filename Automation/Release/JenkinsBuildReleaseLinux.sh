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

cmake -D CMAKE_BUILD_TYPE=Release -D VERSION_NUMBER=${Version} -D BUILD_NUMBER=${BUILD_NUMBER} -G "Unix Makefiles" ../Source
if [ $? -ne 0 ]
then
	echo "Executing cmake failed"
	exit 1
fi

cmake --build .  # To compile
if [ $? -ne 0 ]
then
	echo "CMake --build failed"
	exit 1
fi

zip -j AudioAnalysisTool.zip "${WORKSPACE}/ReleaseBuild/Application/AudioAnalysisTool"
if [ $? -ne 0 ]
then
	echo "Failed to zip AudioAnalysisTool"
	exit 1
fi

cp AudioAnalysisTool.zip "${ReleaseDestination}/AudioAnalysisTool-Deb64-${Version}-${BUILD_NUMBER}.zip"
if [ $? -ne 0 ]
then
	echo "Failed to copy AudioAnalysisTool.zip to release directory"
	exit 1
fi

exit 0
