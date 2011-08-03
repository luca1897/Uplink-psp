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

#include "draw.h"

#define MAX_FILES_PER_PAGE 17

extern CSystem USystem;
extern CMain   obj;

animazione btm,txt1;
sprites batt;

extern int Y_Barra_filelist,menu,selected,i,filelistI,numfiles,list_offset,k,printf_filelist,CountFileDir,file_selected;
extern bool first,direzione;
extern IFileList *filelist;
extern IFileSystem *FileSystem;
extern core::stringw CurrentMenu[2],array_Files_Dir[100],currdir,FileInfo[3];
extern CFilelist UFilelist;

//{DIALOG
extern bool Dialog;
extern core::stringw DialogTextTitle;
extern core::stringw DialogText1;
extern core::stringw DialogText2;

//DIALOG}

//core::stringw localIp;

void CDraw::InitDraw(gui::IGUIEnvironment* env,engineDevice *device,video::IVideoDriver* driver)
{
    //localIp = L"prova";
    skin  = env->getSkin();
    font  = env->getFont("media/fonttahoma.bmp");
    font2 = device->getGUIEnvironment()->getBuiltInFont();
    if (font)
        skin->setFont(font2);

    bg1 = driver->getTexture("media/all.png");
    //credit1 = CUplink.driver->getTexture("immagini/credit.png");
    //io::IReadFile* file = io::createMemoryReadFile(AudioIntro, size_AudioIntro, "#AudioIntro", false);
    //snd = CUplink.device->getAudioDriver()->addSound(file,0,false,true);

}

void CDraw::Set()
{
    btm.alpha = 50;
    btm.anim  = 0;
    btm.anim_ = 0;
    btm._anim = 15;


    txtScorr[0] = L"Visualizzatore di News pubblicate su psp-ita.com";
    txtScorr[1] = L"Permette di scaricare HB,Temi ecc ";
    txtScorr[2] = L"Filelist: Esegue PBP,LUA ed estrare RAR e ZIP";
    txtScorr[3] = L"Modifica le impostazioni di Uplink";
    txtScorr[4] = L"Visualizza i crediti di Uplink v5";

    FileInfo[0] = L"";
    FileInfo[1] = L"";
    FileInfo[2] = L"";

    txt1.X = 18;
    //txt1.Y =
    //txt1.anim =
    batt.X[0] = 124;
    batt.X[1] = 148;
    batt.Y[1] = 395;
    batt.Y[0] = 384;

    AnimAlpha_ALL = 0;
    Y_Barra_filelist = 56;
    CurrentMenu[0] = L"Now:                      Triangle:";
    CurrentMenu[1] = L"Main Menu                   System Info";
}

void CDraw::ResetAndSelect(int select)
{
    if (select==0)
    {
        menu = select;
        btm.alpha = 50;
        btm.anim  = 0;
        btm.anim_ = 0;
        btm._anim = 15;
        CurrentMenu[0] = L"Now:                      Triangle:";
        CurrentMenu[1] = L"Main Menu                   System Info";
        first = true;
    }
    else if (select==3)
    {
        AnimAlpha_ALL = 0;
        menu = select;
        CurrentMenu[1] = L"Filelist";
        CurrentMenu[1] += "                ";
        CurrentMenu[0]=L"Now:";
        CurrentMenu[0]+=L"               File/Dir:";
        CurrentMenu[1] += CountFileDir;
    }
    else if (select==6)
    {
        menu = select;
        CurrentMenu[0]=L"Now:";
        CurrentMenu[1] = L"System Info";
        AnimAlpha_ALL = 0;
    }
}

