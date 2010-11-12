
//-------------------------------АЛГОРИТМЫ------------------------------------//
//----------------------------------------------------------------------------//

//  ФИЛЬТР НИЗКИХ ЧАСТОТ  (ГАУССИАН - Gaussian)

//  --------------------------------------------------------------------------//
    // треугольная весовая функция
    // y(n)= -y(n-2)+2y(n-1)+x(n-2k-2)-2x(n-k-1)+xn

 void GBitsetContour::filterHighM(vector<int> &In, int KHig){
 //int KHig=11+1; //порядок высокочастотного фильтра (k=15) 2< KLow,KHig =<63

 int x,y,n,Varu,Khg,sum;
 short size=In.size();
 //int size=nrows;
 vector<int> BufIn(size+514);
 vector<int> BufOut1(size+514);
 vector<int> lt1(size+514);


    if ( KHig<2 ) KHig=1;   if ( KHig>63 ) KHig=63;
    for ( y=0; y < size; y++ ){BufIn[y+257]=In[y];} // Входной буфер BufIn[y]
    ///sum=0;
    for ( y=0; y < 257; y++ ){BufIn[y]=0; BufOut1[y]=0; lt1[y]=0;}             //0000
    for ( y=size+257; y < size+514; y++ ){BufIn[y]=0; BufOut1[y]=0; lt1[y]=0;} //0000
    //for ( y=0; y < size+514; y++ ){BufIn[y]=0;} BufIn[257+size/2]=1000;sum=0;//TEST
    //BufIn[257+32]=5000; BufIn[257+size/2]=5000; BufIn[size+257-32]=5000;     //TEST
      Khg=KHig*KHig;
      for ( y=129; y < size+385; y++ ) { //треугольная весовая функция, прямая фильтрация
         lt1[y]=-lt1[y-2]+2*lt1[y-1]+BufIn[y-KHig-KHig]-2*BufIn[y-KHig]+BufIn[y]; //k=15+
      }
      for ( y=0; y < size+514; y++ ) { lt1[y]=lt1[y]/Khg; }         //Norm
      for ( y=size+385; y > 129; y--) { //треугольная весовая функция, инверсная фильтрация
         BufOut1[y]=-BufOut1[y+2]+2*BufOut1[y+1]+lt1[y+KHig+KHig]-2*lt1[y+KHig]+lt1[y];//k=15-
      }
      for ( y=257; y < size+257; y++ ){ BufOut1[y]=BufOut1[y]/Khg;  //Norm
       //  if(y<=size/2+257){Varu=y-257;} else {Varu=(size+257-y);}
       //  BufOut1[y-257]=(BufOut1[y]*1)*Varu/size;//временная регилировка усиления (вдоль y)
          In[y-257]=BufOut1[y];                    // Выходной буфер BufOut1
       /// BufOut1[y-257]=BufOut1[y]; // /1
       //// sum=sum+BufOut1[y]; //подсчет постоянной составляющей
        }

///DC(sum/size<<"summa "); //контроль постоянной составляющей
// DC("ГАУССИАН ");TIME_PRINT

#ifdef DEBUGLVL
            /*    static short delta=0.8*ncolumns;
                for(y=0; y < drawData->rows(); y++) {
              //DC(BufOut1[y]/200<<" ");
                if(BufOut1[y]>=0){
                  for(x =delta; x < (BufOut1[y])+delta; x++ )drawData[0][y][x]*=0.6;
                 }else{

                  for(x =delta; x > (BufOut1[y])+delta; x-- )drawData[0][y][x]*=0.6;

                 }

               }

           */

#endif


}//_____________________________________________________________________________



// -----------------------------------------------------------------------------

// ФИЛЬТР НИЗКИХ ЧАСТОТ  (ГАУССИАН - Gaussian), попытка минимальной реализации.

// Адаптивный F(KHig) нолевой бордюр вокруг массивов.

// -----------------------------------------------------------------------------


 void GBitsetContour::filterHigh(vector<int> &In, int KHig){


 int y,Khg;
 short size=In.size(); // GBuf

 if ( KHig<2 ) KHig=1;   if ( KHig>63 ) KHig=63;
 // для фильтра низких частот  KhgN=KHig*N+1 ,  при KHig=64 :
 //   129             257             385              514
 int  Khg2=KHig*2+1,  Khg4=KHig*4+1,  Khg3=KHig*6+1,   Khg8=KHig*8+2;

 vector<int> BufIn(size+Khg8);
 vector<int> lt1(size+Khg8);
 vector<int> BufOut1(size+Khg8);

      // Входной буфер BufIn[y+Khg4], In[y]
      for ( y=0; y < size; y++ ){BufIn[y+Khg4]=In[y];}
      Khg=KHig*KHig;
      for ( y=Khg2; y < size+Khg3; y++ ) { //треугольная весовая функция, прямая фильтрация
         lt1[y]=-lt1[y-2]+2*lt1[y-1]+BufIn[y-KHig-KHig]-2*BufIn[y-KHig]+BufIn[y]; //k=15+
      }
      for ( y=0; y < size+Khg8; y++ ) { lt1[y]=lt1[y]/Khg; }         //Norm
      for ( y=size+Khg3; y > Khg2; y--) { //треугольная весовая функция, инверсная фильтрация
         BufOut1[y]=-BufOut1[y+2]+2*BufOut1[y+1]+lt1[y+KHig+KHig]-2*lt1[y+KHig]+lt1[y];//k=15-
      }
      for ( y=Khg4; y < size+Khg4; y++ ){ In[y-Khg4]=BufOut1[y]/Khg; }
      // Выходной буфер In[y-Khg4, BufOut1[y]]

//DC(size<<" sizeG ");  DC(END);

/*

      if ( KHig<2 ) KHig=1;   if ( KHig>63 ) KHig=63;

      // Входной буфер BufIn[y+257], In[y]
      for ( y=0; y < size; y++ ){BufIn[y+257]=In[y];}
      Khg=KHig*KHig;
      for ( y=129; y < size+385; y++ ) { //треугольная весовая функция, прямая фильтрация
         lt1[y]=-lt1[y-2]+2*lt1[y-1]+BufIn[y-KHig-KHig]-2*BufIn[y-KHig]+BufIn[y]; //k=15+
      }
      for ( y=0; y < size+514; y++ ) { lt1[y]=lt1[y]/Khg; }         //Norm
      for ( y=size+385; y > 129; y--) { //треугольная весовая функция, инверсная фильтрация
         BufOut1[y]=-BufOut1[y+2]+2*BufOut1[y+1]+lt1[y+KHig+KHig]-2*lt1[y+KHig]+lt1[y];//k=15-
      }
      for ( y=257; y < size+257; y++ ){ In[y-257]=BufOut1[y]/Khg; }
      // Выходной буфер In[y-257, BufOut1[y]]

*/


}//_____________________________________________________________________________





