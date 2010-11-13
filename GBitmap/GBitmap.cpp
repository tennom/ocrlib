//13_3 ноября 2010 года.

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
# include "GBitmap.h"
# include "config.h" 
#include <string.h>
#include <stdio.h>
#include "php2stl.h"

namespace ocr{

#include "detectorRadon.h"
#include "focalPoint.h"

	
GBitmap::~GBitmap(){
}

void
GBitmap::destroy(void)
{
	//cout<<" data_size="<<data_size<<" pack_flag="<<pack_flag<<endl;
	if(data_size){  
	    if(!pack_flag){
			free(bytes_data);
		}else{
		   free(bites_data);
		}
	}	
	//data_size=0; cout<<"done";
}

GBitmap::GBitmap()
  : nrows(0), ncolumns(0), border(0),
	bytes_per_row(0),data_size(0)

{
}

GBitmap::GBitmap(int ncolumns,int nrows)
  : nrows(0), ncolumns(0), border(0),
	bytes_per_row(0), data_size(0)
{
  try
  {
	init(ncolumns,nrows);
  }
  catch(int a)
  {
	destroy();
  }
}


GBitmap::GBitmap(const GBitmap* ref)
  : nrows(0), ncolumns(0), border(0),
	bytes_per_row(0),data_size(0)
{
  try
  {
	init(ref);
  }
  catch(int a)
  {
	destroy();
  }
}
	
GBitmap::GBitmap(const GBitmap* ref, float scale, float rotation)
	: nrows(0), ncolumns(0), border(0),
	bytes_per_row(0),data_size(0)
{
		try
		{
			init(ref,scale,rotation);
		}
		catch(int a)
		{
			destroy();
		}
}

GBitmap::GBitmap(const GBitmap* ref, int x0,int y0, int w, int h)
	: nrows(0), ncolumns(0), border(0),
	bytes_per_row(0),data_size(0)
{
	try
	{
		initRegion(ref, x0, y0, w, h);
	}
	catch(int a)
	{
		destroy();
	}
}
	
	
GBitmap::GBitmap(const char *path, int mode, int invert)
: nrows(0), ncolumns(0), border(0),
bytes_per_row(0),data_size(0)
{
	try
	{   
		init(path, mode, invert);
	}
	catch(int a)
	{
		destroy();
	}
}
	
GBitmap::GBitmap(string &inputData,int invert)
: nrows(0), ncolumns(0), border(0),
bytes_per_row(0),data_size(0)
{
		try
		{   
			init(inputData,invert);
		}
		catch(int a)
		{
			destroy();
		}
}
	
	
	

// ----- initialization

void
GBitmap::init(int acolumns, int arows)
{
  grays = 2;
  // выравнивание bytes_data по 32
  // добавляет к исходной картинке вправо и вниз бордюр размером в остаток
  // от деления сответственно: ncolumns на 32 (ncolumns%32),  nrows на 32 (nrows%32).
  nrows = (arows/32+1)*32;       // nrows = arows;
  ncolumns =(acolumns/32+1)*32;  // ncolumns = acolumns;

  data_size=ncolumns*nrows;
  int npixels = data_size;
  w=ncolumns;  h=nrows;  bytes_per_row=ncolumns;
  border=0;

  // инициализация байтового массива char размером  data_size
  bytes_data=(unsigned char*)malloc(data_size);  // запрос памяти с очисткой 0

  fill(255);
  pack_flag=0;
  pack_flag32=0;

/*   // старый вариант (можно удалить)
  grays = 2;
 // nrows = arows;
  nrows = (arows/32+1)*32;
 // ncolumns = acolumns;
  ncolumns =(acolumns/32+1)*32;

//if(ncolumns>128){
//	  if(ncolumns%8<4){
//		ncolumns-=ncolumns%8; //выравнивание битмапа по 8 увеличивает скорость обращения и необходимо для компрессии
//	  }else{
//		ncolumns-=ncolumns%8;
//	  }
//}
  border = 0; w=ncolumns; h=nrows;
  bytes_per_row = ncolumns;
  int npixels = nrows * bytes_per_row;
  data_size=ncolumns*nrows;
  if (npixels > 0)
	{
	  // инициализация байтового массива char размером  data_size
	  bytes_data=(unsigned char*)malloc(npixels);  // запрос памяти с очисткой 0
	}

  fill(255);
  pack_flag=0;
  pack_flag32=0;
*/
}


void
GBitmap::init(const GBitmap* ref){
  if (this != ref)
	{	
	  border=0;
	  init(ref->ncolumns,ref->nrows);
	  unsigned char *row = bytes_data;
	  unsigned char *rowDest;
	  for (int n=0; n<nrows; n++, row+=bytes_per_row){
		 rowDest=ref->bytes_data+bytes_per_row*n;
		 memcpy( (void*)row, (void*)rowDest,  ncolumns );
	  }
	}
   data_size=ncolumns*nrows;
   pack_flag=0;	
}


	/** @fn void GBitmap::initRegion(const GBitmap* ref, int x0,int y0, int w, int h)
	 @brief функция инициализации GBitmap регионом графического файла ref по заданным  координатам 
	 */
void GBitmap::initRegion(const GBitmap* ref, int x0,int y0, int w, int h){
    //cout<<"start"<<" x0="<<x0<<" y0="<<y0<<" w="<<w<<" h="<<h<<END;
	data_size=0;	
	pack_flag=0;
	    //normalisation
	    if(x0<0)x0=0;
		if(y0<0)y0=0;
	    if(x0>ref[0].columns())x0=0;
	    if(y0>ref[0].rows())y0=0;
		if(w+x0>ref[0].columns())w=ref[0].columns()-x0;
	    if(h+y0>ref[0].rows())h=ref[0].rows()-y0;
		unsigned char *p;
	if (this != ref)
	{	
		init(w,h); //после инициализации битмап выровнен по 8
		//cout<<"start1"<<" x0="<<x0<<" y0="<<y0<<" w="<<w<<" h="<<h<<END;
		int x,y;      // ( переменная d, 7 ноября 2010, быстрее классической).
		unsigned char *d;
		for (y = 0; y < h; y++){
			d=bytes_data+y*ncolumns;
			for (x = 0; x < ncolumns; x++){
				p=d+x;
				*p=ref[0][y0+y][x0+x];
				//if(  pImg[0][y][x]>150){
				//   DS(0);
				//}else{
				//   DS(1);
				//};
			 }//DS(END);
		}
	}
	data_size=ncolumns*nrows;	
	pack_flag=0;
	//cout<<"done read"<<END;
}//_____________________________________________________________________________
	

void GBitmap::init(const GBitmap* ref, float scale, float rotation){
//cout << "@@@_____scale="<<scale<<endl;
	if (this != ref){
		pack_flag=0;
		
		if(scale!=0&&rotation!=0){
		rotateFast(ref,scale,rotation);
		return;
		}
		if(scale!=0){
		scaleFast(ref,scale);
		return;
		}
		if(rotation!=0){
		  
		rotateFast(ref,1,rotation);
		return;
		}

	}

}//_____________________________________________________________________________
	

void GBitmap::init(const char *path, int mode, int invert_){
	//cout << "@@@_____init new GBitmap from file="<<path<<endl;

	int arows,acolumns;
	nrows=0;ncolumns=0;data_size=0;pack_flag=0;
		
	readTIFF(path,invert_,&bites_data,&acolumns,&arows);
	if(!acolumns||!arows)return;
	nrows = arows;
	ncolumns = acolumns;
	border = 0;
	bytes_per_row = ncolumns;
	TIFF_string=readText(path);

	/*
	for(int i=0;i<nrows;i++){
	   for(int j=0;j<ncolumns/8;j++){
		   if(bites_data[i*(ncolumns/8)+j]){cout<<".";}else{cout<<"0";}
	   }cout<<endl;
	}
	*/ 
	
	data_size=nrows*ncolumns;
	pack_flag=1;
	unpackImg(1);
	if(invert_)invert();

		
}//_____________________________________________________________________________
	
	
void GBitmap::init(string &inputData,int invert_){
	// cout << "@@@_____init new GBitmap from Tiff string="<<endl;
		
		//int arows,acolumns;
		nrows=0;ncolumns=0;data_size=0;pack_flag=0;
		
		//readTIFF(path,invert,&bites_data,&acolumns,&arows);
		readTIFFFromString(inputData,invert_,&bites_data,&ncolumns,&nrows);

		if(!ncolumns||!nrows)return;
		border = 0;
		bytes_per_row = ncolumns;
		
		/*
		 for(int i=0;i<nrows;i++){
		 for(int j=0;j<ncolumns/8;j++){
		 if(bites_data[i*(ncolumns/8)+j]){cout<<".";}else{cout<<"0";}
		 }cout<<endl;
		 }
		 */ 
		
		data_size=nrows*ncolumns;
		pack_flag=1;
		unpackImg(1);
	    if(invert_)invert();
		
}//_____________________________________________________________________________
	
	

													 // ГОТОВАЯ version

/** масштабирование (Resample) серого (char) массива по методу "ближайших соседей" */
void GBitmap::scaleFast(const GBitmap*ref, float scale){

				int x,y,yp;
				int w=ref->columns();    //cout<<"w="<<w;  /// ширина массива
				int h=ref->rows();       //cout<<" h="<<h; /// высота массива
				int p,new_p;             ///  пиксел, бижайший пиксел
				//unsigned char *d;
				//scale=1.33;
TIME_START
				// float scale=0.536;   масштаб нового массива float, ипи double
				if (scale>5){scale=5;}   if (scale<0.2){scale=0.2;} // ограничения на масштаб
				int new_w=w*scale;  // ширина нового массива
				int new_h=h*scale;  // высота нового массива
				int scaleP=256*scale;

				// инициализация нового (маштабированного) битового массива bytes_data
				// Get a new buffer to interpolate into bool Resample   http://www.cplusplus.com/forum/general/2615/
	            init(new_w,new_h);

				//cout<<"init(), Resample (scale), New version V0 new_w="<<new_w<<" new_h="<<new_h<<" w="<<w<<" h="<<h<<END;

				unsigned char *p0=bytes_data;
				unsigned char *p1=ref->bytes_data;

			   int w_h=w*h-1;   int new_h_new_w=new_h*new_w-1;// ( переменнне, 7 ноября 2010, быстрее классической).
	           for(y = 0; y < new_h; y++) { //cout<<y<<" ";
				  yp=((y<<8)/scaleP)*w;                         // *256
				  p=y*new_w;
				  for(x = 0; x < new_w; x++) {                  //p=y*new_w + x;
					//new_p=( ((int)(y/scale)*w) + ((int)(x/scale)) ); // medlenno
					new_p=(x<<8)/scaleP + yp;
					//  разный масштаб по разным координатам
					/// new_p=( ((int)(y/scale_h)*w) + ((int)(x/scale_w)) );
					/// if(new_p>=w*h){continue;} if(p + x>=new_h*new_w){continue;}
					if(new_p>w_h){continue;}
					if(p + x>new_h_new_w){continue;}
					*(p0 + p + x)=*(p1+new_p);
					// вывод на экран
					////d=new_data + p;     if(*d>127){cout<<"1";}else{cout<<".";}
				  } ////cout<<END;
			   }

TIME_PRINT
			   //cout<<"done" ;
/**/
}//_______________________________________________________________________________

