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



#ifndef     DRAW_H
#define     DRAW_H

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


struct animazione
{
    double X;
    double Y;
    double alpha;
    double anim , _anim , anim_;
};

struct sprites
{
    int X[1];
    int Y[1];
};

class CDraw
{
private:
    IGUISkin* skin;//puntatore skin

    video::ITexture* bg1;//puntatori immagini

    IGUIFont* font,*font2;

    core::stringw txtScorr[5];

    double AnimAlpha_ALL;

    IReadFile *FileSize;

    core::stringw FilesizeString;


public:

    //audio::IAudioSound* snd;//puntatore suono

    void InitDraw(gui::IGUIEnvironment* env,engineDevice *device,video::IVideoDriver* driver);

    void BigDraw(video::IVideoDriver* driver);

    void Set();

    void ResetAndSelect(int select);

};

#endif


