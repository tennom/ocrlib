float GBitsetOCR::lineOCRScaleDetector(GBitmap *line,
									   vector<OCRMatch>&matchLine, 
									   int yLimit0, 
									   int yLimit1, 
									   float scale,
									   int index,
									   int *betterCorrelation,
									   int limit){

//line size detector first pass
float step=scale/5;
int correlation; int maxCorrelation=0; float scale_;
float maxScale=0;
for(int s=-3;s<7;s++){
	scale_=scale+step*s;
	matchLine.resize(inputBitmap->columns()*scale_+256);
	correlation=lineOCR(line,matchLine, yLimit0, yLimit1, scale_,index,limit);
	if(correlation>maxCorrelation){
		maxCorrelation=correlation;
		maxScale=scale_;
	}	   
	cout<<"c="<<correlation<<" m="<<maxCorrelation<<" ms="<<maxScale<<" s="<<scale_<<" st="<<step<<endl;
	}
	if(!maxScale){return 0;}
	//line size detector second pass
	cout<<"/2/______"<<endl;
	step=scale/10; float maxScale_=0;
	for(int s=0;s<2;s++){
		if(s==0)scale_=maxScale-step;
		if(s==1)scale_=maxScale+step;
		matchLine.resize(inputBitmap->columns()*scale_+256);
		correlation=lineOCR(line,matchLine, yLimit0, yLimit1, scale_,index,limit);
		if(correlation>maxCorrelation){
			maxCorrelation=correlation;
			maxScale_=scale_;
		}	
		cout<<"c="<<correlation<<" m="<<maxCorrelation<<" ms="<<maxScale_<<" s="<<scale_<<" st="<<step<<endl;
	}
	if(maxScale_>0){
		maxScale=maxScale_;
	}	
	//line size detector second pass
	cout<<"/3/______"<<endl;
	step=scale/20; maxScale_=0;
	for(int s=0;s<2;s++){
		if(s==0)scale_=maxScale-step;
		if(s==1)scale_=maxScale+step;
		matchLine.resize(inputBitmap->columns()*scale_+256);
		correlation=lineOCR(line,matchLine, yLimit0, yLimit1, scale_,index,limit);
		if(correlation>maxCorrelation){
			maxCorrelation=correlation;
			maxScale_=scale_;
		}	
		cout<<"c="<<correlation<<" m="<<maxCorrelation<<" ms="<<maxScale_<<" s="<<scale_<<" st="<<step<<endl;
	}
	if(maxScale_>0){
		maxScale=maxScale_;
	}
	scale=maxScale;
	*betterCorrelation=maxCorrelation;
	//
	cout<<"@@@ scale="<<scale<<endl;
	return scale;
	
};//___________________________________________________________________________________________	



int GBitsetOCR::lineOCR(GBitmap *line,vector<OCRMatch>&matchLine, int yLimit0, int yLimit1, float scale,int index,int scaleMode){

	int print=0;
	DT("m0_1");
	GBitmap *lineScale=GBitmap::createScale(line,scale);
	DT("m0_2");
	//GImageEditor *editor=GImageEditor::create();
	//editor->WriteImageData(lineScale,"/1.jpg",0);
	DT("m1");
	setMatrix=GBitsetMatrix::createRegion(lineScale,
										  0,
										  0,
										  lineScale->columns(),
										  lineScale->rows(),
										  1,1,
										  IMGNOFLIP
										  );
	DT("m2");
	lineScale->destroy();
	
	setMatrix->letterCorrelation(inputData,
								 matchLine,
								 aliKali,
								 yLimit0*scale, 
								 yLimit1*scale,
								 scaleMode,
								 0);
	DT("m3");
	setMatrix->destroy();
	delete setMatrix;

	//now we start check result of correlation and make decision about place of every letter

	int correlation=0; int count=0;
	for(int m=0;m<matchLine.size();m++){
		if(matchLine[m].correlation>80){
			correlation+=matchLine[m].correlation;
			count++;
		}
	}
	if(count&&correlation)correlation/=count;
    matchLine.resize(0);
	return correlation;

	
	return 0;
 
 }////////////////////////////////////////////////////////////////////////////////

