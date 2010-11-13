void  GLogicProcessor::mainDictReport(commandData *inputData){
	           int reportLevel=0;
		string srcLine, testLine,delimiter, request, answer;
		short recordFound;
		short spaceFlag=1;
		bool FullReport=false;
		OCRDictRecord record;
		string str;
	    int print=1;

		for (int entry=0; entry<stringItemVector.size();entry++){ //for every syllabon in List
			
			for (int k=stringItemVector.size();k>entry;k--){ //for every syllabon in List
				recordFound=0;
				srcLine=""; str="";
				for (int c=entry;c<k;c++){
					srcLine+=stringItemVector[c]+" ";   //all syllabons in this part of source string
					str+=stringItemVector[c]+delimeterTib[1];
				}
				testLine=srcLine;
				if(inputData->data["ocrData"]=="TibetanUTFToEng"){
					for(int m=0;m<grammarTib.size();m++){
						testLine=str_replace(grammarTib[m].c_str(),"",testLine);  //cout<<"grammarTib[m]="<<grammarTib[m]<<" testLine="<<testLine<<endl;
					}
					testLine=str_replace("  "," ",testLine);
					testLine=str_replace("  "," ",testLine);
					DT(" srcLine="<<srcLine<<" testLine=/"<<testLine<<"/"<<END);
					
					//DT("size="<<dictIndexTib.size()<<END);
					//answer=dataIP(testLine,TIB_TO_ENG_UTF);  //send data by TCP/IP socket on main dictionary program
					if(dictIndexTib.find(testLine)!=dictIndexTib.end()){
						cout<<"match @@@"<<END;
						for(int m=0;m<dictIndexTib[testLine].size();m++){ //all dictRecords for that word
							//dictRecord[dictIndex[testLine][m]].searchString=str;
							dictReport.push_back(dictRecord[dictIndexTib[testLine][m]]);
							dictReport[dictReport.size()-1].searchString=str;
							DT("found testLine "<<m<<" word index"<<dictRecord[dictIndexTib[testLine][m]].wordID<<END);
						}
					
						recordFound=1;
					}else{ DT(" not_found");}
				}
				if(inputData->data["ocrData"]=="SanskritUTFToEng"){
					//DT("size="<<dictIndexPali.size()<<END);
					DT("testLine0="<<testLine<<"/"<<END;)
					for(int m=0;m<grammarPali.size();m++){
						//cout<<m<<"="<< grammarPali[m]<<"/"<<END;
						testLine=str_replace(grammarPali[m].c_str()," ",testLine);
					}
					//testLine.resize(testLine.size()-1); //remove delimeter in Pali
					DT("testLine0="<<testLine<<"/"<<END;)
					if(dictIndexPali.find(testLine)!=dictIndexPali.end()){
						
						for(int m=0;m<dictIndexPali[testLine].size();m++){
							//dictRecord[dictIndex[testLine][m]].searchString=str;
							dictReport.push_back(dictRecord[dictIndexPali[testLine][m]]);
							dictReport[dictReport.size()-1].searchString=str;
							DT("found testLine "<<m<<" word index"<<dictRecord[dictIndexPali[testLine][m]].wordID<<END);
						}
						recordFound=1;
					}
					
				}
				
				if(recordFound&&FullReport==false){entry=k-1;
					dictReportPage.push_back(dictReport);
					dictReport.resize(0);
					DT("record found"<<k<<" e="<<entry<<END);
				break;}
				
			}//end for (int k=StringItemList->Count
		}//end for (int entry=0;
	           //write dictionary report in XML file
      
		
}//_________________________________________________________

void  GLogicProcessor::buildDictionary(commandData *inputData,vector<string> &strVector ){

	vector <string>srcVect;
	vector <string>srcVectKey;
	string srcLine,srcString,str,testLine,mainString;
	int step=0,recordFound,k;
	
	if(inputData->data["ocrData"]=="buildDict"){
		int index=0; 
		for(int i = 0; i<strVector.size(); i++) {
			strVector[i]=str_replace("\r", "", strVector[i]);
			
			vector <string> stringItemVector;
			stringItemVector=explode(" ", strVector[i]); //stringItemVector now contain all words from string
			for (int entry=0; entry<stringItemVector.size();entry++){ //for every syllabon in List
				for (int k=stringItemVector.size();k>entry;k--){ //for every syllabon in List
					recordFound=0;
					srcLine=""; str="";
					for (int c=entry;c<k;c++){
						srcLine+=stringItemVector[c]+" ";   //all syllabons in this part of source string
					}
					//cout<<" srcLine="<<srcLine<<END;
					if(mainDict.find(srcLine)!=mainDict.end()){
						mainDict[srcLine].wordCount++; break;
					} 	mainDict[srcLine].wordCount++;
					
				}//end for (int k=StringItemList->Count
			}//end for (int entry=0;
			if (step==1000){cout<<"translate line "<<index<<END;step=0; }
			step++;index++;
		
		}
		cout<<"mainDict.size()="<<mainDict.size()<<END;
			cout<<"start save dictionary"<<END;
			writeDictionaryTXT(inputData, mainDict);
	}

}//_______________________________________________________________________________

