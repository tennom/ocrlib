void  GLogicProcessor::LoadUniToTibetanMapUTF( commandData *inputData ){
	string path=inputData->data["tablePath"];
	path+="/ASCIToUni.map";
	//cout<<"TEST"<<path<<endl;
	
	//char tmp[4094];
	///load ASCIToUni.map/////////////////////////
	
};//____________________________________________________________________________


void GLogicProcessor::LoadYagpoToWylieMap(commandData *inputData){
	string path=inputData->data["tablePath"];
	path+="/codePages/TranslitTableUni_Wylie.xml";
	//cout<<"TEST"<<path<<endl;
	
	
	//char tmp[4094];
	///load ASCIToUni.map/////////////////////////
	
	ifstream YagpoToWylieMapInput(path.c_str());
	if( !YagpoToWylieMapInput )return;
	
    // skip comment
    streamsize maxLineSize =1024;
    while( YagpoToWylieMapInput.peek() == '%'||YagpoToWylieMapInput.peek() == '#' ||YagpoToWylieMapInput.peek() == '/')
		YagpoToWylieMapInput.ignore( maxLineSize , '\n' );
	
	vector<string> srcStrings;
	string tString;
	vector<string>lineStrings;
	vector<string>value;
	//unsigned int i=0,d;
	uniRecord record;
	
	while (getline(YagpoToWylieMapInput, tString,'\n')){
		//cout<<tString.c_str()<<endl;
		tString=str_replace("\r","",tString);
		lineStrings=explode("|",tString);
		if(lineStrings.size()==4) {
			record.Wylie=lineStrings[1];
			record.translit=lineStrings[2];
			YagpoToWylieMap[lineStrings[0]]=record;
			UniToWylieMap[lineStrings[3]]=record;
			//cout<<lineStrings[0]<<" "<<lineStrings[1]<<" "<<lineStrings[3]<<endl;
		}
		//i++;
	}
	
	//cout<<"tibStr size1="<<tibStr.size()<<endl;
	cout<<"YagpoToWylieMap.size()="<<YagpoToWylieMap.size();
	
	
	return;
};//____________________________________________________________________________


void  GLogicProcessor::LoadFontNameMap(commandData* inputData){
	string path=inputData->data["tablePath"];
	path+="/codePages/FontMap/TibetanFontList.map";
	ifstream FontNameMap(path.c_str());
	if( !FontNameMap ){cout<<"path "<<path<<" not open"<<END;return;}
	
	vector<string> srcStrings;
	string tString;
	vector<string>lineStrings;
	vector<string>value;
	
	while (getline(FontNameMap, tString,'\n')){
		tString=str_replace("\r","",tString);
		fontNameMap[tString]=1;
	}
	return;
};//____________________________________________________________________________

