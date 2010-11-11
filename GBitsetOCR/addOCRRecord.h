-(void)addOCRRecord:(glyphOCR)letterOCRSet_ :(NSString *)str_{
/*		const char *nameRecord;
		nameRecord=[str cStringUsingEncoding:1];

short currentRecord_, indexMain, index;
//first we set root record-longest outer contour 
short maxLength=0; short maxRecord=0;
for(indexMain=0;indexMain<letterOCRSet_.count; indexMain++){ ////check the bigest outer contour in letterSet
	if(vectorBase[letterOCRSet_.letter[indexMain]].angLength>maxLength&&
	vectorBase[letterOCRSet_.letter[indexMain]].contour==1){
	maxLength=vectorBase[letterOCRSet_.letter[indexMain]].angLength;maxRecord=letterOCRSet_.letter[indexMain];
	}
} 
vectorBase[maxRecord].contour=3; //set the bigest outer contour in letterSet  
cout<<"maxRecord="<<maxRecord<<" vectorBase[maxRecord].contour="<<(short)vectorBase[maxRecord].contour<<endl;
for (i=0;i<[str_ length]+1;i++){vectorBase[maxRecord].name[i]=nameRecord[i];}
vectorBase[maxRecord].OCRStatus=[self setOCRStatus:vectorBase[maxRecord].name];
//cout<<"vectorBase[maxRecord].OCRStatus="<<(short)vectorBase[maxRecord].OCRStatus<<endl;

//next we set record in OCR Base|////////////////////////////////////////////////////////////////////////////////////
		short startIndex;
		startIndex=letterBase[0].allContourCount;
for(indexMain=0;indexMain<letterOCRSet_.count; indexMain++){   //for every elment of letterOCRSet 
currentRecord_=letterOCRSet_.letter[indexMain];
//cout<<"vectorBase["<<currentRecord_<<"].contour"<<(short)vectorBase[currentRecord_].contour<<endl;
index=letterBase[0].allContourCount;

for (i=0;i<[str_ length]+1;i++){vectorBase[currentRecord_].name[i]=nameRecord[i];letterBase[index].name[i]=nameRecord[i];}

                letterBase[index].contourIndex=index;  //index of this contour in base
	        letterBase[index].angLength=vectorBase[currentRecord_].angLength;
	        letterBase[index].vectorCount=vectorBase[currentRecord_].vectorCount; //cout<<"vectorBase["<<currentRecord_<<"].vectorCount"<<vectorBase[currentRecord_].vectorCount<<endl;
	        letterBase[index].letterCenter.x=vectorBase[currentRecord_].letterCenter.x;
		letterBase[index].letterCenter.y=vectorBase[currentRecord_].letterCenter.y;
		//letterBase[index].vLetterCenter.x=vectorBase[currentRecord_].vLetterCenter.x;
		//letterBase[index].vLetterCenter.y=vectorBase[currentRecord_].vLetterCenter.y;
		letterBase[index].xMin=vectorBase[currentRecord_].xMin;
	        letterBase[index].xMax=vectorBase[currentRecord_].xMax;
	        letterBase[index].yMax=vectorBase[currentRecord_].yMax;	
	        letterBase[index].yMin=vectorBase[currentRecord_].yMin;
		letterBase[index].letterW=vectorBase[currentRecord_].xMax-vectorBase[currentRecord_].xMin;
		letterBase[index].letterH=vectorBase[currentRecord_].yMax-vectorBase[currentRecord_].yMin;
		letterBase[index].contour=vectorBase[currentRecord_].contour; 
		letterBase[index].correlation=0;
		letterBase[index].vectorLimit=(letterBase[index].letterW+letterBase[index].letterW+letterBase[index].letterH)/10;
		letterBase[index].OCRStatus=vectorBase[maxRecord].OCRStatus;	
		letterBase[index].correlationMethod=100;
		letterBase[index].recordStatus=1; //Flag for record validation
		letterBase[index].recordFlag=0; //Flag for grammar recognition
		letterBase[index].letterIndex=letterBasebase.size();
		letterBase[index].letterSetCount=letterOCRSet_.count; 

		/////IMPORTANT///set cross reference for letterSet
                for(i=0;i<letterOCRSet_.count;i++){ 
	        letterBase[startIndex+i].letterSet[indexMain]=letterBase[0].allContourCount;
		}
                letterBase[0].allContourCount++;
			
//for (i=0;i<vectorBase[currentRecord_].angLength;i++){
//letterBase[index].angDiff[i]=vectorBase[currentRecord_].angDiff[i];
//letterBase[index].letterX[i]=vectorBase[currentRecord_].letterX[i];
//letterBase[index].letterY[i]=vectorBase[currentRecord_].letterY[i];
//letterBase[index].status[i]=vectorBase[currentRecord_].status[i];
//letterBase[index].OCRZone[i]=vectorBase[currentRecord_].OCRZone[i];
//}//end for

////////////////////////add vector records in vector records Base

for (i=0;i<vectorBase[currentRecord_].vectorCount;i++){
		letterBase[index].v[i].vStart.x=vectorBase[currentRecord_].v[i].vStart.x; //cout<<" baseX "<<letterBase[index].v[i].vStart.x;
		letterBase[index].v[i].vStart.y=vectorBase[currentRecord_].v[i].vStart.y; //cout<<" baseY "<<letterBase[index].v[i].vStart.y;
		letterBase[index].v[i].vEnd.x=vectorBase[currentRecord_].v[i].vEnd.x;
		letterBase[index].v[i].vEnd.y=vectorBase[currentRecord_].v[i].vEnd.y;
		letterBase[index].v[i].vStartIndex=vectorBase[currentRecord_].v[i].vStartIndex; 
		letterBase[index].v[i].vEndIndex=vectorBase[currentRecord_].v[i].vEndIndex; 
		letterBase[index].v[i].length=vectorBase[currentRecord_].v[i].length; 
		letterBase[index].v[i].vCenter.x=vectorBase[currentRecord_].v[i].vCenter.x;
		letterBase[index].v[i].vCenter.y=vectorBase[currentRecord_].v[i].vCenter.y;
		letterBase[index].v[i].matchSum=0; 
		letterBase[index].v[i].vectorFlag=0;
		letterBase[index].v[i].contourFlag=0;
		letterBase[index].v[i].vectorPointCount=vectorBase[currentRecord_].v[i].vectorPointCount; 
		letterBase[index].v[i].vectorAngle=vectorBase[currentRecord_].v[i].vectorAngle; 
		     	   

}//end for
}//end for(indexMain=0;indexMain<letterOCRSet_.count;

letterBasebase.size()++;
//cout<<"letterBasebase.size()="<<letterBasebase.size()<<endl;
//cout<<"letterBase[0].allContourCount="<<letterBase[0].allContourCount<<endl;

				[letterStructure setData:letterBase :vectorBase :letterModelScale :srcData :&textOCRData];
				[self reloadTextOCR:letterOCRSet_.count];
				[letterOCRView setData:vectorBase :letterBase :letterModelScale :&textOCRData :mainGrammarBase]; //we send OCR Base to letterOCRView.  In letterOCRView we can use mouse event.	
				[letterOCRView setAllVectorLetter:[newGlyphOCR drawAllOCRLetter]];

*/
}////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////build OCR record from OCR Table letter pict///////////////////////////////////////////////////////////////////////
-(void)setFontOCRRecord:(GP<GBitmap>&) lineData_ :(NSString *)recordName :(short) wScale {
//[newGlyphOCR release];
	/*
//cout<<"letterBase[0].allContourCount="<<letterBase[0].allContourCount<<" letterIndex="<<letterIndex<<endl;
letterBase[letterIndex].letterSetCount=letterBase[0].allContourCount-letterIndex; //set contours count in letter
short indexMain;
//////////////////////IMPORTANT///set cross reference for letterSet
                //cout<<"letterBase["<<letterIndex<<"].letterSetCount="<<(short)letterBase[letterIndex].letterSetCount<<endl;
                for(indexMain=0;indexMain<letterBase[letterIndex].letterSetCount;indexMain++){
		for(i=0;i<letterBase[letterIndex].letterSetCount;i++){ 
		letterBase[letterIndex+i].letterSet[indexMain]=letterIndex+indexMain;
		letterBase[letterIndex+i].letterSetCount=letterBase[letterIndex].letterSetCount; //set contours count in letter
		}}

//set root record-longest outer contour 
short maxLength=0; short maxRecord=0;
for(indexMain=0;indexMain<letterBase[letterIndex].letterSetCount; indexMain++){ ////check the bigest outer contour in letterSet
	if(letterBase[letterIndex+indexMain].angLength>maxLength&&
	letterBase[letterIndex+indexMain].contour==1){
	maxLength=letterBase[letterIndex+indexMain].angLength;maxRecord=letterIndex+indexMain;
	}
} 
 letterBase[maxRecord].contour=3; //cout<<" maxRecord="<<maxRecord<<endl; //set the bigest outer contour in letterSet  

for (i=0;i<[recordName length];i++){letterBase[maxRecord].name[i]=nameRecord[i];} //set name for bigest contour in letterSet
letterBase[maxRecord].name[[recordName length]]=0;
  letterBase[maxRecord].OCRStatus=[self setOCRStatus:letterBase[maxRecord].name];
 //cout<<"maxRecord="<<maxRecord<<" letterBase[maxRecord].contour="<<(short)letterBase[maxRecord].contour<<endl;
 //cout<<"name[0]="<< letterBase[maxRecord].name[0]<<endl;
*/
}//end method//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



