//  ПОЛОСОВОЙ ФИЛЬТР (ГАУССИАН - Gaussian)
//  ----------------------------------------------------------------------------
    // прямоугольная весовая функция
    // y(n)= y(n-1)+xn-x(n-2k-1)
    // треугольная весовая функция
    // y(n)= -y(n-2)+2y(n-1)+x(n-2k-2)-2x(n-k-1)+xn

 void GBitsetContour::filterLaplasian(vector<int> &In, int KHig, int KLow){
 //int KHig=8+1; //порядок высокочастотного фильтра (k=15) 2< KLow,KHig =<63
 //int KLow=63+1; //порядок низкочастотного фильтра (k=63) 2< KLow,KHig =<63
                // KLow >< Hig
 int x,y,n,Varu,Klw,Khg,sum;
 short size=In.size();
 //int size=nrows;  HBuf.assign(ncolumns,0);
 vector<int> BufIn(size+514);
 vector<int> BufOut1(size+514);
 vector<int> BufOut2(size+514);
 vector<int> lt1(size+514);
 vector<int> lt2(size+514);


// TIME_START
    if ( KHig<2 ) KHig=1;   if ( KHig>63 ) KHig=63;
    if ( KLow<2 ) KLow=2;   if ( KLow>63 ) KLow=63;
/*
    BufIn.assign(size+514,0);
    BufOut1.assign(size+514,0); BufOut2.assign(size+514,0);
    lt1.assign(size+514,0);     lt2.assign(size+514,0);
*/
   for ( y=0; y < size; y++ ){BufIn[y+257]=In[y];} // Входной буфер BufIn[y]
     ///sum=0;
/*    for ( y=0; y < 257; y++ ){BufIn[y]=0;BufOut1[y]=0;BufOut2[y]=0;            //0000
    lt1[y]=0;lt2[y]=0;}                                                        //0000
    for ( y=size+257; y < size+514; y++ ){BufIn[y]=0;BufOut1[y]=0;BufOut2[y]=0;//0000
    lt1[y]=0;lt2[y]=0;}                                                        //0000
*/    //for ( y=0; y < size+514; y++ ){BufIn[y]=0;} BufIn[257+size/2]=1000;sum=0;//TEST
    //BufIn[257+32]=5000; BufIn[257+size/2]=5000; BufIn[size+257-32]=5000;     //TEST
    /// BufIn.empty(); BufIn.resize(size+514)
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
      for ( y=257; y < size+257; y++ ){ In[y-257]=BufOut1[y]/Khg-BufOut2[y]/Klw; // Выход In[y-257]
       //  if(y<=size/2+257){Varu=y-257;} else {Varu=(size+257-y);}
       //  BufOut1[y-257]=(BufOut1[y]*1)*Varu/size;//временная регилировка усиления (вдоль y)
       //   In[y-257]=BufOut1[y];                   // Выходной буфер BufOut1
       ///   BufOut1[y-257]=BufOut1[y]/1;
       //// sum=sum+BufOut1[y]; //подсчет постоянной составляющей
        }

//// DC(sum/size<<"summa "); //контроль постоянной составляющей
// DC("ГАУССИАН "); TIME_PRINT

/*
#ifdef DEBUGLVL
                static short delta=0.8*ncolumns;
                for(y=0; y < drawData->rows(); y++) {
              //DC(BufOut1[y]/200<<" ");
                if(BufOut1[y]>=0){
                  for(x =delta; x < (BufOut1[y])+delta; x++ )drawData[0][y][x]*=0.6;
                 }else{

                  for(x =delta; x > (BufOut1[y])+delta; x-- )drawData[0][y][x]*=0.6;

                 }

               }

#endif

*/


}//_____________________________________________________________________________
//                                                     *
//                                                     *                                                       *
// Визуализация аналоговая вертикальных графиков L     *
// -----------------------------------------------------------------------------

void GBitsetContour::LDraw(vector<int> &HStr, int sm, int color){

#ifdef DEBUGLVL
#ifdef WIN32_DRAW
 int y,x,in,m;
 int size=HStr.size();
 TPoint ris[25000];
 // ВАЖНО - сумма вдоль текста HStr[y] поделена на 8 и на 4  (8*4=32)
                   m=32;
           for (  y=0; y < nrows; y++ ) {
                   x=sm + HStr[y]/m;
                   ris[y].x=x;

                   ris[y].y=nrows-y;  //заполнение массива координат линии

           } // for y
		in=ImageProcessor->ImageEnView1->AddNewObject();
		ImageProcessor->ImageEnView1->ObjPenColor[in]=(TColor)color;
		ImageProcessor->ImageEnView1->ObjPenWidth[in]=0,5;
		ImageProcessor->ImageEnView1->ObjKind[in]=iekPOLYLINE;
		ImageProcessor->ImageEnView1->SetObjPolylinePoints(in,ris,nrows-2);

		ImageProcessor->ImageEnView1->Update();
#endif
#endif
 // size=nrows;
}//_____________________________________________________________________________


void GBitsetContour::vDraw(){

#ifdef DEBUGLVL
#ifdef WIN32_DRAW
 int y,x,in,m;
 int index;


 DC("start_draw"<<END);
 DC("vectorBase[0].allVectorCount="<<vectorBase[0].allVectorCount<<END);


if(vectorBase[0].allVectorCount==0)return;

//iLeft-=32;
//iTop-=32;


 TPoint ris[25000];
 int dl=0;

		  // заполняем массив значениями координат векторов
		  for (index=0; index<vectorBase[0].allVectorCount;index++) {

				//OCRPoint vStart1,vEnd1;
				//vStart1=vectorBase[index].vStart;
				//DP("vStart.x="<<vectorBase[index].vStart.x<<" vStart.y="<<vectorBase[index].vStart.y);
				//vEnd1=vectorBase[index].vEnd;
				//DP("vEnd.x="<<vectorBase[index].vEnd.x<<" vEnd.y="<<vectorBase[index].vEnd.y<<" index="<<index<<" count="<<vectorBase[0].allVectorCount<<END);

			  //startPoint1.x=(float)(vStart1.x+0.5);
			  //startPoint1.y=(float)(vStart1.y-0.5);

				//endPoint1.x=(float)(vEnd1.x+0.5);
				//endPoint1.y=(float)(vEnd1.y-0.5);   //cout<<vectYEnd<<" ";
			  vectorBase[index].vStart.x+=iLeft-dl;
			  vectorBase[index].vStart.y+=iTop-dl;
			  vectorBase[index].vEnd.x+=iLeft-dl;
			  vectorBase[index].vEnd.y+=iTop-dl;
			  vectorBase[index].vCenter.x+=iLeft-dl;
			  vectorBase[index].vCenter.y+=iTop-dl;



			  //ris[0].x=vectorBase[index].vStart.x;
			  //ris[0].y=vectorBase[index].vStart.y;
			  //ris[1].x=vectorBase[index].vEnd.x;
			  //ris[1].y=vectorBase[index].vEnd.y;
			  //ris[2].x=vectorBase[index].vEnd.x;
			  //ris[2].y=vectorBase[index].vEnd.y;


		//in=ImageProcessor->ImageEnVect1->AddNewObject();
		//ImageProcessor->ImageEnVect1->ObjPenColor[in]=(TColor)0x0000AA00;
		//ImageProcessor->ImageEnVect1->ObjKind[in]=iekPOLYLINE;
		//ImageProcessor->ImageEnVect1->SetObjPolylinePoints(in,ris,2);
		//vectorBase[index].objIndex=index;
		}



		//ImageProcessor->ImageEnView1->Update();
		//ImageProcessor->ImageEnVect1->Update();

#endif
#endif

}//_____________________________________________________________________________


