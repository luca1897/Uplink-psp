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
#ifndef FILELIST_H
#define FILELIST_H

#include    "main.h"

//**********************************************************************************
//	NAMESPACE
//**********************************************************************************

using namespace engine;
using namespace scene;
using namespace io;
using namespace video;
using namespace std;
using namespace net;
using namespace core;
using namespace gui;

class CFilelist
{
private:



public:

    void InitFileList();				   //inizializza la filelist
    int  execute(int index,int mode);
    int  getExts(core::stringc path);
    int  GetFileSize(const c8*filename);
    ScePspDateTime GetFileCreationTime(const c8*filename);
};
#endif
//*******************************  END OF FILE  ************************************


