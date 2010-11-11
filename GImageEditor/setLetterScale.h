int GImageEditor::setLetterScale(GBitmap *img128, glyphOCR *glyph_){
   
	int maxCorrelation=0;
	int c1, index, mC,mS,c2;
	float scale,step;
	
	cout<<"//so we has two letters. One is from base and one is from text we need found the best correlation"<<endl;
	glyphOCR glyph; glyph.copy(glyph_);
	
	c1=setCorrelation(img128,&glyph,1); 
	step=0.25; index=0; scale=1; mC=0;
	if(c1>0){  cout<<"two way search"<<endl;
		mC=c1; mS=1;
		while(index<4){	
			glyph.copy(glyph_);
			c2=setCorrelation(img128,&glyph,scale); //scale UP
			if (c2>mC){ mC=c2;mS=scale;}
			scale+=step; index++;
		}
		index=0; scale=1;
		while(index<3){	
			glyph.copy(glyph_);
			c2=setCorrelation(img128,&glyph,scale); //scale UP
			if (c2>mC){ mC=c2;mS=scale;}
			scale-=step; index++;
		}
		cout<<"second pass case1"<<endl;
		glyph.copy(glyph_);
		c2=setCorrelation(img128,&glyph,mS-0.1); //scale UP
		if (c2>mC){ mC=c2;mS=mS-0.1;}
		glyph.copy(glyph_);
		c2=setCorrelation(img128,&glyph,mS+0.2); //scale UP
		if (c2>mC){ mC=c2;mS=mS+0.2;}
		
		
	}else{
		cout<<"step by step search"<<endl;  scale=0.5;
		while(index<9){	
			glyph.copy(glyph_);
			c2=setCorrelation(img128,&glyph,scale); //scale UP
			if (c2>mC){ mC=c2;mS=scale;}
			scale+=step; index++;
			cout<<"c2="<<c2<<"scale="<<scale<<endl;
		}
		if(mC>0){ cout<<"second pass case2 mS="<<mS<<" mC="<<mC<<endl;
			glyph.copy(glyph_);
			c2=setCorrelation(img128,&glyph,mS-0.1); //scale UP
			if (c2>mC){ mC=c2;mS=mS-0.1;}
			glyph.copy(glyph_);
			c2=setCorrelation(img128,&glyph,mS+0.2); //scale UP
			if (c2>mC){ mC=c2;mS=mS+0.2;}
			cout<<" done"<<endl;
		}
	}
	if(mC>0){
		cout<<" result mS="<<mS<<" mC="<<mC<<endl;	
		//glyph.copy(glyph_);
		mC=setCorrelation(img128,glyph_,mS);  //setCorrelation store actual information in glyph_
		glyph_->scale=mS;
		return mC;
	} 
	return 0;


	
}//_____________________________________________________________________________


int GImageEditor::setCorrelation(GBitmap *img128, glyphOCR *glyph,float scale){  //function need copy of actual letter. It store OCR information 
	int correlation;
	GBitsetMatrix *setMatrix;
	GBitmap *img,*img_;
	
	if(scale<0.1||scale>10)return 0;
    
	if(scale!=1){
		img=GBitmap::createScale(img128, scale);
        //img->printToScreen(); exit(0);
		img_=GBitmap::create(img->columns()+60,img->rows()+60);
		img_->fill(255);
		img_->drawImg(img,30,30);
		img->destroy();
	}else{
	    img_=GBitmap::create(img128->columns()+60,img128->rows()+60);
		img_->fill(255);
		img_->drawImg(img128,30,30);
	}	
    //img_->printToScreen();
	//cout<<"c1";
	setMatrix=GBitsetMatrix::createRegion(img_,
										  0,
										  0,
										  img_->columns(),
										  img_->rows(),
										  1,1,
										  IMGNOFLIP);
	
	
	//cout<<"c2";
    correlation=setMatrix->letterToLetterCorrelation (
													  glyph,
													  0,
													  img_->rows(),
													  0);
	
	 setMatrix->destroy();
	 delete setMatrix;
	 img_->destroy();
	//cout<<"c3";
	return correlation;
}//____________________________________________________________________________
