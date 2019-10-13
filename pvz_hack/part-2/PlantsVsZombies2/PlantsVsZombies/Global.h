#pragma once

// Вспомогательные дефайны для определения где произошла ошибка 
#define WIDEN2(x) L##x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)
#define __WDATE__ WIDEN(__DATE__)
#define __WTIME__ WIDEN(__TIME__)
#define __WFUNCTION__ WIDEN(__FUNCTION__)
#define __WFUNCDNAME__ WIDEN(__FUNCDNAME__)
#define __WFUNCSIG__ WIDEN(__FUNCSIG__)

#include <windows.h>
#include <process.h>
#include <tlhelp32.h>
#include <new>
#include <iostream>
#include <time.h>
#include <tchar.h>
#include <vector>
#include <map>

using namespace std;

#define QWORD unsigned __int64

#include "Enumerations.h"
#include "Structures.h"
#include "Utils.h"

extern HANDLE hGame;