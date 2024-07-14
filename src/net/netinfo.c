#include "netinfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__

#include <ifaddrs.h>
#include <net/if.h>

#elif _WIN32

#include <winsock2.h>
#include <iphlpapi.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#endif // __linux__

// Public common function
void printNetworkInfo(NetworkInfo* netInfo) {
    printf("Adapter Name: %s\n", netInfo->adapterName);
    printf("IP Address: %s\n", netInfo->ipAddress);
    printf("Subnet Mask: %s\n", netInfo->subnetMask);
    printf("Gateway: %s\n", netInfo->gateway);
}


int getAdapterInfo(const char* adapterName, NetworkInfo* netInfo) 
{
#ifdef _WIN32
    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);

    pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) {
        printf("Error allocating memory\n");
        return 1;
    }

    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
        if (pAdapterInfo == NULL) {
            printf("Error allocating memory\n");
            return 1;
        }
    }

    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) != NO_ERROR) {
        printf("GetAdaptersInfo failed with error: %d\n", dwRetVal);
        if (pAdapterInfo)
            free(pAdapterInfo);
        return 1;
    }

    pAdapter = pAdapterInfo;
    while (pAdapter) {
        if (strcmp(pAdapter->Description, adapterName) == 0) {
            strcpy(netInfo->adapterName, pAdapter->Description);
            strcpy(netInfo->ipAddress, pAdapter->IpAddressList.IpAddress.String);
            strcpy(netInfo->subnetMask, pAdapter->IpAddressList.IpMask.String);
            strcpy(netInfo->gateway, pAdapter->GatewayList.IpAddress.String);
            free(pAdapterInfo);
            return 0;
        }
        pAdapter = pAdapter->Next;
    }

    printf("Adapter '%s' not found\n", adapterName);
    if (pAdapterInfo)
        free(pAdapterInfo);
#endif // _WIN32
    return 1;
}



int printAllAdapterNames() 
{
#ifdef _WIN32
    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);

    pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) {
        printf("Error allocating memory\n");
        return 1;
    }

    // Make an initial call to GetAdaptersInfo to get the necessary size into ulOutBufLen
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
        if (pAdapterInfo == NULL) {
            printf("Error allocating memory\n");
            return 1;
        }
    }

    // Call GetAdaptersInfo again to get actual adapter information
    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) != NO_ERROR) {
        printf("GetAdaptersInfo failed with error: %d\n", dwRetVal);
        if (pAdapterInfo)
            free(pAdapterInfo);
        return 1;
    }

    pAdapter = pAdapterInfo;
    while (pAdapter) {
        printf("Adapter Name: %s\n", pAdapter->Description);
        pAdapter = pAdapter->Next;
    }

    if (pAdapterInfo)
        free(pAdapterInfo);
#endif // _WIN32
    return 0;

}

char** getAllAdapterNames(int* numAdapters)
{
#ifdef _WIN32
    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
    int count = 0;

    // Allocate initial memory for the adapter info
    pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) {
        printf("Error allocating memory\n");
        *numAdapters = 0;
        return NULL;
    }

    // Make an initial call to GetAdaptersInfo to get the necessary size into ulOutBufLen
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
        if (pAdapterInfo == NULL) {
            printf("Error allocating memory\n");
            *numAdapters = 0;
            return NULL;
        }
    }

    // Call GetAdaptersInfo again to get actual adapter information
    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) != NO_ERROR) {
        printf("GetAdaptersInfo failed with error: %d\n", dwRetVal);
        if (pAdapterInfo)
            free(pAdapterInfo);
        *numAdapters = 0;
        return NULL;
    }

    // Count the number of adapters
    pAdapter = pAdapterInfo;
    while (pAdapter) {
        count++;
        pAdapter = pAdapter->Next;
    }

    // Allocate memory for storing adapter names
    char** adapterNames = (char**)malloc(count * sizeof(char*));
    if (adapterNames == NULL) {
        printf("Error allocating memory\n");
        *numAdapters = 0;
        if (pAdapterInfo)
            free(pAdapterInfo);
        return NULL;
    }

    // Copy adapter names into the allocated memory
    pAdapter = pAdapterInfo;
    for (int i = 0; i < count; i++) {
        adapterNames[i] = (char*)malloc(strlen(pAdapter->Description) + 1);
        if (adapterNames[i] == NULL) {
            printf("Error allocating memory\n");
            *numAdapters = i; // Update numAdapters to indicate how many were allocated
            freeAdapterNames(adapterNames, i);
            if (pAdapterInfo)
                free(pAdapterInfo);
            return NULL;
        }
        strcpy(adapterNames[i], pAdapter->Description);
        pAdapter = pAdapter->Next;
    }

    *numAdapters = count;
    if (pAdapterInfo)
        free(pAdapterInfo);

    return adapterNames;
#endif // _WIN32
    return NULL;
}

void freeAdapterNames(char** adapterNames, int numAdapters)
{
#ifdef _WIN32
    for (int i = 0; i < numAdapters; i++) {
        free(adapterNames[i]);
    }
    free(adapterNames);
#endif // _WIN32
}
int device_info(int argc, const char** argv)
{
#ifdef _WIN32
    printf("device Info Function\n");
    const char* adapterName = "Realtek Gaming 2.5GbE Family Controller"; // 替换为实际网卡名称
    NetworkInfo netInfo;
    int numAdapters;
    char** adapterNames = getAllAdapterNames(&numAdapters);

    if (adapterNames != NULL) {
        printf("Found %d network adapters:\n", numAdapters);
        for (int i = 0; i < numAdapters; i++) {
            printf("%d. %s\n", i + 1, adapterNames[i]);
        }
        freeAdapterNames(adapterNames, numAdapters);
    }
    else {
        printf("Failed to retrieve network adapter information.\n");
    }

    printAllAdapterNames();

    if (getAdapterInfo(adapterName, &netInfo) == 0) {
        printNetworkInfo(&netInfo);
    }
    else {
        printf("Failed to get network adapter information.");
    }
#endif // _WIN32
    return 0;
}



#ifdef __linux__

#endif // __linux__
