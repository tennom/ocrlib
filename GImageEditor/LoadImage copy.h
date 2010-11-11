/** \fn void GImageEditor::RemoveBorder(GBitmap *data,  GBitset *set,
 string &filePath)
 \brief Remove black border around scaned page  
 
 обработка скана в виде ОДНОГО БЛОКА
 Создание из скана одного блока текста (печа) не зависимо от того
 есть ли колонки в тексте или их нет в виде;
 файлов - (jpg) с добавлением Border, или
 файлов - (jpg) с добавлением сдвига (change) (выключки) блока текста.
 при сохранении исходного размера скана.
 */
   void GImageEditor::RemoveBorder(GBitmap *data, 
						       GBitset *set,
						       int pageBorder,
						       string &filePath){

	   
		int xfg0,xfg1,yfg0,yfg1;    // координаты прямоугольника вокруг колонок
	           int brd=30;//set->Brd;           // brd=border;  где Brd - глобальная /////////////
		int hp=data->rows();        // -brd*2 //+64*2  border*2   // hp=nrows;
	           int wp=data->columns();        // -brd*2 //+64*2  border*2   // hp=nrows;
		unsigned char *pSrc;
		int nFrm;
		
		///     // вычисленное количество строк в печа - NStrok=strArray.size();
		///            NStrok=strArray->size();
		///            if( NStrok<3 ) { return; }
		
		
		// получение координат x,y файлов - колонок (число колонок =0)
		//int nFrame=set->frameArray.size();  // nFrame - номера колонок 1,2,3...   1-печа
		//nFrm=nFrame-1;
		nFrm=0;   // nFrm - номера колонок 0,1,2,3...   0-печа
	           if(!set->frameArray.size())return;
		frameOCR *wF=&set->frameArray[nFrm];
		//////  xfg0=wF->Xfg0;   xfg1=wF->Xfg1;   yfg0=wF->Yfg0;   yfg1=wF->Yfg1;
		xfg0=wF->Xfg0+brd-2;  xfg1=wF->Xfg1-brd+2;
		if( xfg0<0)xfg0=0; if( xfg1>wp)xfg1=wp;
		yfg0=wF->Yfg0+brd-2;  yfg1=wF->Yfg1-brd+2;
	          
		// задание размеров выходного файла
		int w=xfg1-xfg0+pageBorder*2;
		int h=yfg1-yfg0+pageBorder*2;
	           GBitmap *cropImg = GBitmap::create(h,w,0);
	            
	           //cout<<" w="<<w<<" h="<<h<<" data->columns()="<<data->columns()<<END;
		//cout<<"yfg0="<<yfg0<<" yfg1="<<yfg1<<" xfg0="<<xfg0<<" xfg1="<<xfg1<<END;
		// cout<<hp<<" hp "<<nFrm<<" nFrm "<<yfg1<<" yfg1 "<<yfg0<<" yfg0 "<<END;
		//cout <<"nFrm="<<nFrm<<"yfg1"<<yfg1<<"yfg0"<<yfg0<<END;
		//cout<<"strArray.size()="<<strArray.size()<<END;
		
		int x,y,p,q,yInd;
		int nColumn,nClm,nColum0,nColumN;
		int yf0,yf1;      // координаты прямоугольника вокруг вертикальной
		// колонки, касающийся краёв горизонтальных блок букв
		int x0,x1,y0,y1;  // координаты прямоугольника вокруг горизонтальных
		// блоков описывающих многоугольники колонок
		
		// Левый и правый бордюр, заполнение белым (255)
		nColumn=set->frameArray[nFrm].columnArray.size();
	           yInd=pageBorder;
	           int a; 
		for ( nClm=nColumn-1; nClm >= 0; nClm-- ){ // Цикл по количеству блоков строк Clm
			columnOCR *wC=&set->frameArray[nFrm].columnArray[nClm];
			x0=wC->Xc0;   x1=wC->Xc1;   y0=wC->Yc0;   y1=wC->Yc1;
			//cout<<" xfg0="<<xfg0<<" xfg1="<<xfg1<<" x0="<<wC->Xc0<<"  x1="<<wC->Xc1<<"  y0="<<wC->Yc0<<"  y1="<<wC->Yc1<<END;
			for (y = y1;  y < y0; y++){
				pSrc = cropImg->bytes_data;
				pSrc +=yInd*w+pageBorder; yInd++;
				q++;  // p++;  if(q>h){q=h;}
				for (x=xfg0; x < xfg1; x++){
					 if( x > x0 && x < x1 ) {
						 *pSrc=data[0][y][x];
					  } // 254-белое
					 else{ *pSrc=255; }  // 0-черное, 255-белое
					 pSrc++;
				}
			}
		///DM(nClm<<" nClm "); DM(hp-y1<<" hp-y1 "); DM(hp-y0<<" hp-y0 "); DM(q<<" q2 "); DM(p<<" p ");  DM(END);
		} // Цикл по количеству блоков колонок nClm
	   cout<<"filePath="<<filePath<<END;
	   WriteImageData(cropImg,filePath,0);
	   cropImg->destroy();
	   delete cropImg;
	   
}//_____________________________________________________________________________

/** @fn  void GImageEditor::WriteSpreadData(GBitmap *data,  GBitset *set,
 int nFrm,  string &filePath)
  @brief обработка скана (разворотов книги) с РАЗДЕЛЕНИЕМ  на файлы - СТРАНИЦЫ
  
 Исходная сканированная страница разворота книги разделяется на два файла в формате  jpg
 с именами исходного файла и добавлением суффикса номера страницы в развороте
 */
 void GImageEditor::WriteSpreadData(GBitmap *data,  
							GBitset *set,
							int nFrm,  
							string &filePath){


  int xfg0,xfg1,yfg0,yfg1;        // координаты прямоугольника вокруг колонок
  int brd=set->Brd;               // brd=border;  где Brd - глобальная /////////
  int wp=data->columns(); //- brd*2; // w=  -64*2                      /////////
  int hp=data->rows();    //- brd*2; // h=  -64*2                      /////////
  unsigned char *pSrc;


///     // вычисленное колличество строк в печа - NStrok=strArray.size();
///             NStrok=strArray->size();
///            if( NStrok<3 ) { return; }


		// получение координат x,y файлов - страниц
	          
		int TurnXL=set->TurnX;  //ShowMessage(TurnXL);
                      cout<<"TurnXL="<<TurnXL<<END;
	 
		if( TurnXL==0 ) { return; } // НЕТ вертикальной линии разделения скана
		if( nFrm >-1 || nFrm <-2 ) { return; }

		// получение координат x,y файлов - страниц
		if( nFrm==-1 ) { xfg0=0;   xfg1=TurnXL;  yfg0=0; yfg1=hp; } // левая  страница
		if( nFrm==-2 ) { xfg0=TurnXL;  xfg1=wp;  yfg0=0; yfg1=hp; } // правая страница

		int w=xfg1-xfg0;
		int h=yfg1-yfg0;
		GBitmap *cropImg = GBitmap::create(h,w,0);
// DM("yfg0="<<yfg0<<" yfg1="<<yfg1<<" xfg0="<<xfg0<<" xfg1="<<xfg1<<" w="<<w<<" h="<<h<<END);

  /// разделение на страницы. Создание файлов (jpg).
  // Создание файлов (jpg) без стирания изображения по периметру
			   int x,y,p=0;
			   for (y = 0; y < h; y++){
				  pSrc = cropImg->bytes_data;
				  pSrc+=y*w;  
				  p=y + hp-yfg1;
				  for (x=xfg0; x < xfg1; x++){
							*pSrc=data[0][p][x];  //  куда
							pSrc++;
				}}
	 //  detectRotation(nFrm);
	 cout<<"filePath="<<filePath<<END;
	 WriteImageData(cropImg,filePath,0);
	 cropImg->destroy();
	 delete cropImg;
	 
}//_____________________________________________________________________________

