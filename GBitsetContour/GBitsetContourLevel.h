void
GBitsetContour::init(const GBitmap *ref, short stepW, short stepH, short flipV)
{
	  srcW=ref->columns()+4;
	  srcH=ref->rows()+4;
	  if(stepH<1)stepH=1;
      if(stepW<1)stepW=1;

	  nrows=ref->rows()/stepH;
	  ncolumns=ref->columns()/stepW;
	  init(ncolumns,nrows);
	  unsigned char *row=bytes_data;
      unsigned char *p;
      short h=nrows;
	  short w=ncolumns;
	  textLineSize=0;

#ifdef DEBUGLVL
      drawData=GBitmap::create(ncolumns,nrows);
#endif
	
	  line=GBitmap::create(w,h);
	  line->fill(0);

if(flipV){
	for (int n=2; n<nrows-2; n++){
		for(int m=2; m<ncolumns-2;m++){
			p=row+n*ncolumns+m;
			if(ref[0][h-n*stepH+2][m*stepW-2]<125){*p=1; //DP(1);
			}else{*p=0;  //DP(0);
			}
#ifdef DEBUGLVL
			drawData[0][n][m]=255+*p*120;
#endif
			line[0][h-n][m]=(short)*p;
						//DC((short)*p);

		}
		//DC(END)
	}
}else{
	for (int n=2; n<nrows-2; n++){
		for(int m=2; m<ncolumns-2;m++){
			p=row+n*ncolumns+m;
			if(ref[0][n*stepH+2][m*stepW-2]<125){*p=1; ;
			}else{*p=0;
			}
#ifdef DEBUGLVL
			drawData[0][n][m]=255+*p*120;
#endif
			line[0][n][m]=(short)*p;

		}
		//_//_DC(END);
		}

}
////////////////////////////////////////////////////////////////////////////////

}//__________________________________________

