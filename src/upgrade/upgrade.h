#ifndef UPGRADE_H
#define UPGRADE_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

    int device_upgrade(int argc, const char** argv);
    bool info_check(int n);
#ifdef __cplusplus
}
#endif

#endif // UPGRADE_H