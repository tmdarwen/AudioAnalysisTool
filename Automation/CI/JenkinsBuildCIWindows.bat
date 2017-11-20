call "%VisualStudioPath%\vcvarsall.bat" amd64
cd %WORKSPACE%
mkdir AudioAnalysisToolBuilt
cd AudioAnalysisToolBuilt
cmake -G "%CMakeGeneratorString%" -D CMAKE_PREFIX_PATH="%QtMSVCPath%" ../Source
devenv AudioAnalysisTool.sln /Build Debug
devenv AudioAnalysisTool.sln /Build Release