/** @fn void GImageEditor::WriteColumnsData(GBitmap *data, GBitset *set,  int nFrm,  string &filePath)
  @brief обработка скана с РАЗДЕЛЕНИЕМ НА КОЛОНКИ
   
   Исходная сканированная страница книги содержащая колонки текста разделяется на
  файлы по числу колонок текста. Для каждой колонки создается отдельный файл  (jpg)
  с именем исходной страницы и суффиксом номера колонки. Вокруг каждой колонки 
  добавляется свободное пространство шириной  Border
*/ 
void GImageEditor::WriteColumnsData(GBitmap *data,
										 GBitset *set,
										 int nFrm,
										 string &filePath){
/*
  int xfg0,xfg1,yfg0,yfg1;    // координаты прямоугольника вокруг колонок
  int hp=data->rows();        //+64*2 // border*2   // hp=nrows; ////////////////////////////
  unsigned char *pSrc;
  //short level=0;            //if(invert)level=255;


		// получение координат x,y файлов - колонок
		if( nFrm >= 0 ) {      // nFrm - номера колонок 0,1,2,3...   0-печа
			frameOCR *wF=&set->frameArray[nFrm];
		  //xfg0=wF->xfg0;   xfg1=wF->xfg1;   yfg0=wF->yfg0;   yfg1=wF->yfg1;
			xfg0=wF->Xfg0;   xfg1=wF->Xfg1;   yfg0=wF->Yfg0;   yfg1=wF->Yfg1;
		  //ShowMessage(nFrm);
		}
		else  { return; }

		// задание размеров выходного фвйла
		ImageEnView1->RemoveAllObjects();
		int w=xfg1-xfg0;
		ImageEnView1->IEBitmap->Width=w;
		int h=yfg1-yfg0;
		ImageEnView1->IEBitmap->Height=h;
		ImageEnView1->IEBitmap->PixelFormat=ie8g;

//DM("yfg0="<<yfg0<<" yfg1="<<yfg1<<" xfg0="<<xfg0<<" xfg1="<<xfg1<<" w="<<w<<" h="<<h<<END);
//DM(END); DM(hp<<" hp "); DM(nFrm<<" nFrm "); DM(END);
//ShowMessage(nFrm);   ShowMessage(xfg1);   ShowMessage(xfg0);

 int x,y,p,q;
 int nColumn,nClm,nColum0,nColumN;
 int yf0,yf1;      // координаты прямоугольника вокруг вертикальной
				   // колонки, касающийся краёв горизонтальных блок букв
 int x0,x1,y0,y1;  // координаты прямоугольника вокруг горизонтальных
				   // блоков описывающих многоугольники колонок

*/
/********************************
		/// разделение на колонки, заполнение белым только левого и правого бордюра.
		// Создание файлов (jpg).
		q=0; //pSrc=0;
		nColumn=set->frameArray[nFrm].columnArray.size();
		for ( nClm=nColumn-1; nClm >= 0; nClm-- ){ // Цикл по количеству блоков колонок Clm
		  columnOCR *wC=&set->frameArray[nFrm].columnArray[nClm];
		  x0=wC->xc0;   x1=wC->xc1;   y0=wC->yc0;   y1=wC->yc1;
				for (y = hp-y1;  y < hp-y0; y++){  // (y = hp-y1;  y < hp-y0; y++)
					pSrc = (unsigned char *)ImageEnView1->IEBitmap->ScanLine[q];
					q++;   // p=y + hp-yfg1; yfg1
				  for (x=xfg0; x < xfg1; x++){
					  if( x > x0 && x < x1 ) { *pSrc=data[0][y][x]; }  // p куда
					  else{ *pSrc=255; }  // 0-черное, 255-белое
					  pSrc++;
				}}
			///DM(nClm<<" nClm "); DM(END);
		} // Цикл по количеству блоков колонок nClm
*****************/

/*
/// заполнение бордюра белым (255) между прямоугольником вокруг горизонтальных
/// блоков и самими горизонтальными блоками

		// Верхний бордюр, заполнение белым (255)
		yf1=set->frameArray[nFrm].Yf1;
		q=0;  // p=0; // индикатор
		for (y=hp-yfg1;  y < hp-yf1; y++){
			pSrc = (unsigned char *)ImageEnView1->IEBitmap->ScanLine[q];
			q++; // p++;
		  for (x=xfg0; x < xfg1; x++){
			  *pSrc=255;   // 0-черное, 255-белое
			  pSrc++;
		}}
///DM(END); DM(hp-yfg1<<" hp-yfg1 "); DM(hp-yf1<<" hp-yf1 "); DM(q<<" q1 "); DM(p<<" p "); DM(END); DM(END);

		// Левый и правый бордюр, заполнение белым (255)
		nColumn=set->frameArray[nFrm].columnArray.size();
		for ( nClm=nColumn-1; nClm >= 0; nClm-- ){ // Цикл по количеству блоков колонок Clm
		  columnOCR *wC=&set->frameArray[nFrm].columnArray[nClm];
		  x0=wC->Xc0;   x1=wC->Xc1;   y0=wC->Yc0;   y1=wC->Yc1;
				for (y = hp-y1;  y < hp-y0; y++){
					pSrc = (unsigned char *)ImageEnView1->IEBitmap->ScanLine[q];
					q++;   // p++; if(q>h){q=h;}
				  for (x=xfg0; x < xfg1; x++){
					  if( x > x0 && x < x1 ) { *pSrc=data[0][y][x]; } // 254-белое
					  else{ *pSrc=255; }  // 0-черное, 255-белое
					  pSrc++;
				}}
///DM(nClm<<" nClm "); DM(hp-y1<<" hp-y1 "); DM(hp-y0<<" hp-y0 "); DM(q<<" q2 "); DM(p<<" p ");  DM(END);
		} // Цикл по количеству блоков колонок nClm
DM(END);
		// Нижний бордюр, заполнение белым (255)
		yf0=set->frameArray[nFrm].Yf0;
		for (y = hp-yf0;  y < hp-yfg0; y++){
			pSrc = (unsigned char *)ImageEnView1->IEBitmap->ScanLine[q];
			q++;   // p++; if(q>h){q=h;}
		  for (x=xfg0; x < xfg1; x++){
			  *pSrc=255;   // 0-черное, 255-белое
			  pSrc++;
		}}
///DM(END); DM(hp-yf0<<" hp-yf0 "); DM(hp-yfg0<<" hp-yfg0 "); DM(q<<" q3 "); DM(p<<" p "); DM(END); DM(END);

//DM(END); DM(h<<" h "); DM(yf1-yf0<<" yf1-yf0 "); DM(END);


	   //DM("done"<<filePath.c_str());
	   ImageEnView1->Update(); Application->ProcessMessages();
	   pageFrameIndex=-1;  pechaDataLoaded=0;
	   detectRotation(nFrm);
	   //ShowMessage(filePath.c_str());
		   if(CheckBoxTIFF->Checked==true){
			   ImageEnView1->IO->Params->BitsPerSample=1;
			   ImageEnView1->IO->Params->SamplesPerPixel=1;
			   ImageEnView1->IO->Params->TIFF_Compression=ioTIFF_G4FAX;
			   ImageEnView1->IO->SaveToFileTIFF(filePath.c_str());
		  }else{
			   ImageEnView1->IO->SaveToFile(filePath.c_str());
		  }
*/
//x0=wC->xc0;   x1=wC->xc1;   y0=wC->yc0;   y1=wC->yc1;
//int wp=data->columns();   // w=
// int NStrok = sArray.size();
// int NStrok=set->NStrok;
}//_____________________________________________________________________________


