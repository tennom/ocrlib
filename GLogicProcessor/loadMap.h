void GLogicProcessor::loadMapFilePali(const char *mapName){
//cout<<"Start inputData->data[\"inputFolder\"]"<<inputData->data["inputFolder"]<<END;
string str;
xml_node resultSet;
xml_document doc;
	
	str="codePages/";
	str+=mapName;
	
	if(!doc.load_file(str.c_str())){
		cout<<str<<" not loaded"<<END;
		return;
	}
	
	resultSet = doc.child("letterBase");
	// Iterate through books
	int index=0;
	
	for (xml_node row = resultSet.child("rec"); row; row = row.next_sibling("rec")){
		uniRecord letter;
		letter.letterUTF=row.attribute("n").value();
		letter.keyUTF=row.attribute("k").value();
		letter.letterUTFLowerCase=row.attribute("l").value();
		mettaPali.push_back(letter);
	}	
}//________________________________________________________________________________________________________________


void GLogicProcessor::loadTransliterationFile(const char *mapName){
	//cout<<"Start inputData->data[\"inputFolder\"]"<<inputData->data["inputFolder"]<<END;
	string str;
	xml_node resultSet;
	xml_document doc;
	
		
	str="codePages/";
	str+=mapName;
	vector<string>strVector;
	vector<string>itemVector;
	
	readText(strVector,str);
	
	for(int i=0;i<strVector.size();i++){
		strVector[i]=str_replace("\r", "", strVector[i]);
		uniRecord letter;
		itemVector=explode("|",strVector[i]);
		
		//str=YagpoToUni(itemVector[0]);
		//strVector[i]+="|";
		//strVector[i]+=str;	
		//cout<<strVector[i]<<END;
		
		if(itemVector.size()<4)continue;
 	    letter.letterUTF=itemVector[0];
		letter.Wylie=itemVector[1];
		letter.translit=itemVector[2];
		letter.keyUTF=itemVector[3];
		   
		   YagpoToWylieMap[letter.keyUTF]=letter;
	
	}
	cout<<"YagpoToWylieMap.size()="<<YagpoToWylieMap.size();
	
}//________________________________________________________________________________________________________________

