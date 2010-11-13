short GBitsetOCR::setHollogramCorrelation(int print){
//we start HologramCorrelation (structure recognition) method
//for that we construst two vectors "box". First box all vectors from model letter and second box all vectors 
//from area of model letter on pecha
///////////////////glyph model letter
///////////////////gSrc test letter
///////////////////NEXT we set Contour Corelation between this glyph  and gSrc

int  correlation1, correlation2,i,index, x0,x1,y0,y1,x2,y2,x3,y3,x4,y4,vL,pointBit, angDelta,matchStart,matchEnd;
unsigned int  matchCount, matchCenterCount, ind,shape;
unsigned long lenSumModel,lenSumTest;
	int vIndex,letterSetTestInd,letterIndex, lRecord, correlationCountTest, correlationCountModel;
OCRMatch matchPoint[1024], matchOCR[1024];
int L3;
int pr=0;



	//struct timezone dontcare = { 0, 0 }; struct timeval before, after; float milli;  //timing of program implementation
    //gettimeofday(&before, &dontcare);
	if(vDest[0].allVectorCount>vSrc[0].allVectorCount*2){
		//if(print)DC("LENGTH glyph->leterIndex="<<glyph->letterIndex<<END);
		return 0;
	}


lenSumTest=0;lRecord=0; lenSumModel=0;
matchOCR[0].allMatchCount=0;

for(vIndex=0;vIndex<glyph->vectorCount;vIndex++){
	if(vDest[vIndex].length<1)continue;
        vDest[vIndex].pointCassidy=0;
        vDest[vIndex].matchSum=0;
// for every vector in model letter Box we build oval Cassidy and check all vectors of test letter inside of that oval
	if(print)DC("///______________________________________/model letter vector ___________________"<<vIndex<<END);//<<" vectorPointCount="<<v[vIndex].vectorPointCount<<END);
//first iteration of program we check every point in test contour.
	 if(print)DC("//////////////////////++new vector="<<vIndex<<"/////////////////////"<<END);
	  x1=vDest[vIndex].vStart.x; if(print)DC("vStart x1="<<x1);// x1 model vector start x
		y1=vDest[vIndex].vStart.y; if(print)DC("; vStart y1="<<y1);// y1 model vector start y
                x3=vDest[vIndex].vEnd.x; if(print)DC("; vEnd x3="<<x3);// x2 model vector end x
		y3=vDest[vIndex].vEnd.y; if(print)DC("; vEnd y3="<<y3);// y2 model vector end y
                L3=vDest[vIndex].length; //L3 model vector length
		matchCount=0;
		matchPoint[0].allMatchCount=0;
	if(print)DC("; L3["<<vIndex<<"]="<<L3<<" glyph->letterH="<<glyph->letterH<<END);

	if(L3>600){ // ---- NEED --- DEVELOPED ADAPTIVE WAY

	 if(print)DC("big ");// <<" lBoxTestCount="<<lBoxTestCount;
				shape=220;  //// ---- NEED --- DEVELOPED ADAPTIVE WAY
				//if(shape>300)shape=300;
		L3=((L3*L3)/shape)*((L3*L3)/shape);
		if(print)DC(" kShapeCassidy="<<shape<<END);
	    if(print)DC("###__L3="<<L3<<END);
		//L3=((L3*L3)/kShapeCassidy)*((L3*L3)/kShapeCassidy); //cout<<" L3="<<L3;

				for (i=0;i<gSrc.vectorCount;i++) { //for every vector in test letter
			 if(print)DC("///////////////////////////new test vector "<<i<<END);
				pointBit=0;
				 //first we check does vector center of test vector is inside of Cassidy oval

						x2=vSrc[i].vCenter.x; //cout <<" x2="<<x2;
						y2=vSrc[i].vCenter.y; //cout <<" y2="<<y2<<END);
						if(((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))*((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3))<L3){
						 if(print)DC("center match"<<END);
							//next we check does angle between model and test vector is small enouth
							angDelta=abs(vSrc[i].vectorAngle-vDest[vIndex].vectorAngle);
							if(print)DC("vSrc["<<i<<"].vectorAngle"<<vSrc[i].vectorAngle<<"vDest["<<vIndex<<"].vectorAngle"<<vDest[vIndex].vectorAngle<<" angDelta="<<angDelta<<END);
							if(angDelta<45||angDelta>315){matchStart=0;matchEnd=0;  matchPoint[matchPoint[0].allMatchCount].matchCount=0;
								if(print)DC("angle match"<<END);
						                //vSrc[i].vectorFlag=vIndex+1; //mark vector for draw
								//next we check does start of test vector is inside of Cassidy oval
								x2=vSrc[i].vStart.x; if(print)DC("; x2="<<x2);// x2 test point x
								y2=vSrc[i].vStart.y;if(print)DC("; y2="<<y2);//<<" pointBit="<<(short)pointBit;// x2 test point
								if(print)DC("((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))*((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3)="<<((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))*((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3))<<" L3="<<L3<<END);
									if(((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))*((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3))<L3){
									matchPoint[matchPoint[0].allMatchCount].start.x=vSrc[i].vStart.x;
									matchPoint[matchPoint[0].allMatchCount].start.y=vSrc[i].vStart.y;
						 			matchPoint[matchPoint[0].allMatchCount].matchCount+=vSrc[i].length/2;
						                 if(print)DC("start match"<<END); //if it is inside
									matchStart=1;}

							        //next we check does end of test vector is inside of Cassidy oval
								x2=vSrc[i].vEnd.x; //cout <<"; xEnd2="<<x2;// x2 test point x
								y2=vSrc[i].vEnd.y; //cout <<"; yEnd2="<<y2;//<<" pointBit="<<(short)pointBit;// x2 test point
									if(((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))*((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3))<L3){
									matchPoint[matchPoint[0].allMatchCount].end.x=vSrc[i].vEnd.x;
									matchPoint[matchPoint[0].allMatchCount].end.y=vSrc[i].vEnd.y;
									matchPoint[matchPoint[0].allMatchCount].matchCount+=vSrc[i].length/2;
										 if(print)DC("end match"<<END); //if it is inside
									matchEnd=1;
									}
						 if(print)DC("///////////////////////////new test vector "<<i<<" big start match"<<"matchStart="<<matchStart<<" matchEnd="<<matchEnd<<END);
						        if(matchStart==0&&matchEnd==1){
								x0=vSrc[i].vStart.x; //cout <<"; x2="<<x2;// x2 test point x
								y0=vSrc[i].vStart.y; //cout <<"; y2="<<y2;//<<" pointBit="<<(short)pointBit;// x2 test point
								x2=vSrc[i].vCenter.x; //cout <<" x2="<<x2<<"vectorTestBase["<<vBoxTest[i]<<"].vCenter.x="<<vectorTestBase[vBoxTest[i]].vCenter.x;// x2 test point x
								y2=vSrc[i].vCenter.y; //cout <<" y2="<<y2<<END);//<<" pointBit="<<(short)pointBit;// x2 test point
									matchPoint[matchPoint[0].allMatchCount].matchCount+=setMatchCassidy(vSrc[i].length,L3,x1,y1,x3,y3,x0,y0,x2,y2);
							    }//if(matchStart==0
							if(matchStart==0&&matchEnd==0){
								x0=vSrc[i].vStart.x; //cout <<"; x2="<<x2;// x2 test point x
								y0=vSrc[i].vStart.y; //cout <<"; y2="<<y2;//<<" pointBit="<<(short)pointBit;// x2 test point
								x2=vSrc[i].vCenter.x; //cout <<" x2="<<x2<<"vectorTestBase["<<vBoxTest[i]<<"].vCenter.x="<<vectorTestBase[vBoxTest[i]].vCenter.x;// x2 test point x
								y2=vSrc[i].vCenter.y; //cout <<" y2="<<y2<<END);//<<" pointBit="<<(short)pointBit;// x2 test point
								matchPoint[matchPoint[0].allMatchCount].matchCount+=setMatchCassidy(vSrc[i].length,L3,x1,y1,x3,y3,x0,y0,x2,y2);
									x0=vSrc[i].vEnd.x; //cout <<"; x2="<<x2;// x2 test point x
									y0=vSrc[i].vEnd.y; //cout <<"; y2="<<y2;//<<" pointBit="<<(short)pointBit;// x2 test point
									x2=vSrc[i].vCenter.x; //cout <<" x2="<<x2<<"vectorTestBase["<<vBoxTest[i]<<"].vCenter.x="<<vectorTestBase[vBoxTest[i]].vCenter.x;// x2 test point x
									y2=vSrc[i].vCenter.y; //cout <<" y2="<<y2<<END);//<<" pointBit="<<(short)pointBit;// x2 test point
									matchPoint[matchPoint[0].allMatchCount].matchCount+=setMatchCassidy(vSrc[i].length,L3,x1,y1,x3,y3,x0,y0,x2,y2);
							}//if(matchStart==0
							if(matchStart==1&&matchEnd==0){
								x0=vSrc[i].vEnd.x; //cout <<"; x2="<<x2;// x2 test point x
								y0=vSrc[i].vEnd.y; //cout <<"; y2="<<y2;//<<" pointBit="<<(short)pointBit;// x2 test point
								x2=vSrc[i].vCenter.x; //cout <<" x2="<<x2<<"vectorTestBase["<<vBoxTest[i]<<"].vCenter.x="<<vectorTestBase[vBoxTest[i]].vCenter.x;// x2 test point x
								y2=vSrc[i].vCenter.y; //cout <<" y2="<<y2<<END);//<<" pointBit="<<(short)pointBit;// x2 test point
								matchPoint[matchPoint[0].allMatchCount].matchCount+= setMatchCassidy(vSrc[i].length,L3,x1,y1,x3,y3,x0,y0,x2,y2);
							}//if(matchStart==0
							matchPoint[matchPoint[0].allMatchCount].letterIndex=letterIndex;
							matchPoint[matchPoint[0].allMatchCount].vectorIndexModel=vIndex;
							//matchPoint[matchPoint[0].allMatchCount].contourIndexTest=ind;
							matchPoint[matchPoint[0].allMatchCount].vectorIndexTest=i;
							matchPoint[matchPoint[0].allMatchCount].status=0;
								x0=vSrc[i].vCenter.x; //cout <<" x0="<<x0;// x2 test point x
								y0=vSrc[i].vCenter.y; //cout <<"; y0="<<y0;//<<" pointBit="<<(short)pointBit;// x2 test point
								x2=vDest[vIndex].vCenter.x; //cout <<" x2="<<x2;// x1 model vector middle point x
								y2=vDest[vIndex].vCenter.y; //cout <<"; y2="<<y2;// y1 model vector middle point x
						    matchPoint[matchPoint[0].allMatchCount].centerDist=100-(((x2-x0)*(x2-x0)+(y2-y0)*(y2-y0))*100)/1200;
							if(matchPoint[matchPoint[0].allMatchCount].centerDist<0)matchPoint[matchPoint[0].allMatchCount].centerDist=0;
							//cout<<"matchPoint["<<matchPoint[0].allMatchCount<<"].matchCount="<<matchPoint[matchPoint[0].allMatchCount].matchCount<<END);
							//" centerDist="<<matchPoint[matchPoint[0].allMatchCount].centerDist<<END);
							matchPoint[0].status=0;
	if(print)DC("big	matchPoint["<<matchPoint[0].allMatchCount<<"].matchCount="<<matchPoint[matchPoint[0].allMatchCount].matchCount<<END);
	if(print)DC("big	matchPoint["<<matchPoint[0].allMatchCount<<"].vectorIndexModel="<<matchPoint[matchPoint[0].allMatchCount].vectorIndexModel<<END);
	if(print)DC("big	matchPoint["<<matchPoint[0].allMatchCount<<"].vectorIndexTest="<<matchPoint[matchPoint[0].allMatchCount].vectorIndexTest<<END);
	if(print)DC("big	matchPoint["<<matchPoint[0].allMatchCount<<"].centerDist="<<matchPoint[matchPoint[0].allMatchCount].centerDist<<END);
	//if(print)DC("	matchPoint["<<matchPoint[0].allMatchCount<<"].endPoint="<<matchPoint[matchPoint[0].allMatchCount].endPoint<<END);
	//if(print)DC("	matchPoint["<<matchPoint[0].allMatchCount<<"].status="<<matchPoint[matchPoint[0].allMatchCount].status<<endl<<endl<<END);
							matchPoint[0].allMatchCount++;



							}//if(angDelta

						}//if center of test vector is inside of Cassidy oval
			//if(matchCount>vectorModelBase[vBoxModel[index]].vectorPointCount){matchCount=vectorModelBase[vBoxModel[index]].vectorPointCount; break;}//match all vector length
			}//for (i=0 //for every vector in vBoxTest

		}else{//L3>vectorLimit*Radius

	if(print)DC("small ");
		L3=900;
		x1=vDest[vIndex].vCenter.x; if(print)DC("v[vIndex].vCenter.x="<<x1);// x1 model vector middle point x
		y1=vDest[vIndex].vCenter.y; if(print)DC("; v[vIndex].vCenter.y="<<y1<<END);// y1 model vector middle point x

			for (i=0;i<gSrc.vectorCount;i++) { //for every vector in test letter
			 if(print)DC("///////////////////////////////new test vector "<<i<<END);
				pointBit=0;
				 //first we check does vector center of test vector is inside of Cassidy oval

						x2=vSrc[i].vCenter.x;  if(print)DC(" vSrc[i].vCenter.x="<<vSrc[i].vCenter.x<<END);// x2 test point x
						y2=vSrc[i].vCenter.y;  if(print)DC(" vSrc[i].vCenter.y="<<vSrc[i].vCenter.y<<END);// x2 test point
				                                 if(print)DC(" radius match="<<(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<<END);

						if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<L3){

					 	 if(print)DC("center match"<<END);
							//next we check does angle between model and test vector is small enouth
							angDelta=abs(vSrc[i].vectorAngle-vDest[vIndex].vectorAngle);
							//cout<<"vectorTestBase["<<vBoxTest[i]<<"].vectorAngle"<<vectorTestBase[vBoxTest[i]].vectorAngle<<"vectorModelBase["<<vBoxModel[index]<<"].vectorAngle"<<vectorModelBase[vBoxModel[index]].vectorAngle<<" angDelta="<<angDelta<<END);
							if(angDelta<45||angDelta>315){matchStart=0;matchEnd=0;  matchPoint[matchPoint[0].allMatchCount].matchCount=0;
						 if(print)DC("angle match"<<END);
								//vSrc[i].vectorFlag=vIndex+1; //mark vector for draw
								//next we check does start of test vector is inside of Cassidy oval
								x2=vSrc[i].vStart.x; //cout <<"; x2="<<x2;// x2 test point x
								y2=vSrc[i].vStart.y; //cout <<"; y2="<<y2;//<<" pointBit="<<(short)pointBit;// x2 test point
								if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<L3){
									matchPoint[matchPoint[0].allMatchCount].start.x=vSrc[i].vStart.x;
									matchPoint[matchPoint[0].allMatchCount].start.y=vSrc[i].vStart.y;
									matchPoint[matchPoint[0].allMatchCount].matchCount+=vSrc[i].length/2;					 //cout<<"start match"<<END); //if it is inside
									matchStart=1;
						if(print)DC("start match"<<END); //if it is inside
									}
							        //next we check does end of test vector is inside of Cassidy oval
								x2=vSrc[i].vEnd.x; //cout <<"; x2="<<x2;// x2 test point x
								y2=vSrc[i].vEnd.y; //cout <<"; y2="<<y2;//<<" pointBit="<<(short)pointBit;// x2 test point
								if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<L3){
									matchPoint[matchPoint[0].allMatchCount].end.x=vSrc[i].vEnd.x;
									matchPoint[matchPoint[0].allMatchCount].end.y=vSrc[i].vEnd.y;
									matchPoint[matchPoint[0].allMatchCount].matchCount+=vSrc[i].length/2;
						 if(print)DC("end match"<<END); //if it is inside
									matchEnd=1;
									}

						 if(print)DC("///////////////////////////new test vector "<<i<<" small start match"<<"matchStart="<<matchStart<<" matchEnd="<<matchEnd<<END);
						        if(matchStart==0&&matchEnd==1){
								x0=vSrc[i].vStart.x; //cout <<"; x2="<<x2;// x2 test point x
								y0=vSrc[i].vStart.y; //cout <<"; y2="<<y2;//<<" pointBit="<<(short)pointBit;// x2 test point
								x2=vSrc[i].vCenter.x; //cout <<" x2="<<x2<<"vectorTestBase["<<vBoxTest[i]<<"].vCenter.x="<<vectorTestBase[vBoxTest[i]].vCenter.x;// x2 test point x
								y2=vSrc[i].vCenter.y; //cout <<" y2="<<y2<<END);//<<" pointBit="<<(short)pointBit;// x2 test point
								matchPoint[matchPoint[0].allMatchCount].matchCount+=setMatchCircle(vSrc[i].length,L3,x1,y1,x0,y0,x2,y2);
							}//if(matchStart==0
							if(matchStart==0&&matchEnd==0){
								x0=vSrc[i].vStart.x; //cout <<"; x2="<<x2;// x2 test point x
								y0=vSrc[i].vStart.y; //cout <<"; y2="<<y2;//<<" pointBit="<<(short)pointBit;// x2 test point
								x2=vSrc[i].vCenter.x; //cout <<" x2="<<x2<<"vectorTestBase["<<vBoxTest[i]<<"].vCenter.x="<<vectorTestBase[vBoxTest[i]].vCenter.x;// x2 test point x
								y2=vSrc[i].vCenter.y; //cout <<" y2="<<y2<<END);//<<" pointBit="<<(short)pointBit;// x2 test point
								matchPoint[matchPoint[0].allMatchCount].matchCount+=setMatchCircle(vSrc[i].length,L3,x1,y1,x0,y0,x2,y2);
									x0=vSrc[i].vEnd.x; //cout <<"; x2="<<x2;// x2 test point x
									y0=vSrc[i].vEnd.y; //cout <<"; y2="<<y2;//<<" pointBit="<<(short)pointBit;// x2 test point
									x2=vSrc[i].vCenter.x; //cout <<" x2="<<x2<<"vectorTestBase["<<vBoxTest[i]<<"].vCenter.x="<<vectorTestBase[vBoxTest[i]].vCenter.x;// x2 test point x
									y2=vSrc[i].vCenter.y; //cout <<" y2="<<y2<<END);//<<" pointBit="<<(short)pointBit;// x2 test point
									matchPoint[matchPoint[0].allMatchCount].matchCount+=setMatchCircle(vSrc[i].length,L3,x1,y1,x0,y0,x2,y2);
							}//if(matchStart==0
							if(matchStart==1&&matchEnd==0){
								x0=vSrc[i].vEnd.x; //cout <<"; x2="<<x2;// x2 test point x
								y0=vSrc[i].vEnd.y; //cout <<"; y2="<<y2;//<<" pointBit="<<(short)pointBit;// x2 test point
								x2=vSrc[i].vCenter.x; //cout <<" x2="<<x2<<"vectorTestBase["<<vBoxTest[i]<<"].vCenter.x="<<vectorTestBase[vBoxTest[i]].vCenter.x;// x2 test point x
								y2=vSrc[i].vCenter.y; //cout <<" y2="<<y2<<END);//<<" pointBit="<<(short)pointBit;// x2 test point
								matchPoint[matchPoint[0].allMatchCount].matchCount+=setMatchCircle(vSrc[i].length,L3,x1,y1,x0,y0,x2,y2);
							}//if(matchStart==0
							matchPoint[matchPoint[0].allMatchCount].letterIndex=letterIndex;
							matchPoint[matchPoint[0].allMatchCount].vectorIndexModel=vIndex;
							//matchPoint[matchPoint[0].allMatchCount].contourIndexTest=ind;
							matchPoint[matchPoint[0].allMatchCount].vectorIndexTest=i;
							matchPoint[matchPoint[0].allMatchCount].status=0;
								x0=vSrc[i].vCenter.x; //cout <<"; x0="<<x0;// x2 test point x
								y0=vSrc[i].vCenter.y; //cout <<"; y0="<<y0;//<<" pointBit="<<(short)pointBit;// x2 test point
								x2=vDest[vIndex].vCenter.x; //cout <<" x2="<<x2;// x1 model vector middle point x
								y2=vDest[vIndex].vCenter.y; //cout <<"; y2="<<y2;// y1 model vector middle point x
							matchPoint[matchPoint[0].allMatchCount].centerDist=100-(((x2-x0)*(x2-x0)+(y2-y0)*(y2-y0))*100)/1200;  ////// ---- NEED --- DEVELOPED ADAPTIVE WAY
							if(matchPoint[matchPoint[0].allMatchCount].centerDist<0)matchPoint[matchPoint[0].allMatchCount].centerDist=0;
							//cout<<"matchPoint["<<matchPoint[0].allMatchCount<<"].matchCount="<<matchPoint[matchPoint[0].allMatchCount].matchCount<<END);
							//" centerDist="<<matchPoint[matchPoint[0].allMatchCount].centerDist<<END);
							matchPoint[0].status=0;
								if(print)DC("small	matchPoint["<<matchPoint[0].allMatchCount<<"].matchCount="<<matchPoint[matchPoint[0].allMatchCount].matchCount<<END);
								if(print)DC("small	matchPoint["<<matchPoint[0].allMatchCount<<"].vectorIndexModel="<<matchPoint[matchPoint[0].allMatchCount].vectorIndexModel<<END);
								if(print)DC("small	matchPoint["<<matchPoint[0].allMatchCount<<"].vectorIndexTest="<<matchPoint[matchPoint[0].allMatchCount].vectorIndexTest<<END);
								if(print)DC("small	matchPoint["<<matchPoint[0].allMatchCount<<"].centerDist="<<matchPoint[matchPoint[0].allMatchCount].centerDist<<END);
								//if(print)DC("	matchPoint["<<matchPoint[0].allMatchCount<<"].endPoint="<<matchPoint[matchPoint[0].allMatchCount].endPoint<<END);
								//if(print)DC("	matchPoint["<<matchPoint[0].allMatchCount<<"].status="<<matchPoint[matchPoint[0].allMatchCount].status<<endl<<endl<<END);

							matchPoint[0].allMatchCount++;

							}//if(angDelta

					      }//if center of test vector is inside of test circle
			//if(matchCount>vectorModelBase[vBoxModel[index]].vectorPointCount){matchCount=vectorModelBase[vBoxModel[index]].vectorPointCount;break;} //match all vector length
			}


		}//else{//if(L3>vBoxModel[index].vectorLimit

