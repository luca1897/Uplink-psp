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

#include "net.h"

//**********************************************************************************
//	Extern var
//**********************************************************************************
extern  CMain      obj;
//extern  CXML         UXML;
//extern  CDraw   UDraw;
extern int MenuSelez;
extern core::stringw localIp;
//extern core::stringc PBPPath;
//extern core::stringw status;
//**********************************************************************************
//   Variabili
//**********************************************************************************
//extern CSystem USystem;
//**********************************************************************************
//
//**********************************************************************************
u8 xmlbuffer[10*1024] __attribute__((aligned(64))); // this should go as global var

core::stringc URLserver = L"";


extern CSystem     USystem;
extern CRun URun;
extern CNet UNet;
extern core::stringc PBPPath;
//extern core::stringw status;
bool connesso = false;
extern core::stringw localIp;
extern int DownloadMode;
extern IFileSystem *FileSystem;

int CNet::connect_to_apctl(int config)
{
    int err;
    int stateLast = -1;
    /* Connect using the first profile */
    err = sceNetApctlConnect(config);
    if (err != 0)
    {
        printf("sceNetApctlConnect returns %08X\n", err);
        return 0;
    }

    printf("Connecting...\n");
    while (1)
    {
        int state;
        err = sceNetApctlGetState(&state);
        if (err != 0)
        {
            printf("sceNetApctlGetState returns $%x\n" , err);
            break;
        }
        if (state > stateLast)
        {
            printf("connection state %d of 4\n", state);
            stateLast = state;
        }
        if (state == 4)
            break;  // connected with static IP

        // wait a little before polling again
        sceKernelDelayThread(50*1000); // 50ms
    }
    printf("Connected!\n");

    if(err != 0)
    {
        return 0;
    }
    return 1;
}


int CNet::net_thread(SceSize args, void *argp)
{
    int res = UNet.connect_to_apctl(1);
    if(res)
    {
        SceNetApctlInfo sz;

        if (sceNetApctlGetInfo(8, &sz) != 0)
        {
            sceKernelSleepThread();
        }
        else
        {
            USystem.LocalIp=L"Local Ip: ";
            USystem.LocalIp+=sz.ip;
            connesso=true;
            UNet.FileDownload(L"http://www.psp-ita.com/forum/templates/BBTech/images/BBTech-hd_logo.jpg");
        }
    }

    sceKernelExitDeleteThread(0);

}


int CNet::FileDownload(core::stringc URL)
{
    if (connesso==true)
    {
        //USystem.GetServer();
        //char *the_url = "http://192.168.1.104/uplink/xml.xml";
        char *the_url = (char*)URL.c_str();
        printf(the_url);
        u64 filesize;
        int nbytes;

        if (sceHttpInit(20000) < 0)
        {
            // error here
            printf("Error1\n");
            return 0;

        }

        int templat = sceHttpCreateTemplate((char*)"MyUserAgent/0.0.1 libhttp/1.0.0", 1, 1);

        if (templat < 0)
        {
            // error here
            printf("Error2\n");
            return 0;

        }

        if (sceHttpSetResolveTimeOut(templat, 3000000) < 0)
        {
            // error here
            printf("Error3\n");
            return 0;

        }

        if (sceHttpSetRecvTimeOut(templat, 60000000) < 0)
        {
            // error here
            printf("Error4\n");
            return 0;

        }

        if (sceHttpSetSendTimeOut(templat, 60000000) < 0)
        {
            // error here
            printf("Error5\n");
            return 0;

        }

        int connection = sceHttpCreateConnectionWithURL(templat, the_url, 0);

        if (connection < 0)
        {
            // error here
            printf("Error6\n");
            return 0;

        }

        int request = sceHttpCreateRequestWithURL(connection, PSP_HTTP_METHOD_GET, the_url, 0);

        if (request < 0)
        {
            // error here
            printf("Error7\n");
            return 0;

        }

        if (sceHttpSendRequest(request, 0, 0) < 0)
        {
            // error here
            printf("Error8\n");
            return 0;

        }
        int statuss;
        int ret = sceHttpGetStatusCode(request, &statuss);
        printf("status:%d\n",statuss);
        if (statuss != 200)
        {
            // error here
            printf("Error9\n");
            return 0;

        }
        ret = sceHttpGetContentLength(request, &filesize);

        FILE* file;
        //core::stringw xmlpath;
        //xmlpath = "/immagini/pspita.xml";
        file = fopen("./media/pspita.jpg", "w");
        while ((nbytes = sceHttpReadData(request, xmlbuffer, sizeof(xmlbuffer))) != 0)
        {
            if (nbytes < 0)
            {
                printf("readdata fail\n");
            }
            xmlbuffer[nbytes] = '\0';
            // if this is our first time round, we need to get rid of the headers
            //
            fwrite( xmlbuffer,1,sizeof(xmlbuffer),file);

        }
        fclose(file);
        sceHttpEnd();
        sceNetApctlDisconnect();
        sceHttpDeleteTemplate(templat);
        sceHttpDeleteConnection(connection);
        sceHttpDeleteRequest(request);

        sceUtilityUnloadNetModule(PSP_NET_MODULE_HTTP);
        sceUtilityUnloadNetModule(PSP_NET_MODULE_PARSEHTTP);
        sceUtilityUnloadNetModule(PSP_NET_MODULE_PARSEURI);
        sceUtilityLoadNetModule(PSP_NET_MODULE_HTTP);
        sceUtilityLoadNetModule(PSP_NET_MODULE_INET);
        sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);
        //UXML.xmlReader();
        return 1;
    }
}


//*******************************  END OF FILE  ************************************

