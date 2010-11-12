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

//if ( ImBuf !=NULL ) farfree(ImBuf);  //  освобождение памяти
//q=(тип_q *)farmalloc(n_byte);     // запрос памяти без очистки 0
//q_new=farrealloc(q_old,n_byte);;  // изменение размера блока


#ifndef _GImageEditor_H_
#define _GImageEditor_H_
#include "config.h"

#include <stdlib.h>

#include "OCRTypes/OCRTypes.h"
#include "pugixml/pugixml.hpp"
#include "GBitmap/GBitmap.h"
#include "GBitmapInt/GBitmapInt.h"
#include "GBitset/GBitset_.h"
#include "GBitsetMatrix/GBitsetMatrix.h"
#include "GBitsetContour/GBitsetContour.h"
#include "GBitsetOCR/GBitsetOCR.h"
#include "OCRString/php2stl.h"
#include "../../libtiff/tiffio.h"


#ifdef WIN_BS //Vic WIN32
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include "ieview.hpp"
#include "imageenview.hpp"
#include <vcl.h>
#endif

#pragma hdrstop

using namespace std;
using namespace pugi;

namespace ocr{
///Основной диспетчерский класс. Обеспечивает ввод и ввывод, логику создания и выполнения процессов обработки как изображения так и текста.
class  GImageEditor {
protected:
  GImageEditor(void);
  GImageEditor(int nrows, int ncolumns, int border=0);
  GImageEditor(const GImageEditor *ref);
  GImageEditor(const GImageEditor *ref, int border);
 public:
  virtual ~GImageEditor();
  void destroy(void);
  /** @name Initialization. */
  //@{
  void init();
protected:
public:
		GBitmap *pechaImg, *baseImg;              ///<global bitmap data 
		//GBitmap *pechaImgContour;
		vectorOCR vectorBase[300];   //
		letterBase aliKali;                             ///<main letter OCR base
	    vector<letterBase>aliKaliStore;                 ///<Array of all letterBase from letterStore
	    vector<string>letterSign;                       ///<Array of vowel letters
	    vector<string>letterScale;                      ///<Array of scale letters
		glyphOCR glyphNew;
		//vector<stringOCR>strArray;                     ///<global array of page string data
		map<string,uniRecord>uniTibTable;
 	    vector<stringOCR>correctionTable; ///vector of all unsertan and hand-checked letters for draw in correction table
	    GLogicProcessor *logicProcessor;
		//commandData inputData;
		unsigned int vectorCount;
		GBitset *setBit;
		GBitsetContour *setContour;
		//GBitsetOCR *setOCR;
		int stringIndex, wordIndex, iLeft,iTop;
		int pechaDataLoaded;
		string mainString;
	    unsigned char hexCode[18991]; //byte to char string hex code
#ifdef WIN_BS//Vic WIN32	  
		TIEBitmap *bitmapImg;
#endif	
		short PechaLoaded;
		int print;
		//TmainOCRObject *newOCRObject;
		ofstream c_out;

		static GImageEditor* create(void) {return new GImageEditor;}
	    ///диспетчер выполнения процесса распознавания страницы.
	    ///создает все необходимые объекты, контролирует ход выполнения процедур и формирует результат
		void startOCR(commandData *inputData);
	    ///читает и интерпретирует команды интерфейса записанные в управляющий файл input.xml 
	    string readInputAction(commandData *inputData);
	    void startOCR_socket(commandData *inputData);  ///<(deprecated)
        ///На Маке запускает восемь потоков постраничного распознавания. На PC вополняет постраничное распознавание
	    void startOCRBatch(commandData *inputData);    
	    void startOCRBatch_socket(commandData *inputData);  ///<(deprecated)
	    ///распознавание фрагмента текста из корректурной таблицы
	    string letterBlockCorrelation(commandData *inputData,unsigned int in);
		void pageToBase(commandData *inputData); ///<(deprecated)
	    ///На Маке запускает 8 потоков обработки изображений (proccessImage). На PC обрабатывает изображения в один поток. main multi praccessor image proccesing batch
		void imageProcess(commandData *inputData); 
	    /// Выполнение функций обработки изображения. Авто поворот, чистка бордюров, деление на колонки, масштабирование.  image proccesing implementation
	    void proccessImage(commandData *inputData, GBitmap *pechaImg); 


