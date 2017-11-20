ECHO Building AudioAnalysisTool version number %Version% 
ECHO Build number is %BUILD_NUMBER%

call "%VisualStudioPath%\vcvarsall.bat" amd64

REM Switch to the tag
git checkout tags/v%Version%

REM Run CMake
echo "Creating build dir"
mkdir AudioAnalysisToolBuilt
echo "Accessing build dir"
cd AudioAnalysisToolBuilt
echo "Running cmake"
cmake -D VERSION_NUMBER=%Version% -D BUILD_NUMBER=%BUILD_NUMBER% -D CMAKE_PREFIX_PATH="%QtMSVCPath%" -G "%CMakeGeneratorString%" ..\Source
IF %ERRORLEVEL% NEQ 0 (
    ECHO CMake failed
    EXIT 1
)

REM Do the build
echo "Building release version of AudioAnalysisTool"
devenv AudioAnalysisTool.sln /Build Release
IF %ERRORLEVEL% NEQ 0 (
    ECHO The build failed    
    EXIT 1
)

REM Zip the executable
echo "7z" a -tzip AudioAnalysisTool.zip "%WORKSPACE%\AudioAnalysisToolBuilt\Application\Release\AudioAnalysisTool.exe" 
"7z" a -tzip AudioAnalysisTool.zip "%WORKSPACE%\AudioAnalysisToolBuilt\Release\AudioAnalysisTool.exe" 

IF %ERRORLEVEL% NEQ 0 (
    ECHO Zipping AudioAnalysisTool.exe failed
    EXIT 1
)

REM Copy the resulting installer to the Releases folder
echo copy AudioAnalysisTool.zip %ReleaseDestination%\AudioAnalysisTool-Win64-%Version%-%BUILD_NUMBER%.zip
copy AudioAnalysisTool.zip %ReleaseDestination%\AudioAnalysisTool-Win64-%Version%-%BUILD_NUMBER%.zip

IF %ERRORLEVEL% NEQ 0 (
    ECHO Copying AudioAnalysisTool.exe to release destination 
    EXIT 1
)