void GLogicProcessor::LoadASCIToUniMap(commandData *inputData){
	
	xml_node col,data,resultSet,letterBaseXML, st;
	xml_document doc;
	string str;
	unsigned int dInt,in;
	unsigned long long  in64;
	
	
	string path=inputData->data["tablePath"];
	path+="/codePages/ASCIToUni.xml";
	cout<<"path="<<path<<END;
	
	readMapXML(ASCIToUni,path);
	cout<<"ASCIToUni size1="<<ASCIToUni.size()<<END;
	
	LoadFontNameMap(inputData);
	cout<<"tibFontName.size()="<<fontNameMap.size()<<END;
	
	
	path=inputData->data["tablePath"];
	path+="/codePages/UniToTibetanBig.xml";
	cout<<"path="<<path<<END;
	
	/*
	 <FIELD EMPTYOK="YES" MAXREPEAT="1" NAME="name" TYPE="TEXT"/>
	 <FIELD EMPTYOK="YES" MAXREPEAT="1" NAME="stackFlag" TYPE="TEXT"/>
	 <FIELD EMPTYOK="YES" MAXREPEAT="1" NAME="tibUniUTF" TYPE="TEXT"/>
	 <FIELD EMPTYOK="YES" MAXREPEAT="1" NAME="tibUniHex" TYPE="TEXT"/>
	 <FIELD EMPTYOK="YES" MAXREPEAT="1" NAME="uniHexKey" TYPE="TEXT"/>
	 <FIELD EMPTYOK="YES" MAXREPEAT="1" NAME="uniHexTibetan" TYPE="TEXT"/>
	 <FIELD EMPTYOK="YES" MAXREPEAT="1" NAME="Wylie" TYPE="TEXT"/>
	 <FIELD EMPTYOK="YES" MAXREPEAT="1" NAME="OCRKey" TYPE="TEXT"/>
	 <FIELD EMPTYOK="YES" MAXREPEAT="1" NAME="baseLetter" TYPE="TEXT"/>
	 <FIELD EMPTYOK="YES" MAXREPEAT="1" NAME="OCRIndex" TYPE="TEXT"/>
	 <FIELD EMPTYOK="YES" MAXREPEAT="1" NAME="translit" TYPE="TEXT"/>
	 <FIELD EMPTYOK="YES" MAXREPEAT="1" NAME="lang" TYPE="TEXT"/>
	 <FIELD EMPTYOK="YES" MAXREPEAT="1" NAME="letterName" TYPE="TEXT"/>
	 */
	
	//ShowMessage(fileName.c_str());
	
	if(!doc.load_file(path.c_str())){
		cout<<path<<" not loaded"<<END;return;
	}
	letterBaseXML = doc.child("FMPXMLRESULT");
	// DM("xmlns " << letterBaseXML.attribute("xmlns").value()<<END);
	//data = letterBaseXML.child("ERRORCODE");
	//DM("ERRORCODE" << data.child_value()<<END);
	resultSet = letterBaseXML.child("RESULTSET");
	//DM("FOUND " <<resultSet.attribute("FOUND").value()<<END);
	// Iterate through books
	for (xml_node row = resultSet.child("ROW"); row; row = row.next_sibling("ROW")){
		//DM("RECORDID " << row.attribute("RECORDID").value()<<END);
		uniRecord record;
		
		col = row.child("COL");                               //name 
		data=col.child("DATA");
		//DM("name="<<data.child_value());                    
		record.letterUTF=data.child_value();
		col = col.next_sibling("COL");                        //stackFlag
		data=col.child("DATA");                               
		//DM("tibUni="<<data.child_value());
   	    record.stackFlag=atoi(data.child_value());          
		col = col.next_sibling("COL");                        //tibUniUTF
		data=col.child("DATA");                               
		//DM("uniHexKey="<<data.child_value());
		record.utfTibKey=data.child_value();      
		col = col.next_sibling("COL");                       //tibUniHex 
		data=col.child("DATA");                               
		//DM("uniHexTibetan="<<data.child_value());
		//record.uniHexTibetan=data.child_value();
		col = col.next_sibling("COL");                       //uniHexKey  
		data=col.child("DATA");                               
		//DM("Wylie="<<data.child_value());
		//record.Wylie=data.child_value();
		col = col.next_sibling("COL");                       //uniHexTibetan
		data=col.child("DATA");                               
		//DM("OCRKey="<<data.child_value());
		//record.OCRKey=atoi(data.child_value());
		col = col.next_sibling("COL");                       //Wylie
		//      data=col.child("DATA");
		//DM("baseLetter="<<data.value());
		record.Wylie=data.child_value();
	    col = col.next_sibling("COL");                       //OCRKey   
		//      data=col.child("DATA");
		//DM("OCRIndex="<<data.child_value());		            
		col = col.next_sibling("COL");                       //baseLetter
		//      data=col.child("DATA");
		//DM("uniHexKey="<<data.child_value());
		record.baseLetter=atoi(data.child_value());
		col = col.next_sibling("COL");                       //OCRIndex
		//      data=col.child("DATA");
		//DM("stackFlag="<<data.child_value());
		record.OCRIndex=atoi(data.child_value());
		col = col.next_sibling("COL");                       //translit
		data=col.child("DATA");
		//DM("OCRKey="<<data.child_value());
		record.OCRKey=data.child_value();                    
		col = col.next_sibling("COL");                       //lang
		data=col.child("DATA");
		//DM("OCRKey="<<data.child_value());
		record.OCRIndex=atoi(data.child_value());
		col = col.next_sibling("COL");                       //letterName
		data=col.child("DATA");
		//DM("lang="<<data.child_value());
		record.lang=data.child_value();
		if(record.Wylie=="space"){ //exeption for XML parser
			record.letterUTF=" ";
			record.utfYagpoTibKey=" ";
			record.utfTibKey=" ";
		}
		uniTibTable[record.letterUTF]=record;
		uniTibTableYagpo[record.utfYagpoTibKey]=record;
		//cout<<"k="<<record.letterUTF<<" v="<<record.utfTibKey<<END;
	}
	
	//(!uniTibTable.size()){ShowMessage((AnsiString)fileName.c_str()+(AnsiString)" not loaded");return;};
	cout<<"uniTibTable.size()="<<uniTibTable.size()<<END;
	
	/*	path=inputData->data["tablePath"];
	 path+="/Tibetan0x0F00.map";
	 //cout<<"TEST"<<path<<endl;
	 
	 ///////////////////////////////////////////////////////////////////
	 path=inputData->data["tablePath"];
	 path+="/TibetanAlphabetGlyph.map";
	 */
	
	
};//____________________________________________________________________________

