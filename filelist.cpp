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
 
#include "filelist.h"

extern IFileList *filelist;
extern IFileSystem *FileSystem;
extern CRun URun;

extern int CountFileDir,menu,filelistI,k,Y_Barra_filelist,file_selected,list_offset;
extern core::stringw currdir,CurrentMenu[2];

int FileType;
/*
1 = PBP
2 = RAR
3 = ZIP
4 = LUA
*/

//{DIALOG
extern bool Dialog;
extern core::stringw DialogTextTitle;
extern core::stringw DialogText1;
extern core::stringw DialogText2;
//DIALOG}


void CFilelist::InitFileList()
{
    filelist = FileSystem->createFileList();

    /*Prendo la directory corrente*/
    currdir =    L"";
    currdir +=   FileSystem->getWorkingDirectory();
    CountFileDir = filelist->getFileCount();
    //if(PBPPath.equalsn("0",1))PBPPath=FileSystem->getWorkingDirectory();
}

int  CFilelist::execute(int index,int mode)
{
    if(mode==1)//dir & confirm
    {
        if (filelist->isDirectory(index))
        {
            filelistI = 0;
            k = 0;
            FileSystem->changeWorkingDirectoryTo(filelist->getFullFileName(index));
            filelist->drop();
            InitFileList();
            Y_Barra_filelist = 56;
            file_selected = 0;
            list_offset = 0;
        }
        else if(getExts(filelist->getFullFileName(index))==1)
        {
            Dialog = true;
            DialogTextTitle = L"";
            DialogTextTitle += L"-    Uplink Info";
            DialogText1 = L"";
            DialogText1 += L">> Press X to launch the EBOOT";

            DialogText2 = L"";
            DialogText2 += L">> Press O to return";
            //URun.LoadExec(filelist->getFullFileName(index));
        }
    }
    else if(mode==2) //execute
    {
        if(getExts(filelist->getFullFileName(index))==1)
            URun.LoadExec(filelist->getFullFileName(index));
    }

}



int CFilelist::getExts(core::stringc path)
{
    int lunghezza;
    core::stringw extbase;

    core::stringw ext;

    extbase = "";
    extbase += path.c_str();
    lunghezza = extbase.size();
    ext = "";
    ext += extbase[lunghezza-3];
    ext += extbase[lunghezza-2];
    ext += extbase[lunghezza-1];

    if ((ext.equalsn("pbp", 3)) || (ext.equalsn("PBP", 3)))
    {
        return 1;
    }
    if ((ext.equalsn("lua", 3)) || (ext.equalsn("LUA", 3)))
    {
        return 2;
    }
    if ((ext.equalsn("rar", 3)) || (ext.equalsn("RAR", 3)) || (ext.equalsn("zip", 3)) || (ext.equalsn("ZIP", 3)))
    {
        return 3;
    }

    return 4;
}

int CFilelist::GetFileSize(const c8*filename)
{
    SceIoStat stat;
    sceIoGetstat(filename, &stat);
    return (int)stat.st_size;
}

ScePspDateTime CFilelist::GetFileCreationTime(const c8*filename)
{
    SceIoStat stat;
    sceIoGetstat(filename, &stat);
    return stat.st_ctime;
}
