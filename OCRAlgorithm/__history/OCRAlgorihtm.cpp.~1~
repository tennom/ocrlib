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

#include "OCRAlgorihtm.h"

namespace ocr{

// ----- constructor and destructor
//________OCRFilter_________________
OCRFilter::~OCRFilter(){}

OCRFilter::OCRFilter(int size){
	szf=sizeof(int);            // szf=4;
	ncnr=size;     ///<создаем размерность буферных массивов

	ImBuf=(int*)malloc((ncnr+512+16)*szf);
	ReBuf=(int*)malloc((ncnr+512+16)*szf);
	BufIn=(int*)malloc((ncnr+512+16)*szf);
	BufOu=(int*)malloc((ncnr+512+16)*szf);
///////////////////////////////////////

  // выход в случае отсутствия свободной памяти запрашиваемого размера
  if (ImBuf==NULL) {DM("ImBuf");exit (1);}
  if (ReBuf==NULL) {DM("ReBuf");exit (1);}
  if (BufIn==NULL) {DM("BufIn");exit (1);}
  if (BufOu==NULL) {DM("BufOu");exit (1);}
}


//-------------------------------АЛГОРИТМЫ------------------------------------//

// -----------------------------------------------------------------------------
// ++++++
// ФИЛЬТР НИЗКИХ ЧАСТОТ  (ГАУССИАН - Gaussian), попытка минимальной реализации.
// Адаптивный F(KHig) нолевой бордюр вокруг массивов.
// 2 массива
// -----------------------------------------------------------------------------
	// треугольная весовая функция
	// y(n)= -y(n-2)+2y(n-1)+x(n-2k-2)-2x(n-k-1)+xn

 void OCRFilter::filterHigh(vector<int> &In, int KHig){
 int y,Khg;
 int size=In.size();
 //if(size>ncnr) return;

 //////////////////////////////////////////////  всего 2 массива

 if ( KHig<2 ) KHig=1;   if ( KHig>80 ) KHig=80;   // if ( KHig>63 ) KHig=63;
 // для фильтра низких частот  KhgN=KHig*N+1 ,  при KHig=64 :
 //      129           257             385
 int  s2=KHig*2+1,  s4=KHig*4,    s6=KHig*6+1;

// vector<int> BufIn(size+s6);
// vector<int> lt1(size+s6);
// int BufIn[10000]={0};
// int lt1[10000]={0};

	  // обнуление ImBuf,ReBuf ( где ImBuf,ReBuf глобальные )
	  memset(ImBuf,0,4*(ncnr+512));      memset(ReBuf,0,4*(ncnr+512));
	  //for ( y=0; y < size+s6; y++ ){BufIn[y]=lt1[y]=0;}

	  // Входной буфер BufIn[y+s2], In[y]
	  for ( y=0; y < size; y++ ){ImBuf[y+s2]=In[y];}
	  Khg=KHig*KHig;
	  for ( y=s2; y < size+s4; y++ ) { //прямоугольная весовая функция, прямая фильтрация
		 ReBuf[y]=-ReBuf[y-2]+2*ReBuf[y-1]+ImBuf[y-KHig-KHig]-2*ImBuf[y-KHig]+ImBuf[y]; //k=15+
	  }
	  for ( y=s2; y < size+s4; y++ ) { ReBuf[y]=ReBuf[y]/Khg;  ImBuf[y]=0; } // Norm // y=0; size+s6;
	  // memset(ImBuf,0,4*(ncnr+512));
	  for ( y=size+s4; y > s2; y-- ) { //прямоугольная весовая функция, инверсная фильтрация
		 ImBuf[y]=-ImBuf[y+2]+2*ImBuf[y+1]+ReBuf[y+KHig+KHig]-2*ReBuf[y+KHig]+ReBuf[y];//k=15-
	  }
	  for ( y=s2; y < size+s2; y++ ) { In[y-s2]=ImBuf[y]/Khg; }
	  // Выходной буфер In[y-s2]
/**/

}//_____________________________________________________________________________

// -----------------------------------------------------------------------------
// ++++++
// Полосовой фильтр Гауссиан (ГАУССИАН - Gaussian), попытка минимальной реализации.
// Входной буфер &In. Адаптивный F(KHig) нолевой бордюр вокруг массивов
// 4 массива
// -----------------------------------------------------------------------------