	// ГОТОВАЯ version
	/**  Вращение или (и) масштабирование битовой картинки */
	void GBitmap::rotateFast(const GBitmap*src, float scale, float rotation){
		
		if( rotation == 0 ) { return; }
		
		// the scaling factor  // Коэффициент масштабирования  (обратно прпорциональный масштаб)
		//float scale=1.0;
		
#define SCALE scale* ///выполнение масштабирования при вращении
		//#define SCALE          ///
		
		// the rotation angle  // угол поворота в градусах    ///ang=0.03;
		double ang=rotation / 57.29747;  // ang - угол поворота в радианах
		// 57.29747 = 180/3.1415 = PI / 180;
		
		
		int w,h;
		int x,y;
		w=src->columns(); // ширина массива  IMAGE WIDTH
		h=src->rows();    // высота массива  IMAGE HEIGHT
		int w_1=w-1;      int h_1=h-1;
		int w_2=w/2;      int h_2=h/2;
		int w_h=w*h;
		int k=1<<16;      //  k=65536        // 0x10000=65536      0x8000=32768
		int d0, d1;
		
		
		// Вращение битовой картинки на +90° или -90°
		if (rotation==90||rotation==-90) {    //cout<<"abc(rotation)=90"<<END;
			cout<<END<<"rotateFast(), rotate -90, +90 New version V0"<<END;
			
			TIME_START    //  time=0.14  w=2591  h=3990  rotation== -90
			// изменение размеров выходной картинки для углов вращения 90 или -90 градусов
			
			init(h,w);  // обратный порядок h,w
			unsigned char *p0=bytes_data;
			unsigned char *p1=src->bytes_data;
			
			// Rotate one pixel at a time.
			// rotate by-90°, вращение против часовой стрелки,
			unsigned int index_=0;  int dlt=1; // было unsigned int dlt до 5 ноября 2010 года
			// rotate by+90°, вращение по часовой стрелки.
			if (rotation== 90) { index_=w_h, dlt=-1; }
			
			// переупаковка (транспонирование) всего  горизонтального
			// массива строк в массив вертикальные строк.
			for ( x=0; x < w ; x++ ) {    // time=0.016
				for ( y=0; y < w_h; y+=w){
					*(p0 + index_)= *(p1 + x + y);
					index_+=dlt;
				} // y
			} // x
			
			TIME_PRINT
			cout<<"rotation="<<rotation<<END;
			return;
			
		}  // if
		/**/
		
		TIME_START     //  time=0.156  w=2591,  h=3990,  rotation=-5
		
		// Вращение битовой картинки на произвольный угол и 180°
		cout<<END<<"rotateFast(), rotate free and 180° version V0"<<END;
		
		// размеры выходной картинки не меняются
		init(w,h);    // прямой порядок h,w
		unsigned char *p0=bytes_data;
		unsigned char *p1=src->bytes_data;
		
		int x0,y0,x1,y1, xp,yp, xdx,xdy,ydx,ydy;

	   //	SCALE=1.0/(1.0+0.2*cos(ang*4.0)); //коэффициент yвеличения каpтинки

		double SinA=sin(ang);       // float, ипи double
		double CosA=cos(ang);

		// какyю точкy каpтинки надо изобpажать в веpхней левой точке экpана?
		//x0 = (160.0 + scale*(-160.0*CosA+100.0*1.2*SinA))*65536.0;
		//y0 = (100.0 + scale*(-100.0*CosA-160.0*SinA/1.2))*65536.0;

		x0 = (w_2 + SCALE(-w_2*CosA+h_2*SinA))*k;
		y0 = (h_2 + SCALE(-h_2*CosA-w_2*SinA))*k;

		// на сколько надо сместиться по каpтинке пpи пеpемешении по экpанy
		// на пиксель влево
		xdx = SCALE(CosA*k);     //xdx = scale*CosA*65536.0;
		xdy = SCALE(SinA*k);     //xdy = scale*SinA*65536.0/1.2;
		// на пиксель вниз
		ydx =-SCALE(SinA*k);     //ydx =-scale*SinA*65536.0*1.2;
		ydy = SCALE(CosA*k);     //ydy = scale*CosA*65536.0;
		
		
		for (y=0; y<h; y++) {
			// x0, y0 - кооpдинаты на каpтинке начала текyщей стpоки сканиpования
			// x1, y1 - кооpдинаты на каpтинке текyщей pисyемой точки
			x1 = x0;    y1 = y0;
			
			d0 = y*w;
			for (x=0; x<w; x++) {
				// xp, yp - кооpдинаты на каpтинке текyщей pисyемой точки
				xp = x1 >> 16;  yp = y1 >> 16;   // /65536
				
				d1 = yp*w;
				if ( xp>=0 && xp<=w_1 && yp>=0 && yp<=h_1 ) {
					// dest[0][y][x] = src[0][yp][xp];
					*(p0 + x + d0) = *(p1 + xp + d1);
				}
				  // { dest[0][y][x] = 255; }
				else { *(p0 + x + d0) = 255; }
				
				x1+=xdx;   y1+=xdy; // пеpедвижение вдоль стpоки сканиpования
			} // x
			x0+=ydx;   y0+=ydy;     // пеpеход к новой стpоке сканиpования
		} // y
		
		cout<<"rotation="<<rotation<<END;
		
		TIME_PRINT

		// http://www.enlight.ru/demo/faq/smth.phtml?query=alg_bitmap_rotate
		// "DEMO.DESIGN FAQ, http://www.enlight.ru/demo/faq".
		// Вpащение pастpовой каpтинки
		// http://algolist.manual.ru/graphics/rotate.php

	}//_____________________________________________________________________________
	
	
// Fills a bitmap with the given value
// Заполняет растровое изображение заданным значением value
void  GBitmap::fill(unsigned char value){
		
		memset (bytes_data, value, data_size);

//  for(unsigned int y=0; y<rows(); y++)
//	{
//	  unsigned char* bm_y = (*this)[y];
//	  for(unsigned int x=0; x<columns(); x++)
//		bm_y[x] = value;
//	}
}//_________________________________________________________________________

// вывод на экран растрового изображения
void GBitmap::drawImg(GBitmap *img,int x0,int y0){
	int w=img->columns();
	int h=img->rows();
	//cout<<"x0="<<x0<<" y0="<<y0<<" w="<<w<<" h="<<h<<" ncolumns="<<ncolumns<<" nrows="<<nrows<<endl;
	if(w>ncolumns)w=ncolumns;
	if(h>nrows)h=nrows;
	
	if(x0+w>ncolumns)x0=0;
	if(y0+h>nrows)y0=0;

	int x,y;
	unsigned char *p,*d; // (переменная d, 7 ноября 2010, быстрее классической).

	for (y = 0; y < h; y++){
		d=bytes_data+(y0+y)*ncolumns+x0;
		for (x = 0; x < w; x++){
			p=d+x;
			*p=img[0][y][x];
		}
	}
	//cout<<"draw done";
}//___________________________________________________________________________

// вывод на экран псевдографики массива битмап bytes_data
void GBitmap::printToScreen(){
	int w=ncolumns;
	int h=nrows;

	int x,y;
	unsigned char *p,*d; // (переменная d, 7 ноября 2010, быстрее классической).

	for (y = 0; y < h; y++){
		d=bytes_data+y*ncolumns;
		for (x = 0; x < w; x++){
			p=d+x;
			printf("%02x", *p);
			//if(*p>0){cout<<"1";}else{cout<<".";}
		}cout<<END;
	}

}//____________________________________________________________________________

// инверсия входного массива битмап bytes_data с уровнями 0-255.
void GBitmap::invert(){


//DM(END<<" TIME_START invert "<<END);
//TIME_START

		//Новая версия. Инверсия входного массива битмап.
		// (изменено 7 ноября 2010, в 9 раз быстрее классической).
//*
		// приведенный к unsigned int исходный распакованный массив черно-белого скана
		unsigned int* bytes_data_32=(unsigned int*)bytes_data;

		// инвертируем одновременно все 4 байта 32х разрядного слова. 255 11111111
		// 255,255,555,255 0xFFFFFFFF    0,0,0,0 0x00000000
		unsigned int b_data=data_size/4;
		for ( int x=0; x < b_data; x++ ) {
		   bytes_data_32[x]=~bytes_data_32[x]; //>>7 & 0x1010101 ^ invert
		} // x                                 // ^ исключающее ИЛИ
//*/

/*
	   //Старая версия. Инверсия входного массива битмап.
		int w=ncolumns;
		int h=nrows;
		int x,y;
		unsigned char *p;
		for (y = 0; y < h;y++){
			for (x = 0; x < w; x++){
				p=bytes_data+y*ncolumns+x;
				*p=255-*p;
				//if(*p>0){cout<<"1";}else{cout<<".";}
			}//cout<<END;
		}
//*/
//TIME_PRINT_

}//____________________________________________________________________________


void GBitmap::rotate(int count){


}//____________________________________________________________________________


	// ГОТОВАЯ НОВАЯ fast version
	
	//***********************Adaptive Threshold************************************
	// функция преобразования серого массива в битовый массив (адаптивный порог)

	// Авторы = "DerekBradley and GerhardRoth".
	// www.derekbradley.ca / AdaptiveThresholding / index.html.
	