//                                                                      *


//                                                                      *

//                                                                      *                                                       *
// Визуализация аналоговая вертикальных графиков H переменной длинны    *
// -----------------------------------------------------------------------------

void GBitsetContour::LDrawVar(vector<int> &HStr, int HDrawSize, int sm, int scope, int color){

#ifdef DEBUGLVL
#ifdef WIN32_DRAW
 int y,x,in,m;
 TPoint ris[25000];

 // WDrawSize - размер, sm - смещение по вертикали,   scope - масштаб=32, color - цвет
 // ВАЖНО - сумма вдоль текста HStr[y] поделена на 8 и на 4  (8*4=32)
           if(scope<=0) scope = 1;  //  m=32;
           for (  y=0; y < HDrawSize; y++ ) {
                   x=sm + HStr[y]/scope;
                   ris[y].x=x;

                   ris[y].y=HDrawSize-y;  //заполнение массива координат линии

           } // for y
		in=ImageProcessor->ImageEnView1->AddNewObject();
		ImageProcessor->ImageEnView1->ObjPenColor[in]=(TColor)color;
		ImageProcessor->ImageEnView1->ObjPenWidth[in]=0,5;
		ImageProcessor->ImageEnView1->ObjKind[in]=iekPOLYLINE;
		ImageProcessor->ImageEnView1->SetObjPolylinePoints(in,ris,HDrawSize-2);

		ImageProcessor->ImageEnView1->Update();
#endif
#endif

}//_____________________________________________________________________________


//                                                    |

//                                                    |

//                                                    |                                                        *

// Визуализация аналоговая вертикальных линий         |
// ---------------------------------------------------------------------------

void GBitsetContour::LineVertical(int sm, int color){

#ifdef DEBUGLVL
#ifdef WIN32_DRAW
 int in;
 TPoint ris[4]; 

        //заполнение массива координат линии
        ris[0].x=sm;      ris[1].x=sm;    ris[2].x=sm;
        ris[0].y=nrows;   ris[1].y=0;     ris[2].y=0;
		in=ImageProcessor->ImageEnView1->AddNewObject();
		ImageProcessor->ImageEnView1->ObjPenColor[in]=(TColor)color;
		ImageProcessor->ImageEnView1->ObjPenWidth[in]=0,1;
		ImageProcessor->ImageEnView1->ObjKind[in]=iekPOLYLINE;
		ImageProcessor->ImageEnView1->SetObjPolylinePoints(in,ris,2);

        ImageProcessor->ImageEnView1->Update();

 #endif
 #endif

}//_____________________________________________________________________________



// Визуализация аналоговая горизональных графиков W  *******

// -----------------------------------------------------------------------------


void GBitsetContour::WDraw(vector<int> &LStr, int sm, int color){ //  LStr

#ifdef DEBUGLVL
#ifdef WIN32_DRAW
 int y,x,in,m,size;
 TPoint ris[50000];
 // ВАЖНО - сумма вдоль текста LStr[y] поделена на 8 и на 4  (8*4=32)
           //заполнение маассива координат линии
                  m=16; sm=nrows-sm;
           for (  x=0; x < ncolumns; x++ ) {
                   y=sm - LStr[x]/m;
                   ris[x].y=y;   // амплитуда

                   ris[x].x=x;   // горизонтальная разертка

           } // for x
		in=ImageProcessor->ImageEnView1->AddNewObject();
		ImageProcessor->ImageEnView1->ObjPenColor[in]=(TColor)color;
		ImageProcessor->ImageEnView1->ObjKind[in]=iekPOLYLINE;
		ImageProcessor->ImageEnView1->SetObjPolylinePoints(in,ris,ncolumns-2);

		ImageProcessor->ImageEnView1->Update();
 #endif
 #endif
}//_____________________________________________________________________________



// Визуализация аналоговая горизональных графиков W переменной длинны ******* **

// -----------------------------------------------------------------------------


void GBitsetContour::WDrawVar(vector<int> &LStr, int WDrawSize, int sm, int scope, int color){

#ifdef DEBUGLVL
#ifdef WIN32_DRAW

 // WDrawSize - размер, sm - смещение по вертикали,   scope - масштаб=8, color - цвет
 int y,x,in,size;
 TPoint ris[50000];
 // ВАЖНО - сумма вдоль текста LStr[y] поделена на 8 и на 4  (8*4=32)
           //заполнение массива координат линии
           if(scope<=0) scope = 1;
           sm=nrows-sm;
           for (  x=0; x < WDrawSize; x++ ) {
                   y=sm - LStr[x]/scope;
                   ris[x].y=y;   // амплитуда

                   ris[x].x=x;   // горизонтальная разертка

           } // for x
		in=ImageProcessor->ImageEnView1->AddNewObject();
		ImageProcessor->ImageEnView1->ObjPenColor[in]=(TColor)color;
		ImageProcessor->ImageEnView1->ObjKind[in]=iekPOLYLINE;
		ImageProcessor->ImageEnView1->SetObjPolylinePoints(in,ris,WDrawSize-2);

		ImageProcessor->ImageEnView1->Update();
 #endif
 #endif
}//_____________________________________________________________________________


//                                                       * * *

//                                                      *     *

//                                                      *     *

// Визуализация аналоговая полярные координаты           * * *

// -----------------------------------------------------------------------------


// Polar coordinates  полярные координаты
void GBitsetContour::PolarCoordinates(vector<int> &HBuf,
                               vector<int> &GBuf,
                               int LDrawSize,
                               int smX,  int smY,
                               int scope,int color){

#ifdef DEBUGLVL
#ifdef WIN32_DRAW

 // WDrawSize - круговая длинна , smY - смещение по вертикали,   scope - масштаб=8, color - цвет
 int y,x,i,in,size;
 TPoint ris[50000];

           if(nrows<=ncolumns) { size = nrows; }
           else { size = ncolumns; }

           if(scope<=0) scope = 1;
           //smY=nrows-smY;
           //заполнение массива координат линии
           for (  i=0; i < size; i++ ) {
                   y=smY - GBuf[i]/scope;
                   x=smX - HBuf[i]/scope;
                   ris[i].y=y;   // вертикальная разертка

                   ris[i].x=x;   // горизонтальная разертка

           } // for i
		in=ImageProcessor->ImageEnView1->AddNewObject();
		ImageProcessor->ImageEnView1->ObjPenColor[in]=(TColor)color;
		ImageProcessor->ImageEnView1->ObjKind[in]=iekPOLYLINE;
		ImageProcessor->ImageEnView1->SetObjPolylinePoints(in,ris,size-2);

		ImageProcessor->ImageEnView1->Update();
 #endif
 #endif
}//_____________________________________________________________________________


           //    ВОПРОС

//                                                       * 

//                                                      *  * * *

//                                                     *         *

// Визуализация аналоговая амплитуда частота

