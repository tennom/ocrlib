							 // STARTING //
// ---------------------------------------------------------------------------//

// --- Matrix_Starting --- GBitsetMatrix_Starting.h ---
// Подпрограмма управления последовательностью выполнения всех подпрограмм.

// ---------------------------------------------------------------------------//

//void GBitsetMatrix::pageStringDetector(vector<stringOCR>&strArray_){
void GBitsetMatrix::Matrix_Starting(vector<stringOCR>&strArray_,glyphOCR *aliKali_, int stringNum_){
  int y,x;

  strArray=&strArray_;
  stringNum=stringNum_;
  aliKali=aliKali_;


  //aliKali - указатель на массив букв (база букв).
  //aliKali[0].alLetterCount - количество букв в базе
  //BitMask32 *mask=&aliKali[0][1].mask32[0];  -- указатель на первую маску во второй букве базы
  //aliKali[0][1].mask32Count - количество масок во второй букве базы

  // resize(ncnr) векторных массивов сделан в Bitset_base.h

//TIME_START
															 /////////


GrafT[0][0]=1;
if( GrafT[0][0] ) {
DM(END); DM(END); DM(END);  DM(0000<<" SUMM_Matrix_Starting_SUMM " );
DM(END); DM(ncolumns<<" ncolumns "); DM(nrows<<" nrows "); DM(ncnr<<" ncnr ");
						 DM(END);
}
			  // обнуление массива GrafT
			  for ( x=0; x < 32; x++ ){
				  for ( y=0; y < 16; y++ ) { GrafT[x][y]=0; }
			  } // x=0

 // ключ к запуску графики в подпрограммах
 // GrafT[M][N]=1;  M - номер подпрограммы с активной графикой  (0-31)
 //                 N - разновидность активной графики подпрограммы (0-15)
 //                 1, 0 - соответственно; выводится, не выводится на экран графика




		   // Подпрограмма чистки (border) входного однобитового массива. ВХОД
				  GrafT[15][0]=1; GrafT[15][1]=0;

				 //data_null_border();
				 // затирает мусор с краев скана + border


		   // Запуск подпрограммы для получения единичных битов в числе.
				   GrafT[2][0]=1; GrafT[2][1]=1;  GrafT[2][2]=0;  GrafT[2][3]=0;

				   //unsigned int Sbits=0;

		  //		   bitsCountA( Sbits );

		   //		   bitsCountB( Sbits );

					  //letterRecognition();

///		    	   bitsCountC();   /////

//		  		   bitsCountD( Sbits );

/*
		   // Подпрограмма структурализации букв.
				   GrafT[8][0]=1;  GrafT[8][1]=0;
				 StructureWorld();
				 // получили основу букв

		   // Набор подпрограмм тестирования алгоритмов.
				   startTest();
*/

//****************************************************************************//
	   // Визуализация букв темно синими квадратиками из структур //
////				wordDraw(0x00AA0011);    // темно синий

//****************************************************************************//


/**/

//TIME_PRINT

////////////////////////////////////////////////////////////////////////////////


/*
// Распаковка битовой маски из массива 32 int  в массив 1024 bool

//int y,x;
int d,s,w=32;  // (w=64;)
unsigned int MascInt[32];     // битовая маска OnOff 32*32, упакованная в массив 32 int
bool MascBool[1024]; // битовая маска OnOff 32*32, упакованная в массив 1024 bool


			// TEST,  квадрат 32*32   15 и 16  строки состоят из единиц и т.д.
			for( x=0; x < w; x++ ){ MascInt[x]=0; }
			for( x=0; x < w*w; x++ ){ MascBool[x]=0;}
			MascInt[0]=0x000000FF;   MascInt[1]=1<<1;   MascInt[2]=2;
			MascInt[15]=MascInt[16]=0xFFFFFFFF;    MascInt[31]=1<<31;

			MascInt[31]=1; MascInt[0]=1<<31;

			// 11111111000000000000000000000000
			// 01000000000000000000000000000000
			// 01000000000000000000000000000000
			// ................................
			// 00000000000000000000000000000000
			// 11111111111111111111111111111111
			// 11111111111111111111111111111111
			// 00000000000000000000000000000000
			// 00000000000000000000000000000000
			// ................................
			// 00000000000000000000000000000001

			// РАСПАКОВКА
// перепаковка битовой маски упакованной в массив 32 int  в массив 1024 bool
			for( y=0; y < w; y++ ){
				s=MascInt[y];   d=y*w;
				for( x=0; x < w; x++ ){
				  (MascBool[d + x])=s & 1;     s=(s >> 1); // прямой порядок пикселей
//				  (MascBool[d + w-x-1])=s & 1; s=(s >> 1); // обратный порядок пикселей
				} // x
			} // y



			  // Индикаторы цифровые 1 //
			  DM(END);  // TABL
			  for ( x=0; x < w*w; x++ ) {
				 DM(MascBool[x]<<" "); if ((x+1)%w==0)DM(END);
			  }
			  DM(END);
*/

/**/

/*
////////////////////////////////////////////////////////////////////////////////
  int szf=sizeof(int);            // szf=4;
  int ncVnr=w*w;
  int ss;
  int p=0;
  bool *BolS;
  unsigned int *StrM;
  // запрос памяти
  BolS=(bool*)farcalloc(ncVnr+64, 1);
  StrM=(unsigned int*)farcalloc(ncVnr+64, szf);     // Маска

  // выход в случае отсутствия свободной памяти запрашиваемого размера
  if (BolS==NULL) {DM("BolS"); exit (1);}
  if (StrM==NULL) {DM("StrM"); exit (1);}


			// РАСПАКОВКА
// перепаковка битовой маски упакованной в массив 32 int  в массив 1024 bool
			for( y=0; y < w; y++ ){
				s=MascInt[y];   d=y*w;
				for( x=0; x < w; x++ ){
				  (BolS[d + x])=s & 1;    s=(s >> 1);
				} // x
			} // y



			  // Индикаторы цифровые 1 //
			  DM(END);  // TABL
			  for ( x=0; x < ncVnr; x++ ) {
				 DM(BolS[x]<<" "); if ((x+1)%w==0)DM(END);
			  }
			  DM(END); DM(END); DM(END); DM(END);


////////////////////////////////////////////////////////////////////////////////

				for( x=0; x < ncVnr; x++ ){ StrM[x]=0; }

			  // ЗАПАКОВКА
  // Запаковка битовой маски в массиве 1024 bool в массив  32 int
			  unsigned int reg=0, b;
			  for( y=0; y < w; y++ ){
				 d=y*w;
				 for ( x=0; x < w; x++ ) {
				   //reg=(reg << 1) + BolS[d + x];  // обратный порядок пикселей
					 b=(BolS[d + x])<<31; // <<31 умножение на 2 в 31 степени, >> 1 деление на 2
					 reg=b + (reg >> 1) ;           // прямой порядок пикселей
				 } // x
				StrM[y]=reg;
			  } // y


				// РАСПАКОВКА
				DM(END);
				for( y=0; y < w; y++ ){
					ss=s=StrM[y]; d=y*w;
					for( x=0; x < w; x++ ){
					   ss=ss & 0x00000001;
					//(BolS[d + w-x-1])=ss;             // обратный порядок пикселей
					  (BolS[d + x])=ss;                 // прямой порядок пикселей
					   ss=s=(s >>  1);
					}
				}


			  // Индикаторы цифровые 1 //
			  DM(END);  // TABL
			  for ( x=0; x < w*w; x++ ) {
				 DM(BolS[x]<<" "); if ((x+1)%w==0)DM(END);
			  }
			  DM(END);

  //  освобождение памяти
  if ( BolS !=NULL ) farfree(BolS);
  if ( StrM !=NULL ) farfree(StrM);

////////////////////////////////////////////////////////////////////////////////
*/



/*
			// РАСПАКОВКА
			DM(END);
			for( y=0; y < w; y++ ){
				ss=s=StrM[y]; d=y*w;
				for( x=0; x < w; x++ ){
				   ss=ss & 0x00000001;
///				  (BolS[d + w-x-1])=ss;             // обратный порядок пикселей
				  (BolS[d + x])=ss;                 // прямой порядок пикселей
				   ss=s=(s >>  1);
				}
			}
*/

/*
			// Индикаторы цифровые 1 //
			DM(END);
			for( y=0; y < w; y++ ){
				d=y*w;
				for( x=0; x < w; x++ ){
				 DM(" "<<BolS[d + x]);
				}
			  DM(END);
			}
			DM(END);
*/
}//_____________________________________________________________________________





