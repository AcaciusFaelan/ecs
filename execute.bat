@echo off
setlocal enabledelayedexpansion

REM CMake Build Script for Windows
REM Usage: execute.bat [command] [executable_name]

set "BUILD_DIR=build"
set "EXECUTABLE_NAME="

REM Parse command line arguments
set "COMMAND=%~1"
if "%COMMAND%"=="" set "COMMAND=run"

REM Check for executable name argument
if not "%~2"=="" (
    set "EXECUTABLE_NAME=%~2"
)

REM Main script logic
if /i "%COMMAND%"=="run" goto run_all
if /i "%COMMAND%"=="generate" goto generate_build_files
if /i "%COMMAND%"=="gen" goto generate_build_files
if /i "%COMMAND%"=="build" goto build_app
if /i "%COMMAND%"=="clean" goto clean_build
if /i "%COMMAND%"=="execute" goto run_executable
if /i "%COMMAND%"=="exec" goto run_executable
if /i "%COMMAND%"=="help" goto show_help
if /i "%COMMAND%"=="-h" goto show_help
if /i "%COMMAND%"=="--help" goto show_help

call :print_error "Unknown command: %COMMAND%"
echo Use 'execute.bat help' for usage information
exit /b 1

:run_all
call :print_status "Starting complete build process..."
call :generate_build_files
if errorlevel 1 exit /b 1
call :build_app
if errorlevel 1 exit /b 1
call :run_executable
if errorlevel 1 exit /b 1
call :print_status "All steps completed successfully!"
goto :eof

:generate_build_files
call :print_status "Generating build files with CMake..."

if not exist "CMakeLists.txt" (
    call :print_error "CMakeLists.txt not found in current directory"
    exit /b 1
)

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"
cmake -G "Unix Makefiles" .. 
if errorlevel 1 (
    cd ..
    call :print_error "Failed to generate build files"
    exit /b 1
)
cd ..

if exist "%BUILD_DIR%\compile_commands.json" (
    copy /y "%BUILD_DIR%\compile_commands.json" . >nul
    call :print_status "Updated compile_commands.json for clangd"
)

call :print_status "Build files generated successfully"
goto :eof

:build_app
call :print_status "Building the application..."

if not exist "%BUILD_DIR%" (
    call :print_error "Build directory not found. Run generation first."
    exit /b 1
)

cmake --build "%BUILD_DIR%"
if errorlevel 1 (
    call :print_error "Build failed"
    exit /b 1
)

call :print_status "Build completed successfully"
goto :eof

:clean_build
call :print_status "Cleaning build directory..."

if exist "%BUILD_DIR%" (
    rmdir /s /q "%BUILD_DIR%"
    call :print_status "Build directory cleaned"
) else (
    call :print_warning "Build directory doesn't exist"
)
goto :eof

:run_executable
call :print_status "Running the executable..."

call :find_executable
if errorlevel 1 exit /b 1

if not exist "!EXE_PATH!" (
    call :print_error "Executable not found: !EXE_PATH!"
    exit /b 1
)

call :print_status "Executing: !EXE_PATH!"
echo ----------------------------------------
call "!EXE_PATH!"
if errorlevel 1 (
    call :print_error "Execution failed with exit code !errorlevel!"
    exit /b 1
)
echo ----------------------------------------
call :print_status "Execution completed successfully"
goto :eof

:find_executable
if not "%EXECUTABLE_NAME%"=="" (
    set "EXE_PATH=%BUILD_DIR%\%EXECUTABLE_NAME%"
    goto :eof
)

REM Try to find executable automatically
set "EXE_PATH="
set "EXE_COUNT=0"

for /r "%BUILD_DIR%" %%f in (*.exe) do (
    set "FILE_PATH=%%f"
    REM Skip CMake internal files
    echo !FILE_PATH! | findstr /i "CMakeFiles" >nul
    if errorlevel 1 (
        set /a EXE_COUNT+=1
        set "EXE_LIST_!EXE_COUNT!=%%f"
        set "EXE_NAME_!EXE_COUNT!=%%~nxf"
    )
)

if !EXE_COUNT! equ 0 (
    call :print_error "No executable found in %BUILD_DIR%"
    exit /b 1
)

if !EXE_COUNT! equ 1 (
    set "EXE_PATH=!EXE_LIST_1!"
    goto :eof
)

call :print_warning "Multiple executables found. Please select one:"
for /L %%i in (1,1,!EXE_COUNT!) do (
    echo   %%i. !EXE_NAME_%%i!
)

:ask_selection
set /p "SELECTION=Enter number (1-!EXE_COUNT!): "

REM Simple validation checking if the index variable exists
if not defined EXE_LIST_!SELECTION! (
    call :print_error "Invalid selection. Please try again."
    goto ask_selection
)

set "EXE_PATH=!EXE_LIST_!SELECTION!!"
goto :eof

:show_help
echo Usage: execute.bat [command] [executable_name]
echo.
echo Commands:
echo   run       Run all steps (generate, build, execute) [default]
echo   generate  Generate build files only
echo   build     Build the application only
echo   clean     Clean build directory
echo   execute   Run the executable only
echo   help      Show this help message
echo.
echo Arguments:
echo   executable_name  Optional name of the executable to run (for 'run' and 'execute' commands)
echo.
echo Environment variables:
echo   EXECUTABLE_NAME  Set the executable name manually
goto :eof

:print_status
echo [INFO] %~1
goto :eof

:print_warning
echo [WARNING] %~1
goto :eof

:print_error
echo [ERROR] %~1
goto :eof