// -----------------------------------------------------------------------------


// AmplitudeFrequency  амплитуда частота
void GBitsetContour::AmplitudeFrequency(vector<int> &GBuf,int smX,int smY,int scope,int color){

#ifdef DEBUGLVL
#ifdef WIN32_DRAW

 // WDrawSize - круговая длинна , smY - смещение по вертикали,   scope - масштаб=8, color - цвет
 int y,x,i,in,size;
 TPoint ris[50000];

           if(nrows<=ncolumns) { size = nrows; }
           else { size = ncolumns; }
 //          size = ncolumns;

           if(scope<=0) scope = 1;
           smY=nrows-smY;
           //заполнение массива координат линии
           for (  x=0; x < size; x=x+10 ) { // x++   LfMem=10*DeltaNstrKH;
        //     if(GBuf[x]>=0) { y=smY - GBuf[x]/scope; } // if
             y=smY - GBuf[x]/scope;
             ris[x].y=y;   // амплитуда
             ris[x].x=x;   // горизонтальная разертка
           } // for x

		in=ImageProcessor->ImageEnView1->AddNewObject();
		ImageProcessor->ImageEnView1->ObjPenColor[in]=(TColor)color;
		ImageProcessor->ImageEnView1->ObjKind[in]=iekPOLYLINE;
		ImageProcessor->ImageEnView1->SetObjPolylinePoints(in,ris,size-2);

		ImageProcessor->ImageEnView1->Update();
/*   */
 #endif
 #endif
}//_____________________________________________________________________________





//                                                                   ***********

//                                                                   ***********

// Визуализация аналоговая  строк (прямоугольников) в структурах     ***********
// -----------------------------------------------------------------------------

void GBitsetContour::stringDraw(int color){
#ifdef DEBUGLVL
#ifdef WIN32_DRAW
int in;
TPoint ris[6];

           // заполнение массива координат прямоугольника
           for (int m=0; m < strArray->size(); m++ )
              {
                   ris[0].x=strArray[0][m].x0;
                   ris[0].y=nrows-strArray[0][m].y0;

                   ris[1].x=strArray[0][m].x0;

                   ris[1].y=nrows-strArray[0][m].y1;

                   ris[2].x=strArray[0][m].x1;

                   ris[2].y=nrows-strArray[0][m].y1;

                   ris[3].x=strArray[0][m].x1;

                   ris[3].y=nrows-strArray[0][m].y0;

                   ris[4].x=strArray[0][m].x0;

                   ris[4].y=nrows-strArray[0][m].y0;

                   ris[5].x=strArray[0][m].x0;

                   ris[5].y=nrows-strArray[0][m].y0;

					in=ImageProcessor->ImageEnView1->AddNewObject();

					ImageProcessor->ImageEnView1->ObjPenColor[in]=(TColor)color; // цвет линии
					ImageProcessor->ImageEnView1->ObjPenWidth[in]=0,1;  // толщина линии
					ImageProcessor->ImageEnView1->ObjKind[in]=iekPOLYLINE;
					ImageProcessor->ImageEnView1->SetObjPolylinePoints(in,ris,5);
           } // m
		   ImageProcessor->ImageEnView1->Update();
// x0,y0,x1,y1
// x0,y0 координаты левого нижнего угла прямоугольника строки (глифа, слога, буквы).
// x1,y1 координаты правого верхнего угла прямоугольника строки (глифа, слога, буквы).
#endif
#endif
}//_____________________________________________________________________________


//                                                           *******

//                                                           *     *

//                                                           *******

// Визуализация аналоговая  прямоугольников в структурах для букв
// -----------------------------------------------------------------------------

void GBitsetContour::wordDraw(int color){

#ifdef DEBUGLVL
#ifdef WIN32_DRAW  //
int strInd,m,in;
int x,x0,x1,y0,y1;        // ,xt0,yt0,xt1,yt1
int NString,MaxString=10; // MaxString - ограничение на колличество выводимых на эран строк
TPoint ris[6];            // ( если больше графический порт вешается)

// x0,x1, y0,y1     координаты квадрата вокруг буквы
// xt0,xt1, yt0,yt1 координаты прямоугольника вокруг стека


         // заполнение массива координат прямоугольника
         NString = strArray->size();
         if ( NString > MaxString ) NString=MaxString;

         for ( strInd=0; strInd < NString; strInd++ ){
           for ( m=0; m < strArray[0][strInd].wordArray.size(); m++ ){
            // рисует горизонтальную двойную черную черту ниже стека, если он есть
            wordOCR *wP=&strArray[0][strInd].wordArray[m];
            if ( strArray[0][strInd].wordArray[m].stackFlag ) {     // != 0
               x0=wP->xt0;  x1=wP->xt1;  y0=wP->yt0;  y1=wP->yt1;
               for (x=0; x <= x1-x0; x++) { drawData[0][y0-5][(x+x0)]*=0.1;
                                            drawData[0][y0-6][(x+x0)]*=0.1; }
               }
                   x0=wP->x0;   x1=wP->x1;   y0=wP->y0;   y1=wP->y1;
                   ris[0].x=x0;
                   ris[0].y=nrows-y0;

                   ris[1].x=x0;

                   ris[1].y=nrows-y1;

                   ris[2].x=x1;

                   ris[2].y=nrows-y1;

                   ris[3].x=x1;

                   ris[3].y=nrows-y0;

                   ris[4].x=x0;

                   ris[4].y=nrows-y0;

                   ris[5].x=x0;

                   ris[5].y=nrows-y0;

					in=ImageProcessor->ImageEnView1->AddNewObject();
					ImageProcessor->ImageEnView1->ObjPenColor[in]=(TColor)color; // цвет линии
                    ImageProcessor->ImageEnView1->ObjPenWidth[in]=1;  // толщина линии
                    ImageProcessor->ImageEnView1->ObjKind[in]=iekPOLYLINE;
                    ImageProcessor->ImageEnView1->SetObjPolylinePoints(in,ris,5);
           } // m
         } // strInd
         ImageProcessor->ImageEnView1->Update();
/**/

/*
         for ( strInd=0; strInd < NString; strInd++ ){
           for ( m=0; m < strArray[0][strInd].wordArray.size(); m++ ){
                   ris[0].x=strArray[0][strInd].wordArray[m].x0;
                   ris[0].y=nrows-strArray[0][strInd].wordArray[m].y0;

                   ris[1].x=strArray[0][strInd].wordArray[m].x0;

                   ris[1].y=nrows-strArray[0][strInd].wordArray[m].y1;

                   ris[2].x=strArray[0][strInd].wordArray[m].x1;

                   ris[2].y=nrows-strArray[0][strInd].wordArray[m].y1;

                   ris[3].x=strArray[0][strInd].wordArray[m].x1;

                   ris[3].y=nrows-strArray[0][strInd].wordArray[m].y0;

                   ris[4].x=strArray[0][strInd].wordArray[m].x0;

                   ris[4].y=nrows-strArray[0][strInd].wordArray[m].y0;

                   ris[5].x=strArray[0][strInd].wordArray[m].x0;

                   ris[5].y=nrows-strArray[0][strInd].wordArray[m].y0;

                    in=ImageProcessor->ImageEnView1->AddNewObject();
                    ImageProcessor->ImageEnView1->ObjPenColor[in]=(TColor)color; // цвет линии
                    ImageProcessor->ImageEnView1->ObjPenWidth[in]=1;  // толщина линии
                    ImageProcessor->ImageEnView1->ObjKind[in]=iekPOLYLINE;
                    ImageProcessor->ImageEnView1->SetObjPolylinePoints(in,ris,5);
           } // m
         } // strInd
         ImageProcessor->ImageEnView1->Update();
*/

// x0,y0,x1,y1
// x0,y0 координаты левого нижнего угла прямоугольника строки (глифа, слога, буквы).
// x1,y1 координаты правого верхнего угла прямоугольника строки (глифа, слога, буквы).
/*
  // выбор визуализации, квадрат вокруг верхней или нижней буквы стека
  if ( strArray[0][strInd].wordArray[m].stackFlag )   // != 0
       { x0=wP->xt0;  x1=wP->xt1;  y0=wP->yt0;  y1=wP->yt1; }
  else { x0=wP->x0;   x1=wP->x1;   y0=wP->y0;   y1=wP->y1;  }
*/

#endif    //
#endif
}//_____________________________________________________________________________


