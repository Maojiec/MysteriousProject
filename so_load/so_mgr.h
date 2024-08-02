// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (c) 2024-2024 maodengjie maodengjie@foxmail.com
#ifndef _IOT_SO_MGR_H_
#define _IOT_SO_MGR_H_

typedef int (*init)(void);
typedef int (*deinit)(void);


typedef enum {
    SMG_INIT,
    SMG_DEINIT
} SoMgrStat;

#define SO_INSTALL_PATH "/usr/local/.iot_so_install"

int SoLoad(const char *path, const char *sig);

#endif