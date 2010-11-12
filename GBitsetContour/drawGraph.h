/////*this file draw Letter recognition graph in mainOCR window

-(void)drawGraph:(unsigned char *)graphData_{
//graph /////////////////////*0
short x,y;
	short angLength=angDiff.size();

m=0;    for ( x = 10; x <angLength+10 ; x++ ) {//std::cout<<"ang[i]="<<ang[m]<<"\n";
            if(angDiff[m]<0){
			for ( y =40-angDiff[m]*10;y>=40; y-- ) {
			i=y * 200+ x;
			p1 = graphData_ + i;
			*p1=(char)rint(255);
	    }}else{
			for ( y =40; y >=40-angDiff[m]*10; y-- ) {
			i=y * 200+ x;
			p1 = graphData_ + i;
				*p1=(char)rint(255);
			}}	   
	    m++;}m=0;//end for x
	   
	    for ( x = 10; x <angLength + 10; x++ ) {
//if(angDiff[m]>=0){
	    for ( y =150; y >150-angInt[m]*10; y-- ) {
	    i=y * 200+ x;
	    p1 = graphData_ + i;
            *p1=(char)rint(255);
	    }
//}else{
	    for ( y =151; y <151-angInt[m]*10; y++ ) {
	    i=y * 200+ x;
	    p1 = graphData_ + i;
            *p1=(char)rint(255);
	    }//}
m++;}

 for ( x = 10; x <angLength + 10; x++ ) {
 
   y=70;
 i=y * 200+ x;
 p1 = graphData_ + i;
*p1=(char)rint(70);
    y=80;
 i=y * 200+ x;
 p1 = graphData_ + i;
*p1=(char)rint(70);
  y=90;
 i=y * 200+ x;
 p1 = graphData_ + i;
*p1=(char)rint(70);
   y=100;
 i=y * 200+ x;
 p1 = graphData_ + i;
*p1=(char)rint(70);
 
 y=110;
 i=y * 200+ x;
 p1 = graphData_ + i;
*p1=(char)rint(70);
   
y=120;
 i=y * 200+ x;
 p1 = graphData_ + i;
*p1=(char)rint(70);

  y=130;
 i=y * 200+ x;
 p1 = graphData_ + i;
*p1=(char)rint(70);

 y=140;
 i=y * 200+ x;
 p1 = graphData_ + i;
*p1=(char)rint(70);

 y=150;
 i=y * 200+ x;
 p1 = graphData_ + i;
*p1=(char)rint(70);
y=160;
 i=y * 200+ x;
 p1 = graphData_ + i;
*p1=(char)rint(70);
y=170;
 i=y * 200+ x;
 p1 = graphData_ + i;
*p1=(char)rint(70);
y=180;
 i=y * 200+ x;
 p1 = graphData_ + i;
*p1=(char)rint(70);
}

}//end method///////////////////////////////////////*
///////////////////////*readVSum//////////////////////////////*////////
-(void)readVSum{
short x,y;
//for (t=0;t<=m;t++){ tt=0;dlt_y=0; ////printf("ln_v=%d\n",ln[t]);
//y_line=ln[t];
ln=new short[w];
lt=new short[w];
for ( x = 0; x < w ; x++ ) {
for ( y =0; y < hL; y++ ) {
	    i=y * w + x;
	   //p1 = srcData + i;
            res=res+255-*p1;
	    }
    res=res/100;
    ln[x]=res;
   ////printf("res_v=%d\n",res);}
    res=0;}

//for ( x = 0; x < 10; x++ ){ln[x]=0;}
//for ( x = w-10; x < w; x++ ){ln[x]=0;}
//for ( x = 10; x < w-10; x++ ) {  //read image make sum
//lt[x]=(ln[x-10]+ln[x-9]+ln[x-8]+ln[x-7]+ln[x-6]+ln[x-5]+ln[x-4]+ln[x-3]+ln[x-2]+ln[x-1]
//+ln[x]+ln[x+1]+ln[x+2]+ln[x+3]+ln[x+4]+ln[x+5]+ln[x+6]+ln[x+7]+ln[x+8]+ln[x+9]+ln[x+10])/21;}

 for ( x =0; x <w ; x++ ) {
 ////printf("res_v=%d\n",ln[x]);
 for ( y =hL; y >hL-ln[x] ; y-- ) {
            //p2 = srcData + y * w + x;
            *p2 = (char)rint(*p2/2);
			}}
}//end method

////////////////////////////////////////////////////////*
