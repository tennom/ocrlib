-(short)setLimitCorrelation
			:(OCRLetterData *)letterModelBase 
			:(OCRVectorData *)vectorModelBase 
			:(OCRLetterData *)letterTestBase 
			:(OCRVectorData *)vectorTestBase 
			:(short)record
			:(short)currentRecord_{

//letterModelBase[record] //model letter
//letterTestBase[currentRecord_] //test letter

short vIndModel, modelVectorCount, vectorFound, tIndex, i, i_, correlation, vIndTest, testVectorCount;
short indexMTest,endTestLetter;
short index,correlationCount,allPointsCount;
OCRPoint letterCenterModel, letterCenterTest;
unsigned char  limitPoints[128][8]; 
short limit=cLimit*10;  //limit equal 4 pix *10
allPointsCount=0;correlationCount=0;endTestLetter=0;
///////////////////////*first we read all model letter data
modelVectorCount=letterModelBase[record].vectorCount;    //cout<<"modelVectorCount"<<modelVectorCount<<endl;
letterCenterModel=letterModelBase[record].letterCenter;
vIndModel=letterModelBase[record].vInd;
vIndTest=letterTestBase[currentRecord_].vInd;
testVectorCount=letterTestBase[currentRecord_].vectorCount;
letterCenterTest=letterTestBase[currentRecord_].letterCenter;
vectorFound=0;
correlation=0;
				for(i=vIndModel;i<vIndModel+modelVectorCount;i++)vectorModelBase[i].correlation=0; //for all model letter's vectors set correlation
					//for(tIndex=vIndTest;tIndex<vIndTest+testVectorCount;tIndex++)vectorTestBase[tIndex].startPointStatus=0; //for all test letter's vectors set status
					
//if(modelVectorCount>=testVectorCount){limit = modelVectorCount;}else{limit=testVectorCount;}
///////////////////////second we compare all points from test letter with points in model letter 

//cout <<"////////////*//////////////**"<<" currentRecord_="<<currentRecord_<<" record="<<record<<endl;
allPointsCount=0;index=0;
for (i=vIndModel;i<vIndModel+modelVectorCount;i++){ //for every point of model letter
//cout<<"next i="<<i<<endl;
x=vectorModelBase[i].vStart.x-letterCenterModel.x;
y=vectorModelBase[i].vStart.y-letterCenterModel.y;

limitPoints[index][0]=0;//start point count
				for(tIndex=vIndTest;tIndex<vIndTest+testVectorCount;tIndex++){  //for every point of test letter
				//cout<<" base model index="<<i-vIndModel<<"///base test index="<<tIndex<<endl;
						//cout<<" x0="<<vectorTestBase[tIndex].x0<<" x1="<<vectorTestBase[tIndex].x1;
						//cout<<" y0="<<vectorTestBase[tIndex].y0<<" y1="<<vectorTestBase[tIndex].y1 <<" testXStart"<<x<<" testYStart"<<y<<endl;
						//if(x>vectorTestBase[tIndex].x0){
						//if(x<vectorTestBase[tIndex].x1){
						//if(y>vectorTestBase[tIndex].y0){
						//if(y<vectorTestBase[tIndex].y1){ 
						/////////////////*we found that start of test vector exist in model letter
						//cout<<" #"<<"tIndexFound" <<tIndex-vIndTest<<" foundXStart="<<x<<" foundYStart="<<y<<endl;
						//limitPoints[index][0]++;// increase points count 
						//limitPoints[index][limitPoints[index][0]]=tIndex-vIndTest;														
					     //  }}}}
				}//end for(tIndex=vIndTest;tIndex
//cout<<"///////////////////////////////// limitPoints["<<index<<"][0]="<<(short)limitPoints[index][0]<<endl;
if(limitPoints[index][0]>0)allPointsCount++;//increase model letter limits count
index++;
}///for (i=vIndModel 
////////*print limitPoint array
//for(i=0;i<modelVectorCount;i++){
//cout<<"modelLetterPoint/// "<<i<<" /// ";
//for(tIndex=1;tIndex<=limitPoints[i][0];tIndex++){
//cout<<(short)limitPoints[i][tIndex]<<" ";
//}cout<<endl;
//}

//cout <<"allPointsCount="<<allPointsCount<<" modelVectorCount="<<modelVectorCount<<endl;

//if this two letter has enouth common points
if(allPointsCount>modelVectorCount/2){
//if(allPointsCount>0){
correlationCount=0;

// limitPoints contain array all test points correlated with avery model point
//now we read it

short startPointModel, startPointTest,endPointModel, minTestPoint,endPointTest, minDelta,minPointIndex,delta;
short startPointLimit,deltaT,deltaM,startPointLimitTest;
//cout<<"MODEL       TEST"<<endl;
//cout<<"start|stop  start|stop";
for(i=0;i<modelVectorCount;i++){//for every model letter point 
		if(limitPoints[i][0]>0){startPointLimit=i;
					//we found first model letter limit in which exist test letter vector
					//now we choose startPointLimitTest
					//for thet we choose closest test letter vector in limit
					startPointLimitTest=512;minDelta=512;
					for(tIndex=1;tIndex<=limitPoints[i][0];tIndex++){//for every test point in limit
					/////test distanse clockwise 
					deltaT=testVectorCount-startPointLimit+limitPoints[i][tIndex];
					if(deltaT>=testVectorCount)deltaT-=testVectorCount;
					/////test distance contr clockwise
					deltaM=testVectorCount-limitPoints[i][tIndex]+startPointLimit;
					if(deltaM>=testVectorCount)deltaM-=testVectorCount;
					//now we choose min distance
					if(deltaT<minDelta){minDelta=deltaT;startPointLimitTest=limitPoints[i][tIndex];}
					if(deltaM<minDelta){minDelta=deltaM;startPointLimitTest=limitPoints[i][tIndex];}
					}
//cout<<" startPointLimitTest="<<startPointLimitTest<<endl;				
		break;}//found first model point and firs test point for correlation
}//end for (i=0;i<modelVectorCount

		index=0;
endPointTest=startPointLimitTest; //start from min distance test vector in limit
/////////////////now we test all model points from this point in cicle		
while(index<modelVectorCount){
		//now check test points
		i=index+startPointLimit;
		if(i>=modelVectorCount)i-=modelVectorCount;
		if(limitPoints[i][0]>0){startPointModel=i;}else{continue;}//found first model point for correlation

/////////////////*choose min distant value between startTestLetterPoint and test point in limit
                                        minTestPoint=512;minDelta=512;
					for(tIndex=1;tIndex<=limitPoints[i][0];tIndex++){//for every test point in limit 
					delta=testVectorCount-endPointTest+limitPoints[i][tIndex];
					if(delta>=testVectorCount)delta-=testVectorCount;
					//if(limitPoints[i][tIndex]<minTestPoint&&limitPoints[i][tIndex]>=endPointTest) minTestPoint=limitPoints[i][tIndex];					
					if(delta<=minDelta){minTestPoint=limitPoints[i][tIndex];minDelta=delta;}															
					}
//cout <<endl<<"now checked"<<i<<" endPointTest="<<endPointTest<<" minTestPoint="<<minTestPoint;					
//////////////**check existens few test points in one limit		
					startPointTest=minTestPoint;
					for(tIndex=1;tIndex<=limitPoints[i][0];tIndex++){//for every test point in limit 					
					delta=testVectorCount-minTestPoint+limitPoints[i][tIndex];
					if(delta>=testVectorCount)delta-=testVectorCount;
					//if(limitPoints[i][tIndex]>minTestPoint&&limitPoints[i][tIndex]-minTestPoint==1) {
					if(delta==1) {
					minTestPoint=limitPoints[i][tIndex];	
					//cout<<endl<<"  "<<i<<"///"<<i<<"\t\t"<<startPointTest<<"///"<<minTestPoint<<" * ";
					vectorFound+=vectorTestBase[startPointTest+vIndTest].length;
					//vectorTestBase[startPointTest+vIndTest].startPointStatus=10;  //mark vector for drawing
			                //cout<<endl<<"1_len["<<startPointTest<<"]="<<vectorTestBase[startPointTest+vIndTest].length<<" vectorFound="<<vectorFound<<"  lenSum="<<letterTestBase[currentRecord_].vectorSum;							
						//if vector start and vector end exist in one limit we sum his length in correlation
					startPointTest=limitPoints[i][tIndex];
					if(minTestPoint==startPointLimitTest){endTestLetter=1;}//end of test letter
					}}
		if(endTestLetter==1)break;			
                startPointTest=minTestPoint;
		startPointModel=i;	
		
		
		//if(startPointTest-vIndTest==modelVectorCount-1)break;
		//we found start of correlation event
		//now we check end of this event
		minDelta=512;
			indexMTest=modelVectorCount;
////////choose min distance between startTestPoint and endTestPoint			
			while(indexMTest>index){//for every model letter point 
			i_=indexMTest+startPointLimit;  
			if(i_>=modelVectorCount)i_-=modelVectorCount;   //test border value
 			for(tIndex=1;tIndex<=limitPoints[i_][0];tIndex++){//for every test point in limit 
			deltaT=testVectorCount-startPointTest+limitPoints[i_][tIndex];
			if(deltaT>=testVectorCount)deltaT-=testVectorCount;
			deltaT+=indexMTest;
				//cout<<endl<<"///*"<<i_<<"/// limitPoints["<<i_<<"]["<<tIndex<<"]="<<(short)limitPoints[i_][tIndex]<<" delta="<<deltaT<<" vCout="<<testVectorCount;
				if((deltaT<=minDelta&&deltaT>indexMTest)||(deltaT==indexMTest&&i_-i==1)){minDelta=deltaT;
				endPointTest=limitPoints[i_][tIndex];
				minPointIndex=i_;}
			}indexMTest--;}
			endPointModel=minPointIndex;					

///////////print data/////////**
//		//cout<<endl<<"  "<<startPointModel<<"///"<<endPointModel<<"\t\t"<<startPointTest<<"///"<<endPointTest;
		
/////////////////////////////**now we calculate correlation/////////////////////////////////////////////////////////////////////**
				deltaM=modelVectorCount-startPointModel+endPointModel;
				if(deltaM>=modelVectorCount)deltaM-=modelVectorCount;   //cout<<endl<<"delta1="<<delta;
			        deltaT=testVectorCount-startPointTest+endPointTest;
				if(deltaT>=testVectorCount)deltaT-=testVectorCount; 	//cout<<endl<<"delta1="<<delta;
		if(deltaM==1){						
		if(deltaT==1){		
				vectorFound+=vectorTestBase[startPointTest+vIndTest].length;
				//vectorTestBase[startPointTest+vIndTest].startPointStatus=30;  //mark vector for drawing
				//cout<<endl<<"2_len["<<startPointTest<<"]="<<vectorTestBase[startPointTest+vIndTest].length<<" vectorFound="<<vectorFound<<"  lenSum="<<letterTestBase[currentRecord_].vectorSum;
		if(endPointTest==startPointLimitTest){endTestLetter=1; break;} //end test letter
		}}else{
		if(deltaM==0){
		if(deltaT==0)break;}
		}		
					
		
///////////**if between two limit of model letters exist more then one vector
///////////**or between two base limit of model letters exist limit(limits) in which not exist test letter points
///////////**we start method for count correlation for vectors between two base points 		
                if(deltaM>1||deltaT>1){

//cout <<endl<<"@*"<<startPointModel<<"///"<<endPointModel<<"\t\t"<<startPointTest<<"///"<<endPointTest;

correlationCount+=[self setPointCorrelation
				:letterModelBase 
				:letterTestBase 
				:record
				:currentRecord_
				:startPointModel
				:endPointModel
				:startPointTest
				:endPointTest
				:deltaM
				:deltaT];

/////**test end test letter
//cout<<endl<<" startPointTest="<<startPointTest<<" endPointTest="<<endPointTest<<
//" testVectorCount="<<testVectorCount<<" startPointLimitTest="<<startPointLimitTest;

delta=testVectorCount-startPointTest+endPointTest;
if(delta>=testVectorCount)delta-=testVectorCount;
deltaT=testVectorCount-startPointTest+startPointLimitTest;
if(deltaT>=testVectorCount)deltaT-=testVectorCount;

//cout<<endl<<" delta="<<delta<<" deltaT="<<deltaT<<endl;
if(delta>=deltaT&&startPointTest!=startPointLimitTest){endTestLetter=1;break;}// end test letter

//now we test how much model points we must pass
while(deltaM>0){
index++;startPointModel++;
if(startPointModel>modelVectorCount)startPointModel-=modelVectorCount;
deltaM=modelVectorCount-startPointModel+endPointModel;
if(deltaM>=modelVectorCount)deltaM-=modelVectorCount;   
//cout<<endl<<"delta1="<<deltaM;
}	

}else{index++;}

//cout<<endl<<"startPointLimitTest="<<startPointLimitTest<<" endPointTest="<<endPointTest;
//cout<<endl<<" modelVectorCount="<<modelVectorCount<<" testVectorCount="<<testVectorCount;

		//		i=minPointIndex;
//index++;
}//end while(index<=modelVectorCount)

if(endTestLetter==0){
index=0;
deltaT=testVectorCount-endPointTest+startPointLimitTest;
if(deltaT>=testVectorCount)deltaT-=testVectorCount; 	//cout<<endl<<"delta1="<<delta;
if(deltaT>0){
//cout<<endl<<" deltaT="<<deltaT<<" startPointLimitTest="<<startPointLimitTest<<" endPointTest="<<endPointTest<<" testVectorCount="<<testVectorCount<<endl;
while(index<=deltaT){
tIndex=index+endPointTest;
if(tIndex>testVectorCount)tIndex-=testVectorCount;
//cout<<" tIndex="<<tIndex<<endl;
//vectorTestBase[tIndex+vIndTest].startPointStatus=35;
index++;
}}}

//cout<<endl<<" limit="<<limit<<" letterTestBase[currentRecord_].vectorSum="<<letterTestBase[currentRecord_].vectorSum<<
//" letterModelBase[record].vectorSum="<<letterModelBase[record].vectorSum<<" correlationCount="<<correlationCount<<" vectorFound="<<vectorFound;

//allPointsCount=(letterTestBase[currentRecord_].vectorSum+letterModelBase[record].vectorSum)/limit;
correlationCount=(vectorFound*2)/limit+correlationCount*2;
correlation=correlationCount*100/allPointsCount;//end for (index	
//cout<<endl<<" vectorFound="<<vectorFound<<"  lenSum="<<letterTestBase[currentRecord_].vectorSum;
//cout<<endl<<"correlationCount="<<correlationCount<<" allPointsCount="<<allPointsCount<<" correlation="<<correlation<<endl<<endl;

//for(i=0;i<testVectorCount;i++)cout<<"len["<<i<<"]="<<vectorTestBase[i+vIndTest].length<<endl;
}//if(allPointsCount>modelVectorCount/2)				
return correlation;

}/////////////////////////////////////////////////////////////////////////////////////////				

