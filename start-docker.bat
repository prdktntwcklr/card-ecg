@echo off

REM get a unique image name based on the name of this folder
for %%I in (.) do set container_name=%%~nxI

REM convert container name to lower case
set container_name
call :LoCase container_name

REM stop container if it is running
docker stop %container_name%

REM delete container before we can recreate it
docker rm %container_name%

REM build the image if it does not exist (takes several minutes)
docker image ls | findstr "%container_name%" >nul
if /I "%ERRORLEVEL%" NEQ "0" (
    docker build -t %container_name% .
)

REM run docker container and mount current folder
docker run -dit --name %container_name% --mount type=bind,source="%cd%",target=/app %container_name%

REM start bash in container to execute commands (use exit to end session)
docker exec -it %container_name% /bin/bash

goto:eof

:LoCase
:: Subroutine to convert a variable VALUE to all lower case.
:: The argument for this subroutine is the variable NAME.
for %%i in ("A=a" "B=b" "C=c" "D=d" "E=e" "F=f" "G=g" "H=h" "I=i" "J=j" "K=k" "L=l" "M=m" "N=n" "O=o" "P=p" "Q=q" "R=r" "S=s" "T=t" "U=u" "V=v" "W=w" "X=x" "Y=y" "Z=z") do call set "%1=%%%1:%%~i%%"
goto:eof
