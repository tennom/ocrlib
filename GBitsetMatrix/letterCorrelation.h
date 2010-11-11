void GBitsetMatrix::letterCorrelation(commandData *inData,
									  vector<OCRMatch>&matchLine,
									  letterBase *aliKali,
									  int y0,
									  int y1,
									  int scaleMode,
									  int print){

  //aliKali - указатель на массив букв (база букв).
  //aliKali[0].alLetterCount - количество букв в базе
  //BitMask32 *mask=&aliKali[0][1].mask32[0];  -- указатель на первую маску во второй букве базы
  //aliKali[0][1].mask32Count - количество масок во второй букве базы
  //stringArray - массив строк как в CBitset
  //stringNum - номер строки в массиве

  // resize(ncnr) векторных массивов сделан в Bitset_base.h
#define  c_out_ cout
#define  c_out1_ inData->c_out

#ifdef REPORT
DT("inData->name"<<inData->data["name"]<<" border="<<border<<END);
int mCMax=0; string name;
#endif


  //GBitMask32 *mask;//=&aliKali[2].mask32[0];  //-- указатель на первую маску во второй букве базы
  //DM("/1/____aliKali[0].Wylie"<<aliKali[0].Wylie.c_str());
  //printMask(mask,c_out);
  //TIME_START

  int mC,mC0,dX,dY,mY,mX;
  int maxX,maxY,maxSumX,maxSumY,count;
  int letterY0, maskY0, maskY1,limitY;
  glyphOCR *glyph;


  // константы для алгоритма подсчета единиц в 128 или в 64р словах
static const unsigned int constF[12]={              // 12  16
	0x33333333, 0x33333333, 0x33333333, 0x33333333,
	0x55555555, 0x55555555, 0x55555555, 0x55555555,
	0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f  // ,
//	0x00000000, 0x00000000, 0x00000000, 0x00000000  // TEST
};

// переход в режим Assembler, загрузка констант
__asm {     //  movups (без требования выравнивания)
	// загрузка констант в регистр 64p ММХ ( считаем в байтах - int*4)
	movq            mm5, qword ptr constF+16;   // 55 Пересылка данных (64 бит)
	movq            mm6, qword ptr constF;      // 33 из/в регистр ММХ  MOVDQU-128
	movq            mm7, qword ptr constF+32;   // 0f
/**/
	// загрузка констант в регистр 128p SSE
	//  movups без требования выравнивания  ( MOVAPS должны быть выровнены )
#ifdef WIN32
	movups          xmm5, dqword ptr constF+16;  // 55  Пересылка данных (128 бит)
	movups          xmm6, dqword ptr constF;     // 33  + MOVDQU
	movups          xmm7, dqword ptr constF+32;  // 0f
//	movups          xmm2, dqword ptr constF+48;  // TEST
#else
	movups          xmm5, [constF+16];  // 55  Пересылка данных (128 бит)
	movups          xmm6, [constF];     // 33  + MOVDQU
	movups          xmm7, [constF+32];  // 0f
	//	movups          xmm2, dqword ptr constF+48;  // TEST
#endif

} // __asm
//Инструкция movq выполняется за шесть тактов, тогда как для pshufw требуется только два
/**/

//clock_t  tm_start, tm_end ,tm_0=0, tm_1=0; double time; // tm_start=clock();
//static clock_t tm0=0, tm1=0;

	 for(int in=0; in<aliKali->letterCount;in++){  DT(" in="<<in<<" name"<<aliKali[0][in]->name);
     //for(int in=0; in<1;in++){  DT(" in="<<in<<" name"<<aliKali[0][in]->name);
		 
		 glyph=aliKali[0][in];
         if(scaleMode&&glyph->OCRIndex!=5)continue;
		 
		 #ifdef REPORT
		 //if(inData->data["name"]==glyph[0].name){print=1;}else{print=0;}
		 //cout<<"/"<<glyph[0].name<<"/check glyph="<<glyph[0].name<<" in="<<in<<" inData->x1="<<inData->x1<<" inData->x0="<<inData->x0<<END;
		 //cout<<(short)glyph[0].name[0]<<endl;
		 //if((short)glyph[0].name[0]==58)print=1;
		 
		// DT("inData->x1="<<inData->x0<<" inData->x1="<<inData->x1<<" y0="<<y0<<" y1="<<y1<<" border="<<border<<" nrows="<<nrows<<END);
		 #endif




		 letterY0=glyph[0].y0;

		 if(glyph[0].mask32Count>0){
			 dX=glyph[0].mask32[0].mWOn;
			 dY=glyph[0].mask32[0].mHOn;
			 //if(dY>24)dY=24;
			 if(y0==0)y0=nrows/10;
			 if(y1==0)y1=nrows-nrows/10-border;	 
				 
			 limitY=(y1-y0)/1;
			
			 maskY0=y0-letterY0+glyph[0].mask32[0].yMask+border-limitY; //
			 maskY1=maskY0+limitY*2;
			 DT("y0="<<y0+border<<" maskY0="<<maskY0<<" border="<<border<<" ncolumns="<<ncolumns<<" limitY="<<limitY<<END);

			 for(int y=maskY0;y<=maskY1;y+=dY){  //cout<<"y="<<y<<endl;
				for(int x=border+32;x<ncolumns-border+32;x+=dX){

						mC=0; maxSumX=-1;maxSumY=0; count=0;
					for(int m=0;m<glyph[0].mask32Count;m++){ //DT("c="<<glyph[0].mask32Count<<" m="<<m<<" ");
							maxX=0; maxY=0;

						#ifdef REPORT
							// print=0;
							// if(x-border-32>inData->x0&&
							// x-border-32<inData->x1){
							//   if(inData->data["name"]==glyph[0].name){print=1;}else{print=0;}
							// }
							// if(m!=0)print=0;

						#endif
                            
							if(m==0){
							   //tm_start=clock();
							   mC0=setMatrix_Lion(&glyph[0].mask32[m],
												   glyph[0].mask32[0].xMask+x,
												   y,
												   glyph[0].mask32[0].xMask+x+dX,
												   y+dY,
												   0,
												   &maxX,
												   &maxY,
												   c_out1_,
												   print);
//DT("t1");

								mX=x+(maxX-glyph[0].mask32[0].xMask-x);
								mY=y+(maxY-glyph[0].mask32[0].yMask-y);

								//tm_end=clock(); tm_end-=tm_start; tm0+=tm_end;
							}else{
								//tm_start=clock();
								
								 mC0=setMatrix_Lion(&glyph[0].mask32[m],
												   glyph[0].mask32[m].xMask+mX,
												   glyph[0].mask32[m].yMask+mY,
												   0,0,
												   4,
												   &maxX,
												   &maxY,
												   c_out1_,
												   print);
//DT("t2");
							//tm_end=clock(); tm_end-=tm_start; tm1+=tm_end;
							}

							//#ifdef REPORT
							//if(print)glyph[0].mask32[m].printMask();
							//DT("mask"<<m<<" mC0="<<mC0<<" x="<<x<<" y="<<y<<" glyph y="<<glyph[0].mask32[m].yMask);
							//DT("__________________MatrixCorrelation="<<mC0<<" glyph[0].name="<<glyph[0].name.c_str());
							//DT(" mask["<<m<<"].mHOn="<<glyph[0].mask32[m].mHOn);
							//DT("   maxX="<<maxX<<" =maxY"<<maxY<<END);
							//#endif
							if(mC0<50)break;
							mC+=mC0;
							maxSumX+=maxX;
							maxSumY+=maxY;
							count++;
							//SH(glyph[0].Wylie.c_str());

						 }//for(int m=0;m<glyph[0].mask32Count
//DT("t3");
					     mC/=glyph[0].mask32Count;
						 if(count){
							#ifdef REPORT
							DT("/_ALL MatrixCorrelation/_____________________________________________mC="<<mC<<END);
							#endif
							maxSumX=maxSumX/count-32;
							//if(maxSumX<0)maxSumX=0;
							//if(maxSumX>matchLine.size())maxSumX=matchLine.size()-1;

							//maxSumX=glyph[0].xSum+maxSumX-border+16-glyph[0].letterW/2;
							 maxSumX=maxSumX-border-glyph[0].xSum; 
							if(maxSumX<0)maxSumX=0;
							if(maxSumX>matchLine.size()-10)maxSumX=matchLine.size()-10;
							maxSumY=maxSumY/count;

						 }
						 //SH(mC);
						 //ImageProcessor->WriteImageData(drawDataRGB,IMGNOFLIP);
						 #ifdef REPORT
						 if(mC>0)DT("ALL mC="<<mC<<" y="<<maxSumY<<" x="<<maxSumX<<" glyph[0].ySum="<<glyph[0].ySum<<END);
						  if(inData->idNumber==in){
							 if(mC>mCMax){mCMax=mC; name=glyph[0].name;}
						  }
						 #endif
						 if(!maxSumX)continue;
//DT("t4 maxSumX="<<maxSumX);
							if(mC>50){
								 //cout<<"set c0="<<matchLine[maxSumX].correlation;
								//возможна по этому адресу уже есть буква, например огласовка.
								//проверяем и если это так вставляем букву перед огласовкой
								 maxSumX+=glyph[0].dX;
								if(maxSumX>matchLine.size()){ //cout<<"owerflow"; exit(0);
								   maxSumX=matchLine.size();
								}
								 if(matchLine[maxSumX].OCRIndex==3&&glyph[0].OCRIndex!=3){
								  maxSumX--;
								 }
								 if(matchLine[maxSumX].OCRIndex==3&&glyph[0].OCRIndex!=3){
								  maxSumX--;
								 }
								if(matchLine[maxSumX].OCRIndex==3&&glyph[0].OCRIndex!=3){
									maxSumX--;
								}
								if(matchLine[maxSumX].OCRIndex!=3&&glyph[0].OCRIndex==3){
								  maxSumX++;
								}
								 if(matchLine[maxSumX].OCRIndex!=3&&glyph[0].OCRIndex==3){
								  maxSumX++;
								 }
								if(matchLine[maxSumX].OCRIndex!=3&&glyph[0].OCRIndex==3){
									maxSumX++;
								}
								

								 if(matchLine[maxSumX].correlation==mC){
								  maxSumX++;
								 }
								 if(matchLine[maxSumX].correlation==mC){
								  maxSumX++;
								 }
								if(matchLine[maxSumX].correlation==mC){
									maxSumX++;
								}

								 /*if(matchLine[maxSumX].correlation==mC){
									 OCRMatch match;
									 match.correlation=mC;
									 match.name=glyph[0].name;
									 match.Wylie=glyph[0].Wylie;
									 match.OCRIndex=glyph[0].OCRIndex;
									 match.letterIndex=in;
									 match.maxY=maxSumY;
									 matchLine[maxSumX].match.push_back(match);
								 }
								 */

									/*
									static index=0;
									cout<<"letter_"<<in<<" index_"<<index<<" maxSumX="<<maxSumX<<END;
									if(index>4){
									int a=0;
									cout<<"name="<<glyph[0].name<<END;
									}index++;
									*/

								 if(matchLine[maxSumX].correlation<mC){
									//cout<<"maxSumX="<<maxSumX<<"name="<<glyph[0].Wylie<<END;
									matchLine[maxSumX].correlation=mC;
									matchLine[maxSumX].name=glyph[0].name;
									matchLine[maxSumX].Wylie=glyph[0].Wylie;
									matchLine[maxSumX].OCRIndex=glyph[0].OCRIndex;
									matchLine[maxSumX].letterIndex=in;
									matchLine[maxSumX].maxY=maxSumY-border;  
								 }
							}//if(mC>50
//DT("t5");			 
			}//for(int x=border+32
DT("t6");				 
		  }//for(int y=maskY0;
DT("t7");
		 }//if(glyph[0].mask32Count
	 
	 
	 }//for(int in=0; in<aliKali->base.size();

	 #ifdef REPORT
	 DT("/@@@/___ALL mCMax="<<mCMax<<" name="<<name<<END);
	 #endif
	 __asm {
		     emms; 
		   }

	 //cout<<"tm0="<<(double)tm0/CLOCKS_PER_SEC<<" tm1="<<(double)tm1/CLOCKS_PER_SEC<<" tm0/tm1="<<(double)tm0/tm1<<END;
	// emms; команда обеспечивает переход процессора от исполнения MMX-команд
	// к исполнению обычных команд с плавающей запятой:
	// она устанавливает значение 1 во всех разрядах слова состояния.

	//DM("2@@")tm_end=clock(); tm_end-=tm_start; time=tm_end/CLOCKS_PER_SEC;DM("time="<<time<<END);
	//DP("Matrix_Lion_2@@")tm_end=clock(); tm_end-=tm_start1; time=tm_end/CLOCKS_PER_SEC;DP("time="<<time<<END<<END);
/**/

//#ifdef WIN32
	 //ImageProcessor->WriteImageData(drawDataRGB,IMGNOFLIP);  //SH(1);
//#endif
  // TIME_PRINT

#undef c_out_


}//_____________________________________________________________________________

