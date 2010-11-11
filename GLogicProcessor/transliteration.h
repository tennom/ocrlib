string translitWylieToYagpo(commandData *inputData,string &srcLine){
	
	string fileName;
	int i,j;

	static map<wstring,uniRecord>uniTibTableUni;
	static map<wstring,uniRecord>uniTibTableYagpo;
	static map<wstring,wstring>ASCItoUni;
	static map<string, uniRecord>uniTibTableWylie;
	static vector<string>tibStr;
	vector<string>wylieStr;
	vector<string>wylieStrVect;
	vector<string>yagpoStrVect;

	if(!ASCItoUni.size())LoadUniToTibetanMapUni(inputData,ASCItoUni,uniTibTableUni,uniTibTableYagpo,uniTibTableWylie);
	//cout<<"ASCItoUni size="<<uniTibTableYagpo.size()<<endl;
	//cout<<"srcLine="<<srcLine<<endl;

	wstring destStr;
	string destLine;
	wstring srcLineUni;
	wstring match;
	string needConvertToWylie="";
	string result;

	srcLine=str_replace("\r","",srcLine);
	srcLineUni=UTF_to_Unicode(srcLine);
	destStr=L"";


	for(i=0;i<srcLineUni.size();i++){
		match=srcLineUni[i];
		destStr+=ASCItoUni[match];
		cout<<(short)srcLineUni[i]<<" "<<destStr[destStr.size()-1]<<endl;

	}
	result=tibetanUTFToYagpo(destStr, uniTibTableYagpo);
	//cout<<"destStr="<<Unicode_to_UTF(destStr)<<"result="<<result<<endl;

	return result;

}//_______________________________________________________________________________________

void AcipToYagpo(commandData *inputData){
  /*
	string fileName;
	int i,j;

	static map<wstring,uniRecord>uniTibTableUni;
	static map<wstring,uniRecord>uniTibTableYagpo;
	static map<wstring,wstring>ASCItoUni;
	static map<string, uniRecord>uniTibTableWylie;
	static vector<string>tibStr;
	vector<string>wylieStr;
	vector<string>wylieStrVect;
	vector<string>yagpoStrVect;
	string tablePath=configPath+"/TibUniDLL/";

	if(!ASCItoUni.size())LoadUniToTibetanMapUni(tablePath,ASCItoUni,uniTibTableUni,uniTibTableYagpo,uniTibTableWylie);
	//cout<<"ASCItoUni size="<<uniTibTableYagpo.size()<<endl;
	//cout<<"srcLine="<<srcLine<<endl;

	wstring destStr;
	string destLine;
	wstring srcLineUni;
	wstring match;
	string needConvertToWylie="";
	string result;

	srcLine=str_replace("\r","",srcLine);
	srcLineUni=UTF_to_Unicode(srcLine);
	destStr=L"";


	for(i=0;i<srcLineUni.size();i++){
		match=srcLineUni[i];
		destStr+=ASCItoUni[match];
		cout<<(short)srcLineUni[i]<<" "<<destStr[destStr.size()-1]<<endl;

	}
	result=tibetanUTFToYagpo(destStr, uniTibTableYagpo);
	//cout<<"destStr="<<Unicode_to_UTF(destStr)<<"result="<<result<<endl;

	return result;
   */
}//_______________________________________________________________________________________




