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


#include "libdwgr.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include "drw_textcodec.h"
#include "dwgreader.h"
//#include "dxfwriter.h"


using namespace std;

#define FIRSTHANDLE 48

/*enum sections {
    secUnknown,
    secHeader,
    secTables,
    secBlocks,
    secEntities,
    secObjects
};*/

dwgR::dwgR(const char* name){
    fileName = name;
    reader = NULL;
//    writer = NULL;
    applyExt = false;
    version = DRW::UNKNOWNV;
    error = DRW::BAD_NONE;
}
dwgR::~dwgR(){
    if (reader != NULL)
        delete reader;

}

bool dwgR::read(DRW_Interface *interface_, bool ext){
    bool isOk = false;
    error = DRW::BAD_NONE;
    applyExt = ext;
    ifstream filestr;
    DBG("dwgR::read 1\n");
    filestr.open (fileName.c_str(), ios_base::in | ios::binary);
    if (!filestr.is_open() || !filestr.good() ){
        error = DRW::BAD_OPEN;
        return isOk;
    }

    char line[6];
    filestr.read (line, 6);
    iface = interface_;
    DBG("dwgR::read 2\n");
    DBG("dwgR::read line version: ");
    DBG(line);
    DBG("\n");

    if (strcmp(line, "AC1006") == 0)
        version = DRW::AC1006;
    else if (strcmp(line, "AC1009") == 0) {
        version = DRW::AC1009;
//        reader = new dwgReader21(&filestr, this);
    }else if (strcmp(line, "AC1012") == 0){
        version = DRW::AC1012;
        reader = new dwgReader15(&filestr, this);
    } else if (strcmp(line, "AC1014") == 0) {
        version = DRW::AC1014;
        reader = new dwgReader15(&filestr, this);
    } else if (strcmp(line, "AC1015") == 0) {
        version = DRW::AC1015;
        reader = new dwgReader15(&filestr, this);
    } else if (strcmp(line, "AC1018") == 0){
        version = DRW::AC1018;
//        reader = new dwgReader18(&filestr, this);
    } else if (strcmp(line, "AC1021") == 0) {
        version = DRW::AC1021;
//        reader = new dwgReader21(&filestr, this);
    } else if (strcmp(line, "AC1024") == 0) {
        version = DRW::AC1024;
//        reader = new dwgReader21(&filestr, this);
    } else
        version = DRW::UNKNOWNV;

    if (reader != NULL) {
        isOk = processDwg();
    } else
        error = DRW::BAD_VERSION;

    filestr.close();
    if (reader != NULL) {
        delete reader;
        reader = NULL;
    }
    return isOk;
}

/*bool dwgR::write(DRW_Interface *interface_, DRW::Version ver, bool bin){
    bool isOk = false;
    return isOk;
}*/

/********* Reader Process *********/

bool dwgR::processDwg() {
    DBG("dwgR::processDwg() start processing dwg\n");
    bool ret;
    bool ret2;
    ret = reader->readFileHeader();
    if (!ret) {
        error = DRW::BAD_READ_FILE_HEADER;
        return ret;
    }
    //RLZ todo    readDwgHeader();
    //RLZ todo    readDwgClasses();
    ret = reader->readDwgObjectOffsets();
    if (!ret) {
        error = DRW::BAD_READ_OFFSETS;
//        return ret;
    }

    ret2 = reader->readDwgTables();
    if (ret && !ret2) {
        error = DRW::BAD_READ_TABLES;
        ret = ret2;
    }

    for (std::map<int, DRW_LType*>::iterator it=reader->ltypemap.begin(); it!=reader->ltypemap.end(); ++it) {
        DRW_LType *lt = it->second;
        iface->addLType(const_cast<DRW_LType&>(*lt) );
    }
    for (std::map<int, DRW_Layer*>::iterator it=reader->layermap.begin(); it!=reader->layermap.end(); ++it) {
        DRW_Layer *ly = it->second;
        iface->addLayer(const_cast<DRW_Layer&>(*ly));
    }

    for (std::map<int, DRW_Block*>::iterator it=reader->blockmap.begin(); it!=reader->blockmap.end(); ++it) {
        DRW_Block *bk = it->second;
        iface->addBlock(const_cast<DRW_Block&>(*bk));
        iface->endBlock();
    }

    std::map<int, DRW_Block*>::iterator bkit = reader->blockmap.find(0);
    if (bkit == reader->blockmap.end()){//fail, find by name
        reader->currBlock = 0;
    } else
        reader->currBlock = 0;

    iface->setBlock(0);
    for (std::list<objHandle>::iterator it=reader->ObjectMap.begin(); it != reader->ObjectMap.end(); ++it){
        DBG("object map Handle= "); DBG(it->handle); DBG(" "); DBG(it->loc); DBG("\n");
        ret2 = reader->readDwgEntity(*it, *iface);
    }

    if (ret && !ret2) {
        error = DRW::BAD_READ_ENTITIES;
        ret = ret2;
    }
    return ret;
}
