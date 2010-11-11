

// Вычисление коэффициента корреляции по маске единичных битов  IEST
// -----------------------------------------------------------------------------
int GBitsetMatrix::setMatrixCorrelationASM(GBitMask32 *mask32,
										int xSrc0,
										int ySrc0,
										int xSrc1,
										int ySrc1,
										int dlt,
										int *maxX,
										int *maxY,
										ofstream &c_out){

  int correlation=0;
  // img - исходное изображение для примениения маски
  // mask32  - маска которая применяется по всей площади img

//DP("xSrc0="<<xSrc0<<" ySrc0"<<ySrc0<<" dlt="<<dlt<<" border="<<border<<END);
  if(ySrc0+border>nrows||xSrc0+border>ncolumns||xSrc0<0||ySrc0<0)return 0;
   //drawDataRGB[0][ySrc0+border][xSrc0+border]=0;

  int y,x,m,p;
  int sx0,sy0,sx1,sy1;
  int SumBitOn,SumBitOff,SumBtMax,deltaSum;
	int nr=nrows;  // SH(ncolumns);  SH(nrows);
	int mH=mask32[0].mH;// mW=32;        // mH(8-96) высота и mW (32) ширина (габарит) битовой
						   // маски перефирийной области  "Off"

  unsigned long *Si64,*Sm64;
  unsigned long  resBitOn,resBitOff;


static const unsigned  int COF[2]={0x0f0f0f0f, 0x0f0f0f0f};
static const unsigned  int C55[2]={0x55555555, 0x55555555};
static const unsigned  int C33[2]={0x33333333, 0x33333333};

//unsigned long test1[2]={ 0xFFFFFFFF, 0xFFFFFFFF};

  //unsigned int Sum;
  unsigned int *mask;
  mask=mask32[0].Off;

  //int ncVnr=mH*mW;
  //int sf=szf*8;     //  sf=32,  для int=32


//DP(" TIME_START setMatrixCorrelation ON TEST mask32[0].mH="<<mask32[0].mH<<END);
///TIME_START

		 ///mask32->printMask(c_out);         DM(END);DM(END);

		 // Задание области скольжение маски по смещению dlt или по координатам x,y
		 if(dlt>0){
			 sx0=xSrc0 + border + 32,  sx1=xSrc0 + dlt + border + 32;
			 sy0=ySrc0 + border,       sy1=ySrc0 + dlt + border;
		 }else{  //  dlt=-dlt
			 sx0=xSrc0 + border + 32,  sx1=xSrc1 + border + 32;
			 sy0=ySrc0 + border,       sy1=ySrc1 + border;
//			 mH=sy1 - sy0;
		 }

  int wVh=(sx1 - sx0)*(sy1 - sy0);
  int d;
  unsigned short *BolS;

  // запрос памяти
	BolS=(unsigned short*)malloc((wVh+64)*2);
  // выход в случае отсутсттвия свободной памяти запрашиваемого размера
  if (BolS==NULL) {DP("BolS"); exit (1);}



		 // Скольжение маски по всей nc*nr площади скана.
		 SumBtMax=d=0;

		 for ( x=sx0; x < sx1; x++ ) {
		 p=x*nr;
		 for ( y=sy0; y < sy1; y++ ) {
			   SumBitOn=SumBitOff=0;
			   // Суммы маски mask32 по  Y
			   for ( m=0; m < mH; m+=2 ) {
				 // Умножение маски на транспонированный скан SInt
				 //Si=sInt[y+p+m];
				 Si64=(unsigned long *)(sInt+y+p+m);
				 if(*Si64 != 0) {
					Sm64=(unsigned long *)(mask32[0].On+m);
					resBitOn=*Si64 & *Sm64;    //Sb64- адрес переменной  resBit
					Sm64=(unsigned long *)(mask32[0].Off+m);
					resBitOff=*Si64 & *Sm64;    //Sb64- адрес переменной  resBit

// 32   // 16MD
__asm {

// Форматы данных и команды их обработки процессоров Pentium III, Pentium IV
// http://www.bestreferat.ru/referat-53991.html

				CPUID                  ;//0Fh, 0A2h CPUID instruction
				// MMX64
				//MOVDDUP         xmm1,EAX
				//lddqu       xmm1, xmmword ptr maskON; //dqword

				///	PSLLDQ          XMM0,5
				///PINSRW XMM1,EAX,0
			   ///// PSLLDQ  ; pslldq shift double quadword left logical (5 bytes)
				movq            mm0, qword ptr resBitOn;   //

//				movd            mm0, d3;    // v_low
//				punpckldq       mm0, d5;    // v

				movq            mm5, qword ptr C55;   // Пересылка данных (64 бит) из/в регистр ММХ  MOVDQU-128
				movq            mm6, qword ptr C33;
				movq            mm7, qword ptr COF;
		//        movd            mm0, word ptr v;   // обмен данными между: MMX регистрами, стандартными 32-битным регистрами, а также ячейками памяти. (Movd, Movq)
		//        punpckldq       mm0, word ptr v + 4;
				movq            mm1, mm0;   // v
				psrld           mm0, 1;     // v >> 1     psrld    PSLLDQ  Логический сдвиг вправо упакованных слов (двойных, учетверенных) операнда назначения на количество бит, указанных в операнде- источнике, с заполнением старших бит нулями
				pand            mm0, mm5;   // (v >> 1) & 0x55555555
				psubd           mm1, mm0;   // w = v - ((v >> 1) & 0x55555555)  Вычитание упакованных байт (слов или двойных слов) без насыщения (с циклическим антипереполнением)
				movq            mm0, mm1;   // w                                Пересылка данных (64 бит) из/в регистр ММХ
				psrld           mm1, 2;     // w >> 2
				pand            mm0, mm6;   // w & 0x33333333  //команда выполняет побитовую операцию логическое И над всеми битами операндов источника и приемника. Результат помещается в операнд приемник.
				pand            mm1, mm6;   // (w >> 2)  & 0x33333333
				paddd           mm0, mm1;   // x = (w & 0x33333333) + ((w >> 2) & 0x33333333)  Сложение упакованных байт (слов или двойных слов) без насыщения PADDW (с циклическим переполнением)
				movq            mm1, mm0;   // x                                Пересылка данных (64 бит) из/в регистр ММХ
				psrld           mm0, 4;     // x >> 4
				paddd           mm0, mm1;   // x + (x >> 4)
				pand            mm0, mm7;   // y = (x + (x >> 4) & 0x0F0F0F0F)
				pxor            mm1, mm1;   // Исключающее ИЛИ   ==1
				psadbw          mm0, mm1;   // Нахождение суммы модулей разности пар слов (результат — 16- битное число)

				movd            eax, mm0;  // END
		//		mov             Sum, eax ;  ////////////////////////////

				//заносим сумму единиц в накопительную переменную  SumBitOn
				add             eax, SumBitOn  //SumBitOn=SumBitOn & 0x7F;  // 127 Обнуляем старшие разряды, содержащие "мусор"
				mov             SumBitOn, eax

			   // к исполнению обычных команд с плавающей запятой:
			   // она устанавливает значение 1 во всех разрядах слова состояния.


					// Умножение маски Off на транспонированный скан SInt

//				movd            mm0, d3;    // v_low
//				punpckldq       mm0, d5;    // v
				movq            mm0, qword ptr resBitOff;   //
				///movq            mm5, C55;
				//movq            mm6, C33;
				//movq            mm7, COF;
		//        movd            mm0, word ptr v;   // обмен данными между: MMX регистрами, стандартными 32-битным регистрами, а также ячейками памяти. (Movd, Movq)
		//        punpckldq       mm0, word ptr v + 4;
				movq            mm1, mm0;   // обмен
				psrld           mm0, 1;     // v >> 1     psrld    PSLLDQ
				pand            mm0, mm5; // (v >> 1) & 0x55555555
				psubd           mm1, mm0;   // w = v - ((v >> 1) & 0x55555555)
				movq            mm0, mm1;   // w
				psrld           mm1, 2;     // w >> 2
				pand            mm0, mm6; // w & 0x33333333
				pand            mm1, mm6; // (w >> 2)  & 0x33333333
				paddd           mm0, mm1;   // x = (w & 0x33333333) + ((w >> 2) & 0x33333333)
				movq            mm1, mm0;   // x
				psrld           mm0, 4;     // x >> 4
				paddd           mm0, mm1;   // x + (x >> 4)
				pand            mm0, mm7; // y = (x + (x >> 4) & 0x0F0F0F0F)
				pxor            mm1, mm1;  // Исключающее ИЛИ == 1
				psadbw          mm0, mm1;
				movd            eax, mm0;
//				mov             Sum, eax ;   ////////////////////////////

				//заносим сумму единиц в накопительную переменную  SumBitOn
				add             eax, SumBitOff  //SumBitOn=SumBitOn & 0x7F;  // 127 Обнуляем старшие разряды, содержащие "мусор"
				mov             SumBitOff, eax
				emms;
			   // emms; команда обеспечивает переход процессора от исполнения MMX-команд


// PSADBW rxmm1, rxmm2/m128
// psadbw Действие: для каждой пары байт двух упакованных учетверенных слов операндов источник и приемник вычислить модуль разности,
//  после чего сложить полученные модули. Результат записать в младшее слово каждого из двух упакованных учетверенных слов приемника,
//  старшие три слова в упакованных учетверенных словах приемника обнулить. Принцип работы программы поясняет схема ниже.
 } // __asm
					// Регистровые суммы маски mask32 по  X    //0xFFFFFFFF
					//Sb-=(Sb >> 1) & 0x55555555;                // 2-битовые ячейки
					//Sb=(Sb & 0x33333333) + ((Sb >> 2) & 0x33333333); // 4-битовые
					//Sb=(Sb + (Sb >> 4)) & 0x0F0F0F0F;                // 8-битоовые
					//Sb+=Sb >> 8;                               // 16-битовые
					//Sb+=Sb >> 16;                              // 32-битовая ячейка
					//SumBitOff+=Sb & 0x3F;  // 63 Обнуляем старшие разряды, содержащие "мусор"
				 }
			   } // m
			   // максимальная сумма по всей площади скана
			   DP("SumBitOn="<<SumBitOn<<" SumBitOff="<<SumBitOff<<END);

			   deltaSum=SumBitOn-SumBitOff;
			   if(deltaSum<0){deltaSum=0;}
			   if( deltaSum >= SumBtMax ) { SumBtMax=deltaSum; *maxX=x; *maxY=y; }
			   //DP("SumBitOn="<<SumBitOn<<" SumBitOff="<<SumBitOff<<" SumBtMax"<<SumBtMax<<
			   //" sx0="<<sx0<<" sx1"<<sx1<<" sy0="<<sy0<<" sy1"<<sy1<<END);
			   BolS[d]=deltaSum;  d++; // DM(SumBitOn<<" ";)    SumBitOn
#ifdef DEBUGLVL
//if(drawDataRGB[0][y][x-32])drawDataRGB[0][y][x-32]=
//drawDataRGB[0][y][x-32] - ((SumBitOn+4)<<24); // - SumBitOn*0.7-20;  // (SumBit/4)  //  drawDataRGB[0][y][x]*=0xff00ff;
#endif
			 } // y
		 } // x

// число белых пикселей на вершине +4  //  454==SumBtMax;


#ifdef DEBUGLVL_RGB	
//if( GrafT[2][1] ) {
		d=0;
		 for ( x=sx0; x < sx1; x++ ) {
			 p=x*nr;
			 for ( y=sy0; y < sy1; y++ ) {
			  if(drawDataRGB[0][y][x-32])drawDataRGB[0][y][x-32]=
			  drawDataRGB[0][y][x-32] - ((BolS[d]+4)<<8)/(mask32[0].NMask+1); // - s*0.8-20  (SumBit/4)  SumBtMax
			  d++;
				 } // y
		 } // x
#endif
//	}
/**/

DP(" SumBtMax="<<SumBtMax<<" mask32[0].NMask"<<mask32[0].NMask<<END);
//SH(SumBtMax); SH(SumBtMaxOff); SH(" ");

			  // Индикаторы цифровые //
//if( GrafT[2][1] ) {
//			  DM(END);
//			  DM(END);  // TABL
//			  for ( x=0; x < ncVnr; x++ ) {
//				 if(bits_data[x]==1){DM("1");}else{DM(".")}
//				 if ((x+1)%mW==0)DM(END);
//			  }
//			  DM(END);
// }


///TIME_PRINT
//DM(END); DM(mH<<" mH "); DM(wVh<<" wVh "); DM(SumBtMax<<" SumBtMax "); DM(END);
//DM(" TIME_PRINT setMatrixCorrelation TEST"); DM(END);



  //  освобождение памяти
	if ( BolS !=NULL ) free(BolS);



if(SumBtMax<1||mask32[0].NMask<1)return 0;


			 maxX=maxX - border - 32;

			 maxY=maxY - border;

correlation=SumBtMax*100/mask32[0].NMask;

//DP("//__correlation="<<correlation<<END);
return correlation;
// визуализация // 255 << 24; черный // 255 << 16; G  // 255 << 8; R  // 255; B //
}//_____________________________________________________________________________

/**/
