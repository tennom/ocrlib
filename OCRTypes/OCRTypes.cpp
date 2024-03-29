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

#ifndef OCRTYPES_H
#define OCRTYPES_H

#include "config.h"

#include "OCRTypes.h"
#include <string.h>
#include <fstream>
#include "OCRString/php2stl.h"


namespace ocr {

ostream&operator<<(ostream& s, GTextBufer z){
	return s<<z.size<<" "<<z.data;
}		
	
//________vectorOCR_________________
vectorOCR::~vectorOCR(){}

void vectorOCR::destroy(void){}

vectorOCR::vectorOCR(){
	selectFlag=0;
}

//________wordOCR_________________
	wordOCR::~wordOCR(){
	}

	void wordOCR::destroy(void){
		if(imgFlag){
			img->destroy();
			delete img;
		}

	}

	wordOCR::wordOCR(void){
		delimeter="";
		name="";
		newLine="";
		commentaryIndex="";
		imgFlag=0;
	}
	
	bool  wordOCR::operator==(vector<string> &ref){
		for(int a=0;a<ref.size();a++){
			if(ref[a]==name)return true;
		}
		return false;
	
	}
	bool wordOCR::testDelimeter(vector<string> &ref){
		for(int a=0;a<ref.size();a++){
			if(ref[a]==delimeter||ref[a]==name)return true;
		}
		return false;
	}
	
	
//________blockOCR_______________
blockOCR::~blockOCR(){}

void blockOCR::destroy(void){}

blockOCR::blockOCR(void){}
/**/
//________lineOCR_______________
lineOCR::~lineOCR(){}

void lineOCR::destroy(void){}

lineOCR::lineOCR(void){}
/**/
	

	
	
	
//________stringOCR_______________
	stringOCR::~stringOCR(void){
	    //destroy();
	}

	void stringOCR::destroy(void){
		if(imgFlag){
			img->destroy();
			delete img;
		}
		wordArray.resize(0);	
		
	}

	stringOCR::stringOCR(){
		x0=0;x1=0;y0=0;y1=0;
		count=0;
		imgFlag=0;
	}
		
	int stringOCR::length(){
		return count;	
	}
	int stringOCR::size(){
		return count;	
	}//_______________________________________________	
		
	void stringOCR::push_back(const wordOCR &word){
		string str_=str_replace("/", "", word.name.c_str());
		name+=str_+word.delimeter+word.commentaryIndex+word.newLine; //cout<<str_;
		wordArray.push_back(word);
		if(str_!=word.name){wordArray[count].fontSize=6;}else{wordArray[count].fontSize=14;}
		wordArray[count].name=str_;
		
		str+=str_;
		strHTML+="<c id=\"";
		char d[10];
		memset(d,0,10);
		sprintf(d, "%d",word.id);
		strHTML+=d; strHTML+="\">"+str_+"</c>";
		
		if(word.newLine!=""){x0=10000;y0=10000;x1=0;y1=0;}
		
		if(wordArray[count].x0>0&&wordArray[count].x0<x0)x0=wordArray[count].x0;
		if(wordArray[count].y0>0&&wordArray[count].y0<y0)y0=wordArray[count].y0;
		if(wordArray[count].x1>0&&wordArray[count].x1>x1)x1=wordArray[count].x1;
		if(wordArray[count].y1>0&&wordArray[count].y1>y1)y1=wordArray[count].y1;
		
		count++;
	}//_______________________________________________	
	
	wordOCR*  stringOCR::operator[](int index){
		if (index<0 || index>=count) {
			return &wordArray[0];
		}
		return &wordArray[index];
	}//_______________________________________________	
	

	void  stringOCR::operator+=(stringOCR& ref){
	    for(int a=0;a<ref.size();a++){
			string str_=str_replace("/", "", ref[a]->name.c_str());
			name+=str_;
			wordArray.push_back(*ref[a]);
			if(str_!=ref[a]->name){wordArray[count].fontSize=6;}else{wordArray[count].fontSize=14;}
			wordArray[count].name=str_;
			
			str+=str_;
			strHTML+="<c id=\"";
			char d[10];
			memset(d,0,10);
			sprintf(d, "%d",ref[a]->id);
			strHTML+=d; strHTML+="\">"+str_+"</c>";
			
			if(wordArray[count].x0>0&&wordArray[count].x0<x0)x0=wordArray[count].x0;
			if(wordArray[count].y0>0&&wordArray[count].y0<y0)y0=wordArray[count].y0;
			if(wordArray[count].x1>0&&wordArray[count].x1>x1)x1=wordArray[count].x1;
			if(wordArray[count].y1>0&&wordArray[count].y1>y1)y1=wordArray[count].y1;
			
			count++;
			delimeter=ref.delimeter;
		
		}
	
	}//_______________________________________________
	
