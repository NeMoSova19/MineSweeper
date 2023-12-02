#pragma once
#define DLL extern "C" __declspec(dllexport)

DLL bool _LoadLibrary(const char*);
DLL void* _GetProcAddress(const char*, const char*);
DLL void _FreeLibrary(const char*);