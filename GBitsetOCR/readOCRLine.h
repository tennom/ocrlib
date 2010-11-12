-(void)readOCRLine{    //sort OCR contour base by line 

//baseCount=vectorBase[0].allContourCount;
short stringArray[1024];
short stringXArray[1024];
//short stringArraySort[1024];
short stringIndex, stringCount, index;
	strOCR.count=0;

for(lineNum=0;lineNum<=lineCount;lineNum++){//for all strokes		
                        stringIndex=0; stringCount=0;
		        for(record=0;record<vectorBase[0].allContourCount;record++){ //read string contours in array
					if(vectorBase[record].stringNum==lineNum){
					stringArray[stringIndex]=record;
					stringXArray[stringIndex]=vectorBase[record].letterCenter.x;
					stringIndex++;}
			}//
			stringCount=stringIndex;
			//cout<<"lineNum="<<lineNum<<" stringCount="<<stringCount<<endl;
			if(stringCount>0){   //now we sort  stringArray by x
			
			quickSort(stringXArray, stringCount); 
			
			}//if(stringCount>0		
	for(stringIndex=0;stringIndex<stringCount;stringIndex++){
	for(index=0;index<stringCount;index++){
		if(vectorBase[stringArray[index]].letterCenter.x==stringXArray[stringIndex]&&vectorBase[stringArray[index]].recordFlag!=3){
		vectorBase[stringArray[index]].recordFlag=3;
		strOCR.letter[strOCR.count]=stringArray[index]; //write to strOCR this contour
		//cout<<"stringArray["<<index<<"]="<<stringArray[index]<<endl;
		strOCR.count++;
		stringXArray[stringIndex]=0; //mask this value
		//cout <<"vectorBase["<<stringArray[index]<<"].name="<<vectorBase[stringArray[index]].name<<" stringNum="<<vectorBase[stringArray[index]].stringNum<<endl; 
		}
	//cout <<stringXArray[stringIndex]<<" "; 
	}}
} //for(lineNum=0
//cout<<"vectorBase[0].allContourCount="<<vectorBase[0].allContourCount<<" OCRIndex="<<OCRIndex<<endl;


}////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
