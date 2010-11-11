void GBitsetOCR::textOCR(vector<stringOCR>&correctionTable,GLogicProcessor *logicProcessor, int mode){
	int baseCount;
	unsigned int letterW,letterH;
	int print=0;
	int w,h;
	int y0,y1,x0,x1,yLimit0,yLimit1,count,id_index;
	string letter;
	int wIndex,indexW;
	mainString="";
	indexW=0; id_index=0;
	vector<wordOCR>pageText;
	vector<OCRMatch>matchLine;
	
	static float bestScale=0;
	static int bestCorrelation=0;
	int needLineSize=0;
	
#define  c_out_ cout

int draw=0;
if(inputData->data["ocrData"]=="drawLetter"){
	draw=1; print=1;

c_out_<<"<span style=\"font-family:OCRUnicode;\">";
c_out_<<"inputData->ocrData="<<inputData->data["ocrData"]<<END;
}
	

DT("//_________________________print text OCR"<<END);
DT("//_________________________start correlation"<<END);
	if(strArray[0].size()==0)return;

	
	
#ifdef MAC
	struct timezone dontcare = { 0, 0 }; struct timeval before, after; float milli;  //timing of program implementation
#endif
	baseCount=0;  letterW=0; letterH=0;
		//setOCRCorrelation(0,1,ROOT_LETTER); return;
if(aliKali->letterCount<1)return;
		//if(baseCount<1||letterW<1||letterH<1)return;

		//letterWsum=(int)letterW/baseCount;
		//letterHsum=(int)letterH/baseCount;
		//proportion=(float)letterWsum/letterHsum;
		//DC(" strArray[0][0].wordArray[0].letterWsum="<<strArray[0][0].wordArray[0].letterWsum<<" letterW="<<letterW<<" baseCount"<<baseCount<<END);
		//DC(" strArray[0][0].wordArray[0].proportion="<<strArray[0][0].wordArray[0].proportion<<END);
		//return;

		//int index=1;

	//for (int index=15;index>=15; --index){  //for every string
	for (int index=strArray[0].size()-1;index>=0; --index){  //for every string
		 
		//if(index!=0)continue;
	
		//if(index==strArray[0].size()-1){print=1;}else{print=0;}
			//cout<<"ocr string "<<index<<END;
			//if(index==28){draw=1;strArray[0][index].selectFlag=3;}else{draw=0;print=0; continue;}
			if(draw){
				 if(strArray[0][index].selectFlag!=3){
				     cout<<"skip string"<<END;
				     continue;
				 }else{
				     cout<<"//_________start string "<<index<<END;print=1;
				 }
			}else{
				if(index==0){
					cout<<" "<<index<<END;
				}else{
					cout<<" "<<index;	
				    //cout<<" strArray[0][index].wordArray.size()="<<strArray[0][index].wordArray.size()<<END;			
				}		
			}
		    //###ALERT need redevelop in GBitset (horizontal frame detector)
		        if(strArray[0][index].wordArray.size()==0)pageText.resize(0);
		    //
		    
						//Create GBitsetMatrix for matrix correlation
						//SH(inputData->borderSize());
						w=inputBitmap->columns();
						h=inputBitmap->rows();
		
		                //*** ВЫЧИСЛЕНИЕ ГАБАРИТОВ ПОИСКА БУКВ В СТРОКЕ ***///
		                   yLimit0=(strArray[0][index].y1-strArray[0][index].y0)*3;	
		                   yLimit1=(strArray[0][index].y1-strArray[0][index].y0)*4; 
		                   int LimY0=yLimit0*0.6;  
		                  //normalisation
		

							DT("w="<<w<<"h="<<h<<
							   "y0="<< strArray[0][index].y0<<" y1="<< strArray[0][index].y1<<" yLimit0="<<yLimit0<<" yLimit1="<<yLimit1<<END);
		
		                   if(strArray[0][index].y0-yLimit0<0)yLimit0=strArray[0][index].y0;
						   if(strArray[0][index].y1+yLimit1>h)yLimit1=h-strArray[0][index].y1;
											
		                   DT("w="<<w<<"h="<<h<<
						   "y0="<< strArray[0][index].y0<<" y1="<< strArray[0][index].y1<<" yLimit0="<<yLimit0<<" yLimit1="<<yLimit1<<END);
		                   DT("@@Y0="<<strArray[0][index].y0-yLimit0<<endl);
		                   DT("@@H="<<strArray[0][index].y1-strArray[0][index].y0+yLimit0+yLimit1);
		                   
		                int textLineSize=strArray[0][index].y1-strArray[0][index].y0;
		                //cout<<" textLineSize0="<<textLineSize;
   	                    /*
		                for(int a=0;a<inputData->lineSize.size();a++){  //set size of text line from page layout
		                    if(textLineSize>inputData->lineSize[a]-inputData->lineSize[a]/5&&
							   textLineSize<inputData->lineSize[a]+inputData->lineSize[a]/5){
							   textLineSize=inputData->lineSize[a];break;
							}
		          
		                }
						*/ 
						cout<<" textLineSize1="<<textLineSize;
		                float scale=0;   
		                int needScaleFlag=1; //1 если нужно масштабировать строку
		               
		
		                GBitmap *line=GBitmap::createRegion(inputBitmap, 
															0, 
															strArray[0][index].y0-LimY0, 
															inputBitmap->columns(), 
															yLimit0*3
		                                                    );
		                
		                 int correlation; int stepCount=0;
		                 GBitmap *lineScale;
	   ScaleDetector:;   
	   if(needScaleFlag){
						if(needLineSize<3){
								if(textLineSize){
									scale=(float)aliKali->textLineSize/textLineSize; //стартуем поиск от размера строки 
								}else{
									scale=1;
								}	
								
							scale=lineOCRScaleDetector(line,
													   matchLine, 
													   LimY0*scale, 
													   (LimY0+textLineSize)*scale, 
													   scale,
													   index,
													   &correlation,
													   1);
							bestScale=scale;
							bestCorrelation=correlation;
							needLineSize++;
						}else{
						    scale=bestScale;
						}
							
		
		                cout<<"///@@@@ main scale="<<scale<<" stepCount="<<stepCount<<endl;
		                if(scale==0){
							continue;
							//stepCount++;
							//if(stepCount>2){needLineSize=0;continue;}
							//goto ScaleDetector;
			            }
		
	 DT("m0_1");
	   	   
		                lineScale=GBitmap::createScale(line,scale);
	}else {
		                lineScale=line;
	}
		                matchLine.resize(0);
		                matchLine.resize(inputBitmap->columns()*scale+256);
		
	DT("m0_2");
		                //GImageEditor *editor=GImageEditor::create();
		                //editor->WriteImageData(lineScale,"/__XML__/1.jpg",0); //exit(0);
	 DT("m1");
						setMatrix=GBitsetMatrix::createRegion(lineScale,
															  0,
															  0,
															  lineScale->columns(),
															  lineScale->rows(),
															  1,1,
															  IMGNOFLIP
															  );      
						lineScale->destroy();
/*						setMatrix->letterCorrelation(inputData,
													 matchLine,
													 aliKali,
													 (yLimit0-(strArray[0][index].y1-strArray[0][index].y0)/2)*scale, ///?
													 (strArray[0][index].y1-strArray[0][index].y0+yLimit0+yLimit1+(strArray[0][index].y1-strArray[0][index].y0)/4)*scale,
													 1,
													 0);
*/
		                
						setMatrix->letterCorrelation(inputData,
													 matchLine,
													 aliKali,
													 LimY0*scale, 
													 (LimY0+textLineSize)*scale,
													 0,   //no scale mode
													 0);  //no print
						//GImageEditor *editor=GImageEditor::create();
						//editor->WriteImageData(setMatrix->drawData,"/__XML__/2.jpg",0); //exit(0);
						
		
		DT("m3");
						#ifndef REPORT_DRAW
		                setMatrix->destroy();
						delete setMatrix;
                        #endif
						//now we start check result of correlation and make decision about place of every letter
	   DT("m3_1");					//разборка строки на буквы в соответствии с величиной корреляции и вложенностью букв. например О-С

						
		
		
						int ln=matchLine.size(); int maxW=0, indexMaxW;
						yLimit1=(strArray[0][index].y0-strArray[0][index].LimY0)*scale;
						for(int m=0;m<ln;m++){
							if(matchLine[m].correlation==0){
							  matchLine[m].status=1;  //исключаем пустые значения
							  continue;
							}
							if(matchLine[m].name=="་"){
							   //если тсерто не на месте мы его гасим
							   DT("/tserto/__yLimit1"<<yLimit1<<" maxY="<<matchLine[m].maxY<<" correlation="<<matchLine[m].correlation<<END);
							   if(abs((int)(LimY0*scale)-matchLine[m].maxY)>
								  aliKali[0][matchLine[m].letterIndex]->letterW*2){
								  matchLine[m].correlation=5;
								  matchLine[m].status=1;  //исключаем из рассмотрения
							   }
							}
                            
							if(matchLine[m].OCRIndex==3){
							   //если огласовка не на месте мы её гасим
							  if(abs((int)(LimY0*scale)-matchLine[m].maxY)>aliKali[0][matchLine[m].letterIndex]->letterW){
							 	  matchLine[m].correlation=5;
							 	  matchLine[m].status=1;  //исключаем из рассмотрения
							  }
							  DT("/vowel/__LimY0="<<LimY0*scale<<" maxY="<<matchLine[m].maxY<<" correlation="<<
								 matchLine[m].correlation<<" name="<<matchLine[m].name<<" letterW="<<aliKali[0][matchLine[m].letterIndex]->letterW<<END);
							  	
							}
                            
							//if(matchLine[m].Wylie=="."||matchLine[m].Wylie==","){
							//   //если точка не на месте мы её гасим
							//   DT("/point/__yLimit1="<<yLimit1<<" maxY="<<matchLine[m].maxY<<" correlation="<<matchLine[m].correlation<<END);
							//   if(matchLine[m].maxY-yLimit1<<aliKali[0][matchLine[m].letterIndex].letterW){
							//	  matchLine[m].correlation=5;
							//	  matchLine[m].status=1;  //исключаем из рассмотрения
							//   }
							//}


							 DT("matchLine["<<m<<"].correlation="<<matchLine[m].correlation<<
							 " name="<<matchLine[m].name.c_str()<<"        y="<<matchLine[m].maxY<<" w="<<aliKali[0][matchLine[m].letterIndex]->letterW<<" in="<<matchLine[m].OCRIndex<<END);
						}

						DT("//__________"<<END<<END<<END<<END<<END<<"//__________"<<END<<END<<END<<END<<END);
DT("m3_2");                          	
						while(1){  //продолжаем до полной разборки строки
							//находим максимальную неразобранную букву макимальной ширины
							maxW=0;
							for(int m=0;m<ln;m++){
							 if (matchLine[m].status)continue;
							 if (aliKali[0][matchLine[m].letterIndex]->letterW>maxW){
								 maxW=aliKali[0][matchLine[m].letterIndex]->letterW;

								 indexMaxW=m;

							 }
							} if(maxW==0)break;
							DT(END<<"//@@@/indexMaxW="<<indexMaxW<<"________________________________________________________________/check maxW="<<maxW<<"indexMaxW="<<indexMaxW<<" name"<<matchLine[indexMaxW].name<<" OCRIndex="<<matchLine[indexMaxW].OCRIndex<<" correlation="<<matchLine[indexMaxW].correlation<<END);
							//  теперь внутри этой буквы мы ищем вложенные буквы
							//  если эти буквы являются частью буквы мы их гасимю
								x0=indexMaxW-maxW/2-2; if(x0<0)x0=0;
								x1=indexMaxW+maxW/2+2; if(x1>ln)x1=ln;

								//отмечаем  саму тестовую букву как разобранную
								matchLine[indexMaxW].status=1;

								for (int xInd=x0;xInd<x1;xInd++){
								  DT("/0/________________check c="<<matchLine[xInd].status<<" xInd="<<xInd<<" name="<<matchLine[xInd].name<<END);
								  //если буква, взятая для рассмотрения, не огласовка, то идем дальше
								  //огласовки и церто рассматриваем до победного
								  if ((matchLine[xInd].status)&&
										 (matchLine[xInd].OCRIndex!=3))continue;

								  DT(END<<"/0/______________________________check c="<<matchLine[xInd].status<<" xInd="<<xInd<<" name="<<matchLine[xInd].name<<
								  " correlation="<<matchLine[xInd].correlation<<" wy="<<matchLine[xInd].Wylie<<" OCRIndex="<<matchLine[xInd].OCRIndex<<END);


								  //если внутри буквы мы находим саму себя c меньшей корреляцией мы ее гасим
								  if(matchLine[xInd].name==matchLine[indexMaxW].name&&indexMaxW!=xInd){
									if(matchLine[xInd].correlation<=matchLine[indexMaxW].correlation){
									matchLine[xInd].correlation=5;
									DT("/5/");
									continue;
									}
								  }
								  DT("/5_1/");
									 //если внутри буквы стоит огласовка, и сама эта буква огласовка
									 //то мы ее гасим в случае меньшей корреляции
									  if(matchLine[indexMaxW].OCRIndex==3){
										 if(
										 matchLine[xInd].OCRIndex==3){
											  if(!(matchLine[indexMaxW].Wylie!="tsheg"&&
											  matchLine[xInd].Wylie=="tsheg")){ //огласовки не гасят церто
											  	if(matchLine[xInd].correlation<matchLine[indexMaxW].correlation){
												 matchLine[xInd].correlation=19; DT("/m31/"<<xInd);
												 //matchLine[xInd].status=1; //отмечаем букву как разобранную										 }
												 }
											  }
										 }
										 DT("/31/");
									  }
									 DT("/5_2/");
									  //сочетания буквы и огласовки мы дальше не проверяем
									 if(matchLine[indexMaxW].OCRIndex==3||matchLine[xInd].OCRIndex==3){
											continue;
									 }
								  //matchLine[xInd].OCRIndex>matchLine[m].OCRIndex&&
								  //если внутри буквы есть буквы с невысокой корреляцией мы их гасим
								  if(matchLine[xInd].correlation<=matchLine[indexMaxW].correlation){
											  matchLine[xInd].correlation=32; DT("/m32/"<<xInd);
											  matchLine[xInd].status=1; //отмечаем букву как разобранную										 }
								  }else{
								  //если же эта часть имеет высокую корреляцию, то нужно что-то делать.
								  //вероятнее всего нужно погасить большую букву
									 if(matchLine[indexMaxW].OCRIndex!=3){
									 matchLine[indexMaxW].correlation=33; DT("/m33_/"<<xInd);
									 matchLine[indexMaxW].status=1; //отмечаем букву как разобранную
									 //после этого нужно опять проверять все правила для этого места
									 break;
									 }
								  }
								}
						}
		DT("//__________"<<END<<END<<END<<END<<END<<"//__________"<<END<<END<<END<<END<<END);

DT("m3_3");
						//повторяем цикл разборки стороки
						//если огласовка стоит перед буквой, меняем их местами
						int indexLetter=-1;
						for(int m=0;m<matchLine.size();m++){
						  if(matchLine[m].correlation<70)continue;

							  if(matchLine[m].OCRIndex==3){
								   DT("//vowel found indexLetter="<<m<<END);
								   indexLetter=m;
								}else{
								   //проверяем предыдущую огласовку
								   if(indexLetter<=0)continue; //начальные значения
									   //проверяем, находится ли предыдущая огласовка внутри буквы
									   if(m-aliKali[0][matchLine[m].letterIndex]->letterW/2<indexLetter){
												 //если да, то меняем их местами
												 DT("//start swap"<<" matchLine["<<indexLetter<<"]="<<matchLine[indexLetter].name<<" matchLine["<<m<<"]="<<matchLine[m].name<<END);
												 OCRMatch match;
												 match.Wylie=matchLine[indexLetter].Wylie;
												 match.name=matchLine[indexLetter].name;
												 match.letterIndex=matchLine[indexLetter].letterIndex;
												 match.correlation=matchLine[indexLetter].correlation;
												 match.OCRIndex=matchLine[indexLetter].OCRIndex;
												 match.maxY=matchLine[indexLetter].maxY;

												 matchLine[indexLetter].Wylie=matchLine[m].Wylie;
												 matchLine[indexLetter].name=matchLine[m].name;
												 matchLine[indexLetter].letterIndex=matchLine[m].letterIndex;
												 matchLine[indexLetter].correlation=matchLine[m].correlation;
												 matchLine[indexLetter].OCRIndex=matchLine[m].OCRIndex;
												 matchLine[indexLetter].maxY=matchLine[m].maxY;

												 matchLine[m].Wylie=match.Wylie;
												 matchLine[m].name=match.name;
												 matchLine[m].letterIndex=match.letterIndex;
												 matchLine[m].correlation=match.correlation;
												 matchLine[m].OCRIndex=match.OCRIndex;
												 matchLine[m].maxY=match.maxY;
												 DT("//end swap"<<" matchLine["<<indexLetter<<"]="<<matchLine[indexLetter].name<<" matchLine["<<m<<"]="<<matchLine[m].name<<END);
									   }
								}
						  }

		                //распознаем рамку вокруг текста
				strArray[0][index].stringFlag=1; 
DT("m3_4");
		for(int m=0;m<matchLine.size();m++){ //cout<<"index="<<index<<" matchLine[m].name="<<matchLine[m].name<<END;
					//горизонтальная рамка. помечаем строку как пустую 
				        if(matchLine[m].name=="---"&&matchLine[m].correlation>80){
							//проверяем имеем ли мы дело с таблицей или с рамкой вокруг текста
							count=0;
                            //cout<<"@@@ index="<<index<<END;
							if(index<strArray[0].size()-4){//если это верхняя рамка текста, убираем колонтитул
								for (int ind=0;ind<index;ind++)strArray[0][ind].stringFlag=-1;
							}		

							for(int t=0;t<=matchLine.size();t++){
								if(matchLine[t].correlation>80&&matchLine[t].name!="|"&&matchLine[t].name!="---")count++;
							}	
							if(count<3){		
								 for (int ind=0;ind<strArray[0][index].wordArray.size();ind++){
									 strArray[0][index].wordArray[ind].correlation=-1;
									 strArray[0][index].wordArray[ind].name="";
								 }			 
								strArray[0][index].stringFlag=-1; //label for string which indicate frame around the text	
								//for(int t=0;t<m;t++) matchLine[t].correlation=-1;
								break;
							}	
					 }
					//вертикальная рамка. Убираем шум вокруг рамки
					 if(matchLine[m].name=="|"&&matchLine[m].correlation>80){
						 if(m<matchLine.size()/2){
							 //проверяем имеем ли мы дело с таблицей или с рамкой вокруг текста
							 count=0;
							 for(int t=0;t<=m;t++){
								 if(matchLine[t].correlation>80&&matchLine[t].name!="|")count++;
							}
							 if(count<3){						 
								 for (int ind=0;ind<strArray[0][index].wordArray.size();ind++){
									 if(strArray[0][index].wordArray[ind].x0<m){
										 strArray[0][index].wordArray[ind].correlation=-1;
										 strArray[0][index].wordArray[ind].name="^";
									 } 
								 }	
							         for(int t=0;t<=m;t++) matchLine[t].correlation=0;
							 }
					           }else{
						         //проверяем имеем ли мы дело с таблицей или с рамкой вокруг текста
							 count=0;
							 for(int t=m;t<matchLine.size();t++){
							                 if(matchLine[t].correlation>80&&matchLine[t].name!="|")count++;
							 }
							if(count<3){		 
								for (int ind=0;ind<strArray[0][index].wordArray.size();ind++){
									 if(strArray[0][index].wordArray[ind].x1>m){
										 strArray[0][index].wordArray[ind].correlation=-1;
										 strArray[0][index].wordArray[ind].name="^";
									 } 
									 }
								for(int t=m;t<matchLine.size();t++) matchLine[t].correlation=0;
							}
						 }
					 }
		                 }
			         //strArray[0][index].stringFlag=1;
		                 if(strArray[0][index].stringFlag<0)continue;

				 int space=0,bLeft,bRight=0,bRightOld=0,space0=0,space1=0,lw1, spaceAll=0, letterSpaceAll=0;
				 int spaceCount=1,letterCount=1,letterSpace,letterWidth=0;
						  //подсчет среднего пробела
DT("m3_5");
				 for(int m=0;m<matchLine.size();m++){
					 if(matchLine[m].OCRIndex==3||matchLine[m].correlation<70){continue;}
							 lw1=aliKali[0][matchLine[m].letterIndex]->letterW;
							 bLeft=m-lw1/2;
							 //cout<<"bLeft="<<bLeft<<" bRightOld="<<bRightOld<<" lw1="<<lw1<<END;
							 space1=bLeft-bRightOld;   if(space1<0)space1=0;
							 if(space1<lw1*2){
								 if(space1>lw1*0.25){
									spaceAll+=space1;       spaceCount++;
								 }else{
									letterSpaceAll+=space1; letterCount++;
									letterWidth+=lw1;
								 }
							 }
							 bRight=m+lw1/2; //DT(" new sR="<<sR<<" matchLine[m].name="<<matchLine[m].name<<END);
							 space0=space1;
							 bRightOld=bRight;
				 }
				 space=spaceAll/spaceCount;               //средняя величина пробела
				 letterWidth=letterWidth/letterCount;
				 if(space<letterWidth/2)space=letterWidth/2;
				 letterSpace=letterSpaceAll/letterCount;  //средняя величина расстояния между буквами (кернинга)
				 //cout<<"space="<<space<<" spaceCount="<<spaceCount<<" letterSpace="<<letterSpace<<" letterCount="<<letterCount<<" letterWidth="<<letterWidth<<END;
				 space=(space+letterSpace)*2;             //вычисление порога  //###need adaptive value
DT("m3_5_1 space=");
				 for(int m=0;m<matchLine.size();m++){
					 if(matchLine[m].correlation==0)continue;
					 DT("matchLine["<<m<<"].correlation="<<matchLine[m].correlation<<
						" name="<<matchLine[m].name.c_str()<<"        w="<<aliKali[0][matchLine[m].letterIndex]->letterW<<" in="<<matchLine[m].OCRIndex<<END);

					 if(matchLine[m].OCRIndex==3&&matchLine[m].correlation<85){continue;}

						wIndex=0;
						  if(matchLine[m].correlation>90)DT("//_____________");
						  if(matchLine[m].correlation>70){
							  DT("matchLine[m].letterIndex="<<matchLine[m].letterIndex<<" aliKali->base.size()="<<aliKali->letterCount);
							  lw1=aliKali[0][matchLine[m].letterIndex]->letterW;   //cout<<"lw1="<<lw1;
							 bLeft=m-lw1/2;
							 space1=bLeft-bRightOld;   if(space1<0)space1=0;
							 DT(" space1="<<space1<<" space="<<space);
							  if(space1>space){
								 if(pageText.size()){
									 if(pageText[pageText.size()-1].name!="་"&&matchLine[m].name!="་"){
										 wordOCR st;
										 st.name="";
										 st.delimeter=" ";
										 st.newLine="";
										 DT(" space found"<<END);
										 st.id=id_index; id_index++;
										 pageText.push_back(st);
									 }	 
								}
							}
							 //cout<<".3";
							 bRight=m+lw1/2; DT(" matchLine[m].name="<<matchLine[m].name<<END);
							 space0=space1;
							 bRightOld=bRight;

							 //mainString+=matchLine[m].name;
							 //DT("mainString="<<mainString<<END);
							 letter=matchLine[m].Wylie;
							 count=0;
							 //теперь внутри буквы мы убираем лишние квадратики
							 //и устанавливаем верные габариты буквы
							 DT("/@/_______m="<<m<<" ="<<matchLine[m].name<<" matchLine[m].maxY="<<matchLine[m].maxY
								<<" aliKali[0]["<<matchLine[m].letterIndex<<"]->ySum="<<aliKali[0][matchLine[m].letterIndex]->ySum
								<<" yLimit0="<<yLimit0<<END);

							 for (int in=0;in<strArray[0][index].wordArray.size();in++){
								x0=(m-aliKali[0][matchLine[m].letterIndex]->letterW/2)/scale;//+aliKali[0][matchLine[m].letterIndex]->dX;
								if(x0<0)x0=0;
								 x1=(m+aliKali[0][matchLine[m].letterIndex]->letterW/2)/scale;//+aliKali[0][matchLine[m].letterIndex]->dX;
								if(x1>ln)x1=ln;
								if(strArray[0][index].wordArray[in].center.x>x0&&
								   strArray[0][index].wordArray[in].center.x<x1&&
								   strArray[0][index].wordArray[in].name=="*"){
                                   DT("old"<<END);
								   if(count==0){
									 strArray[0][index].wordArray[in].name=matchLine[m].name;
									 strArray[0][index].wordArray[in].Wylie=matchLine[m].Wylie;
									 strArray[0][index].wordArray[in].correlation=matchLine[m].correlation;
									 strArray[0][index].wordArray[in].w=aliKali[0][matchLine[m].letterIndex]->letterW/scale;
									 strArray[0][index].wordArray[in].x0=x0;
									 strArray[0][index].wordArray[in].x1=x1;
									 //strArray[0][index].wordArray[in].center.x=(strArray[0][index].wordArray[in].x1-strArray[0][index].wordArray[in].x0)/2;
									 //strArray[0][index].wordArray[in].center.y=matchLine[m].maxY;
                                     strArray[0][index].wordArray[in].OCRIndex=matchLine[m].OCRIndex;
									   strArray[0][index].wordArray[in].y0=strArray[0][index].y0;//-yLimit0
									   //+matchLine[m].maxY
									   //-aliKali[0][matchLine[m].letterIndex]->letterH/2
									   //-aliKali[0][matchLine[m].letterIndex]->ySum;
									   strArray[0][index].wordArray[in].y1=strArray[0][index].y1;//-yLimit0
									   //+matchLine[m].maxY
									   //+aliKali[0][matchLine[m].letterIndex]->letterH/2
									   //-aliKali[0][matchLine[m].letterIndex]->ySum;
									   wIndex=in;
									strArray[0][index].wordArray[in].id=id_index; id_index++;   
									pageText.push_back(strArray[0][index].wordArray[in]);   
                                    DT("x0="<<x0<<" x1="<<x1<<" center.x="<<strArray[0][index].wordArray[in].center.x<<END);
								   }else{
									  if(strArray[0][index].wordArray[in].name=="*"){
										 strArray[0][index].wordArray.erase(strArray[0][index].wordArray.begin()+in,strArray[0][index].wordArray.begin()+in+1);
									  }
								   }

								   count++;
								}

							 }
								if(count==0){ //не найдено подходящих квадратиков, нужно вставить в строку новый
									 DT("new"<<END);
									 wordOCR wP;
									 wP.center.x=m/scale;
									 wP.center.y=matchLine[m].maxY/scale;
									 wP.name=matchLine[m].name;
									 wP.Wylie=matchLine[m].Wylie;
									 wP.w=aliKali[0][matchLine[m].letterIndex]->letterW/scale;
									 wP.x0=x0;
									 wP.x1=x1;
									 wP.OCRIndex=matchLine[m].OCRIndex;
									wP.y0=strArray[0][index].y0;//-yLimit0
										//+matchLine[m].maxY
										//-aliKali[0][matchLine[m].letterIndex]->letterH/2
										//-aliKali[0][matchLine[m].letterIndex]->ySum;
									wP.y1=strArray[0][index].y1;//-yLimit0
									    //+matchLine[m].maxY
									    //+aliKali[0][matchLine[m].letterIndex]->letterH/2
									    //-aliKali[0][matchLine[m].letterIndex]->ySum;
									wP.correlation=matchLine[m].correlation;
									 strArray[0][index].wordArray.insert(strArray[0][index].wordArray.begin()+wIndex,wP);
									 wIndex++;
									wP.id=id_index; id_index++;   
									pageText.push_back(wP); 
								}
                                //сохраняем статистику использования буквы
							  
							aliKali[0][matchLine[m].letterIndex]->cn++;
							aliKali[0][matchLine[m].letterIndex]->crSum+=matchLine[m].correlation;
						}
				  }
				  //mainString+="\n";
             //оцениваем результат распознавания строкию Если он не соответствует результату распознавания
		     //предыдущей строки, запускаем определение размера строки и распознаем строку с новым масштабом
			correlation=0; int count=0;
			for(int m=0;m<matchLine.size();m++){
				if(matchLine[m].correlation>50){
					if(matchLine[m].name=="་")continue;
					correlation+=matchLine[m].correlation;
					count++;
				}
			}
		    if(count&&correlation){
				correlation/=count; 
			}else{
				stepCount++;    cout<<"stepCount="<<stepCount<<"c=0 goto ScaleDetector"<<endl;
				if(stepCount<2){
					needLineSize=0;
					goto ScaleDetector;
				}	
			}
			cout<<" correlation="<<correlation<<" bestCorrelation="<<bestCorrelation<<endl;
		    if((correlation+correlation/10<bestCorrelation&&correlation<85)||correlation<70){
				stepCount++;   cout<<"stepCount="<<stepCount<<"c="<<correlation<<" best c="<<bestCorrelation<<" goto ScaleDetector"<<endl;
				if(stepCount<2){
					needLineSize=0;
					goto ScaleDetector;
				}	
			}

		
		    matchLine.resize(0);
			if(needScaleFlag)line->destroy();  //destroy text line bitmap
		
			if(pageText.size())pageText[pageText.size()-1].newLine="<br/>\n"; 
			DT("m4"<<END;)     		
 						//cout<<"pageText.size()="<<pageText.size()<<END;

						//setOCRCorrelation(stackFlag,mode);  //set correlation for this letter
	 //break;
         
	}

	//mainString=str_replace("་ ", "་",  mainString);
	//mainString=str_replace("་ ", "་",  mainString);
	//mainString=str_replace("ིི", "ི",  mainString);
	//mainString=str_replace("ེེ", "ེ",  mainString);
	//mainString=str_replace("ོོ", "ོ",  mainString);
	//mainString=str_replace("ལཁ", "འཁ",  mainString);
	DT("start grammar corrector"<<END);	
	if(inputData->data["ocrData"]!="tibLetters"){
		mainString=logicProcessor->grammarCorrector(inputData,pageText,correctionTable,LOCAL_MODE);
	}	
	//cout<<"mainString1="<<mainString<<endl;
	DT("done Grammar"<<endl);
	
 }////////////////////////////////////////////////////////////////////////////////


