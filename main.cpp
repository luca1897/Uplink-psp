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

#include "main.h"

PSP_MODULE_INFO("Uplink", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(0);
PSP_HEAP_SIZE_KB(18*1024);

PSPCommon CallbackPSP;

CDraw     UDraw;
CFilelist UFilelist;
CSystem   USystem;
CMain obj;
CRun URun;
CNet UNet;

extern animazione btm,txt1;
extern sprites batt;


int i = 0,selected=2,file_selected=0;
int Y_Barra_filelist;
int filelistI       = 0;
int list_offset     = 0;	//per stampare i file
int numfiles;			// serve per stampare la filelist
int k;				// ciclo
int printf_filelist = 0;	//coordinate Y dei files da stampare


bool direzione;
bool first = true;



//{DIALOG
bool Dialog = false;
bool DialogPress = false;
core::stringw DialogTextTitle;
core::stringw DialogText1;
core::stringw DialogText2;
//DIALOG}

core::stringw currdir;		//Directory corrente
core::stringw array_Files_Dir[100];
IFileSystem * FileSystem;

int menu;
/*

menu 100 = dialog
*/
engineDevice *device;
IFileList *filelist;
long CLOCKS_PER_MS = (CLOCKS_PER_SEC / 1000);
core::stringw CurrentMenu[2];
core::stringw FileInfo[3];

int CountFileDir = 1;


/* main function */
int engineMain(unsigned int argc, void *argv)
{
    CallbackPSP.setupPSP();

    obj.run();
}

CMain::CMain()
{

    /* sets data */

}

void CMain::Log(core::stringc Text)
{
    IWriteFile *FileLog;
    core::stringc PATH;
    PATH = "log.txt";
    Text += "\n";
    FileLog = device->getFileSystem()->createAndWriteFile(PATH.c_str(), true);
    FileLog->write(Text.c_str(), Text.size());
    FileLog->drop();
}

bool CMain::OnEvent(SEvent event)
{
    if (!device)
        return false;

    if (event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown == false )
    {
        if (menu==0)
        {
            if (event.KeyInput.Key == KEY_UP && (clock() / CLOCKS_PER_MS) - UpLastTime > 250)
            {

                if (selected>0)
                {
                    selected--;
                    btm.anim_=0;
                    btm._anim = 15;
                    direzione = true;
                    first = false;
                    txt1.X = 0;
                }
                UpLastTime = clock() / CLOCKS_PER_MS;
            }
            else if (event.KeyInput.Key == KEY_DOWN && (clock() / CLOCKS_PER_MS) - DownLastTime > 250)
            {

                if (selected<4)
                {
                    selected++;
                    btm.anim_=0;
                    btm._anim = 15;
                    direzione = false;
                    first = false;
                    txt1.X = 0;
                }
                DownLastTime = clock() / CLOCKS_PER_MS;
            }
            else if (event.KeyInput.Key == KEY_TRIANGLE && (clock() / CLOCKS_PER_MS) - TriangleLastTime > 250)
            {
                USystem.GetSystemInfo();
                UDraw.ResetAndSelect(6);
                TriangleLastTime = clock() / CLOCKS_PER_MS;
            }
            else if (event.KeyInput.Key == KEY_CROSS && (clock() / CLOCKS_PER_MS) - CrossLastTime > 250)
            {
                UDraw.ResetAndSelect(selected+1);
                CrossLastTime = clock() / CLOCKS_PER_MS;
            }
        }
        else if (menu==6)
        {
            if (event.KeyInput.Key == KEY_TRIANGLE && (clock() / CLOCKS_PER_MS) - TriangleLastTime > 250)
            {

                UDraw.ResetAndSelect(0);
                TriangleLastTime = clock() / CLOCKS_PER_MS;
            }
        }
        else if (menu==3 && !Dialog)
        {
            if (event.KeyInput.Key == KEY_UP && (clock() / CLOCKS_PER_MS) - UpLastTime > 170)
            {
                if (Y_Barra_filelist<=56)
                {
                    Y_Barra_filelist=66;
                    list_offset--;
                    if (list_offset < 0) list_offset = 0;
                }
                Y_Barra_filelist-=10;
                file_selected--;

                if (file_selected <= 0)file_selected  = 0;

                FileInfo[0] = filelist->getFileName(file_selected);

                FileInfo[1] = UFilelist.GetFileSize(filelist->getFullFileName(file_selected))/1024;
                FileInfo[1] += L" kb";

                ScePspDateTime pspdatetime = UFilelist.GetFileCreationTime(filelist->getFullFileName(file_selected));
                FileInfo[2] = pspdatetime.day;
                FileInfo[2] += L"/";
                FileInfo[2]+= pspdatetime.month;
                FileInfo[2] += L"/";
                FileInfo[2] += pspdatetime.year;

                UpLastTime = clock() / CLOCKS_PER_MS;
            }
            else if (event.KeyInput.Key == KEY_DOWN && (clock() / CLOCKS_PER_MS) - DownLastTime > 170)
            {
                if (CountFileDir>=17)
                {
                    if (Y_Barra_filelist>=216)
                    {
                        Y_Barra_filelist=206;
                        list_offset++;
                        if (list_offset > CountFileDir) list_offset = CountFileDir;
                    }
                    Y_Barra_filelist+=10;
                    if (file_selected >= CountFileDir - 2)
                    {
                        file_selected = CountFileDir - 2;
                        list_offset = CountFileDir - 17;
                    }
                    file_selected++;

                }
                else
                {
                    if (file_selected<CountFileDir-1)
                    {
                        file_selected++;
                        Y_Barra_filelist+=10;
                    }
                }

                FileInfo[0] = filelist->getFileName(file_selected);

                FileInfo[1] = UFilelist.GetFileSize(filelist->getFullFileName(file_selected))/1024;
                FileInfo[1] += L" kb";

                ScePspDateTime pspdatetime = UFilelist.GetFileCreationTime(filelist->getFullFileName(file_selected));
                FileInfo[2] = pspdatetime.day;
                FileInfo[2] += L"/";
                FileInfo[2]+= pspdatetime.month;
                FileInfo[2] += L"/";
                FileInfo[2] += pspdatetime.year;
                DownLastTime = clock() / CLOCKS_PER_MS;
            }
            else if (event.KeyInput.Key == KEY_TRIANGLE && (clock() / CLOCKS_PER_MS) - TriangleLastTime > 250)
            {
                UDraw.ResetAndSelect(0);
                TriangleLastTime = clock() / CLOCKS_PER_MS;
            }
            else if (event.KeyInput.Key == KEY_CROSS && (clock() / CLOCKS_PER_MS) - CrossLastTime > 250)
            {
                UFilelist.execute(file_selected,1);
                CrossLastTime = clock() / CLOCKS_PER_MS;
            }
        }
        else if (Dialog)
        {
            if (event.KeyInput.Key == KEY_CIRCLE && (clock() / CLOCKS_PER_MS) - CircleLastTime > 250)
            {
                Dialog = false;
                CircleLastTime = clock() / CLOCKS_PER_MS;
            }
            if (event.KeyInput.Key == KEY_CROSS && (clock() / CLOCKS_PER_MS) - CrossLastTime > 250)
            {
                Dialog = false;
                UFilelist.execute(file_selected,2);
                CrossLastTime = clock() / CLOCKS_PER_MS;
            }
        }
    }

}

CMain::~CMain()
{

}

core::stringc PBPPath;

void CMain::InitNetwork()
{
    int err;
    sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);
    sceUtilityLoadNetModule(PSP_NET_MODULE_INET);

    if (sceUtilityLoadNetModule(PSP_NET_MODULE_PARSEURI) < 0)
    {
        // error here
        printf("Error, Could Not initialize the Net module PARSEURI\n");

        sceKernelExitGame();
    }

    if (sceUtilityLoadNetModule(PSP_NET_MODULE_PARSEHTTP) < 0)
    {
        // error here
        printf("Error, Could Not initialize the Net module PARSEHTTP\n");

        sceKernelExitGame();
    }

    if (sceUtilityLoadNetModule(PSP_NET_MODULE_HTTP) < 0)
    {
        // error here
        printf("Error, Could Not initialize the Net module HTTP\n");

        sceKernelExitGame();
    }
    //Those functions initalise the network libraries that are loaded with the previous functions.
    sceNetInit(128 * 1024, 42, 4 * 1024, 42, 4 * 1024);
    sceNetInetInit();
    sceNetApctlInit(0x8000, 48);

    SceUID thread_net_thread;
    thread_net_thread = sceKernelCreateThread("net_thread", UNet.net_thread, 0x18, 0x10000, PSP_THREAD_ATTR_USER, NULL);
    sceKernelStartThread(thread_net_thread, 0, NULL);
}

void CMain::run()
{

    device = createDevice(this);
    FileSystem =  device->getFileSystem();

    menu = 0;

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

    backColor.set(255,100,101,140);
    core::rect<int> pos(0,0,60,20);
    device->getCursorControl()->setVisible(false);

    //get firmware version
    USystem.GetFirmwareVersion();
    //get Ethernet address
    USystem.GetEthernetAddress();
    USystem.LocalIp = L"None";

    UDraw.InitDraw(guienv,device,driver);
    UDraw.Set();

    PBPPath = FileSystem->getWorkingDirectory();

    UFilelist.InitFileList();

    InitNetwork();

    while (device->run() && driver)
    {
        {
            // load next scene if necessary

            // draw everything

            driver->beginScene(true, true, backColor);
            UDraw.BigDraw(driver);
            smgr->drawAll();
            guienv->drawAll();

            driver->endScene();


        }
    }

    device->drop();
}

