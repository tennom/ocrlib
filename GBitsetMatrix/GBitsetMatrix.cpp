//C-
//C- This software is subject to, and may be distributed under, the
//C- GNU General Public License, either Version 2 of the license,
//C- or (at your option) any later version. The license should have
//C- accompanied the software or you may obtain a copy of the license
//C- from the Free Software Foundation at http://www.fsf.org .
//C-
//C- This program is distributed in the hope that it will be useful,
//C- but WITHOUT ANY WARRANTY; without even the implied warranty of
//C- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//C- GNU General Public License for more details.
//C-

# include "config.h"

#include "GBitsetMatrix.h"
#include <string.h>
#include <time.h>
#include <math.h>

# ifdef WIN32_DRAW
#include "ieview.hpp"
#include "imageenview.hpp"
#include "iemview.hpp"
#include "ievect.hpp"
#include "imageen.hpp"
#include "ImageEditorMain.h"
#endif


namespace ocr {

#include "GBitsetMatrix_base.h"
#include "MartixCorrelation.h"
#include "MatrixCorrelationASM.h"
#include "letterCorrelation.h"
#include "letterToLetterCorrelation.h"	
#include "Matrix_Lion.h"
#include "GBitsetMatrix_level.h"







}//_____________________________________________________________________________



