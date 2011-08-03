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

//**********************************************************************************
//	Include Files
//**********************************************************************************

#include "system.h"

extern IFileSystem *FileSystem;

void CSystem::GetSystemInfo()
{
    /**BATTERY*/
    /**PERCENTUALE CARICA DELLA BATTERIA*/
    BatteryLifePerc = L"Battery charge percentage: ";
    BatteryLifePerc += scePowerGetBatteryLifePercent();
    BatteryLifePerc += L"%";


    /**PERCENTUALE CARICA DELLA BATTERIA*/
    BatteryLifeTime = L"Battery Life Time: ";
    BatteryLifeTime += scePowerGetBatteryLifeTime() / 3600;
    BatteryLifeTime += L"m";


    /**TEMPERATURA DELLA BATTERIA*/
    BatteryTemp = L"Temperature of the battery: ";
    BatteryTemp += scePowerGetBatteryTemp();
    BatteryTemp += L"deg C";


    /**EXTERNAL POWER*/
    IsPowerOnline = scePowerIsPowerOnline() ? L"External Power: Yes" : L"External Power: No ";

    /**BATTERY PRESENT*/
    IsBatteryExist = scePowerIsBatteryExist() ? L"Battery Present: Yes" : L"Battery Present: No ";

    /**FREEMEMORY*/
    FreeMemory = L"Free Memory: ";
    FreeMemory += __freemem();

    /**CPU BUS*/
    CpuClock = L"CPU: ";
    CpuClock += scePowerGetCpuClockFrequency();
    CpuClock += " MHZ";

    BusClock = L"BUS: ";
    BusClock += scePowerGetBusClockFrequency();
    BusClock += " MHZ";


}


void CSystem::GetEthernetAddress()
{
    unsigned char sVal[7];
    char themac[18];
    memset(sVal, 0, 7);

    int ret = sceWlanGetEtherAddr(sVal);
    if (!ret)
    {
        sprintf(themac, "%02X:%02X:%02X:%02X:%02X:%02X", sVal[0], sVal[1], sVal[2], sVal[3], sVal[4], sVal[5]);
        EthernetAddress = L"Ethernet Address: ";
        EthernetAddress += themac;
    }
    else
    {
        EthernetAddress = L"None";
    }
}

void CSystem::GetFirmwareVersion()
{
    FirmwareVersion = L"Firmware Version: ";
    unsigned int ver;
    char FirmwareVer[20];
    ver = sceKernelDevkitVersion();
    sprintf(FirmwareVer, "%d.%d%d (0x%08X)", (ver >> 24) & 0xFF, (ver >> 16) & 0xFF,(ver>>8) & 0xFF, ver);
    FirmwareVersion += FirmwareVer;
}

core::stringw CSystem::GetData()
{

    sceRtcGetCurrentClockLocalTime(&psptime);

    anno = psptime.year;

    mese = psptime.month;

    giorno = psptime.day;

    ore = psptime.hour;

    minuti = psptime.minutes;

    core::stringw Data;

    Data  = giorno;
    Data += "/";
    Data += mese;
    Data += "/";
    Data += anno;

    if (ore < 10)
    {
        Data += " - ";
        Data += "0";
        Data += ore;
        Data += ":";
    }
    else
    {
        Data += " - ";
        Data += ore;
        Data += ":";
    }
    if (minuti < 10)
    {
        Data += "0";
        Data += minuti;
    }
    else
    {
        Data += minuti;
    }

    return Data;

}

extern sprites batt;

void CSystem::GetBattery()
{
    if (scePowerGetBatteryLifePercent() <= 100)
    {
        batt.Y[1] = 395;
        batt.Y[0] = 384;
    }
    if (scePowerGetBatteryLifePercent() <= 80)
    {
        batt.Y[1] = 413;
        batt.Y[0] = 402;
    }
    if (scePowerGetBatteryLifePercent() <= 50)
    {
        batt.Y[1] = 431;
        batt.Y[0] = 420;
    }
    if (scePowerGetBatteryLifePercent() <= 30)
    {
        batt.Y[1] = 448;
        batt.Y[0] = 437;
    }


    if (scePowerGetBatteryLifePercent() <= 10)
    {
        batt.Y[1] = 466;
        batt.Y[0] = 455;
    }
}

int CSystem::__freemem()
{
    void *ptrs[480];
    int mem, x, i;
    for (x = 0; x < 480; x++)
    {
        void *ptr = malloc(51200);
        if (!ptr) break;

        ptrs[x] = ptr;
    }
    mem = x * 51200;
    for (i = 0; i < x; i++)
        free(ptrs[i]);

    return mem;
}

int CSystem::GetConf()
{
    FILE *fstream;
    int conf;
    char* PATH;
    //sprintf(PATH, "./netconf.txt", PBPPath.c_str());
    if (FileSystem->existFile("./netconf.txt"))
    {
        fstream = fopen("./netconf.txt","r");
        fscanf(fstream, "%d", &conf);
        fclose(fstream);
        return conf;
    }
    else	  //se il file non esiste setto le impostazioni di default
    {
        return 0;
    }
}