/** @fn void GImageEditor::WriteImageData(GBitmapInt *data,string &path,bool flip)    
     @brief отладочная функция записи в графический файл графического массива GBitmapInt
 
 выполнение этой функции платформо зависимо и реализуется на основе применяемой в основной программе 
 графических библиотек ввода-вывода
 реализован вариант для MACOS Cocoa и  PC HiComponent InImage
*/
void GImageEditor::WriteImageData(GBitmapInt *data,string &path,bool flip){
#ifdef WIN32
		short w=data->columns();
		short h=data->rows();
		TIEBitmap *bitmapImg=new TIEBitmap;
		bitmapImg->Width=w;
		bitmapImg->Height=h;
		unsigned char *pSrc;
		unsigned char *pDest;
		unsigned int *p;
		unsigned char *rgb;
		//short level=0; //if(invert)level=255;
		bitmapImg->PixelFormat=ie8p;
		bitmapImg->Palette[255]=TColor2TRGB((TColor)0xffffff);
		bitmapImg->Palette[3]=TColor2TRGB((TColor)0x00aaFF);     // yellow
		bitmapImg->Palette[250]=TColor2TRGB((TColor)0x999999);
		bitmapImg->Palette[5]=TColor2TRGB((TColor)0xFF0000);     //blue
		bitmapImg->Palette[7]=TColor2TRGB((TColor)0xFFff00);     //blue
		bitmapImg->Palette[6]=TColor2TRGB((TColor)0x0000aa);     //red
		bitmapImg->Palette[8]=TColor2TRGB((TColor)0x00FF00);     //green
		bitmapImg->Palette[253]=TColor2TRGB((TColor)0x00ff00);

		//for (int y = 0; y < h;y++){
		//  for (int x = 0; x < w; x++){
		//  DM((unsigned int)data[0][y][x]);
		//}
		//DM(END);
		//}


			int x,y;
			///if(flip){
				for (y = 0; y < h;y++){
				  pSrc = (unsigned char*)bitmapImg->ScanLine[y];
				  for (x = 0; x < w; x++){
							*pSrc=data[0][y][x];
							//pDest=(unsigned char*)pSrc;
							//rgb=(unsigned char*)&data[0][y][x];
							//*pDest=rgb[0];
							//pDest++;
							//*pDest=rgb[1];
							//pDest++;
							//*pDest=rgb[2];
							//DM((int)data[0][h-y][x]<<" ");
							pSrc++;

				}//DM(END);
				}
			 //}else{

			 //}
			 int t=0;
		DP("path="<<path<<END);
		bitmapImg->Write(path.c_str());
		delete bitmapImg;
#else



#endif	
	
	
	
	
}//_____________________________________________________________________________

/** @fn void GImageEditor::WriteImageData(GBitmap *data,string &path,bool flip)   
 @brief функция записи в графический файл байтового графического массива GBitmap
 
 выполнение этой функции платформо зависимо и реализуется на основе применяемой в основной программе 
 графических библиотек ввода-вывода
 реализован вариант для MACOS Cocoa и  PC HiComponent InImage
 */
void GImageEditor::WriteImageData(GBitmap *data,string &path,bool flip){
#ifdef WIN32
		short w=data->columns();
		short h=data->rows();
		TIEBitmap *bitmapImg=new TIEBitmap;
		bitmapImg->Width=w;
		bitmapImg->Height=h;
		unsigned char *pSrc;
		unsigned char *pDest;
		unsigned char *p;
		//short level=0; //if(invert)level=255;
		//bitmapImg->PixelFormat=ie8p;
		//bitmapImg->Palette[255]=TColor2TRGB((TColor)0xffffff);
		//bitmapImg->Palette[3]=TColor2TRGB((TColor)0x0000aa);
		//bitmapImg->Palette[250]=TColor2TRGB((TColor)0x999999);
		//bitmapImg->Palette[5]=TColor2TRGB((TColor)0x550021);
		//bitmapImg->Palette[6]=TColor2TRGB((TColor)0x0000aa);
		//bitmapImg->Palette[253]=TColor2TRGB((TColor)0x00ff00);
		bitmapImg->PixelFormat=ie8g;


			int x,y,in=0;
			if(flip){
				for (y = 0; y < h;y++){
				  pSrc = (unsigned char *)bitmapImg->ScanLine[y];
				  for (x = 0; x < w; x++){
							*pSrc=data[0][h-y][x];
							//if(*pSrc>128){DP("1")}else{DP(".")};
							pSrc++;
				}//DP(END);
				}
			 }else{
				for (y = 0; y < h;y++){
				  pSrc = (unsigned char *)bitmapImg->ScanLine[y];
				  for (x = 0; x < w; x++){
							*pSrc=data[0][y][x];
							//*pSrc=in;
							//in++; if(in>255)in=0;
							//if(*pSrc>128){DP("1")}else{DP(".")};
							pSrc++;
				}//DP(END);
				}
			 }
	
		DP("path="<<path<<END);
		bitmapImg->Write(path.c_str());
		delete bitmapImg;
#endif
#ifdef MACOS
#define DP(x) cout<<x
	short w=data->columns();
	short h=data->rows();
	
//static	NSApplication *app = [NSApplication sharedApplication];		
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	
	NSString *filePath=[[NSString alloc]initWithCString:path.c_str() encoding:1];
	//NSImage *sourceImage=[[NSImage alloc] initWithSize:NSMakeSize(w, h)]; //create Image;
	
	
	NSBitmapImageRep *srcImageRep = [[NSBitmapImageRep alloc] 
									 initWithBitmapDataPlanes:NULL
									 pixelsWide:w 
									 pixelsHigh:h
									 bitsPerSample:8 
									 samplesPerPixel:1
									 hasAlpha:NO
									 isPlanar:NO
									 colorSpaceName:NSCalibratedWhiteColorSpace
									 bytesPerRow:w 
									 bitsPerPixel:8];
	
	DP("DRAW0_2");	
	//short delta=0;   //really a problem. in 600 dpi pecha pixelsWide != wigth of pecha! 
	int wByte;
	w = [srcImageRep  pixelsWide];	
	h = [srcImageRep pixelsHigh];
	wByte=[srcImageRep bytesPerRow];   //ATENTION on Tiger bytesPerRow aligned by word and bytesPerRow!=w
	
	DP("bytesPerRow="<<[srcImageRep bytesPerRow]<<END);		
	DP("main w="<<w<<" h="<<h<<END);		
	//unsigned char lineData[wByte*h+w];
	unsigned char *srcData = [srcImageRep bitmapData];
	
	unsigned char *pSrc;
	
           int x,y;
	for (y = 1; y < h;y++){
		for (x = 0; x < wByte; x++){
			pSrc=srcData+y*wByte+x;
			*pSrc=data[0][y][x];
			//if(*pSrc>120){DP(1);}else{DP(0);} //draw on screen
		}
		//DP(END); //draw on screen
	}
	//[sourceImage addRepresentation:srcImageRep];	
	///NSData *TIFFData = [sourceImage TIFFRepresentation];   //write file on disk
	
	//[[sourceImage TIFFRepresentation] writeToFile:@"/_1111.tiff" atomically:YES];
	
	
	//NSData * tiffData = [[lbLoading image] TIFFRepresentation]; 
	//NSBitmapImageRep *bits = [NSBitmapImageRep imageRepWithData:tiffData]; // get a rep from your image, or grab from a view
	cout<<"start save "<<path<<END;
	NSData *dataJpeg;
	dataJpeg = [srcImageRep representationUsingType: NSJPEGFileType properties:nil];
	[dataJpeg writeToFile:filePath atomically: NO];
    [srcImageRep release];
	[pool release];
	
	//icon = [[[NSBitmapImageRep imageRepWithData:[newIcon TIFFRepresentation]] 
    //         representationUsingType:NSGIFFileType properties:nil] retain];
	
	//icon = [[[NSBitmapImageRep imageRepWithData:[newIcon TIFFRepresentation]] 
              //representationUsingType:NSGIFFileType properties:
	//		 [NSDictionary dictionaryWithObjectsAndKeys:
	//		 NSImageRGBColorTable, NULL]] retain];
	
#define DP(x)	
	
#endif		
	
}//_____________________________________________________________________________
void GImageEditor::WriteImageData(GBitmap *data,char* path, bool invert){
	string str=path;
	WriteImageData(data,str,invert);
	
}