// Подпрограмма чистки (из за border) входного однобитового массива. ВХОД
// -----------------------------------------------------------------------------
void GBitsetMatrix::data_null_border() {

  //int y,x;
  //int brd1,brd2,bit;
  //int w=ncolumns;
  //bool *d;


//----------------------------------------------------------------------------//
						 // ОБНУЛЕНИЕ //

//szf=0;       // обычно в 32р системах sfz=4=32/8;  szf=sizeof(int);
// *ImBuf=0;    // запрос памяти с очисткой 0
 ImBf=0;      // текущий размер массива ImBuf
// *ReBuf=0;    // запрос памяти с очисткой 0
 ReBf=0;      // текущий размер массива ReBuf
 m=0;         // ширина двухмерного массива (если массивы так используем)
// *BufIn=0;    // запрос памяти с очисткой 0
 BfIn=0;      // текущий размер массива ImBuf
// *BufOu=0;    // запрос памяти с очисткой 0
 BfOu=0;      // текущий размер массива ImBuf

//----------------------------------------------------------------------------//

/* */


}//_____________________________________________________________________________

////////////////////////////////////////////////////////////////////////////////




// Подсчет единичных битов в числе  AAAAAAAAAAAAAAAAAAAAAAA
// -----------------------------------------------------------------------------