	void  GBitmap::binarisation(int Tr, int BASE) {
		//***********************Adaptive Threshold************************************

		// BASE средний размер буквы или строки по всей странице. Напрямер Tenjur BASE=46pix.
		// скользящия область S*S вычисления значения средней яркости  в 3,5
		// больше размера буквы или строки S=BASE*3.5
		
		// Tr - устанавливает порог как число процентов, от вычисленного
		// адаптивного порога в виде значения средней яркости по области S*S.
		// Если значение яркости текущего пикселя на Tr процентов ниже, чем в среднея
		// яркость по области S*S то он установлевается в черное,
		// в противном случае он установлевается в белое. Обычно Tr=80.
		// Tr меньше - более тонкие линии (штрихи), Tr больше - более толстые линии.
		
		// Check arguments and init variables
		short w=ncolumns;   // ширина массива   IMAGE_WIDTH
		short h=nrows;      // высота массива   IMAGE_HEIGHT
		
		unsigned int* integralImg;
		unsigned int *d1;
		unsigned char* input=bytes_data;
		unsigned char *d0, *p0;
		
		unsigned int sum=0;
		unsigned int count=0;
		int x, y, x1, y1, x2, y2;
		// вспомогательные переменные для увеличения быстродействия
		unsigned int *p1, *p2;
		
		cout<<END<<"adaptiveThreshold(), New version V0"<<END;
		
		
		TIME_START  //  time=0.297  w=2698 h= 4000
		
		
		integralImg = (unsigned int*)malloc(w*h*sizeof(unsigned int*));
		
		// выход в случае отсутствия свободной памяти запрашиваемого размера
		if (integralImg==NULL) {DC("integralImg"); return;}
		
		// обнуление массива new_data
		//memset(integralImg,0,w*h*sizeof(unsigned int*));
		
		
		// create the integral image
		// интегральная яркость integrated brightness
		
		for (y=0; y<h; y++)
		{
			// reset this column sum
			sum = 0;
			// вспомогательные переменные для увеличения быстродействия
			p0 = input + y*w;
			p1 = integralImg + y*w;
			
			for (x=0; x<w; x++)
			{
				d1 = p1 + x;             // d0 = (input + y*w + x);
				
				// подсчет сумм яркостей для обработки скользящего суммирующего квадрата S*S
				sum += *(p0 + x);        // sum += input[index];
				
				if ( y==0 )              // d0=(input + index);
					*d1 = sum;           // integralImg[index] = sum;
				else
					*d1 = *(d1-w) + sum; // integralImg[index]=integralImg[index-1] + sum;
			} //x
		} //y
		/* */
		
		// TIME_PRINT
		
		
		// ограничения на процент от порога  Tr
		if (Tr < 16) Tr = 16;   if (Tr > 99) Tr = 99;
		
		// позволяет использовать сдвиг <<7 вместо деления в цикле perform thresholding
		Tr=(Tr<<7)/100 + 1 ; //     // 80*128/100;   (80<<7)/100;
		
		// ограничения на размер буквы BASE в пикселях, где
		// BASE средний размер буквы или строки по всей странице, в Tenjur=46
		if (BASE < 4) BASE = 4;   if (BASE > 160) BASE = 160;
		int S=BASE*35/10;  // S в 3,5 больше размера буквы или строки  S=46 *3,5=160
		int s2=S/2;
		
		// вспомогательные переменные, для увеличения быстродействия
		int h_1=h-1;
		int w_1=w-1;
		int y2_y1;
		
		
		
		// perform thresholding
		
		for (y=0; y<h; y++){
			
			// set the SxS region
			y1 = y - s2;  y2 = y + s2;
			
			// check the border
			if (y1 < 0)   y1 = 0;
			if (y2 > h_1) y2 = h_1;         //   if (y2 >=h) y2 = h-1;
			
			// вспомогательные переменные, для увеличения быстродействия
			p0 = input + y*w;
			p1 = integralImg + y1*w;
			p2 = integralImg + y2*w;
			y2_y1 = y2 - y1;
			
			for (x=0; x<w; x++){
				
				// set the SxS region
				x1 = x - s2;  x2 = x + s2;
				
				// check the border
				if (x1 < 0)   x1 = 0;
				if (x2 > w_1) x2 = w_1;     //   if (x2 >=w) x2 = w-1;
				
				// площадь суммирующего квадрата S*S с учетом border
				count = y2_y1*(x2-x1);      // count = countX*(y2-y1);
				
				// сумма серого папавшая в площадь квадрата S*S
				// I(x,y)=s(x2,y2)-s(x1,y2)-s(x2,y1)+s(x1,x1)
				// sum = integralImg[y2*w + x2] - integralImg[y1*w + x2]
				//	    -integralImg[y2*w + x1] + integralImg[y1*w + x1];
				sum = *(p2 + x2) - *(p1 + x2) - *(p2 + x1) + *(p1 + x1);
				
				d0 = p0 + x;
				/// Бинаризация///
				// если яркость (0-255) пиксела больше средней по площади
				// яркости скользящего квадрата S*S,то считаем пиксель белым.
				// if (input[index]*count > (sum*Tr)>>7)  {input[index]=255;}
				if ( *d0*count > ((sum*Tr)>>7) )  { *d0=255; }  // 255 белый
				else { *d0=0; }   //else { input[index]=0; }    //  /128
				
			} // x
			
		}  // y
		/**/
		
		
		// освобождение массива integralImg
		if ( integralImg !=NULL ) free(integralImg);

		
		// cout<<"w="<<w<<END;    cout<<"h="<<h<<END;
		// cout<<"Tr="<<Tr<<END;
		// cout<<"(Tr*100)>>7="<<((Tr*100)>>7)<<END;
		// cout<<"S="<<S<<END;
		// cout<<"sizeof(int)="<<sizeof(int)<<END;

		TIME_PRINT

	}//_____________________________________________________________________________


	// Упаковка большого битмапа в маленькй битовый массив.
	// Используется для записи в формате TIFF.
	// есть 32х битная реализация packImg32

	void GBitmap::packImg(int invert){

		if(pack_flag)return;

	int y,x,d;
	unsigned int s;
	unsigned int data_size_p=data_size/8;
	// data_size=ncolumns*nrows;  размер массива буквы (букв)
	// ncolumns ширина массива буквы (букв), nrows высота массива буквы (букв)

	// инициализация битового массива char размером  data_size_p=data_siz/8
	bites_data=(unsigned char*)malloc(data_size_p);
	// обнуление bites_data
	memset(bites_data,0,data_size_p);
	// выход в случае отсутствия свободной памяти запрашиваемого размера
	//if (bites_data==NULL) {DC("bites_data"); exit (1);}

			 //автоопределение количества градаций в битмапе
			 int max=0;
			 for ( x=0; x < data_size; x++ ) {
			   s=bytes_data[x];
			   if ( s > max ) max=s;
			 }

			 // бинаризация входного массива битмап
			 if(max>1){
				 for ( x=0; x < data_size; x++ ) {
					 if(invert){
					   if ( bytes_data[x]>127 ){ bytes_data[x]=0; } // уровни в битмапе 0 и 255
					   else { bytes_data[x]=1; }  // уровни в битовом массиве 1 и 0
					 }else{
					   if ( bytes_data[x]>127 ){ bytes_data[x]=1; } // уровни в битмапе 0 и 255
					   else { bytes_data[x]=0; }  // уровни в битовом массиве 1 и 0
					 }

				  }
			 }
/**/


								  // ЗАПАКОВКА
			  // Запаковка стандартного большого байтового массива битмап
			  // (в одном байте 1 бит) в маленькй битовый массив (в одном байте 8 бит).
			  unsigned int reg=0;
			  for( y=0; y < data_size_p; y++ ){  // >>3  деление на 8
				 d=y*8;                          // <<3  умножение на 2 в 3 степени = 8
				 for ( x=0; x < 8; x++ ) {
					  reg=(reg << 1) + bytes_data[d+x]; // обратный порядок пикселей
///					 s=(bytes_data[d + x])<<7; // <<31 умножение на 2 в 31 степени, >> 1 деление на 2
///					 reg=s + (reg >> 1) ;               // прямой порядок пикселей
				 } // x
				bites_data[y]=reg;  // заполнение маленького выходной битового массива char
			  } // y
/**/

			  free(bytes_data);  // освобождение большого массива битмап

			  // 1 запакован, каждый бит всех байтов маленького (char) массива заполнен битами
			  pack_flag=1;

}//_____________________________________________________________________________

// Распаковка маленького битового массива в большй битмап.
// Используется для увеличения скорости доступа при обработке картинок букв.
// есть 32х битная реализация unpackImg32

void GBitmap::unpackImg(int invert){
	//cout<<"pack_flag"<<pack_flag<<" data_size="<<data_size<<endl;

	if(!pack_flag)return;

	if(TIFF_string.size()){
		readTIFFFromString(TIFF_string,0, &bites_data, &ncolumns, &nrows);
		data_size=ncolumns*nrows;
		w=ncolumns; h=nrows; invert=1;
		//cout<<"ncolumns="<<ncolumns<<" nrows="<<nrows<<endl;
	}
	int y,x,d;
	unsigned int s;
	unsigned int data_size_p=data_size/8;

	// инициализация большого массива (битмап) bytes_data  полного размера data_siz
	bytes_data=(unsigned char*)malloc(data_size);

								  // РАСПАКОВКА
			// Распаковка маленького битового массива (в одном байте 8 бит) в
			// большй стандартный байтовый массив битмап (в одном байте 1 бит).
			for( y=0; y < data_size_p; y++ ){  // >>3  деление на 8
				s=bites_data[y];   d=y*8;
				for( x=0; x < 8; x++ ){
				  //(bytes_data[d + x])=s & 1;     s=(s >> 1); // прямой порядок пикселей
					if(invert){
						bytes_data[d + 8-x-1]=255-255*(s & 1); s=(s >> 1); // обратный порядок пикселей
					}else{
						bytes_data[d + 8-x-1]=255*(s & 1); s=(s >> 1); // обратный порядок пикселей
					}
				  // уровни в битмапе  0 и 255
				} // x
			} // y

			free(bites_data);  // освобождение маленького массива

			// распакован, один бит каждого байта большого массива (битмап) заполнен битами
			pack_flag=0;
}//_____________________________________________________________________________

		// использует packImg  unpackImg, а не быстрые packImg32  unpackImg32

string GBitmap::drawToTIFFString(int invert){

	int print=1;
	DT("draw TIFF_string_size="<<TIFF_string.size()<<" pack_flag="<<pack_flag<<endl);
	string data;
	if(TIFF_string.size()){
		return TIFF_string;
	}else if(data_size){
	   DT(".1");
	   if(!pack_flag){
		  packImg(1);
	   }
	   DT(".2");
	   TIFF_string=dataToTIFF(bites_data,data_size/8,ncolumns, nrows);
	}
	DT(".3");
	unpackImg(0);
	return TIFF_string;

};

/** Save GBitmap as TIFF file with GroupFax4 compression*/
void GBitmap::saveTIFF(string &path){
	string str=drawToTIFFString(0);
	writeText(str,path);
}
	
/** Save GBitmap as TIFF file with GroupFax4 compression*/
void GBitmap::saveTIFF(const char* path){
 string str=drawToTIFFString(0);
 string file=path;
 writeText(str,file);
}	
	
	
/**  Убирает белый фон вокруг изображения */
GBitmap* GBitmap::detectRegion(int frame, int *x0,int *x1,int *y0,int *y1){
	
	*x0=-1,*y0=-1,*x1=-1,*y1=-1;

	for(int x=0;x<ncolumns;x++){
		for(int y=0;y<nrows;y++){
			if(*(bytes_data+y*ncolumns+x)<128){*x0=x;break;}
		}
		if(*x0>0)break;
	}
	
	for(int x=ncolumns-1;x>-1;x--){
		for(int y=0;y<nrows;y++){
			if(*(bytes_data+y*ncolumns+x)<128){*x1=x;break;}
		}
		if(*x1>0)break;
	}

	for(int y=0;y<nrows;y++){
		for(int x=0;x<ncolumns;x++){
			if(*(bytes_data+y*ncolumns+x)<128){*y0=y;break;}
		}
		if(*y0>0)break;
	}
	
	for(int y=nrows-2;y>-1;y--){
		for(int x=0;x<ncolumns;x++){
			if(*(bytes_data+y*ncolumns+x)<128){*y1=y;break;}
		}
		if(*y1>0)break;
	}
	
	*x0-=frame; if(*x0<0)*x0=0;
	*y0-=frame; if(*y0<0)*y0=0;
	*x1+=frame; if(*x1>=ncolumns)*x1=ncolumns-1;
	*y1+=frame; if(*y1>=nrows)*y1=nrows-1;	
	
	GBitmap *img=GBitmap::createRegion(this, *x0, *y0, *x1-*x0, *y1-*y0);
    return img;

}//_____________________________________________________________________________