/** @fn void GImageEditor::WriteImageData(GBitset *data,string &path, bool flip) 
 @brief функция записи в графический файл битового графического массива GBitset
 
 выполнение этой функции платформо зависимо и реализуется на основе применяемой в основной программе 
 графических библиотек ввода-вывода
 реализован вариант для MACOS Cocoa и  PC HiComponent InImage
 */
void GImageEditor::WriteImageData(GBitset *data,string &path, bool flip){
#ifdef WIN32
	    short w=data->columns();
		short h=data->rows();
		TIEBitmap *bitmapImg=new TIEBitmap;
		bitmapImg->Width=w;
		bitmapImg->Height=h;

		//DM("w="<<w<<" h="<<h<<END);
		unsigned char *pSrc;
		unsigned char *pDest;
		unsigned char *p;

		//ShowMessage((AnsiString)(short)ImageEnView1->IEBitmap->IsGrayScale());
		bitmapImg->PixelFormat=ie8g;

			int x,y;

		   if(flip){
				for (y = 0; y < h;y++){
				  pSrc = (unsigned char *)bitmapImg->ScanLine[y];
				  for (x = 0; x < w; x++){
							*pSrc=255+data[0][h-y][x];
							pSrc++;
				}}
		   }else{
				for (y = 0; y < h;y++){
				  pSrc = (unsigned char *)bitmapImg->ScanLine[y];
				  for (x = 0; x < w; x++){
							*pSrc=255+data[0][y][x];
							pSrc++;
				}}
		   }
		DP("path="<<path<<END);
		bitmapImg->Write(path.c_str());
		delete bitmapImg;
#endif	
#ifdef MACOS
	short w=data->columns();
	short h=data->rows();
	
//static	NSApplication *app = [NSApplication sharedApplication];		
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	
	NSString *filePath=[[NSString alloc]initWithCString:path.c_str() encoding:1];
	NSImage *sourceImage=[[NSImage alloc] initWithSize:NSMakeSize(w, h)]; //create Image;

	
	NSBitmapImageRep *srcImageRep =[[NSBitmapImageRep imageRepWithData:[sourceImage TIFFRepresentation]]retain];
	DP("DRAW0_1"<<END);	
	//short delta=0;   //really a problem. in 600 dpi pecha pixelsWide != wigth of pecha! 
	int wByte;
	w = [srcImageRep  pixelsWide];	
	h = [srcImageRep pixelsHigh];
	wByte=[srcImageRep bytesPerRow];   //ATENTION on Tiger bytesPerRow aligned by word and bytesPerRow!=w
	
	DP("bytesPerRow="<<[srcImageRep bytesPerRow]<<END);		
	DP("_main wByte="<<wByte<<" w="<<w<<" h="<<h<<END);		
	//unsigned char lineData[wByte*h+w];
	 DP("start save");
	unsigned char *srcData = [srcImageRep bitmapData];
	
	unsigned char *pSrc;
	
    int x,y;
	for (y = 1; y < h;y++){
		for (x = 0; x < wByte; x++){
			pSrc=srcData+y*wByte+x;
			*pSrc=data[0][h-y][x];
			//if(*pSrc>120){cout<<1;}else{cout<<0;} //draw on screen
		}
		DP(END); //draw on screen
	}
	
	
	///NSData *TIFFData = [sourceImage TIFFRepresentation];   //write file on disk
	[[sourceImage TIFFRepresentation] writeToFile:@"/1.jpg" atomically:YES];
	DP("save path="<<path<<END);	
	//[[NSBitmapImageRep representationOfImageRepsInArray:representations 
	///				   usingType:NSJPEGFileType properties:nil] writeToFile:filePath atomically:YES];
	/*
	NSData *imageData;// = [stretchView TIFFRepresentation];
	//NSBitmapImageRep *imageRep = [NSBitmapImageRep imageRepWithData:imageData];
	//NSDictionary *imageProps = [NSDictionary dictionaryWithObject:[NSNumber numberWithFloat:0.9] forKey:NSImageCompressionFactor];
	NSDictionary *imageProps = [NSDictionary dictionaryWithObject:[NSNumber numberWithFloat:0.9] forKey:NSImageCompressionFactor];
	imageData = [sourceImage representationUsingType:NSJPEGFileType properties:imageProps];
	[imageData writeToFile:filePath atomically:NO];
	*/
	
	
	[pool release];
	
#endif	
	
}//_____________________________________________________________________________

void GImageEditor::WriteImageData(GBitset *data,char* path, bool flip){
	string str=path;
	WriteImageData(data,str,flip);
	
}

/** @fn void GImageEditor::LoadImageData(string &inputPath)
 @brief функция загрузки из графического файла глобального байтого графического массива pechaImg
 
 выполнение этой функции платформо зависимо и реализуется на основе применяемой в основной программе 
 графических библиотек ввода-вывода
 реализован вариант для MACOS Cocoa и  PC HiComponent InImage
 */
