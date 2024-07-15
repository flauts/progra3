#include "Command.h"
#include "../Menu/Menu.h"
#include <iostream>
#include <thread>
#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Command.h"
#include "Menu.h"

// Implementaciones de SearchOption
void SearchOption::execute() {
    std::vector<std::unique_ptr<Command>> commands;
    commands.push_back(std::make_unique<SearchByTagsSubOption>());
    commands.push_back(std::make_unique<SearchByNameSubOption>());
    commands.push_back(std::make_unique<SearchBySynopsisSubOption>());
    commands.push_back(std::make_unique<ReturnOption>());
    Menu::getInstance().setCommands(std::move(commands));
}

// Implementaciones de CheckBookmarksOption
void CheckBookmarksOption::execute() {
    std::vector<std::unique_ptr<Command>> commands;
    commands.push_back(std::make_unique<WatchLaterOption>());
    commands.push_back(std::make_unique<FavoritesOption>());
    commands.push_back(std::make_unique<ReturnOption>());
    Menu::getInstance().setCommands(std::move(commands));
}

// Implementaciones de SeeMoreOption
void SeeMoreOption::execute() {
    std::vector<std::unique_ptr<Command>> commands;
    commands.push_back(std::make_unique<DevModeOption>());
    commands.push_back(std::make_unique<WhatIsChavezNetOption>());
    commands.push_back(std::make_unique<ReturnOption>());
    Menu::getInstance().setCommands(std::move(commands));
}

// Implementaciones de ExitOption
void ExitOption::execute() {
    std::cout << "Exiting application..." << std::endl;
    exit(0);
}

// Implementaciones de SearchByTagsSubOption
void SearchByTagsSubOption::execute() {
    std::cout << "Executing Search by Tags" << std::endl;
}

// Implementaciones de SearchByNameSubOption
void SearchByNameSubOption::execute() {
    std::cout << "Executing Search by Name" << std::endl;
}

// Implementaciones de SearchBySynopsisSubOption
void SearchBySynopsisSubOption::execute() {
    std::cout << "Executing Search by Synopsis" << std::endl;
}

// Implementaciones de ReturnSubOption
void ReturnSubOption::execute() {
    Menu::getInstance().restoreState();
}

// Implementaciones de WatchLaterOption
void WatchLaterOption::execute() {
    std::cout << "Executing Watch Later Option" << std::endl;
}

// Implementaciones de FavoritesOption
void FavoritesOption::execute() {
    std::cout << "Executing Favorites Option" << std::endl;
}

// Implementaciones de WhatIsChavezNetOption
void WhatIsChavezNetOption::execute() {
    std::cout << "Executing What is ChavezNet Option" << std::endl;
}

// Implementaciones de ReturnOption
void ReturnOption::execute() {
    Menu::getInstance().restoreState();
}

// Implementaciones de ConfirmOption
void ConfirmOption::execute() {
    std::cout << "Confirming selection." << std::endl;
}

// = = = = = ADDITIONALLY FUNCTIONALITIES FOR DEVMODE = = = = =

// Function to compare file times = = = = =
long CompareFileTime(FILETIME time1, FILETIME time2) {
    ULARGE_INTEGER a, b;
    a.LowPart = time1.dwLowDateTime;
    a.HighPart = time1.dwHighDateTime;

    b.LowPart = time2.dwLowDateTime;
    b.HighPart = time2.dwHighDateTime;

    return b.QuadPart - a.QuadPart;
}

// Function to get CPU usage = = = = =
float getCPUUsage() {
    static FILETIME prevSysIdle, prevSysKernel, prevSysUser;
    FILETIME sysIdle, sysKernel, sysUser;

    if (!GetSystemTimes(&sysIdle, &sysKernel, &sysUser)) {
        return -1.0f; // Error
    }

    if (prevSysIdle.dwLowDateTime != 0 && prevSysKernel.dwLowDateTime != 0 && prevSysUser.dwLowDateTime != 0) {
        auto diffSysIdle = CompareFileTime(prevSysIdle, sysIdle);
        auto diffSysKernel = CompareFileTime(prevSysKernel, sysKernel);
        auto diffSysUser = CompareFileTime(prevSysUser, sysUser);

        auto totalSys = diffSysKernel + diffSysUser;
        return (totalSys - diffSysIdle) * 100.0f / totalSys;
    }

    prevSysIdle = sysIdle;
    prevSysKernel = sysKernel;
    prevSysUser = sysUser;

    return -1.0f; // First call
}

// Function to get memory usage = = = = =
float getMemoryUsage() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
    DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;

    return physMemUsed / (float)totalPhysMem * 100.0f;
}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// Implementations of DevModeOption = = = = =
void DevModeOption::execute() {
    std::cout << "Attempting to engage DevMode" << std::endl;
    if (authenticate()) {
        std::cout << "Authentication successful!" << std::endl;
        displayDebugInfo();
        showResourceUsage();

        std::vector<std::unique_ptr<Command>> commands;
        commands.push_back(std::make_unique<ConfirmOption>());
        commands.push_back(std::make_unique<ReturnOption>());
        Menu::getInstance().setCommands(std::move(commands));
    } else {
        std::cout << "Authentication failed!" << std::endl;
    }
}

bool DevModeOption::authenticate() {
    std::string password;
    std::cout << "Enter password to access DevMode: ";
    std::cin >> password;
    return password == "devpass"; // Replace "devpass" with your secure password
}

void DevModeOption::displayDebugInfo() {
    std::cout << "\n--- Debugging Information ---" << std::endl;
    std::cout << "Application Version: 1.0.0" << std::endl;
    std::cout << "Build Time: " << __DATE__ << " " << __TIME__ << std::endl;
    std::cout << "Running on: " << std::this_thread::get_id() << std::endl;
    std::cout << "Engine F.O.R.C.E. by DynamicProjects." << std::endl;
    // Add more debugging information as needed
}

void DevModeOption::showResourceUsage() {
    std::cout << "\n--- Resource Usage ---" << std::endl;
    std::cout << "CPU Usage: " << getCPUUsage() << "%" << std::endl;
    std::cout << "Memory Usage: " << getMemoryUsage() << "%" << std::endl;
    std::cout << "Disk I/O: 1.2MB/s" << std::endl; // Dummy data for disk I/O
    // Add real resource usage metrics if available
}
