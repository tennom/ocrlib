float GBitsetOCR::lineOCRScaleDetector(GBitmap *line, int yLimit0, int yLimit1, float scale_){

	int print=1;
	float step=scale_/10; DT("step="<<step<<"scale_="<<scale_<<endl);
	float scale;
	int maxCorrelation=0;
	float maxScale;
	
	//first line scale detector run 
	for(int index=-7;index<10;index++){
		
		    scale=scale_+(float)step*index;	 //DT("scale="<<scale<<" s="<<(float)step*index<<endl);
			vector<OCRMatch>matchLine;
			matchLine.resize(inputBitmap->columns()*scale+256);
			
			DT("s0_1");
			GBitmap *lineScale=GBitmap::createScale(line,scale);
			DT("s0_2");
			//GImageEditor *editor=GImageEditor::create();
			//editor->WriteImageData(lineScale,"/1.jpg",0);
			DT("s1");
			setMatrix=GBitsetMatrix::createRegion(lineScale,
												  0,
												  0,
												  lineScale->columns(),
												  lineScale->rows(),
												  1,1,
												  IMGNOFLIP
												  );
			DT("s2");       	
			lineScale->destroy();
			setMatrix->letterCorrelation(inputData,
										 matchLine,
										 aliKali,
										 (yLimit0-(strArray[0][index].y1-strArray[0][index].y0)/2)*scale, ///?
										 (strArray[0][index].y1-strArray[0][index].y0+yLimit0+yLimit1+(strArray[0][index].y1-strArray[0][index].y0)/4)*scale,
										 0);

			DT("s3");
		int correlation=0; int count=0;
		for(int i=0;i<matchLine.size()-256;i++){
		    if(matchLine[i].correlation){
			if(matchLine[i].name=="་")continue;	
			  correlation+=matchLine[i].correlation;
			  count++;
			}
		}
        if(count&&correlation) correlation/=count;
		if(correlation>maxCorrelation){
			maxCorrelation=correlation;
		    maxScale=scale;
		}
		cout<<" correlation="<<correlation<<" maxCorrelation="<<maxCorrelation<<" maxScale="<<maxScale<<" scale="<<scale<<endl;
			setMatrix->destroy();
			delete setMatrix;
    }

		//second line scale detector run 
	step=scale_/20;
	float maxScale_=0;
	for(int index=0;index<2;index++){
		if(index==0)scale=maxScale+step;  
		if(index==1)scale=maxScale-step;    		
		vector<OCRMatch>matchLine;
		matchLine.resize(inputBitmap->columns()*scale+256);
		
		DT("t0_1");
		GBitmap *lineScale=GBitmap::createScale(line,scale);
		DT("t0_2");
		//GImageEditor *editor=GImageEditor::create();
		//editor->WriteImageData(lineScale,"/1.jpg",0);
		DT("t1");
		setMatrix=GBitsetMatrix::createRegion(lineScale,
											  0,
											  0,
											  lineScale->columns(),
											  lineScale->rows(),
											  1,1,
											  IMGNOFLIP
											  );
		DT("t2");       	
		lineScale->destroy();
		setMatrix->letterCorrelation(inputData,
									 matchLine,
									 aliKali,
									 (yLimit0-(strArray[0][index].y1-strArray[0][index].y0)/2)*scale, ///?
									 (strArray[0][index].y1-strArray[0][index].y0+yLimit0+yLimit1+(strArray[0][index].y1-strArray[0][index].y0)/4)*scale,
									 0);
		
		DT("t3");
		int correlation=0; int count=0;
		for(int i=0;i<matchLine.size()-256;i++){
			if(matchLine[i].name=="་")continue;
		    if(matchLine[i].correlation){
				correlation+=matchLine[i].correlation;
				count++;
			}
		}
		if(count&&correlation) correlation/=count;
		if(correlation>maxCorrelation){
			maxCorrelation=correlation;
		    maxScale_=scale;
		}
		cout<<" correlation="<<correlation<<" maxCorrelation="<<maxCorrelation<<" maxScale="<<maxScale_<<" scale="<<scale<<endl;
		setMatrix->destroy();
		delete setMatrix;
    }
	
	if(maxScale_)return maxScale_;
	
	return maxScale;
	
 }////////////////////////////////////////////////////////////////////////////////