					 // ПОЛИГРАФИЧЕСКОЕ РАСТИСКИВАНИЕ //
					   //(изменено 25 октября 2010).//

/**\brief  Имитация полиграфического растискивания и зашумленности */
void GBitmap::dotGain(int gRateLefts, int gRateRight,
					  int gRateHighs, int gRateLower, int noiseRate){


/**\Подпрограмма представляет собой пространственный фильтр с импульсной
характеристикой (реакция пространственного фильтра на один pix) в виде квадрата
размером gainRate X gainRate */

/**\ При инициализации массива bytes_data необходимо обязательно выровнить по 32
nrows и ncolumns,   nrows = (arows/32+1)*32;   ncolumns =(acolumns/32+1)*32;  */

//if( gRateLefts==0 && gRateRight==0 && gRateHighs==0 && gRateLower==0 ) return;

	int x,y,n;
	unsigned int s,s0,s1;
	unsigned int data_size_p32=data_size/32;
	// bytes_data_buf  ///<промежуточный буфер обработки битмэпа

/**\Типичный способ получения полиграфического растискивания двумя запусками dotGain
убираем со всех сторон по пикселю, сьедаем мелкие детали, которые не надо растискивать
dotGain(-1,-1,-1,-1, noiseRate);
добавляем со всех сторон символа по нескольку пикселей
dotGain( 2, 2, 2, 2, noiseRate);

Количество добавленных однопиксельных слоёв вокруг символа от 1 до 31,
убавленных от -1 до -31, без изменений 0 .   */

///gRateLefts=2;  gRateRight=2;  gRateHighs=2;  gRateLower=2; //TMP ////////////



// количество добавленных однопиксельных слоёв с левой стороны символа
if(gRateLefts>31) gRateLefts=31;   if(gRateLefts<-31) gRateLefts=-31;
// количество добавленных однопиксельных слоёв с правой стороны символа
if(gRateRight>31) gRateRight=31;   if(gRateRight<-31) gRateRight=-31;
// количество добавленных однопиксельных слоёв с верхней стороны символа
if(gRateHighs>31) gRateHighs=31;   if(gRateHighs<-31) gRateHighs=-31;
// количество добавленных однопиксельных слоёв с нижней стороны символа
if(gRateLower>31) gRateLower=31;   if(gRateLower<-31) gRateLower=-31;
/**/

DM(END<<" TIME_START dotGain /GGG/ gRateLefts="<<gRateLefts);
//DM(END); DM("/SHIFTS/");
TIME_START

/**/
//------------------------------------------------------------------------------

					  // УПАКОВКА  PACKING //
	// вызов функции упаковки большого битмапа в маленькй int массив.
	// Массив bites_data из 32х разрядных слов упакован битово.
	// pack_flag32=0; // обнулили в функции GBitmap::init(int acolumns, int arows)
	// invert=0 без инверсии черного и белого, invert=1 с инверсией черного и белого.
	packImg32(0);

	// приведенный к unsigned int исходный упакованный массив черно-белого скана
	unsigned int* bites_data_32=(unsigned int*)bites_data;
/**/
//------------------------------------------------------------------------------

						   // СДВИГИ SHIFTS //
// сдвиг влево, вправо, вверх, вниз всего массива data_size_p32, как единого регистра

	int dl=1;  int dm=32-dl;  // dl - толщина одного слоя в pix по горизонтали
	int d0=dl*ncolumns/32;    // d0 - толщина одного слоя в pix по вертикали

	int dltLefts=abs(gRateLefts);  int dltRight=abs(gRateRight);
	int dltHighs=abs(gRateHighs);  int dltLower=abs(gRateLower);

	// нахождение максимума gainRate из dltLefts, dltRight, dltHighs, dltLower
	int gainRate=0; // количество однопиксельных слоёв
	if( dltLefts>gainRate ) { gainRate=dltLefts; }
	if( dltRight>dltLefts ) { gainRate=dltRight; }
	if( dltHighs>dltRight ) { gainRate=dltHighs; }
	if( dltLower>dltHighs ) { gainRate=dltLower; }
	DM(" gainRate "<<gainRate);

//------------------------------------------------------------------------------

// Цикл по количеству однопиксельных слоёв
int m;
for ( m=0;  m < gainRate;  m++ ) {

// СДВИГ ВЛЕВО всего массива bites_data_32, как единого регистра dltLefts раз
// на величину dl, для прямого порядока пикселей.

	// Добавление пикселей (пикселя) слевой стороны символа.
	if(gRateLefts>0 && m<dltLefts) {
		s0=bites_data_32[0];  // input
		for ( x=0;  x < data_size_p32-1;  x++ ) { // ncolumns*nrows/32;
			s1=bites_data_32[x+1];
			// сдвиг двух 32р регистров s0 и s1 влево, как одного 64р регистра
			bites_data_32[x]=s0&(s0>>dl|s1<<dm);   s0=s1;
		} // x
	} // if

	// убавление пикселей (пикселя) слевой стороны символа.
	if(gRateLefts<0 && m<dltLefts) {
		s0=bites_data_32[0];  // input
		for ( x=0;  x < data_size_p32-1;  x++ ) { // ncolumns*nrows/32;
			s1=bites_data_32[x+1];
			// сдвиг двух 32р регистров s0 и s1 влево, как одного 64р регистра
			bites_data_32[x]=s0|(s0>>dl|s1<<dm);   s0=s1;
		} // x
	} // if

//------------------------------------------------------------------------------
/**/

// СДВИГ ВПРАВО всего массива bites_data_32, как единого регистра dltRight раз
// на величину dl, для прямого порядока пикселей.

	// Добавление пикселей (пикселя) справой стороны символа.
	if(gRateRight>0 && m<dltRight) {
		s0=bites_data_32[data_size_p32-1];
		for ( x=data_size_p32-1;  x > 0 ;  x-- ) {  //  x=data_size_p32-1;  x > -1+1
			s1=bites_data_32[x-1];
			// сдвиг двух 32 разрядных регистров s0 и s1 вправо, как одного 64 разрядного регистра
			bites_data_32[x]=s0&(s0<<dl|s1>>dm);   s0=s1;
		} // x      // уровни в битмапе  0-чёрный и 1-белый
	} // if

	// Убавление пикселей (пикселя) справой стороны символа.
	if(gRateRight<0 && m<dltRight) {
		s0=bites_data_32[data_size_p32-1];
		for ( x=data_size_p32-1;  x > 0 ;  x-- ) {  //  x=data_size_p32-1;  x > -1+1
			s1=bites_data_32[x-1];
			// сдвиг двух 32 разрядных регистров s0 и s1 вправо, как одного 64 разрядного регистра
			bites_data_32[x]=s0|(s0<<dl|s1>>dm);   s0=s1;
		} // x      // уровни в битмапе  0-чёрный и 1-белый
	} // if

//------------------------------------------------------------------------------
/**/

// СДВИГ ВВЕРХ  всего массива bites_data_32, как единого регистра на d0 строк

	// Добавление пикселей с верхней стороны символа.
	if(gRateHighs>0 && m<dltHighs) { // количество добавленных однопиксельных слоёв с верхней стороны символа
		for ( x=0;  x < data_size_p32-d0;  x++ ) {
			bites_data_32[x]=bites_data_32[x] & bites_data_32[x+d0];
		} // x
	} // if

	// Убавление пикселей с верхней стороны символа.
	if(gRateHighs<0 && m<dltHighs) { // количество убавленных однопиксельных слоёв с верхней стороны символа
		for ( x=0;  x < data_size_p32-d0;  x++ ) {
			bites_data_32[x]=bites_data_32[x] | bites_data_32[x+d0];
		} // x
	} // if

//------------------------------------------------------------------------------
/**/

// СДВИГ ВНИЗ всего массива bites_data_32, как единого регистра на d0 строк
	 //int dirRev=~0;  // ^ dirRev)
	 int dirRev=0;
	// Добавление пикселей с нижней стороны символа.
	if(gRateLower>0 && m<dltLower) { // количество добавленных однопиксельных слоёв с нижней стороны символа
		for ( x=data_size_p32;  x > d0;  x-- ) {
			bites_data_32[x]=bites_data_32[x] & bites_data_32[x-d0];
		} // x
	} // if

	// Убавление пикселей с нижней стороны символа.
	if(gRateLower<0 && m<dltLower) { // количество убавленных однопиксельных слоёв с нижней стороны символа
		for ( x=data_size_p32;  x > d0;  x-- ) {   // d0
			bites_data_32[x]=bites_data_32[x] | bites_data_32[x-d0];
		} // x
	} // if
/**/

} // m

//------------------------------------------------------------------------------

/**/
					// РАСПАКОВКА UNPACKING 32 //
	  // вызов функции распаковки маленького битового массива int в большй битмап.
	  // invert=0 без инверсии черного и белого, invert=1 с инверсией черного и белого.
	  unpackImg32(0);
	  //invert();

//******************************************************************************

			// работающая исходная версия
			// сдвиг влево, вправо всего массива data_size_p32, как единого регистра
/*
			dl=1;  // 31
			if(dl<1 || dl>31) return;
			dm=32-dl;
			unsigned int data_size_p32_1=data_size_p32-1;
*/
/*
			// сдвиг влево всего массива data_size_p32, как единого регистра
			// на величину dl, для прямого порядока пикселей
			s0=bites_data_32[0];
			for ( x=0;  x < data_size_p32_1;  x++ ) {   // ncolumns*nrows/32;
				s1=bites_data_32[x+1];
				// беззнаковый сдвиг двух 32 разрядных регистров s0 и s1 влево,
				// как одного 64 разрядного регистра, для прямого порядока пикселей
				///bites_data_32[x]=y1=s1<<dl|s0>>dm;    // y0=s0<<dl;
				bites_data_32[x]=s0>>dl|s1<<dm;    s0=s1;
			} // x
*/
/*
			// сдвиг вправо всего массива data_size_p32, как единого регистра
			// на величину dl, для прямого порядока пикселей
			s0=bites_data_32[data_size_p32-1];
			for ( x=data_size_p32-1;  x > 0 ;  x-- ) {  //  x=data_size_p32-1;  x > -1+1
				s1=bites_data_32[x-1];
				// беззнаковый сдвиг двух 32 разрядных регистров s0 и s1 вправо,
				// как одного 64 разрядного регистра, для прямого порядока пикселей
				bites_data_32[x]=s0<<dl|s1>>dm;    s0=s1;
		   } // x
*/
//******************************************************************************

DM(" ncolumns "<<ncolumns<<" nrows "<<nrows<<END); // DM(" m "<<m<<END);

DM(" gRateLefts "<<gRateLefts<<" gRateRight "<<gRateRight
<<" gRateHighs "<<gRateHighs<<" gRateLower "<<gRateLower<<END);

DM(" TIME_PRINT dotGain /GGG/ ");
TIME_PRINT_  DM(END);


/**/	// y0=~0;   y1=~0;     // ^ |

}//_____________________________________________________________________________