        ///отладочная функция вывода графической информации процесса распознавания
		void drawString(int nStr,int border);
		///вывод результатов распознавания в HTML файл постранично.
		void drawStrArray(commandData *inputData,vector<stringOCR>&strArray,int border);
		///вывод результатов распознавания в HTML файл постранично с сохранением графических обьектов строк и букв. Используется при ручном составлении и коррекции базы букв.
        void drawStrArrayDebug(commandData *inputData,vector<stringOCR>&strArray, int border);
	    ///формирование корректурных таблиц на основании грамматической проверки теста
	    void drawLettersInCorrectionTable(commandData *inputData,int mode);
        ///вывод всей таблицы букв в HTML файл
	    string drawBase(commandData *inputData,string data);
	    ///вывод одной буквы в HTML
	    string drawLetter(commandData *inputData, unsigned int idNumder);
	    ///вывод окна редактирования буквы
	    string drawEditLetter(commandData *inputData,unsigned int idNumder);
	    ///вывод коректурных таблиц в HTML файл
	    string drawCorrectionTable(commandData *inputData,string data);
     	///draw image as JPEG data for HTTP and file operations
	    string drawToString(GBitmap *data); 
	    ///draw image as TIFF GroupFax4 data for HTTP and file operations
	    string drawToTiffString(GBitmap *data); 
	    ///рисование одного фрагмента текста из корректурной таблицы
		string drawLetterBlock(commandData *inputData,unsigned int idNumber);
	    ///рисование одного фрагмента текста из корректурной таблицы для редактуры
	    string drawEditLetterBlock(commandData *inputData,string &resultOCR, unsigned int idNumber);
	    ///чтение данных базы букв из OCRData/OCRTables/OCRLetterBase.xml //@@@ нужо читать все базы из папки
		void readLetterBase(commandData *inputData);
	    void readFontDataXML(string &path);
		///чтение всех данных баз букв из OCRData/OCRTables/OCRLetterBase.xml //@@@ слишком дорого по памяти и времени
		void readLetterStore(commandData *inputData);
		///запись данных базы букв из OCRData/OCRTables/OCRLetterBase.xml //@@@ нужо записывать все измененные базы
	    void writeLetterBase(commandData *inputData);
		///функция читает результаты первого прогона распознавания книги. Пока не пригодилась, проще распознать заново
	    void readStrArray(commandData *inputData,vector<stringOCR>&strArray);
		///функция пишет гна диск результаты первого прогона распознавания книги. Пока не пригодилась, проще распознать заново
	    void writeStrArray(commandData *inputData,vector<stringOCR>&strArray);
	    ///запись на диск результаты распознавания в XML файл. Формат необходимо согласовывать с TBRC
	    void writePageXML(commandData *inputData);
 	    ///записывает в базу статистику использования буквы  //@@@ нужно дорабатывать
	    void writeLetterStat(commandData *inputData);