//                                                           ******

//                                                           *    *

//                                                           ******

// Визуализация аналоговая  прямоугольников в структурах для точек
// -----------------------------------------------------------------------------

void GBitsetContour::pointDraw(int color){

#ifdef DEBUGLVL
#ifdef WIN32_DRAW  //
int strInd,m,in,Lp,Cp;
int NString,MaxString=10; // MaxString - ограничение на колличество выводимых на эран строк
TPoint ris[6];            // ( если больше графический порт вешается)
//// DC("NhIm");

         // заполнение массива координат прямоугольника
         NString = strArray->size();
         if ( NString > MaxString ) NString=MaxString;


         for ( strInd=0; strInd < NString; strInd++ ){
           for ( m=0; m < strArray[0][strInd].wordArray.size(); m++ ){
                   ris[0].x=strArray[0][strInd].wordArray[m].xp0;
                   ris[0].y=nrows-strArray[0][strInd].wordArray[m].yp0;

                   ris[1].x=strArray[0][strInd].wordArray[m].xp0;

                   ris[1].y=nrows-strArray[0][strInd].wordArray[m].yp1;

                   ris[2].x=strArray[0][strInd].wordArray[m].xp1;

                   ris[2].y=nrows-strArray[0][strInd].wordArray[m].yp1;

                   ris[3].x=strArray[0][strInd].wordArray[m].xp1;

                   ris[3].y=nrows-strArray[0][strInd].wordArray[m].yp0;

                   ris[4].x=strArray[0][strInd].wordArray[m].xp0;

                   ris[4].y=nrows-strArray[0][strInd].wordArray[m].yp0;

                   ris[5].x=strArray[0][strInd].wordArray[m].xp0;

                   ris[5].y=nrows-strArray[0][strInd].wordArray[m].yp0;
                    Lp=0.5; Cp=color;  // толщина линии, цвет
                    if ( strArray[0][strInd].wordArray[m].tsertoFlag ) // != 0
                    { Lp=1.5; Cp=0x0000AA00; } // зеленый
                    if ( strArray[0][strInd].wordArray[m].spaceFlag )
                    { Lp=2.5; Cp=0xAF00AA00; } // светло серый
                    in=ImageProcessor->ImageEnView1->AddNewObject();
                    ImageProcessor->ImageEnView1->ObjPenColor[in]=(TColor)Cp; // цвет линии
                    ImageProcessor->ImageEnView1->ObjPenWidth[in]=Lp; // толщина линии
                    ImageProcessor->ImageEnView1->ObjKind[in]=iekPOLYLINE;
                    ImageProcessor->ImageEnView1->SetObjPolylinePoints(in,ris,5);
           } // m
         } // strInd
         ImageProcessor->ImageEnView1->Update();

/**/
// x0,y0,x1,y1
// x0,y0 координаты левого нижнего угла прямоугольника строки (глифа, слога, буквы).
// x1,y1 координаты правого верхнего угла прямоугольника строки (глифа, слога, буквы).

#endif    //
#endif
}//_____________________________________________________________________________



// Sorting  сортировка

// ---------------------------------------------------------------------------

void GBitsetContour::Sort(vector<int> &GBuf,int NSort){

   int y,x;
 // сортировка
   int trash=0;
   bool f=true;
   int i,j,Nff;

                    //  DC(NSort<<" NSort+ ");
                    if( NSort==0) { return; }
  /*
#ifdef DEBUGLVL
              DC(END);  DC(END);
              for ( x=0; x < NSort;  x++ ){      // x < d+1;
                DC(GBuf[x]<<"\t"); if (x%10==0)DC(END);  /// ТАБЛИЦА
                  }//for x
              DC(END);
#endif
  */

                        // "сортировка Шейкера".
                 // http://www.abc-it.lv/index.php/id/610

                              Nff=NSort;  // -1 ////
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
              DC(END);  DC(END);
              for ( x=0; x < NSort;  x++ ){      // x < d+1;
                DC(GBuf[x]<<"\t"); if (x%10==0)DC(END);  /// ТАБЛИЦА
                  }//for x
              DC(END);
#endif
  */
}//_____________________________________________________________________________



// Statistics Вычисление распределения вероятностей с параметром (Porog, Delta)

// Подпрограмма расчета моментов распределения: матожидания, дисперсии.

// -----------------------------------------------------------------------------


void GBitsetContour::Statistics(vector<int> &HBuf, vector<int> &GBuf,

                         int Porog, int Delta ) {
                         


  int x,y,d,p;

  vector<int> BufS(ncolumns);

  vector<int> BufR(ncolumns);


              if( NLet<=0 || NLet>ncolumns) { return; }


                                BufS=GBuf;


              for (  y=0; y < NLet-1; y++ ){ BufR[y+1]= GBuf[y+1]-GBuf[y]; }


                        

/*                   // TMP

              DC(END);            // size-1   N0Fase
              for ( x=0; x < NLet;  x++ ){      // x < d+1;
                DC(BufR[x]<<"\t"); if (x%10==0)DC(END);  /// ТАБЛИЦА
                  }//for x
              DC(END);

*/


                          // "сортировка Шейкера". // GBuf

                 // http://www.abc-it.lv/index.php/id/610
                             Sort(BufR,NLet-1);

             //             sort(BufR.begin(), BufR.end());



/*                            // TMP

              DC(END);            // size-1   N0Fase
              for ( x=0; x < NLet;  x++ ){      // x < d+1;
                DC(BufR[x]<<"\t"); if (x%10==0)DC(END);  /// ТАБЛИЦА
                  }//for x
              DC(END);

*/

              // фильтрация по порогу, отбрасывание хвостов распределения

              d=0;

              for (  y=0; y < NLet; y++ ){

                 if ( BufR[y] > Porog/8 && BufR[y] < Porog )

                    { BufR[d]=BufR[y]; d++; }

              }// for y



/*                               // TMP

              DC(END);            // size-1   N0Fase
              for ( x=0; x < d;  x++ ){      // x < d+1;
                DC(BufR[x]<<"\t"); if (x%10==0)DC(END);  /// ТАБЛИЦА
                  }//for x
              DC(END);

*/


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



/*

#ifdef DEBUGLVL

              // ВИЗУАЛИЗАЦИЯ цифровая

     DC(MeanSA<<" -MeanSA*10- "); DC(p<<" p "); DC(Delta<<" Delta ");DC(END);


               // TMP

              DC(END);            // size-1   N0Fase
              for ( x=0; x < NLet;  x++ ){      // x < d+1;
                DC(BufS[x]<<"\t"); if (x%10==0)DC(END);  /// ТАБЛИЦА
                  }//for x
              DC(END);


              // TMP

              DC(END);            // size-1   N0Fase
              for ( x=0; x < p;  x++ ){      // x < d+1;
                DC(BufR[x]<<"\t"); if (x%10==0)DC(END);  /// ТАБЛИЦА
                  }//for x
              DC(END);

#endif

*/

}//_____________________________________________________________________________


                        //////////////////

