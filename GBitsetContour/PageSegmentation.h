

//  ----------------------------------------------------------------------------
// Запуск подпрограм для выделения рамки вокруг текста печа.
//  ----------------------------------------------------------------------------
void GBitsetContour::startFrameDetector(vector<int> &HStr,
                                 vector<int> &HBuf,
                                 vector<int> &GBuf) {

// HBuf, GBuf переменной длинны nrows или ncolumns,
// в HStr лежат горизонтальные суммамы
// в LStr кладем вертикальные суммамы

  vector<int> LStr(ncolumns);
  int y,x,d;
  int res=0;

        //void LSum(vector<int> &L);  // заполняет массив L вертикальными суммами
        //void HSum(vector<int> &H);  // заполняет массив H горизонтальными суммами

                       LStr.assign(ncolumns,0);

             // подсчет вертикальных сумм
             //int d;
             for ( x=0; x < ncolumns; x++ ) {  // read image make sum
                   res=0;
                   for ( y=0; y < nrows; y++ ) {
                        d=y*ncolumns;  res+=bits_data[d + x];
                       }  // for y
                 LStr[x]=res<<5; // ВАЖНО - сумма вдоль строк домножена на *256 res<<8;
           //        LStr[x]=res;
                 }  //  for x


       // Запуск подпрограм для выделения рамки вокруг текста печа.
       pageFrameDetector(LStr,HStr,GBuf);

       // подпрограмма фильтрации плато.
       platoDetector(HStr,HBuf,GBuf);
       // в HStr[y] получили горизонтальные суммы без плато.


/*  // ВИЗУАЛИЗАЦИЯ аналоговая исходных вертикальных сумм (черная), для LStr[x]>=0
  int M=64; static short delta=nrows*10/60; // 300
  for(x=0; x < ncolumns-16; x++) {
  for (y=delta; y<(LStr[x]/M)+delta; y++)drawData[0][y][x+16]*=0.1;} // 0.8*ncolumns;
*/

/**/
}//_____________________________________________________________________________


//  ----------------------------------------------------------------------------
// Подпрограмма выделения рамки вокруг текста печа.
//  ----------------------------------------------------------------------------
void GBitsetContour::pageFrameDetector(vector<int> &LStr,
                                vector<int> &HStr,
                                vector<int> &GBuf) {

int y,x,d;


        //void LSum(vector<int> &L);  // заполняет массив L вертикальными суммами
        //void HSum(vector<int> &H);  // заполняет массив H горизонтальными суммами
        
// http://ru.wikipedia.org/wiki/

// Применительно к массивам данных, поиск осуществляется по ключу, присвоенному
// каждому из элементов массива (в простейшем случае сам элемент является ключом).

// Двоичный (бинарный) поиск (также известен, как метод деления пополам и метод
// половинного деления) — алгоритм нахождения заданного значения монотонной
// (невозрастающей или неубывающей) функции. Поиск основывается на теореме о
// промежуточных значениях.


// В качестве примера можно рассмотреть поиск значения монотонной функции,
// записанной в массиве, заключающийся в сравнении срединного элемента массива
// с искомым значением, и повторением алгоритма для той или другой половины,
// в зависимости от результата сравнения.

// Пускай переменные Lb и Ub содержат, соответственно, левую и правую границы
// отрезка массива, где находится нужный нам элемент. Исследования начинаются
// со среднего элемента отрезка. Если искомое значение меньше среднего элемента,
// осуществляется переход к поиску в верхней половине отрезка, где все элементы
// меньше только что проверенного, то есть значением Ub становится M - 1 и на 
// следующей итерации исследуется только половина массива. Т.о., в результате 
// каждой роверки область поиска сужается вдвое.

// Например, если длина массива равна 1023, после первого сравнения область
// сужается до 511 элементов, а после второй — до 255.Т.о. для поиска в массиве
// из 1023 элементов достаточно 10 сравнений.

/*
int function BinarySearch (Array A, int Lb, int Ub, int Key);
  begin
  do forever
    M = Lb + (Ub-Lb)/2;
    if (Key < A[M]) then
      Ub = M - 1;
    else if (Key > A[M]) then
      Lb = M + 1;
    else
      return M;
    if (Lb > Ub) then
    return -1;
  end;
*/
                    

/*
int Lb=0,Ub=ncolumns; // левая и правая граница отрезка массива
int Key=100, K; // Key - искомое значение, K - адрес искомого значения в массиве
vector<int> A(ncolumns);
//map<int,int> AMap;  // AMap[x]=x;

                     //  TEST
         for ( x=0; x < ncolumns; x++ ) { A[x]=x; }  //  for x

DC(END);
//if (Lb > Ub);
for ( x=0; Key != A[K] && x < 16; x++ ) { //  else if (Key == A[K]) break;
     K = Lb + (Ub-Lb)/2;
     if (Key < A[K]) Ub = K - 1;
     else
     if (Key > A[K]) Lb = K + 1;
DC(K<<" K ");
     }  //  for x

        DC(END); DC(Key<<" Key "); DC(K<<" K "); DC(END);

*/
    //    if(AMap.find(100) != AMap.end()){
    //    DC("AMap[100]="<<AMap[100]<<END);  }





/*
#ifdef DEBUGLVL
   //  Вешается на одиночной букве
   // ВИЗУАЛИЗАЦИЯ аналоговая исходных горизонтальных сумм (черная), для HStr[y]>=0
   int M=16; static short delta=50;
   for(y=0; y < drawData->rows(); y++) {
   for(x=delta; x<(HStr[y]/M)+delta; x++)drawData[0][y][x]*=0.1;} // 0.8*ncolumns;
#endif
*/
// pageSegmentation PageSegmentation

}//_____________________________________________________________________________





