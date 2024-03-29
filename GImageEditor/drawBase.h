﻿string GImageEditor::drawBase(commandData *inputData,string data){
ostringstream out;

	string fontName=aliKali.fontName;
	if(fontName=="")fontName="Kailasa";

	string path=inputData->data["root"]+"edit/headerTable.xml";
    out<<readText(path);

	out<<".b  {background-color:#ccccff;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b0 {background-color:#cc0033;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b30{background-color:#ff6600;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b40{background-color:#ff9900;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b50{background-color:#ffff66;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b70{background-color:#66ff66;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b80{background-color:#33ff99;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b90{background-color:#00cc66;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b95{background-color:#009966;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	
	out<<".c{background-color:#ffcc99;position:absoute; text-align:center; font-family:"<<fontName<<"}</style>\n";
	//out+="data=";་out+=data;
	out<<"<table><tr>";
	int step=1;

	//cout<<"aliKali.base.size()="<<aliKali.base.size()<<" data="<<data<<"|"<<endl;
	
	for(int i=0;i<aliKali.letterCount;i++){

		if(data!=""){
			if(aliKali[i]->name.find(data)==-1)continue;
		}
		if(aliKali[i]->name=="")continue;
		out<<"<td><div class=\"gL\" id=\""<<aliKali[i]->idNumber<<"\" onClick=\"edit(";
		out<<aliKali[i]->idNumber<<")\">";
		out<<"<img id=\"g"<<aliKali[i]->idNumber<<"\" class=\"i\" src=\"?m=pict&l="<<aliKali[i]->idNumber;
		out<<"\" width=\"70\"></div>";
		out<<"<div class=\"";
		if(aliKali[i]->selfCorrelation<97){
			if(aliKali[i]->selfCorrelation<50){
			   out<<"b95";
			}else{
			   out<<"b";
			}	
		
		}else{out<<"c";}
		
		//if(aliKali[i]->crRes>95&&aliKali[i]->crRes<101){out<<"b95";}
		//if(aliKali[i]->crRes>90&&aliKali[i]->crRes<96){out<<"b90";}
		//if(aliKali[i]->crRes>80&&aliKali[i]->crRes<91){out<<"b80";}
		//if(aliKali[i]->crRes>70&&aliKali[i]->crRes<81){out<<"b70";}		
		//if(aliKali[i]->crRes>50&&aliKali[i]->crRes<71){out<<"b50";}
		//if(aliKali[i]->crRes>40&&aliKali[i]->crRes<51){out<<"b40";}
		//if(aliKali[i]->crRes>30&&aliKali[i]->crRes<41){out<<"b30";}
		//if(aliKali[i]->crRes>0&&aliKali[i]->crRes<31){out<<"b0";}
		//if(aliKali[i]->crRes==0){out<<"c";}
		
		out<<"\" >"<<aliKali[i]->name;
		if(aliKali[i]->selfCorrelation<97||aliKali[i]->codeSpace>87){
			out<<"<font color=\"#0000FF\" face=\"Arial\" size=\"2\">"<<aliKali[i]->selfCorrelation<<"/"<<aliKali[i]->codeSpace<<"</font>";
		}
		
		out<<"</div></td>\n";
		if(step==20){
		   out<<"</tr><tr>\n";
			step=0;	
		}step++;
		
	}
	
	out<<"</tr></table>";
	out<<"<div id=\"selector\"></div>";

	
return out.str();	
}//_____________________________________________________________________________


