@echo off
color 0A
echo.
echo            ================================
echo             ��ѡ��Ҫ���еĲ�����Ȼ�󰴻س�
echo            ================================
echo.
echo.             1.����ȫ��������(DEBUG)
echo.             
echo.             2.����ȫ��������(RELEASE)
echo.     
echo.             3.�ر�ȫ��������
echo.
echo.             4.�˳������
echo.
echo.
set DebugDir=%cd%\Server\Debug\
set ReleaseDir=%cd%\Server\Release\
echo.
echo Debug = %DebugDir%
echo Release= %ReleaseDir%
echo.


:cho
set choice=
set /p choice=          ��ѡ��:
IF NOT "%choice%"=="" SET choice=%choice:~0,1%
if /i "%choice%"=="1" start /D %DebugDir% /MIN %DebugDir%CenterServer.exe & start /D %DebugDir% /MIN %DebugDir%LoginServer.exe & start /D %DebugDir% /MIN %DebugDir%ProxyServer.exe & start /D %DebugDir% /MIN %DebugDir%DBServer.exe & start /D %DebugDir% /MIN %DebugDir%GameServer.exe
if /i "%choice%"=="2" start /D %DebugDir% /MIN %DebugDir%CenterServer.exe & start /D %DebugDir% /MIN %DebugDir%LoginServer.exe & start /D %DebugDir% /MIN %DebugDir%ProxyServer.exe & start /D %DebugDir% /MIN %DebugDir%DBServer.exe & start /D %DebugDir% /MIN %DebugDir%GameServer.exe
if /i "%choice%"=="3" taskkill /im CenterServer.exe & taskkill /im LoginServer.exe & taskkill /im ProxyServer.exe & taskkill /im DBServer.exe & taskkill /im GameServer.exe
if /i "%choice%"=="4" exit
goto cho


