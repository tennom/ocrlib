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
//C- GNU General Public License for .more details.
//C-

//if ( ImBuf !=NULL ) farfree(ImBuf);  //  освобождение памяти
//q=(тип_q *)farmalloc(n_byte);     // запрос памяти без очистки 0
//q_new=farrealloc(q_old,n_byte);;  // изменение размера блока

#ifndef _GLogicProcessor_H_
#define _GLogicProcessor_H_

#include "config.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <algorithm>

#include "OCRTypes/OCRTypes.h"
#include "OCRTypes/glyphOCR.h"
#include "pugixml/pugixml.hpp"
#include "OCRString/php2stl.h"

//#include <boost/xpressive/xpressive.hpp>

using namespace std;
using namespace pugi;
//using namespace boost::xpressive;

namespace ocr{
///класс содержит данные по языковой модели,методы словарного и грамматического контроля
class  GLogicProcessor {
protected:
  GLogicProcessor(void);
 public:
  virtual ~GLogicProcessor();
  void destroy(void);
  void init();
protected:
public:
		glyphOCR *aliKali;    //
		vector<stringOCR>*strArray;
		///vector of Pali letters in codepage Pali from www.metter.lk <-> Uni
	           vector<uniRecord>mettaPali;
	           ///main map of dictionary records. 
	           map<string, OCRDictRecord>mainDict;
		int print;
		ofstream c_out;
	
	map<string,vector <int> >dictIndexTib; ///< index map for all tibetan dictionary
	map<string,vector <int> >dictIndexPali; ///< index map for all pali dictionary
	map<int, OCRDictRecord> dictRecord; ///< main map for all dictionary
	vector<OCRDictRecord> dictReport; ///< vector for translation output
	vector<vector<OCRDictRecord> >dictReportPage;  ///<vector for multi-line translation output
	vector<string>tibStr;
	vector<string>wylieStr;
	vector<string>wylieStrVect;
	vector<string>yagpoStrVect;
	vector<string>strVector; //<<source text vector
	vector<string>delimeterTib; //<vector for all tibetan punctuation marks
	vector<string>grammarTib; //<common tibetan words. It is not used in search
	vector<string>delimeterPali; //<vector for all tibetan punctuation marks
	vector<string>grammarPali; //<common tibetan words. It is not used in search
	vector<string>commentaryIndex; //<commentary index in text

	
	vector<string>inputVect;
	vector <string> stringItemVector;
		

	map<string,int>fontNameMap;  ///<map of tibetan font names 
	map<string, uniRecord>uniTibTable; ///<map of tibetan letters conversion in Unicode and UTF
	map<string, uniRecord>uniTibTableYagpo;  ///<main map of tibetan letters in codepage Uni<->Yagpo
	map<string,string>ASCIToUni;    ///<map of tibetan letters in Unicode and ASCI keyboard layout
	map<string, uniRecord>YagpoToWylieMap; ///<map of Yagpo UTF To Wylie conversion
	map<string, uniRecord>UniToWylieMap; ///<map of Uni To Wylie conversion
	map<string,string> SinhalaASCI;  //map for Sinhala font convertion function  
	vector<uniRecord>uniTibTable0F00;
	vector<string>TibetanAlphabet;
	map<string,map<string,uniRecord> >fontMap;
	
	map<string,map<string,string> > mainLetterTableUni; ///base letter table for all letter conversion function in Uni key
	map<string,map<string,string> > mainLetterTableYagpo; ///base letter table for all letter conversion function in Yagpo key
	map<string,map<string,string> > mainLetterTableKey; ///base letter table for all letter conversion function in typing key

	char *hashData;  ///hashed index for all words and phrases (about 600mb) this data it is all adress space of integer. Every integer it is uniq hash of string
	///integer it is index of one bit in hashData block of memory. Value of this bit it is exist this hash or not. 
    hashRecord *hashVector; ///second level hash index. Every adress in hashRecord it is offset in text buffer.
	unsigned long hashSize; //size of second level hash index. 
	vector<stringEntry> textKeyIndex; ///vector for all words and phrases key without grammar particals and words delimeters(about 600mb);
	
	
	char *textBuffer;
	FILE *hFile1,*hFile2,*hFile3,*hFile4;
	