void GBitsetMatrix::bitsCountA( int Sbits ) {

////////////////////////////////////////////////////////////////////////////////
//TIME_START
//TIME_PRINT
////////////////////////////////////////////////////////////////////////////////
	 // int ss[1];
	  //bool *bL,*bL1;
	  //int *q1,*q2;

	 //s=(1 << 31)-1;  DM(END); DM(s<<" s ")
	  //int sP=(1 << 30)-1;

	  //unsigned int s;
	  //int digitWrd=szf*8; // =32
	  //int w1=ncolumns/32;
	  //unsigned int *dT;
	  //unsigned short *tt;
	  //unsigned char cH[32];
	  //unsigned char *chP;



 /*  //////////////////  // TEST   int == bool>32   рабочий  в отладке

  HStr.assign(ncnr,0);   ///HStS.assign(ncnr,0);

	  int sum;
	  DM("w="<<w<<" w1="<<w1<<" nrows="<<nrows<<" ncolumns"<<ncolumns<<END);
	  for ( y=0; y < nrows; y++ ) {
		 res=0; d1=bits_data+y*w;   // ncolumns
		 for( x=0; x < w; x+=24 ){  // d2=d1+x;

			cH[0]=*((unsigned short*)(d1+x));      //DM((short)cH[0]<<" ");
			cH[1]=*((unsigned short*)(d1+x+8));    //DM((short)cH[1]<<" ");
			cH[2]=*((unsigned short*)(d1+x+16));   //DM((short)cH[2]<<" ");
			cH[3]=*((unsigned short*)(d1+x+24));   //DM((short)cH[3]<<" ");
			cH[4]=*((unsigned short*)(d1+x+32));   //DM((short)cH[3]<<" ");

			dT=(unsigned int*)cH;
			DM(*dT<<" ");

			s=s - ((s >> 1) & 0x55555555);                // 2-битовые ячейки
			s=(s & 0x33333333) + ((s >> 2) & 0x33333333); // 4-битовые
			s=(s + (s >> 4)) & 0x0F0F0F0F;                // 8-битовые
			s=s + (s >> 8);                               // 16-битовые
			s=s + (s >> 16);                              // 32-битовая ячейка
			s=s & 0x3F;         // Обнуляем старшие разряды, содержащие "мусор"

			res+=s;     //DM(s<<" ");


			//DM(*dT<<";");
			///if(*dT!=0){DM(1);}else{DM(0);}  //(s);

		 } // x
		//DM(END);
		HStr[y]=res;
		DM(" res1 "<<res); DM(END);
	  } // y



*/  //////////////////

/**/

//DM(END); DM(szf<<" szf "); DM(s<<" s "); DM(END);
}//_____________________________________________________________________________



// Подсчет единичных битов в числе  BBBBBBBBBBBBBBBBB   ++
// -----------------------------------------------------------------------------

void GBitsetMatrix::bitsCountB( int Sbits ) {

/*
 bool ch[8],*p;
 bool v=1;
 ch[0]=v; ch[1]=v; ch[2]=v; ch[3]=v; //ch[4]=v; ch[5]=v; ch[6]=v; ch[7]=v;
 p=ch;
 unsigned int *cI=( unsigned int*)p;
 unsigned int cIn;
 Sbits=cIn=*cI;

 int L= sizeof(ch);                     DM(END); DM(sizeof(ch)<<" sizeof(ch) ");
 int B= sizeof(ch[0]);                  DM(sizeof(ch[0])<<" sizeof(ch[0]) ");
 int N= sizeof(ch) / sizeof(ch[0]);     DM(N<<" N "); DM(END);
*/

/////////////////

///////


 // Класс bitset
 //count()  Количество битов, равных 1  a.count()
 // quiz1.set(27);
 bitset<32> BitVec( 0xFFFFFFFF );
 Sbits=BitVec.count();
/**/
 Sbits=0x3F; //Sbits=63;
 Sbits=0x7F; //Sbits=127;


 // Вывод на экран числа в двоичнном виде  00000000000000001111111111111111
 // http://www.softboard.ru/index.php?s=96380ba5ff201b788dc05c4a9b218058&showtopic=30685&st=120
 char str[128]; // char *string;   строка результата
 //Sbits=*cI;   // преобразуемое число
 int r=2;       // где r = radix = 2 для двоичного представления целого числа (binary number);
				// radix = 8 для восьмеричного... и т.д.

#ifdef WIN32
 ltoa(Sbits,str,r); // двоичное представление числа
#endif
	DM(END); DM(END); DM(Sbits<<" Sbits двоичное представление числа "); DM(END);
 DM(str<<""); // вывод строки двоичного представления числа
 DM(END);
/**/


			//Sbits=16843009;      // 16843009  Sbits_число  4 Sbits_N_единиц

			//Sbits=4294967295;    //@dt=  -1  Sbits_число  32 Sbits_N_единиц
			//Sbits=0xFFFFFFFF;    // -1 Sbits_число  32 Sbits_N_единиц
			//Sbits=0xFFFFFFFE;    // -2 Sbits_число  31 Sbits_N_единиц
			//Sbits=4294967295;

			//Sbits=(1 << 32)-1;

			DM(END); DM(Sbits<<" Sbits_число "); DM(END);

			Sbits=Sbits - ((Sbits >> 1) & 0x55555555);                // 2-битовые ячейки
			Sbits=(Sbits & 0x33333333) + ((Sbits >> 2) & 0x33333333); // 4-битовые
			Sbits=(Sbits + (Sbits >> 4)) & 0x0F0F0F0F;                // 8-битовые
			Sbits=Sbits + (Sbits >> 8);                               // 16-битовые
			Sbits=Sbits + (Sbits >> 16);                              // 32-битовая ячейка
			Sbits=Sbits & 0x3F;         // Обнуляем старшие разряды, содержащие "мусор"
			//return s;

			DM(END); DM(Sbits<<" Sbits_N_единиц "); DM(END);


/*
// TEST 32 единици
unsigned char cH[32];
unsigned int *dT;

cH[0]=1; cH[1]=1; cH[2]=1; cH[3]=1; cH[4]=1; cH[5]=1; cH[6]=1; cH[7]=1;
cH[8]=1; cH[9]=1; cH[10]=1; cH[11]=1; cH[12]=1; cH[13]=1; cH[14]=1; cH[15]=1;
cH[16]=1; cH[17]=1; cH[18]=1; cH[19]=1; cH[20]=1; cH[21]=1; cH[22]=1; cH[23]=1;
cH[24]=1; cH[25]=1; cH[26]=1; cH[27]=1; cH[28]=1; cH[29]=1; cH[30]=1; cH[31]=1;

DM("@dt1="<<0<<END)
dT=(unsigned int*)cH;
DM("@dt="<<*dT<<END);
*/
}//_____________________________________________________________________________