// Подпрограмма гребенчатого фильтра Comb Filter с параметрами ( dt, g ).

// -----------------------------------------------------------------------------


  void GBitsetContour::CombFilter(vector<int> &GBuf, int dt, int g) {


  int x;

                   // dt - задержка delay

                   // добротность гребенчатого фильтра;  1 < g < 10


     if( dt<=0 || dt>=ncolumns || g >= 10 || g <= 1) { return; }


     for (x=dt+4; x<ncolumns-dt-4; x++){GBuf[x]=(GBuf[x]+ GBuf[x-dt]*g/10);}

     for (x=ncolumns-dt-4; x>dt+4; x--){GBuf[x]=(GBuf[x]+ GBuf[x+dt]*g/10);}


}//_____________________________________________________________________________


//                        +++++++++++++++++++

// Подпрограмма расчета средней амплитуды в массиве с параметром ( ms-сдвиг ).

// -----------------------------------------------------------------------------


  void GBitsetContour::AmplitudeS(vector<int> &GBuf, int ms, int &AmSum) {


  int x;


// ms-сдвиг на ms позиций, те деление на степень двойки значений в исходном массиве.


          AmSum=0;

          for ( x=0; x < ncolumns; x+=1 ){ AmSum+=abs(GBuf[x]); }  // x++
          AmSum=AmSum /(ncolumns>>ms);   // >>ms


}//_____________________________________________________________________________



// Преобразование ГИЛБЕРТА с параметром (ширина) PGilb