void GLogicProcessor::LoadMapXML(commandData *inputData){
	
	xml_node Cell,Data, letterSet,resultSet,table, metadata, field;
	xml_document doc;
	string str;
	int i;
    vector<string> nameArray; nameArray.resize(100);
	
	string path=inputData->data["tablePath"];
	path+="/codePages/ASCIToUni.xml";
	cout<<"path="<<path<<END;
	
	readMapXML(ASCIToUni,path);
	cout<<"ASCIToUni size1="<<ASCIToUni.size()<<END;
	
	LoadFontNameMap(inputData);
	cout<<"tibFontName.size()="<<fontNameMap.size()<<END;
	
	
	path=inputData->data["tablePath"];
	path+="/codePages/UniToTibetanBig.xml";
	cout<<"path="<<path<<END;
	
	if(!doc.load_file(path.c_str())){
		cout<<path<<" not loaded"<<END;return;
	}
	
	letterSet = doc.child("FMPXMLRESULT");
    metadata = letterSet.child("METADATA");
	i=0; //from first we get map key name from field name 
	for (field = metadata.child("FIELD"); field; field = field.next_sibling("FIELD")){
		nameArray[i]=field.attribute("NAME").value(); //cout<<"nameArray["<<i<<"]="<<field.attribute("NAME").value()<<END;
		i++;  			
	}//nameArray now contain database field name
	
	resultSet=letterSet.child("RESULTSET");
	for (xml_node row = resultSet.child("ROW"); row; row = row.next_sibling("ROW")){
		map<string,string>record; ///base record for all letter conversion function
		i=0;
		for (Cell = row.child("COL"); Cell; Cell = Cell.next_sibling("COL")){
			Data=Cell.child("DATA");
			record[nameArray[i]]=Data.child_value();  //cout<<"record["<<nameArray[i]<<"]="<<record[nameArray[i]]<<END;
			i++;  			
		}//nameArray now contain database field name
		
		if(record["Wylie"]=="space"){ //exeption for XML parser
			record["name"]=" ";
			record["uniHexKey"]=" ";
			record["tibUniUTF"]=" ";
		}
		mainLetterTableYagpo[record["name"]]=record;
		mainLetterTableUni[record["tibUniUTF"]]=record;
		mainLetterTableKey[record["uniKey"]]=record;
		
		//cout<<"k="<<record["name"]<<" v="<<record["tibUniUTF"]<<" u="<<record["uniKey"]<<" size="<<mainLetterTable.size()<<END;
	}
	
	cout<<"mainLetterTableYagpo.size()="<<mainLetterTableUni.size()<<END;
	
	
};//____________________________________________________________________________