//test all match in Cassidy oval
       if(matchPoint[0].allMatchCount>0){
		  matchCount=testCassidyMatch(matchPoint,matchOCR);
       }

//if(print)DC("v["<<vIndex<<"].pointCassidy="<<matchCount<<END);
vDest[vIndex].pointCassidy=matchCount;


}//for(vIndex


	//gettimeofday(&after, &dontcare);
	//if(after.tv_usec > before.tv_usec){milli=(after.tv_usec - before.tv_usec);
	//}else{milli=(after.tv_usec+1000000-before.tv_usec);
	//}
	//if(print)DC("         setHollogramCorrelation sec"<<(after.tv_sec - before.tv_sec)<< " milli.sec"<<milli<<END);
	//gettimeofday(&before, &dontcare);

	//for(int ind=0;ind<matchOCR[0].allMatchCount;ind++){ //for all match
	//if(print)DC(" matchOCR["<<ind<<"].vectorIndexModel="<<matchOCR[ind].vectorIndexModel<<" matchOCR["<<ind<<"].vectorIndexTest="<<matchOCR[ind].vectorIndexTest);
    //if(print)DC(" matchOCR["<<ind<<"].status="<<matchOCR[ind].status<<" matchOCR["<<ind<<"].matchSumTest="<<matchOCR[ind].matchSumTest<<END);
    //}