void  GLogicProcessor::buildWordDictionary(commandData *inputData,vector<string> &strVector ){
	
	vector <string>srcVect;
	vector <string>srcVectKey;
	string srcLine,srcString,str,testLine,mainString;
	int step=0,recordFound,k;

	
		int index=0; 
		for(int i = 0; i<strVector.size(); i++) {
			//strVector[i]=str_replace("\n", "", strVector[i]);
			vector <string> stringItemVector;
			stringItemVector=explode(" ", strVector[i]); //stringItemVector now contain all words from string
			//cout<<"stringItemVector.size()"<<stringItemVector.size()<<END;
			for (int entry=0; entry<stringItemVector.size();entry++){ //for every word in List
					mainDict[stringItemVector[entry] ].wordCount++; 
			}//end for (int entry=0;
			if (step==3000){cout<<"translate line "<<index<<END;step=0; }
			step++;index++;	
		}
     
	 
	
}//_______________________________________________________________________________

string GLogicProcessor::writeDictReport(commandData *inputData,string &srcStr,int reportLevel, int fullReport){
	
	int i;
	xml_document doc;
	xml_node mainNode;
	xml_node book, data;
	int wordID=0;
	char cbuf[20];
	int print=1; 
	string str, dL;
	vector<dictKey> keyArray;
	//cout<<"dictReportPage size="<<dictReportPage.size()<<END;
	DT("<br>{/"<<srcStr<<"/}={} "<<END);
	if(dictReportPage.size()==0)return "";
	DT("dictRecord size="<<dictReportPage[0].size()<<END);
	
	if(inputData->data["dictReport"]=="main"){  //main dict report
	
		for(int m=0;m<dictReportPage.size();m++) {
			DT("{"<<dictReportPage[m][0].searchString<<"}\t"<<END);
			
			for(i=0;i<dictReportPage[m].size();i++){
				//dL+="<div id=\"srcStr\">"; dL+=dictReportPage[m][0].searchString; dL+="</div>";
				for(int j=0;j<dictReportPage[m][i].reportKey.size();j++){
					dL+="<div id=\""; dL+=dictReportPage[m][i].reportKey[j].ln+"\">"; 
					dL+=dictReportPage[m][i].reportKey[j].key;
					dL+="</div>\n";
				}
				dL+="<div id=\"eentry\">"; dL+=dictReportPage[m][i].eentry+"</div>\n";
				dL+="<div id=\"rentry\">"; dL+=dictReportPage[m][i].rentry+"</div>\n";
				dL+="<div id=\"example\">"; dL+=dictReportPage[m][i].example+"</div>\n";
				dL+="<div id=\"dict\">"; dL+=dictReportPage[m][i].dict+"</div>\n";

				if(dictReportPage[m][i].dict=="ER"||
				   dictReportPage[m][i].dict=="RHD"||
				   dictReportPage[m][i].dict=="RE"||
				   dictReportPage[m][i].dict=="TD")break;
				if(dL.size()>512)break;
			}
			//sortKey(keyArray,dictReportPage[m][0].searchString,fullReport);
			//keyArray.resize(0);
			//cout<<dL;
		}
	}else{  //all dict report
		 for(int m=0;m<dictReportPage.size();m++) {
			DT("{"<<dictReportPage[m][0].searchString<<"}\t"<<END);
			
			for(i=0;i<dictReportPage[m].size();i++){
				//dL+="<div id=\"srcStr\">"; dL+=dictReportPage[m][0].searchString; dL+="</div>";
				for(int j=0;j<dictReportPage[m][i].reportKey.size();j++){
					dL+="<div id=\""; dL+=dictReportPage[m][i].reportKey[j].ln+"\">"; 
					dL+=dictReportPage[m][i].reportKey[j].key;
					dL+="</div>\n";
					
				}
				dL+="<div id=\"eentry\">"; dL+=dictReportPage[m][i].eentry+"</div>\n";
				dL+="<div id=\"rentry\">"; dL+=dictReportPage[m][i].rentry+"</div>\n";
				dL+="<div id=\"example\">"; dL+=dictReportPage[m][i].example+"</div>\n";
				dL+="<div id=\"dict\">"; dL+=dictReportPage[m][i].dict+"</div>\n";

			}
			cout<<dL;
		}
	}
		
  return dL;
	
}//_____________________________________________________________________________


