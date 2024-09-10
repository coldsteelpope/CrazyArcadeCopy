#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <tchar.h>
#include <iterator>
#include <assert.h>
#include <algorithm>

#include <WinSock2.h>
#pragma comment(lib, "ws2_32")

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

using namespace std;

#include "Defines.h"


#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif