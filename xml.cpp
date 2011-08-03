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


#include "xml.hpp"

//**********************************************************************************
//	Extern var
//**********************************************************************************

extern MUplink CUplink;

extern UplinkUpdate    uplinkupdate;

extern int MenuSelez;

extern bool xmlLetto;

extern  core::stringc PBPPath;		     //path dell'eboot

extern core::stringw ServerTesto;
//**********************************************************************************
//   Variabili
//**********************************************************************************

int Dimensione[19];		//ARRAY CON LE DIMENSIONI DEI FILE
int RELEASENUMBER = 400;	//numero di versione uplink
int CicloSplit;			//Ciclo che splitta e rimpiazza /n /r
int CicloSplitNews;		//Ciclo che splitta le news
int i;
int VersioneUplink;

core::stringw CicloTitoloi = "";	     //mi serve nell'xml
core::stringw array_Files_Dir[100];	     //Array contenente i nomi dei files/dir
core::stringw Download_Titolo[19];	     //Array di download
core::stringw Url_Titolo[19] = 0;	     //Array url
core::stringw News_Titolo[8];		     //Array di titoli
core::stringw AutoreHB[19] = 0;		     //Array autore HB
core::stringw Descrizione[19] = 0;	     //Array descrizione HB
core::stringw News_Commento[8][52];	     //Array di commenti
core::stringc ListaServer[8];
core::stringc LinkServer [8];
core::stringc LinkNews   [8];

int NumeroServer;

void CXML::ServerReader()
{
    int i;

    while (xmlServer && xmlServer->read())
    {
        if (core::stringw("server") == xmlServer->getNodeName())
        {
            NumeroServer = xmlServer->getAttributeValueAsInt(L"numserver");
        }

        if (core::stringw("server") == xmlServer->getNodeName())
        {
            for (i = 0; i <= 7; i++)
            {
                CicloTitoloi = "";
                CicloTitoloi += "server";
                CicloTitoloi += i + 1;
                ListaServer[i] = xmlServer->getAttributeValue(CicloTitoloi.c_str());
            }
        }

        if (core::stringw("server") == xmlServer->getNodeName())
        {
            for (i = 0; i <= 7; i++)
            {
                CicloTitoloi = "";
                CicloTitoloi += "link";
                CicloTitoloi += i + 1;
                LinkServer[i] = xmlServer->getAttributeValue(CicloTitoloi.c_str());
            }
        }

        ServerTesto = "";
        ServerTesto += "Numero Server: ";
        ServerTesto += NumeroServer;
    }

    delete xmlServer;

}

void CXML::xmlReader()
{

    xml = CUplink.device->getFileSystem()->createXMLReader("immagini/pspita.xml");
    while (xml && xml->read())
    {
        if (core::stringw("ver") == xml->getNodeName())
        {
            VersioneUplink = xml->getAttributeValueAsInt(L"vers");
            uplinkupdate.dim_tot = xml->getAttributeValueAsInt(L"vers1") / 1024;
        }

        if (VersioneUplink >= RELEASENUMBER)
        {
            MenuSelez = 5;
        }
        else
        {
            if (core::stringw("news") == xml->getNodeName())
            {
                for (i = 0; i <= 7; i++)
                {
                    CicloTitoloi = "";
                    CicloTitoloi += "titolo";
                    CicloTitoloi += i + 1;
                    News_Titolo[i] = xml->getAttributeValue(CicloTitoloi.c_str());
                    if(News_Titolo[i] == "")
                    {
                        News_Titolo[i] = "- Untitled -";
                    }
                }
            }

            /** Link delle news*/
            if (core::stringw("linknews") == xml->getNodeName())
            {
                for (i = 0; i <= 7; i++)
                {
                    CicloTitoloi = "";
                    CicloTitoloi += "linknws";
                    CicloTitoloi += i + 1;
                    LinkNews[i] = xml->getAttributeValue(CicloTitoloi.c_str());
                }
            }

            if (core::stringw("commento") == xml->getNodeName())
            {
                for (i = 0; i <= 7; i++)
                {
                    CicloTitoloi = "";
                    CicloTitoloi += "commento";
                    CicloTitoloi += i + 1;
                    News_Commento[i][0] = xml->getAttributeValue(CicloTitoloi.c_str());
                }

                for (CicloSplit = 0; CicloSplit <= 7; CicloSplit++)
                {
                    News_Commento[CicloSplit][0].replace('\n', ' ');
                    News_Commento[CicloSplit][0].replace('\r', ' ');
                    News_Commento[CicloSplit][0].trim();
                }

                for (CicloSplit = 0; CicloSplit <= 7; CicloSplit++)
                {
                    for (CicloSplitNews = 1; CicloSplitNews <= (News_Commento[CicloSplit][0].size() / 75) + 1; CicloSplitNews++)
                    {
                        News_Commento[CicloSplit][CicloSplitNews] = News_Commento[CicloSplit][0].subString((CicloSplitNews - 1) * 75, 75);
                    }
                }
            }
            if (core::stringw("download") == xml->getNodeName())
            {
                for (i = 0; i <= 17; i++)
                {
                    CicloTitoloi = "";
                    CicloTitoloi += "download";
                    CicloTitoloi += i + 1;
                    Download_Titolo[i] = xml->getAttributeValue(CicloTitoloi.c_str());
                }
            }

            if (core::stringw("url") == xml->getNodeName())
            {
                for (i = 0; i <= 17; i++)
                {
                    CicloTitoloi = "";
                    CicloTitoloi += "url";
                    CicloTitoloi += i + 1;
                    Url_Titolo[i] = xml->getAttributeValue(CicloTitoloi.c_str());
                }
            }
            if (core::stringw("authors") == xml->getNodeName())
            {
                for (i = 0; i <= 17; i++)
                {
                    CicloTitoloi = "";
                    CicloTitoloi += "author";
                    CicloTitoloi += i + 1;
                    AutoreHB[i] = xml->getAttributeValue(CicloTitoloi.c_str());
                }
            }

            if (core::stringw("description") == xml->getNodeName())
            {
                for (i = 0; i <= 17; i++)
                {
                    CicloTitoloi = "";
                    CicloTitoloi += "description";
                    CicloTitoloi += i + 1;
                    Descrizione[i] = xml->getAttributeValue(CicloTitoloi.c_str());
                }
            }
            /** Dimensione dei files*/
            if (core::stringw("dims") == xml->getNodeName())
            {
                for (i = 0; i <= 17; i++)
                {
                    CicloTitoloi = "";
                    CicloTitoloi += "dim";
                    CicloTitoloi += i + 1;
                    Dimensione[i] = xml->getAttributeValueAsInt(CicloTitoloi.c_str());
                }
            }

            xmlLetto = true;
            //MenuSelez = 4;
        }
    }
    delete xml;

}


