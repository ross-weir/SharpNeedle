#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <stdlib.h>

/* Injects the specified dll into a running process, calls a specific
 * method on that dll, then unloads the dll.
 */
BOOL InjectAndRunThenUnload(DWORD processId, const char * dllName, const std::string& ExportName, const wchar_t * ExportArgument);

/* Given a pid, a dll name, and a method name, walks the export address
 * table then calls the named method.
 */
DWORD CallExport(DWORD ProcId, const std::string& ModuleName, const std::string& ExportName, const wchar_t * ExportArgument);