//____________now calculate correlation for model
//short correlationCountModel=0, correlationCountTest=0;

correlationCountModel=setCassidyCorrelation(matchOCR);
	lenSumTest=1;	correlationCountTest=0;
for(vIndex=0;vIndex<glyph->vectorCount;vIndex++){
// for every vector in model letter Box we check correlation and sum vector Length depend of it.
	if(print)DC("vDest["<<vIndex<<"].matchSum="<<vDest[vIndex].matchSum<<END);
	correlationCountModel+=(vDest[vIndex].length*vDest[vIndex].matchSum)/100;
}
	for(vIndex=0;vIndex<gSrc.vectorCount;vIndex++){
		// for every vector in model letter Box we check correlation and sum vector Length depend of it.
		//if(print)DC("vSrc["<<vIndex<<"].matchSum="<<vSrc[vIndex].matchSum<<" vSrc[vIndex].length"<<vSrc[vIndex].length<<END);
		if(vSrc[vIndex].matchSum){
			correlationCountTest+=(vSrc[vIndex].length*vSrc[vIndex].matchSum)/100;
		    lenSumTest+=vSrc[vIndex].length;
		}
	}



//____________no calculate correlation for test
//for (i=0;i<gSrc.vectorCount;i++) { //for every vector in test letter
//		if(print)DC("vSrc["<<i<<"].matchSum="<<vSrc[i].matchSum<<END);
//       correlationCountTest+=(vSrc[i].length*vSrc[i].matchSum)/100;
//}


