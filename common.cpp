/*
 * Uplink
 * Copyright (C) 2007-2010 Luca Barbàra <l33tb1t@live.it>
 *  
 * This file is part of Uplink.
 *
 * Uplink is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Uplink is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Uplink.  If not, see <http://www.gnu.org/licenses/>
 *
 */
 
 
#define PSP_BOOST_CPU

#include <pspkernel.h>
#ifdef PSP_BOOST_CPU
#include <psppower.h>
#endif

#ifdef PSP_ENABLE_DEBUG
#include <pspdebug.h>
#define printf pspDebugScreenPrintf
#endif


#include "common.h"
#include "main.h"
int exitCallback(int arg1, int arg2, void *common)
{
    //pspSdkInetTerm();
    sceNetApctlTerm();
    sceNetInetTerm();
    sceNetTerm();
    sceKernelExitGame();
    return 0;
}

int callbackThread(SceSize args, void *argp)
{
    int cbid;

    cbid = sceKernelCreateCallback("Exit Callback", exitCallback, NULL);
    sceKernelRegisterExitCallback(cbid);

    sceKernelSleepThreadCB();

    return 0;
}

int setupCallbacks(void)
{
    int thid = 0;

    thid = sceKernelCreateThread("update_thread", callbackThread, 0x11, 0xFA0, 0, 0);
    if (thid >= 0)
    {
        sceKernelStartThread(thid, 0, 0);
    }

    return thid;

}

int PSPCommon::setupPSP(void)
{

    scePowerSetClockFrequency(333, 333, 166);
    // setup callbacks
    setupCallbacks();

#ifdef PSP_ENABLE_DEBUG
    pspDebugScreenInit();
#endif

}