	int maxUniRecord;  ///<max length of tibetan staÏck letter in Unicode codepage
	string report;  //string for conversion errors output;
	
/*	map<string,string>fontMapLoaded;
		map<string, string>::const_iterator fontIndex;
	map<wstring, wstring>::const_iterator ASCIIndex;
	map<string,map<wstring,uniRecord> >::const_iterator fontIndexInMap;
	map<wstring,uniRecord>::const_iterator letterIndexInMap;
*/	
	int dictionaryReady;  //flag of dictionary loading
	
	/// @name Initialisation
//@{
	static GLogicProcessor* create(void) {return new GLogicProcessor;}
//}
/// @name Language codepage conversion function
	
//@{
	/**  @brief load all conversion map from XML files
	 */
	void  LoadUniToTibetanMapUTF(commandData *inputData );
	/**  @brief load convrsion map for font from XML files
	 */
	void  LoadFontNameMap(commandData* inputData, map<string, string>&fontNameMap);
	/**  @brief main conversion function. all conversion parameter set in inputData structure 
	 */
	/** @brief load XML in to STL map	*/		
	void LoadMapXML(commandData *inputData);
	
	void loadTransliterationFile(const char *mapName);
	
 	string  startConvert(commandData *inputData); 
	/** @brief convert string from Wylie transliteration to Yagpo UTF		   
	 */	
	string WylieToYagpoConverter(string &inStr);
	/** @brief convert string from delimeted Wylie transliteration to Yagpo UTF  (english {Wylie} english) 		   
	*/	
	string dWylieToYagpoConverter(string &inStr);
	/** @brief convert string from tibetan Unicode in UTF to Wylie transliteration		   
	 */
	string UniToWylieConverter(string &inStr);
	/** @brief convert string from delimeted Singhala ASCI font (FMAbhaya etc.) transliteration to Sinhala UTF  (english {Singhala ASCI} english) 		   
	 */
	string dSinhalaASCIToYagpo(string &inStr);
	/** @brief convert string from Singhala ASCI font (FMAbhaya etc.) transliteration to Sinhala UTF  (english {Singhala ASCI} english) 		   
	 */
	string SinghalaASCIToYagpo(string &uniStack);
	/** @brief convert string from Singhala Unicode font to Sinhala Yagpo precomposed Unicode codepage UniToTibetanBig.xml 		   
	 */
     string SinhalaUniToYagpo(string &uniStack,int mode);
	/** @brief convert string from CXS Extended Sanskrit codepage in Uni UTF8 string
	 this is fast conversion without copy string		   
	 */	
	void convertCXS_to_UTF_nocopy(string &inStr);
	/** @brief convert string from CXS Extended Sanskrit codepage in Uni UTF8 string
	 this is save conversion with copy string		   
	 */	
	string convertCXS_to_UTF(string &inStr);
	/** @brief convert string to lower case from Uni UTF8  Extended Sanskrit string
	 this is no save conversion with original string		   
	 */	
	void lowerCase_nocopy(string &inStr);
	