void GImageEditor::LoadImageData(string &inputPath,bool invert){

#ifdef WIN32
bitmapImg=new TIEBitmap;

ifstream in; in.open(inputPath.c_str());
if(in==NULL){exit(0);};
in.close();

bitmapImg->Read(inputPath.c_str());
bitmapImg->PixelFormat=ie8g;
//cout<<bitmapImg->Width;

DP("start");
int frameFlag=0;
int w,h,iRight,iDown;


		  w=bitmapImg->Width-1;
		  h=bitmapImg->Height;

		unsigned char *pSrc;
		unsigned char *pDest;
		unsigned char *p;
		//inputData->imgW=w; inputData->imgH=h;
		//if(pechaImg)pechaImg->destroy();
		pechaImg=GBitmap::create(h,w);

		//if(pechaImgContour)pechaImgContour->destroy();
		//pechaImgContour=GBitmap::create(h,w);
		//ImageEnView1->IEBitmap->PixelFormat=ie8g;

		DP("w="<<w<<END);
			int x,y;
			for (y = 0; y < h;y++){
			  pSrc = (unsigned char *)bitmapImg->ScanLine[y+iTop];
			  pSrc+=iLeft;
			  for (x = 0; x < w; x++){
						pechaImg[0][y][x]=*pSrc;
						pSrc++; //if(*pSrc>150){DP(0);}else{DP(1);};
			  }//DP(END);
			}

       delete bitmapImg;

#endif
#ifdef MACOS


    int print=1;
	//cout<<"@0";
//static	NSApplication *app = [NSApplication sharedApplication];		
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	
	NSString *filePath=[[NSString alloc]initWithCString:inputPath.c_str() encoding:1];
	NSImage *sourceImage=[[NSImage alloc] initWithContentsOfFile:filePath]; //open Image;
	//[[sourceImage TIFFRepresentation] writeToFile:@"/_1112.tiff" atomically:YES];
	//cout<<"@1";
	
	NSBitmapImageRep *srcImageRep =[NSBitmapImageRep imageRepWithData:[sourceImage TIFFRepresentation]];
	//DP("DRAW0_2");	
	//short delta=0;   //really a problem. in 600 dpi pecha pixelsWide != wigth of pecha! 
	int wByte;
	int w = [srcImageRep  pixelsWide];	
	int h = [srcImageRep pixelsHigh];
	wByte=[srcImageRep bytesPerRow];   //ATENTION on Tiger bytesPerRow aligned by word and bytesPerRow!=w
	//cout<<"@2";
	DP("bytesPerRow="<<[srcImageRep bytesPerRow]<<END);		
	DP("main w="<<w<<" h="<<h<<END);		
	//unsigned char lineData[wByte*h+w];
	unsigned char *srcData = [srcImageRep bitmapData];
	
	unsigned char *pSrc;
	
	pechaImg=GBitmap::create(h,wByte);
	//cout<<"@3";
	int samplesPerPixel = [srcImageRep samplesPerPixel];
	int bytesPerSample = ([srcImageRep bitsPerPixel]/8)/samplesPerPixel;
	int totalBytes = [srcImageRep pixelsHigh]*[srcImageRep pixelsWide]*samplesPerPixel*bytesPerSample;
	
	DP("samplesPerPixel="<<samplesPerPixel<<" bytesPerSample="<<bytesPerSample<<endl);
	
    if(bytesPerSample==1){
	   if(samplesPerPixel>2){
			int o = 0;
			int i = 0;
			int background = 255;
			//for (ini=0; i<totalBytes; i+=samplesPerPixel){
		   for (int y = 1; y < h;y++){
			   o = 0;
			   for (i = 0; i < wByte-samplesPerPixel; i+=samplesPerPixel){
					int R = (int)*(srcData+y*wByte+i);
					int G = (int)*(srcData+y*wByte+i+1);
					int B = (int)*(srcData+y*wByte+i+2);
					int grayValue = (int)((R+G+B)/3);
					if (samplesPerPixel==4)
					{
						int alpha = (int)*(srcData+y*wByte+i+3);  // this is the alpha value
						grayValue = (int) (    (grayValue*alpha + background*(255-alpha))    / 255);
					}
				    pechaImg[0][y][o] = grayValue;  //if(grayValue){cout<<1;}else{cout<<0;}
					o++;
			   }}
	   }else{
		   int x,y;
		   if(invert){
			   for (y = 1; y < h;y++){ // cout<<".";
				   for (x = 0; x < wByte; x++){
					   pSrc=srcData+y*wByte+x;
					   pechaImg[0][y][x]=255-*pSrc;
					   //if(pechaImg[0][h-y-1][x]>120)//_DM(1);}else//_DM(0);}; //draw on screen
				   }
				   //_//_DM(END); //draw on screen
			   }		  
		   }else{
			   for (y = 1; y < h;y++){ // cout<<".";
				   for (x = 0; x < wByte; x++){
					   pSrc=srcData+y*wByte+x;
					   pechaImg[0][y][x]=*pSrc;
					   //if(pechaImg[0][h-y-1][x]>120)//_DM(1);}else//_DM(0);}; //draw on screen
				   }
				   //_//_DM(END); //draw on screen
			   }		  
		   }	   
	   }
    } else NSLog(@"Bytes per sample != 1 or less than 3 samples per pixel");
	DP("@3_2");

           [sourceImage autorelease];
	       [pool release];
    DP("@4");
	
#endif
	  //imgArray.push_back(pImg);
	  pechaDataLoaded=1;

 
}//_____________________________________________________________________________

/** @fn void GImageEditor::LoadImageData(GBitmap* pImg, int x0,int y0, int w, int h)
 @brief функция загрузки фрагмента графического файла по заданным  координатам 
    в глобальный байтый графический массив pechaImg
 */
void GImageEditor::LoadImageData(GBitmap* pImg, int x0,int y0, int w, int h){
			//cout<<"start"<<" x0="<<x0<<" y0="<<y0<<" w="<<w<<" h="<<h<<END;

	        if(x0<0||y0<0)return;
	        if(w+x0>pechaImg[0].columns()||
		h+y0>pechaImg[0].rows())return;

		unsigned char *pSrc;
		unsigned char *pDest;
		unsigned char *p;

			int x,y;
			for (y = 0; y < h;y++){
			  for (x = 0; x < w; x++){
						pImg[0][y][x]=pechaImg[0][y0+y][x0+x];
						if(pImg[0][y][x]>150){DS(0);}else{DS(1);};
			  }DS(END);
			}
	//cout<<"done"<<END;
}//_____________________________________________________________________________


/** @fn void GImageEditor::drawString(int nStr, int border)
 @brief вывод в стандартный выходной поток HTML отображения
 одной строки из глобального массива результатов распознования strArray
  */
void GImageEditor::drawString(int nStr, int border){
/*
#ifdef DEBUGLVL
#ifdef DRAW1  //
int strInd,m,in,strFlag;
int x,x0,x1,y0,y1;        // ,xt0,yt0,xt1,yt1
int NString,MaxString=60; // MaxString - ограничение на колличество выводимых на эран строк
TPoint ris[9];            // ( если больше графический порт вешается) 6
ImageEnView1->RemoveAllObjects();

// x0,x1, y0,y1     координаты квадрата вокруг буквы


		 // заполнение массива координат прямоугольника
		 for ( strInd=nStr; strInd <=nStr; strInd++ ){
		 strFlag=strArray[strInd].stringFlag;
		   // если stringFlag==0 то строку не заполняем квадратиками букв (в строке линия)
		   for ( m=0; strFlag==1 && m < strArray[strInd].wordArray.size(); m++ ){
			wordOCR *wP=&strArray[strInd].wordArray[m];
				   x0=wP->x0;   x1=wP->x1;   y0=wP->y0;   y1=wP->y1;
///				   DM("y0="<<y0<<" y1="<<y1<<" x0="<<x0<<" x1="<<x1<<" nrowsImg="<<nrowsImg<<" LimY0="<<strArray[strInd].LimY0<<" LimY1="<<strArray[strInd].LimY1<<END);
				   ris[0].x=x0;
				   ris[0].y=strArray[strInd].LimY0-y1+border;  ///DM(" ris[0].y0="<<ris[0].y<<END);
				   ris[1].x=x0;
				   ris[1].y=strArray[strInd].LimY0-y0+border;
				   ris[2].x=x1;
				   ris[2].y=strArray[strInd].LimY0-y0+border;  ///DM(" ris[0].y1="<<ris[0].y<<END);
				   ris[3].x=x1;
				   ris[3].y=strArray[strInd].LimY0-y1+border;
				   ris[4].x=x0;
				   ris[4].y=strArray[strInd].LimY0-y1+border;
				   //ris[5].x=x0;
				   //ris[5].y=nrowsImg-y0;
					in=ImageEnView1->AddNewObject();
//                    DM(wP->stackFlag);
					if(wP->stackFlag>0){
					ImageEnView1->ObjPenColor[in]=(TColor)0xffff00; // цвет линии салатовый
					}else{
					ImageEnView1->ObjPenColor[in]=(TColor)0xff1400; // цвет линии светло синий
					}
					ImageEnView1->ObjPenWidth[in]=1;  // толщина линии
					ImageEnView1->ObjKind[in]=iekPOLYLINE;
					ImageEnView1->SetObjPolylinePoints(in,ris,4); // 5
		   } // m

		 } // strInd
		 ImageProcessor->ImageEnView1->Update();


// x0,y0,x1,y1
// x0,y0 координаты левого нижнего угла прямоугольника строки (глифа, слога, буквы).
// x1,y1 координаты правого верхнего угла прямоугольника строки (глифа, слога, буквы).


#endif    //
#endif
*/
}//_____________________________________________________________________________

/** @fn void GImageEditor::drawString(int nStr, int border)
 @brief вывод в стандартный выходной поток HTML отображения
 глобального массива результатов распознования strArray
 
 параметры вывода задаются в  управляющей структуре inputData
 */