						 // УПАКОВКА  PACKING 32 //
	/**\ Упаковка большого битмапа в маленькй int массив. Массив bites_data
	из 32х разрядных слов упакован битово.
	Используется для функции имитация полиграфического растискивания и зашумленности.*/

	// При переносе в основную версию использовать эту функцию packImg32Б вместо
	// функции packImg.   САА 3 ноября 2010 года.

	void GBitmap::packImg32(int invert){

	if(pack_flag32)return;

	int y,x,d;

	// ncolumns ширина массива буквы (букв), nrows высота массива буквы (букв)
	// data_size=ncolumns*nrows;  размер большого битмапа
	unsigned int data_size_p=data_size/8;   //
	unsigned int data_size_p32=data_size/32;//

DM(END<<" TIME_START packImg32 /P32/ 0="<<0<<END);

	// инициализация битового массива char размером  data_size_p=data_siz/8
	bites_data=(unsigned char*)malloc(data_size_p);           // +ncolumns
	// обнуление bites_data                                   // +ncolumns
	memset(bites_data,0,data_size_p);
	// выход в случае отсутствия свободной памяти запрашиваемого размера
	//if (bites_data==NULL) {DC("bites_data"); exit (1);}

	// приведенный к unsigned int исходный упакованный массив черно-белого скана
	unsigned int* bites_data_32=(unsigned int*)bites_data;
/**/


		  // автоопределение количества градаций в битмапе с управляемой инверсией.
		  //  invert=0;  без инверсии (обычно белый фон)
		  //  invert=1;  с инверсией (обычно черный фон)
		  AutodetectGradations(invert);

						   // Классический вариант //
		  // Запаковка стандартного большого байтового массива битмап
		  // (в одном байте 1 бит) в маленькй  массив int (в одном int 32 бита).

		  unsigned int reg;  // unsigned int dirRev=31; // direct, reverse. dir_rev
		  for( y=0; y < data_size_p32; y++ ){ // >>5  деление на 5  data_size/32
			 d=y*32;  reg=0;             // <<5  умножение на 2 в 5 степени = 32
			 for ( x=0; x < 32; x++ ) {
///	 ///  		 reg=(reg << 1) + bytes_data[d+x]; // обратный порядок пикселей ///////////
			   //reg=bytes_data[d+x] + (reg << 1); // обратный порядок пикселей
				 reg=(bytes_data[d + x]<<31) + (reg >> 1); // прямой порядок пикселей ///////////
			 } // x      // <<31 умножение на 2 в 31 степени,  >> 1 деление на 2
			bites_data_32[y]=reg;  // заполнение маленького выходного массива int
		  } // y
/**/

			  free(bytes_data);  // освобождение исходного большого массива битмап

			  // 1 если массив bites_data из 32х разрядных слов упакован побитово
			  pack_flag32=1;
/**/

}//_____________________________________________________________________________

						// РАСПАКОВКА UNPACKING 32 //
/**\ Распаковка маленького битового массива int в большй битмап.
Используется для функции имитация полиграфического растискивания и зашумленности.*/

// При переносе в основную версию использовать эту функцию unpackImg32 вместо
// функции unpackImg.   САА 3 ноября 2010 года.


void GBitmap::unpackImg32(int invert){
	//cout<<"pack_flag32"<<pack_flag32<<" data_size="<<data_size<<endl;

	if(!pack_flag32)return;

	int y,x,d;
	unsigned int s;
	unsigned int data_size_p32=data_size/32;

DM(END<<" TIME_START unpackImg32 /UP32/ 0="<<0<<END);

	// инициализация большого массива (битмап) bytes_data полного размера data_siz
	bytes_data=(unsigned char*)malloc(data_size);
	// обнуление bytes_data
	memset(bytes_data,0,data_size);
	// выход в случае отсутствия свободной памяти запрашиваемого размера
	//if (bytes_data==NULL) {DC("bytes_data"); exit (1);}

	// приведенный к unsigned int упакованный битовый массив черно-белого скана
	// маленький запакованный массив
	unsigned int* bites_data_32=(unsigned int*)bites_data;

	// приведенный к unsigned int распакованный байтовый массив черно-белого скана
	// большой распакованный массив
	unsigned int* bytes_data_32=(unsigned int*)bytes_data;
/**/

							  // РАСПАКОВКА
		// Распаковка маленького массива int (в одном int 32 бита) в большй стандартный
		// байтовый массив битмап (в одном байте 1 бит) с управляемой инверсией.
//*
						  // Более быстрый вариант. //
		// (изменено 8 ноября 2010, в 1,3 раза быстрее классической).
		// invert=0; // без инверсии (белый фон), invert=1 с инверсией (обычно черный фон)
		if(invert<1) { invert=0;}   if(invert>0) { invert=~0;}

		// По словная запись в массив bytes_data (по 4 байта одновременно)
		unsigned int s0;
		for( y=0; y < data_size_p32; y++ ){  // >>5  деление на 32  // data_size/32
			s=bites_data_32[y];   d=y*8; // 32/4
			for( x=0; x < 8; x++ ){ // 32/4

			  // прямой порядок пикселей     // bytes_data[d + x]=s & 1;  s=(s >> 1);
			  s0 =0x000000FF*(s & 1); s>>=1; // заполнение 00000000 или 11111111 1ого байта 255*
			  s0|=0x0000FF00*(s & 1); s>>=1; // заполнение 00000000 или 11111111 2ого байта 255*<<8;
			  s0|=0x00FF0000*(s & 1); s>>=1; // заполнение 00000000 или 11111111 3его байта 255*<<16;
			  // заполнение 00000000 или 11111111 4ого байта с управляемой инверсией.       255*<<24
			  bytes_data_32[d + x]=(0xFF000000*(s & 1) | s0) ^ invert;   s>>=1;
			  // запись в массив bytes_data одним 32р словом 4х байт одновременно

			  // обратный порядок пикселей // bytes_data[d + 32-x-1]=255*(s & 1);  s>>=1;
//			  s0=255*(s & 1)<<24;   s>>=1; // заполнение 00000000 или 11111111 4ого байта
//			  s0|=255*(s & 1)<<16;  s>>=1; // заполнение 00000000 или 11111111 3его байта
//			  s0|=255*(s & 1)<<8;   s>>=1; // заполнение 00000000 или 11111111 2ого байта
			  // заполнение 00000000 или 11111111 1ого байта с управляемой инверсией.
//			  bytes_data_32[d + 8-x-1]=(255*(s & 1) | s0) ^ invert;   s>>=1;
			  // запись в массив bytes_data одним 32р словом 4х байт одновременно

			} // x     // уровни в битмапе  0-чёрный и 255-белый
		} // y      // s>>=1; деление на 2 с присваиванием
//*/


/*
							// Классический вариант //
		//invert=0; // без инверсии (белый фон), invert=1 с инверсией (обычно черный фон)
		if(invert<1) { invert=0;}   if(invert>0) { invert=1;}

		// По байтная запись массив bytes_data. Классический вариант
		for( y=0; y < data_size_p32; y++ ){  // >>5  деление на 32  // data_size/32
		s=bites_data_32[y];   d=y*32;
			for( x=0; x < 32; x++ ){
			//bytes_data[d + x]=s & 1;     s=(s >> 1);        // прямой порядок пикселей
			  //bytes_data[d + x]= 255*(s & 1 ^ invert);   s=(s >> 1);  // прямой порядок пикселей ///////////
			  bytes_data[d + x]= 255*(s & 1 ^ invert);   s>>=1;  // прямой порядок пикселей ///////////
			//bytes_data[d + 32-x-1]=255*(s & 1); s=(s >> 1); // обратный порядок пикселей       ///////////
			} // x     // уровни в битмапе  0-чёрный и 255-белый
		} // y         // s>>=1; деление на 2 с присваиванием
//*/

//------------------------------------------------------------------------------

						   // TEST //

/*            // 255   65280   16711680    4278190080
			  binaryPrint(0x000000FF, 2);  DM(" "); DM(END);
			  binaryPrint(0x0000FF00, 2);  DM(" "); DM(END);
			  binaryPrint(0x00FF0000, 2);  DM(" "); DM(END);
			  binaryPrint(0xFF000000, 2);  DM(" "); DM(END);

			  // прямой порядок пикселей
			  //bytes_data[d + x]=s & 1;     s=(s >> 1);        // прямой порядок пикселей
			  s0=(s & 1);       s>>=1;  // прямой порядок пикселей ///////////s0=s & 1;   s>>=1;  // прямой порядок пикселей ///////////
			  s0|=(s & 1)<<8;   s>>=1;  // прямой порядок пикселей ///////////
			  s0|=(s & 1)<<16;  s>>=1;  // прямой порядок пикселей ///////////
			  s0|=(s & 1)<<24;  s>>=1;  // 255*
			  ///bytes_data_32[d + x]=(255*(s & 1)<<24 | s0) ^ invert;    s>>=1;  // прямой порядок пикселей ///////////
			  // одновременное умножение 4х байт на 255 с управляемой инверсией.
			  ///bytes_data_32[d + x]=s0 ^ invert; //255*
			  bytes_data_32[d + x]=((s0<<8)-s0) ^ invert;   //  +(s0<<7)
			  ///bytes_data_32[d + x]=((s0<<8)-s0) ^ invert;   //  +(s0<<7)
*/

/*            // TEST
			  invert=~0; // TEST
			  invert=0;  // TEST
			  s=0xFFFFFFFF-1;
			  s=0xFFFFFF01;
			  //s=0x00000000;
			  //s=0xFFFFFF00;
			  unsigned int s0;
			  binaryPrint(s, 2);  DM(" "); DM(END);
			  //s0 = 255*(s & 1);       s>>=1;  // прямой порядок пикселей ///////////s0=s & 1;   s>>=1;  // прямой порядок пикселей ///////////
			  s0 =(s & 1);      s>>=1;
			  binaryPrint(s0, 2);  DM(" "); DM(END);
			  s0|=(s & 1)<<8;   s>>=1;  // прямой порядок пикселей /////////// 255*
			  binaryPrint(s0, 2);  DM(" "); DM(END);
			  s0|=(s & 1)<<16;  s>>=1;  // прямой порядок пикселей ///////////  255*
			  binaryPrint(s0, 2);  DM(" "); DM(END);
			  s0|=(s & 1)<<24;  s>>=1;  // прямой порядок пикселей ///////////   255*
			  binaryPrint(s0, 2);  DM(" "); DM(END);
			  //s0=s0 ^ invert; //255*
			  // одновременное умножение 4х байт на 255 с управляемой инверсией.
			  ///s0=((s0<<7)-s0+(s0<<7)) ^ invert; //255*
			  s0=((s0<<8)-s0) ^ invert; //255*  +(s0<<7)
			  binaryPrint(s0, 2);  DM(" "); DM(END);
			  //bytes_data_32[d + x]=s0; //255*   ^ invert
//*/
//------------------------------------------------------------------------------

/**/
		free(bites_data);  // освобождение маленького массива

		// 0 - массив bites_data распакован функцией unpackImg32
		pack_flag32=0;

//		DM(END<<" data_size "<<data_size<<" ncolumns*nrows "<<ncolumns*nrows<<END);

}//_____________________________________________________________________________



