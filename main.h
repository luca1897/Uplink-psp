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


#ifndef __C_MAIN_H_INCLUDED__
#define __C_MAIN_H_INCLUDED__

#include <systemctrl.h>
#include <pspctrl.h>
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pspctrl.h>

#include <engine.h>

#include <psprtc.h>
#include <pspiofilemgr.h>
#include <pspmodulemgr.h>
#include <pspkernel.h>
#include <pspusb.h>
#include <pspusbstor.h>
#include <pspthreadman.h>
#include <pspnet.h>
#include <pspnet_inet.h>
#include <pspsdk.h>
#include    <psppower.h>
#include <pspdebug.h>
#include <string.h>
#include <pspwlan.h>
#include <systemctrl.h>
#include <psputility_netmodules.h>
#include <psputility_netparam.h>
#include <netinet/in.h>
#include <pspnet_apctl.h>
#include <pspnet_resolver.h>
#include <psphttp.h>
#include <pspssl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "system.h"
#include "common.h"
#include "filelist.h"
#include "run.h"
#include "net.h"
#include "draw.h"


using namespace engine;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace audio;


class CMain : public IEventReceiver
{
public:

    CMain();

    ~CMain();

    void run();

    virtual bool OnEvent(SEvent event);

    int UpLastTime,DownLastTime,TriangleLastTime,CrossLastTime,CircleLastTime;

    void InitNetwork();

    void Log(core::stringc Text);

    //0 = main menu

private:

    video::SColor backColor;

};

#endif

