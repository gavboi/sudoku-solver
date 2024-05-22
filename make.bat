@echo off
setlocal enabledelayedexpansion 

rem Compiler
set CC=gcc

rem Compiler flags
set CFLAGS=-Wall -Wextra -std=c11

rem Source files
set SRCS=solver.c params.c

rem Output executable
set TARGET=solver.exe

rem Object files (automatically generated)
set OBJS=

rem Entry point
:main
    if "%1"=="build" goto build
    if "%1"=="clean" goto clean
    goto help

rem Build target
:build
    %CC% %CFLAGS% -c %SRCS%
	if %ERRORLEVEL% neq 0 (
		echo Compilation failed
		goto end
	)
    for %%f in (%SRCS:.c=.o%) do set OBJS=!OBJS! %%f
    %CC% %CFLAGS% -o %TARGET% %OBJS%
	if %ERRORLEVEL% neq 0 (
		echo Compilation failed!
	) else (
		echo Compilation successful!
	)
    goto end

rem Clean target
:clean
    del %TARGET% *.o
    echo Cleaned up!
    goto end

rem Help target
:help
    echo Usage:
    echo   compile.bat [build ^| clean]
    goto end

:end