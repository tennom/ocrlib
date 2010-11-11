string GLogicProcessor::tibetanUTFToYagpo(string &uniStack,int mode){
	
	const int minUniRecord=1;
	const int maxUniRecord=27;
	int i,matchLen;
	string match, resultStr, str;
	short flag, flagExistInMap;
	//int LetterIndex=-1;
	int print=0;
	DT("mode= "<<mode<<" stack count="<<uniStack.size()<<" maxUniRecord"<<maxUniRecord<<" uniStack="<<uniStack<<"/ mainLetterTableUni.size()="<<mainLetterTableUni.size()<<END);

	
	if(uniStack.size()<minUniRecord)return uniStack;
	flagExistInMap=0;
	if(uniStack.size()<maxUniRecord){
		matchLen=uniStack.size();
	}else{
		matchLen=maxUniRecord;
	}	
	map<string, map<string,string> >::const_iterator it;
	while(matchLen>=0){  //from longest match till one letter
		DT(".1");
		if(uniStack.size()>=matchLen){  //if stack is long enouth
			match="";
			for(i=0;i<=matchLen;i++){
				match+=uniStack[i];//fill match string
			}
			DT("matchLen"<<matchLen<<" match=/"<<match<<"/ uniStack="<<uniStack<<"/"<<END);
			flag=0;
			if(mode==1){it = mainLetterTableUni.find(match);if(it != mainLetterTableUni.end())flag=1;}
			if(mode==2){it = mainLetterTableKey.find(match);if(it != mainLetterTableKey.end())flag=1;}
			DT(".2"<<"flag="<<flag);
			if (flag) {
				flag=1;
				if(mode==1)str=mainLetterTableUni[match]["Wylie"];
				if(mode==2)str=mainLetterTableKey[match]["Wylie"];
				DT("str="<<str<<endl);
				if(str=="i"){resultStr+="";flag=0;}
				if(str=="o"){resultStr+="";flag=0;}
				if(str=="e"){resultStr+="";flag=0;}
				if(str=="u"){resultStr+="";flag=0;}
				if(str=="A"){resultStr+="";flag=0;}
				if(str=="I"){resultStr+="";flag=0;}
				if(str=="E"){resultStr+="";flag=0;}
				if(str=="U"){resultStr+="";flag=0;}
				if(str=="O"){resultStr+="";flag=0;}
				if(str=="space"){resultStr+="་";flag=0;}
				
				if(flag){
					if(mode==1)resultStr+=mainLetterTableUni[match]["name"];
					if(mode==2)resultStr+=mainLetterTableKey[match]["name"];
				}
				if(mode==1)DT(" match="<<match<<"mainLetterTableUni[match].[\"name\"]="<<mainLetterTableUni[match]["name"]<<" "<<mainLetterTableUni[match]["Wylie"]<<END);
				if(mode==2)DT(" match="<<match<<"mainLetterTableKey[match].[\"name\"]="<<mainLetterTableKey[match]["name"]<<" "<<mainLetterTableKey[match]["Wylie"]<<END);
				uniStack.erase(0,matchLen+1);
				if(uniStack.size()==0){break;}
				if(uniStack.size()<=maxUniRecord){
					matchLen=uniStack.size();
				}else{
					matchLen=maxUniRecord;
				}
				
			}else{
				if(matchLen==0){
					resultStr+=match;
					DT(" one letter match=/"<<match<<"/"<<END);
					uniStack.erase(0,matchLen+1);
					if(uniStack.size()==0){break;}
					if(uniStack.size()<=maxUniRecord){
						matchLen=uniStack.size();
					}else{
						matchLen=maxUniRecord;
					}
				}	
			}
			DT(" matchLen="<<matchLen<<"/ resultStr=/"<<resultStr<<"/"<<END);
			DT(".3");
			
		}//if(uniStackIndex
		DT(".4");
		matchLen--;
    }//while(matchLen>=0)
	
	DT("resultStr=/"<<resultStr<<"/"<<END);
	return resultStr;
}//_______________________________________________________________________________________