// Подсчет единичных битов в числе  CCCCCCCCCCCCCCCCCCCCCCC
// -----------------------------------------------------------------------------

void GBitsetMatrix::bitsCountC() {



  int y,x,p,d;  //  ,n,g
  unsigned int x0,x1,y0,y1;
  unsigned int s;
  int sf=szf*8;     //  sf=32,  для int=32
  unsigned int w=32, ncVnr=w*w;   // "w" размерность битовой маскиw=32     maskSize


  unsigned char *BolS;
  unsigned int *StrM,*Sbit;
  unsigned int q,*q1;

  // запрос памяти
	BolS=(unsigned char*)malloc(ncVnr+64);
  // выход в случае отсутсттвия свободной памяти запрашиваемого размера
  if (BolS==NULL) {DM("BolS"); exit (1);}


// mask32[0] - указатель на объект "маска"  в массиве mask32
// РАСПАКОВКА на экран, битовой маски, упакованной в массив 32 int
// printMask(mask32[0],c_out);

///////
/*
// Распаковка битовой маски из массива 32 int  в массив 1024 bool
unPackBitMask( mask32[0].On, BolS, w, c_out );

			  // вычисление максимальных и минимальных габаритов центральной области "ON"
			  x0=y0=128; x1=y1=0;
			  for ( y=0; y < w; y++ ) {
				p=y*w;
				for ( x=0; x < w; x++ ) {
					if( BolS[x+p] == 1 ) {
					  if( x >= x1 ) { x1=x; }   if( x <= x0 ) { x0=x; }
					  if( y >= y1 ) { y1=y; }   if( y <= y0 ) { y0=y; }
					}
				} // x
			  } // y

			  // dlt отступ от края центральной области "ON" влево, вправо, в верх, в низ.
			  int dlt=2;  if( dlt < 1 ) { dlt=1; }
			  x0=x0-dlt;  x1=x1+dlt+1;  y0=y0-dlt;  y1=y1+dlt+1;
			  // ограничения
			  if( x0 <= 0 ) { x0=0; }    if( x1 >= w ) { x1=w; }
			  if( y0 <= 0 ) { y0=0; }    if( y1 >= w ) { y1=w; }

			  // формирование перефирийной области  "Off"
			  for ( y=y0; y < y1; y++ ) {
				p=y*w;
				for ( x=x0; x < x1; x++ ) {
					BolS[x+p]=1-BolS[x+p];
				} // x
			  } // y


			  DM("bitsCountCCC входной массив 1024"<<END);
			  DM(END);  // TABL
			  for ( x=0; x < ncVnr; x++ ) {
				 DM((int)BolS[x]<<""); if ((x+1)%w==0)DM(END);  // nc
			  }
			  DM(END);

			  packBitMask(mask32[0].Off,BolS, w,c_out);
*/

/*
DM(" TIME_START CCCCCCCCCCCCCCCCCCCCCCC  ");
///			  printMask(mask32[0], c_out);

//  unsigned char MaskDest[1024];    MaskInt=srcMask[0].Off;
//		unsigned int mHor[32];
//		unsigned int mVer[32];

///////
  MaskBuf[128];
  int wr=32, wc=32; // wr(8-96) высота и wc (32) ширина (габарит) битовой
					// маски перефирийной области  "Off"
  int wrH=32, wcV=32;
  int dlt=4;            // толщина стенок перефирийной области  "Off"
  d=dlt;

			 //memset(Off,0,128);  "ON" в маске  (центральная область)

			 // формирование левой и правой части перефирийной области  "Off"   // ^   | | | |
			 for ( y=0; y < wr; y++ ) {
				 s=mask32[0][0].On[y];
				 mask32[0][0].mHor[y]=mask32[0][0].Off[y]=~s & ((s >> d) | (s << d));
			 }

			 // формирование нижней части перефирийной области  "Off"
			 for ( y=d; y < wr; y++ ) {
				 mask32[0][0].mVer[y-d]=mask32[0][0].Off[y-d]=
				 mask32[0][0].Off[y-d] | mask32[0][0].On[y];
			 }

			 // формирование верхней части перефирийной области  "Off"
			 for ( y=wr-d; y > 0; y-- ) {
				  mask32[0][0].mVer[y+d]=mask32[0][0].Off[y+d]=
				  mask32[0][0].Off[y+d] | mask32[0][0].On[y];
			 }



			 // удаление центральной области  "On"
			 for ( y=0; y < wr; y++ ) {
				 mask32[0][0].Off[y] =~mask32[0][0].On[y] & mask32[0][0].Off[y];
				 //mask32[0][0].mVer[y]=~mask32[0][0].On[y] & mask32[0][0].mVer[y];
				 //mask32[0][0].mHor[y]=~mask32[0][0].On[y] & mask32[0][0].mHor[y];
			 }



			  // РАСПАКОВКА на экран, битовой маски, упакованной в массив 32 int
///			  printMask(mask32[0][0].Off, c_out);
			  printMask(mask32[0], c_out);

//////

DM(" TIME_PRINT CCCCCCCCCCCCCCCCCCCCCCC  "); DM(END);
 */

////////////////////////////////////////////////////////////////////////////////

int wr=32, dlt;
//unsigned int s;

unsigned int BufOff[128];
memset(BufOff,0,128);  // обнуление   char

int Ntest=32*16;
unsigned char BufOn[32*16];
unsigned int Test[32*16]={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};




//			  packBitMask (Test, BufOn, 32,16, c_out);
// Запаковка битовой маски в массиве 1024 BolS в массив  32 bit,   wr !=32
//			  packBitMask(mask32[0].Off, BolS, mW, mH, c_out);


				 for ( x=0; x < Ntest; x++ ) {
//				   mask32[0][0].On[x]=BufOn[x];
				 }
/*
			  // автоматическое опреденение размера маски (по габаритам буквы)
			  ///int x0,x1,y0,y1;  // габариты буквы
			  ///dlt=0.3*(x0-x1+y0-y1)/2; // часть среднего размера буквы

			  // внешний размер маски Off на dlt пикселей больше маски On
			  dlt=4;   //  1 <= dlt <=5

			  // формирование обтекающей перефирийной области  "Off"
			  MatrixT( mask32[0][0].On, mask32[0][0].Off, wr, dlt );

			  // формирование прямоугольной перефирийной области  "Off"
//			  setOnOffInMask(mask32[0], dlt, c_out);               // mask32[0]
			  //  setOnOffInMask(&mask,2,c_out);

///			  printMask( mask32[0][0].Off, c_out );

			  // получение маски переходной области между "On" и "Off"
			  // ширина переходной области между "On" и "Off"  =abc(dlt+dlt)
			  dlt=-1;  //  -2 <= dlt <=-1   // автоопреденение  dlt=-dlt/2;
			  MatrixT( mask32[0][0].On, BufOff, wr, dlt );

			 // формирование центральной  области  "On"  без переходной области
			 // формирование перефирийной области  "Off" без переходной области
			 for ( y=0; y < wr; y++ ) {
				 s=~BufOff[y];
				 mask32[0][0].On[y] =mask32[0][0].On[y]  & s;
				 mask32[0][0].Off[y]=mask32[0][0].Off[y] & s;
			 }
			 printMask( mask32[0], c_out );

					  //printMask( BufOff, c_out );
*/
/**/

  //  освобождение памяти
	if ( BolS !=NULL ) free(BolS);
  //if ( StrM !=NULL ) farfree(StrM);
  //if ( Sbit !=NULL ) farfree(Sbit);
  //if ( Ssss !=NULL ) farfree(Ssss);

//for ( y=0; y < wr; y++ ) { BufOn[y]=mask32[0][0].On[y]; }

////////////////////////////////////////////////////////////////////////////////
/*
  //Sb=Sbit[m+p+1]<<32 + Sbit[m+p];       // <<31 умножение на 2 в 31 степени
  Sb -= (Sb >> 1) & 0x5555555555555555;
  Sb = (Sb & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
  Sb = (Sb + (Sb >> 4)) & 0x0f0f0f0f0f0f0f0f;
  Sb += Sb >>  8;
  Sb += Sb >> 16;
  Sb += Sb >> 32;
  Sb=Sb & 0x7F;  // 127 Обнуляем старшие разряды, содержащие "мусор"
  SumBit+=Sb;
*/
////////////////////////////////////////////////////////////////////////////////

}//_____________________________________________________________________________

