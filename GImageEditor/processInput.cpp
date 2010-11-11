//C-
//C- This software is subject to, and may be distributed under, the
//C- GNU General Public License, either Version 2 of the license,
//C- or (at your option) any later version. The license should have
//C- accompanied the software or you may obtain a copy of the license
//C- from the Free Software Foundation at http://www.fsf.org .
//C-
//C- This program is distributed in the hope that it will be useful,
//C- but WITHOUT ANY WARRANTY; without even the implied warranty of
//C- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//C- GNU General Public License for more details.
//C-
#include "php2stl.h"
#include "GImageEditor.h"
#include "GLogicProcessor.h"

///основной перекресток управления программой через интерфейс
///состояние интерфейса записанное в inputData в процессе обработки HTTP запроса браузера или из командной строки интерпретируеся, 
///вызывая создание соответсвующих объектов и выполнение методов
///inputData также содержит указатели на глобальные обьекты.
///processInput возвращает строку результирующих данных которая передается как ответ программы на запрос браузера или другого интерфейса.

string processInput(commandData *inputData, string &dataStr){
	int print=1;
	string destLine,srcLine;
	//char buffer[MAXDATASIZE];
		DT("get message1:"<<dataStr<<END);
		GImageEditor *imageEditor=(GImageEditor*)inputData->imageEditor;
		GLogicProcessor *logicProcessor=(GLogicProcessor*)inputData->logicProcessor;
	
	   vector<string>HttpHeader=explode("\n", dataStr);
	    cout<<"HttpHeader="<<HttpHeader.size();
		string request;
		if(!HttpHeader.size())return "";
		if(HttpHeader.size()==1){
			request=dataStr;
			inputData->data["m"]="dict";
		}else{
			request=substr(4,HttpHeader[0].size()-14,HttpHeader[0]);  DT("request="<<request<<endl);
		}

		string postData=substr(request.find("?")+1,request.size(),request);     DT("postData="<<postData<<endl);
		if(postData.size()){
			readPostString(inputData, postData);
		}

		inputData->data["request"]=request;

	string mode=inputData->data["m"];
	if(mode.size()<4)mode="link";      DT("mode="<<mode<<endl);
	string data=inputData->data["l"];   DT("data="<<data<<"/"<<endl);
	//request=inputData->data["request"];    DT("request="<<request<<endl);
	string fileStr=request;

	cout<<"fileStr="<<fileStr<<endl;

	DT("request[0]="<<request[0]<<endl);
	
	if(request[0]=='2'){
		DT("tib string translation mode"<<END);
		srcLine=request.substr(1, request.size());
		srcLine=logicProcessor->tibetanUTFToYagpo(srcLine,1);
		srcLine=logicProcessor->WylieToYagpoConverter(srcLine); DT("srcLine="<<srcLine<<END);
		inputData->fileList=explode("\n",srcLine);
		inputData->data["ocrData"]="TibetanUTFToEng";
		inputData->data["dictReport"]="main";
		destLine=logicProcessor->startDictionary(inputData);
		DT(" destLine="<<destLine);
	}
	if(request[0]=='3'){
		DT("tib string report mode "<<END);
		srcLine=request.substr(1, request.size());
		inputData->fileList=explode("\n",srcLine);
		inputData->data["ocrData"]="TibetanUTFToEng";
		inputData->data["dictReport"]="report";
		destLine=logicProcessor->startDictionary(inputData);
		DT(" destLine="<<destLine;)
	}
	if(request[0]=='4'){
		DT("Skt string report mode "<<END);
		srcLine=request.substr(1, request.size());
		inputData->fileList=explode("\n",srcLine);
		inputData->data["ocrData"]="SanskritUTFToEng";
		inputData->data["dictReport"]="main";
		destLine=logicProcessor->startDictionary(inputData);
		DT(" destLine="<<destLine;)
	}
	
	if(request[0]=='0'){
		if(request[1]=='1'){  //UnicodeToYagpo converter
			DT("UnicodeToYagpo "<<request<<endl);
			srcLine=request.substr(2, request.size());
			inputData->fileList=explode("\n",srcLine);
			inputData->data["ocrData"]="UnicodeToYagpo";
			inputData->data["InputMethod"]=="text";
			destLine=logicProcessor->startConvert(inputData);
			
		}
		if(request[1]=='2'){  //UnicodeToYagpo converter
			DT("YagpoToUnicode "<<destLine<<endl);
			srcLine=request.substr(2, request.size());
			inputData->fileList=explode("\n",srcLine);
			inputData->data["ocrData"]="YagpoToUnicode";
			inputData->data["InputMethod"]=="text";
			destLine=logicProcessor->startConvert(inputData);
			
		}
		if(request[1]=='3'){  //UnicodeToYagpo converter
			DT("TibUniToWylie "<<destLine<<endl);
			srcLine=request.substr(2, request.size());
			inputData->fileList=explode("\n",srcLine);
			inputData->data["ocrData"]="TibUniToWylie";
			inputData->data["InputMethod"]=="text";
			destLine=logicProcessor->startConvert(inputData);
			
		}
		if(request[1]=='4'){  //UnicodeToYagpo converter
			DT("TibUniToWylie "<<request<<endl);
			srcLine=request.substr(2, request.size());
			inputData->fileList=explode("\n",srcLine);
			inputData->data["ocrData"]="YagpoToWylie";
			inputData->data["InputMethod"]=="text";
			destLine=logicProcessor->startConvert(inputData);
			
		}
		if(request[1]=='5'){  //UnicodeToYagpo converter
			DT("WylieToYagpo "<<request<<endl);
			srcLine=request.substr(2, request.size());
			srcLine=str_replace("%", "+", srcLine);
			inputData->fileList=explode(":|:",srcLine);
			inputData->data["ocrData"]="WylieToYagpo";
			inputData->data["InputMethod"]=="text";
			destLine=logicProcessor->startConvert(inputData);
			destLine=str_replace("\n", "<br>", destLine);
			
		}
		if(request[1]=='6'){  //UnicodeToYagpo converter
			DT("dWylieToYagpo "<<destLine<<endl);
			srcLine=request.substr(2, request.size());
			inputData->fileList=explode("\n",srcLine);
			inputData->data["ocrData"]="dWylieToYagpo";
			inputData->data["InputMethod"]=="text";
			destLine=logicProcessor->startConvert(inputData);
			cout<<" destLine="<<destLine<<endl;
			
		}
		
		
		
	}
	
	if(request[0]=='1'){
		if(request[1]=='0'){  //One file OCR (letters mode)
			DT("One file OCR (letters mode)"<<END);
			srcLine=request.substr(2, request.size());
			inputData->data["ocrData"]="tibLetters";
			readInput(inputData,srcLine);
			if(!inputData->fileList.size()){
				readDirectoryToArray(inputData->fileList,inputData->data["inputFolder"],"img");
			}
			if(inputData->fileList.size()){
				string str=inputData->data["inputFile"];
				str=substr(0,str.rfind("."),str);
				str+=".html";   DT(str<<END);
				inputData->c_out.open(str.c_str());
				imageEditor->readCorrectionTable(inputData);
				imageEditor->startOCR(inputData);
				inputData->c_out.close();
			}	
		}
	}
	
	
	if(request[0]=='5'){
		/*
		DT("hash index mode"<<END);
		unsigned int hash;
		memcpy(&hash,buffer+1,4);
		DT("hash="<<hash<<END);
		int byteAdress=hash>>3;
		int adress=hash-(byteAdress<<3);   //cout<<"byteAdress="<<byteAdress<<" adress="<<dec<<adress<<endl;
		char *c=logicProcessor->hashData+byteAdress;
		//put bite on adress//*c = (1<<adress)|*c;
		//read bite from adress
		int data = (*c>>adress)&1;
		if(data){
			destLine="@|@"; DT("@@@ match"<<END);
		}else{
			destLine=":|:";
		}
		*/

	}
	
	if(request[0]=='6'){
		DT("string find mode"<<END);
	}	
	
	
	
	//if(request[0]=='0'){\
	//	DT("close pipe mode"<<END);
	//	exit(1);
	//}

	//if(mode=='1'){continue;}
	//inputData->data["ocrData"]=="TibetanUTFToEng";
	
	//if(substr(0,3,destLine)=="GET")mode=76; 
		DT("start fileStr="<<fileStr<<" mode="<<mode<<" data="<<data<<"/"<<endl);
		//data=decodeURLString(data); cout<<"data1="<<data;
		
		if(mode=="link"){
			if(data!="/"&&data!=""){
#ifdef WIN32				
			if(data[0]=='/')data=substr(1,data);
#endif				
			   destLine=readText(data);  //cout<<"destLine="<<destLine<<endl;
			}else{
//#ifdef WIN32
			   if(fileStr[0]=='/')fileStr=substr(1,fileStr);
//#endif				
			    if(fileStr=="/"||fileStr==""){
					fileStr=inputData->data["root"]+"edit/mainGUI.html";
				}else{
					fileStr=inputData->data["root"]+fileStr;				
				}	
				destLine=readText(fileStr);  //cout<<"destLine="<<destLine<<endl;
			}
			DT("link destLine.size()="<<destLine.size()<<endl);
		}	
		if(mode=="data"){
			if(data!="/"){
				destLine=readText(data);  DT("data="<<data<<" destLine="<<destLine<<endl);
			}	
			DT("destLine.size()="<<destLine.size()<<endl);
		}	
		
		if(mode=="file"){
			if(data!="1")inputData->data["inputFolder"]=data;
#ifdef MACOS
			if(inputData->data["inputFolder"]=="")inputData->data["inputFolder"]="/";
#endif
#ifdef WIN23
			if(inputData->data["inputFolder"]=="")inputData->data["inputFolder"]="C:/";
#endif
			readDirectory(inputData->fileList,inputData->folderList, inputData->data["inputFolder"]);
            return "";
			destLine=readText(fileStr);
			fileStr=implode("<br>",inputData->fileList); DT("fileStr="<<fileStr<<endl);
			
			string folderStr,upFolder; 
			
			if(inputData->folderList.size()){
				upFolder=substr(0, inputData->folderList[0].rfind("/"),inputData->folderList[0]);	
				upFolder=substr(0, upFolder.rfind("/"),upFolder);	DT("upFolder="<<upFolder<<endl);
			}else if(inputData->fileList.size()){
				upFolder=substr(0, inputData->fileList[0].rfind("/"),inputData->fileList[0]);	
				upFolder=substr(0, upFolder.rfind("/"),upFolder);	DT("upFolder="<<upFolder<<endl);
			}else{
				upFolder=substr(0, data.rfind("/"),data);	
				upFolder=substr(0, upFolder.rfind("/"),upFolder);	DT("upFolder="<<upFolder<<endl);
			}
			
			if(upFolder=="")upFolder="/";
			folderStr+="<a href=\"?m=file&l="+upFolder;
			folderStr+="\"><<..";
			folderStr+="</a><br>";
			
			for(int a=0;a<inputData->folderList.size();a++){
				folderStr+="<a href=\"?m=file&l="+inputData->folderList[a];
				folderStr+="\">"+inputData->folderList[a];
				folderStr+="</a><br>";
			}	
			folderStr+=fileStr;
			destLine=str_replace("{fieList}", folderStr, destLine);
			DT("fOpenStr="<<destLine<<endl);
		}
		if(mode=="main"){
			writeText(data,"input.xml"); //return 1;
			destLine="Start OCR";
		}
		if(mode=="char"){ 
			string path;
			if(data=="1"){
				path=inputData->data["root"]+"edit/OCRBase.html";
				destLine=readText(path);  //cout<<"destLine="<<destLine<<endl;
			}	
			if(data=="2"){
				path=inputData->data["root"]+"edit/correctionTable.html";
				destLine=readText(path);  //cout<<"destLine="<<destLine<<endl;
			}
		}
		if(mode=="base"){
			destLine=imageEditor->drawBase(inputData,data);
		}
		if(mode=="take"){
			destLine=imageEditor->drawCorrectionTable(inputData,data);
		}
		
		if(mode=="pict"){
			unsigned int in=strtoul (data.c_str(),NULL,0);
			//destLine=readText("/cgi/edit/103-0365a.jpg");  cout<<"destLine="<<destLine.size()<<endl;
			destLine=imageEditor->drawLetter(inputData,in);
		}
		if(mode=="grab"){ DT("start grab");
			unsigned int in=strtoul (data.c_str(),NULL,0);
			destLine=imageEditor->drawLetterBlock(inputData,in);
		}
		
		if(mode=="edit"){
			unsigned int in=strtoul (data.c_str(),NULL,0); //cout<<"data="<<data<<" in="<<in<<endl;
			destLine=imageEditor->drawEditLetter(inputData,in);
		}
		if(mode=="hook"){
			unsigned int in=strtoul (data.c_str(),NULL,0); //cout<<"data="<<data<<" in="<<in<<endl;
			string str="";
			destLine=imageEditor->drawEditLetterBlock(inputData,str,in);
		}
		if(mode=="look"){
			unsigned int in=strtoul (data.c_str(),NULL,0); //cout<<"data="<<data<<" in="<<in<<endl;
			destLine=imageEditor->letterBlockCorrelation(inputData,in);
		}
		if(mode=="draw"){
			destLine="<ocrData>"; destLine+="setBase"; destLine+="</ocrData>";
			destLine+="<setBase>"; destLine+=data; destLine+="</setBase>";
			writeText(destLine, "input.xml");
			unsigned int in=getID(data);
			ostringstream s;
			s<<"<script>location.href=\""<<"?m=edit&l="<<in<<"\";</script>";
			destLine=s.str();
			DT("draw destline="<<destLine<<endl);
		}
		if(mode=="plus"){
			destLine="<ocrData>"; destLine+="setLetter"; destLine+="</ocrData>";
			destLine+="<setLetter>"; destLine+=data; destLine+="</setLetter>";
			writeText(destLine, "input.xml");
			ostringstream s;
			s<<"<script>location.href=\"?m=edit&l=0\"</script>";
			destLine=s.str();
			DT("draw destline="<<destLine<<endl);
		}
		if(mode=="save"){
			destLine="<ocrData>"; destLine+="saveBase"; destLine+="</ocrData>";
			writeText(destLine, "input.xml");
			destLine="<script>alert(\"OCR Base saved\"); location.href=\"?m=main&l=<ocrData>openLetterBase</ocrData>\";</script>";
		}
		if(mode=="free"){
			writeText(data, "input.xml");
			destLine="<script>location.href=\"?m=base&l=\"</script>";
			DT("draw destline="<<destLine<<endl);
		}
		if(mode=="find"){
			DT("mode=find"<<endl);
			data=decodeURLString(data);
			destLine=imageEditor->drawBase(inputData,data);
		}
		if(mode=="test"){
			DT("mode=test"<<endl);
			data=decodeURLString(data);
			unsigned int idNumber=strtoul(data.c_str(),NULL,0);
			destLine=imageEditor->drawEditLetter(inputData,idNumber);
			destLine+=imageEditor->testLetter(inputData,idNumber);
			
			
		}
		if(mode=="code"){
			DT("mode=code"<<endl);
			destLine="<ocrData>"; destLine+="testBase"; destLine+="</ocrData>";
			writeText(destLine, "input.xml");
			destLine="Test code space in base";
		}
		if(mode=="book"){
			data=decodeURLString(data);
			DT("INPUT str="<<data<<endl);
			readInput(inputData,data);
			
			cout<<"REZULT inputData->data[ocrData]="<<inputData->data["ocrData"]<<endl;
			if(inputData->fileList.size()){
				string str=inputData->fileList[0];
				str=substr(0,str.rfind("."),str);
				str+=".html";   cout<<str<<END;
				string path=inputData->data["root"]+"edit/OCRPage.html";
				destLine=readText(path);
				destLine+="<iframe src=\"m=data&l=";
				destLine+=str;
				destLine+="\" name=\"bookPage\" id=\"bookPage\" style=\"width:100%; height:95%; background-color:#FFFFFF;\" frameborder=\"0\"></iframe>";
			}else{
				destLine="Open file for OCR";
			}
		}
		if(mode=="draw"||  ///< в этих режимах мы закрываем дочерний процесс и даем указание основной программе что нужно создать новый процесс выполнения 
		   mode=="save"||
		   mode=="free"||
		   mode=="main"||
		   mode=="test"||
		   mode=="code"||
		   mode=="plus"){
		   string str="StartOCR";	
		   writeText(str,"signal.xml");
		}
			
	return destLine;  ///<возвращаем результат выполнения. 
}//_________________________________________________________________________________________________