void CDraw::BigDraw(video::IVideoDriver* driver)
{

    /* SFONDO PRINCIPALE */
    driver->draw2DImage(bg1, core::position2d<s32>(0, 0),
                        core::rect<s32>(0, 0, 480, 272), 0,
                        video::SColor(255, 255, 255, 255), true);

    /* DATA E ORA */
    core::stringw Data = USystem.GetData();
    /*OMBRA*/
    font->draw(Data.c_str(), core::rect<s32>(323, 8, 250, 60),
               video::SColor(50, 0, 0, 0));
    /*DATA*/
    font->draw(Data.c_str(), core::rect<s32>(322, 7, 250, 60),
               video::SColor(140, 255, 255, 255));


    /* NOW */
    font->draw(CurrentMenu[0].c_str(), core::rect<s32>(28, 7, 250, 60),
               video::SColor(255, 106, 168, 184));

    /* MENU */
    font->draw(CurrentMenu[1].c_str(), core::rect<s32>(63, 7, 250, 60),
               video::SColor(140, 255, 255, 255));


    /*BATTERIA */
    USystem.GetBattery();
    driver->draw2DImage(bg1, core::position2d<s32>(441, 9),
                        core::rect<s32>(batt.X[0], batt.Y[0], batt.X[1], batt.Y[1]), 0,
                        video::SColor(255, 255, 255, 255), true);
    if (menu==0)
    {

        if (btm.anim<=15)
            btm.anim+=0.5;
        if (btm.anim_<=15)
            btm.anim_+=1;
        if (btm._anim>=0)
            btm._anim-=1;
        if (btm.alpha<=254)
            btm.alpha+=5;
        if (txt1.X<=460-(int)txtScorr[selected].size()*6)
            txt1.X+=1;
        for (i = 0; i <= 4; i++)
        {


            /* PULSANTI VERDI */
            driver->draw2DImage(bg1, core::position2d<s32>(i==selected?   btm.anim_+btm.anim:i==selected-1 && !direzione && !first?15+   btm._anim:i==selected+1 && direzione && !first?15+   btm._anim:btm.anim, 53+35*i),
                                core::rect<s32>(0, 300, 193, 331), 0,
                                video::SColor(i==selected?btm.alpha:btm.alpha-50, 255, 255, 255), true);
            /* TESTO DENTRO IL PULSANTE */
            driver->draw2DImage(bg1, core::position2d<s32>(i==selected?18+btm.anim_+btm.anim:i==selected-1 && !direzione && !first?15+18+btm._anim:i==selected+1 && direzione && !first?15+18+btm._anim:18+btm.anim, 63+35*i),
                                core::rect<s32>(17, 368+21*i, 91, 387+21*i), 0,
                                video::SColor(i==selected?btm.alpha:btm.alpha-50, 255, 255, 255), true);
        }

        /* CONTENITORE ARANCIONE */
        driver->draw2DImage(bg1, core::position2d<s32>(10,240),
                            core::rect<s32>(3, 335, 470, 365), 0,
                            video::SColor(230, 255, 255, 255), true);
        /*OMBRA*/
        font->draw(txtScorr[selected].c_str(), core::rect<s32>(txt1.X+1, 246, 250, 60),
                   video::SColor(20, 0, 0, 0));
        /*TESTO SCORREVOLE*/
        font->draw(txtScorr[selected].c_str(), core::rect<s32>(txt1.X, 245, 250, 60),
                   video::SColor(200, 255, 255, 255));
        /*IMG PIC*/
        driver->draw2DImage(bg1, core::position2d<s32>(0,240),
                            core::rect<s32>(0, 240 , 10, 272), 0,
                            video::SColor(255, 255, 255, 255), true);

    }
    else if (menu==3)
    {
        if (AnimAlpha_ALL<=254)
            AnimAlpha_ALL+=5;
        for (i=11; i<=289;)
        {
            i+=4;
            driver->draw2DImage(bg1, core::position2d<s32>(i,31),
                                core::rect<s32>(490, 24 , 494, 230), 0,
                                video::SColor(AnimAlpha_ALL, 255, 255, 255), true);
        }
        for (i=296; i<=456;)
        {
            i+=4;
            driver->draw2DImage(bg1, core::position2d<s32>(i,31),
                                core::rect<s32>(490, 24 , 494, 230), 0,
                                video::SColor(AnimAlpha_ALL, 255, 255, 255), true);
        }
        /*SELEZIONATORE*/
        driver->draw2DImage(bg1, core::position2d<s32>(18,Y_Barra_filelist),
                            core::rect<s32>(236, 492 , 505, 236+270), 0,
                            video::SColor(AnimAlpha_ALL, 255, 255, 255), true);

        /*Aggiunta di siberian star */
        filelistI = 0;

        for (numfiles = list_offset; filelistI < MAX_FILES_PER_PAGE && numfiles < filelist->getFileCount(); numfiles++)
        {
            array_Files_Dir[filelistI++] = filelist->getFileName(numfiles);
        }

        /*Stampo tutti i files della directory*/
        for (k = 0; k < filelistI; k++)
        {
            printf_filelist = 58 + k * 10;

            font2->draw(array_Files_Dir[k].c_str(),
                        core::rect<s32>(21, printf_filelist, 100, 60),
                        video::SColor(AnimAlpha_ALL,255, 255, 255));
            /* DIR / FILESIZE */

            /*if (filelist->isDirectory(k)==false)
            {
                FilesizeString = L"";
                //FileSize = FileSystem->createAndOpenFile(filelist->getFullFileName(k));
                FilesizeString += UFilelist.GetFileSize(filelist->getFullFileName(k))/1024;
                FilesizeString += L" kb";
                FilesizeString += L"      ";
                ScePspDateTime pspdatetime = UFilelist.GetFileCreationTime(filelist->getFullFileName(k));
                FilesizeString += pspdatetime.day;
                FilesizeString += L"/";
                FilesizeString += pspdatetime.month;
                FilesizeString += L"/";
                FilesizeString += pspdatetime.year;
            }*/


        }

        /*TESTO STATICO */
        font->draw(L"FileInfo:",
                   core::rect<s32>(24, 247, 100, 60),
                   video::SColor(AnimAlpha_ALL, 106, 168, 184));
        font->draw(filelist->isDirectory(file_selected)?L"Type:":L"FileSize:",
                   core::rect<s32>(223, 247, 100, 60),
                   video::SColor(AnimAlpha_ALL,106, 168, 184));
        font->draw(L"Creation Time:",
                   core::rect<s32>(324, 247, 100, 60),
                   video::SColor(AnimAlpha_ALL,106, 168, 184));
        /*TESTO DINAMICO*/
        font->draw(FileInfo[0].c_str(),
                   core::rect<s32>(74, 247, 100, 60),
                   video::SColor(AnimAlpha_ALL>=140?140:AnimAlpha_ALL, 255, 255, 255));
        font->draw(filelist->isDirectory(file_selected)?L"Dir":FileInfo[1].c_str(),
                   core::rect<s32>(273, 247, 100, 60),
                   video::SColor(AnimAlpha_ALL>=140?140:AnimAlpha_ALL,255, 255, 255));
        font->draw(FileInfo[2].c_str(),
                   core::rect<s32>(413, 247, 100, 60),
                   video::SColor(AnimAlpha_ALL>=140?140:AnimAlpha_ALL,255, 255, 255));

        /* CURR DIR */
        font2->draw(currdir.c_str(),
                    core::rect<s32>(21, 33, 100, 60),
                    video::SColor(AnimAlpha_ALL,255, 255, 255));
        /* QUICK RUN */
        font2->draw(L"Quick Run:",
                    core::rect<s32>(305, 33, 100, 60),
                    video::SColor(AnimAlpha_ALL,255, 255, 255));

        if (Dialog)
        {
            for (i=137; i<=343;)
            {
                i+=4;
                driver->draw2DImage(bg1, core::position2d<s32>(i,94),
                                    core::rect<s32>(490, 24 , 494, 115), 0,
                                    video::SColor(AnimAlpha_ALL, 255, 255, 255), true);
            }
            font2->draw(DialogTextTitle.c_str(),
                        core::rect<s32>(147, 95, 100, 60),
                        video::SColor(AnimAlpha_ALL,255, 255, 255));

            font2->draw(DialogText1.c_str(),
                        core::rect<s32>(147, 133, 100, 60),
                        video::SColor(AnimAlpha_ALL,255, 255, 255));

            font2->draw(DialogText2.c_str(),
                        core::rect<s32>(147, 147, 100, 60),
                        video::SColor(AnimAlpha_ALL,255, 255, 255));
        }
    }
    else if (menu==6)
    {
        if (AnimAlpha_ALL<=254)
            AnimAlpha_ALL+=5;
        for (i=11; i<=456;)
        {
            i+=4;
            driver->draw2DImage(bg1, core::position2d<s32>(i,31),
                                core::rect<s32>(490, 39 , 494, 230), 0,
                                video::SColor(AnimAlpha_ALL, 255, 255, 255), true);
        }
        /**BATTERY*/
        /**PERCENTUALE CARICA DELLA BATTERIA*/
        font->draw(USystem.BatteryLifePerc.c_str(), core::rect<s32>(21, 45, 250, 60),
                   video::SColor(AnimAlpha_ALL, 255, 255, 255));
        /**PERCENTUALE CARICA DELLA BATTERIA*/
        font->draw(USystem.BatteryLifeTime.c_str(), core::rect<s32>(21, 60, 250, 60),
                   video::SColor(AnimAlpha_ALL, 255, 255, 255));
        /**TEMPERATURA DELLA BATTERIA*/
        font->draw(USystem.BatteryTemp.c_str(), core::rect<s32>(21, 75, 250, 60),
                   video::SColor(AnimAlpha_ALL, 255, 255, 255));
        /**EXTERNAL POWER*/
        font->draw(USystem.IsPowerOnline.c_str(), core::rect<s32>(21, 90, 250, 60),
                   video::SColor(AnimAlpha_ALL, 255, 255, 255));
        /**BATTERY PRESENT*/
        font->draw(USystem.IsBatteryExist.c_str(), core::rect<s32>(21, 105, 250, 60),
                   video::SColor(AnimAlpha_ALL, 255, 255, 255));


        /**FREE MEMORY*/
        font->draw(USystem.FreeMemory.c_str(), core::rect<s32>(21, 120, 250, 60),
                   video::SColor(AnimAlpha_ALL, 255, 255, 255));


        /**CPU BUS*/
        font->draw(USystem.CpuClock.c_str(), core::rect<s32>(21, 135, 250, 60),
                   video::SColor(AnimAlpha_ALL, 255, 255, 255));

        font->draw(USystem.BusClock.c_str(), core::rect<s32>(21, 150, 250, 60),
                   video::SColor(AnimAlpha_ALL, 255, 255, 255));

        /**FIRMWARE*/
        font->draw(USystem.FirmwareVersion.c_str(), core::rect<s32>(21, 165, 250, 60),
                   video::SColor(AnimAlpha_ALL, 255, 255, 255));

        /**MAC*/
        font->draw(USystem.EthernetAddress.c_str(), core::rect<s32>(21, 180, 250, 60),
                   video::SColor(AnimAlpha_ALL, 255, 255, 255));


        /**IP*/
        font->draw(USystem.LocalIp.c_str(), core::rect<s32>(21, 195, 250, 60),
                   video::SColor(AnimAlpha_ALL, 255, 255, 255));

    }

}