//deprecated
string GLogicProcessor::UniToTibetan(string &uniStack, int YagpoWylieFontFlag){
	
	const int minUniRecord=1;
	const int maxUniRecord=27;
	unsigned int i,matchFlag;
	int matchLen;
	//cout<<"stack count="<<uniStack.size()<<" maxUniRecord"<<maxUniRecord<<" uniStack[0]="<<(short)uniStack[0]<<END;
	string match, resultStr, wstr;
	string str;
	string test;
	short flagExistInMap;//maxLetterSize=0;
	//int LetterIndex=-1;
	map<string, uniRecord>::const_iterator it;
	map<string, string>::const_iterator index;
	
	//for(i=0;i<uniStack.size();i++)cout<<"uniStack["<<i<<"]="<<(short)uniStack[i]<<hex<<END;
	//cout<<" test="<<uniStack<<END;
	
	
	if(uniStack.size()<minUniRecord)return uniStack;
	flagExistInMap=0;
	matchLen=maxUniRecord;
	while(matchLen>=0){  //from longest match till one letter
		//cout<<".";
		if(uniStack.size()>=matchLen){  //if stack is long enouth
			match="";
			for(i=0;i<=matchLen;i++)match+=uniStack[i];//fill match string
			
			//for(int s=0;s<match.size();s++)cout<<"match["<<s<<"]="<<hex<<match[s]<<END;
			//cout<<"matchLen1="<<matchLen<<" match="<<match.size()<<" uniStack.size="<<uniStack.size()<<" match="<<match<<END;
			matchFlag=0;
			if(YagpoWylieFontFlag){
				if (uniTibTableYagpo.find(match) != uniTibTableYagpo.end()){matchFlag=1;
					resultStr+=uniTibTableYagpo[match].letterUTF;
					//cout<<"uniTibTableYagpo[match].letterUTF="<<uniTibTableYagpo[match].letterUTF<<END;
				}
			}else{
				if (uniTibTable.find(match) != uniTibTable.end()){matchFlag=1;
					resultStr+=uniTibTable[match].letterUTF;
					//cout<<"uniTibTable[match].letterUTF="<<uniTibTable[match].letterUTF<<END;
				}				
			}
			
			
			if(matchFlag){
				//str=uniTibTable[match].Wylie[0];
				//if(str=="i"){resultStr+="";flag=0;}	//if(str=="o"){resultStr+="";flag=0;}	//if(str=="e"){resultStr+="";flag=0;}	//if(str=="u"){resultStr+="";flag=0;}
				//if(str=="A"){resultStr+="";flag=0;}	//if(str=="I"){resultStr+="";flag=0;} //if(str=="E"){resultStr+="";flag=0;}	//if(str=="U"){resultStr+="";flag=0;}
				//if(str=="O"){resultStr+="";flag=0;}
				
				//cout<<" match="<<match.c_str()<<"uniTibTable[match].letterUni="<<Unicode_to_UTF(uniTibTable[match].letterUni)<<" "<<uniTibTable[match].Wylie[0]<<END;
				uniStack.erase(0,matchLen+1);
				if(uniStack.size()==0){break;}
				if(uniStack.size()<=maxUniRecord){
					matchLen=uniStack.size();
				}else{
					matchLen=maxUniRecord;
				}
				//cout<<" uniStack.size()="<<uniStack.size()<<" uniStack="<<uniStack<<END;
			}
		}//if(uniStackIndex
		matchLen--;
	}//while(matchLen>6)
	
	string txt=resultStr;
   	if(YagpoWylieFontFlag){
		txt=str_replace("","",txt);
		txt=str_replace("ོ","",txt);
		txt=str_replace("ེ","",txt);
		txt=str_replace("ི","",txt);
		txt=str_replace("ུ","",txt);
		txt=str_replace("ཱ","",txt);
		txt=str_replace("ཱི","",txt);
		txt=str_replace("཰","",txt);
		txt=str_replace("ཱུ","",txt);
		txt=str_replace("཯","",txt);
	txt=str_replace("࿎","ༀ",txt);	}
	
	//cout<<" resultStr.size="<<resultStr.size()<<" "<<resultStr<<END;
	return txt;
}//_______________________________________________________________________________________

string GLogicProcessor::singhalaToUTF(string &uniStack){
	//cout<<"uniStack="<<uniStack<<END;
	string str=uniStack,strDest;
	map<string, string>::iterator p; 
	for(p = SinhalaASCI.begin(); p != SinhalaASCI.end(); p++) {
		strDest= p->first;
		str=str_replace(strDest,p->second, str);
	}	
	//cout<<"str="<<str<<END;
   	return str;
}//_______________________________________________________________________________________

