#ifndef HEADER_glyphOCR
#define HEADER_glyphOCR
//__OCR CLASSES_____________________________________
#include "config.h"
#include<string>
#include<vector>
#include<list>
#include<map>
#include "GBitmask/GBitmask.h"
#include "OCRTypes.h"

using namespace std;

namespace ocr {

///класс содержит данные буквы языка и методы обращения к ее графическим особеностям
	class glyphOCR {
	public:
		glyphOCR(void);
		virtual ~glyphOCR();
		void destroy(void);
		static glyphOCR* create(void){return new glyphOCR;}
		int letterIndex;           ///letter index in base
		unsigned int idNumber;     ///<id number in base
		int stringNum;
		int recordFlag;
		int recordStatus;
		unsigned long lengthSum;
		int angLength;
		vectorOCR v[300];
		int vectorCount;
		GBitMask32 mask32[300];    ///<<маски признаков
		GBitMask128 mask128[4];    ///>габаритные маски буквы
		int mask32Count;           ///<количество признаков
		int mask128Count;
		int dX,dY;                 ///<смещение координат центра буквы относительно изображения буквы  (mask128)
		string name;
		string Wylie;
		string OCRKey;
		int OCRIndex;
		int correlation;           ///<value of correlation
		int selfCorrelation;       ///<test value of self correlation
		int codeSpace;             ///<test value of test value of code space between this letter and all letters in letter base
		int Character;
		int vectorLimit;
		int stackFlag;
		int OCRStatus;
		int letterW;
		int letterH;
		int baseLetter;
		int xMin;
		int xMax;
		int yMax;
		int yMin;
		int xSum;
		int ySum;
		float scale;
		int cn;         //counter of this letter recognition
		unsigned int cnRes;      //rezult counter of this letter recognition (cCount/10 000)
		unsigned int crSum;  //buffer for store result of correlation this letter in text  
		unsigned int crRes;  //middle result of correlation
		int y0;   //верхний габарит строки относительно центра изображения буквы  (mask128)
		int y1;   //нижний габарит строки относительно центра изображения буквы (mask128)
		int textLineSize;  //size of text line in text in pixels
		int newLetter;
		int newLetterInBook;
		int allLetterCount;
		int letterBaseSize;
		
		void eraseMask(int id);
		void copy(glyphOCR* letter);
		void calibrateMask(GBitmap *img);
		void reloadMask();
		void maskFromVector();
        string drawToSVG();
	};

int operator==(const glyphOCR &left, const glyphOCR &right);
int operator<(const glyphOCR &left, const glyphOCR &right);


///main class for ctore all bata about letters in base

class letterBase{
public:
	letterBase(void);
	glyphOCR base[600];
	int letterCount;
	glyphOCR*  operator[](int index);
	int indexById(unsigned int Id);
	void  operator+=(glyphOCR ref);
	int textLineSize;
	string fontName;
};

};


#endif