string GImageEditor::drawCorrectionTable(commandData *inputData,string data){
	if(correctionTable.size()==0)readCorrectionTable(inputData);

	string fontName=aliKali.fontName;
	if(fontName=="")fontName="Kailasa";

	ostringstream out;
	int limit=atoi(data.c_str());
	cout<<"limit="<<limit<<" correctionTable.size()="<<correctionTable.size()<<endl;

	string path=inputData->data["root"]+"edit/headerCorrectionTable.xml";
    out<<readText(path);

	
	out<<".b  {background-color:#ccccff;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b0 {background-color:#cc0033;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b30{background-color:#ff6600;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b40{background-color:#ff9900;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b50{background-color:#ffff66;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b70{background-color:#66ff66;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b80{background-color:#33ff99;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b90{background-color:#00cc66;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	out<<".b95{background-color:#009966;position:absoute; text-align:center; font-family:"<<fontName<<"}\n";
	
	out<<".c{background-color:#ffcc99;position:absoute; text-align:center; font-family:"<<fontName<<"}</style>\n";
	//out+="data=";་out+=data;
	out<<"<table><tr>";
	int step=1;
	char buff[15];
	int w,h;
	int c;
	
    for(int i=limit;i<correctionTable.size()&&i<limit+500;i++){
		
		//if(data!=""){
		//	if(correctionTable[i].name.find(data)==-1)continue;
		//}
		if(!correctionTable[i].img)continue;
		w=correctionTable[i].img->w/3;
		h=correctionTable[i].img->h/3;
		
		//if(w>180){h=h*180/w;w=180;}
		//if(h>100){w=w*100/h;h=100;}
		out<<"<td><div class=\"gL\" id=\""<<correctionTable[i].idNumber<<"\" onClick=\"edit(";
		out<<correctionTable[i].idNumber<<")\"><div class=\"g\"><img id=\"g"<<correctionTable[i].idNumber<<"\" class=\"i\" src=\"?m=grab&l="<<correctionTable[i].idNumber;
		out<<"\" ";
		out<<"width=\""<<w<<"\" height=\""<<h<<"\"/></div>";
		out<<"</div><div class=\"";
		c=correctionTable[i].correlation;
		if(c>95&&c<101){out<<"b95";}
		if(c>90&&c<96){out<<"b90";}
		if(c>80&&c<91){out<<"b80";}
		if(c>70&&c<81){out<<"b70";}		
		if(c>50&&c<71){out<<"b50";}
		if(c>40&&c<51){out<<"b40";}
		if(c>30&&c<41){out<<"b30";}
		if(c>0&&c<31){out<<"b0";}
		if(c==0){out<<"c";}
		
		out<<"\" >"<<correctionTable[i].correlation<<"| "<<correctionTable[i].name<<"</div>";
		
		out<<"</td>\n";
		if(step==15){
			out<<"</tr><tr>\n";
			step=0;	
		}step++;
		
	}
	
	out<<"</tr></table>";
	out<<"<div id=\"selector\"></div>";
	
	
	return out.str();	
}//_____________________________________________________________________________


string GImageEditor::drawEditLetter(commandData *inputData,unsigned int idNumber){
	int indexMask, x0,y0,w,h;
	int in=-1;
	string fontName=aliKali.fontName;
	if(fontName=="")fontName="Kailasa";
	
	if(idNumber==0){
		in=aliKali.letterCount-1;
		idNumber=aliKali[in]->idNumber;
	}else{
		//находим нужную букву по idNumber
		for(int i=0;i<aliKali.letterCount;i++){
			if(aliKali[i]->idNumber==idNumber){
				in=i; break;
			}
		}
	}	
	if(in<0){cout<<" NO LETTER"; return "";}
	int zoom=3;
	int size=PICT_SIZE*zoom;
	//cout<<"drawEditLetter in="<<in<<endl;
	ostringstream out;

	string path=inputData->data["root"]+"edit/headerEdit.xml";
    out<<readText(path);

	out<<"var pictW="<<size<<";\n";
	out<<"var zoom="<<zoom<<";\n";
	out<<"</script>\n";
	out<<"</head><body topmargin=0; leftmargin=0;>\n";
	out<<"<style>.a{border:1px solid green; width:"<<size<<"px; height:"<<size<<"px}</style>";
	//out<<"<form enctype=\"application/x-www-form-urlencoded\" method=\"get\" action=\"javastcript:submit("<<idNumber<<")\" name=\"main\">\n";
	
	out<<"<table cellspacing=\"0\" cellpadding=\"0\" border=\"0\"><tr><td valign=\"top\">";	
		out<<"<div class=\"a\" id=\">"<<idNumber<<"\" )><img src=\"?m=pict&l="<<idNumber<<"\" width=\""<<size<<"\"></div>";
    	indexMask=0;
		string name=aliKali[in]->name;
		int count=0;
	out<<"</td><td valign=\"top\">";	
		out<<"<textarea class=\"nG\" style=\"font-family:"<<fontName<<"\" id=\""<<aliKali[in]->idNumber;
		out<<"\" onClick=\"edit("<<aliKali[in]->idNumber<<")\" onBlur=\"setText("<<aliKali[in]->idNumber;
		out<<")\">"<<aliKali[in]->name<<"</textarea><br>";
		out<<"<font size=5>"<<aliKali[in]->idNumber<<"|"<<aliKali[in]->mask32Count<<"</font><br>";
	    out<<"<font size=3>Correlation value "<<aliKali[in]->crRes<<"</font><br>";
	    out<<"<font size=3>Correlation count "<<aliKali[in]->cn+aliKali[in]->cnRes*1000<<"</font><br>";
	    out<<"<font size=3>Mask count "<<aliKali[in]->mask32Count<<"</font><br>";
	    out<<"<font size=3>Self correlation "<<aliKali[in]->selfCorrelation<<"</font><br>";
	    out<<"<font size=3>Code space "<<aliKali[in]->codeSpace<<"</font><br>";
	    out<<"<font size=3>OCRIndex "<<aliKali[in]->OCRIndex<<"</font><br>";
	    out<<"<button onClick=\"saveBase()\">Save base</button><br>\n";
	    out<<"<button onClick=\"testLetter("<<idNumber<<")\">Test this letter with base</button><br>\n";
    	out<<"<button onClick=\"submit("<<idNumber<<")\">Save letter</button><br>\n";


		
		out<<"<div class=\"dE dM\" id=\"s";
	    out<<aliKali[in]->idNumber<<"\" style=\"left:";
		out<<0<<"px; top:"<<size/2+aliKali[in]->y0*zoom<<"px; width:"<<size;
		out<<"px; height:"<<aliKali[in]->y1*zoom-aliKali[in]->y0*zoom<<"px; border: 1px solid grey;\" ></div>\n";
		
			//cout<<"draw "<<in<<END;
			x0=PICT_SIZE/2-aliKali[in]->letterW/2+aliKali[in]->dX;
			y0=PICT_SIZE/2-aliKali[in]->letterH/2+aliKali[in]->dY;
			w=aliKali[in]->letterW;
			h=aliKali[in]->letterH;
			out<<"<div class=\"dE dM\" id=\"g"<<aliKali[in]->idNumber<<"\" style=\"left:"<<x0*zoom<<"px; top:"<<y0*zoom;
			out<<"px; width:"<<w*zoom<<"px; height:"<<h*zoom<<"px; border: 2px solid blue;\">\n";
			out<<"</div>\n";

	    int color; srand(time(NULL));
	    for(int m=0; m<aliKali[in]->mask32Count;m++){
			x0=aliKali[in]->mask32[m].xMask+PICT_SIZE/2;
			y0=aliKali[in]->mask32[m].yMask+PICT_SIZE/2;
			w=aliKali[in]->mask32[m].imgW-2;     //компенсация неточности JavaScript
			h=aliKali[in]->mask32[m].mH;
			out<<"<div class=\"dE dM\" id=\"p";
			out<<aliKali[in]->idNumber<<"_"<<m<<"_"<<indexMask<<"\" style=\"left:";
			out<<x0*zoom<<"px; top:"<<y0*zoom<<"px; width:"<<w*zoom<<"px; height:";
			out<<h*zoom<<"px;";
				if(aliKali[in]->mask32[m].correlation>95){
					if(m==0){
						out<<" border: 3px solid red;\">";
					}else{	
					    out<<" border: 1px solid rgb(";
						color= rand() % 100 + 1;
						out<<color<<"%,";
						color= rand() % 100 + 1;
						out<<color<<"%,";
						color= rand() % 100 + 1;
						out<<color<<"%)\"/>"<<endl;
						
					}	
				}else{
					if(m==0){
						out<<" border: 3px dotted red;\">";
					}else{
						out<<" border: 2px dotted rgb(";
						color= rand() % 100 + 1;
						out<<color<<"%,";
						color= rand() % 100 + 1;
						out<<color<<"%,";
						color= rand() % 100 + 1;
						out<<color<<"%)\"/>"<<endl;
					}
				}	
			out<<"<div class=\"nP\" id=\"m"<<aliKali[in]->idNumber<<"_"<<m<<"_"<<indexMask<<"\" onClick=\"edit1(\'m";
			out<<aliKali[in]->idNumber<<"_"<<m<<"_"<<indexMask<<"\')\" onBlur=\"setText1(";
			out<<aliKali[in]->idNumber<<")\">"<<aliKali[in]->mask32[m].dlt0;//<<"/"<<(short)aliKali[in]->mask32[m].correlation;
			out<<"</div></div>\n";
			indexMask++;
			
			//if(aliKali[in]->mask32[m].status<1)continue;
	    } 

		for(int m=aliKali[in]->mask32Count; m<=11;m++){
			//SH(aliKali[in]->mask32[m].w*zoomImage);  SH(aliKali[in]->mask32[m].h*zoomImage);
			
			x0=0;
			y0=0;
			w=10;
			h=10;
			out<<"<div class=\"dE dM\" id=\"p"<<aliKali[in]->idNumber<<"_"<<m<<"_"<<indexMask;
			out<<"\" style=\"left:"<<x0*zoom<<"px; top:"<<y0*zoom<<"px; width:";
			out<<w*zoom<<"px; height:"<<h*zoom<<"px; border: 1px solid green;\">";
			out<<"<div class=\"nP\" id=\"m"<<aliKali[in]->idNumber<<"_"<<m<<"_"<<indexMask;
			out<<"\" onClick=\"edit1(\'m"<<aliKali[in]->idNumber<<"_"<<m<<"_"<<indexMask;
			out<<"\')\" onBlur=\"setText1("<<aliKali[in]->idNumber<<")\">8</div></div>\n";
			indexMask++;
		}
		for(int m=12; m<15;m++){	
			x0=10;
			y0=0;
			w=10;
			h=10;
			out<<"<div class=\"dE dM\" id=\"p"<<aliKali[in]->idNumber<<"_"<<m<<"_"<<indexMask;
			out<<"\" style=\"left:"<<x0*zoom<<"px; top:"<<y0*zoom<<"px; width:";
			out<<w*zoom<<"px; height:"<<h*zoom<<"px; border: 1px solid green;\">";
			out<<"<div class=\"nP\" id=\"m"<<aliKali[in]->idNumber<<"_"<<m<<"_"<<indexMask;
			out<<"\" onClick=\"edit1(\'m"<<aliKali[in]->idNumber<<"_"<<m<<"_"<<indexMask;
			out<<"\')\" onBlur=\"setText1("<<aliKali[in]->idNumber<<")\">28</div></div>\n";
			indexMask++;
		}
	
	out<<"</td></tr><tr><td>";
	out<<"<input  name=\"inputFile\" id=\"inputFile\" type=\"hidden\" value=\""; out<<inputData->data["inputFile"];out<<"\">\n";
	out<<"<input  name=\"ocrData\"  type=\"hidden\" value=\"setBase\">\n";
	out<<"<input  name=\"inputFolder\"  type=\"hidden\" value=\""; out<<inputData->data["inputFolder"];out<<"\">\n";
	out<<"<textarea id=\"outputStr\" name=\"setBase\" rows=\"3\" style=\"width:"<<size<<"px\"></textarea>\n";
	out<<"</td></tr><table>";
	//out<<"</form>";	
	return out.str();	
}//_____________________________________________________________________________


string GImageEditor::drawEditLetterBlock(commandData *inputData,string &resultOCR,unsigned int idNumber){
	char buff[15];
	int in,indexMask, x0,y0,w,h;
	
	//находим нужную букву по idNumber
	for(int i=0;i<correctionTable.size();i++){
		if(correctionTable[i].idNumber==idNumber){
			in=i; break;
		}
	}
	//int zoom=3;
	//int size=PICT_SIZE*zoom;
	//cout<<"drawEditLetter"<<endl;
	ostringstream out;

	string path=inputData->data["root"]+"edit/headerEditLetterBlock.xml";
    out<<readText(path);
	
	out<<"var idNumber="<<idNumber<<";";
	
	//out<<"var pictW="<<size<<";";
	//out<<"var zoom="<<zoom<<";";
	out<<"</script>\n";
	out<<"</head><body topmargin=0; leftmargin=0;>\n";
	//out<<"<style>.a{border:1px solid green; width:"<<size<<"px; height:"<<size<<"px}</style>";
	//out<<"<form enctype=\"application/x-www-form-urlencoded\" method=\"get\" action=\"javastcript:submit("<<idNumber<<")\" name=\"main\">\n";
	
	out<<"<table cellspacing=\"0\" cellpadding=\"0\" border=\"0\"><tr><td valign=\"top\">";	
	out<<"<div class=\"a\" id=\">"<<idNumber<<"\" )><img src=\"?m=grab&l="<<idNumber<<"\" ></div>";
	out<<resultOCR;

	//out<<"</td><td valign=\"top\">";	
	//out<<"<br><textarea class=\"nG\" id=\""<<aliKali[in]->idNumber;
	//out<<"\" onClick=\"edit("<<aliKali[in]->idNumber<<")\" onBlur=\"setText("<<aliKali[in]->idNumber;
	//out<<")\">"<<correctionTable[in].name<<"</textarea><br>";
	out<<"<div>"<<correctionTable[in].name<<"</div><br>";
	out<<"<textarea id=\"outputStr\" name=\"setBase\" rows=\"3\" style=\"width:420px\"></textarea>\n";
	//out<<"<font size=5>"<<aliKali[in]->idNumber<<"|"<<aliKali[in]->mask32Count<<"</font><br>";
	out<<"<font size=3>Correlation value "<<correctionTable[in].correlation<<"</font><br>";
	out<<"<font size=3>Letter block width "<<correctionTable[in].img->columns()<<"</font><br>";
	out<<"<button onClick=\"submit()\">Set letter in base</button><br>\n";
	out<<"<button onClick=\"correlation("<<idNumber<<")\">Correlation letter in base</button><br>\n";
	out<<"<input type=\"text\" style=\"border:1px solid; width:100px\" id=\"searchLetter\"/>";
	out<<"<button onClick=\"openLetter()\">Open letter in base</button><br>\n";
	

    out<<"</td></tr><table>";
	
/*
	out<<"<div class=\"dE dM\" id=\"s";
	out<<aliKali[in]->idNumber<<"\" style=\"left:";
	out<<0<<"px; top:"<<size/2+aliKali[in]->y0*zoom<<"px; width:"<<size;
	out<<"px; height:"<<aliKali[in]->y1*zoom-aliKali[in]->y0*zoom<<"px; border: 1px solid grey;\" ></div>\n";
	
	//cout<<"draw "<<in<<END;
	x0=PICT_SIZE/2-aliKali[in]->letterW/2+aliKali[in]->dX;
	y0=PICT_SIZE/2-aliKali[in]->letterH/2+aliKali[in]->dY;
	w=aliKali[in]->letterW;
	h=aliKali[in]->letterH;
	out<<"<div class=\"dE\" id=\"g"<<aliKali[in]->idNumber<<"\" style=\"left:"<<x0*zoom<<"px; top:"<<y0*zoom;
	out<<"px; width:"<<w*zoom<<"px; height:"<<h*zoom<<"px;\">\n";
	out<<"<div class=\"dM\" width:"<<w*zoom<<"px; height:"<<3<<"px;></div>\n";
	out<<"</div>";
	
    out<<"</td></tr><tr><td>";
	out<<"<input  name=\"inputFile\"  type=\"hidden\" value=\""; out<<inputData->data["inputFile"];out<<"\">\n";
	out<<"<input  name=\"ocrData\"  type=\"hidden\" value=\"setBase\">\n";
	out<<"<input  name=\"inputFolder\"  type=\"hidden\" value=\""; out<<inputData->data["inputFolder"];out<<"\">\n";
	out<<"<textarea id=\"outputStr\" name=\"setBase\" rows=\"3\" style=\"width:"<<size<<"px\"></textarea>\n";
	out<<"</td></tr><table>";
*/
 //out<<"</form>";	
	return out.str();	
}//_____________________________________________________________________________




string GImageEditor::drawLetter(commandData *inputData,unsigned int idNumber){

	//cout<<"draw letter"<<endl;
	string str;
	int indexMask,indexX,indexY,x0,y0,w,h;
	int color0=255;    //fill
	int color1=0;     //on mask
	int color2=200;   //off mask
	int color3=80;     //letter
	int in;
	
   //находим нужную букву по idNumber
	for(int i=0;i<aliKali.letterCount;i++){
		if(aliKali[i]->idNumber==idNumber){
			in=i; break;
		}
	}
	
	GBitmap *outBitmap=GBitmap::create(PICT_SIZE,PICT_SIZE);
	GBitmap *img=aliKali[in]->mask128[0].unPackMask(); 
	for (int y = 0; y <img[0].rows() ;y++){
		//pSrc = (unsigned char*)letterImage->Canvas->ScanLine[y];
		for (int x = 0; x <img[0].columns(); x++){
			
			//if((int)img[0][y][x]){cout<<"1";}else{cout<<"0";}
			
			if(img[0][y][x]){
				
			}else{
				//if(outBitmap[0]
				//   [y+aliKali[index]->mask128[0].yMask]
				//   [x+aliKali[index]->mask128[0].xMask]==255){
					outBitmap[0]
					[y+aliKali[in]->mask128[0].yMask+PICT_SIZE/2]
					[x+aliKali[in]->mask128[0].xMask+PICT_SIZE/2]=color3;
				//}
			}
		}//cout<<END;
	}
	img->destroy();
	for(int m=0; m<aliKali[in]->mask32Count;m++){
		//SH(aliKali[in]->mask32[m].w*zoomImage);  SH(aliKali[in]->mask32[m].h*zoomImage);
		x0=aliKali[in]->mask32[m].xMask+PICT_SIZE/2+indexX*PICT_SIZE;
		y0=aliKali[in]->mask32[m].yMask+PICT_SIZE/2+indexY*PICT_SIZE;
		w=aliKali[in]->mask32[m].imgW-2;     //компенсация неточности JavaScript
		h=aliKali[in]->mask32[m].mH;
		//out+="<div class=\"dE dM\" id=\"p";
		//out+=aliKali[in]->letterIndex<<"_"<<m<<"_"<<indexMask<<"\" style=\"left:";
		///out+=x0*2<<"px; top:"<<y0*2<<"px; width:"<<w*2<<"px; height:";
		//out+=h*2<<"px; border: 1px";
		//if(m==0){
		//	out+=" solid red;\">";
		//}else{
		//	out+=" solid green;\">";
		//}
		//out+="<div class=\"nP\" id=\"m"<<aliKali[in]->letterIndex<<"_"<<m<<"_"<<indexMask<<"\" onClick=\"edit1(\'m";
		//out+=aliKali[in]->letterIndex<<"_"<<m<<"_"<<indexMask<<"\')\" onBlur=\"setText1(";
		//out+=aliKali[in]->letterIndex<<")\">"<<aliKali[in]->mask32[m].dlt0;
	 	        //sprintf(cbuf,"%d",aliKali[in]->mask32[m].status);
		//out+="</div></div>\n";
		///indexMask++;
		
		if(aliKali[in]->mask32[m].status<1)continue;
		if(w<0||h<0)continue;
		
		img=aliKali[in]->mask32[m].unPackMask();
		for (int y = 0; y <img[0].rows();y++){
			for (int x = 0; x <img[0].columns(); x++){
				if(img[0][y][x]){
				}else{
					outBitmap[0]
					[y+(aliKali[in]->mask32[m].yMask)+PICT_SIZE/2]
					[x+(aliKali[in]->mask32[m].xMask)+PICT_SIZE/2]=color1;
				}
				
			}//DM(END);
		}
		img->destroy();
		img=aliKali[in]->mask32[m].unPackMaskOff();
		for (int y = 0; y <img[0].rows();y++){
			for (int x = 0; x <img[0].columns(); x++){
				if(img[0][y][x]){
				}else{
					outBitmap[0]
					[y+(aliKali[in]->mask32[m].yMask)+PICT_SIZE/2]
					[x+(aliKali[in]->mask32[m].xMask)+PICT_SIZE/2]=color2;
				}
				
			}//DM(END);
		} 
		img->destroy();
		
	}
	
	str=drawToString(outBitmap);
	return str;
}



/*

void GImageEditor::drawBase(commandData *inputData){
	//ShowMessage("start_drawing");
	int i;
	//char *angDiffRecord, *angDiffSumRecord;
	//int *letterX;
	//int *letterY;
	//int shiftX=PICT_SIZE;
	//int shiftY=PICT_SIZE;
	OCRPoint letterCentre, vLetterCentre, startPoint, endPoint, vStart, vEnd;
	//float zoomImage=1;
	int index=0,indexMask,indexX,indexY,x0,y0,w,h;
	indexX=0;indexY=0;
	//int letterIndex=0;
	//unsigned char  *pSrc, *pDest;
	char cbuf[10];
	string path;
	//TImage *Image2,*letterImage;
	//float zoomImage=(float)zoomSlider->Position/100;     //SH(zoomImage);
	//SH(aliKali.base.size());
	if(!aliKali.base.size())return;
	//TPoint ris[9];
	//if(imgList==NULL)imgList=new TList;
	int color0=255;    //fill
	int color1=0;     //on mask
	int color2=200;   //off mask
	int color3=80;     //letter
	ofstream *out=&inputData->c_out;
	
	
	int imgW=PICT_SIZE*10;
	int imgH=aliKali.base.size()*PICT_SIZE/10+PICT_SIZE;
	GBitmap* outBitmap=GBitmap::create(imgW,imgH);
	outBitmap->fill(color0);
	
	//дальше рисуем все в два раза больше
	
	i=0;
	clock_t  tm_start;  tm_start=clock();
	char c[20];
	sprintf(c,"%d",tm_start);

	out+="<div style=\"position:absolute; left:0px; top:0px;\">";
	out+="<img src=\"OCRBase.jpg?link="<<c<<"\" wigth=\""<<imgW*2;
	out+="px\" height=\""<<imgH*2<<"px\">\n";

	//DM("tableDraw="<<tableDraw<<" aliKali[0].vectorCount="<<aliKali[0].vectorCount<<END);
	indexMask=0;

	for(int in=0;in<aliKali.base.size();in++){
		if(aliKali[in]->recordFlag==0)continue;
		string name=aliKali[in]->name;
		//if(name.find("/")!=string::npos){
		//  if(name.find("/2")==string::npos)continue;
		//}
		//cout<<"in="<<in<<" name="<<name<<END;
		if(indexX==10){
			indexX=0;
			indexY++;
		}
		int count=0;
		for(int m=0; m<aliKali[in]->mask32Count;m++){
			if(aliKali[in]->mask32[m].status<1)count++;
		}
		if(aliKali[in]->mask32Count==0)count++;
		//if(count==0)continue;
		
		out+="<div class=\"gL\" id=\"d"<<aliKali[in]->letterIndex<<"\" style=\"left:";
		out+=indexX*PICT_SIZE*2<<"px; top:"<<indexY*PICT_SIZE*2;
		out+="px; width:"<<PICT_SIZE*2<<"px; height:"<<PICT_SIZE*2<<"px;\">";
		//out+="<div class=\"ctrl\"><input type=\"checkbox\" id=\"b"<<aliKali[in]->letterIndex<<"\"  value=\"0\" onClick=\"checkGlyphBox("<<aliKali[in]->letterIndex<<")\" ";
		//if(aliKali[in]->newLetterInBook){
		// out+="checked";
		//}else{
		// out+="unchecked";
		//}
		out+="<div class=\"nG\" id=\""<<aliKali[in]->letterIndex;
		out+="\" onClick=\"edit("<<aliKali[in]->letterIndex<<")\" onBlur=\"setText1("<<aliKali[in]->letterIndex;
		out+=")\">"<<aliKali[in]->name<<"</div>";
		out+="<font size=5>"<<aliKali[in]->letterIndex<<"|"<<aliKali[in]->mask32Count<<"</font>";
		out+="</div>\n";

			out+="<div class=\"dE dM\" id=\"s";
			out+=aliKali[in]->letterIndex<<"\" style=\"left:";
			out+=indexX*PICT_SIZE*2<<"px; top:"<<indexY*PICT_SIZE*2+PICT_SIZE+aliKali[in]->y0*2<<"px; width:"<<PICT_SIZE*2;
			out+="px; height:"<<aliKali[in]->y1*2-aliKali[in]->y0*2<<"px; border: 1px solid grey;\" ></div>\n";

		for(int m=0; m<aliKali[in]->mask128Count;m++){
			//cout<<"draw "<<in<<END;
			GBitmap *img=GBitmap::create(aliKali[in]->mask128[m].mW,aliKali[in]->mask128[m].mH);
			aliKali[in]->mask128[m].unPackMask(img); 
			for (int y = 0; y <img[0].rows() ;y++){
				//pSrc = (unsigned char*)letterImage->Canvas->ScanLine[y];
				for (int x = 0; x <img[0].columns(); x++){
					
					//if((int)img[0][y][x]){cout<<"1";}else{cout<<"0";}
					
					if(img[0][y][x]){
						//letterImage->Canvas->Pixels[x+15][y+10]=clWhite;
					}else{
						if(outBitmap[0]
						   [y+aliKali[in]->mask128[m].yMask+PICT_SIZE/2+PICT_SIZE*indexY]
						   [x+aliKali[in]->mask128[m].xMask+PICT_SIZE/2+PICT_SIZE*indexX]==color0){
							outBitmap[0]
							[y+aliKali[in]->mask128[m].yMask+PICT_SIZE/2+PICT_SIZE*indexY]
							[x+aliKali[in]->mask128[m].xMask+PICT_SIZE/2+PICT_SIZE*indexX]=color3;
						}
					}
				}//cout<<END;
			}
			//exit(0);
			img->destroy();
			x0=PICT_SIZE/2+indexX*PICT_SIZE-aliKali[in]->letterW/2+aliKali[in]->dX;
			//y0=aliKali[in]->mask128[m].yMask+PICT_SIZE/2+indexY*PICT_SIZE;
			y0=PICT_SIZE/2+indexY*PICT_SIZE-aliKali[in]->letterH/2+aliKali[in]->dY;
			w=aliKali[in]->letterW;
			h=aliKali[in]->letterH;
			//y1=y0+h;
			out+="<div class=\"dE\" id=\"g";
			sprintf(cbuf,"%d",aliKali[in]->letterIndex); out+=cbuf;
			out+="\" style=\"left:";
			sprintf(cbuf,"%d",x0*2); out+=cbuf;
			out+="px; top:";
			sprintf(cbuf,"%d",y0*2); out+=cbuf;
			out+="px; width:";
			sprintf(cbuf,"%d",w*2); out+=cbuf;
			out+="px; height:";
			sprintf(cbuf,"%d",h*2); out+=cbuf;
			out+="px;\">\n";
			out+="<div class=\"dM\" width: ";
			sprintf(cbuf,"%d",w*2); out+=cbuf;
			out+="px; height:";
			sprintf(cbuf,"%d",3); out+=cbuf;
			out+="px;></div>\n";
			out+="</div>";
			index++;
			
			
		}
		


		for(int m=0; m<aliKali[in]->mask32Count;m++){
			//SH(aliKali[in]->mask32[m].w*zoomImage);  SH(aliKali[in]->mask32[m].h*zoomImage);

			x0=aliKali[in]->mask32[m].xMask+PICT_SIZE/2+indexX*PICT_SIZE;
			y0=aliKali[in]->mask32[m].yMask+PICT_SIZE/2+indexY*PICT_SIZE;
			w=aliKali[in]->mask32[m].imgW-2;     //компенсация неточности JavaScript
			h=aliKali[in]->mask32[m].mH;
			out+="<div class=\"dE dM\" id=\"p";
			out+=aliKali[in]->letterIndex<<"_"<<m<<"_"<<indexMask<<"\" style=\"left:";
			out+=x0*2<<"px; top:"<<y0*2<<"px; width:"<<w*2<<"px; height:";
			out+=h*2<<"px; border: 1px";
			if(m==0){
			   out+=" solid red;\">";
			}else{
			   out+=" solid green;\">";
			}
			out+="<div class=\"nP\" id=\"m"<<aliKali[in]->letterIndex<<"_"<<m<<"_"<<indexMask<<"\" onClick=\"edit1(\'m";
			out+=aliKali[in]->letterIndex<<"_"<<m<<"_"<<indexMask<<"\')\" onBlur=\"setText1(";
			out+=aliKali[in]->letterIndex<<")\">"<<aliKali[in]->mask32[m].dlt0;
			//sprintf(cbuf,"%d",aliKali[in]->mask32[m].status);
			out+="</div></div>\n";
			indexMask++;

			if(aliKali[in]->mask32[m].status<1)continue;

			GBitmap *img=GBitmap::create(aliKali[in]->mask32[m].mW,aliKali[in]->mask32[m].mH);
			aliKali[in]->mask32[m].unPackMask(img);
			for (int y = 0; y <img[0].rows();y++){
				for (int x = 0; x <img[0].columns(); x++){
					if(img[0][y][x]){
					}else{
						outBitmap[0]
						[y+(aliKali[in]->mask32[m].yMask)+PICT_SIZE/2+PICT_SIZE*indexY]
						[x+(aliKali[in]->mask32[m].xMask)+PICT_SIZE/2+PICT_SIZE*indexX]=color1;
					}

				}//DM(END);
			}
			aliKali[in]->mask32[m].unPackMaskOff(img);
			for (int y = 0; y <img[0].rows();y++){
				for (int x = 0; x <img[0].columns(); x++){
					if(img[0][y][x]){
					}else{
						outBitmap[0]
						[y+(aliKali[in]->mask32[m].yMask)+PICT_SIZE/2+PICT_SIZE*indexY]
						[x+(aliKali[in]->mask32[m].xMask)+PICT_SIZE/2+PICT_SIZE*indexX]=color2;
					}

				}//DM(END);
			} img->destroy();

		}

		for(int m=aliKali[in]->mask32Count; m<=11;m++){
			//SH(aliKali[in]->mask32[m].w*zoomImage);  SH(aliKali[in]->mask32[m].h*zoomImage);

			x0=indexX*PICT_SIZE;
			y0=indexY*PICT_SIZE;
			w=10;
			h=10;
			out+="<div class=\"dE dM\" id=\"p"<<aliKali[in]->letterIndex<<"_"<<m<<"_"<<indexMask;
			out+="\" style=\"left:"<<x0*2<<"px; top:"<<y0*2<<"px; width:";
			out+=w*2<<"px; height:"<<h*2<<"px; border: 1px solid green;\">";
			out+="<div class=\"nP\" id=\"m"<<aliKali[in]->letterIndex<<"_"<<m<<"_"<<indexMask;
			out+="\" onClick=\"edit1(\'m"<<aliKali[in]->letterIndex<<"_"<<m<<"_"<<indexMask;
			out+="\')\" onBlur=\"setText1("<<aliKali[in]->letterIndex<<")\">8</div></div>\n";
			indexMask++;
		}
		for(int m=12; m<15;m++){
			//SH(aliKali[in]->mask32[m].w*zoomImage);  SH(aliKali[in]->mask32[m].h*zoomImage);
			
			x0=indexX*PICT_SIZE+10;
			y0=indexY*PICT_SIZE;
			w=10;
			h=10;
			out+="<div class=\"dE dM\" id=\"p"<<aliKali[in]->letterIndex<<"_"<<m<<"_"<<indexMask;
			out+="\" style=\"left:"<<x0*2<<"px; top:"<<y0*2<<"px; width:";
			out+=w*2<<"px; height:"<<h*2<<"px; border: 1px solid green;\">";
			out+="<div class=\"nP\" id=\"m"<<aliKali[in]->letterIndex<<"_"<<m<<"_"<<indexMask;
			out+="\" onClick=\"edit1(\'m"<<aliKali[in]->letterIndex<<"_"<<m<<"_"<<indexMask;
			out+="\')\" onBlur=\"setText1("<<aliKali[in]->letterIndex<<")\">28</div></div>\n";
			indexMask++;
		}

		

		//DP("aliKali["<<in<<"].vectorCount="<<aliKali[in]->vectorCount<<END);
		
         
		//letterImage->Canvas->Font->Name = "Yagpo";
		//letterImage->Canvas->Font->Size=7;
		//if(letterBase[recordIndex].name[0]){
		//letterImage->Canvas->TextOut(3,1,IntToHex(letterBase[recordIndex].name[0],4));
		//letterImage->Canvas->TextOut(3,3,aliKali[in]->stackFlag);
		//letterImage->Canvas->Font->Size=12;
		//letterImage->Canvas->TextOut(15,3,UTF_to_Unicode(aliKali[in]->name).c_str());
		//letterImage->Canvas->Font->Size=7;
		//letterImage->Canvas->TextOut(3,65,aliKali[in]->OCRIndex);
		//letterImage->Canvas->TextOut(15,65,aliKali[in]->Character);
		//letterImage->Canvas->Font->Size=8;
		//letterImage->Canvas->TextOut(90,3,in);
		//letterImage->Canvas->TextOut(3,45,(short)letterBase[recordIndex].letterIndex);
		//}
		
		///Image2->Canvas->Draw(PICT_SIZE*indexX,PICT_SIZE*indexY, letterImage->Picture->Bitmap);
		//outBitmapDraw->Canvas->Draw(PICT_SIZE*indexX,PICT_SIZE*indexY, letterImage);
		indexX++;
		
	}
	
	out+="<form enctype=\"application/x-www-form-urlencoded\" method=\"post\" action=\"/cgi/yagpoOCR.cgi\" name=\"main\">\n";
	out+="<input  name=\"inputFile\"  type=\"hidden\" value=\""; out+=inputData->data["inputFile"];out+="\"><br>\n";
	out+="<input  name=\"ocrData\"  type=\"hidden\" value=\"setBase\"><br>\n";
	out+="<input  name=\"inputFolder\"  type=\"hidden\" value=\""; out+=inputData->data["inputFolder"];out+="\"><br>\n";
	out+="<button name=\"submit\" value=\"submit\" type=\"submit\">Set letter in base</button><br>\n";
	out+="<div class=\"header\"><textarea ID=\"outputStr\" name=\"setBase\" cols=\"110\" rows=\"7\"></textarea></div></div>\n";
	out+="</form>";

	path=inputData->data["inputFolder"]+"/OCRBase.jpg";

	WriteImageData(outBitmap,path,0);
	
}//_____________________________________________________________________________
*/
 /*
 void TmainOCRBaseReader::drawMatch(int stringIndex, int wordIndex){
 
 char *angDiffRecord, *angDiffSumRecord;
 short *letterX;
 short *letterY;
 int PICT_SIZE=90;
 short shiftX=PICT_SIZE;
 short shiftY=PICT_SIZE;
 static int sIm=0;
 OCRPoint letterCentre, vLetterCentre, startPoint, endPoint, vStart, vEnd;
 //float zoomImage=1;
 short index,count,indexX,indexY;
 indexX=0;indexY=0;
 int letterIndex=0;
 float zoomImage=(float)zoomSlider->Position/100;
 
 if(!aliKali[0].vectorCount)return;
 TControl *tIm;
 
 int i=0;
 //ShowMessage(ScrollBox2->ComponentCount);
 for(i=ScrollBox2->ComponentCount-1;i>0;i--){
 letterImage=(TImage*)ScrollBox2->Components[i];
 ScrollBox2->RemoveComponent(ScrollBox2->Components[i]);
 letterImage->Hide();
 delete letterImage;
 }
 
 i=0;
 vector<OCRMatch> *match=&strArray[0][stringIndex].wordArray[wordIndex].match;
 count=match[0].size();
 
 
 //DM("tableDraw="<<tableDraw<<" aliKali[0].vectorCount="<<aliKali[0].vectorCount<<END);
 for(int in=0;in<count;in++){
 //DM("i="<<i<<" letterIndex="<<END);
 letterImage= new TImage(ScrollBox2);
 letterImage->Name=(AnsiString)"glyphMatch_"+IntToStr(sIm);
 letterImage->Width=shiftX; letterImage->Height=PICT_SIZE;
 letterImage->Left=indexX*shiftX; //Pozition X
 letterImage->Top=0+shiftX*indexY; //Pozition Y
 indexX++;  sIm++;
 if(indexX*shiftX>ScrollBox2->Width-shiftX){
 indexX=0;
 indexY++;
 }
 letterImage->OnClick=OnLetterImageClick;
 //letterImage->Caption=IntToStr(i); //Подпись кнопки
 letterImage->Parent=ScrollBox2;
 
 letterImage->Canvas->Pen->Color = clWhite;
 letterImage->Canvas->FillRect(Rect(0,0,shiftX,shiftX));
 letterImage->Canvas->Pen->Color = clBlack;
 letterImage->Canvas->Rectangle(Rect(0,0,shiftX,shiftX));
 
 letterImage->Canvas->Pen->Color = clBlue;
 
 
 //letterCentre.x=letterBase[record].letterCentre.x;
 //letterCentre.y=letterBase[record].letterCentre.y; //c_out+="x="<<letterCentre.x<<" y="<<letterCentre.y<<endl;
 letterIndex=match[0][in].letterIndex;
 
 for(int vIn=0; vIn<aliKali[letterIndex].vectorCount;vIn++){
 DM("aliKali["<<in<<"].vectorCount="<<aliKali[in]->vectorCount<<END);
 vStart.x=aliKali[letterIndex].v[vIn].vStart.x;  //DM("vStart.x="<<vStart.x<<END);
 vStart.y=aliKali[letterIndex].v[vIn].vStart.y;  //DM("vStart.y="<<vStart.y<<END);
 
 vEnd.x=aliKali[letterIndex].v[vIn].vEnd.x;    //DM("vEnd.x="<<vEnd.x<<END);
 vEnd.y=aliKali[letterIndex].v[vIn].vEnd.y;    //DM("vEnd.y="<<vEnd.y<<END);
 
 
 startPoint.x=(vStart.x)*zoomImage+25;
 startPoint.y=(vStart.y)*zoomImage+25;
 
 endPoint.x=(vEnd.x)*zoomImage+25;
 endPoint.y=(vEnd.y)*zoomImage+25;  // c_out+=endPoint.y<<" ";
 letterImage->Canvas->MoveTo(startPoint.x,startPoint.y);
 //letterImage->Canvas->MoveTo(0,0);
 letterImage->Canvas->LineTo(endPoint.x,endPoint.y);
 
 letterImage->Canvas->Font->Name = "Arial";
 letterImage->Canvas->Font->Size=8;
 //if(letterBase[recordIndex].name[0]){
 //letterImage->Canvas->TextOut(3,1,IntToHex(letterBase[recordIndex].name[0],4));
 letterImage->Canvas->TextOut(3,1,aliKali[letterIndex].stackFlag);
 letterImage->Canvas->TextOut(15,1,aliKali[letterIndex].Wylie.c_str());
 //ShowMessage(match[0][in].correlation);
 letterImage->Canvas->TextOut(3,65,match[0][in].correlation);
 letterImage->Canvas->TextOut(25,65,match[0][in].Character);
 letterImage->Canvas->TextOut(45,1,in);
 //letterImage->Canvas->TextOut(19,45,match[0][in].OCRIndex);
 //letterImage->Canvas->TextOut(3,45,(short)letterBase[recordIndex].letterIndex);
 //}
 }
 //Image2->Canvas->Draw(shiftX*indexX,0, Image2->Picture->Bitmap);
 
 }
 //MyList=new TList;
 
 tableDraw=1;
 }
 
 
 void TmainOCRBaseReader::redrawLettersInBase(){
 //c_out+="start_redrawing"<<endl;
 
 short i, letterIndex;
 i=0;letterIndex=0;
 while(i < letterBase[0].allContourCount){
 letterImage=(TImage*)MyList->Items[letterIndex];
 drawLetter(i);
 i+=letterBase[i].letterSetCount;
 letterIndex++;
 }
 
 }//_____________________________________________________________________________
 
 
 void TmainOCRBaseReader::drawLetter(short letterIndex){
 
 DM("start_drawing new letter "<<record<<END;
 short i,recordIndex;
 char *angDiffRecord, *angDiffSumRecord;
 short *letterX;
 short *letterY;
 float zoomImage=(float)zoomSlider->Position/100;
 short index,count;
 OCRPoint letterCentre, vLetterCentre, startPoint, endPoint, vStart, vEnd;
 
 letterImage->Canvas->Pen->Color = clWhite;
 letterImage->Canvas->FillRect(Rect(0,0,56,56));
 letterImage->Canvas->Pen->Color = clBlack;
 letterImage->Canvas->Rectangle(Rect(0,0,56,56));
 
 letterImage->Canvas->Pen->Color = clBlue;
 
 letterCentre.x=letterBase[record].letterCentre.x;
 letterCentre.y=letterBase[record].letterCentre.y; //c_out+="x="<<letterCentre.x<<" y="<<letterCentre.y<<endl;
 
 for(i=0; i < letterBase[record].letterSetCount; i++){
 recordIndex=letterBase[record].letterSet[i];
 //c_out+="letterBase["<<recordIndex<<"].vectorCount="<<letterBase[recordIndex].vectorCount<<endl;
 //c_out+="letterBase["<<recordIndex<<"].angLength="<<letterBase[recordIndex].angLength<<endl;
 
 for (count=0; count<letterBase[recordIndex].vectorCount;count++) {
 //c_out+="count="<<count<<endl;
 vStart.x=letterBase[recordIndex].v[count].vStart.x-letterCentre.x;  //c_out+="vStart.x="<<vStart.x<<endl;
 vStart.y=letterBase[recordIndex].v[count].vStart.y-letterCentre.y;  //c_out+="vStart.y="<<vStart.y<<endl;
 
 vEnd.x=letterBase[recordIndex].v[count].vEnd.x-letterCentre.x;    //c_out+="vEnd.x="<<vEnd.x<<endl;
 vEnd.y=letterBase[recordIndex].v[count].vEnd.y-letterCentre.y;   //c_out+="vEnd.y="<<vEnd.y<<endl;
 
 
 startPoint.x=(vStart.x)*zoomImage+25;
 startPoint.y=(vStart.y)*zoomImage+25;
 
 endPoint.x=(vEnd.x)*zoomImage+25;
 endPoint.y=(vEnd.y)*zoomImage+25;  // c_out+=endPoint.y<<" ";
 letterImage->Canvas->MoveTo(startPoint.x,startPoint.y);
 //letterImage->Canvas->MoveTo(0,0);
 letterImage->Canvas->LineTo(endPoint.x,endPoint.y);
 
 letterImage->Canvas->Font->Name = "Arial";
 letterImage->Canvas->Font->Size=8;
 if(letterBase[recordIndex].name[0]){
 letterImage->Canvas->TextOut(3,1,IntToHex(letterBase[recordIndex].name[0],4));
 letterImage->Canvas->TextOut(3,45,(short)letterBase[recordIndex].letterIndex);
 }
 //cout+=vectorRecordBase[count].correlation<<" ";
 
 }//end main for (index=0; index<contourRecordBase[0].allContourCount
 }//end count lettterSet
 
 }//_____________________________________________________________________________
 
 void __fastcall  TmainOCRBaseReader::OnLetterImageClick(TObject *Sender){
 //Label1->Caption=((TImage *)Sender)->Name;
 AnsiString str=((TImage *)Sender)->Name;
 
 //((TImage *)Sender)->Visible=false;
 string s;
 for(int a=7;a<=str.Length();a++)s.push_back(str[a]);
 int in=atoi(s.c_str());
 selectLetters.push_back(in);
 
 ((TImage *)Sender)->Canvas->Pen->Color = clRed;
 ((TImage *)Sender)->Canvas->Rectangle(Rect(3,3,15,15));
 
 }//_____________________________________________________________________________
 
 */










