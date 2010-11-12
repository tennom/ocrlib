void GImageEditor::setLetterFromStore(commandData *inputData, glyphOCR *letter,GBitmap* img128){
	
	int c1,c2,maxCorrelation=0, correlation;
	int print=1;
	int bestBaseIndex,bestLetterIndex,lineIndex;
	//GBitmap *testImg=GBitmap::create(img128, 0);
	int bestXMask,bestYMask;
	vector<glyphOCR>letterLine;
    float step,scale,mS;
	int index;

	//WriteImageData(img128,"/1.jpg",0);
    //	exit(0); 
	
	cout<<" w="<<img128->rows()<<endl;
	lineIndex=0;
	
	for(int baseIndex=0;baseIndex<aliKaliStore.size();baseIndex++){
		//cout<<"baseIndex="<<baseIndex<<END;
		for(int letterIndex=0;letterIndex<aliKaliStore[baseIndex].letterCount;letterIndex++){
			//cout<<aliKaliStore[baseIndex][letterIndex]->name<<endl;
			if(aliKaliStore[baseIndex][letterIndex]->name!=letter->name&&
			   aliKaliStore[baseIndex][letterIndex]->name!=letter->name+"/"&&
			   aliKaliStore[baseIndex][letterIndex]->name!=letter->name+"/1"&&
			   aliKaliStore[baseIndex][letterIndex]->name!=letter->name+"/2")continue;
			
			cout<<"//so we has two letters. One is from store and one is from text we need found the best correlation"<<endl;
		    correlation=setLetterScale(img128, aliKaliStore[baseIndex][letterIndex]);
			if(correlation>maxCorrelation){
				maxCorrelation=correlation;
				letterLine.push_back(*aliKaliStore[baseIndex][letterIndex]);
			}
			
		}	
	}
	
	if(maxCorrelation>80){
		cout<<"maxCorrelation="<<maxCorrelation<<" scale="<<letterLine[letterLine.size()-1].scale<<endl;
		float scale=letterLine[letterLine.size()-1].scale;
		letter=aliKali[aliKali.letterCount-1];
		letter->copy(&letterLine[letterLine.size()-1]);
		letter->mask128Count=0;
		letter->mask128[0].packBitMask128(img128);  //now mask size changed and divide on 32
		letter->mask128[0].xMask=-1*(letter->mask128[0].mW/2);
		letter->mask128[0].yMask=-1*(letter->mask128[0].mH/2);
        letter->letterH/=scale;
		letter->letterW/=scale;
		letter->y0/=scale;
		letter->y1/=scale;
		
		for(int a=0;a<letter[0].mask32Count;a++){
			
			if(scale!=1){
				//cout<<"mask32[m].xMask"<<mask32[m].xMask;
				letter[0].mask32[a].xMask/=scale;  //cout<<"mask32[m].xMask1"<<mask32[m].xMask;
				letter[0].mask32[a].yMask/=scale;
				letter[0].mask32[a].imgW/=scale;
				letter[0].mask32[a].mH/=scale;
			}
			
			
			letter[0].mask32[a].xMask=-1*(letter->mask128[0].mW/2-letter[0].mask32[a].xMask); //coordinate from center of mask128
			letter[0].mask32[a].yMask=-1*(letter->mask128[0].mH/2-letter[0].mask32[a].yMask);
			cout<<"@mask m="<<a<<" xMask="<<letter[0].mask32[a].xMask<<" yMask="<<letter[0].mask32[a].yMask<<endl;
			
	    }
		
		letter->mask128Count++;
		letter->letterIndex=aliKali.letterCount-1;
		letter->reloadMask();
		cout<<"done reload scale="<<letter->scale<<endl;
	}else{
		letter=aliKali[aliKali.letterCount-1];
		letter->mask128Count=1;
		letter->mask128[0].packBitMask128(img128);  //now mask size changed and divide on 32
		letter->mask128[0].xMask=-1*(letter->mask128[0].mW/2);
		letter->mask128[0].yMask=-1*(letter->mask128[0].mH/2);
	}
	
	
}//////////////////////////////////////////////////////////////////////////////////////////////////

