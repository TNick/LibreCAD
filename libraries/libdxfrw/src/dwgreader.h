/******************************************************************************
**  libDXFrw - Library to read/write DXF files (ascii & binary)              **
**                                                                           **
**  Copyright (C) 2011 Rallaz, rallazz@gmail.com                             **
**                                                                           **
**  This library is free software, licensed under the terms of the GNU       **
**  General Public License as published by the Free Software Foundation,     **
**  either version 2 of the License, or (at your option) any later version.  **
**  You should have received a copy of the GNU General Public License        **
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.    **
******************************************************************************/

#ifndef DWGREADER_H
#define DWGREADER_H

#include <map>
#include <list>
#include "drw_textcodec.h"
#include "dwgbuffer.h"
#include "libdwgr.h"

class objHandle{
public:
    objHandle(dint32 t, dint32 h, dint32 l){
        type = t;
        handle = h;
        loc = l;
    }
    dint32 type;
    dint32 handle;
    dint32 loc;
};

class dwgReader {
public:
    dwgReader(std::ifstream *stream, dwgR *p){
//        filestr = stream;
        buf = new dwgBuffer(stream);
        parent = p;
        decoder.setVersion(DRW::AC1021);//default 2007 in utf8(no convert)
        decoder.setCodePage("UTF-8");
#ifdef DRWG_DBG
//        count =0;
#endif
    }
    virtual ~dwgReader();
    virtual bool readFileHeader() = 0;
    //RLZ todo    virtual bool readDwgHeader() = 0;
    //RLZ todo    virtual bool readDwgClasses() = 0;
    virtual bool readDwgObjectOffsets() = 0;
    virtual bool readDwgTables() = 0;
    virtual bool readDwgEntity(objHandle& obj, DRW_Interface& intfa) = 0;
    void parseAttribs(DRW_Entity* e);

    void setCodePage(std::string *c){decoder.setCodePage(c);}
    std::string getCodePage(){ return decoder.getCodePage();}

public:
    std::list<objHandle>ObjectMap;
    std::map<int, DRW_LType*> ltypemap;
    std::map<int, DRW_Layer*> layermap;
    std::map<int, DRW_Block_Record*> block_recmap;
    std::map<int, DRW_Block*> blockmap;
    int currBlock;

protected:
    dwgBuffer *buf;
    dwgR *parent;
    DRW::Version version;

    duint32 seekerImageData;
//sections map
    std::map<std::string, std::pair<dint32,dint32 > >sections;

protected:
    DRW_TextCodec decoder;
};

class dwgReader15 : public dwgReader {
public:
    dwgReader15(std::ifstream *stream, dwgR *p):dwgReader(stream, p){ }
    virtual ~dwgReader15() {
        //RLZ: clear & destroy ltmap;
    }
    bool readFileHeader();
    //RLZ todo    bool readDwgHeader();
    //RLZ todo    bool readDwgClasses();
    bool readDwgObjectOffsets();
    bool readDwgTables();
    bool readDwgEntity(objHandle& obj, DRW_Interface& intfa);
};

class dwgReader18 : public dwgReader {
public:
    dwgReader18(std::ifstream *stream, dwgR *p):dwgReader(stream, p){ }
    virtual ~dwgReader18(){}
    bool readFileHeader();
    //RLZ todo    bool readDwgHeader();
    //RLZ todo    bool readDwgClasses();
    bool readDwgObjectOffsets(){return false;}
    bool readDwgTables(){return false;}
    bool readDwgEntity(objHandle& obj, DRW_Interface& intfa);
};

#endif // DWGREADER_H