	void  stringOCR::operator+=(wordOCR ref){
	    wordArray.push_back(ref);
	}

	int stringOCR::find(const string& match,int position){
		string str_;
		string matchStr=match;
		
		//cout<<"match="<<match<<" position="<<position<<" count="<<count<<endl;
		
		for(int a=position;a<count;a++){
			str_=wordArray[a].name; //cout<<"str_="<<str_<<" a="<<a<<endl;
			if(match.find(str_,0)!=0){
				//cout<<"(-)";
			}else{
				//cout<<"(+)";
				matchStr=match.substr(str_.length(),match.length());
				//cout<<" matchStr="<<matchStr<<endl;
				if(matchStr.length()==0)return a;
			}	
		}	
		return -1;
	}//_______________________________________________
	
	stringOCR stringOCR::substr(int position,int length){
		stringOCR str_;
	    for(int a=position;a<position+length&&a<count;a++){
			str_.push_back(wordArray[a]);
		}
		//cout<<" str_="<<str_.str<<" position="<<position<<" length="<<length<<" count="<<count<<endl;
		return str_;
	
	}//_______________________________________________
	
	void stringOCR::resize(int length){
	    wordArray.resize(length);
		count=length;
		if(length==0){
			str="";
			name="";
			strHTML="";
			x0=100000;y0=100000;x1=0;y1=0;
		
		}
	}//_______________________________________________
		
	
	string stringOCR::set_id(string &strReport_){
//на вход функции приходит строка ответа базы данных с расставленными слогами.
//как выход функции мы получаем строку в которой сохранена пунктуация исходной строки с добавлением пунктуации словаря		
		
	    string destStr;
		string strReport=strReport_,st;
		int startIndex=0,indexSrc;
		char d[10];
	    int print=0;
		DT("///_________set id strReport_="<<strReport_<<" str=/"<<str<<"/"<<END);
		while(startIndex<count){ 
			DT("wordArray["<<startIndex<<"].delimeter="<<wordArray[startIndex].delimeter<<endl);
		    if(wordArray[startIndex].delimeter==""){ DT("@/l/");
				indexSrc=strReport.find(wordArray[startIndex].name,0);
				if(indexSrc!=string::npos){
					//if(indexSrc!=0){
					//	st=srcStr.substr(0,indexSrc); 
					//	destStr+="<c id=\"-1\">"+st+"</c>";
					//}	
					destStr+="<c onClick=\"a(";
					memset(d, 0, 10);
					sprintf(d,"%d",wordArray[startIndex].id);
					destStr+=d; destStr+=")\">";
					if(indexSrc!=0)destStr+=strReport.substr(0,indexSrc);
					destStr+=wordArray[startIndex].name+wordArray[startIndex].commentaryIndex+wordArray[startIndex].newLine+"</c>";
					strReport=strReport.substr(indexSrc+wordArray[startIndex].name.size(),strReport.length()); 
					if(strReport.find(wordArray[startIndex].delimeter,0)==0)strReport=strReport.substr(wordArray[startIndex].delimeter.size(),strReport.size()-wordArray[startIndex].delimeter.size());
					DT("wordArray["<<startIndex<<"].commentaryIndex="<<wordArray[startIndex].commentaryIndex<<endl);
					if(wordArray[startIndex].commentaryIndex!="")if(strReport.find(wordArray[startIndex].commentaryIndex,0)==0){
						DT("find commentary strReport1="<<strReport<<endl);
						strReport=strReport.substr(wordArray[startIndex].commentaryIndex.size(),strReport.size()-wordArray[startIndex].commentaryIndex.size());
						DT("find commentary strReport2="<<strReport<<endl);
					}
					if(wordArray[startIndex].newLine!="")if(strReport.find(wordArray[startIndex].newLine,0)==0){
						DT("find commentary strReport1="<<strReport<<endl);
						strReport=strReport.substr(wordArray[startIndex].newLine.size(),strReport.size()-wordArray[startIndex].newLine.size());
						DT("find commentary strReport2="<<strReport<<endl);
					}
				}//else{destStr+="<b>ALERT</b>";}
			}else{ DT("@/cd/");
			   destStr+="<c onClick=\"a(";
			   memset(d, 0, 10);
			   sprintf(d,"%d",wordArray[startIndex].id);
 			   destStr+=d; destStr+="\")>";
			   destStr+=wordArray[startIndex].delimeter+wordArray[startIndex].commentaryIndex+wordArray[startIndex].newLine+"</c>";
			    if(wordArray[startIndex].delimeter!="")if(strReport.find("་",0)==0)strReport=strReport.substr(3,strReport.size()-3);
				DT("wordArray["<<startIndex<<"].commentaryIndex="<<wordArray[startIndex].commentaryIndex<<endl);
				if(wordArray[startIndex].commentaryIndex!="")if(strReport.find(wordArray[startIndex].commentaryIndex,0)==0){
					DT("find commentary strReport1="<<strReport<<endl);
					strReport=strReport.substr(wordArray[startIndex].commentaryIndex.size(),strReport.size()-wordArray[startIndex].commentaryIndex.size());
					DT("find commentary strReport2="<<strReport<<endl);
				}	
				if(wordArray[startIndex].newLine!="")if(strReport.find(wordArray[startIndex].newLine,0)==0){
					DT("find commentary strReport1="<<strReport<<endl);
					strReport=strReport.substr(wordArray[startIndex].newLine.size(),strReport.size()-wordArray[startIndex].newLine.size());
					DT("find commentary strReport2="<<strReport<<endl);
				}
				
			}
			//destStr+=wordArray[startIndex].newLine;
			DT("wordArray["<<startIndex<<"].name="<<wordArray[startIndex].name<<
			   "wordArray["<<startIndex<<"].delimeter="<<wordArray[startIndex].delimeter<<
			   "wordArray["<<startIndex<<"].newLine="<<wordArray[startIndex].newLine<<
   			   "wordArray["<<startIndex<<"].commentaryIndex="<<wordArray[startIndex].commentaryIndex<<endl<<
			   " indexSrc="<<indexSrc<<"strReport="<<strReport<<" destStr="<<destStr<<endl;)
			startIndex++;
				
		}
		//destStr+=strReport; //rest of string can has newLine
		return destStr;				
	}//_______________________________________________
	
	
	
//________columnOCR_______________
columnOCR::~columnOCR(){}

void columnOCR::destroy(void){}

columnOCR::columnOCR(void){}
//________recordOCR_______________

recordOCR::~recordOCR(){}

void recordOCR::destroy(void){}

recordOCR::recordOCR(void){}
/**/
//________frameOCR_______________
frameOCR::~frameOCR(void){}
void frameOCR::destroy(void){}

frameOCR::frameOCR(){}
	
//_______ drawDataRecord__________
//drawDataRecord::~drawDataRecord(void){}

//void drawDataRecord::destroy(void){}

drawDataRecord::drawDataRecord(){}

//________OCRPoint_________________
OCRPoint::OCRPoint(){}


OCRMatch::OCRMatch(){
		matchCount=0; //count for mutch points in structure
		centerDist=0;  //distance between centers of match vector
		vectorIndexModel=0; //index of match vector in base
		vectorIndexTest=0; //index of match vector in base
		allMatchCount=0;  //in [0] element we store count for all array of mutch
		matchSumTest=0; //calculated match
		status=0;
		letterIndex=0;
		correlation=0;
		Character=0;
		maxY=0;
};


int operator==(const OCRMatch &left, const OCRMatch &right){
	return  left.correlation==right.correlation;
}

int operator<(const OCRMatch &left, const OCRMatch &right){
	return  left.correlation>right.correlation;
}

//________TsertoOCR_________________
TsertoOCR::TsertoOCR(){};

//_______ OCRDictRecord
//OCRDictRecord::~OCRDictRecord(void){}

//void OCRDictRecord::destroy(void){}

OCRDictRecord::OCRDictRecord(){
	wordCount=0;
}





}

#endif