void GImageEditor::drawStrArray(commandData *inputData,vector<stringOCR>&strArray, int border){

int strInd,m,in,strFlag;
int x,x0,x1,y0,y1,gY;        // ,xt0,yt0,xt1,yt1
int NString; 
char cbuf[10];
// x0,x1, y0,y1     координаты квадрата вокруг буквы
		 //pr
int index=0;
	
	int pageWide=0;
	if(pechaImg->columns()>pechaImg->rows())pageWide=1;
	
	string path=fileName(inputData->data["inputFile"]);
	//cout<<"path="<<inputData->data["inputFileName"]<<END;
	//cout<<"inputData->data[\"inputFile\"]="<<inputData->data["inputFile"];

#define c_out1   inputData->c_out
	
	
	path=inputData->data["tablePath"]+"/headerPage.xml";
	replace(path.begin(),path.end(),'\\','/');
	
	string headerPageHTML=readText(path);
	
	c_out1<<headerPageHTML<<endl;
	c_out1<<"			var pictW = "<<pechaImg[0].columns()<<";"<<endl;
	
	
	for ( strInd=strArray.size()-1; strInd >=0; strInd-- ){
	    for ( m=0; m < strArray[strInd].wordArray.size(); m++ ){
			wordOCR *wP=&strArray[strInd].wordArray[m];
			if(wP->id<0)continue;
			x0=wP->x0;   x1=wP->x1;   y0=wP->y0;   y1=wP->y1;
			c_out1<<"   frame["<<wP->id<<"]=new Array(4); ";
			c_out1<<"frame["<<wP->id<<"].x="<<x0<<"; ";
			c_out1<<"frame["<<wP->id<<"].y="<<y0<<"; ";
			c_out1<<"frame["<<wP->id<<"].w="<<x1-x0<<"; ";
			c_out1<<"frame["<<wP->id<<"].h="<<y1-y0<<";"<<endl;
		}
	}
	
	if(pageWide){
		c_out1<<"function a(index){"<<endl;
		c_out1<<"	//alert(document.getElementById(\"frame\"));"<<endl;
		c_out1<<"	var xFrame=frame[index].x*(1600/pictW*3)+20;"<<endl;
		c_out1<<"	var yFrame=frame[index].y*(1600/pictW*3)+20;"<<endl;
		//c_out1<<"	//alert(xFrame);"<<endl;
		c_out1<<"	document.getElementById(\"frame\").style.left=xFrame+\"px\";"<<endl;
		c_out1<<"	document.getElementById(\"frame\").style.top=yFrame+\"px\"; "<<endl;
		//c_out1<<"	document.getElementById('outputStr').innerHTML=frame[index].x+":|:"+frame[index].y;"<<endl;
		c_out1<<"}";
	}else{
		c_out1<<"function a(index){"<<endl;
		c_out1<<"	//alert(document.getElementById(\"frame\"));"<<endl;
		c_out1<<"	var xFrame=frame[index].x*(600/pictW)+640-10;"<<endl;
		c_out1<<"	var yFrame=frame[index].y*(600/pictW)-10;"<<endl;
		//c_out1<<"	//alert(xFrame);"<<endl;
		c_out1<<"	document.getElementById(\"frame\").style.left=xFrame+\"px\";"<<endl;
		c_out1<<"	document.getElementById(\"frame\").style.top=yFrame+\"px\"; "<<endl;
		//c_out1<<"	document.getElementById('outputStr').innerHTML=frame[index].x+":|:"+frame[index].y;"<<endl;
		c_out1<<"}";
	}	

	c_out1<<"</script>";
	c_out1<<"</head><body topmargin=\"0px\" leftmargin=\"0px\">"<<endl;
	c_out1<<"<form enctype=\"application/x-www-form-urlencoded\" method=\"post\" action=\"/cgi/yagpoOCR.cgi\" name=\"main\">\n";
	c_out1<<"<input  name=\"inputFile\"  type=\"hidden\" value=\""; c_out1<<inputData->data["inputFile"];c_out1<<"\"/>\n";
	c_out1<<"<input  name=\"ocrData\"  type=\"hidden\" value=\"setLetter\"/>\n";
	c_out1<<"<input  name=\"inputFolder\"  type=\"hidden\" value=\""; c_out1<<inputData->data["inputFolder"];c_out1<<"\"/>\n";
	c_out1<<"<button name=\"submit\" value=\"submit\" type=\"submit\">Set letter in base</button>";
	c_out1<<"<input  name=\"newLetter\"  type=\"checkbox\" value=\"true\" />Set as new letter<br>\n";
	c_out1<<"<textarea ID=\"outputStr\" name=\"setLetter\" cols=\"70\" rows=\"3\"></textarea>\n";
	c_out1<<"</form>";
	
	
	c_out1<<"<div id=\"frame\" style=\"width:30px; height:30px; position: absolute;  left:640px; top:100; border:2px solid red\"></div>";
	
	for(int i=0;i<25;i++){
		c_out1<<"<div class=\"dE\" id=\"g"<<i<<"\" c=\"83\" style=\"left:640px; top:10px; width:30px; height:30px; \">"<<endl;
		c_out1<<"<div class=\"dM\" style=\"width: 17px; height:3px;\"></div>"<<endl;
		c_out1<<"<div class=\"nG\" id=\""<<i<<"\" style=\" top:39px\" onClick=\"edit("<<i<<")\" onBlur=\"setText("<<i<<")\">*</div></div>"<<endl;
	}
	
	if(pageWide){
		c_out1<<"<div id=\"page_bitmap\" style=\"margin-left: 0px; margin-right: 0px;   position: absolute;";
		c_out1<<"text-align: left; width: 1600px; left:20px; z-index:-1; top: 20px;\"><br />"<<endl;
		c_out1<<"<img src=\""<<fileName(inputData->data["inputFile"])<<"\" width=\"1600px\">"<<endl;
		c_out1<<"</div>";
		
		c_out1<<"<div style=\"font-family:Kailasa; font-size:1.6em; width:1600px; position:absolute; top:350px; left:250px;\"><br>"<<END;
		c_out1<<mainString;
		c_out1<<"</div>";
	}else{
		c_out1<<"<div style=\"font-family:Kailasa; font-size:1.6em; width: 600px; position:absolute; top:40px; left:20px;\"><br>"<<END;
		c_out1<<mainString;
		c_out1<<"</div>";
		c_out1<<"<div id=\"page_bitmap\" style=\"margin-left: 0px; margin-right: 0px;   position: absolute;";
		c_out1<<"text-align: left; width: 480px; left:640px; z-index:-1; top: -20px;\"><br />"<<endl;
		c_out1<<"<img src=\""<<fileName(inputData->data["inputFile"])<<"\" width=\"600px\">"<<endl;
		c_out1<<"</div>";
		
	}	
	path=inputData->data["inputFolder"]+"/_all_text_html.html";
    ofstream c_out; c_out.open(path.c_str(),ofstream::app);
    c_out<<"{"<<inputData->data["inputFile"]<<"}"<<endl;
	c_out<<"<div style=\"font-family:Kailasa; font-size:1.6em; width: 600px;\"><br>"<<END;
    c_out<<mainString;
	c_out<<"</div>\n";
	c_out.close();
	
	#undef c_out1
	
// x0,y0,x1,y1
// x0,y0 координаты левого нижнего угла прямоугольника строки (глифа, слога, буквы).
// x1,y1 координаты правого верхнего угла прямоугольника строки (глифа, слога, буквы).

}//_____________________________________________________________________________


/** @fn void GImageEditor::drawString(int nStr, int border)
 @brief вывод в стандартный выходной поток HTML отображения
 глобального массива результатов распознования strArray
 
 параметры вывода задаются в  управляющей структуре inputData
 */