		///на основании координат буквы копирует ее изображение из текста, векторизует, определяет признаки буквы и создает запись в базе букв
	    void setLetter(commandData *inputData);
	    ///определяет с каким максимальным коеффициентом корреляции и в каком масштабе данная буква изображена в GBitmap. Данные о масштабе записываются в букву
	    int setLetterScale(GBitmap *img128, glyphOCR *glyph_);
	    ///один из вариантов определить что за буква для занесения в базу. Ищет похожую букву во всех сохраненных базах. 
		/// не проходит по памяти и вариабельности. (не находит себя в базах)
	    void setLetterFromStore(commandData *inputData, glyphOCR *letter,GBitmap* img128); 
	    ///This function check correlation of test letter with all letters database and return array of letters with close correlation
	    ///проверяет есть ли похожие буквы в базе. Функцию нужно существенно расширить. Необходимо выявить в базе ВСЕ слишком похожие буквы.
	    ///В наилучшем результате между всеми буквами базы должно быть наибольшее кодовое расстояние.
	    string testLetter(commandData *inputData, unsigned int idNumber);
		///This function check correlation of every letter with all letters database and return array of letters with close correlation
		///проверяет есть ли похожие буквы в базе. Функцию нужно существенно расширить. Необходимо выявить в базе ВСЕ слишком похожие буквы.
		///В наилучшем результате между всеми буквами базы должно быть наибольшее кодовое расстояние.
		void testBase(commandData *inputData);
	    ///определение величины корреляции между изображением и буквой с заданным масштабом. function need copy of actual letter. It store OCR information 
	    int  setCorrelation(GBitmap *img, glyphOCR *glyph,float scale);
	    ///внесение изменений в базу букв на основе редактирования буквы через интерфейс
		void setBase(commandData *inputData);
	    ///чтение данных корректeрных таблиц из XML файла
	    void readCorrectionTable(commandData *inputData);
		/// This function build letter base from text file of alphabet
	    /// генерация базы букв на основании текстового файла алфавита. Функция платформо зависима.
	    void buildLetter(commandData *inputData);

		//void LoadImageFromPath(string &imgPath);
		/// Загрузка данных из графического файла. Проверка на пригодность данных.  Функция платформо зависима.
		GBitmap* LoadImageData(string &inputPath,bool invert);
	    /// Загрузка данных из TiffGroupFax4. Проверка на пригодность данных. Реализована на базе TiffLib.
	    GBitmap* loadFromTiffString(string &dataStr, bool invert);   
        ///Запись данных Bitmap в графический файл. Функция платформо зависима.
		void WriteImageData(GBitmap *data,string &path,bool flip, string &mode);
		///Запись данных Bitmap в графический файл. Функция платформо зависима. 
	    void WriteImageData(GBitmap *data,const char* path, bool invert);
   	    ///Запись данных Bitmap в графический файл. Функция платформо зависима.
	    void WriteImageData(GBitmap *data,string &path, bool invert);
        ///Запись данных Bitmap в графический файл. Функция платформо зависима.
	    void WriteImageData(GBitmapInt *data,string &path, bool invert);
        ///Запись данных Bitmap в графический файл. Функция платформо зависима. 
	    void WriteImageData(GBitset *data,string &path, bool invert);
		///Запись данных Bitmap в графический файл. Функция платформо зависима.
	    void WriteImageData(GBitset *data,const char* path, bool invert);
		///Деление на колонки и запись в файл
		void WriteColumnsData(GBitmap *data, GBitset *set, int nFrm, string &filePath);
		///Деление на разворота на страницы и запись в файл
		void WriteSpreadData(GBitmap *data, GBitset *set, int nFrm, string &filePath);
		///Определение и чистка бордюров вокруг текста
		void RemoveBorder(GBitmap *data, GBitset *set, int pageBorder, string &filePath);

	    void setHex(); //set conversion hex code
		
	
	    ///что-то из области фантастики. Читает и интерпретирует HTML файл результатов распознавания. 
	    void readPageHTML(commandData *inputData,vector<stringOCR>&strArray);
	           //Start detect scan page rotation. i - angle rotation limit
	           //void detectRotation(short i);

		//void LoadImage_mark();
		//void EncodeDjvuExe(AnsiString filePath);
		//void SavePDFAsDjVu();
		//void blur_aniso(short fileIndex);
		//void LoadDjvu();
		//void SaveDjvuExe(TStringList *fileList);
		//void EncodeDjvu(AnsiString filePath);
		//void collectDjvu();
		//void LoadDjvuExe();
};
};
// ---------------- IMPLEMENTATION
# endif

