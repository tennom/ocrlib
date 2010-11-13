//  ----------------------------------------------------------------------------
// --- Page Steck Detector --- GBitsetStack.h ---
// Подпрограмма распознования вертикальных стеков в пределах строки.
// Только - только начата.
//  ----------------------------------------------------------------------------

void GBitset::pageStackDetector (vector<int> &HBuf,
                                 vector<int> &GBuf) {
                                

TIME_START

        if( NStrok<0) { return; }





        // Запуск подпрограммы предвармтельнного определения наличия стеков
                    PredvStackDetector(HBuf,GBuf);
/*
        // Запуск подпрограммы получения координат прямоугольников вокруг стеков.
                    SquareStackDetector();

        // Запуск подпрограммы распознования стеков в пределах строки.
                    RecognitionStack();


*/
TIME_PRINT

      // получили маркер (в структуре) на наличие стека вместо коренной буквы.

        DM(END);  DM(0000<<" pagePointDetector ");  DM(END);

}//_____________________________________________________________________________


//  ----------------------------------------------------------------------------
// Запуск подпрограммы предвармтельнного определения наличия стеков
// задача не пропустить стек и отсеить прямоугольников заведомо с коренными буквами
//  ----------------------------------------------------------------------------

void GBitset::PredvStackDetector(vector<int> &HBuf,
                                 vector<int> &GBuf){


  int y,x,p,d,m,n,s0,s1;
  int x0,x1,y0,y1;
  int NWord,res,Prg1,Prg2;  // DltNstrN,DltNstrNKh,
//  vector<int> BufHelp(ncolumns);


//TIME_START

   // получение коэффициента масштабирования печа
    int DeltaKh = 100*ncolumns/srcW*srcH/nrows;  //ncolumns/srcW*srcH/nrows;
   //   int DeltaKh = 100*ncolumns*srcH/srcW/nrows;

   for ( Nstr=0; Nstr < strArray->size(); Nstr++ ){ // Цикл по количеству строк NStrok

        NWord = strArray[0][Nstr].wordArray.size();
        for ( Nwrd=0; Nwrd < NWord; Nwrd++ ){ // Цикл по количеству квадратиков вдоль строки NWord

            wordOCR *wP=&strArray[0][Nstr].wordArray[Nwrd];
            // x0,x1, y0,y1 координаты квадрата вокруг буквы
            x0 = wP->x0;    x1 = wP->x1;    y0 = wP->y0;    y1 = wP->y1;

            // получение области поиска стеков - прямоугольников
            res=0;   s0=y0-(y1-y0);  s1=y0;

            strArray[0][Nstr].wordArray[Nwrd].yt1 = s1;
            strArray[0][Nstr].wordArray[Nwrd].yt0 = s0;
            strArray[0][Nstr].wordArray[Nwrd].xt1 = x1;
            strArray[0][Nstr].wordArray[Nwrd].xt0 = x0;

            for ( y=s0; y < s1; y++ ) { // горизонтальный цикл
                d=y*ncolumns;
                for ( x=x0; x<x1 && x<ncolumns; x++ ) { // копирование из bits_data в HBuf
                    res+=bits_data[d + x];
                    // визуализация (серым) области поиска стеков - прямоугольников
                    drawData[0][y][x]*=0.8;      // визуализация //
                    } // for x
//                SP->filterHigh(HBuf,KHigHKh); // сглаживание HBuf ФИЛЬТР НИЗКИХ ЧАСТОТ
            } // for y

            Prg1=(x1-x0)*(y1-y0)/8;   // порог по площади области поиска стеков
            Prg2=DeltaKh*10*(y1-y0)/(abs(x1-x0)+1)/100;  // порог по прямоугольности области поиска
            if ( res > Prg1 && Prg2 < 15)
            { strArray[0][Nstr].wordArray[Nwrd].steckFlag = 1; }
            


        } // Nwrd   // Цикл по количеству квадратиков вдоль строки NWord

   } // for Nstr  // Цикл по количеству строк NStro



/**/
#ifdef DEBUGLVL

// Визуализация скорректированных по горизонтали букв темно синими квадратиками //
                   wordDraw(0x00AA0011);  // темно синий

DM(END);  DM(1111<<" PredvSteckDetector ") DM(DeltaKh<<" DeltaKh ")
DM(srcW<<" srcW ") DM(srcH<<" srcH ") DM(END);

#endif

//TIME_PRINT



/**/

}//__________________________________________________________________________



 