void GLogicProcessor::LoadFontMap(map<string,uniRecord>&fMap,string &fileName){
	
	ifstream TibetanFontMap(fileName.c_str());
	if( !TibetanFontMap ){
		cout<<fileName<<" not found"<<END;  return;
	}
	
	vector<string> srcStrings;
	string tString;
	vector<string>lineStrings;
	short i=0;
	uniRecord record;
	vector<string> value;
	vector<string>::size_type d;
	wstring wstr;
	unsigned short data;
	        //cout<<"load map "<<fileName<<END; 
	maxUniRecord=0;
	
	while (getline(TibetanFontMap, tString,'\n')){
		srcStrings.push_back(tString);    //cout<<"vector count="<<srcStrings.size()<<endl;
		lineStrings=explode("|",tString);   //for(i=0;i<lineStrings.size();i++)c_out<<lineStrings[i]<<" ";
		wstr=L"";
		
		value=explode(";",lineStrings[0]);  //cout<<" value[0]"<< value[0]<<END;
		for(d=0;d<value.size();d++){
			istringstream conv (value[d]);
			conv >>hex>>data;
			wstr+=(wchar_t)data;
		}
		//cout<<"lineStrings="<<tString<<" wstr="<<Unicode_to_UTF(wstr)<<END;
		record.OCRKeyHex=lineStrings[0];
		record.OCRKey=Unicode_to_UTF(wstr);
		record.Wylie=lineStrings[1];  //c_ut<<uniTibTable[i].uniCode[0]<<" "<<uniTibTable[i].Wylie[0]<<endl;
		wstr=L"";
		if(lineStrings.size()>2){
			//cout<<"lineStrings.size()="<<lineStrings.size()<<" v="<<lineStrings[2]<<endl;
			data=0;
			value=explode(";",lineStrings[2]);
			for(d=0;d<value.size();d++){
				istringstream conv1 (value[d]);
				conv1 >>hex >>data;
				if(data)wstr+=(wchar_t)data;
			}
			record.keyUTF=Unicode_to_UTF(wstr);
			if(value.size()>maxUniRecord)maxUniRecord=value.size();		
			//cout<<" wstr="<<Unicode_to_UTF(wstr)<<" value.size()="<<value.size()<<END;
 		    //cout<<" str="<<record.keyUTF<<" hex="<<lineStrings[0]<<"key="<<record.OCRKey<<"//"<<END;
		}
		wstr=L"";
		if(lineStrings.size()>3){
			//cout<<"lineStrings.size()="<<lineStrings.size()<<" v="<<lineStrings[3]<<"/"<<endl;
			    value=explode(";",lineStrings[3]); //cout<<"value.size()="<<value.size();
				for(d=0;d<value.size();d++){
					istringstream conv2 (value[d]);
					conv2 >>hex >>data;
					wstr+=(wchar_t)data;
				}
				record.letterUTF=Unicode_to_UTF(wstr);		
				//cout<<" wstr="<<Unicode_to_UTF(wstr)<<END;
		}		
		
		fMap[record.OCRKey]=record;
		//cout<<"fMap[record.OCRKey]="<<fMap[record.OCRKey].keyUTF<<"//"<<END;
	}
	//cout<<"fontMap[str][letter].OCRKey"<<fontMap["Dederis-a"][" "].keyUTF<<"//"<<END;
	//cout<< "fMap.size()="<<fMap.size()<<" maxUniRecord="<<maxUniRecord<<endl;
	return;
};//____________________________________________________________________________

