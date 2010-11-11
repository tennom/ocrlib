
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#if NEED_GNUG_PRAGMAS
# pragma implementation
#endif

#include <iostream>
using namespace std;

#include "GBitsetOCR.h"
#include <string.h>
#include <time.h>
#include <math.h>

#ifdef WIN32_DRAW
#include "ieview.hpp"
#include "imageenview.hpp"
#include "iemview.hpp"
#include "ievect.hpp"
#include "imageen.hpp"
#include "ImageEditorMain.h"
#endif


namespace ocr {

#include "GBitset_baseOCR.h"
#include "GBitset_setDataOCR.h"
#include "textOCR.h"
#include "setOCRCorrelation.h"
#include "setOCRRecordCorrelation.h"
#include "setScaleRecord.h"
#include "testCassidyMatch.h"
#include "setMatch.h"

#include "lineOCR.h"	

}
using namespace ocr;



