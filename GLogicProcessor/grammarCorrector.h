string GLogicProcessor::grammarCorrector(commandData* inputData, vector<wordOCR> &pageText,vector<stringOCR> &correctionWordArray,int mode){
cout<<"Start grammar correction pageText.size()="<<pageText.size()<<" delimeterTib.size()="<<delimeterTib.size()<<" correctionWordArray.size()="<<correctionWordArray.size()<<END;

	int recordFound, length,c;
	//string srcString=str_+" ";
	string srcLine,srcStr,str,testLine,request,answer,oldString;    
		str="";
	if(!dictionaryReady){cout<<"dictionary not ready"; return str;}
	
	
	//unsigned int hash;
	char buffer[5]; 
    vector<stringOCR> stringItemVector;
	vector<string>strResultArray;
	stringOCR wordLine,testLineOCR,testLineOCR_revers;
	string strResult,strReport,strReportMem;
	string strCount;
	int print=0;
	static int startSocket=0;
	int entryStart;
	string color; 


	for(int a=0;a<pageText.size();a++){
			if(pageText[a]==commentaryIndex){
			pageText[a].commentaryIndex=pageText[a].name;
			pageText[a].name="";	
		}	
		if(pageText[a]==delimeterTib){  //???
			pageText[a].delimeter=pageText[a].name;
			pageText[a].name="";	
		}
	}

	for(int a=1;a<pageText.size();a++){
#ifdef MACOS
			//vowel normalisation
			if(pageText[a].name=="ི")if(pageText[a-1].name.find("ི",0)!=string::npos)pageText.erase(pageText.begin()+a);
			if(pageText[a].name=="ེ")if(pageText[a-1].name.find("ུ",0)!=string::npos){pageText.erase(pageText.begin()+a);pageText[a-1].name=str_replace("ུ","ེ", pageText[a-1].name);}
			if(pageText[a].name=="ི")if(pageText[a-1].name.find("ེ",0)!=string::npos){pageText.erase(pageText.begin()+a);pageText[a-1].name=str_replace("ེ", "ི", pageText[a-1].name);}
			if(pageText[a].name=="ོ")if(pageText[a-1].name.find("ེ",0)!=string::npos){pageText.erase(pageText.begin()+a);pageText[a-1].name=str_replace("ེ", "ོ", pageText[a-1].name);}
			if(pageText[a].name=="ེ")if(pageText[a-1].name.find("ེ",0)!=string::npos||
									   pageText[a-1].name.find("ི",0)!=string::npos||
									   pageText[a-1].name.find("ོ",0)!=string::npos)pageText.erase(pageText.begin()+a);
			if(pageText[a].name=="ོ")if(pageText[a-1].name.find("ོ",0)!=string::npos)pageText.erase(pageText.begin()+a);
			if(pageText[a].name=="་/")if(pageText[a-1].name.find("་",0)!=string::npos||pageText[a-1].delimeter=="་")pageText.erase(pageText.begin()+a);
			//mantra normalisation
			if(pageText[a].name=="ཾ")if(pageText[a-1].delimeter.find("ཿ",0)!=string::npos)pageText.erase(pageText.begin()+a);
			if(pageText[a].name=="ྃ")if(pageText[a-1].name.find("ྃ",0)!=string::npos)pageText.erase(pageText.begin()+a);
			if(pageText[a].name=="ཽ")if(pageText[a-1].name.find("ཽ",0)!=string::npos)pageText.erase(pageText.begin()+a);
			if(pageText[a].name=="ོཾ")if(pageText[a-1].name.find("ོཾ",0)!=string::npos)pageText.erase(pageText.begin()+a);
#endif
	}
	
	for(int a=0;a<pageText.size();a++){
		DT("pageText["<<a<<"]="<<pageText[a].name<<" ");	
		DT("pageText["<<a<<"]="<<pageText[a].name<<" delimeter="<<pageText[a].delimeter<<endl);
	}

		
	
	if(mode==SOCKET_MODE){
		//if(!startSocket){
		//	request="start";
		//	dataIP(request,INIT_SOCKET);
		//	//DP(" str="<<srcString<<END);
		//}startSocket++;
    }
DT("%2");
	vector<string>delimeterString;
#ifdef MACOS
	delimeterString.push_back("།");
	delimeterString.push_back("༈");
	delimeterString.push_back("༾");
	delimeterString.push_back("༿");
	delimeterString.push_back("༼");
	delimeterString.push_back("༽");
	delimeterString.push_back("_");
	delimeterString.push_back("།/");
	delimeterString.push_back(" ");
	delimeterString.push_back("@");
#endif

	
	//wordList=explode(" ",str_); strResult.resize(wordList.size());
	//cout<<END<<END;
cout<<"%3";	
	for(int a=0;a<pageText.size();a++){
		//if(pageText[a].delimeter==" "||pageText[a].delimeter=="@"){cout<<"@@@";
		//    DT(" @@@_pageText["<<a<<"].name="<<pageText[a].name<<" d="<<pageText[a].delimeter<<
			  // " c="<<pageText[a].commentaryIndex<<" n="<<pageText[a].newLine<<" str="<<wordLine.str<<END);
		//	   strResult+="@";
		//}else{ //continue;
		  wordLine.push_back(pageText[a]);  
		  DT(" pageText["<<a<<"].name="<<pageText[a].name<<" d="<<pageText[a].delimeter<<
			  " c="<<pageText[a].commentaryIndex<<" n="<<pageText[a].newLine<<" str="<<wordLine.str<<END);
		//}
		if(pageText[a].testDelimeter(delimeterString)||a==pageText.size()-1){
			
			//stringItemVector=explode(delimeterTib,wordLine); //stringItemVector now contain all syllabons from string
			
			//for(int i=0;i<wordLine.size();i++){
			//	DP("str_=/"<<wordLine[i]->name<<"/ delimeter="<<wordLine[i]->delimeter<<endl);
			//}	
			    //cout<<wordLine.strHTML<<endl; exit(0);
			
				DT("start report wordLine.size()="<<wordLine.size()<<" str="<<wordLine.str<<END);
				for (int entry=0; entry<wordLine.size();entry++){ //for every syllabon in List
					for (int k=wordLine.size();k>entry;k--){ //for every syllabon in List
						recordFound=0;
						srcLine=""; srcStr=""; length=0; testLineOCR.resize(0);
						for (c=entry;c<k;c++){
							//DP("stringItemVector["<<c<<"].str=/"<<wordLine[c]->name<<"/ wordLine["<<c<<"].delimeter="<<wordLine[c]->delimeter<<endl);
							testLineOCR.push_back(*wordLine[c]);  //all syllabons in this part of source string
                            //cout<<"testLineOCR.x0="<<testLineOCR.x0<<" wordLine["<<c<<"].x0="<<wordLine[c]->x0<<END;
							srcStr+=wordLine[c]->name+wordLine[c]->delimeter;
							length++;
						}
						DT(" testLineOCR.size()="<<testLineOCR.size()<<" testLineOCR.str=/"<<testLineOCR.str<<" testLineOCR.name=/"<<testLineOCR.name<<"/"<<END); 
                        
						testLine=testLineOCR.str; //all string syllables without delimeters

						if(testLine!=""&&testLine!=" "&&testLine!=delimeterString[0]){
						testLine+=":|:";
						testLine+=srcStr;
							DT(" srcLine="<<srcStr<<" testLine=/"<<testLine<<"/ length="<<length<<END);
							if(mode==SOCKET_MODE){
							  //answer=dataIP(testLine,REMAP_STRING_TIB);
							}else{
							   answer=remapString(testLine);
							}	
						
						}else{
						    answer=srcStr;
							testLineOCR.str=srcStr;
						   
						}	
						
						
						
						
						if(answer!=":|:"){
							recordFound=1;
							//str=answer;
							DP("match found testLineOCR.str="<<testLineOCR.str<<" testLineOCR.name="<<testLineOCR.name<<" answer="<<answer<<" srcStr="<<srcStr<<END);
							//strReport=str_replace(testLineOCR.name,answer,srcStr);
							strReport=answer;
							//strCount=str_replace("་","", answer); length=(answer.size()-strCount.size())/3+1; 
							DP(" length="<<length<<" answer=/"<<answer<<"/ s="<<answer.size()<<"-"<<" strReport="<<strReport<<endl);
							//DP("answer="<<str<<END);							
						
						}else{ DP(" not_found"<<" length="<<length<<END);
                               if(length==1)recordFound=1;
							   strReport=testLineOCR.name;
						}
						
						
						if(recordFound){
							DT("record found "<<k<<" e="<<entry<<END);
							if(srcStr=="།"&&(entry==0||entry==wordLine.size()-1))length=9;
							DT("input str="<<testLineOCR.name<<" strReport="<<strReport<<END);
							if(srcStr!=" "&&srcStr!="@"){
								strReport=testLineOCR.set_id(strReport);
								DT("output str="<<strReport<<END);
									if(length<5){
										testLineOCR.path=fileName(inputData->data["inputFile"]); 
										testLineOCR.file=fileName(testLineOCR.path);
										testLineOCR.stringFlag=0;  //heed check;
									//если строка не найдена проверяем есть ли в словаре эта строка плюс предыдущий слог
									//(обратный поиск)
										
										int entry_revers=entry-1; int letterCount=0, length_revers=0;
										while(entry_revers>0&&wordLine[entry_revers]->name=="")entry_revers--; //пропускаем разделители слогов
									    //string strReport1;
										while(entry_revers>0){ DT("revers search"<<endl);
											testLineOCR_revers.resize(0); srcStr=""; length_revers=0;
											for (c=entry_revers;c<k;c++){
												DT("stringItemVector["<<c<<"].str=/"<<wordLine[c]->name<<"/ wordLine["<<c<<"].delimeter="<<wordLine[c]->delimeter<<endl);
												testLineOCR_revers.push_back(*wordLine[c]);  //all syllabons in this part of source string
												srcStr+=wordLine[c]->name+wordLine[c]->delimeter;
												length_revers++;
											}
											
											testLine=testLineOCR_revers.str; //all string syllables without delimeters
											if(testLine!=""&&testLine!=" "&&testLine!=delimeterString[0]){
												testLine+=":|:";
												testLine+=srcStr;
												DT(" srcLine="<<srcStr<<" testLine=/"<<testLine<<"/ length_revers="<<length_revers<<END);
												if(mode==SOCKET_MODE){
													//answer=dataIP(testLine,REMAP_STRING_TIB);
												}else{
													answer=remapString(testLine);
												}	
												if(answer!=":|:"){  
													//теперь нужно объединить результаты прямого и обратного поиска
													//если ответ найден, то в текст пишем новую объединенную строку
													DT("match="<<length_revers<<" entryStart="<<entryStart<<endl);
													testLineOCR_revers.resize(0); length_revers=0; srcStr="";
													for (c=entryStart;c<k;c++){
														DT("wordLine["<<c<<"]->name=/"<<wordLine[c]->name<<"/ wordLine["<<c<<"].delimeter="<<wordLine[c]->delimeter<<endl);
														testLineOCR_revers.push_back(*wordLine[c]);  //all syllabons in this part of source string
														//cout<<"testLineOCR.x0="<<testLineOCR.x0<<" wordLine["<<c<<"].x0="<<wordLine[c]->x0<<END;
														srcStr+=wordLine[c]->name+wordLine[c]->delimeter;
														length_revers++;
													}
													DT("new str="<<testLineOCR_revers.name<<endl);
													strReport=remapTibString(testLineOCR_revers.name,answer); 
													DT("strReport="<<strReport<<endl);

													
													strReport=testLineOCR_revers.set_id(strReport);
													DT("full report="<<strReport<<endl);
													length=length_revers;
													strResultArray.pop_back();  //стираем предыдущую строку
													break;
												}
												
											}else{
												entryStart=entry;
												break;//если строка пустая то прекращаем обратный разбор строки												
											}	
											entry_revers--;
											if(answer==":|:"){ //если строка не найдена то ищем еще 7 букв (размер слога)
												letterCount++;
												if(letterCount==7||entry_revers==0){
													DT("no match entry="<<entry<<endl)
													entryStart=entry;
													break;        //если предыдущий слог не найден, то прекращаем обратный разбор строки
												}	
											}
											
										}
									}
								        DT("length="<<length<<endl);
 										if(length<6)checkInCorrectionTable(correctionWordArray,testLineOCR,srcStr);   
								
										if(length==0)color="<span style=\"color:#FF0000\">";
										if(length==1)color="<span style=\"color:#FF0000\">";
										if(length==2)color="<span style=\"color:#FF0000\">";
										if(length==3)color="<span style=\"color:#FF0000\">";
										if(length==4)color="<span style=\"color:#FF0000\">";
										if(length==5)color="<span style=\"color:#FF0000\">";
										if(length==6)color="<span style=\"color:#008800\">";
										if(length==7)color="<span style=\"color:#007700\">";
										if(length==8)color="<span style=\"color:#006600\">";
										if(length==9)color="<span style=\"color:#006633\">";
										if(length==10)color="<span style=\"color:#009900\">";
										if(length==11)color="<span style=\"color:#009900\">";
										if(length==12)color="<span style=\"color:#006633\">";
										if(length==13)color="<span style=\"color:#006633\">";
										if(length==14)color="<span style=\"color:#0033FF\">";
										if(length==15)color="<span style=\"color:#0033FF\">";
										if(length==16)color="<span style=\"color:#0066CC\">";
										if(length==16)color="<span style=\"color:#0066CC\">";
										if(length==17)color="<span style=\"color:#003399\">";
										if(length==18)color="<span style=\"color:#003399\">";
										if(length==19)color="<span style=\"color:#0000CC\">";
										if(length==20)color="<span style=\"color:#0000CC\">";
										if(length==21)color="<span style=\"color:#000099\">";
										if(length==22)color="<span style=\"color:#000099\">";
										if(length==23)color="<span style=\"color:#000066\">";
										if(length==24)color="<span style=\"color:#000066\">";
										if(length==25)color="<span style=\"color:#000033\">";
										if(length==26)color="<span style=\"color:#000033\">";
										if(length>=27)color="<span style=\"color:#000000\">";
										strResult=color+strReport+"</span>";
								        //strResultArray.push_back("/#/<br>");
								        //cout<<"/@@@ strResult="<<strResult<<endl;
										strResultArray.push_back(strResult);
								        //strResultArray.push_back("/@/<br>");								
								        DT("strResult="<<strResult<<endl);
							}else{
							  strResult=" ";
							  strResultArray.push_back(strResult);	
							}	
							strReportMem=answer;   //запоминаем результаты разбора строки для использования при обратном поиске
							if(!testLineOCR_revers.size())entryStart=entry;
							testLineOCR_revers.resize(0);
							entry=k-1;
							break;	
						} 			
					}//end for (int k=StringItemList->Count
				}//end for (int entry=0;
	    //request="stop";
	    //dataIP(request,CLOSE_SOCKET);
		    wordLine.resize(0); //exit(0);
		} //wordLine analise
		
	} //pageText analise
	DT("%4");
    
	strResult="<br>\n";  //cout<<"strResult="<<strResult<<endl;
	strResultArray.push_back(strResult);
	strResult=implode("",strResultArray);
	
	return strResult;


}//__________________________________________________________________________

