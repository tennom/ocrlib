string GLogicProcessor::startDictionary(commandData *inputData){

	string fileName;
	string srcLine, report,srcString;
	int fullReport=0;
	string inputLine;
	struct stat attrib;			// create a file attribute structure
	int time=0,time1=0;
	int step=0,i,j;

	int index=0;
	DIR *dir;
	int fileFlag;
	
	while(index<inputData->fileList.size()){
		if( ( dir=opendir(inputData->fileList[index].c_str()))!=NULL){
			if(inputData->data["ocrData"]=="RTFToYagpo"){
			    fileFlag=readDirectoryToArray(inputData->fileList, inputData->fileList[index],"rtf");
			}else{
			    fileFlag=readDirectoryToArray(inputData->fileList, inputData->fileList[index],"txt");
			}
			inputData->fileList.erase(inputData->fileList.begin()+index);
			continue;
		}
		index++;
	}
	
	
	
	/*
	LoadUniToTibetanMapUni(inputData,ASCItoUni,uniTibTableUni,uniTibTableYagpo,uniTibTableWylie);
	 exit(0);
	 */
	//cout<<srcVect[0].c_str()<<endl;
	//exit(0);
	inputData->data["dictionary"]="1";
	string dictPath="";
	if(inputData->data["dictionary"]!="1")readDictionary(inputData);

	if(inputData->data["ocrData"]=="joinDict"){
		if(!inputData->fileList.size()){
			readDirectoryToArray(inputData->fileList,inputData->data["inputFolder"],"txt");
		}
		cout<<"fileList.size()="<<inputData->fileList.size();
		strVector.resize(0); 
		mainDict.clear();
		
		for(int i=0;i<inputData->fileList.size();i++){
			inputData->data["inputFile"]=inputData->fileList[i];
			cout<<"join "<<i<<" from "<<inputData->fileList.size()<<" "<<inputData->fileList[i]<<END;
			//strVector.resize(0);
			//readText(strVector,inputData->data["inputFile"]);			
			loadDictLevelFile(inputData);
			
			/*cout<<"strVector.size()="<<strVector.size()<<END;
			 int index=0,step=0; 
			 for(int i = 0; i<strVector.size(); i++) {
			 strVector[i]=str_replace("\r", "", strVector[i]);
			 vector <string> stringItemVector;
			 stringItemVector=explode(":|:", strVector[i]);
			 if(stringItemVector.size()<2)continue;
			 
			 //cout<<"stringItemVector[1]="<<stringItemVector[1]<<" wordCount="<<
			 //mainDict[stringItemVector[1]].wordCount<<" strVector[0]="<<atoi(stringItemVector[0].c_str())<<END;
			 
			 mainDict[stringItemVector[1]].wordCount+=atoi(stringItemVector[0].c_str());
			 if(step==100000){
			 cout<<index<<" mainDict.size()="<<mainDict.size()<<END;
			 step=0;
			 }step++;index++;
			 }	
			 */	
			
		}
		inputData->data["inputFile"]=inputData->data["inputFolder"];
		cout<<"start save dictionary"<<endl;
		writeDictionaryTXT(inputData, mainDict);
		
	}
	if(inputData->data["ocrData"]=="buildDict"){
		if(!inputData->fileList.size()){
			readDirectoryToArray(inputData->fileList,inputData->data["inputFolder"],"txt");
		}
		cout<<"fileList.size()="<<inputData->fileList.size();
		
		for(int i=0;i<inputData->fileList.size();i++){
			inputData->data["inputFile"]=inputData->fileList[i];
			cout<<"convert "<<i<<" from "<<inputData->fileList.size()<<" "<<inputData->fileList[i]<<END;
			strVector.resize(0); 
			mainDict.clear();
			readText(strVector,inputData->data["inputFile"]);
			int step=0;
			cout<<"strVector.size()="<<strVector.size()<<END;
			buildDictionary(inputData,strVector);
		}
		
	}
	if(inputData->data["ocrData"]=="buildDictFromText"){
		if(!inputData->fileList.size()){
			readDirectoryToArray(inputData->fileList,inputData->data["inputFolder"],"txt");
		}
		cout<<"buildDictFromText  fileList.size()="<<inputData->fileList.size()<<END;
		
		for(int i=0;i<inputData->fileList.size();i++){
			inputData->data["inputFile"]=inputData->fileList[i];
			cout<<"convert "<<i<<" from "<<inputData->fileList.size()<<" "<<inputData->fileList[i]<<END;
			strVector.resize(0); 
			readText(strVector,inputData->data["inputFile"]);
			int step=0;
			//cout<<"strVector.size()="<<strVector.size()<<END;
			buildWordDictionary(inputData,strVector);
			//cout<<"mainDict.size()="<<mainDict.size()<<END;
		}
		cout<<"start save dictionary"<<END;
		writeDictionaryTXT(inputData, mainDict);
		
	}
	
	if(inputData->data["ocrData"]=="buildHashDict"){
		if(!inputData->fileList.size()){
			readDirectoryToArray(inputData->fileList,inputData->data["inputFolder"],"txt");
		}
		cout<<"buildDictionaryHashIndex  fileList.size()="<<inputData->fileList.size()<<END;
		
		for(int i=0;i<inputData->fileList.size();i++){
			inputData->data["inputFile"]=inputData->fileList[i];
			cout<<"convert "<<i<<" from "<<inputData->fileList.size()<<" "<<inputData->fileList[i]<<END;
			strVector.resize(0); 
			readText(strVector,inputData->data["inputFile"]);
			int step=0;
			cout<<"strVector.size()="<<strVector.size()<<END;
			buildDictionaryHashIndexUni(inputData,strVector);
			cout<<"mainDict.size()="<<mainDict.size()<<END;
		}
		cout<<"start save dictionary"<<END;
		//writeDictionaryTXT(inputData, mainDict);
	}
	
	
	
	
	if(inputData->data["ocrData"]=="spellChecker"){
		int count=0,step;
        string path,str;
		//map<int,int>hashDict;
		readGrammarDataXML(inputData->data["wordsDataPath"]);
	    inputData->c_out.open("/out.html");
		//second actual spellchecker;
	    vector <string >outArray;		
		readInputData(inputData,"txt");
		for(int i=0;i<inputData->fileList.size();i++){			
			path=inputData->fileList[i]+"_out.html";			
			strVector.resize(0); outArray.resize(0);
			inputData->data["inputFile"]=inputData->fileList[i];
			readText(strVector,inputData->data["inputFile"]);	
            str=readText("/cgi/spellChecker.html");
			cout<<"input "<<i<<" from "<<inputData->fileList.size()<<" "<<inputData->fileList[i]<<
			   " count="<<strVector.size()<<" str="<<str<<END;
			outArray.push_back(str);
			for(int j=0;j<strVector.size();j++){cout<<".";
				if(step>100){cout<<" step="<<step<<"j="<<j;step=0;}step++;
				outArray.push_back(spellCheck(inputData,strVector[j]));
			}
			cout<<"save file to path "<<path<<END;
		    //writeText(outArray, path);
		}	
		
	}
	
	
	
	if(inputData->data["ocrData"]=="TibetanUTFToEng"||
	    inputData->data["ocrData"]=="SanskritUTFToEng"){
		cout<<"inputData->data[\"InputMethod\"]="<<inputData->data["InputMethod"]<<END;
		//read source file with tibetan string punctuation mark
		//readGrammarDataXML(inputData->data["wordsDataPath"]);
        //readInputData(inputData,"txt")
		cout<<"fileList.size()="<<inputData->fileList.size();
				for(int i=0;i<inputData->fileList.size();i++){
				dictReport.resize(0); dictReportPage.resize(0);
				srcLine=inputData->fileList[i]; 
				srcLine=str_replace("\r","",srcLine);
				srcLine=str_replace("\n","",srcLine);
				cout<<" start srcLine="<<srcLine<<endl;
				
				//if(inputData->data["cmd"]=="-dt")srcLine=translitWylieToYagpo(inputData,srcLine);
				srcString=srcLine;
				//normalise tibetan string strip punctuation mark
				for(int m=1;m<delimeterTib.size();m++){
					srcLine=str_replace(delimeterTib[m].c_str()," ",srcLine);
					//cout<<"delimeter["<<m<<"]"<<delimeter[m]<<" srcLine="<<srcLine<<endl;
				}
				cout<<" srcLine="<<srcLine<<endl;
				stringItemVector=explode(" ",srcLine); //stringItemVector now contain all syllabons from string
				cout<<"start report stringItemVector.size()="<<stringItemVector.size()<<END;
				mainDictReport(inputData);
				return  writeDictReport(inputData,srcString,1,0);
				
			}
	}

	return "";
	
}//////////////////////////////////////////////////////////////////////////

