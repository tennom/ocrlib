void
GBitsetMatrix::init(const GBitmap *ref, short stepW, short stepH, short flipV)
{
	  border=64;
	  srcW=ref->columns()+ border*2;
	  srcH=ref->rows()+ border*2;
	  if(stepH<1)stepH=1;
	  if(stepW<1)stepW=1;
	  nrows=ref->rows()/stepH;
	  ncolumns=ref->columns()/stepW;
	  init(nrows,ncolumns, border);
	  bool *row=bits_data;
	  bool *p,*p1;
	  int dH,dW;
	  int h=ref->rows();

#ifdef DEBUGLVL_GREY
	  drawData=GBitmap::create(ncolumns,nrows);
#endif
#ifdef DEBUGLVL_RGB		
	  drawDataRGB=GBitmapInt::create(nrows,ncolumns,0);
#endif
	  //line=GBitmap::create(w,h);
	  //BitVec=new bitset<nrows*ncolumns>;

if(flipV){

	for (int n=border; n<nrows-border; n++){
		p1=row+n*ncolumns;  dH=h-(n-border)*stepH;
		for(int m=border; m<ncolumns-border;m++){
			p=p1+m;   dW=(m-border)*stepW;
			if(ref[0][dH][dW]<125){*p=1;

#ifdef DEBUGLVL_GREY
			  drawData[0][n][m]=0;       //DM(1);
#endif
#ifdef DEBUGLVL_RGB					
			  drawDataRGB[0][n][m]=0;   //DM(drawDataRGB[0][n][m]);  // 0-черное, 255-белое
#endif
			}
			else{*p=0;
#ifdef DEBUGLVL_GREY
			  drawData[0][n][m]=255;     //DM(0);
#endif
#ifdef DEBUGLVL_RGB					
			  drawDataRGB[0][n][m]=255; //DM(drawDataRGB[0][n][m]);  // 0-черное, 255-белое
#endif
			}
#ifdef DEBUGLVL_GREY
			//drawData[0][n][m]=255+*p*120;
			///drawData[0][n][m]*=1-*p;
#endif
		}
	 //DM(END);
	 }

/*
//	    -- draw picture in text graphic ---
	   bool *d1;
	   for (int y=0; y < nrows; y+=4 ) {
		  for(int x=0;x<ncolumns;x+=32){
		  d1=bits_data+y*ncolumns+x;
		  if(*d1){DM(1);}else{DM(0);
		  }
	   }DM(END);
	   }DM(" NEW"<<END<<END<<END);
*/

}else{
	for (int n=border; n<nrows-border; n++){
		p1=row+n*ncolumns; dH=(n-border)*stepH;
		for(int m=border; m<ncolumns-border;m++){
			p=p1+m;  dW=(m-border)*stepW;
			if(ref[0][dH][dW]<125){*p=1;

#ifdef DEBUGLVL_RGB
			  //drawData[0][n][m]=0;
			  drawDataRGB[0][n][m]=0;
#endif
			}else{*p=0;
#ifdef DEBUGLVL_GREY
			  //drawData[0][n][m]=255;
			  drawData[0][n][m]=255;
#endif
			}
#ifdef DEBUGLVL_GREY
			//drawData[0][n][m]=255+*p*120;
			//line[0][n][m]=(short)*p;
#endif
		}
		//_//_DM(END);
	 }

}

			  // переупаковка сдвигом массива горизонтальных строк
			  unsigned int nbits=nrows*ncolumns;
			  unsigned int reg=0;           // обратный порядок пикселей
			  for (unsigned int x=0; x < nbits; x++ ) { srcInt[x]=reg=(reg << 1)+ bits_data[x]; }
			  //бордюр в 32 пиксела с краев каждого ряда содержит мусор
			  //for ( x=0; x < ncVnr; x++ ) { SInt[x]=reg=(reg >> 1) + ((BolS[x])<<31); } // прямой порядок пикселей
			  // <<31 умножение на 2 в 31 степени, >> 1 деление на 2

			  // переупаковка (транспонирование) всего  горизонтального
			  // массива строк StrM (int) в массив вертикальные строк SInt (int)
			  unsigned int index=0;
			  for (int  x=0; x < ncolumns; x++ ) {
				for (int y=0; y < nbits; y+=ncolumns){
					sInt[index]=srcInt[x+y];
					//if(sInt[index]>0){drawDataRGB[0].int_data[x+y]=drawDataRGB[0].int_data[x+y]<<8;}
					index++;
				} // y
			  } // x

  // Временный массив для тестирования быстродействия (bool*)farcalloc(nbits+512,1)


}//__________________________________________