/*
					//TTTTTTTTTTTTTTTTTTTTT

// -----------------------------------------------------------------------------
void GBitsetMatrix::MatrixT(unsigned int *BufOn,
							unsigned int *BufOff,
							int wr, int dlt) {

  // wr(8-96)=32  высота и wc (32) ширина (габарит) битовой
  // маски перефирийной области  "Off"
  // "ON" в маске  (центральная область)

  int d=dlt;          // dlt толщина стенок перефирийной области  "Off"
  unsigned int y,x,s;



DM(" TIME_START TTTTTTTTTTTTTTTTTTTTT  ");


   // формирование обтекающей перефирийной области  "Off"
   if( d > 0 ) {
			 if ( d < 0 )  d=0;   if ( d > 5 )  d=5;

			 // формирование левой и правой части перефирийной области  "Off"
			 for ( y=0; y < wr; y++ ) {
				 s=BufOn[y];
				 BufOff[y]=~s & ((s >> d) | (s << d));
			 }

//			 for ( y=d;  y < wr-d;  y++ ) { BufOff[y]=BufOff[y] | BufOn[y+d] ^ BufOn[y-d]; }

			 // формирование нижней части перефирийной области  "Off"
			 for ( y=d;  y < wr;  y++ ) { BufOff[y-d]=BufOff[y-d] | BufOn[y] | BufOff[y]; }

			 // формирование верхней части перефирийной области  "Off"
			 for ( y=wr-d; y > 0; y-- ) { BufOff[y+d]=BufOff[y+d] | BufOn[y] | BufOff[y]; }

			 // удаление центральной области  "On"
			 for ( y=0; y < wr; y++ ) { BufOff[y]=~BufOn[y] & BufOff[y]; }

   } // if


   // формирование переходной области между "On" и "Off"
   if( d < 0 ) {
			 if ( d > -1 ) d=-1;  if ( d < -2 ) d=-2;     d=-d;

			 // формирование левой и правой части переходной области между "On" и "Off"
			 for ( y=0; y < wr; y++ ) {
				 s=BufOn[y];      BufOff[y]=((s >> d) ^ (s << d));
			 }

			 // формирование верхней и нижней части переходной области между "On" и "Off"
//			 for ( y=d;  y < wr-d;  y++ ) { BufOff[y]=BufOff[y] | (BufOn[y+d] ^ BufOn[y-d]); }

			 // формирование верхней и нижней части переходной области между "On" и "Off"
			 for ( y=0;  y < wr-d;  y++ ) {
				 BufOff[y]=BufOff[y] | (BufOn[y+d] ^ BufOn[y]);
			 }

			 // формирование верхней и нижней части переходной области между "On" и "Off"
			 for ( y=wr; y >= d; y-- ) {
				 BufOff[y]=BufOff[y] | (BufOn[y-d] ^ BufOn[y]);
			 }

   } // if



DM(" TIME_PRINT TTTTTTTTTTTTTTTTTTTTT  "); DM(END);

//			 for ( y=wr-d; y > 0; y-- ) { BufOff[y+d]=BufOff[y+d] | BufOn[y]; }
////////////////////////////////////////////////////////////////////////////////

// ^ // ~s & // ||  //  ss=(s << d);

			  // РАСПАКОВКА на экран, битовой маски, упакованной в массив 32 int
//            printMask(mask32[0], c_out);

// memset(BufOff,0,128);  // обнуление

			 // формирование верхней части перефирийной области  "Off"
///			 for ( y=wr-d; y > 0; y-- ) { BufOff[y+d]=BufOff[y+d] | BufOn[y];
//			      BufOff[y+d]=BufOff[y+d] | BufOn[y];
///			 }

			 // удаление центральной области  "On"
///			 for ( y=0; y < wr; y++ ) { BufOff[y]=~BufOn[y] & BufOff[y]; }

}//_____________________________________________________________________________

 */
