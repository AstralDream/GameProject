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
:cho
set choice=
set /p choice=          ��ѡ��:
IF NOT "%choice%"=="" SET choice=%choice:~0,1%
if /i "%choice%"=="1" start /D Server\Debug\ /MIN ./Server/Debug/CenterServer.exe & start /D .\Server\Debug\ /MIN ./Server/Debug/LoginServer.exe & start /D .\Server\Debug\ /MIN ./Server/Debug/ProxyServer.exe & start /D .\Server\Debug\ /MIN ./Server/Debug/DBServer.exe & start /D .\Server\Debug\ /MIN ./Server/Debug/GameServer.exe
if /i "%choice%"=="2" start /D Server\Release\ /MIN ./Server/Release/CenterServer.exe & start /D .\Server\Release\ /MIN ./Server/Release/LoginServer.exe & start /D .\Server\Release\ /MIN ./Server/Release/ProxyServer.exe & start /D .\Server\Release\ /MIN ./Server/Release/DBServer.exe & start /D .\Server\Release\ /MIN ./Server/Release/GameServer.exe
if /i "%choice%"=="3" taskkill /im CenterServer.exe & taskkill /im LoginServer.exe & taskkill /im ProxyServer.exe & taskkill /im DBServer.exe & taskkill /im GameServer.exe
if /i "%choice%"=="4" exit
goto cho