			  // АВТООПРЕДЕЛЕНИЕ ГРАДАЦИЙ В БИТМАПЕ //
/**\ автоопределение количества градаций в битмапе с управляемой инверсией.
Используется для приведения битмапа в состояние: младший бит байта 0-черный, 1-белый.
Входной битмап м.б. 255-белый (напрямер 255-tif, 208-jpeg), 0-черный.*/

void GBitmap::AutodetectGradations(int invert){
	//cout<<"pack_flag32"<<pack_flag32<<" data_size="<<data_size<<endl;

	unsigned int x,s;
	// ncolumns ширина массива буквы (букв), nrows высота массива буквы (букв)
	// data_size=ncolumns*nrows;  размер большого битмапа

	// bytes_data[x]=0 или 1 всегда s=0; битмап уже бинаризован.
	// bytes_data[x]>1       всегда s>0; битмап надо бинаризовать.

	// TEST
	// for ( x=0; x < data_size; x++ ) { bytes_data[x]=1; }

DM(" TIME_START AutodetectGradations /AAA/ invert="<<invert<<END);
TIME_START
//DM(END);


	/// быстрое автоопределение и бинаризация входного массива битмап ///
		 // (изменино 31 октября 2010, в 6-9 раз быстрее классической).
//*
	// приведенный к unsigned int исходный распакованный массив черно-белого скана
	unsigned int* bytes_data_32=(unsigned int*)bytes_data;

	// 0xFEFEFEFE=~(1+(1<<8)+(1<<16)+(1<<24));  0xFEFEFEFE=~(16843009=0x1010101)
	// binaryPrint(0xFEFEFEFE, 2);  DM(" "); DM(END);

	// автоопределение количества градаций в битмапе.

	// маской убираем младший бит во всех 4х байтах 32х разрядного слова в этих
	// младших битах находятся 0 или 1 возможно бинаризованного битмапа. Если в
	// массиве встречается серое (или чб) значит оставшиеся биты составляют число
	// больше ноля, то останавливаем цикл и далее выполняем бинаризацию битмапа.
	unsigned int b_data=data_size/4-8;   s=0;
	for ( x=8; s<1 && x<b_data; x++ ) {  // эквивалентно if(s>0) {break;}
		s=bytes_data_32[x] & 0xFEFEFEFE;
	} // x  // в бинаризации д.б. s>0;

	// Graduation=1; в битмапе встречается серое надо применять адаптивный порог
	// Graduation=0; битмап уже бинаризован.
//	int Graduation=0;
//	if(s>0) Graduation=1;

//*
	// invert=1;  // TEST
	// invert=0 без инверсии (белый фон), invert=1 с инверсией (обычно черный фон)
	if(invert<1) { invert=0;}   if(invert>0) { invert=~0;} // 1111111111111111

	// бинаризация входного массива битмап с управляемой инверсией invert.

	// маской выделяем младший бит во всех 4х байтах 32х разрядного слова
	// в этих младших битах находятся искомые 0 или 1 уже бинаризованного битмапа.
	b_data=data_size/4;
	if(s>0) {  // s>0 // s>4
	   for ( x=0; x < b_data; x++ ) {
		   bytes_data_32[x]=bytes_data_32[x]>>7 & 0x1010101 ^ invert; // деление на 128
	   } // x  // ^ исключающее ИЛИ
	} // if
//*/
	 // Получили выходной битмап с уровнями:   0-черный    1-белый

DM(" s "<<s<<END);
//*/

//------------------------------------------------------------------------------

/*
					 // Классический вариант //
/// классическое автоопределение и бинаризация входного массива битмап ///
		 //автоопределение количества градаций в битмапе
		 int max=0;
		 for ( x=0; x < data_size; x++ ) {
		   s=bytes_data[x];
		   if ( s > max ) max=s;
		 }

		 // бинаризация входного массива битмап
		 if(max>1){
			 for ( x=0; x < data_size; x++ ) {
				 if(invert){
				   if ( bytes_data[x]>127 ){ bytes_data[x]=0; } // уровни в битмапе 0 и 255
				   else { bytes_data[x]=1; }  // уровни в битовом массиве 1 и 0
				 }else{
				   if ( bytes_data[x]>127 ){ bytes_data[x]=1; } // уровни в битмапе 0 и 255
				   else { bytes_data[x]=0; }  // уровни в битовом массиве 1 и 0
				 }
			  }
		 }
//*/
//------------------------------------------------------------------------------

DM(" x "<<x<<" s "<<s<<" invert "<<invert<<END);
// DM(END<<" data_size "<<data_size<<" ncolumns*nrows "<<ncolumns*nrows<<END);
//DM(" s "<<s<<END);

DM(" TIME_PRINT AutodetectGradations /AAA/ ");
TIME_PRINT_
DM(END);

}//_____________________________________________________________________________



};
//******************************************************************************


// -----------------------------------------------------------------------------

// в файле стpоки хpанились в обpатном поpядке, их необходимо пеpеставить
//for (y=0; y<200; y++) memcpy(picture[y],buffer[199-y],320); // 320x200

/*
+++++Встроенные функции потокового SIMD расширения.doc
Например, начало массива элементов типа __m64 выравнивается по 8 байтам,
а массив элементов __m128 – по 16 байтам
Для выделения памяти с выравниванием используется функция:
void *_mm_malloc(int size, int align)
size	– объем выделяемой памяти в байтах (как в malloc),
align	– выравнивание в байтах.
Для освобождения памяти, выделенной таким образом, используется функция:
void _mm_free(void *p);
Например:
	float *x;	// массив для обработки с помощью инструкций SSE
	x=(float)_mm_malloc(N*sizeof(float),16);
	// … здесь обработка …
	_mm_free(x);
*/

//----------------

		// формирование центральной  области  "On"  без переходной области
		// формирование перефирийной области  "Off" без переходной области
	/*
		for (int y=0; y < h; y++ ) {
			s=~BufOff[y];
			Sb=On[y];
			///Off[y]=Off[y] & s;
			if (maskType==1) {On[y]=Sb=Sb & s; }
			// подсчет площади центральной маски "On"
			// Регистровые суммы маски mask32 по  X    //0xFFFFFFFF
			Sb-=(Sb >> 1) & 0x55555555;                // 2-битовые ячейки
			Sb=(Sb & 0x33333333) + ((Sb >> 2) & 0x33333333); // 4-битовые
			Sb=(Sb + (Sb >> 4)) & 0x0F0F0F0F;                // 8-битоовые
			Sb+=Sb >> 8;                               // 16-битовые
			Sb+=Sb >> 16;                              // 32-битовая ячейка
			NMask+=Sb & 0x3F;  // 31 Обнуляем старшие разряды, содержащие "мусор"
		}
		//DM(END<<" x0st "<<x0st<<" x0st "<<x1st<<" x1st "<<y0st<<" y0st "<<y1st<<" y1st "<<END);
		*/

/*
		Регистровые суммы. На примере 8-битного числа:

		v = (v & 0x55) + ((v >> 1) & 0x55);
        v = (v & 0x33) + ((v >> 2) & 0x33);
		return (v & 0x0f) + ((v >> 4) & 0x0f);    //0x0000003F;

*/

/*
str 80
// The following works only for 8-bit quantities.
int pop7(unsigned x) {
   x = x*0x08040201;    // Make 4 copies.
   x = x >> 3;          // So next step hits proper bits.
   x = x & 0x11111111;  // Every 4th bit.
   x = x*0x11111111;    // Sum the digits (each 0 or 1).
   x = x >> 28;         // Position the result.
   return x;
}
*/
/**/
//-----------------------------------------

/*
Количество бит
Здесь изюминка в следующем. Как известно, отнимая от числа единицу мы обнуляем
крайний справа бит числа, например для числа 10011000 мы получим 10010xxx.
Применив полученное число как маску к исходному, операцией &, мы обнулим крайний
справа бит числа. Таким образом цикл будет выполняться столько раз, сколько
единичных бит находится в числе

int get_num_bit(unsigned char ch)
{
 for(int n=0; x!=0; ++n)
  x &=x-1;              //x &= ~(-x);
 return n;
}

алгоритм для чисел с большим количеством нулевых бит
  int t = 0;
  while (x != 0) {
    t += 1;
	x &= x-1; // сбрасываем крайний справа бит
  }
  return t;
алгоритм для чисел с большим количеством единичных бит
  int t=16
  while (x != 0xffff) {
    t--;
    x |= x+1;
  }
  return t;
*/

//-----------------------------------------
/**/
/*
http://www.xserver.ru/computer/langprogr/c_c2p/7/
 5.3.
Подсчитать номер младшего единичного бита (n должен быть ненулевым):
Пример для 32-битного числа n.
		k = 0;
		if((n & 0xFFFF) == 0)   k = 16, n >>= 16;
		if((n & 0x00FF) == 0)   k += 8, n >>= 8;
		if((n & 0x000F) == 0)   k += 4, n >>= 4;
		if((n & 0x0003) == 0)   k += 2, n >>= 2;
		if((n & 0x0001) == 0)   k += 1;

Подсчитать номер старшего единичного бита (если n=0, то k=32):
Пример для 32-битного числа n.
		k = 0;
		if(n & 0xFFFF0000)      k = 16, n >>= 16;
		if(n & 0x0000FF00)      k += 8, n >>= 8;
		if(n & 0x000000F0)      k += 4, n >>= 4;
		if(n & 0x0000000С)      k += 2, n >>= 2;
		if(n & 0x00000002)      k += 1;
*/      //return k
//-----------------------------------------
/**/
 /* как перевернуть число 8 бит наоборот
/ / Реверсивные правый 8 бит в слове.
/ / То же самое, но более эффективным, 15 Brisc ОПС.
неподписанных rev8 (неподписанные х) {
   без знака U, M, S, T;

   U = X * 0x00020202;
   м = 0x01044010;
   S = U & M;
   T = (U <<2) и (M <1);
   возвращение 0x01001001 * (S + T)>> 24;
/ / Возврат (S + T)% 4095 / / Альтернативная, что эквивалентно выше.
*/
/*
  u = x*0x00020202
  m = 0x01044010
  s = u&m
 t = (u<<2)&(m<<1)
 x = (0x01001001*(s+t))>>24
*/
/*
http://www.rsdn.ru/forum/cpp/1849986.flat.aspx
uint8_t binvert8(uint8_t value) // see Warren H.S. Hacker's Delight - p. 109
{
    uint32_t const u = value * 0x00020202;
    uint32_t const m = 0x01044010;
    return (uint8_t)((0x01001001 * ((u & m) + ((u << 2) & (m << 1)))) >> 24);

//    return (uint8_t)((value * 0x0202020202ULL & 0x010884422010ULL) % 1023);
}
*/