string GLogicProcessor::YagpoToUni(string &srcStr){
	
	const int minUniRecord=1;
	const int maxUniRecord=27;
	unsigned int i,matchLen;
	//cout<<"stack count="<<uniStack.size()<<" maxUniRecord"<<maxUniRecord<<" uniStack="<<uniStack<<END;
	string match, resultStr, str;
	short flag, flagExistInMap;//maxLetterSize=0;
	string letter,result,destStr,needConvertToUni;
	wstring srcLineUni,testChar;
	
	srcLineUni=UTF_to_Unicode(srcStr);
	result="";
	for(i=0;i<srcLineUni.size();i++){
		testChar=srcLineUni[i];
		letter=Unicode_to_UTF(testChar);
		//cout<<" letter="<<letter<<" testChar="<<hex<<testChar[0]<<END;
		if(testChar==L"\r"){result+="\r"; continue;}
		//if((int)srcLine[i]==-32||(int)yagpoStrVect[i][0]==-18){ //tibetan unicode range
		destStr=mainLetterTableYagpo[letter]["tibUniUTF"];
		//cout<<"letter= "<<letter<<" destString="<<destStr<<END;
		if(destStr!=""){
			result+=destStr;
		}else{
			//cout<<" needConvertToUni "<<hex<<testChar[0]<<endl;
			result+=Unicode_to_UTF(testChar);
			needConvertToUni+=Unicode_to_UTF(testChar)+"|\n";
		}
		//}
		//cout<<"DEST____"<<srcVect[j]<<endl;
	}
	
	//cout<<result<<END;
	//cout<<"DEST"<<srcVect[j]<<endl;
	
	
	if(needConvertToUni!="")cout<<"need Convert To Uni \n"<<needConvertToUni;
	
	
	
	//cout<<"resultStr="<<resultStr<<END;
	return result;
}//_______________________________________________________________________________________


void YagpoToUnicode(commandData *inputData){
	
	string fileName;
	int i,j;
	
	ifstream sourceFile(inputData->data["inputFile"].c_str());
	if( !sourceFile ){
		cout<<"Source path "<<inputData->data["inputFile"]<<" not exist"<<endl;
		exit(10);
	}
	ofstream c_out;  c_out.open(inputData->data["outFile"].c_str());
	if( !c_out ){
		cout<<"destination path "<<inputData->data["outFile"]<<" not exist"<<endl;
		exit(10);
	}
	
	
	vector<string>srcVect;
	string destStr;
	string destLine;
	string delimeter;
	//string::size_type pos = 0;
	wstring srcLineUni, testChar;
	string srcLine, letter, needConvertToUni;
	string result;
	map<string,uniRecord>uniTibTable;
	map<string,uniRecord>uniTibTableYagpo;
	map<string,string>ASCIToUni;
	vector<string>tibStr;
	vector<string>wylieStr;
	vector<string>wylieStrVect;
	vector<string>yagpoStrVect;
	
	while (getline(sourceFile, srcLine,'\n')){
		srcLine=str_replace("\r","",srcLine);
		srcVect.push_back(srcLine);
	}
	//cout<<"stcVect.size="<<stcVect.size()<<endl;
	
	//ifstream YagpoToWylieMap(configPath.c_str());
	//if( !YagpoToWylieMap ){cout<<"YagpoToWylieMap not exist"<<endl;	exit(10);}
	
	//LoadUniToTibetanMapUTF(inputData,ASCIToUni,uniTibTable,uniTibTableYagpo);
	//cout<<"tibStr size="<<convertMap.size()<<endl;
	
	//wcout<<srcVect[0].c_str()<<L" delimeter="<<delimeter.c_str()<<endl;
	
	
	for(j=0;j<srcVect.size();j++){
		srcLineUni=UTF_to_Unicode(srcVect[j]);
		result="";
		for(i=0;i<srcLineUni.size();i++){
			testChar=srcLineUni[i];
			letter=Unicode_to_UTF(testChar);
			//cout<<" letter="<<letter<<" testChar="<<hex<<testChar[0]<<endl;
			//if((int)srcLine[i]==-32||(int)yagpoStrVect[i][0]==-18){ //tibetan unicode range
			destStr=uniTibTableYagpo[letter].keyUTF;
			//cout<<"letter= "<<letter<<" destString="<<destStr<<endl;
			if(destStr!=""){
				result+=destStr;
			}else{
				//cout<<" needConvertToUni "<<hex<<testChar[0]<<endl;
				result+="["+Unicode_to_UTF(testChar)+"]";
				needConvertToUni+=Unicode_to_UTF(testChar)+"|\n";
			}
			//}
			//cout<<"DEST____"<<srcVect[j]<<endl;
		}
		
		c_out<<result<<endl;
		//cout<<"DEST"<<srcVect[j]<<endl;
		
	}
	
	if(needConvertToUni!="")c_out<<"need Convert To Uni \n"<<needConvertToUni;
	
}//_______________________________________________________________________________________