if(print)DC(" glyph->lengthSum"<<glyph->lengthSum<<" correlationCountModel="<<correlationCountModel<<END);
if(print)DC(" gSrc.lengthSum"<<gSrc.lengthSum<<" correlationCountTest="<<correlationCountTest<<END);

//if((lenSumTest-correlationCountTest)>(lenSumModel-correlationCountModel)){ //we choose bigest value of not matched point
correlation1 = (correlationCountModel*100)/(glyph->lengthSum);  //sum value of not matched point
			//*100//for 100%
		    ///(glyph->lengthSum);// divide on all point in model and test
//if(print)DC("#0");
correlation2 = (correlationCountTest*100)/lenSumTest;  //sum value of not matched point
//if(print)DC("#1");


	if(correlation1>correlation2)correlation1=correlation2;
//if(print)DC("#2");
        //correlation1+=glyph->vectorCount/3;
	//
	//if(print)DC("hollogramCassidy correlation1="<<correlation1<<END);
	//
	//if(print)DC("hollogramCassidy correlation2="<<correlation1<<END);


	//if(gSrc.correlation1<correlation1){
	//	gSrc.correlation1=correlation1;
	//	gSrc.letterIndex=glyph->letterIndex;
		//if(print)DC("gSrc.letterIndex="<<gSrc.letterIndex<<" gSrc.correlation1="<<gSrc.correlation1<<END);
	//}
    //if(print)DC("gSrc.correlation1="<<gSrc.correlation1<<END);


	//}else{