// -----------------------------------------------------------------------------


 void GBitsetContour::filterGilbert(vector<int> &HBuf,
                             vector<int> &GBuf,
                             int MGilb,
                             int PGilb){
  int y;

            // MGilb - размер массива преобразования ГИЛБЕРТА
            // PGilb - параметр (ширина) преобразования ГИЛБЕРТА
                      //if( PGilb==0) { return; }

                      for ( y=0; y < 26; y++ ){ GBuf[y]=0; }
                      for ( y=MGilb-26; y < MGilb; y++ ){ GBuf[y]=0; }
 /*  */

         if ( PGilb==0 ) {
                      // преобразование ГИЛБЕРТА PGilb==7
               for (  y=8; y < MGilb-8; y++ ){
               GBuf[y]=(
                         (HBuf[y-7]-HBuf[y+7])/7 + (HBuf[y-6]-HBuf[y+6])/6
                       + (HBuf[y-5]-HBuf[y+5])/5 + (HBuf[y-4]-HBuf[y+4])/4
                       + (HBuf[y-3]-HBuf[y+3])/3 + (HBuf[y-2]-HBuf[y+2])/2
                       +  HBuf[y-1]-HBuf[y+1] )/2;
                    }// for y
            }


         if ( PGilb==1 ) {
                     // преобразование ГИЛБЕРТА PGilb==15
               for (  y=12; y < MGilb-12; y++ ){
               GBuf[y]=(
       //                + (HBuf[y-11]-HBuf[y+11])/11 + (HBuf[y-10]-HBuf[y+10])/10
       //                + (HBuf[y-9]-HBuf[y+9])/9 + (HBuf[y-8]-HBuf[y+8])/8
                       + (HBuf[y-7]-HBuf[y+7])/7 + (HBuf[y-6]-HBuf[y+6])/6
                       + (HBuf[y-5]-HBuf[y+5])/5 + (HBuf[y-4]-HBuf[y+4])/4
                       + (HBuf[y-3]-HBuf[y+3])/3 + (HBuf[y-2]-HBuf[y+2])/2
                       +  HBuf[y-1]-HBuf[y+1] )/2;
                    }// for y
            }


         if ( PGilb==2 ) {
                     // преобразование ГИЛБЕРТА PGilb==15
               for (  y=16; y < MGilb-16; y++ ){
               GBuf[y]=(
       //                + (HBuf[y-15]-HBuf[y+15])/15 + (HBuf[y-14]-HBuf[y+14])/14
       //                + (HBuf[y-13]-HBuf[y+13])/13 + (HBuf[y-12]-HBuf[y+12])/12
                       + (HBuf[y-11]-HBuf[y+11])/11 + (HBuf[y-10]-HBuf[y+10])/10
                       + (HBuf[y-9]-HBuf[y+9])/9 + (HBuf[y-8]-HBuf[y+8])/8
                       + (HBuf[y-7]-HBuf[y+7])/7 + (HBuf[y-6]-HBuf[y+6])/6
                       + (HBuf[y-5]-HBuf[y+5])/5 + (HBuf[y-4]-HBuf[y+4])/4
                       + (HBuf[y-3]-HBuf[y+3])/3 + (HBuf[y-2]-HBuf[y+2])/2
                       +  HBuf[y-1]-HBuf[y+1] )/2;
                    }// for y
            }


         if ( PGilb==3 ) {
                     // преобразование ГИЛБЕРТА PGilb==23
               for (  y=20; y < MGilb-20; y++ ){
               GBuf[y]=(
       //                + (HBuf[y-23]-HBuf[y+23])/23 + (HBuf[y-22]-HBuf[y+22])/22
       //                + (HBuf[y-21]-HBuf[y+21])/21 + (HBuf[y-20]-HBuf[y+20])/20
       //                + (HBuf[y-19]-HBuf[y+19])/19 + (HBuf[y-18]-HBuf[y+18])/18
       //                + (HBuf[y-17]-HBuf[y+17])/17 + (HBuf[y-16]-HBuf[y+16])/16
                       + (HBuf[y-15]-HBuf[y+15])/15 + (HBuf[y-14]-HBuf[y+14])/14
                       + (HBuf[y-13]-HBuf[y+13])/13 + (HBuf[y-12]-HBuf[y+12])/12
                       + (HBuf[y-11]-HBuf[y+11])/11 + (HBuf[y-10]-HBuf[y+10])/10
                       + (HBuf[y-9]-HBuf[y+9])/9 + (HBuf[y-8]-HBuf[y+8])/8
                       + (HBuf[y-7]-HBuf[y+7])/7 + (HBuf[y-6]-HBuf[y+6])/6
                       + (HBuf[y-5]-HBuf[y+5])/5 + (HBuf[y-4]-HBuf[y+4])/4
                       + (HBuf[y-3]-HBuf[y+3])/3 + (HBuf[y-2]-HBuf[y+2])/2
                       +  HBuf[y-1]-HBuf[y+1] )/2;
                    }// for y
            }
 /* */

         if ( PGilb==4 ) {
                     // преобразование ГИЛБЕРТА PGilb==23
               for (  y=24; y < MGilb-24; y++ ){
               GBuf[y]=(
       //                + (HBuf[y-23]-HBuf[y+23])/23 + (HBuf[y-22]-HBuf[y+22])/22
       //                + (HBuf[y-21]-HBuf[y+21])/21 + (HBuf[y-20]-HBuf[y+20])/20
                       + (HBuf[y-19]-HBuf[y+19])/19 + (HBuf[y-18]-HBuf[y+18])/18
                       + (HBuf[y-17]-HBuf[y+17])/17 + (HBuf[y-16]-HBuf[y+16])/16
                       + (HBuf[y-15]-HBuf[y+15])/15 + (HBuf[y-14]-HBuf[y+14])/14
                       + (HBuf[y-13]-HBuf[y+13])/13 + (HBuf[y-12]-HBuf[y+12])/12
                       + (HBuf[y-11]-HBuf[y+11])/11 + (HBuf[y-10]-HBuf[y+10])/10
                       + (HBuf[y-9]-HBuf[y+9])/9 + (HBuf[y-8]-HBuf[y+8])/8
                       + (HBuf[y-7]-HBuf[y+7])/7 + (HBuf[y-6]-HBuf[y+6])/6
                       + (HBuf[y-5]-HBuf[y+5])/5 + (HBuf[y-4]-HBuf[y+4])/4
                       + (HBuf[y-3]-HBuf[y+3])/3 + (HBuf[y-2]-HBuf[y+2])/2
                       +  HBuf[y-1]-HBuf[y+1] )/2;
                    }// for y
            }
 /* */
         if ( PGilb==5 ) {
                    // преобразование ГИЛБЕРТА PGilb==31
               for (  y=32; y < MGilb-32; y++ ){
               GBuf[y]=(
                       + (HBuf[y-31]-HBuf[y+31])/31 + (HBuf[y-30]-HBuf[y+30])/30
                       + (HBuf[y-29]-HBuf[y+29])/29 + (HBuf[y-28]-HBuf[y+28])/28
                       + (HBuf[y-27]-HBuf[y+27])/27 + (HBuf[y-26]-HBuf[y+26])/26
                       + (HBuf[y-25]-HBuf[y+25])/25 + (HBuf[y-24]-HBuf[y+24])/24
                       + (HBuf[y-23]-HBuf[y+23])/23 + (HBuf[y-22]-HBuf[y+22])/22
                       + (HBuf[y-21]-HBuf[y+21])/21 + (HBuf[y-20]-HBuf[y+20])/20
                       + (HBuf[y-19]-HBuf[y+19])/19 + (HBuf[y-18]-HBuf[y+18])/18
                       + (HBuf[y-17]-HBuf[y+17])/17 + (HBuf[y-16]-HBuf[y+16])/16
                       + (HBuf[y-15]-HBuf[y+15])/15 + (HBuf[y-14]-HBuf[y+14])/14
                       + (HBuf[y-13]-HBuf[y+13])/13 + (HBuf[y-12]-HBuf[y+12])/12
                       + (HBuf[y-11]-HBuf[y+11])/11 + (HBuf[y-10]-HBuf[y+10])/10
                       + (HBuf[y-9]-HBuf[y+9])/9 + (HBuf[y-8]-HBuf[y+8])/8
                       + (HBuf[y-7]-HBuf[y+7])/7 + (HBuf[y-6]-HBuf[y+6])/6
                       + (HBuf[y-5]-HBuf[y+5])/5 + (HBuf[y-4]-HBuf[y+4])/4
                       + (HBuf[y-3]-HBuf[y+3])/3 + (HBuf[y-2]-HBuf[y+2])/2
                       +  HBuf[y-1]-HBuf[y+1] )/3;
                    }// for y
         }


         if ( PGilb==6 ) {
              // ассиметричное преобразование ГИЛБЕРТА
              for ( y=4; y < MGilb-4; y++ ){
                GBuf[y]=abs(
                             (HBuf[y-3]-HBuf[y+2])/3 +
                             (HBuf[y-2]-HBuf[y+1])/2 +
                              HBuf[y-1]-HBuf[y]
                           );
              }// for y
          }
/*   */

#ifdef DEBUGLVL
// DC(*MGilb<<" -*MGilb- ");DC(END);
#endif


  }//___________________________________________________________________________


                               ////

                            //     //

                       /////        /////


// Подпрограмма визуализация спектра imaging spectrum .

