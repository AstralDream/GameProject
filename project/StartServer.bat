:start
@echo off
color 0A
echo. �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[
echo. �U  ��ѡ��Ҫ���еĲ�����Ȼ�󰴻س�  �U
echo. �U�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�U
echo. �U                                  �U
echo. �U     1.����ȫ��������(DEBUG)      �U
echo. �U                                  �U
echo. �U     2.����ȫ��������(RELEASE)    �U
echo. �U                                  �U
echo. �U     3.�ر�ȫ��������             �U
echo. �U                                  �U
echo. �U     4.��ʾ����������             �U
echo. �U                                  �U
echo. �U     5.�����Ļ                   �U
echo. �U                                  �U
echo. �U     6.�˳������               �U
echo. �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a
echo.             
set DebugDir=%cd%\Server\Debug\
set ReleaseDir=%cd%\Server\Release\
:cho
set choice=
set /p choice=          ��ѡ��:
IF NOT "%choice%"=="" SET choice=%choice:~0,1%
if /i "%choice%"=="1" start /D %DebugDir% /MIN %DebugDir%CenterServer.exe & start /D %DebugDir% /MIN %DebugDir%LoginServer.exe & start /D %DebugDir% /MIN %DebugDir%ProxyServer.exe & start /D %DebugDir% /MIN %DebugDir%DBServer.exe & start /D %DebugDir% /MIN %DebugDir%GameServer.exe
if /i "%choice%"=="2" start /D %DebugDir% /MIN %DebugDir%CenterServer.exe & start /D %DebugDir% /MIN %DebugDir%LoginServer.exe & start /D %DebugDir% /MIN %DebugDir%ProxyServer.exe & start /D %DebugDir% /MIN %DebugDir%DBServer.exe & start /D %DebugDir% /MIN %DebugDir%GameServer.exe
if /i "%choice%"=="3" taskkill /im CenterServer.exe & taskkill /im LoginServer.exe & taskkill /im ProxyServer.exe & taskkill /im DBServer.exe & taskkill /im GameServer.exe
if /i "%choice%"=="4" type %DebugDir%GameServer.ini & type %DebugDir%LoginServer.ini & type %DebugDir%ProxyServer.ini & type %DebugDir%CenterServer.ini & type %DebugDir%DBServer.ini
if /i "%choice%"=="5" cls & goto start
if /i "%choice%"=="6" exit
echo.
goto cho