// подпрограмма фильтрации плато.
// -----------------------------------------------------------------------------

void GBitsetContour::platoDetector(vector<int> &HStr,
                            vector<int> &HBuf,
                            vector<int> &GBuf){
/*
  int y,d,sm,maxF,maxP,DLt,Porog;
  int scope=1,y0,y1;
  vector<int> BufS(nrows);
  vector<int> BufR(nrows);


                            HBuf=HStr;

              sm=20;
              //  сильная фильтрация (32) исходных горизонтальных сумм
              filterHigh(HBuf,KHig*16);
              filterHigh(HBuf,KHig*16);
           // filterHigh(HBuf,64);


              DC(END); DC(KHig*16<<" KHig*16 "); DC(END);
#ifdef DEBUGLVL
// вызов функции рисования переменной длинны, зеленый
LDrawVar(HBuf,nrows,sm,scope,0x0000AA00);
#endif

              // вычисление максимума maxF сильно фильтрованных исходных сумм
              maxF=0; DLt=nrows/32; int HBf;
              for ( y=DLt; y < nrows-DLt; y=y+8 ) {
                HBf=HBuf[y];
                if( HBf > maxF )
                  { maxF= HBf; } // maxF - max HBuf[y]
              } // for y

///////////////////

              // бинаризация сильно фильтрованных исходных  сумм
              maxP=maxF*2/5;  d=0;
              for ( y=1; y < nrows-1; y++ ) {
                  HBf=HBuf[y] ;
                  if   ( HBf >= maxP  )  { HBf = 1; }
                  else { HBf = 0; }
                  HBuf[y]=HBf*HBuf[y];

                  if( HBuf[y]<=maxP && HBuf[y+1]>maxP ) {
                  BufS[d]=y;  d++; DC(END); DC(y<<" yy0 "); }

                  if( HBuf[y]>=maxP && HBuf[y+1]<maxP ) {
                  BufS[d]=y;  d++; DC(END); DC(y<<" yy1 "); }
              } // for y   d+=2;
////              DC(END); DC(d<<" d "); DC(END);


#ifdef DEBUGLVL
// вызов функции рисования переменной длинны, красный
LDrawVar(HBuf,nrows,sm,scope,0x000000FF);
#endif
*/
/**/

 /*
              // запуск подпрограммы фильтрации строк
              KFStrok=0;
              int Pv1=0;   int Pv2=0;
 /////////             RepeadStringDetector(HStr,HBuf,GBuf);  /////////
              DC(END); DC(NStrok<<" NStrok "); DC(END);


              // получение координат строк y0, y1 из структуры ( NStrok=strArray.size(); )
                int dn=0;
                for ( y=0; y < d; y+=2 ){    // d+++1
                    dn=0;
                    for (int NStrok=0; NStrok < strArray->size(); NStrok++ ){ // Цикл по колличеству строк NStrok
                     y0=strArray[0][Nstr].y0;
                     y1=strArray[0][Nstr].y1;
                     DC(END); DC(y0<<" y0 ");DC(y1<<" y1 "); DC(END);
                       if ( y0>=BufS[y] && y1>=BufS[y] && y0<=BufS[y+1] && y1<=BufS[y+1] )
                     { dn++;  BufR[y]=dn; }
                    } // NStrok
                } // y

                // ВИЗУАЛИЗАЦИЯ цифровая 1
                DC(END);
                for ( y=0; y < d;  y++ ){
                 DC(BufR[y]<<"\t"); if (y%10==0)DC(END);  /// ТАБЛИЦА
                }//for y

/////////////////

              // бинаризация сильно фильтрованных исходных  сумм
              // порог надо брать из общей сегментации страници
              // maxP=maxF/2;  Porog=maxP*ncolumns/nrows*512/nrows;
              if   ( Porog > 165 )   // 165, 190
              {
                for ( y=0; y < nrows; y++ ) {
                  HBf=HBuf[y] ;
                  if   ( HBf > maxP  )  { HBf = 0; }
                  else { HBf = maxF; }
                  HStr[y]=HStr[y] + HBf;
                } // for y
              }
*/

/*
#ifdef DEBUGLVL
//                     ShowMessage(Porog);

              DC(END); DC(maxF<<" maxF "); DC(END); DC(END);
LineVertical(maxP+sm, 0x00AA0011);         // ТЕМНО СИНИЙ
//LDraw(HBf,sm,0x000000FF);                // вызов функции рисования красный
//LDrawVar(HBuf,nrows,sm,scope,0x000000FF);// вызов функции рисования пер. длинны, красный

#endif
*/
/**/
}//_____________________________________________________________________________


