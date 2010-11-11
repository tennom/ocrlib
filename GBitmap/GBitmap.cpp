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
  nrows = arows;
  ncolumns = acolumns;
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
		int x,y;
		
		for (y = 0; y < h;y++){
			for (x = 0; x < ncolumns; x++){
				p=bytes_data+y*ncolumns+x;
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


	           for(y = 0; y < new_h; y++) { //cout<<y<<" ";
				  yp=((y<<8)/scaleP)*w;                         // *256
				  p=y*new_w;
				  for(x = 0; x < new_w; x++) {                  //p=y*new_w + x;
					//new_p=( ((int)(y/scale)*w) + ((int)(x/scale)) ); // medlenno
					new_p=(x<<8)/scaleP + yp;
					//  разный масштаб по разным координатам
					/// new_p=( ((int)(y/scale_h)*w) + ((int)(x/scale_w)) );
					  if(new_p>=w*h){continue;} 
					if(p + x>=new_h*new_w){continue;} 
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
			unsigned int index_=0, dlt=1;
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
		
		double SinA=sin(ang);       // float, ипи double
		double CosA=cos(ang);
		
		//x0 = (160.0 + scale*(-160.0*CosA+100.0*1.2*SinA))*65536.0;
		//y0 = (100.0 + scale*(-100.0*CosA-160.0*SinA/1.2))*65536.0;
		
		x0 = (w_2 + SCALE(-w_2*CosA+h_2*SinA))*k;
		y0 = (h_2 + SCALE(-h_2*CosA-w_2*SinA))*k;
		
		xdx = SCALE(CosA*k);     //xdx = scale*CosA*65536.0;
		xdy = SCALE(SinA*k);     //xdy = scale*SinA*65536.0/1.2;
		
		ydx =-SCALE(SinA*k);     //ydx =-scale*SinA*65536.0*1.2;
		ydy = SCALE(CosA*k);     //ydy = scale*CosA*65536.0;
		
		
		for (y=0; y<h; y++) {
			
			x1 = x0;    y1 = y0;
			
			d0 = y*w;
			for (x=0; x<w; x++) {
				
				xp = x1 >> 16;  yp = y1 >> 16;   // /65536
				
				d1 = yp*w;
				if ( xp>=0 && xp<=w_1 && yp>=0 && yp<=h_1 ) {
					// dest[0][y][x] = src[0][yp][xp];
					*(p0 + x + d0) = *(p1 + xp + d1);
				}
				// { dest[0][y][x] = 255; }
				else { *(p0 + x + d0) = 255; }
				
				x1+=xdx;   y1+=xdy;
			} // x
			x0+=ydx;   y0+=ydy;
		} // y
		
		cout<<"rotation="<<rotation<<END;
		
		TIME_PRINT
		
		// http://www.enlight.ru/demo/faq/smth.phtml?query=alg_bitmap_rotate
		// "DEMO.DESIGN FAQ, http://www.enlight.ru/demo/faq".
		// Вpащение pастpовой каpтинки
		// http://algolist.manual.ru/graphics/rotate.php
		
	}//_____________________________________________________________________________
	
	
// Fills a bitmap with the given value
void  GBitmap::fill(unsigned char value){
		
		memset (bytes_data, value, data_size);
//  for(unsigned int y=0; y<rows(); y++)
//	{
//	  unsigned char* bm_y = (*this)[y];
//	  for(unsigned int x=0; x<columns(); x++)
//		bm_y[x] = value;
//	}
}//_________________________________________________________________________

void GBitmap::drawImg(GBitmap *img,int x0,int y0){
	int w=img->columns();
	int h=img->rows();
	//cout<<"x0="<<x0<<" y0="<<y0<<" w="<<w<<" h="<<h<<" ncolumns="<<ncolumns<<" nrows="<<nrows<<endl;
	if(w>ncolumns)w=ncolumns;
	if(h>nrows)h=nrows;
	
	if(x0+w>ncolumns)x0=0;
	if(y0+h>nrows)y0=0;
	
	unsigned char *p;

	int x,y;
			for (y = 0; y < h;y++){
			  for (x = 0; x < w; x++){
						p=bytes_data+(y0+y)*ncolumns+x0+x;
						*p=img[0][y][x];
			  }
			}
	//cout<<"draw done";
}//___________________________________________________________________________

	
void GBitmap::printToScreen(){
	int w=ncolumns;
	int h=nrows;
	
	unsigned char *p;
	
	int x,y;
	for (y = 0; y < h;y++){
		for (x = 0; x < w; x++){
			p=bytes_data+y*ncolumns+x;
			printf("%02x", *p);
			//if(*p>0){cout<<"1";}else{cout<<".";}
		}cout<<END;
	}

}//____________________________________________________________________________

void GBitmap::invert(){
		int w=ncolumns;
		int h=nrows;
		
		unsigned char *p;
		
		int x,y;
		for (y = 0; y < h;y++){
			for (x = 0; x < w; x++){
				p=bytes_data+y*ncolumns+x;
				*p=255-*p;
				//if(*p>0){cout<<"1";}else{cout<<".";}
			}//cout<<END;
		}
		
}//____________________________________________________________________________
	

void GBitmap::rotate(int count){


}
	
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
				
				if ( y==0 )              //   d0=(input + index);
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

			  // запакован, каждый бит всех байтов маленького (char) массива заполнен битами
			  pack_flag=1;

}//_____________________________________________________________________________

// Распаковка маленького битового массива в большй битмап.
// Используется для увеличения скорости доступа при обработке картинок букв.
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

}	

	
	
	
}

// -----------------------------------------------------------------------------

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
