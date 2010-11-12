/** This function check correlation of test letter with all letter database and return array of letters with close correlation
*/ 
string GImageEditor::testLetter(commandData *inputData, unsigned int idNumber){

	int c1;
	int print=1;
	vector<glyphOCR*>letterLine;
	int index=-1;
	index=aliKali.indexById(idNumber);
	if(index<0)return "";
	ostringstream out_;
	out_<<"<ocrData>setBase</ocrData><setBase>";

	//first we check letter base -> letter corelation
    for(int letterIndex=0;letterIndex<aliKali.letterCount;letterIndex++){
		GBitmap *img128=aliKali[letterIndex]->mask128[0].unPackMask();
		GBitmap *img128_=GBitmap::createScale(img128,0.33);
		img128->destroy();
		img128=GBitmap::createScale(img128_,3); //WriteImageData(img128, "/1jpg", 0);
		img128_->destroy();
		//if(letterIndex!=index)continue;
			cout<<"m1";
			glyphOCR glyph; glyph.copy(aliKali[index]);
			cout<<"m2";
			c1=setCorrelation(img128,&glyph,1); aliKali[letterIndex]->correlation=c1;
			cout<<"m3";
			if(letterIndex==index){
				aliKali[index]->selfCorrelation=c1;
				out_<<"{glyph id=\""<<idNumber<<"\" sC=\""<<c1<<"\"/}";
			}else{
			    if(c1>70){
					letterLine.push_back(aliKali[letterIndex]);
					if(c1>aliKali[index]->codeSpace)aliKali[index]->codeSpace=c1;
			    }
			}
			cout<<"m4";
			DT("name="<<aliKali[letterIndex]->name<<" correlation="<<c1<<" id="<<glyph.idNumber<<endl);
			img128->destroy();

	}
	for(int letterIndex=0;letterIndex<aliKali.letterCount;letterIndex++){
	    if(aliKali[letterIndex]->codeSpace)out_<<"{glyph id=\""<<idNumber<<"\" cS=\""<<aliKali[letterIndex]->codeSpace<<"\"/}";
	} 	
	out_<<"</setBase>";
	string str=out_.str();
	writeText(str,inputData->data["inputPath"]);
	
	if(letterLine.size()){
		///string str=drawEditLetter(inputData,letterLine[0].idNumber);
		
		ostringstream out;
		//out<<"<script language=\"javaScript\">";
		for(int i=0;i<letterLine.size()&i<10;i++){
			out<<"<a href=\"?m=edit&l="<<letterLine[i]->idNumber<<"\", target=\"_blank\">found letter name "<<letterLine[i]->name<<" correllation="<<letterLine[i]->correlation<<"</a><br>"<<endl;
			//out<<"window.open(\"?m=edit&l="<<letterLine[i].idNumber<<"\",  \"_blank\",\"width=600,height=480, menubar=no,location=no,resizable=yes,scrollbars=yes,status=no \");"<<endl;
		}
		//out<<"</script>";
		str=out.str();
		cout<<str;
		return str;
    }else{
	    str="no letters found";
		return str;

	}
	
}//__________________________________________________________________________


/** This function check correlation of every letter with all letter database
 */ 
void GImageEditor::testBase(commandData *inputData){
	
	int c1;
	glyphOCR glyph;
	int print=1;
for(int index=0;index<aliKali.letterCount;index++){
	aliKali[index]->selfCorrelation=0; aliKali[index]->codeSpace=0;
}	
	

for(int index=0;index<aliKali.letterCount;index++){
    for(int letterIndex=0;letterIndex<aliKali.letterCount;letterIndex++){
        glyph.copy(aliKali[index]);
		GBitmap *img128=aliKali[letterIndex]->mask128[0].unPackMask();
		GBitmap *img128_=GBitmap::createScale(img128,0.33);
		img128->destroy();
		img128=GBitmap::createScale(img128_,3); //WriteImageData(img128, "/1jpg", 0);
		img128_->destroy();
		c1=setCorrelation(img128,&glyph,1);
		if(letterIndex==index){
			aliKali[index]->selfCorrelation=c1;
		}else{
			if(c1>70){
				if(c1>aliKali[index]->codeSpace)aliKali[index]->codeSpace=c1;
			}
		}
		//DT("name="<<aliKali[letterIndex]->name<<" correlation="<<c1<<" id="<<glyph.idNumber<<endl);
		img128->destroy();
	}
	DT("name="<<aliKali[index]->name<<" selfCorrelation="<<aliKali[index]->selfCorrelation<<endl);
}	
	
}//__________________________________________________________________________








