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

#include "run.h"
#include <systemctrl.h>


void CRun::LoadExec(core::stringc path)
{
    memset(&param, 0, sizeof(param));
    param.size = sizeof(param);
    param.args = strlen(path.c_str()) + 1;
    param.argp = (char*)path.c_str();
    sctrlKernelLoadExecVSHMs2(path.c_str(), &param);

}