void WylieToYagpo(commandData *inputData){

	string tablePath=inputData->data["tablePath"];

	ifstream sourceFile(inputData->data["inputFile"].c_str());
	if( !sourceFile ){
		cout<<"Source path "<<inputData->data["inputFile"]<<" not exist"<<endl;
		exit(10);
	}
	ofstream c_out; ofstream c_out_html;
	c_out.open(inputData->data["outFile"].c_str());
	if( !c_out ){
		cout<<"destination path "<<inputData->data["outFile"]<<" not exist"<<endl;
		exit(10);
	}

	vector<string>srcVect;
	string srcLine;

	while (getline(sourceFile, srcLine,'\n')){
		srcVect.push_back(srcLine);
	}
	//cout<<"stcVect.size="<<stcVect.size()<<endl;
	//if(srcVect.size()>150){
	//	string st=argVector[3].c_str();
	//	st+=".html";
	//	c_out_html.open(st.c_str());
	//	if( !c_out ){
	//		cout<<"destination path "<<st<<" not exist"<<endl;
	//		exit(10);
	//	}
	//	c_out_html<<"<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body>"
	//	<<"<font face=\"Yagpo\">"<<endl;
	//
	//}


	map<wstring,uniRecord>uniTibTableUni;
	map<wstring,uniRecord>uniTibTableYagpo;
	map<wstring,wstring>ASCItoUni;
	map<string, uniRecord>uniTibTableWylie;
	vector<string>tibStr;
	vector<string>wylieStr;
	vector<string>wylieStrVect;
	vector<string>yagpoStrVect;

	LoadUniToTibetanMapUni(inputData,ASCItoUni,uniTibTableUni,uniTibTableYagpo,uniTibTableWylie);
	//cout<<"UniTibetanBigMap size="<<uniTibTableYagpo.size()<<endl;

	wstring destStr;
	string destLine;
	wstring srcLineUni;
	wstring match;
	string needConvertToWylie="";
	//string::size_type pos = 0;
	string result;
	//wcout<<srcVect[0].c_str()<<L" delimeter="<<delimeter.c_str()<<endl;


	for(int j=0;j<srcVect.size();j++){
		//cout<<"j="<<j<<endl;

		srcVect[j]=str_replace("\r","",srcVect[j]);
		srcLineUni=UTF_to_Unicode(srcVect[j]);
		//wcout<<L"SRC"<<srcLine.c_str()<<endl;
		destStr=L"";

		for(int i=0;i<srcLineUni.size();i++){
			match=srcLineUni[i];
			destStr+=ASCItoUni[match];
		}

		//cout<<"destStr="<<Unicode_to_UTF(destStr)<<endl;
		result=tibetanUTFToYagpo(destStr, uniTibTableYagpo);

		//cout<<"DEST____"<<result<<endl;
		c_out<<result<<endl;
		//if(srcVect.size()>150)c_out_html<<result<<"<br>"<<endl;
		//cout<<"DEST"<<srcVect[j]<<endl;

	}

	//if(needConvertToWylie!="")c_out<<"need Convert To Wylie \n"<<needConvertToWylie;


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

	LoadUniToTibetanMapUTF(inputData,ASCIToUni,uniTibTable,uniTibTableYagpo);
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


void YagpoToWylie(commandData *inputData){

	string fileName;
	int i,j;

	ifstream sourceFile(inputData->data["inputFile"].c_str());
	if( !sourceFile ){
		cout<<"Source path "<<inputData->data["file_Path"]<<" not exist"<<endl;
		exit(10);
	}
	ofstream c_out;  c_out.open(inputData->data["outFile"].c_str());
	if( !c_out ){
		cout<<"destination path "<<inputData->data["outFile"]<<" not exist"<<endl;
		exit(10);
	}


	vector<string>srcVect;
	string srcLine;

	while (getline(sourceFile, srcLine,'\n')){
		srcVect.push_back(srcLine);
	}
	//cout<<"stcVect.size="<<stcVect.size()<<endl;

	//ifstream YagpoToWylieMap(configPath.c_str());
	//if( !YagpoToWylieMap ){cout<<"YagpoToWylieMap not exist"<<endl;	exit(10);}

	map<string,uniRecord>convertMap;
	vector<string>tibStr;
	vector<string>wylieStr;
	vector<string>wylieStrVect;
	vector<string>yagpoStrVect;

	LoadYagpoToWylieMap(inputData,convertMap);
	//cout<<"tibStr size="<<convertMap.size()<<endl;
	string destStr;
	string destLine;
	string delimeter;
	string needConvertToWylie="";
	//string::size_type pos = 0;

	//wcout<<srcVect[0].c_str()<<L" delimeter="<<delimeter.c_str()<<endl;


	for(j=0;j<srcVect.size();j++){
		//cout<<"j="<<j<<endl;
		srcVect[j]=str_replace("\r","",srcVect[j]);

		srcLine=srcVect[j]; destLine="";
		srcLine=str_replace("་"," ",srcLine);
		srcLine=str_replace("།"," ",srcLine);
		srcLine=str_replace("༽"," ",srcLine);
		srcLine=str_replace("༼"," ",srcLine);
		srcLine=str_replace("༏"," ",srcLine);
		srcLine=str_replace("༴"," ",srcLine);
		srcLine=str_replace("༄"," ",srcLine);
		srcLine=str_replace("༅"," ",srcLine);
		srcLine=str_replace("༈"," ",srcLine);
		srcLine=str_replace("༿"," ",srcLine);
		srcLine=str_replace("༾"," ",srcLine);
		srcLine=str_replace("༔"," ",srcLine);
		srcLine=str_replace("ཿ"," ",srcLine);
		srcLine=str_replace("["," ",srcLine);
		srcLine=str_replace("]"," ",srcLine);
		srcLine=str_replace("{"," ",srcLine);
		srcLine=str_replace(")"," ",srcLine);
		srcLine=str_replace("("," ",srcLine);
		srcLine=str_replace(")"," ",srcLine);
		srcLine=str_replace("<"," ",srcLine);
		srcLine=str_replace(">"," ",srcLine);
		srcLine=str_replace("."," ",srcLine);
		srcLine=str_replace(","," ",srcLine);
		srcLine=str_replace(";"," ",srcLine);
		srcLine=str_replace(":"," ",srcLine);
		srcLine=str_replace("#"," ",srcLine);
		srcLine=str_replace("|"," ",srcLine);

		//wcout<<L"SRC"<<srcLine.c_str()<<endl;

		yagpoStrVect=explode(srcLine," ");

		i=0;
		for(i=0;i<yagpoStrVect.size();i++){

			if((int)yagpoStrVect[i][0]==-32||(int)yagpoStrVect[i][0]==-18){ //tibetan unicode range
				destStr=convertMap[yagpoStrVect[i]].Wylie;
				//wcout<<i<<L"= "<<yagpoStrVect[i].c_str()<<L" destString="<<destStr.c_str()<<endl;
				if(destStr!=""){
					srcVect[j]=str_replace(yagpoStrVect[i],destStr,srcVect[j],1);
				}else{
					needConvertToWylie+=yagpoStrVect[i];
					needConvertToWylie+="|\n";
				}
			}
			//cout<<"DEST____"<<srcVect[j]<<endl;
		}
		srcVect[j]=str_replace("་"," ", srcVect[j]);
		srcVect[j]=str_replace("།","/", srcVect[j]);
		srcVect[j]=str_replace("༽", "}", srcVect[j]);
		srcVect[j]=str_replace("༼", "{", srcVect[j]);
		srcVect[j]=str_replace("༏", "|", srcVect[j]);
		srcVect[j]=str_replace("༴", "=", srcVect[j]);
		srcVect[j]=str_replace("༄", "@", srcVect[j]);
		srcVect[j]=str_replace("༅", "#", srcVect[j]);
		srcVect[j]=str_replace("༈", "!", srcVect[j]);
		srcVect[j]=str_replace("༿", "(", srcVect[j]);
		srcVect[j]=str_replace("༾", ")", srcVect[j]);
		srcVect[j]=str_replace("༔", ";", srcVect[j]);
		srcVect[j]=str_replace("ཿ", "H", srcVect[j]);



		c_out<<srcVect[j]<<endl;
		//cout<<"DEST"<<srcVect[j]<<endl;

	}

	if(needConvertToWylie!="")c_out<<"need Convert To Wylie \n"<<needConvertToWylie;

}//_______________________________________________________________________________________

void buildDict(commandData *inputData){

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
	string srcLine;

	while (getline(sourceFile, srcLine,'\n')){
		srcVect.push_back(srcLine);
	}
	//cout<<"stcVect.size="<<stcVect.size()<<endl;

	//ifstream YagpoToWylieMap(configPath.c_str());
	//if( !YagpoToWylieMap ){cout<<"YagpoToWylieMap not exist"<<endl;	exit(10);}

	map<string,uniRecord>convertMap;
	vector<string>tibStr;
	vector<string>wylieStr;
	vector<string>wylieStrVect;
	vector<string>yagpoStrVect;

	LoadYagpoToWylieMap(inputData,convertMap);
	//cout<<"tibStr size="<<convertMap.size()<<endl;
	string destStr;
	string destLine;
	string delimeter;
	string needConvertToWylie="";
	//string::size_type pos = 0;

	//wcout<<srcVect[0].c_str()<<L" delimeter="<<delimeter.c_str()<<endl;

	int  n;
	for(j=0;j<srcVect.size();j++){
		//cout<<"j="<<j<<endl;
		srcVect[j]=str_replace("\r","",srcVect[j]);
		n=1
		; srcLine="";
		while(srcVect[j][n]!='}'&&n<srcVect[j].size()){
			srcLine.push_back(srcVect[j][n]); n++;
		}
		destLine="";

		srcLine=str_replace("་"," ",srcLine);
		srcLine=str_replace("།"," ",srcLine);

		//wcout<<L"SRC"<<srcLine.c_str()<<endl;

		yagpoStrVect=explode(srcLine," ");

		i=0;
		for(i=0;i<yagpoStrVect.size();i++){

			if((int)yagpoStrVect[i][0]==-32||(int)yagpoStrVect[i][0]==-18){ //tibetan unicode range
				destStr=convertMap[yagpoStrVect[i]].Wylie;
				//wcout<<i<<L"= "<<yagpoStrVect[i].c_str()<<L" destString="<<destStr.c_str()<<endl;
				if(destStr!=""){
					srcLine=str_replace(yagpoStrVect[i],destStr,srcLine,1);
				}else{
					needConvertToWylie+=yagpoStrVect[i];
					needConvertToWylie+="|\n";
				}
			}
			//cout<<"DEST____"<<srcVect[j]<<endl;
		}

		srcLine[n-1]='<';
		n+=1;
		while(n<srcVect[j].size()){
			srcLine.push_back(srcVect[j][n]); n++;
		}

		c_out<<srcLine<<endl;
		//cout<<"DEST"<<srcLine<<endl;

	}

	if(needConvertToWylie!="")c_out<<"need Convert To Wylie \n"<<needConvertToWylie;

}//_______________________________________________________________________________________


void TranslitYagpo(commandData *inputData){

	string fileName;
	int i,j;

	ifstream sourceFile(inputData->data["fileName"].c_str());
	if( !sourceFile ){
		cout<<"Source path "<<inputData->data["fileName"]<<" not exist"<<endl;
		exit(10);
	}
	ofstream c_out;  c_out.open(inputData->data["outFile"].c_str());
	if( !c_out ){
		cout<<"destination path "<<inputData->data["outFile"]<<" not exist"<<endl;
		exit(10);
	}


	vector<string>srcVect;
	string srcLine;

	while (getline(sourceFile, srcLine,'\n')){
		srcVect.push_back(srcLine);
	}
	//cout<<"stcVect.size="<<stcVect.size()<<endl;

	//ifstream YagpoToWylieMap(configPath.c_str());
	//if( !YagpoToWylieMap ){cout<<"YagpoToWylieMap not exist"<<endl;	exit(10);}

	map<string,uniRecord>convertMap;
	vector<string>tibStr;
	vector<string>wylieStr;
	vector<string>wylieStrVect;
	vector<string>yagpoStrVect;

	LoadYagpoToWylieMap(inputData,convertMap);
	//cout<<"tibStr size="<<convertMap.size()<<endl;
	string destStr;
	string destLine;
	string delimeter;
	string needConvertToWylie="";
	//string::size_type pos = 0;
	string src;
	//wcout<<srcVect[0].c_str()<<L" delimeter="<<delimeter.c_str()<<endl;


	for(j=0;j<srcVect.size();j++){
		//cout<<"j="<<j<<endl;

		srcVect[j]=str_replace("\r","",srcVect[j]);
		src=srcVect[j];
		srcLine=srcVect[j]; destLine="";
		srcLine=str_replace("་"," ",srcLine);
		srcLine=str_replace("།"," ",srcLine);
		srcLine=str_replace("༽"," ",srcLine);
		srcLine=str_replace("༼"," ",srcLine);
		srcLine=str_replace("༏"," ",srcLine);
		srcLine=str_replace("༴"," ",srcLine);
		srcLine=str_replace("༄"," ",srcLine);
		srcLine=str_replace("༅"," ",srcLine);
		srcLine=str_replace("༈"," ",srcLine);
		srcLine=str_replace("༿"," ",srcLine);
		srcLine=str_replace("༾"," ",srcLine);
		srcLine=str_replace("༔"," ",srcLine);
		srcLine=str_replace("ཿ"," ",srcLine);
		srcLine=str_replace("["," ",srcLine);
		srcLine=str_replace("]"," ",srcLine);
		srcLine=str_replace("{"," ",srcLine);
		srcLine=str_replace(")"," ",srcLine);
		srcLine=str_replace("("," ",srcLine);
		srcLine=str_replace(")"," ",srcLine);
		srcLine=str_replace("<"," ",srcLine);
		srcLine=str_replace(">"," ",srcLine);
		srcLine=str_replace("."," ",srcLine);
		srcLine=str_replace(","," ",srcLine);
		srcLine=str_replace(";"," ",srcLine);
		srcLine=str_replace(":"," ",srcLine);
		srcLine=str_replace("#"," ",srcLine);
		srcLine=str_replace("|"," ",srcLine);

		//wcout<<L"SRC"<<srcLine.c_str()<<endl;

		yagpoStrVect=explode(srcLine," ");

		i=0;

		for(i=0;i<yagpoStrVect.size();i++){

			if((int)yagpoStrVect[i][0]==-32||(int)yagpoStrVect[i][0]==-18){ //tibetan unicode range
				destStr=convertMap[yagpoStrVect[i]].translit;
				//wcout<<i<<L"= "<<yagpoStrVect[i].c_str()<<L" destString="<<destStr.c_str()<<endl;
				if(destStr!=""){
					srcVect[j]=str_replace(yagpoStrVect[i],destStr,srcVect[j],1);
				}else{
					needConvertToWylie+=yagpoStrVect[i];
					needConvertToWylie+="|\n";
				}
			}
			//cout<<"DEST____"<<srcVect[j]<<endl;
		}

		srcVect[j]=str_replace("་"," ", srcVect[j]);
		c_out<<src<<"["<<srcVect[j]<<"]"<<endl;
		//cout<<"DEST"<<srcVect[j]<<endl;

	}

	if(needConvertToWylie!="")c_out<<"need Convert To Wylie \n"<<needConvertToWylie;

}//_______________________________________________________________________________________








void UnicodeToYagpo(commandData *inputData){

	int j;

	ifstream sourceFile(inputData->data["inputFile"].c_str());
	if( !sourceFile ){
		cout<<"Source path "<<inputData->data["inputFile"]<<" not exist"<<endl;
		exit(10);
	}
	ofstream c_out; ofstream c_out_html;
	c_out.open(inputData->data["outFile"].c_str());
	if( !c_out ){
		cout<<"destination path "<<inputData->data["outFile"]<<" not exist"<<endl;
		exit(10);
	}

	vector<string>srcVect;
	string srcLine;

	while (getline(sourceFile, srcLine,'\n')){
		srcVect.push_back(srcLine);
	}
	//cout<<"stcVect.size="<<stcVect.size()<<endl;
	if(srcVect.size()>150){
		string st=inputData->data["outFile"].c_str();
		st+=".html";
		c_out_html.open(st.c_str());
		if( !c_out ){
			cout<<"destination path "<<st<<" not exist"<<endl;
			exit(10);
		}
		c_out_html<<"<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body>"
		<<"<font face=\"Yagpo\">"<<endl;

	}

	map<wstring, uniRecord>uniTibTableUni;
	map<wstring, uniRecord>uniTibTableYagpo;
	map<string, uniRecord>uniTibTableWylie;
	map<wstring,wstring>ASCItoUni;
	vector<string>tibStr;
	vector<string>wylieStr;
	vector<string>wylieStrVect;
	vector<string>yagpoStrVect;

	LoadUniToTibetanMapUni(inputData,ASCItoUni,uniTibTableUni,uniTibTableYagpo,uniTibTableWylie);
	//cout<<"UniTibetanBigMap size="<<UniTibetanBigMap.size()<<endl;

	string destStr;
	string destLine;
	wstring srcUniLine;
	string in;
	string needConvertToWylie="";
	//string::size_type pos = 0;

	//wcout<<srcVect[0].c_str()<<L" delimeter="<<delimeter.c_str()<<endl;


	for(j=0;j<srcVect.size();j++){
		//cout<<"j="<<j<<endl;

		srcVect[j]=str_replace("\r","",srcVect[j]);
		//wcout<<L"SRC"<<srcLine.c_str()<<endl;
		//destStr=srcVect[j];
		srcUniLine=UTF_to_Unicode(srcVect[j]);
		destStr=tibetanUTFToYagpo(srcUniLine, uniTibTableUni);

		//cout<<"DEST____"<<destStr<<endl;

		c_out<<destStr<<endl;
		if(srcVect.size()>150)c_out_html<<destStr<<"<br>"<<endl;

	}

	//if(needConvertToWylie!="")c_out<<"need Convert To Wylie \n"<<needConvertToWylie;


}//_______________________________________________________________________________________


void WylieToUnicode(commandData *inputData){

	int i,j;

	ifstream sourceFile(inputData->data["inputFile"].c_str());
	if( !sourceFile ){
		cout<<"Source path "<<inputData->data["inputFile"]<<" not exist"<<endl;
		exit(10);
	}
	ofstream c_out; ofstream c_out_html;
	c_out.open(inputData->data["outFile"].c_str());
	if( !c_out ){
		cout<<"destination path "<<inputData->data["outFile"]<<" not exist"<<endl;
		exit(10);
	}

	vector<string>srcVect;
	string srcLine;

	while (getline(sourceFile, srcLine,'\n')){
		srcVect.push_back(srcLine);
	}
	//cout<<"stcVect.size="<<stcVect.size()<<endl;
	if(srcVect.size()>150){
		string st=inputData->data["outFile"].c_str();
		st+=".html";
		c_out_html.open(st.c_str());
		if( !c_out ){
			cout<<"destination path "<<st<<" not exist"<<endl;
			exit(10);
		}
		c_out_html<<"<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body>"
		<<"<font face=\"Yagpo\">"<<endl;

	}

	map<string,uniRecord>uniTibTable;
	map<string,uniRecord>uniTibTableYagpo;
	map<string,string>ASCIToUni;
	vector<string>tibStr;
	vector<string>wylieStr;
	vector<string>wylieStrVect;
	vector<string>yagpoStrVect;

	LoadUniToTibetanMapUTF(inputData,ASCIToUni,uniTibTable,uniTibTableYagpo);
	//cout<<"UniTibetanBigMap size="<<UniTibetanBigMap.size()<<endl;

	string destStr;
	string destLine;
	string in;
	string needConvertToWylie="";
	//string::size_type pos = 0;

	//wcout<<srcVect[0].c_str()<<L" delimeter="<<delimeter.c_str()<<endl;

	for(j=0;j<srcVect.size();j++){
		//cout<<"j="<<j<<endl;

		srcVect[j]=str_replace("\r","",srcVect[j]);
		//wcout<<L"SRC"<<srcLine.c_str()<<endl;
		destStr="";

		for(i=0;i<srcVect[j].size();i++){
			in=srcVect[j][i];
			destStr+=ASCIToUni[in];
		}
		destStr=YagpoToUni(destStr, uniTibTable);

		//cout<<"DEST____"<<srcVect[j]<<endl;
		c_out<<destStr<<endl;
		if(srcVect.size()>150)c_out_html<<destStr<<"<br>"<<endl;
		//cout<<"DEST"<<srcVect[j]<<endl;

	}

	//if(needConvertToWylie!="")c_out<<"need Convert To Wylie \n"<<needConvertToWylie;


}//_______________________________________________________________________________________

void extractCodePages(commandData *inputData){

	ifstream sourceFile(inputData->data["inputFile"].c_str());
	if( !sourceFile ){
		cout<<"Source path "<<inputData->data["inputFile"]<<" not exist"<<endl;
		exit(10);
	}
	ofstream c_out; ofstream c_out_html;
	c_out.open(inputData->data["outFile"].c_str());
	if( !c_out ){
		cout<<"destination path "<<inputData->data["outFile"]<<" not exist"<<endl;
		exit(10);
	}

	vector<string>srcVect;
	string srcLine;

	while (getline(sourceFile, srcLine,'\n')){
		srcVect.push_back(srcLine);
	}
	//cout<<"stcVect.size="<<stcVect.size()<<endl;
	if(srcVect.size()>150){
		string st=inputData->data["outFile"].c_str();
		st+=".html";
		c_out_html.open(st.c_str());
		if( !c_out ){
			cout<<"destination path "<<st<<" not exist"<<endl;
			exit(10);
		}
		c_out_html<<"<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body>"
		<<"<font face=\"Yagpo\">"<<endl;

	}

	map<wstring,uniRecord>uniTibTable;
	map<wstring,uniRecord>uniTibTableYagpo;
	map<wstring,wstring>ASCIToUni;
	map<string,uniRecord>uniTibTableWylie;
	vector<string>tibStr;
	vector<string>wylieStr;
	vector<string>wylieStrVect;
	vector<string>yagpoStrVect;

	LoadUniToTibetanMapUni(inputData,ASCIToUni,uniTibTable,uniTibTableYagpo,uniTibTableWylie);
	//cout<<"UniTibetanBigMap size="<<UniTibetanBigMap.size()<<endl;

	string destStr;
	string destLine;
	string in;
	string needConvertToWylie="";
	//string::size_type pos = 0;

	//Extract Unicode script from afm file
	unsigned int i;
	short StartPos,EndPos,value;
	string glyphName;
	string str;

	string match=" ; N ",result,tmp;
	string match1=" ; ";
	string match2=" ; B ";
	map<string, uniRecord>::const_iterator it;

	for(i=0;i<srcVect.size();i++){
		//cout<<"j="<<j<<endl;
		str= srcVect[i];
		//cout<<"str="<<str<<endl;

		if(str.find(match)<str.size()){
			//cout<<"str.find_first_of(match1)="<<str.find(match1)<<endl;

			tmp=str.substr(2,str.find(match1)-2);
			//cout<<"tmp="<<tmp<<endl;

			value=atoi(tmp.c_str());
			result="0x";
			result+=intToHex(value);
			result+="|";
			cout<<"res="<<result<<endl;

			StartPos=str.find(match)+5;
			EndPos=str.find(match2);

			tmp=str.substr(StartPos,EndPos-StartPos);
			cout<<"tmp="<<tmp<<endl;

			glyphName=tmp;
			for(int a=0;a<2;a++){
				if(glyphName[glyphName.size()-1]=='0'||glyphName[glyphName.size()-1]=='1'||
				   glyphName[glyphName.size()-1]=='2'||glyphName[glyphName.size()-1]=='3'||
				   glyphName[glyphName.size()-1]=='4'||glyphName[glyphName.size()-1]=='5'||
				   glyphName[glyphName.size()-1]=='6'||glyphName[glyphName.size()-1]=='7'||
				   glyphName[glyphName.size()-1]=='8'||glyphName[glyphName.size()-1]=='9'){
					glyphName.erase(glyphName.size()-1,1);
				}
			}


			result+=tmp+"|";

			it = uniTibTableWylie.find(glyphName);
			if (it != uniTibTableWylie.end()) {
				cout<<"match found";
				result+=implode(";",uniTibTableWylie[glyphName].uniHexCode);
				result+="|";
				result+=implode(";",uniTibTableWylie[glyphName].uniHexTibetan);

			}
			c_out<<result<<endl;
			cout<<result<<endl;

		}
	}


	/*
	 for(j=0;j<srcVect.size();j++){
	 //cout<<"j="<<j<<endl;

	 srcVect[j]=str_replace("\r","",srcVect[j]);
	 //wcout<<L"SRC"<<srcLine.c_str()<<endl;
	 destStr="";

	 for(i=0;i<srcVect[j].size();i++){
	 in=srcVect[j][i];
	 destStr+=ASCIToUni[in];
	 }
	 destStr=YagpoToUni(destStr, uniTibTable);

	 //cout<<"DEST____"<<srcVect[j]<<endl;
	 c_out<<destStr<<endl;
	 if(srcVect.size()>150)c_out_html<<destStr<<"<br>"<<endl;
	 //cout<<"DEST"<<srcVect[j]<<endl;

	 }

	 */


	//if(needConvertToWylie!="")c_out<<"need Convert To Wylie \n"<<needConvertToWylie;


}//_______________________________________________________________________________________

void TibetanNameSpace(commandData *inputData){

	//int i,j;
	/*
	 ifstream sourceFile(argVector[2].c_str());
	 if( !sourceFile ){
	 cout<<"Source path "<<argVector[2]<<" not exist"<<endl;
	 exit(10);
	 }
	 ofstream c_out; ofstream c_out_html;
	 c_out.open(argVector[3].c_str());
	 if( !c_out ){
	 cout<<"destination path "<<argVector[3]<<" not exist"<<endl;
	 exit(10);
	 }

	 vector<string>srcVect;
	 string srcLine;

	 while (getline(sourceFile, srcLine,'\n')){
	 srcVect.push_back(srcLine);
	 }
	 //cout<<"stcVect.size="<<stcVect.size()<<endl;
	 if(srcVect.size()>150){
	 string st=argVector[3].c_str();
	 st+=".html";
	 c_out_html.open(st.c_str());
	 if( !c_out ){
	 cout<<"destination path "<<st<<" not exist"<<endl;
	 exit(10);
	 }
	 c_out_html<<"<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body>"
	 <<"<font face=\"Yagpo\">"<<endl;

	 }

	 */
	/*
	string destStr;
	string destLine;
	wstring srcUniLine;

	//BuildStandartTibetanUniTable(fileName);


	//wcout<<srcVect[0].c_str()<<L" delimeter="<<delimeter.c_str()<<endl;


	 for(j=0;j<srcVect.size();j++){
	 //cout<<"j="<<j<<endl;

	 srcVect[j]=str_replace("\r","",srcVect[j]);
	 //wcout<<L"SRC"<<srcLine.c_str()<<endl;
	 //destStr=srcVect[j];
	 srcUniLine=UTF_to_Unicode(srcVect[j]);
	 destStr=tibetanUTFToYagpo(srcUniLine, uniTibTableUni);

	 //cout<<"DEST____"<<destStr<<endl;

	 c_out<<destStr<<endl;
	 if(srcVect.size()>150)c_out_html<<destStr<<"<br>"<<endl;

	 }

	 //if(needConvertToWylie!="")c_out<<"need Convert To Wylie \n"<<needConvertToWylie;
	 */

}//_______________________________________________________________________________________


