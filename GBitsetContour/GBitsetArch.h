void GBitsetContour::readHSum(vector<int> &H){
 int y,x,d;
 short res=0;
          for ( y=0; y < nrows; y++ ) {  //read image make sum
            res=0;    d=y*ncolumns; //
            for ( x=0; x < ncolumns; x++ ) {
               res+=bits_data[d + x];
            }
            H[y]=res;
          }

 }//___________________________________________________________________________

  void GBitsetContour::findMaxMin(vector<int> &In){
  int y,b,x;
  short dy_line;
  dl[0]=0; //max value of horisontal summ
  dl[1]=0; //index max allement in summ array
  dl[2]=1; //value of nearest min value in summ array
  dl[3]=0; //index min
  int size=nrows;
  int Varu;
  for(y=0;y<size;y++){ //find max
    if(y<=size/2){Varu=y;} else {Varu=(size-y);}
    In[y]=In[y]*4*Varu/size*Varu/size;//временная регилировка усиления (вдоль y)
    if(In[y]>dl[0]){dl[0]=In[y];dl[1]=y;}
  }   //find max value of array

   #ifdef DEBUGLVL
              for(y=0; y < drawData->rows(); y++) {
                if(In[y]>=0){
                  for(x =600; x < In[y]+600; x++ )drawData[0][y][x]*=0.3;
                 }else{
                  for(x =600; x > In[y]+600; x-- )drawData[0][y][x]*=0.3;
                 }
              }

   #endif


  int c=0;
 // for(y=dl[1];y>0;y--){ //find min
 // if(lt[y]<dl[0]/1.5){dl[2]=lt[y];dl[3]=y;break;}
 // }   //find max value of array

  dy_line= ncolumns*deltaH;  //delta y around 10 degree
  dl[3]= dl[1]-dy_line;  if(dl[3]<0)dl[3]=0;
  dl[1]+=dy_line;        if(dl[1]>nrows)dl[1]=nrows;



      for(int x=0;x<ncolumns;x++){
      drawData[0][dl[1]][x]*=0;
      drawData[0][dl[1]+1][x]*=0;
      drawData[0][dl[3]][x]*=0;
      drawData[0][dl[1]+1][x]*=0;
    }

    DC("dl[1]="<<dl[1]<<" dl[3]="<<dl[3]<<" dy_line"<<dy_line<<END);

   //short indMaxHValue=dl[1]; //index max allement in summ array
  //dl[2]; //value of nearest min value in summ array
   //short indMinHValue=dl[3]; //index min


/*  for(int x=0;x<ncolumns;x++){
     for(int y=dl[1];y<dl[3];y++){
      drawData[0][y][x]*=0.9;
  }}

    for(int x=0;x<ncolumns;x++){
     for(int y=dl[3];y<dl[1];y++){
      drawData[0][y][x]*=0.9;
  }}
 */



  //dlt=ncolumns/dy;  //delta x
  }//___________________________________________________________________________

  void GBitsetContour::roundSum(){
 /* this method read horisontal sum of bool pixel of image from different angle.
  angle is siht of y on 1 pixel every dlt pix on x.
  this method has two calibrate. One is more fast and second more accurate.
  */
  int x,y,i;
  short up_limit,down_limit,count,step,tt,max_down,dlt_y,dy_line,indexHSumArray,res,indexMaxValue;
  GTArray<short> maxHSum; maxHSum.resize(nrows);
  GTArray<short> maxHSumDeltaY; maxHSumDeltaY.resize(nrows);
  //maxHValue=dl[0]; //max value of horisontal summ
  short indMaxHValue=dl[1]; //index max allement in summ array
  //dl[2]; //value of nearest min value in summ array
  short indMinHValue=dl[3]; //index min
  //short l_res[h];
  for (count=0;count<2;count++){  //start calibrate first and second pass


          tt=0;dlt=ncolumns;max_down=0;dlt_y=0;
          if(count==0){step=(indMaxHValue-indMinHValue)/10+1;
          dy_line=(indMaxHValue-indMinHValue);
          }else{step=1;}  // step is choose depend of max value of signal and pass of calibration

  if(count==0){/////////////////value of first pass of calibration //////////////////////////////**
               down_limit=dy=(indMaxHValue-indMinHValue+1)*(-1);up_limit=indMaxHValue-indMinHValue;
          //cout<<"start first calibrate //////dy start="<<ln_h<<endl<<"down_limit="<<dy<<endl<<"up_limit="<<up_limit<<endl;
          // up_limit and dy is limit of calibratioin on y it choose depend of pass and step
  }else{/////////////////value of second pass of calibration //////////////////////////////*
               ln_h=dy; down_limit=dy-dy_line/20-1;up_limit=dy+dy_line/10+1;  //on second pass we choose more narrow limit
               //cout<<"start second calibrate. count="<<count<<" down_limit="<<down_limit<<"  up_limit="<<up_limit<<
               //"//////**dy first=//////**"<<ln_h<<endl;
                        }
                                        //printf("step=%d\n",step);
               indexHSumArray=0;   ////printf("maxUpBit=%d\n",maxUpBit);
  for (dy=down_limit;dy<=up_limit;dy=dy+step+1){ // for every value of delta y in limits //cout<<"dy="<<dy<<endl;
          for ( y=indMinHValue; y <= indMaxHValue; y+=step+1) { ////printf("y=%d\n",y); //here we must make calibration for different y in stroke hight
          if(dy==0){dlt=ncolumns;}else{dlt=abs(ncolumns/dy);}  if(dy>0){direction=-1;}else{direction=1;}
          res=0; dlt_y=0; tt=0;
                                  for ( x=0; x < ncolumns; x++ ) {
                                                  if(tt==dlt){dlt_y++; tt=0; ////printf("_x=%d _y=%d\n", x,y);
                                                  }else{tt++;}
                                                  //i=(y+dlt_y*direction) * w + x;
                                                  #ifdef DEBUGLVL
                                                  drawData[0][y+direction*dlt_y+dy/2][x]*=0.9;
                                                  #endif
                                                  i=(y+direction*dlt_y+dy/2)*ncolumns + x;
                                                  if(i<maxBitAdress&&i>0){
                                                  res+=bits_data[i];
                                                  }
                                  } // end for x (bit)
                                  ////printf("calibrate res=%d y=%d dy=%d\n ", res,y,dy);

                                  dlt_y=0; tt=0;
                  if(res>max_down) max_down=res;  // we put max value of sum for all y

                            ///////////draw it
                            //if (count==0)draw_y(y,90);
                           // for(y=0; y < nrows; y++){ for(x =0; x < ln[y]+10; x++ ){drawData[0][y][x]*=0.3;}}

          }//end for(y=indMinHValue; y <= indMaxHValue;
                  maxHSum[indexHSumArray]=max_down;  //put max value of sum in array
          //@//printf("max_down_res=%d  count=%d  //////*dy=%d\n" , max_down,count,dy);
                  maxHSumDeltaY[indexHSumArray]=dy; // put dy for max value of sum  in array
                  indexHSumArray++;tt=0;max_down=0;////printf("dy=%d up_limit=%d\n",dy,up_limit);
  }  // end for (dy=down_limit;
              indexMaxValue=0;
              for ( y=0; y < indexHSumArray ; y++ ) {if(maxHSum[y]>max_down){max_down=maxHSum[y];indexMaxValue=y;}
              tt++;
              }  //seek max value of sum all first calibrate
             //if (count==1){
              //for ( y=0; y <m ; y++ ){if(l_down[y]==max_down){dl[1]=y; break;}} //@//printf("/////////*calibration result UP=%d _n=%d\n", max_down,y); //in case we has two or more max_down find first from beginning
              //for ( y=m; y >0 ; y-- ){if(l_down[y]==max_down){dl[3]=y; break;}}  //@//printf("/////////*calibration result DOWN=%d _n=%d\n", max_down,y);//in case we has two or more max_down find first from end
              //n=dl[1]+(dl[3]-dl[1])/2; }
              dy=maxHSumDeltaY[indexMaxValue];
              tt=0;dlt_y=0;  //@//printf("/////////*calibration result=%d _n=%d\n", dy,n);

  }//end for (calibrate)


                          //printf("result of the calibration /////////l_up(dy)=%d \n_n=%d\n", dy,n);

                          if(dy==0){dlt=ncolumns;}else{dlt=abs(ncolumns/dy);}
                          if(dy>0){baseDirection=-1;}else{baseDirection=1;}
                          DC(" dy="<<dy<<" baseDirection="<<baseDirection);

                                  //for ( y=0; y <h ; y=y+50 ) {
                                  //draw_y(y,9);}  // just make shcool book line

  deltaX = dlt*stepBit;  DC("deltaX="<<deltaX<<END);
}//_____________________________________________________________________________

  void GBitsetContour::Line_Sum(vector<int> &H) { //read line sum with dlt
 int i=0;
  short tt=0;
  short res=0;
  short dlt_y=0;
  int y,x;
  unsigned char *p2;
  H.resize(nrows);

  if(dy==0){dlt=ncolumns;}else{dlt=abs(ncolumns/dy);}  if(dy>0){direction=-1;}else{direction=1;}
  //std::cout<<"direction="<<direction<<"dlt="<<dlt<<"\n";
           dlt_y=0; tt=0;
                                  for(y=0;y<nrows;y++){
                                                  for(x=0;x<ncolumns;x++){
                                                  if(tt==dlt*stepBit){dlt_y++; tt=0; ////printf("_x=%d _y=%d\n", x,y);
                                                  }else{tt++;}
                                                  i=(y+direction*dlt_y)*ncolumns + x;
                                                  //if(i<maxUp&&i>0){
                                                  //p2=destData + i; //std::cout<<*p3<<" ";
                                                  //res=res+(256-*p2)/100;}
                                                  H[y]=res;
                                  } // end for x (bit)
                                  ////printf("calibrate res=%d y=%d dy=%d\n ", res,y,dy);

                                  dlt_y=0; tt=0; res=0;
                                  } //end y
                   tt=0;dlt_y=0;

              //unsigned char *p2;
              //for(y=0; y < h; y++) {
              //for(x =0; x < ln[y]+10; x++ ) {
              //p2=destData + y * w + x;
              //*p2=*p2*0.9;
              //    }}


 // for ( y=0; y < 15; y++ ){lt[y]=0;}
 // for ( y=h-15; y < h; y++ ){lt[y]=0;}
    for ( y=32; y < nrows-32; y++ ) {
  //lt[y]=ln[y];
  //lt[y]=(ln[y-32]+ln[y-31]+ln[y-30]+ln[y-29]+ln[y-28]+ln[y-27]+ln[y-26]+ln[y-25]+ln[y-24]+ln[y-23]+ln[y-22]+ln[y-21]+ln[y-20]+ln[y-19]+ln[y-18]+ln[y-17]+ln[y-16]+ln[y-15]+ln[y-14]+ln[y-13]+ln[y-12]+ln[y-11]+ln[y-10]+ln[y-9]+ln[y-8]+ln[y-7]+ln[y-6]+ln[y-5]+ln[y-4]+ln[y-3]+ln[y-2]+ln[y-1]+ln[y]+
  //ln[y+1]+ln[y+2]+ln[y+3]+ln[y+4]+ln[y+5]+ln[y+6]+ln[y+7]+ln[y+8]+ln[y+9]+ln[y+10]+ln[y+11]+ln[y+12]+ln[y+13]+ln[y+14]+ln[y+15]+ln[y+16]+ln[y+17]+ln[y+18]+ln[y+19]+ln[y+20]+ln[y+21]+ln[y+22]+ln[y+23]+ln[y+24]+ln[y+25]+ln[y+26]+ln[y+27]+ln[y+28]+ln[y+29]+ln[y+30]+ln[y+31]+ln[y+32])/64;
  // for 300 dpi scan optimum is 32 point. 48 is compromise for 600 dpi scan
              //for ( x =0; x < lt[y]/10; x++ ) {
              //p2=destData + y * w + x;
              //*p2=(char)(*p2*0.7);}
    }
  }//___________________________________________________________________________

  void GBitsetContour::Line_Diff(vector<int> &In){//find differents
  int y,x;
  unsigned char *p2;
  In.resize(nrows);

  for ( y=0; y < 11; y++ ){In[y]=0;}
  for ( y=nrows-11; y < nrows; y++ ){In[y]=0;}
  for ( y=11; y < nrows-11; y++ ) {
  //l_up[y]=lt[y-11]/11+lt[y-9]/9+lt[y-7]/7+lt[y-5]/5+lt[y-3]/3+lt[y-1]-lt[y+1]-lt[y+3]/3-lt[y+5]/5-lt[y+7]/7-lt[y+9]/9-lt[y+11]/11; ////printf("l_up[%d]=%d\n",y,l_up[y]);
              //for( x =0; x < l_up[y]+50; x++ ) {
              //p2=destData + y * w + x+50;
              //*p2=(char)(*p2*0.7);}
  }
  }//___________________________________________________________________________

/*  void GBitsetContour::line_Draw(){
 int y=0;
  short tt=0; //short test;
  short min=0;
  short min_y=0;
  lineCount=0;

  for ( y=20; y < h-20; y++ ) {
      //test=l_up[y];
          if(l_up[y]<0){tt++;
      if(l_up[y]<min){min=l_up[y];min_y=y;}}
      else{
              if(tt>5){
              draw_y(min_y,90); //@//printf("new line y=%d\n",min_y);
              ln[lineCount]=min_y;lineCount++; //array on line y
              tt=0;min=0;min_y=0;}
  }}
  }//___________________________________________________________________________
*/
/*  void GBitsetContour::draw_y(int y_str,char color){
  short tt=0;
  short dlt_y=0;
  int x,i;
              for ( x=0; x < w ; x++ ) {
              if(tt==dlt*4){dlt_y++; tt=0;
              }else{tt++;}
              i=(y_str+dlt_y*direction) * w + x;
              if(i>1&&i<maxUp)destData[i]=(destData[i]*color)/200;
                         }
  }//___________________________________________________________________________
*/
//void  GBitsetContour::setLineCoordinate(){//new array whith line cioordinate data
//  deltaX = dlt*4;
//}//___________________________________________________________________________

 
