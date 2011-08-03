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

#ifndef __COMMON_H_INCLUDED__
#define __COMMON_H_INCLUDED__


#include <engine.h>
#include <pspkernel.h>

using namespace engine;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace audio;

int exitCallback(int arg1, int arg2, void *common);
int callbackThread(SceSize args, void *argp);
int setupCallbacks(void);


class PSPCommon
{
public:

    int setupPSP(void);

private:



};

#endif


