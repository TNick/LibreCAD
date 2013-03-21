QT       -= core gui
TEMPLATE = app
CONFIG += console warn_on

# Use common project definitions.
include(../../settings.pro)
include(../../common.pro)

# google test library
LIBS += -lgtest_main -lgtest # -ldxfrw

# debug output; can't use that because it requires an fricking extern QTextStream readLog;
# DEFINES += DRWG_DBG=1

SOURCES += \
    tests/DRW_Xline_test.cpp \
    tests/DRW_Viewport_test.cpp \
    tests/DRW_Vertex_test.cpp \
    tests/DRW_Unknown_test.cpp \
    tests/DRW_Trace_test.cpp \
    tests/DRW_Text_test.cpp \
    tests/DRW_Spline_test.cpp \
    tests/DRW_Solid_test.cpp \
    tests/DRW_Ray_test.cpp \
    tests/DRW_Polyline_test.cpp \
    tests/DRW_Point_test.cpp \
    tests/DRW_Overlaybox_test.cpp \
    tests/DRW_Mtext_test.cpp \
    tests/DRW_LwPolyline_test.cpp \
    tests/DRW_Line_test.cpp \
    tests/DRW_Leader_test.cpp \
    tests/DRW_Insert_test.cpp \
    tests/DRW_Image_test.cpp \
    tests/DRW_Hatch_test.cpp \
    tests/DRW_Ellipse_test.cpp \
    tests/DRW_E3DFace_test.cpp \
    tests/DRW_DimRadial_test.cpp \
    tests/DRW_DimOrdinate_test.cpp \
    tests/DRW_DimLinear_test.cpp \
    tests/DRW_Dimension_test.cpp \
    tests/DRW_DimDiametric_test.cpp \
    tests/DRW_DimAngular_test.cpp \
    tests/DRW_DimAngular3P_test.cpp \
    tests/DRW_DimAligned_test.cpp \
    tests/DRW_ConstructionLine_test.cpp \
    tests/DRW_Circle_test.cpp \
    tests/DRW_Block_test.cpp \
    tests/DRW_Arc_test.cpp \
    src/libdxfrw.cpp \
    src/libdwgr.cpp \
    src/dxfwriter.cpp \
    src/dxfreader.cpp \
    src/dwgreader.cpp \
    src/dwgbuffer.cpp \
    src/drw_textcodec.cpp \
    src/drw_objects.cpp \
    src/drw_entities.cpp \
    tests/dwgBuffer_test.cpp

HEADERS += \
    src/libdxfrw.h \
    src/libdwgr.h \
    src/dxfwriter.h \
    src/dxfreader.h \
    src/dwgreader.h \
    src/dwgbuffer.h \
    src/drw_textcodec.h \
    src/drw_objects.h \
    src/drw_interface.h \
    src/drw_entities.h \
    src/drw_cptables.h \
    src/drw_cptable950.h \
    src/drw_cptable949.h \
    src/drw_cptable936.h \
    src/drw_cptable932.h \
    src/drw_base.h


