int GBitsetMatrix::letterToLetterCorrelation(glyphOCR *glyph,
											  int y0,
											  int y1,
											  int print){
  //letter - указатель тестовую букву
  //BitMask32 *mask=&aliKali[0][1].mask32[0];  -- указатель на первую маску во второй букве базы
  //aliKali[0][1].mask32Count - количество масок во второй букве базы
	ofstream out;
	
#define  c_out_ cout
#define  c_out1_ out

  //GBitMask32 *mask;//=&aliKali[2].mask32[0];  //-- указатель на первую маску во второй букве базы
  //DM("/1/____aliKali[0].Wylie"<<aliKali[0].Wylie.c_str());
  //printMask(mask,c_out);
  //TIME_START

  int mC,mC0,dX,dY,mY,mX;
  int maxX,maxY,maxSumX,maxSumY,count;
  int letterY0, maskY0, maskY1,limitY;
  OCRMatch match;
	
  

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
#ifdef WIN_VS
	//Vic movups          xmm5, dqword ptr constF+16;  // 55  Пересылка данных (128 бит)
	//Vicmovups          xmm6, dqword ptr constF;     // 33  + MOVDQU
	//Vicmovups          xmm7, dqword ptr constF+32;  // 0f
	//	movups          xmm2, dqword ptr constF+48;  // TEST
	
#endif
	
#ifdef WIN32
	movups          xmm5, dqword ptr constF+16;  // 55  Пересылка данных (128 бит)
	movups          xmm6, dqword ptr constF;     // 33  + MOVDQU
	movups          xmm7, dqword ptr constF+32;  // 0f
//	movups          xmm2, dqword ptr constF+48;  // TEST
#endif
#ifdef MAXCOS	
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
		 letterY0=y0;
	     int maskX[20];
	     int maskY[20];    //temporary arrays for store letter features coordinates
		 int bestX[20];
		 int bestY[20];    
	     int bestMask[20];  //temporary arrays for store letter features correlation

		 if(glyph[0].mask32Count>0){
			 dX=glyph[0].mask32[0].mWOn; if(dX<5)dX=5;
			 dY=glyph[0].mask32[0].mHOn; if(dY<5)dY=5;
			 //if(dY>24)dY=24;
			 limitY=(y1-y0)/2;
			 maskY0=y0+border/2;
			 maskY1=y1+border+border/2;
			 
			 DT("y0="<<y0<<" y1="<<y1<<" maskY0="<<maskY0<<" maskY1="<<maskY1<<" border="<<border<<END);

			 for(int y=maskY0;y<=maskY1;y+=dY){
					for(int x=border+32;x<ncolumns-border+32;x+=dX){

								mC=0; maxSumX=-1;maxSumY=0; count=0;
								for(int m=0;m<glyph[0].mask32Count;m++){
	 								
									maxX=0; maxY=0;

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


										mX=x+(maxX-glyph[0].mask32[0].xMask-x);
										mY=y+(maxY-glyph[0].mask32[0].yMask-y);

										//tm_end=clock(); tm_end-=tm_start; tm0+=tm_end;
									}else{
										//tm_start=clock();
										 mC0=setMatrix_Lion(&glyph[0].mask32[m],
														   glyph[0].mask32[m].xMask+mX,
														   glyph[0].mask32[m].yMask+mY,
														   0,0,
														   8,
														   &maxX,
														   &maxY,
														   c_out1_,
														   print);

									//tm_end=clock(); tm_end-=tm_start; tm1+=tm_end;
									}

									#ifdef REPORT
									//if(print)glyph[0].mask32[m].printMask();
									DT("mask"<<m<<" mC0="<<mC0<<" x="<<x<<" y="<<y<<" glyph y="<<glyph[0].mask32[m].yMask);
									DT("__________________MatrixCorrelation="<<mC0<<" glyph[0].name="<<glyph[0].name.c_str());
									DT(" mask["<<m<<"].mHOn="<<glyph[0].mask32[m].mHOn);
									DT("   maxX="<<maxX<<" =maxY"<<maxY<<END);
									#endif
									if(mC0<50)break;
									mC+=mC0;
									maxSumX+=maxX-32; DT("   maxSumX="<<maxSumX<<END);
									maxSumY+=maxY; DT("   maxSumY="<<maxSumY<<END);
									DT(" xMask="<<glyph[0].mask32[m].xMask<<" yMask="<<glyph[0].mask32[m].yMask<<endl);
									maskX[count]=maxX-32-border;   //coordinate from left upper corner of source image
									maskY[count]=maxY-border;
									count++;
									//SH(glyph[0].Wylie.c_str());

							   }
						       //DT("mC="<<mC<<" glyph[0].mask32Count="<<glyph[0].mask32Count<<endl);
							   mC/=glyph[0].mask32Count;
								 //SH(mC);
								 //ImageProcessor->WriteImageDTta(drawDTtaRGB,IMGNOFLIP);
						 
							 if(match.correlation<mC&&mC>80){
								 DT("@@___maxSumX1="<<maxSumX<<" count="<<count<<END);
								 match.correlation=mC;
								 maxSumX=maxSumX/count-border;
								 maxSumY=maxSumY/count-border;
								 DT("mC="<<mC<<" maxSumX="<<maxSumX<<" nrows="<<nrows<<endl);
								 DT("glyph[0].xSum="<<glyph[0].xSum<<" maxSumX="<<maxSumX<<endl);
								 DT("glyph[0].ySum="<<glyph[0].ySum<<" maxSumY="<<maxSumY<<endl);
								 for(int a=0;a<glyph[0].mask32Count;a++){
									 bestX[a]=maskX[a]; bestY[a]=maskY[a];  //store best rezult;
									 bestMask[a]=glyph[0].mask32[a].correlation;
								 }
								 //glyph[0].mask128[0].xMask=32+glyph[0].xSum-maxSumX-2;
								 //glyph[0].mask128[0].yMask=glyph[0].ySum-maxSumY;
							 }
					}//for(int x=border+32;
			 
			 }
		 }
        for(int a=0;a<glyph[0].mask32Count;a++){
			glyph[0].mask32[a].xMask=bestX[a]; //coordinate from left upper corner of source image
			glyph[0].mask32[a].yMask=bestY[a];
			glyph[0].mask32[a].correlation=bestMask[a];
			DT("@mask m="<<a<<" xMask="<<glyph[0].mask32[a].xMask<<" yMask="<<glyph[0].mask32[a].yMask<<endl);

	    }
	
	
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
	 //ImageProcessor->WriteImageDTta(drawDTtaRGB,IMGNOFLIP);  //SH(1);
//#endif
  // TIME_PRINT

#undef c_out_

	return match.correlation;

}//_____________________________________________________________________________

