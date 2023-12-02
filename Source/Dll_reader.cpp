#include <Windows.h>
#include <map>
#include "Dll_reader.hpp"
#include <string>
using namespace std;
//#include <Psapi.h>


//auto pmc = new PROCESS_MEMORY_COUNTERS;
//auto CurProcess = GetCurrentProcess();
//
//DLL size_t GetMemory() {
//	GetProcessMemoryInfo(CurProcess, pmc, sizeof(PROCESS_MEMORY_COUNTERS));
//	return static_cast<size_t>(pmc->WorkingSetSize);
//} 









static map<string, HMODULE> dlls;

DLL bool _LoadLibrary(const char* str) {
	auto d = LoadLibraryA(str);
	if (!d) return false;
	dlls[str] = d;
	return true;
}
DLL void _FreeLibrary(const char* str) {
	FreeLibrary(dlls[str]);
	dlls.erase(str);
}
DLL void* _GetProcAddress(const char* lib, const char* proc)
{
	return GetProcAddress(dlls[lib], proc);
}

//class Semaphore {
//    static inline HANDLE semaphore;
//    static inline long max_instances{ 1 };
//    static inline const wchar_t* semaphore_name{ L"Global\MyProcess" };
//
//public:
//    static void InitSemaphore(const wchar_t* name, long inst) {
//        semaphore_name = name;
//        max_instances = inst;
//        semaphore = CreateSemaphore(0, max_instances, max_instances, semaphore_name);
//    }
//
//    static bool CanOpenWindow() {
//        if (!semaphore)
//        {
//            semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, false, semaphore_name);
//
//            if (!semaphore)  return false;
//        }
//
//        DWORD acquireResult = WaitForSingleObject(semaphore, 0L);  // timeout after 0 seconds trying to acquire
//
//        if (acquireResult == WAIT_TIMEOUT)
//        {
//            CloseHandle(semaphore);
//            return false;
//        }
//
//        return true;
//    }
//
//    static void CloseSemaphore() {
//        CloseHandle(semaphore);
//    }
//};
//
//DLL void InitSemaphore(const wchar_t* name = L"Global\MyProcess", long inst = 1) {
//    Semaphore::InitSemaphore(name, inst);
//}
//DLL bool CanOpenWindow() {
//    return Semaphore::CanOpenWindow();
//}
//DLL void CloseSemaphore() {
//    Semaphore::CloseSemaphore();
//}