/**/



// Подсчет единичных битов в числе  DDDDDDDDDDDDDDDDDDDDDDDDDD
// -----------------------------------------------------------------------------

void GBitsetMatrix::bitsCountD( int Sbits ) {

 // mask32[mask32count-1]  верхняя маска в массиве
 // unsigned int *pOn=mask32[0].On     - -указатель на данные в маске "On"
 // unsigned int *pOff=mask32[0].On     - -указатель на данные в маске "Off"
 // mask32 - массив который содержит объекты BitMask32 в качестве элементов
 // mask32count - это счетчик массива масок mask32
 //mask32[0] - указатель на объект "маска"  в массиве mask32
 //mask32[0].On - так мы получаем указатель на конечные данные "ON" в маске  (центральная область)
 //mask32[0].Off - так мы получаем указатель на конечные данные "OFF" в маске  (переферийная область)
 //mask32[1].On  - а это указатель на данные в следующей маске в массиве  (результат1)
 //mask32[2].Off  - а это указатель на данные в следующей маске в массиве  (результат2)
 //mask32[2].On[x]- значение х- "On" элемента в int маске.  тоже и pOn[x]

 // printMask(mask32[1],32,c_out);   -  печатает маску mask32[1]
 // MouseEvents//


  // MaskInt вых  int maskSize 32.64

  int y,x,n,m,p;
  int nc=ncolumns, nr=nrows;  // SH(ncolumns);  SH(nrows);
  int ncVnr=nc*nr;
  int wr=32, wc=32; // wr(8-96) высота и wc (32) ширина (габарит) битовой
					// маски перефирийной области  "Off"

  unsigned int Sb,SumBit,SumBtMax;
  int sf=szf*8;  //  sf=32,  для int=32    // ncolumns;  nrows;

  unsigned char *BolS;
  unsigned int *StrM,*SInt;

  // запрос памяти
	BolS=(unsigned char*)malloc(ncVnr+64);      // lng=sizeof(*BolS);  DM(lng<<" BolS ");
	StrM=(unsigned int*)malloc((ncVnr+64)*4);     // Маска
	SInt=(unsigned int*)malloc((ncVnr+64)*4);     // Бордер вокруг маски

  // выход в случае отсутствия свободной памяти запрашиваемого размера
  if (BolS==NULL) {DM("BolS"); exit (1);}
  if (StrM==NULL) {DM("StrM"); exit (1);}
  if (SInt==NULL) {DM("SInt"); exit (1);}

  //printMask(mask32[0],c_out);         DM(END);DM(END);
  DM(" TIME_START DDDDDDDDDDDDDD  ");

			  // обнуление BolS, StrM
			  // memset(BolS,0,ncVnr/8);
			  for ( x=0; x < ncVnr; x++ ) { BolS[x]=0; StrM[x]=SInt[x]=0; }


			  // TEST  дельта функция
			  //BolS[ncVnr/2+nc/2]=1;
/*
			  for ( m=0; m < wr; m++ ) mask32[0][0].On[m]=0;
			  mask32[0][0].On[m/2]=1;
*/

/*			  // TEST  квадрат 32*32  (sf*sf) из 1
			  int sVs=8;
			  int  smY=(nr - sVs)/2,  smX=(nc - sVs)/2;
			  for ( y=smY; y < smY + sVs; y++ ) {
				p=y*nc;
				for ( x=smX; x < smX + sVs; x++ ) {
					BolS[p+x]=1;   //DM(*d2);
#ifdef DEBUGLVL
if( GrafT[2][1] ) {
	//drawData[0][y][x]*=0.8;
	drawDataRGB[0][y][x]=0x0000ff00;  // 0x00ffff    //drawDataRGB[0][y][x]*=0xff00ff;
	}   // визуализация цветом ////
#endif
				}
			  }
*/

//	unPackBitMask(mask32[0][0].On, BolS, 32, c_out);


						// РАСПАКОВКА
// перепаковка битовой маски упакованной в массив 32 int  в массив 1024 bool
			int d=0, count=0, s;
			int  smY=border+4,  smX=border+4;
			for( y=smY; y < smY+32; y++ ){
				s=mask32[0][0].On[d]; d++; p=y*nc;
				for( x=smX; x < smX+32; x++ ){
				  //BolS[p + x]=s & 1;   s=(s >> 1); // прямой порядок пикселей
				  BolS[p + nc-x]=s & 1;  s=(s >> 1); // обратный порядок пикселей
///				  if(BolS[p + x]==1)count++;
				} // x
			} // y
///			SH(count);

/**/

/*
			  DM(END);  // TABL
			  for ( x=0; x < nr*nc; x++ ) {
				 if(BolS[x]==1){DM("1");}else{DM(".")}
				 if ((x+1)%nc==0)DM(END);
			  }
			  DM(END);
*/


			  // переупаковка сдвигом массива горизонтальных строк BolS
			  unsigned int reg=0;
              // обратный порядок пикселей
			  for ( x=0; x < ncVnr; x++ ) { StrM[x]=reg=(reg << 1)+ BolS[x];
//				 if(StrM[x]>0){drawDataRGB[0].int_data[x]=drawDataRGB[0].int_data[x]<<8;}
			  }
/*
			  // прямой порядок пикселей
			  //for ( x=0; x < ncVnr; x++ ) { SInt[x]=reg=(reg >> 1) + ((BolS[x])<<31); }
			  // <<31 умножение на 2 в 31 степени, >> 1 деление на 2
*/

			  // переупаковка всего массива горизонтальных строк StrM в массив вертикальные строк Sbit
			  p=0;
			  for ( x=0; x < nc; x++ ) {
				for ( y=0; y < ncVnr; y+=nc){
					//if(SInt[p]>0){drawDataRGB[0].int_data[x+y]=drawDataRGB[0].int_data[x+y]<<8;}
					SInt[p]=StrM[x+y];  p++;
				}
			  }



///	  for ( n=0; n < 1000; n++ ) { // 1000   // 100 000 000

	  // Скольжжение маски по всей nc*nr площади скана.
	  SumBtMax=0;
	  for ( x=32; x <nc-32; x++ ) {        //бордюр в 32 пиксела с краев каждого ряда содержит мусор
		 p=x*nr;
		 for ( y=32; y < nr-32; y++ ) {
			   SumBit=0;
			   // Суммы маски mask32 по  Y
			   for ( m=0; m < wr; m++ ) {
					// Умножение маски на транспонированный скан SInt
					Sb=SInt[y+p+m] & mask32[0][0].On[m];
					// Регистровые суммы маски mask32 по  X    //0xFFFFFFFF
					Sb-=(Sb >> 1) & 0x55555555;                // 2-битовые ячейки
					Sb=(Sb & 0x33333333) + ((Sb >> 2) & 0x33333333); // 4-битовые
					Sb=(Sb + (Sb >> 4)) & 0x0F0F0F0F;                // 8-битоовые
					Sb+=Sb >> 8;                               // 16-битовые
					Sb+=Sb >> 16;                              // 32-битовая ячейка
					SumBit+=Sb & 0x3F;  // 63 Обнуляем старшие разряды, содержащие "мусор"
			   } // m
			   //  ммакксимальная сумма по всей площади скана
			   if( SumBit >= SumBtMax ) { SumBtMax=SumBit; }
#ifdef DEBUGLVL_RGB
//if( GrafT[2][1] ) {
   drawDataRGB[0][y][x-32]=drawDataRGB[0][y][x-32] - SumBit*0.7; // (SumBit/4)
//	}                                      //  drawDataRGB[0][y][x]*=0xff00ff;
#endif
		 } // y
	  } // x

///	  } // n

/**/


/*
			  // TEST  дельта функция
			  for ( m=0; m < wr; m++ ) mask32[0][0].On[m]=0;
			  mask32[0][0].On[m/2]=1;
*/
//---------------
/*	  // Скоольжение маски по всей площади скана.
	  SumBtMax=0;
	  for ( y=0; y < nr-32; y++ ) {
			 //p=y*nc;
			 for ( x=32; x <nc-32; x++ ) {
			   SumBit=0;
			   // Суммы маски StrM по  Y
			   for ( m=0; m < wr; m++ ) {
					// Умножение маски на скан SInt
					Sb=SInt[x+(y+m)*nc] & mask32[0][0].On[m];  // [x+p+m*nc]   // [x+(y+m)*nc]
					//	  Sb=0xFFFFFFFF & mask32[0][0].On[m];  //  0xFFFFFFFF
					// Суммы маски StrM по  X
					Sb-=(Sb >> 1) & 0x55555555;                // 2-битовые ячейки
					Sb=(Sb & 0x33333333) + ((Sb >> 2) & 0x33333333); // 4-битовые
					Sb=(Sb + (Sb >> 4)) & 0x0F0F0F0F;                // 8-битоовые
					Sb+=Sb >> 8;                               // 16-битовые
					Sb+=Sb >> 16;                              // 32-битовая ячейка
					SumBit+=Sb & 0x3F;  // 63 Обнуляем старшие разряды, содержащие "мусор"
			   } // m
			   // Суммы маски StrM по X и Y
			   if( SumBit >= SumBtMax ) { SumBtMax=SumBit; }
#ifdef DEBUGLVL
//if( GrafT[2][1] ) {
   //drawDataRGB[0][y][x]=drawDataRGB[0][y][x] - 256*SumBit/(SumBtMax+1);  // 1024*SumBit/(SumBtMax+1)  (SumBit/4)  drawDataRGB[0][y][x]*=0xff00ff;
   drawDataRGB[0][y][x-32]=drawDataRGB[0][y][x-32] - SumBit*0.7;  // 1024*SumBit/(SumBtMax+1)  (SumBit/4)  drawDataRGB[0][y][x]*=0xff00ff;
   //	}
#endif
			} // y
		 } // x
//---------------
*/

// визуализация  255 << 24; черный //  255 << 16; G  //  255 << 8; R  //  255; B

DM(END);  DM(SumBtMax<<" SumBtMax ");  DM(END);


			  // Индикаторы цифровые //
			  //DM(END);  DM(ncVnr<<" ncVnr ");  DM(nc<<" nc ");

			  DM(END);  // TABL
			  for ( x=0; x < nr*nc; x++ ) {
				 if(BolS[x]==1){DM("1");}else{DM(".")}
				 if ((x+1)%nc==0)DM(END);
			  }
			  DM(END);
/**/

/**/
DM(" TIME_PRINT DDDDDDDDDDDDDD  "); DM(END);

  //  освобождение памяти
	if ( BolS !=NULL ) free(BolS);
	if ( StrM !=NULL ) free(StrM);
	if ( SInt !=NULL ) free(SInt);

	
////////////////////////////////////////////////////////////////////////////////
/*
  //Sb=Sbit[m+p+1]<<32 + Sbit[m+p];       // <<31 умножение на 2 в 31 степени
  Sb -= (Sb >> 1) & 0x5555555555555555;
  Sb = (Sb & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
  Sb = (Sb + (Sb >> 4)) & 0x0f0f0f0f0f0f0f0f;
  Sb += Sb >>  8;
  Sb += Sb >> 16;
  Sb += Sb >> 32;
  Sb=Sb & 0x7F;  // 127 Обнуляем старшие разряды, содержащие "мусор"
  SumBit+=Sb;
*/
////////////////////////////////////////////////////////////////////////////////


/*
DM(END);
TIME_START

			   for ( y=0; y < nrows; y++ ) {
					d1=A+y*ncolumns;
				  for ( x=0; x < ncolumns; x++ ) {
					 Ssss[x]=*(d1+x);   // d2=d1+x; d=*d2-*(d2+2); resD+=d;    // (d2+1)  //d=*(d1+x);
				  }
				  // сглаживание, полосовой фильтр   filterLaplasStM
				  filterLaplasStM(Ssss,Ssss,ncolumns,4,12); //  KHigS,KLowS //int KLowS=KHigS*3;
				}

TIME_PRINT
 DM(" TIME_PRINT n1  "); DM(END);
*/

			 // обнуление StrM ( где StrM глобальные )
			 // memset(StrM,0,szf*(ncVnr+64));
}//_____________________________________________________________________________




// -----------------------------------------------------------------------------
int GBitsetMatrix::setMatrixCorrelation_WORK(GBitmap *img, GBitMask32 *mask32_){

int correlation=0;
// img - исходное изображение для примениения маски
// mask32  - маска которая применяется по всей площади img (поиск точки)
mask32[0]=mask32_;
//line=img;
//Matrix_Starting(*strArray);
//printMask(&mask32,c_out);


//line->rows()
//line->columns()
//line->byts_data[x]


return correlation;
}//_____________________________________________________________________________