//------------------------------------------------------------------------------

/*                     // СТАТИЧЕСКИЕ  массивы  //
  ImBuf=(int*)farcalloc(ncnr+512, 4);    // запрос памяти с очисткой 0
  if (ImBuf==NULL) exit (1);             // 4 длина каждого элемента в байтах
                                         // ncnr+512 количество элементов в массиве

  //       вычисления        //

  if ( ImBuf !=NULL ) farfree(ImBuf);  //  освобождение памяти
*/
//q=(тип_q *)farmalloc(n_byte);     // запрос памяти без очистки 0
//q_new=farrealloc(q_old,n_byte);;  // изменение размера блока

//int *p;
// p = (int *) malloc(100 * sizeof(int)); /* Выделение памяти для 100 целых чисел */


// -----------------------------------------------------------------------------




//******************************************************************************

//   ТЕСТЫ ДЛЯ ФУНКЦИИ dotGain(int gainRate,int noiseRate)
//   Имитация полиграфического растискивания и зашумленности

/*
		int x,y,p,p0,p1;
		int d=dlt;          // dlt толщина стенок перефирийной области  "Off"
		unsigned int Sb;

		int w_32=ncolumns/32; int h=nrows;
		//unsigned int mWH=data_size/32;
		int mWH_32=ncolumns*nrows/32;

		unsigned int s=0;

//		unsigned char* input=bites_data;  // исходный упакованный массив черно-белого скана  ///////////////
		// приведенный к unsigned int исходный упакованный массив черно-белого скана
//////		unsigned int* input=(unsigned int*)bites_data;
							//
//		unsigned char *d0,  // ссылка на на исходный упакованный массив черно-белого скана bites_data
///		unsigned int *BufOn=On;
		unsigned int BufOff[128];   memset(BufOff,0,128);    // обнуление


		DM(" TIME_START dotGain /GGG/ d="<<d<<END);
///		DM("/@@2@@@/маска пересечений"<<"x0="<<x0<<" x1="<<x1<<" y0="<<y0<<" y1="<<y1<<END);

//------------------------------------------------------------------------------
*/
/*
//-----------------------------------
 // Алгоритмические трюки для программистов стр47 сложение и вычитание двойных слов
			// тест  // s0=~0;
			///unsigned int s0=1+2+4+(1<<31)+(1<<30);  unsigned int s1=8+16+(1<<30); // +(1<<29)
			unsigned int s0=~0-1-(1<<31);  unsigned int s1=~0-1-(1<<31); // +(1<<29)

			DM(END<<END<<" s1 "<<s1<<" s0 "<<s0<<END);
			// РАСПАКОВКА на экран, представления одного целого числа int
			// вход значение input
			// int radix  - где radix = 2 для двоичного представления целого числа (binary number);
			// radix = 8 для восьмеричного... и т.д.
			binaryPrint(s1, 2);  DM(" ");  binaryPrint(s0, 2); DM(" ");
			binaryPrint(s1, 2);  DM(" ");  binaryPrint(s0, 2); DM(" ");
			DM(END); DM(END);

			int dl=2;      // dlt сдвиг изображения влево, вправо, в верх, в низ.
			//if(!dl||dl==32) return;
			if(dl<1 || dl>31) return;
			unsigned int y0; unsigned int y1;
			int dm=32-dl;
			unsigned int Buf[8+1];   memset(Buf,0,(8+1)*4);    // обнуление
			Buf[0]=s0;  Buf[1]=s1;
			Buf[2]=s0;  Buf[3]=s1;
			Buf[4]=s0;  Buf[5]=s1;
			Buf[6]=s0;  Buf[7]=s1;
//-----------------------------------
*/
/*
			// сдвиг всего массива Buf влево на величину dl, как одного многоразрядного регистра
			s0=Buf[0];
			for ( x=0;  x < 8;  x++  ) {

				s1=Buf[x+1];
				// беззнаковый сдвиг двух 32 разрядных регистров s0 и s1 влево, как одного 64 разрядного
				y1=s1<<dl|s0>>dm;    // y0=s0<<dl;
				s0=s1;

				// на псевдографике левый сдвиг отображается смещением цифр влево
				// последнее слово заполнено нолями, кроме перенесеного из соседнего регистра хвоста
				// DM(END<<END<<" y1 "<<y1<<" y0 "<<y0<<END);
				binaryPrint(y1, 2);  DM(" "); // DM(END);

			} // x
*/

/*
//-----------------------------------
			// сдвиг всего массива вправо на величину dl, как одного многоразрядного регистра
			s0=Buf[7];
			for ( x=7;  x > 0 ;  x--  ) {  // ( x=7;  x > -1 ;  x--  )  (x=size-ds; x>ds; x--)

				s1=Buf[x-1];
				// беззнаковый сдвиг двух 32 разрядных регистров s0 и s1 вправо, как одного 64 разрядного
				y0=s0>>dl|s1<<dm;  // y1=s1>>dl;
				s0=s1;

				// на псевдографике правый сдвиг отображается смещением цифр вправо
				// начало последнего слова не корректно
				// DM(END<<END<<" y1 "<<y1<<" y0 "<<y0<<END);
				binaryPrint(y0, 2);  DM(" "); // DM(END);

		   } // x
//-----------------------------------
*/

//------------------------------------------------------------------------------

/*
			// сдвиг влево всего массива data_size_p32, как единого регистра
			// на величину dl, для прямого порядока пикселей
			unsigned int s2,s3,z0,z1,z2;   // s0,s1
			s0=bites_data_32[0];  // input
			//z0=bites_data_32[data_size_p32-1];
			for ( x=1;  x < data_size_p32-1;  x++ ) { // x=0;  // ncolumns*nrows/32;

				s1=bites_data_32[x+1];   //s2=bites_data_32[x];
				// беззнаковый сдвиг двух 32 разрядных регистров s0 и s1 влево,
				// как одного 64 разрядного регистра, для прямого порядока пикселей
///				bites_data_32[x]=s0>>dl|s1<<dm;          // y0=s0<<dl;   // ^ |
				bites_data_32[x]=s0&(s0>>dl|s1<<dm);     // z3=   // bites_data_32[x]=s2&(s0>>dl|s1<<dm);
				// добавление пикселей (пикселя) слева
				///s3=s2&s0;// bites_data_32[x]=s2&s0;  //s2|s0;   s2 |(s2^s0);  input[x+p] | (input[x+p] ^ input[x+p+d]);
				s0=s1;  // z1=s2=

				///z1=s1;  // z1=bites_data_32[x-1];
				// беззнаковый сдвиг двух 32 разрядных регистров s0 и s1 вправо,
				// как одного 64 разрядного регистра, для прямого порядока пикселей
////				bites_data_32[x]=s3&(z0<<dl|z1>>dm);    z0=z1;
				//z0=s1;

			} // x                     // уровни в битмапе  0-чёрный и 1-белый
*/

//------------------------------------------------------------------------------
/*
tmp-------
		//unsigned int s;
		for ( y=0;  y < nrows;  y++ ) {   //  (h-d)
				p=y*ncolumns_p32;
				for (x=0; x<ncolumns_p32; x++) {
					s=bites_data_32[x+p];
					//bites_data_32[x+p]=s | (s ^ bites_data_32[x+p+d]); //p1=x+p0;
					//p1=x+p+d; if( p1>data_size_p32 ) { p1=data_size_p32; }
					bites_data_32[x+p]=s & bites_data_32[x+p+d]; // p1  x+p+d
				} // x
		} // y
*/
/*
//------------------------------------------------------------------------------
tmp-------
		d=10;
		d=d*ncolumns/32;
		for ( y=0;  y < nrows;  y++ ) {   //  (h-d)
				p=y*ncolumns/32;
				for (x=0; x<ncolumns/32; x++) {
					//BufOff[y]=BufOff[y] | (BufOn[y+d] ^ BufOn[y]);
					s=input[x+p];    input[x+p]=s | (s ^ input[x+p+d]); //p1=x+p0;
					///input[x+p]=input[x+p] | (input[x+p] ^ input[x+p+d]);
					//input[y+p]=input[y+p+d];
				} // x
		} // y
//------------------------------------------------------------------------------
*/

//------------------------------------------------------------------------------

/*
 // Алгоритмические трюки для программистов стр47 сложение и вычитание двойных слов
			// тест  // s0=~0;
			///unsigned int s0=1+2+4+(1<<31)+(1<<30);  unsigned int s1=8+16+(1<<30); // +(1<<29)
			s0=~0-1-(1<<31);  s1=~0-1-(1<<31); // +(1<<29)

			DM(END<<END<<" s1 "<<s1<<" s0 "<<s0<<END);
			// РАСПАКОВКА на экран, представления одного целого числа int
			// вход значение input
			// int radix  - где radix = 2 для двоичного представления целого числа (binary number);
			// radix = 8 для восьмеричного... и т.д.
			binaryPrint(s1, 2);  DM(" ");  binaryPrint(s0, 2); DM(" ");
			binaryPrint(s1, 2);  DM(" ");  binaryPrint(s0, 2); DM(" ");
			DM(END); DM(END);

			dlt=2;      // int dlt сдвиг изображения влево, вправо, в верх, в низ.
			//if(!dlt||dlt==32) return;
			if(dlt<1 || dlt>31) return;
			unsigned int y0; unsigned int y1;
			int dm=32-dlt;
			unsigned int Buf[8+1];   memset(Buf,0,(8+1)*4);    // обнуление
			Buf[0]=s0;  Buf[1]=s1;
			Buf[2]=s0;  Buf[3]=s1;
			Buf[4]=s0;  Buf[5]=s1;
			Buf[6]=s0;  Buf[7]=s1;
*/

//------------------------------------------------------------------------------
				// ТЕСТЫ ДЛЯ ФУНКЦИИ УПАКОВКА  PACKING 32 //

