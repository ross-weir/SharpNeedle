#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <stdlib.h>
#include <string>

#include "Injection.h"

using namespace std;

/* There are two defined entry points here, one for a  Windows
 * application, and another for a console application.
 * 
 * To switch between the two versions, we need to change our
 * subsystem dependency and then rebuild. The compiler will
 * automatically choose the appropriate entry point.
 * 
 * To enable Windows (hidden) mode, go to project properties, find the
 * 'linker' section and change the SubSystem option to Windows.
 * 
 * To enable console (debugging) mode, go to project properties, find
 * the 'linker' section and change the SubSystem option to Console.
 */

/* Since there are two entry points for this program, we really
 * ought to get to a common point as soon as possible.  This is that
 * common point.
 */
void true_main(DWORD ProcessId) {
    // Bootstrapper
    char DllName[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, DllName);
    strcat_s(DllName, "\\Bootstrapper.dll");

    // ExampleProject
    wchar_t DllNameW[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, DllNameW);
    wcscat_s(DllNameW, L"\\Main.dll");
    
    InjectAndRunThenUnload(ProcessId, DllName, "LoadManagedProject", DllNameW);
}

/* By starting as a Windows application but not displaying any
 * windows, we can become effectively invisible.
 */
int __stdcall WinMain (HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPSTR lpCmdLine,
                       int cmdShow)
{
	char *NextToken;
	char* StrPid = strtok_s(lpCmdLine, " ", &NextToken);
	DWORD Pid = atoi(StrPid);
    true_main(Pid);
    return 0;
}

/* In any case, it's useful to have a console window visible
 * for debugging purposes.  Use cout to your heart's content!
 */
int main(int argc, char* argv[])
{
	DWORD Pid = atoi(argv[1]);
    true_main(Pid);
    return 0;
}
