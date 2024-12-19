//Program to list all the running processes and terminate the process by using its id

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
using namespace std;

// Function to list all the running processes
void listRunningProcesses() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        cerr << "Error: Unable to take process snapshot.\n";
        return;
    }

    // Initialize the process entry structure
    pe32.dwSize = sizeof(PROCESSENTRY32);

	// Get the first process
    if (Process32First(hProcessSnap, &pe32)) {
        cout << "PID\tProcess Name\n";
        do {
            cout << pe32.th32ProcessID << "\t" << pe32.szExeFile << endl;
        } while (Process32Next(hProcessSnap, &pe32));
    } else {
        cerr << "Error: Unable to fetch process list.\n";
    }

    CloseHandle(hProcessSnap);
}
 // Function to terminate a process by its ID
void terminateProcess(DWORD pid) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess == NULL) {
        cerr << "Error: Unable to open process with PID " << pid << ".\n";
        return;
    }

    if (TerminateProcess(hProcess, 0)) {
        cout << "Process with PID " << pid << " terminated successfully.\n";
    } else {
        cerr << "Error: Unable to terminate process.\n";
    }

    CloseHandle(hProcess);
}

int main() {
    int choice;
    DWORD pid;

    do {
        cout << "1. List Processes\n2. Terminate Process\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listRunningProcesses();
                break;
            case 2:
                cout << "Enter PID to terminate: ";
                cin >> pid;
                terminateProcess(pid);
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