void GImageEditor::drawStrArrayDebug(commandData *inputData,vector<stringOCR>&strArray, int border){
	
	int strInd,m,strFlag;
	int x,x0,x1,y0,y1,gY;        // ,xt0,yt0,xt1,yt1
	//int MaxString=60; // MaxString - ограничение на колличество выводимых на эран строк
	string path;
	//char cbuf[10];
	// x0,x1, y0,y1     координаты квадрата вокруг буквы
	int index=0;
#define c_out1   inputData->c_out
	
	
	path=inputData->data["tablePath"]+"/header.xml";
	replace(path.begin(),path.end(),'\\','/');
	
	string headerPageHTML=readText(path);
	
	c_out1<<headerPageHTML<<endl;

	path=fileName(inputData->data["inputFile"]);
	//cout<<"path="<<inputData->data["inputFileName"]<<END;
	//cout<<"inputData->data[\"inputFile\"]="<<inputData->data["inputFile"];

	c_out1<<"<div style=\"position:absolute; left:0px; top:0px;\">";
	c_out1<<"<img class=\"srcImg\" src=\""<<path<<"\"/>\n";
	
	// заполнение массива координат прямоугольника
	for ( strInd=strArray.size()-1; strInd >=0; strInd-- ){
		strFlag=strArray[strInd].stringFlag; 
		x0=strArray[strInd].x0;   x1=strArray[strInd].x1;
		y0=strArray[strInd].y0;   y1=strArray[strInd].y1;
		c_out1<<"<div class=\"sT\" id=\"s"<<strInd<<"\" style=\"left:";
		c_out1<<x0<<"px; top:"<<y0<<"px; width:"<<x1-x0<<"px; height:";
		c_out1<<y1-y0<<"px;\" ";
		c_out1<<"LimY0=\""<<strArray[strInd].LimY0<<"\" ";
		c_out1<<"LimY1=\""<<strArray[strInd].LimY0<<"\" ";
		c_out1<<"y0=\""<<strArray[strInd].y0<<"\" ";
		c_out1<<"y1=\""<<strArray[strInd].y1<<"\" ";
		c_out1<<"x1=\""<<strArray[strInd].x1<<"\" ></div>\n";
		
		if(strFlag<1)continue; // если stringFlag==0 то строку не заполняем квадратиками букв (в строке линия)
		for ( m=0; m < strArray[strInd].wordArray.size(); m++ ){
			wordOCR *wP=&strArray[strInd].wordArray[m];
			if(wP->correlation<0)continue;  //word marked as text frame etc. 
			x0=wP->x0;   x1=wP->x1;   y0=wP->y0;   y1=wP->y1;
			gY=strArray[strInd].y1-y0+10;
			//DM("y0="<<y0<<" y1="<<y1<<" x0="<<x0<<" x1="<<x1<<" LimY0="<<strArray[strInd].LimY0<<" LimY1="<<strArray[strInd].LimY1<<END);
			if(x1-x0>0){
				c_out1<<"<div class=\"dE\" id=\"g"<<index<<"\" c=\""<<wP->correlation;
				c_out1<<"\" style=\"left:"<<x0<<"px; top:"<<y0<<"px; width:"<<x1-x0<<"px; height:";
				c_out1<<y1-y0<<"px; ";
				if(wP->correlation<70){c_out1<<" border-color:#ff0000; border-width:3px;";}
				if(wP->correlation>70&&wP->correlation<80){c_out1<<" border-color:#cc0033; border-width:2px;";}
				
				c_out1<<"\">\n<div class=\"dM\" style=\"width: "<<x1-x0<<"px; height:3px;\"></div>\n";
				//c_out1<<wP->OCRIndex;
				c_out1<<"<div class=\"nG\" id=\""<<index<<"\" style=\" top:"<<gY<<"px\" onClick=\"edit(";
				c_out1<<index<<")\" onBlur=\"setText("<<index<<")\">"<<wP->name<<"</div></div>";
				index++;
			}
			//DT("n="<<wP->name.c_str()<<" c="<<wP->correlation<<END);
			//if(wP->stackFlag>0){
			//ImageEnView1->ObjPenColor[in]=(TColor)0xffff00; // цвет линии салатовый
			//}else{
			//ImageEnView1->ObjPenColor[in]=(TColor)0xff1400; // цвет линии светло синий
			//}
			
		} // m
		
	} // strInd
	
	
	c_out1<<"<form enctype=\"application/x-www-form-urlencoded\" method=\"post\" action=\"/cgi/yagpoOCR.cgi\" name=\"main\">\n";
	c_out1<<"<input  name=\"inputFile\"  type=\"hidden\" value=\""; c_out1<<inputData->data["inputFile"];c_out1<<"\"/><br/>\n";
	c_out1<<"<input  name=\"ocrData\"  type=\"hidden\" value=\"setLetter\"/><br/>\n";
	c_out1<<"<input  name=\"inputFolder\"  type=\"hidden\" value=\""; c_out1<<inputData->data["inputFolder"];c_out1<<"\"/><br/>\n";
	c_out1<<"<button name=\"submit\" value=\"submit\" type=\"submit\">Set letter in base</button><br/>\n";
	c_out1<<"<input  name=\"newLetter\"  type=\"checkbox\" value=\"true\" /><p>Set as new letter</p>\n";
	c_out1<<"<textarea ID=\"outputStr\" name=\"setLetter\" cols=\"110\" rows=\"7\"></textarea>\n";
	c_out1<<"</form>"<<END;
	c_out1<<mainString<<END;
	//string t;
	//t=str_replace("\n","</div><br/><div class=\"nT\">",mainString);
	//c_out1<<"<div class=\"nT\">"<<mainString<<"</div>";
	c_out1<<"</div></body>";
	
#undef c_out1
	
	ofstream out_st;  out_st.open("/_out.html");
	out_st<<"<html><head><meta content=\"text/html; charset=UTF-8\" http-equiv=\"Content-Type\"></head><body>";
	out_st<<"<div style=\"font-family:Kailasa; font-size:2em;\";>"<<END;
    out_st<<mainString;
	out_st<<"</div>";
	out_st.close();
	
	//SH("done");
	//print=0;
	// x0,y0,x1,y1
	// x0,y0 координаты левого нижнего угла прямоугольника строки (глифа, слога, буквы).
	// x1,y1 координаты правого верхнего угла прямоугольника строки (глифа, слога, буквы).
	
	
}//_____________________________________________________________________________