void GBitsetMatrix::init(const GBitmap *ref,
					short x,
					short y,
					short w,
					short h,
					short stepW,
					short stepH,
					short flipV){
	
	  border=128;
	  if(stepH<1)stepH=1;
	  if(stepW<1)stepW=1;
	    //normalisation 
	
	    //cout<<"x="<<x<<" y="<<y<<" w="<<w<<" h="<<h<<" ref->columns()="<<ref->columns()<<" ref->rows()="<<ref->rows()<<" border="<<border<<endl;
	
	    if(!w||!h)return;
	    if(x<0)x=0;
	    if(w>ref->columns())w=ref->columns();
		if(x+w>ref->columns()){
			x=ref->columns()-w;
		}
	    if(y<0)y=0;
		if(h>ref->rows())h=ref->rows();
		if(y+h>=ref->rows()-10){
			y-=10;
		}
	//cout<<" new w="<<w<<" h="<<h<<" y="<<y<<endl;

	
	  nrows=h/stepH;
	  ncolumns=w/stepW;
	  init(nrows,ncolumns,border);
	  bool *row=bits_data;
	  bool *p,*p1;
	  int dH,dW;
	  int refH=ref->rows();
	
#ifdef DEBUGLVL_GREY
	drawData=GBitmap::create(ncolumns,nrows);
#endif
#ifdef DEBUGLVL_RGB
	drawDataRGB=GBitmapInt::create(nrows,ncolumns,0);
#endif
	
if(flipV){

	for (int n=border; n<nrows-border; n++){
		p1=row+n*ncolumns;  dH=refH-y-(n-border)*stepH;
		for(int m=border; m<ncolumns-border;m++){
			p=p1+m;   dW=(m-border)*stepW+x;
			if(ref[0][dH][dW]<125){*p=1;

#ifdef DEBUGLVL_GREY
			  drawData[0][n][m]=0;       //DM(1);
#endif
#ifdef DEBUGLVL_RGB				
			  drawDataRGB[0][n][m]=0;   //DM(drawDataRGB[0][n][m]);  // 0-черное, 255-белое
#endif
			}
			else{*p=0;
#ifdef DEBUGLVL_GREY
			  drawData[0][n][m]=255;     //DM(0);
#endif
#ifdef DEBUGLVL_RGB							
			  drawDataRGB[0][n][m]=255; //DM(drawDataRGB[0][n][m]);  // 0-черное, 255-белое
#endif
			}
#ifdef DEBUGLVL_GREY
			//drawData[0][n][m]=255+*p*120;
			///drawData[0][n][m]*=1-*p;
#endif
		}
	 //DM(END);
	 }

/*
//	    -- draw picture in text graphic ---
	   bool *d1;
	   for (int y=0; y < nrows; y+=4 ) {
		  for(int x=0;x<ncolumns;x+=32){
		  d1=bits_data+y*ncolumns+x;
		  if(*d1){DM(1);}else{DM(0);
		  }
	   }DM(END);
	   }DM(" NEW"<<END<<END<<END);
*/

}else{
	for (int n=border; n<nrows-border; n++){
		p1=row+n*ncolumns; dH=(n-border)*stepH+y;
		for(int m=border; m<ncolumns-border;m++){
			p=p1+m;  dW=(m-border)*stepW+x;
			if(ref[0][dH][dW]<125){*p=1;

#ifdef DEBUGLVL_GREY
			  drawData[0][n][m]=0;
#endif
#ifdef DEBUGLVL_RGB					
			  drawDataRGB[0][n][m]=0;
#endif
			}else{*p=0;
#ifdef DEBUGLVL_GREY
			  drawData[0][n][m]=255;
#endif
#ifdef DEBUGLVL_RGB					
			  drawDataRGB[0][n][m]=255;
#endif
			}
#ifdef DEBUGLVL_GREY
			//drawData[0][n][m]=255+*p*120;
			//line[0][n][m]=(short)*p;
#endif
		}
		//_//_DM(END);
	 }

}

			  // переупаковка сдвигом массива горизонтальных строк
			  unsigned int nbits=nrows*ncolumns;
			  unsigned int reg=0;           // обратный порядок пикселей
			  for (unsigned int x=0; x < nbits; x++ ) { srcInt[x]=reg=(reg << 1)+ bits_data[x]; }
			  //бордюр в 32 пиксела с краев каждого ряда содержит мусор
			  //for ( x=0; x < ncVnr; x++ ) { SInt[x]=reg=(reg >> 1) + ((BolS[x])<<31); } // прямой порядок пикселей
			  // <<31 умножение на 2 в 31 степени, >> 1 деление на 2

			  // переупаковка (транспонирование) всего  горизонтального
			  // массива строк srcInt (int) в массив вертикальные строк sInt (int)
			  unsigned int index=0;
			  for (int  x=0; x < ncolumns; x++ ) {
				for (int y=0; y < nbits; y+=ncolumns){
					sInt[index]=srcInt[x+y];
					//if(sInt[index]>0){drawDataRGB[0].int_data[x+y]=drawDataRGB[0].int_data[x+y]<<8;}
					index++;
				} // y
			  } // x
	//cout<<"done border="<<border<<endl;

}//__________________________________________