//correlation = ((lenSumTest+lenSumModel)//all point in model and test
//		    -(lenSumModel-correlationCountModel)*2 //bigest value of not matched point
		    //all match point
//		    )*100   //for 100%
//		    /(lenSumTest+lenSumModel);// divide on all point in model and test
//}
//correlation = (correlationCount*200)/(lenSumTest+lenSumModel);
//if(print)DC("hollogramCassidy correlation="<<correlation<<END);


//if(lBoxTestCount!=glyph->letterSetCount)correlation=correlation-abs(glyph->letterSetCount-lBoxTestCount)*10;  //if we hasn't some part of letter

//cout<<"lBoxTestCount="<<lBoxTestCount<<" letterModelScale["<<0<<"].letterSetCount="<<(short)glyph->letterSetCount<<END);
//cout<<"hollogramCassidy LetterSet correlation="<<correlation<<END);
//for(index=0;index<letterSetTest.count;index++){ //for every contour in letterSetTest
//if(correlation>contourTestBase[letterSetTest.letter[index]].correlation)
//contourTestBase[letterSetTest.letter[index]].correlation=correlation;
//}


	//gettimeofday(&after, &dontcare);
	//if(after.tv_usec > before.tv_usec){milli=(after.tv_usec - before.tv_usec);
	//}else{milli=(after.tv_usec+1000000-before.tv_usec);
	//}
	//if(print)DC("         setCassidyCorrelation sec"<<(after.tv_sec - before.tv_sec)<< " milli.sec"<<milli<<END);


return correlation1;

}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