// -----------------------------------------------------------------------------


  void GBitsetContour::ImagingSpectrum(vector<int> &HBuf) {


  int y,x,n,p,d,g;

  int DnKH,LfAmSum;

  int size=DeltaNstrKH*8;    //  SmGr=nrows/4,scope=8,

  vector<int> BufR(ncolumns);

  vector<int> BufS(size);

  vector<int> BufHelp(ncolumns);

  // fabs


                       BufHelp.assign(ncolumns,0);

                     // ВИЗУАЛИЗАЦИЯ максимума сректра
// линейное нахождение максимума Функции ( максимум сректра )
// (средней резонансной пространственной частоты букв в строке).
// Функция состоит из: гребенчатого фильтра, полосового фильтра и амплитудного детектора.

    g=3; // добротность гребенчатого фильтра = 3;  1 < g < 1
    DnKH=(DeltaNstrKH*5/2-DeltaNstrKH/2)/16; // 16-число дискретных отсчетов // DeltaNstrKH/8;
    if ( DnKH<1 ) DnKH=1;
    d=0; p=0;
    for ( n=DeltaNstrKH/2; n<DeltaNstrKH*5/2 && n<size/2; n=n+DnKH ){ //12
           BufR=HBuf;
          filterLaplasian(BufR,n/4,(n/4)*2); // полосовой фильтр, (n/4)*2) это не ошибка
          CombFilter(BufR, n, g);            // гребенчатый фильтр, резонансный фильтр
          AmplitudeS(BufR, 2, LfAmSum);      // получение средней амплитуды
           BufS[n+size/2]=LfAmSum;
           p=p+DnKH;  d++;
////           DC(n<<"n  "); DC(LfAmSum<<"  ");
    }// for n
////    DC(END);


          //  нахождение min Функции maxRes
          int minResY, minRes=9999;
          for ( y=DeltaNstrKH/2; y<DeltaNstrKH*5/2; y=y+DnKH ){
              if( BufS[y+size/2] < minRes && BufS[y+size/2]!= 0 ) //
              { minRes=BufS[y+size/2]; minResY=y; }
          } // minResY  координаты min Функции maxRes

/* */

          // вычитание фона ( minResY ) из сректра

          for ( y=DeltaNstrKH/2; y<DeltaNstrKH*5/2; y=y+DnKH )

          { BufS[y+size/2]=(BufS[y+size/2]-minRes)*8; }

          // фильтрация максимума Функции
          // смещение на size/2 делает менее актуальным краевые  эффекты при фильтрации
          int DnKHF=DeltaNstrKH/3;  // *3/2;
          if ( DnKHF<2 ) DnKHF=1;   if ( DnKHF>=31 ) DnKHF=31;
          filterLaplasian(BufS,DnKHF,DnKHF*2);  // полосовой фильтр  ,31,62

          //  нахождение максимума сректра ( максимума Функции BufS )
          int maxRes=0, maxResY, maxResYs;
          for ( y=DeltaNstrKH/2; y<DeltaNstrKH*5/2; y=y+1 ){
                 if( BufS[y+size/2] >= maxRes )
                 { maxRes=BufS[y+size/2]; maxResY=y+size/2; }
          } // maxResY  координаты максимума Функции maxRes


          //  максимум сректра

          maxResYs=maxResY-size/2;


//// DC(END); DC(maxResYs<<"-maxResYs-  ") DC(minRes<<"minRes  "); DC(maxResY<<"maxResY  "); ;
//// DC(maxRes<<"maxRes  "); DC(d<<"d  ");  DC(DnKH<<"DnKH  "); DC(END);

          for ( y=0; y < size; y++ ){  //
            BufHelp[y+ncolumns/2-size/2]=BufS[y]/8;
          }// for y

/*
#ifdef DEBUGLVL
                       // ВИЗУАЛИЗАЦИЯ  параметров
                                 DC(END);
DC(KHig<<" KHig ") ;DC(DeltaNstr<<" DeltaNstr ");DC(DeltaNstrKH<<" DeltaNstrKH ");
                                 DC(END);

                       // ВИЗУАЛИЗАЦИЯ цифровая, таблица
              DC(END);            // size-1   N0Fase
              for ( x=0; x < size;  x++ ){      // x < d+1;
                DC(BufS[x]<<"\t"); if (x%10==0)DC(END);  /// ТАБЛИЦА
                  }//for x
              DC(END);

                       // ВИЗУАЛИЗАЦИЯ аналоговая
 // ВИЗУАЛИЗАЦИЯ аналоговая исходных вертикальных сумм в пределах строки (черная)
  int M=1; static short delta=nrows/2-nrows/20; // 300
  for(x=0; x < ncolumns; x++) {
   if(BufHelp[x]>=0){ for (y=delta; y<(BufHelp[x]/M)+delta; y++)drawData[0][y][x]*=0.1; }
   else             { for (y=delta; y>(BufHelp[x]/M)+delta; y--)drawData[0][y][x]*=0.1; }

  } // x++  // 0.8*ncolumns;

#endif
*/


}//_____________________________________________________________________________





////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
//                        FFFFFFFFFFFFFFFFFF
// Подпрограмма объединяет: гребенчатый фильтр, амплитудный детектор.

// -----------------------------------------------------------------------------


  void GBitsetContour::FunctionSpectrum( vector<int> &HBuf, int dt, int &AmSum) {



  int x, ds=dt+4;

  int size=HBuf.size();

//  int size=ncolumns;




     // Подпрограмма гребенчатого фильтра Comb Filter с параметрами ( dt, g ).


     // добротность гребенчатого фильтра;  1 < g < 10

     /// if( dt<=0 || dt>=size || g >= 10 || g <= 1) { return; }


     int g=3; // dt - задержка delay

     for (x=ds; x<size-ds; x++){HBuf[x]=(HBuf[x]+ HBuf[x-dt]*g/10);}

     for (x=size-ds; x>ds; x--){HBuf[x]=(HBuf[x]+ HBuf[x+dt]*g/10);}



     // Подпрограмма расчета средней амплитуды в массиве с параметром ( ms-сдвиг ).


     int ms=1;

     AmSum=0;

     for ( x=8; x < size-8; x+=2 ){ AmSum+=abs(HBuf[x]); } // x++; x+=1 //x+=2 ms=1;
     AmSum=AmSum /(size>>ms);   // >>ms

     // ms-сдвиг на ms позиций, те деление на степень двойки значений

     // в исходном массиве.

// DC(size<<" sizeF ");  DC(END);


}//_____________________________________________________________________________

/**/



// -----------------------------------------------------------------------------

// Полосовой фильтр Гауссиан (ГАУССИАН - Gaussian), попытка минимальной реализации.

// Адаптивный F(KHig) нолевой бордюр вокруг массивов

// -----------------------------------------------------------------------------


 void GBitsetContour::filterLaplasianM( vector<int> &HBuf,

                                 vector<int> &GBuf,

                                 int KHig, int KLow){


 int y,Klw,Khg,S;
 int size=HBuf.size();

 if ( KHig<2 ) KHig=1;   if ( KHig>63 ) KHig=63;
 if ( KLow<2 ) KLow=2;   if ( KLow>63 ) KLow=63;
 S=KLow;  if ( S < KHig ) S=KHig;
 // Sn=129        257        385         514        при S=64,   KhgN=KHig*N+1
 int   S2=S*2+1,  S4=S*4+1,  S3=S*6+1,   S8=S*8+2;

 vector<int> BufIn(size+S8);   // 514
 vector<int> BufOut1(size+S8);
 vector<int> BufOut2(size+S8);
 vector<int> lt1(size+S8);
 vector<int> lt2(size+S8);


    for ( y=0; y < size; y++ ){BufIn[y+S4]=HBuf[y];} // Входной буфер BufIn[y]

      Khg=KHig*KHig; Klw=KLow*KLow;
      for ( y=S2; y < size+S3; y++ ) { //треугольная весовая функция, прямая фильтрация
         lt1[y]=-lt1[y-2]+2*lt1[y-1]+BufIn[y-KHig-KHig]-2*BufIn[y-KHig]+BufIn[y]; //k=15+
         lt2[y]=-lt2[y-2]+2*lt2[y-1]+BufIn[y-KLow-KLow]-2*BufIn[y-KLow]+BufIn[y]; //k=63+
      }
      for ( y=0; y < size+S8; y++ ) { lt1[y]=lt1[y]/Khg; lt2[y]=lt2[y]/Klw; }//Norm
      for ( y=size+S3; y > S2; y--) { //треугольная весовая функция, инверсная фильтрация
         BufOut1[y]=-BufOut1[y+2]+2*BufOut1[y+1]+lt1[y+KHig+KHig]-2*lt1[y+KHig]+lt1[y];//k=15-
         BufOut2[y]=-BufOut2[y+2]+2*BufOut2[y+1]+lt2[y+KLow+KLow]-2*lt2[y+KLow]+lt2[y];//k=63-
      }
      for ( y=S4; y < size+S4; y++ ){ GBuf[y-S4]=BufOut1[y]/Khg-BufOut2[y]/Klw; }
      // Выход In[y-S4]
/**/
//DC(size<<" sizeG ");  DC(END);
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




////////////////////////////////////////////////////////////////////////////////