 void OCRFilter::filterLaplasian( vector<int> &In, int KHig, int KLow){  // filterLaplasianM1
 int y,Khg,Klw,S;
 int size=In.size();

 int KHigh=KHig; // заплатка - запрет на модификацию KHig
 if ( KHig<2 ) KHig=1;   if ( KHig>63 ) KHig=63;
 if ( KLow<2 ) KLow=2;   if ( KLow>63 ) KLow=63;
 S=KLow;  if ( S < KHig ) S=KHig;
 // Sn=129        257        385         514        при S=64,   SN=KHig*N+1
 int   S2=S*2+1,  S4=S*4+1,  s6=S*6+1,   S8=S*8+2;

///////////////

// обнуление BufIn,ImBuf,ReBuf,BufOu ( где BufIn,ImBuf,ReBuf,BufOu глобальные )
		memset(BufIn,0,4*(ncnr+512));   memset(BufOu,0,4*(ncnr+512));
		memset(ReBuf,0,4*(ncnr+512));   memset(ImBuf,0,4*(ncnr+512));


	for ( y=0; y < size; y++ ){BufIn[y+S4]=In[y];} // Входной буфер Buf In[y]

	Khg=KHig*KHig; Klw=KLow*KLow;
	for ( y=S2; y < size+s6; y++ ) { //треугольная весовая функция, прямая фильтрация
		ImBuf[y]=-ImBuf[y-2]+2*ImBuf[y-1]+BufIn[y-KHig-KHig]-2*BufIn[y-KHig]+BufIn[y];
		ReBuf[y]=-ReBuf[y-2]+2*ReBuf[y-1]+BufIn[y-KLow-KLow]-2*BufIn[y-KLow]+BufIn[y];
		}
	for ( y=0; y < size+S8; y++ )  { // Norm
		BufIn[y]=ImBuf[y]/Khg;  BufOu[y]=ReBuf[y]/Klw;  ImBuf[y]=ReBuf[y]=0;
		}
	for ( y=size+s6; y > S2; y--) { //треугольная весовая функция, инверсная фильтрация
		ImBuf[y]=-ImBuf[y+2]+2*ImBuf[y+1]+BufIn[y+KHig+KHig]-2*BufIn[y+KHig]+BufIn[y];
		ReBuf[y]=-ReBuf[y+2]+2*ReBuf[y+1]+BufOu[y+KLow+KLow]-2*BufOu[y+KLow]+BufOu[y];
		}
	for ( y=S4; y < size+S4; y++ ){ In[y-S4]=ImBuf[y]/Khg - ReBuf[y]/Klw; }
	// Выход In[y-S4]
/**/

KHig=KHigh; // заплатка - запрет на модификацию KHig

///////////////
/*
 vector<int> BufIn(size+S8);   // 514
 vector<int> BufOut1(size+S8);
 vector<int> BufOut2(size+S8);
 vector<int> lt1(size+S8);
 vector<int> lt2(size+S8);

	for ( y=0; y < size; y++ ){BufIn[y+S4]=In[y];} // Входной буфер Buf In[y]

	  Khg=KHig*KHig; Klw=KLow*KLow;
	  for ( y=S2; y < size+s6; y++ ) { //треугольная весовая функция, прямая фильтрация
		 lt1[y]=-lt1[y-2]+2*lt1[y-1]+BufIn[y-KHig-KHig]-2*BufIn[y-KHig]+BufIn[y]; //k=15+
		 lt2[y]=-lt2[y-2]+2*lt2[y-1]+BufIn[y-KLow-KLow]-2*BufIn[y-KLow]+BufIn[y]; //k=63+
	  }
	  for ( y=0; y < size+S8; y++ ) { lt1[y]=lt1[y]/Khg; lt2[y]=lt2[y]/Klw; }//Norm
	  for ( y=size+s6; y > S2; y--) { //треугольная весовая функция, инверсная фильтрация
		 BufOut1[y]=-BufOut1[y+2]+2*BufOut1[y+1]+lt1[y+KHig+KHig]-2*lt1[y+KHig]+lt1[y];//k=15-
		 BufOut2[y]=-BufOut2[y+2]+2*BufOut2[y+1]+lt2[y+KLow+KLow]-2*lt2[y+KLow]+lt2[y];//k=63-
	  }
	  for ( y=S4; y < size+S4; y++ ){ In[y-S4]=BufOut1[y]/Khg-BufOut2[y]/Klw; }
	  // Выход In[y-S4]
*/

// DM(size<<" sizeG ");  DM(END);

/*
	BufIn.assign(siz,0); BufOut1.assign(siz,0); BufOut2.assign(siz,0);
	lt1.assign(siz,0);   lt2.assign(siz,0);
*/
}//_____________________________________________________________________________