/*
-(void)reloadTextOCR:(short)letterSetCount{
short baseCount;
[mainString setString:@""];
//cout<<"print text OCR"<<endl;
baseCount=vectorBase[0].allContourCount;
if(letterBase[0].allContourCount>=0){

		for (currentRecord=0;currentRecord<=baseCount; currentRecord++){
		//cout<<"letterBase[currentRecord].OCRStatus"<<(short)letterBase[currentRecord].OCRStatus<<endl;
		//cout<<"|||vectorBase["<<currentRecord<<"].contour="<<(short)vectorBase[currentRecord].contour<<endl;
			if(vectorBase[currentRecord].contour==1||vectorBase[currentRecord].contour==3){
			[letterStructure setOCRCorrelation:letterBase :vectorBase :currentRecord :letterBase[0].allContourCount-letterSetCount];  //correlation for last letter only
			}
		}//end for (currentRecord=0;currentRecord<[vectorBase count]-1; currentRecord++)
}//if(letterBase[0].allContourCount>0){
      [self textReaderOCR]; //start grammar recognition
      [self setWylieScript];
		currentRecord=0;
      [stringOCRField setString:mainString];   //now we put all letters in lines and send it for user
		//[self readNextOCRLetter]; //ask user about recognise first low correlation lette

}////////////////////////////////////////////////////////////////////////////////
*/