string GLogicProcessor::remapTibString(string &input0, string &input1){

	//cout<<"//@@@@@@@@@@@/ input0="<<input0<<" input1="<<input1<<endl;
	if(input0.size()<7||input1.size()<7)return (input0+input1);
	string str=substr(0, 7, input1);

	int pos=input0.rfind(str);
	//cout<<"str"<<str<<" pos="<<pos<<endl;
	
	str=substr(0, pos, input0);
	str+=input1;
	return str;

}


void GLogicProcessor::checkInCorrectionTable(vector<stringOCR> &correctionTable,stringOCR &testStr,string &srcStr){

	int x0,x1,y0,y1;
	int dl=5;
	int flag=1;
	//cout<<"//________________ testStr.str="<<testStr.str<<" testStr.file="<<testStr.file<<END;
	int maxX=0, maxY=0,minX=90000,minY=90000;
	testStr.correlation=100;
	
	for(int index=0;index<testStr.size();index++){
		x0=testStr.wordArray[index].x0+dl;
		y0=testStr.wordArray[index].y0+dl;
		x1=testStr.wordArray[index].x1-dl;
		y1=testStr.wordArray[index].y1-dl;
		
		if(x0<minX)minX=x0;
		if(y0<minY)minY=y0;
		if(x1>maxX)maxX=x1;
		if(y1>maxY)maxY=y1;
		//dX=(x1-x0)/2;
		//dY=(y1-y0)/2;
		//testStr.wordArray[index].checkFlag=0;
		//cout<<"testStr.wordArray["<<index<<"].correlation="<<testStr.wordArray[index].correlation<<END;
		if(testStr.wordArray[index].correlation<99){flag=0;}
		if(testStr.correlation>testStr.wordArray[index].correlation)testStr.correlation=testStr.wordArray[index].correlation;

	}
	if(!flag){
		testStr.x0=minX; 
		testStr.y0=minY;
		testStr.x1=maxX;
		testStr.y1=maxY; 
		ostringstream out;
		out<<testStr.file<<minX<<minY<<maxX<<maxY;
		string str=out.str();
		testStr.idNumber=strToHash(str.c_str(), str.size());
		testStr.name=str_replace("<br/>", "{br}",testStr.name);
		correctionTable.push_back(testStr);
	}
		/*
		for(int i=0;i<correctionWordArray.size();i++){
			//if(correctionTable[i].stringFlag!=1)continue;
			if(correctionWordArray[i].file!=testStr.file)continue;	

			
					//cout<<"correctionTable["<<i<<"].stringFlag="<<correctionTable[i].stringFlag<<" str="<<correctionTable[i].str<<" correctionTable[i].file="<<correctionTable[i].file;
					
					dX_=(correctionWordArray[i].x1-correctionWordArray[i].x0)/2;
					dY_=(correctionWordArray[i].y1-correctionWordArray[i].y0)/2;
					
					//cout<<"    x0="<<x0<<" y0="<<y0<<" x1="<<x1<<" y1="<<y1<<END;
					//cout<<"    x0_="<<correctionTable[i].x0<<" y0_="<<correctionTable[i].y0<<" x1_="<<correctionTable[i].x1<<" y1_="<<correctionTable[i].y1<<END;
					if(dX-dX_>dl)continue;
					if(dX_-dX>dl)continue;
					if(dY-dY_>dl)continue;
					if(dY_-dY>dl)continue;
					
					if(x0<correctionWordArray[i].x0)continue;
					if(y0<correctionWordArray[i].y0)continue;
					if(x1>correctionWordArray[i].x1)continue;
					if(y1>correctionWordArray[i].y1)continue;
					testStr.wordArray[index].name=correctionWordArray[i].name;
					//cout<<"### record found ### new name="<<correctionWordArray[i].name<<END;
			
			flag=1;
			testStr.wordArray[index].checkFlag=1;
			break;
		}
		

		*/ 
		
	//}
    //cout<<"correctionWordArray.size()="	<<correctionWordArray.size()<<END;
 
	return;
	
	//exit(0);

}///_________________________________________________________________________