 // -----------------------------------------------------------------------------
// ++++++
// Полосовой фильтр Гауссиан (ГАУССИАН - Gaussian), попытка минимальной реализации.
// Входной буфер &HBuf, &GBuf. Адаптивный F(KHig) нолевой бордюр вокруг массивов
// 4 массива
// -----------------------------------------------------------------------------
 void OCRFilter::filterLaplasian(vector<int> &HBuf,
								 vector<int> &GBuf,
								 int KHig, int KLow){

 int y,Khg,Klw,S;
 int size=HBuf.size()-10; //-10 компенсация только для GBitset

 int KHigh=KHig; // заплатка - запрет на модификацию KHig
 if ( KHig<2 ) KHig=1;   if ( KHig>63 ) KHig=63;
 if ( KLow<2 ) KLow=2;   if ( KLow>63 ) KLow=63;
 S=KLow;  if ( S < KHig ) S=KHig;
 // Sn=129        257        385         514        при S=64,   KhgN=KHig*N+1
 int   S2=S*2+1,  S4=S*4+1,  s6=S*6+1,   S8=S*8+2;

 ///////////////

// обнуление BufIn,ImBuf,ReBuf,BufOu ( где BufIn,ImBuf,ReBuf,BufOu глобальные )
		memset(BufIn,0,4*(ncnr+512));   memset(BufOu,0,4*(ncnr+512));
		memset(ReBuf,0,4*(ncnr+512));   memset(ImBuf,0,4*(ncnr+512));
		GBuf.assign(ncnr,0);

//    for ( y=0; y < size+S8; y++ )  { BufIn[y]=BufOu[y]=ReBuf[y]=ImBuf[y]=0; }

	for ( y=0; y < size; y++ ){BufIn[y+S4]=HBuf[y];} // Входной буфер Buf HBuf[y]
	Khg=KHig*KHig; Klw=KLow*KLow;
	for ( y=S2; y < size+s6; y++ ) { //треугольная весовая функция, прямая фильтрация
		ImBuf[y]=-ImBuf[y-2]+2*ImBuf[y-1]+BufIn[y-KHig-KHig]-2*BufIn[y-KHig]+BufIn[y];
		ReBuf[y]=-ReBuf[y-2]+2*ReBuf[y-1]+BufIn[y-KLow-KLow]-2*BufIn[y-KLow]+BufIn[y];
		}
	for ( y=0; y < size+S8; y++ )  { // Norm
		BufIn[y]=ImBuf[y]/Khg;  BufOu[y]=ReBuf[y]/Klw;  ImBuf[y]=ReBuf[y]=0;
		}

	for ( y=size+s6; y > S2; y--) { //треугольная весовая функция, инверсная фильтрация
		ImBuf[y]=-ImBuf[y+2]+2*ImBuf[y+1]+BufIn[y+KHig+KHig]-2*BufIn[y+KHig]+BufIn[y];
		ReBuf[y]=-ReBuf[y+2]+2*ReBuf[y+1]+BufOu[y+KLow+KLow]-2*BufOu[y+KLow]+BufOu[y];
		}
	for ( y=S4; y < size+S4; y++ ){ GBuf[y-S4]=ImBuf[y]/Khg - ReBuf[y]/Klw; }
	// Выход GBuf[y-S4]


 /**/

KHig=KHigh; // заплатка - запрет на модификацию KHig

 ///////////////

/*
 vector<int> BufIn(size+S8);   // 514
 vector<int> BufOut1(size+S8);
 vector<int> BufOut2(size+S8);
 vector<int> lt1(size+S8);
 vector<int> lt2(size+S8);


	for ( y=0; y < size; y++ ){BufIn[y+S4]=HBuf[y];} // Входной буфер HBuf[y]
													 // Входной буфер In[y]
	  Khg=KHig*KHig; Klw=KLow*KLow;
	  for ( y=S2; y < size+s6; y++ ) { //треугольная весовая функция, прямая фильтрация
		 lt1[y]=-lt1[y-2]+2*lt1[y-1]+BufIn[y-KHig-KHig]-2*BufIn[y-KHig]+BufIn[y]; //k=15+
		 lt2[y]=-lt2[y-2]+2*lt2[y-1]+BufIn[y-KLow-KLow]-2*BufIn[y-KLow]+BufIn[y]; //k=63+
	  }
	  for ( y=0; y < size+S8; y++ ) { lt1[y]=lt1[y]/Khg; lt2[y]=lt2[y]/Klw; }//Norm
	  for ( y=size+s6; y > S2; y--) { //треугольная весовая функция, инверсная фильтрация
		 BufOut1[y]=-BufOut1[y+2]+2*BufOut1[y+1]+lt1[y+KHig+KHig]-2*lt1[y+KHig]+lt1[y];//k=15-
		 BufOut2[y]=-BufOut2[y+2]+2*BufOut2[y+1]+lt2[y+KLow+KLow]-2*lt2[y+KLow]+lt2[y];//k=63-
	  }
	  for ( y=S4; y < size+S4; y++ ){ GBuf[y-S4]=BufOut1[y]/Khg-BufOut2[y]/Klw; }
	  // Выход GBuf   // Выход In[y-S4]
*/

//DM(size<<" sizeG ");  DM(END);
/*
 vector<int> BufIn(size+514);
 vector<int> BufOut1(size+514);
 vector<int> BufOut2(size+514);
 vector<int> lt1(size+514);
 vector<int> lt2(size+514);

   for ( y=0; y < size; y++ ){BufIn[y+257]=HBuf[y];} // Входной буфер BufIn[y]

	  Khg=KHig*KHig; Klw=KLow*KLow;
	  for ( y=129; y < size+385; y++ ) { //треугольная весовая функция, прямая фильтрация
		 lt1[y]=-lt1[y-2]+2*lt1[y-1]+BufIn[y-KHig-KHig]-2*BufIn[y-KHig]+BufIn[y]; //k=15+
		 lt2[y]=-lt2[y-2]+2*lt2[y-1]+BufIn[y-KLow-KLow]-2*BufIn[y-KLow]+BufIn[y]; //k=63+
	  }
	  for ( y=0; y < size+514; y++ ) { lt1[y]=lt1[y]/Khg; lt2[y]=lt2[y]/Klw; }//Norm
	  for ( y=size+385; y > 129; y--) { //треугольная весовая функция, инверсная фильтрация
		 BufOut1[y]=-BufOut1[y+2]+2*BufOut1[y+1]+lt1[y+KHig+KHig]-2*lt1[y+KHig]+lt1[y];//k=15-
		 BufOut2[y]=-BufOut2[y+2]+2*BufOut2[y+1]+lt2[y+KLow+KLow]-2*lt2[y+KLow]+lt2[y];//k=63-
	  }
	  for ( y=257; y < size+257; y++ ){ GBuf[y-257]=BufOut1[y]/Khg-BufOut2[y]/Klw; }
	  // Выход In[y-257]
*/
/*
	BufIn.assign(siz,0); BufOut1.assign(siz,0); BufOut2.assign(siz,0);
	lt1.assign(siz,0);   lt2.assign(siz,0);
*/


}//_____________________________________________________________________________


// -------------------------------_ST_------------------------------------------
// ++++++
// Полосовой фильтр Гауссиан (ГАУССИАН - Gaussian), попытка минимальной реализации.
// Входной ST буфер *BufS, *BufTL. Адаптивный F(KHig) нолевой бордюр вокруг массивов
// 4 ST массива

// -----------------------------------------------------------------------------