	string TibUniToWylie(string &srcStr,int mode);
	
#ifdef MACOS
	void RTFtoYagpoConverter(commandData *inputData, string &mainString,string &path);
#endif	
	string UniToTibetan(string &uniStack, int YagpoWylieFontFlag);
	/** @brief convert mixed (Tibetan+other text)  string from Tibetan Unicode codepage in UTF code pages
	 in Yagpo precomposed Unicode	 */
	string UnicodeToYagpo(string &srcStr);
	/** @brief convert string 
	mode 1 - from Tibetan Unicode codepage in UTF code pages in Yagpo precomposed Unicode
	mode 2 - from Wylie keyboard typed key to  Yagpo precomposed Unicode */
	string tibetanUTFToYagpo(string &uniStack,int mode);
	string YagpoToUni(string &uniStack);
	string YagpoUniToTibetanBig(string &uniStack);
	void  LoadYagpoToWylieMap(commandData *inputData);

	
	//}	
/// @nameDictionary function
	//@{	
	/** @brief function for check spelling of tibetan text
	 */	
	string spellCheck(commandData *inputData, string &str_);
	/** @brief function check misspeled string by dictionary and return corrected string. 
	    as grammar criteria used length of regult correct string
	 */
	string remapString(string &str_);
	/** @brief function check two string returned from dictionary and return one answer string,
	 where it is start from one string and end from second;
	 */
	string remapTibString(string &input0, string &input1);

	
	/** @brief get match from hash index about query string
	 */
	int hashMatch(string &str);
    string findStringMatch(const char *strKey, int sL, int offset);
	void bestMatchString(vector<stringEntry>&matchArray,const char *strKey_,int sL, string &textString,  string &destStr);
	
	/** @brief Returns main string in HTML format as result of grammar correction by dictionary base */
	string grammarCorrector(commandData* inputData, vector<wordOCR> &pageText,vector<stringOCR> &correctionWordArray,int mode);

	/** @brief Returns check letter in correction Table and add it in correction Table if not found*/	
	void checkInCorrectionTable(vector<stringOCR> &correctionWordArray,stringOCR &testStr, string &srcStr);
	
	/** @brief function load dictionare data tree in memory and call all translation methods 	   
	 */
	string startDictionary(commandData *inputData);
	/** @brief function load dictionare data tree in memory from XML files	   
	 */
	void readDictionary(commandData *inputData);
	/** @brief function load dictionare data tree in memory from FileMaker XML files	   
	 */
	void readDictionaryFileMakerXML(string &fileName);
	/** @brief function reload dictionare data tree in memory from XML files	   
	 */
	void reloadDictionary(commandData *inputData);
	/** @brief function set new words in dictionary	   
	 */
	void writeInDictionary(commandData *inputData);
	/** @brief function is used for build dictionary hash index from texts set. Function can be used for biuls full-text search index.	   
	 */	
	void buildDictionaryHashIndex(commandData *inputData);
	void buildDictionaryHashIndexUni(commandData *inputData,vector<string>&strVector);
		
	/** @brief function read grammar particals and punctuation data from  XML file  
	 */
	void readGrammarDataXML(string &path);
	/** @brief function translate one string and add dictionary report in report vector	   
	 */
	void mainDictReport(commandData *inputData);	
	
	/** @brief function analise mainDict map and found match of all parts of every key in it.
	 this is used for build dictionary from texts set.
	 this is no save conversion with original mainDict map		   
	 */	
	void  buildDictionary(commandData *inputData, vector<string> &strVector);
	/** @brief function is used for build dictionary from texts set. Every uniq word set in maindictioary	   
	 */	
	void  buildWordDictionary(commandData *inputData,vector<string> &strVector );
	/** @brief function format dictionary report as HTML
	 */	
	string writeDictReport(commandData *inputData,string &srcStr, int reportLevel, int fullReport);
	void writeDictReportXML(vector <vector <OCRDictRecord> >&dictReportPage,string &binPath);
	/** @brief function sort dictionary report vector and put more important report in top
	 */
	string sortKey(vector<dictKey>&keyArray,string &srcKey,int fullReport);
	/** @brief save mainDict map in TXT file		   
	 */
	void writeDictionaryTXT(commandData *inputData,  map<string, OCRDictRecord>&mainDict);
	/** @brief save mainDict map in XML file		   
	 */
	void writeDictionary(map<int, OCRDictRecord> &dictRecord, string &filePath);
	/** @brief load font map xml file from disk
	 */	   
	void loadMapFilePali(const char *mapName);
	void LoadFontNameMap(commandData* inputData); 
	void LoadFontMap(map<string,uniRecord>&fontMap,string &fileName);
	void loadDictLevelFile(commandData *inputData);
	
//}	

};
};
// ---------------- IMPLEMENTATION
# endif