void GImageEditor::drawLettersInCorrectionTable(commandData *inputData,int mode){
	static GBitmap *img=GBitmap::create(200,200);
	static int xImg=0,yImg=0,x0,y0,x1,y1;
	int index=correctionTable.size()-1;
	static int baseIndex=0;
	char buff[20];
	string path=fileName(inputData->data["inputFile"]);
	int w,h,print=1;
	if(mode==LETTER_ADD){
		for(int index=0;index<correctionWordArray.size();index++){
			//cout<<" path="<<path<<" correctionWordArray["<<index<<"].file="<<correctionWordArray[index].file<<" "<<correctionWordArray[index].name<<END;
			if(correctionWordArray[index].name=="_"||correctionWordArray[index].name==" ")continue;
			if(correctionWordArray[index].file!=path)continue;
				x0=correctionWordArray[index].x0-5;
				y0=correctionWordArray[index].y0-25;
				x1=correctionWordArray[index].x1+5;
				y1=correctionWordArray[index].y1+40;
				w=x1-x0;    if(w>200)w=200; 
				h=y1-y0;   if(h>200)h=200;
				img->fill(255);
				LoadImageData(img,x0,y0, w, h);
				correctionWordArray[index].img=GBitmap::create(img);
				correctionWordArray[index].img->packImg();
				correctionWordArray[index].imgFlag=1;
		}
	}else if(mode==DRAW_BASE){
		DT(END<<"sort ");
		sort(correctionWordArray.begin(),correctionWordArray.end(),wordOCR_sort());
		DT("sort done ");
        static GBitmap *baseImg=GBitmap::create(8000,4000);
		DT("ris ");
		sprintf(buff,"%d",baseIndex);
		string path=inputData->data["OCRTables"]+"/letterBase";
		path+=buff; path+=".jpg";
		cout<<"start write data. baseIndex="<<baseIndex<<" correctionWordArray.size()="<<correctionWordArray.size()<<END;
		int pageIndex=0;

		path=inputData->data["tablePath"]+"/headerTable.xml";
		replace(path.begin(),path.end(),'\\','/');
		
		string headerPageHTML=readText(path);
		sprintf(buff,"%d",pageIndex);
		path=inputData->data["OCRTables"]+"/letterBase";
		path+=buff; path+=".html";
		ofstream c_out; c_out.open(path.c_str());
		c_out<<headerPageHTML<<endl; cout<<"openBasePath="<<path<<END;
		sprintf(buff,"%d",pageIndex);
		path="letterBase";
		path+=buff; path+=".jpg";		
		cout<<"path="<<path<<END;
		cout<<"inputData->data[\"inputFile\"]="<<inputData->data["inputFile"];	
		c_out<<"<div style=\"position:absolute; left:0px; top:0px;\">";
		c_out<<"<img class=\"srcImg\" src=\""<<path<<"\" width=\"2000px\"/>\n";
		int indexLetter=0;  xImg=0; 
		DT("ris1 ");
		for(int index=0;index<correctionWordArray.size();index++){ //cout<<"correctionWordArray["<<index<<"].imgFlag="<<correctionWordArray[index].imgFlag<<END;
			if(correctionWordArray[index].name=="_"||correctionWordArray[index].name==" "||correctionWordArray[index].imgFlag!=1)continue;
			if(yImg>38){
				c_out<<"<form enctype=\"application/x-www-form-urlencoded\" method=\"post\" action=\"/cgi/yagpoOCR.cgi\" name=\"main\">\n";
				//c_out<<"<input  name=\"inputFile\"  type=\"hidden\" value=\""; c_out<<inputData->data["inputFile"];c_out<<"\"/><br/>\n";
				c_out<<"<input  name=\"ocrData\"  type=\"hidden\" value=\"setCorrectionTable\"/><br/>\n";
				c_out<<"<input  name=\"inputFolder\"  type=\"hidden\" value=\""; c_out<<inputData->data["inputFolder"];c_out<<"\"/><br/>\n";
				c_out<<"<button name=\"submit\" value=\"submit\" type=\"submit\">Set letter in base</button><br/>\n";
				c_out<<"<textarea ID=\"outputStr\" name=\"letterCorrection\" cols=\"110\" rows=\"7\"></textarea>\n";
				c_out<<"</form>";
				c_out<<"</div></body>";
				sprintf(buff,"%d",pageIndex);
				path=inputData->data["OCRTables"]+"/letterBase";
				path+=buff; path+=".jpg";
				cout<<"start write data"<<END;
				WriteImageData(baseImg,path,0);
				baseImg->fill(255);
				yImg=0; xImg=0; pageIndex++;
				c_out<<"</div>";
				c_out.close();
				
				sprintf(buff,"%d",pageIndex);
				string path=inputData->data["OCRTables"]+"/letterBase";
				path+=buff; path+=".html";
				c_out.open(path.c_str());
				c_out<<headerPageHTML<<endl;
				sprintf(buff,"%d",pageIndex);
				path="letterBase";
				path+=buff; path+=".jpg";		
				cout<<"path="<<path<<END;
				cout<<"inputData->data[\"inputFile\"]="<<inputData->data["inputFile"];	
				c_out<<"<div style=\"position:absolute; left:0px; top:0px;\">";
				c_out<<"<img class=\"srcImg\" src=\""<<path<<"\" width=\"2000px\"/>\n";
			}
			
			//cout<<"needDraw "<<correctionWordArray[index].name<<END;  //
			correctionWordArray[index].img->unpackImg();
			baseImg->drawImg(correctionWordArray[index].img,xImg*200+20,yImg*200+20);
			//cout<<"done";
			
			c_out<<endl<<"<div class=\"gL"<<correctionWordArray[index].checkFlag<<"\" id=\"d"<<indexLetter<<"\" onClick=\"selectCell('d"<<indexLetter<<"', event)\" onBlur=\"setText('d"<<indexLetter<<"')\" ";
			c_out<<"style=\"left:"<<xImg*100<<"px; top:"<<yImg*100;
			c_out<<"px; width:"<<100<<"px; height:"<<100<<"px; text-align:right \" f=\""<<correctionWordArray[index].file;
			c_out<<"\" x0=\""<<correctionWordArray[index].x0<<"\" y0=\""<<correctionWordArray[index].y0<<"\" x1=\""<<correctionWordArray[index].x1<<"\" y1=\""<<correctionWordArray[index].y1<<"\">";
			//c_out<<"<div class=\"ctrl\"><input type=\"checkbox\" id=\"b"<<index<<"\"  value=\"0\" onClick=\"checkGlyphBox("<<index<<")\" ";
			//c_out<<"<br><font size=5>"<<indexLetter<<"|"<<indexLetter<<"</font>";
			//c_out<<"<div class=\"nG\" id=\""<<index;
			//c_out<<"\" onClick=\"edit("<<indexLetter<<")\" onBlur=\"setText1("<<indexLetter;
			c_out<<"<br/>"<<correctionWordArray[index].name<<correctionWordArray[index].delimeter<<"</div>"<<endl;
			
			//c_out<<"<div class=\"dE dM\" id=\"s";
			//c_out<<aliKali[in].letterIndex<<"\" style=\"left:";
			//c_out<<indexX*PICT_SIZE*2<<"px; top:"<<indexY*PICT_SIZE*2+PICT_SIZE+aliKali[in].y0*2<<"px; width:"<<PICT_SIZE*2;
			//c_out<<"px; height:"<<aliKali[in].y1*2-aliKali[in].y0*2<<"px; border: 1px solid grey;\" ></div>\n";
	
			correctionWordArray[index].destroy(); //erase img
			xImg++;  if(xImg==19){xImg=0;yImg++;} indexLetter++;

		}			
		c_out<<"<form enctype=\"application/x-www-form-urlencoded\" method=\"post\" action=\"/cgi/yagpoOCR.cgi\" name=\"main\">\n";
		//c_out<<"<input  name=\"inputFile\"  type=\"hidden\" value=\""; c_out<<inputData->data["inputFile"];c_out<<"\"/><br/>\n";
		c_out<<"<input  name=\"ocrData\"  type=\"hidden\" value=\"setCorrectionTable\"/><br/>\n";
		c_out<<"<input  name=\"inputFolder\"  type=\"hidden\" value=\""; c_out<<inputData->data["inputFolder"];c_out<<"\"/><br/>\n";
		c_out<<"<button name=\"submit\" value=\"submit\" type=\"submit\">Set letter in base</button><br/>\n";
		c_out<<"<textarea ID=\"outputStr\" name=\"letterCorrection\" cols=\"110\" rows=\"7\"></textarea>\n";
		c_out<<"</form>";
		c_out<<"</div></body>";
		sprintf(buff,"%d",pageIndex);
		path=inputData->data["OCRTables"]+"/letterBase";
		path+=buff; path+=".jpg";
		cout<<"start write data"<<END;
		WriteImageData(baseImg,path,0);
		c_out<<"</div>";
		c_out.close();
    }
}//_____________________________________________________________________________

