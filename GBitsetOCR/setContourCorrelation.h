-(short)setContourCorrelation
		:(OCRLetterData *)letterModelBase 
		:(OCRVectorData *)vectorModelBase 
		:(OCRLetterData *)letterTestBase 
		:(OCRVectorData *)vectorTestBase 
		:(short) record 
		:(short) currentRecord_{

//model letter       letterModelBase[record];
//testLetter letterTestBase[currentRecod_];

//cout <<endl<<"//////////model record="<<record<<" /////////////////currentRecord_="<<currentRecord_<<endl;
//for every vector of test letter we build addition point in some function and receive it in array
//[self setAdditionPoint:letterTestBase :vectorTestBase : currentRecord_];

short index, pointIndex, x1,x2,x3,y1,y2,y3, correlationCount;
int L3;
char pointBit;
short pointCount;
correlationCount=0;
//cout<<"letterModelBase[record].vInd"<<letterModelBase[record].vInd<<" letterModelBase[record].letterCenter.x="<<letterModelBase[record].letterCenter.x<<" letterModelBase[record].letterCenter.y="<<letterModelBase[record].letterCenter.x<<
//" letterTestBase[currentRecord_].letterCenter.x="<<letterTestBase[currentRecord_].letterCenter.x<<" letterTestBase[currentRecord_].letterCenter.y="<<letterTestBase[currentRecord_].letterCenter.y<<endl;

for(pointIndex=0;pointIndex<letterTestBase[currentRecord_].angLength;pointIndex++){ //for every point of contour
letterTestBase[currentRecord_].status[pointIndex]=0;} // erase status

for(index=letterModelBase[record].vInd;index<letterModelBase[record].vInd+letterModelBase[record].vectorCount;index++){
// for every vector in model letter we build oval Cassidy and check all points of test letter inside of that oval
//cout<<"model letter vector "<<index<<endl;
//first iteration of program we check every point in test contour.
		//cout<<"//////////////////////new vector/////////////////////"<<endl;
		//cout<<"record="<<record<<" index="<<index<<" angLength="<<letterModelBase[record].angLength<<endl;
		x1=vectorModelBase[index].vStart.x-letterModelBase[record].letterCenter.x; //cout <<"x1="<<x1;// x1 model vector start x
		y1=vectorModelBase[index].vStart.y-letterModelBase[record].letterCenter.y; //cout <<"; y1="<<y1;// y1 model vector start y
                x3=vectorModelBase[index].vEnd.x-letterModelBase[record].letterCenter.x; //cout <<"; x3="<<x3;// x2 model vector end x
		y3=vectorModelBase[index].vEnd.y-letterModelBase[record].letterCenter.y; //cout <<"; y3="<<y3<<endl;// y2 model vector end y
                L3=vectorModelBase[index].length; //L3 model vector length 
				//cout<<"L3["<<index<<"]="<<L3;
		L3=((L3*L3)/320)*((L3*L3)/320);
		//cout <<" L3^4*125="<<L3<<endl;
		pointCount=1; pointBit=0;
for(pointIndex=0;pointIndex<letterTestBase[currentRecord_].angLength;pointIndex++){ //for every point of contour
	//cout<<" status="<<(short)letterTestBase[currentRecord_].status[pointIndex];
	if(letterTestBase[currentRecord_].status[pointIndex]==0){//if this point is free
	x2=letterTestBase[currentRecord_].letterX[pointIndex]-letterTestBase[currentRecord_].letterCenter.x; //cout <<"; x2="<<x2;// x2 test point x
	y2=letterTestBase[currentRecord_].letterY[pointIndex]-letterTestBase[currentRecord_].letterCenter.y; //cout <<"; x2="<<x2<<" pointBit="<<(short)pointBit;// x2 test point x
			if(((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))*((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3))<=L3){
			if(pointBit==0){pointBit=1;} //start of point chain
				if(pointBit==1){
				letterTestBase[currentRecord_].status[pointIndex]=index+1; //mark point by index of correlation vector
				correlationCount++; //=index-letterModelBase[record].vInd+1;
				//cout<<"index="<<index<<" pointIndex="<<pointIndex<<" correlationCount="<<correlationCount<<endl;
				pointCount++;}
			}else{if(pointBit==1)pointBit=3;}//end points chain		

	}////if this point is free
}//for(pointIndex=0
vectorModelBase[index].pointCassidy=pointCount; //[0] element store count index of array
}//for(index
//cout<<"all correlationCount="<<correlationCount<<endl;
//cout<<"letterTestBase[currentRecord_].angLengt="<<letterTestBase[currentRecord_].angLength<<" letterModelBase[record].angLength="<<letterModelBase[record].angLength<<endl;
short correlation = (correlationCount*200)/(letterTestBase[currentRecord_].angLength+letterModelBase[record].angLength);
//cout<<"Cassidy correlation="<<correlation<<endl;

return correlation;
}//////////////////////////////////////////////////////////////////////////////////////