/*
	bytes_data[0+ncolumns]=0;
	bytes_data[1+ncolumns]=bytes_data[2+ncolumns]=bytes_data[3+ncolumns]=0;
	bytes_data[4+ncolumns]=bytes_data[5+ncolumns]=bytes_data[6+ncolumns]=0;
	bytes_data[7+ncolumns]=0;       bytes_data[1+ncolumns]=1;

	bytes_data[8+2*ncolumns]=0;
	bytes_data[9+2*ncolumns]=bytes_data[10+2*ncolumns]=bytes_data[11+2*ncolumns]=0;
	bytes_data[12+2*ncolumns]=bytes_data[13+2*ncolumns]=bytes_data[14+2*ncolumns]=0;
	bytes_data[15+2*ncolumns]=0;    bytes_data[9+2*ncolumns]=1;
*/
/*
	int y0;
	y0=bites_data_32[0+ncolumns/8]; //y0=255;
	DM(END); DM(END);  binaryPrint(y0, 2);  DM(" ");  DM(END);
	y0=bites_data_32[1+2*ncolumns/8];
	DM(END); DM(END);  binaryPrint(y0, 2);  DM(" ");  DM(END);
*/

//------------------------------------------------------------------------------

				// ТЕСТЫ ДЛЯ ФУНКЦИИ РАСПАКОВКА UNPACKING 32 //

/*
		int v0=bytes_data[0+ncolumns];  int v1=bytes_data[1+ncolumns];
		int v2=bytes_data[2+ncolumns];  int v3=bytes_data[3+ncolumns];
		int v4=bytes_data[4+ncolumns];  int v5=bytes_data[5+ncolumns];
		int v6=bytes_data[6+ncolumns];  int v7=bytes_data[7+ncolumns];
 DM(END<<END<<"  0 "<<v0<<"  1 "<<v1<<"  2 "<<v2<<"  3 "<<v3<<"  4 "<<v4<<"  5 "<<v4
			<<"  6 "<<v6<<"  7 "<<v7<<END);

		v0=bytes_data[8+2*ncolumns];   v1=bytes_data[9+2*ncolumns];
		v2=bytes_data[10+2*ncolumns];  v3=bytes_data[11+2*ncolumns];
		v4=bytes_data[12+2*ncolumns];  v5=bytes_data[13+2*ncolumns];
		v6=bytes_data[14+2*ncolumns];  v7=bytes_data[15+2*ncolumns];
 DM(END<<END<<"  8 "<<v0<<"  9 "<<v1<<"  10 "<<v2<<"  11 "<<v3<<"  12 "<<v4<<"  13 "<<v4
		<<"  14 "<<v6<<"  15 "<<v7<<END);
*/

//******************************************************************************

//-----------------------------------*******************************************
/*                   // почти работающея версия
//	binaryPrint(254, 2);  DM(" "); DM(END);
	unsigned int bytes_data_p32=data_size/32;
	unsigned int bytes_data_p4=data_size/4;
	unsigned int Mask=~(1 + (1<<8) + (1<<16) + (1<<24)); // 16843009  ~4278124286
	Mask=4278124286;
	binaryPrint(Mask, 2);  DM(" "); DM(END);
//	Sb=16843009+(16843009>>2);
//	binaryPrint(Sb, 2);  DM(" "); DM(END);
//	Sb&=Mask;
//	binaryPrint(Sb, 2);  DM(" "); DM(END);

	  for ( x=8; x < bytes_data_p4-8; x++ ) { //s<5 && x<data_size_p_3;   data_size_p32
			Sb=bytes_data_32[x];
////Sb=16843009+(16843009>>2)+(1<<11);
///Sb=bytes_data_32[bytes_data_p4/2+32];
///binaryPrint(Sb, 2);  DM(" "); DM(END);
///DM(" Mask "<<Mask<<" Sb "<<Sb<<END);
			Sb=~(Sb | (~Mask));  // Sb=~Sb & Mask;
///binaryPrint(Sb, 2);  DM(" "); DM(END);
///DM(" Mask "<<Mask<<" Sb "<<Sb<<END);
			// Сумма единиц в регистре Sb    //0xFFFFFFFF
			Sb-=(Sb >> 1) & 0x55555555;                // 2-битовые ячейки
			Sb=(Sb & 0x33333333) + ((Sb >> 2) & 0x33333333); // 4-битовые
			Sb=(Sb + (Sb >> 4)) & 0x0F0F0F0F;                // 8-битоовые
			Sb+=Sb >> 8;                               // 16-битовые
			Sb+=Sb >> 16;                              // 32-битовая ячейка
			//NMask+=Sb & 0x3F;  // 31 Обнуляем старшие разряды, содержащие "мусор"
			Sb=Sb & 0x3F;  // 31 Обнуляем старшие разряды, содержащие "мусор"
			if( Sb>4 ) { break; } //  s>0;
	   } // x    // 255 белый   //  Sb=0; tiff


DM(" Mask "<<Mask<<" Sb "<<Sb<<END);
*/

//------------

/*
		 // работающея версия
		 // бинаризация входного массива битмап (изменино 20 октября 2010)
		 int data_size_3=data_size-3;
		 if(s>0 && invert==0) {
			 for ( x=0; x < data_size_3; x+=4 ) {  // x=0; x < data_size; x++
			 ///for ( x=0; x < data_size; x++ ) {
				///if (bytes_data[x]>127){bytes_data[x]=1;}  else {bytes_data[x]=0;}
				// деление на 128 с присваиванием
				bytes_data[x]>>=7;    bytes_data[x+1]>>=7;
				bytes_data[x+2]>>=7;  bytes_data[x+3]>>=7;
			 } // x
		 } // if   // уровни в битмапе 0 и 255, уровни в битовом массиве 1 и 0   // 255 белый
*/

//------------

/*
	  // работающея версия но не быстрее обычной  (изменино 20 октября 2010)

	// приведенный к unsigned int исходный распакованный массив черно-белого скана
	unsigned int* bytes_data_32=(unsigned int*)bytes_data;

	unsigned int bytes_data_p32=data_size/32;
	unsigned int bytes_data_p4=data_size/4;

	  for ( x=8; x < bytes_data_p4-8; x++ ) { //s<5 && x<data_size_p_3;   data_size_p32
////Sb=16843009+(16843009>>2)+(1<<11);
///Sb=s0=bytes_data_32[bytes_data_p4/2+32];
		   s0=s=bytes_data_32[x];
		   // Sb сумма 4х бит 32х разрядного слова
					  Sb =s0 & 255;
			s0=s>>8;  Sb+=s0 & 255;
			s0=s>>8;  Sb+=s0 & 255;
			s0=s>>8;  Sb+=s0 & 255;

///binaryPrint(s0, 2);  DM(" "); DM(END);        DM(" s0 "<<s0<<END);
///binaryPrint(Sb, 2);  DM(" "); DM(END);        DM(" Sb "<<Sb<<END);
			if( Sb>49999 ) { break; } //  s>0;
	   } // x    // 255 белый   //  Sb=0; tiff

DM(" Sb "<<Sb<<END);

//DM(" Mask "<<Mask<<" Sb "<<Sb<<END);
*/

//------------

/*
	   // работающея версия   (изменино 30 октября 2010)

		 // Автоопределение количества градаций в битмапе
		 // (изменино 20 октября 2010, в 3,0 раза быстрее классической).
		 // Если в массиве встречается серое (или чб) больше едиици, то немедленно
		 // выходим из цикла и далее выполняем бинаризацию битмапа.
		 int data_size_8=data_size-8;
		 for ( x=8; x < data_size_8; x+=4 ) { //s<5 && x<data_size_p_3;
			s=bytes_data[x]+ bytes_data[x+1]+ bytes_data[x+2]+ bytes_data[x+3];
			if( s>4 ) { break; } //  s=4;
		 } // x

//		 DM(END<<" x "<<x<<" s "<<s<<" data_size_8 "<<data_size_8<<END);


		 // бинаризация входного массива битмап (изменино 20 октября 2010)
		 int data_size_3=data_size-3;
		 if(s>4){ // max>1
			 for ( x=0; x < data_size_3; x+=4 ) {  // x=0; x < data_size; x++
			 ///for ( x=0; x < data_size; x++ ) {
				///if (bytes_data[x]>127){bytes_data[x]=1;}  else {bytes_data[x]=0;}
				// деление на 128 с присваиванием
				bytes_data[x]>>=7;    bytes_data[x+1]>>=7;
				bytes_data[x+2]>>=7;  bytes_data[x+3]>>=7;
			 } // x
		 }     // уровни в битмапе 0 и 255, уровни в битовом массиве 1 и 0
*/
//------------

//------------------------------------------------------------------------------
/*
		 // работающея версия    (изменино 31 октября 2010)

		 //автоопределение количества градаций в битмапе.
		 // Если в массиве встречается серое (или чб) больше едиици (1+1+1+1=4),
		 // то немедленно выходим из цикла и далее выполняем бинаризацию битмапа.
		 int data_size_32=data_size-32;   s=0;
		 for ( x=32; s<5 && x < data_size_32; x+=4 ) { // эквивалентно if(s>4) {break;}
			s=bytes_data[x]+ bytes_data[x+1]+ bytes_data[x+2]+ bytes_data[x+3];
		 } // x  // в бинаризации д.б. s>4
//*/
/*
		 //invert=1;
		 unsigned int inv;
		 if(invert<1) { inv=0;} //  invert=0;  без инверсия (обычно белый фон)
		 if(invert>0) { inv=1;} //  invert=1;  инверсия (обычно черный фон)

		 // бинаризация входного массива битмап с управляемой инверсией
		 b_data=data_size-3;
		 if(s>0) { // s>0 // s>4
			 for ( x=0; x < b_data; x+=4 ) {
				// деление на 128 с управляемой инверсией
				bytes_data[x]  =(bytes_data[x]>>7)   - inv;
				bytes_data[x+1]=(bytes_data[x+1]>>7) - inv;
				bytes_data[x+2]=(bytes_data[x+2]>>7) - inv;
				bytes_data[x+3]=(bytes_data[x+3]>>7) - inv;
			 } // x
		 } // if   Выходной битмап:   0-черный    1-белый
//*/
/**/
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
/**/
/*
// СДВИГ ВНИЗ всего массива bites_data_32, как единого регистра на d0 строк

	// Добавление пикселей с нижней стороны символа.
	if(gRateLower>0 && m<dltLower) { // количество добавленных однопиксельных слоёв с нижней стороны символа
		for ( x=data_size_p32;  x > d0;  x-- ) {
			bites_data_32[x]=bites_data_32[x] & bites_data_32[x-d0];
		} // x
	} // if

	// Убавление пикселей с нижней стороны символа.
	if(gRateLower<0 && m<dltLower) { // количество убавленных однопиксельных слоёв с нижней стороны символа
		for ( x=data_size_p32;  x > d0;  x-- ) {   // d0
			bites_data_32[x]=bites_data_32[x] | bites_data_32[x-d0];
		} // x
	} // if


} // m
*/
//------------------------------------------------------------------------------

/**/
//-----------------------------------*******************************************