 void OCRFilter::filterLaplasian( int *Buf1, int *BufTL, int size, int KHig, int KLow ){

 int y,Klw,Khg,S;

 int KHigh=KHig; // заплатка - запрет на модификацию KHig
 if ( KHig<2 ) KHig=1;   if ( KHig>63 ) KHig=63;
 if ( KLow<2 ) KLow=2;   if ( KLow>63 ) KLow=63;
 S=KLow;  if ( S < KHig ) S=KHig;
 // Sn=129        257        385         514        при S=64,   KhgN=KHig*N+1
 int   S2=S*2+1,  S4=S*4+1,  s6=S*6+1,   S8=S*8+2;


// обнуление BufIn,ImBuf,ReBuf,BufOu ( где BufIn,ImBuf,ReBuf,BufOu глобальные )
		memset(BufIn,0,4*(ncnr+512));   memset(BufOu,0,4*(ncnr+512)); // szf=4;
		memset(ReBuf,0,4*(ncnr+512));   memset(ImBuf,0,4*(ncnr+512));
		memset(BufTL,0,4*(size+32 ));

	for ( y=0; y < size; y++ ){BufIn[y+S4]=Buf1[y];} // Входной буфер Buf Buf1[y]
	Khg=KHig*KHig; Klw=KLow*KLow;
	for ( y=S2; y < size+s6; y++ ) { //треугольная весовая функция, прямая фильтрация
		ImBuf[y]=-ImBuf[y-2]+2*ImBuf[y-1]+BufIn[y-KHig-KHig]-2*BufIn[y-KHig]+BufIn[y];
		ReBuf[y]=-ReBuf[y-2]+2*ReBuf[y-1]+BufIn[y-KLow-KLow]-2*BufIn[y-KLow]+BufIn[y];
		}
	for ( y=0; y < size+S8; y++ )  { // Norm
		BufIn[y]=ImBuf[y]/Khg;  BufOu[y]=ReBuf[y]/Klw;  ImBuf[y]=ReBuf[y]=0;
		}
	for ( y=size+s6; y > S2; y--) { //треугольная весовая функция, инверсная фильтрация
		ImBuf[y]=-ImBuf[y+2]+2*ImBuf[y+1]+BufIn[y+KHig+KHig]-2*BufIn[y+KHig]+BufIn[y];
		ReBuf[y]=-ReBuf[y+2]+2*ReBuf[y+1]+BufOu[y+KLow+KLow]-2*BufOu[y+KLow]+BufOu[y];
		}
	for ( y=S4; y < size+S4; y++ ){ BufTL[y-S4]=ImBuf[y]/Khg - ReBuf[y]/Klw; }
	// Выход BufTL[y-S4]
/**/

KHig=KHigh; // заплатка - запрет на модификацию KHig


}//_____________________________________________________________________________


// Sorting  сортировка
// ---------------------------------------------------------------------------

void Sort(vector<int> &GBuf,int Nff){
   int y,x;
 // сортировка
   int trash=0;
   bool f=true;
   int i,j;

   //  DM(NSort<<" NSort+ ");
   if( Nff==0) { return; }
  /*
#ifdef DEBUGLVL
              DM(END);  DM(END);
			  for ( x=0; x < NSort;  x++ ){      // x < d+1;
				DM(GBuf[x]<<"\t"); if (x%10==0)DM(END);  /// ТАБЛИЦА
                  }//for x
			  DM(END);
#endif
  */
				 // "сортировка Шейкера".
				 // http://www.abc-it.lv/index.php/id/610

	 for ( i=1; (i<=Nff) && (f=true) ; i++)
	   {
          f=false;
		  for ( j=i; j<=Nff-i; j++) // проходим с лева на право
             {
                if (GBuf[j]>GBuf [j+1]) // если число слева больше числа
			   {
                  trash=GBuf[j]; // справа, то меняем местами
                  GBuf[j]=GBuf [j+1]; // справа собираются большие числа
				  GBuf[j+1]=trash;
                  f=true;
               }
			 }
			   for ( j=Nff-i-1; j>i ; j--)  // проходим с права на лево
                 {
				   if (GBuf[j]<GBuf[j-1])  // если число справа меньше числа
                   {
                   trash=GBuf[j]; // слева, то меняем местами
				   GBuf[j]=GBuf[j-1]; // слева собираются меньшие числа
                   GBuf[j-1]=trash;
                   f=true;
				 }
				 }
			 }
/*
#ifdef DEBUGLVL
			  DM(END);  DM(END);
			  for ( x=0; x < NSort;  x++ ){      // x < d+1;
				DM(GBuf[x]<<"\t"); if (x%10==0)DM(END);  /// ТАБЛИЦА
				  }//for x
			  DM(END);
#endif
  */
}//_____________________________________________________________________________


/*
// ЗАГОТОВКА Statistics Вычисление распределения вероятностей с параметром (Porog, Delta)
// Подпрограмма расчета моментов распределения: матожидания, дисперсии.
// -----------------------------------------------------------------------------
void GBitset::Statistics(vector<int> &HBuf, vector<int> &GBuf,
						 int Porog, int Delta ) {
  int x,y,d,p;
  ///vector<int> BufS(ncolumns);
  ///vector<int> BufR(ncolumns);

			  if( NLet<=0 || NLet>ncolumns) { return; }
								BufS=GBuf;
			  for (  y=0; y < NLet-1; y++ ){ BufR[y+1]= GBuf[y+1]-GBuf[y]; }
				   // TMP
//              DM(END);            // size-1   N0Fase
//              for ( x=0; x < NLet;  x++ ){      // x < d+1;
//                DM(BufR[x]<<"\t"); if (x%10==0)DM(END);  /// ТАБЛИЦА
//                  }//for x
//              DM(END);

				 // "сортировка Шейкера". // GBuf
				 // http://www.abc-it.lv/index.php/id/610
				 Sort(BufR,NLet-1);
			//             sort(BufR.begin(), BufR.end());

			//              DM(END);            // size-1   N0Fase
//              for ( x=0; x < NLet;  x++ ){      // x < d+1;
//                DM(BufR[x]<<"\t"); if (x%10==0)DM(END);  /// ТАБЛИЦА
//                  }//for x
//             DM(END);

			  // фильтрация по порогу, отбрасывание хвостов распределения
			  d=0;
			  for (  y=0; y < NLet; y++ ){
				 if ( BufR[y] > Porog/8 && BufR[y] < Porog )
					{ BufR[d]=BufR[y]; d++; }
			  }// for y
//              DM(END);            // size-1   N0Fase
//              for ( x=0; x < d;  x++ ){      // x < d+1;
//                DM(BufR[x]<<"\t"); if (x%10==0)DM(END);  /// ТАБЛИЦА
//                  }//for x
//              DM(END);

			  // отбрасывание хвостов распределения
			  // получение среднего по горизонту размера периода букв 10*mean
			  p=0; MeanSA=0;
			  for ( y=Delta; y <d-Delta && p < NLet; y++ ) {
				BufR[p]=BufR[y]; MeanSA+=BufR[p]; p++;
			  }// for y
			  // MeanSA=10*MeanSA/p; PLLLL
			  if( p > 0 && p <= NLet ){ MeanSA=10*MeanSA/p; }
			  else MeanSA=9999;// средний период букв умноженный на 10
			 // вычисленная дисперсия VarianceSA периода букв умноженныя на 10

#ifdef DEBUGLVL
			  // ВИЗУАЛИЗАЦИЯ цифровая
//     DM(MeanSA<<" -MeanSA*10- "); DM(p<<" p "); DM(Delta<<" Delta ");DM(END);
//              DM(END);            // size-1   N0Fase
//              for ( x=0; x < NLet;  x++ ){      // x < d+1;
//                DM(BufS[x]<<"\t"); if (x%10==0)DM(END);  /// ТАБЛИЦА
//                  }//for x
//              DM(END);

//              DM(END);            // size-1   N0Fase
//              for ( x=0; x < p;  x++ ){      // x < d+1;
//                DM(BufR[x]<<"\t"); if (x%10==0)DM(END);  /// ТАБЛИЦА
//                  }//for x
//              DM(END);

#endif
}//_____________________________________________________________________________
*/





////////////////////////////////////////////////////////////////////////


};
