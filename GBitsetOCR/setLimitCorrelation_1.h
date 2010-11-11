-(short)setLimitCorrelation
			:(OCRLetterData *)letterBase1_ 
			:(OCRVectorData *)vectorBase1_ 
			:(OCRLetterData *)letterBase2_ 
			:(OCRVectorData *)vectorBase2_ 
			:(short)record
			:(short)currentRecord_{

//letterBase1_[record] //model letter
//letterBase2_[currentRecord_] //test letter

short vIndModel, modelVectorCount, vectorFound, vIndex, vIndex_,vIndex1_, i,correlation, vIndTest, testVectorCount;
OCRPoint letterCentreModel, letterCentreTest;
///////////////////////*first we read all model letter data
modelVectorCount=letterBase1_[record].vectorCount;    //cout<<"modelVectorCount"<<modelVectorCount<<endl;
letterCentreModel=letterBase1_[record].letterCentre;
vIndModel=letterBase1_[record].vInd;
correlation=0;
vIndTest=letterBase2_[currentRecord_].vInd;
testVectorCount=letterBase2_[currentRecord_].vectorCount;
letterCentreTest=letterBase2_[currentRecord_].letterCentre;

					for(i=vIndModel;i<vIndModel+modelVectorCount;i++)vectorBase1_[i].correlation=0;
//if(modelVectorCount>=testVectorCount){limit = modelVectorCount;}else{limit=testVectorCount;}
///////////////////////second we compare all points from test letter with points in model letter 

for(vIndex=vIndTest;vIndex<vIndTest+testVectorCount;vIndex++){  //for every point of test letter
				vectorFound=0;
				//cout<<"base index="<<vIndex<<endl;

						for (i=vIndModel;i<vIndModel+modelVectorCount;i++){ //for every point of model letter
						x=vectorBase1_[i].vStart.x-letterCentreModel.x;
						y=vectorBase1_[i].vStart.y-letterCentreModel.y;
						
						//cout<<" baseLimit_"<<"index="<<i;
						//cout<<" x0="<<vectorBase2_[vIndex].x0<<" x1="<<vectorBase2_[vIndex].x1;
						//cout<<" y0="<<vectorBase2_[vIndex].y0<<" y1="<<vectorBase2_[vIndex].y1 <<" testXStart"<<x<<" testYStart"<<y<<endl;
						if(vectorBase2_[vIndex].x0<x&&x<vectorBase2_[vIndex].x1&&
						vectorBase2_[vIndex].y0<y&&y<vectorBase2_[vIndex].y1){//cout<<" #"<<"vIndexFound" <<vIndex<<" foundXStart="<<x<<" foundYStart="<<y<<endl<<endl;
										/////////////////*we found that start of test vector exist in model letter. Now we check end of this vector 										
											x=vectorBase1_[i].vEnd.x-letterCentreModel.x; //relative coordinates of test point 
											y=vectorBase1_[i].vEnd.y-letterCentreModel.y;
											
											vIndex_=vIndex+1;  //we test start of next vector in model letter
											if(vIndex_==vIndTest+testVectorCount)vIndex_=vIndTest; //cout<<    //border value 
											//cout<<"vIndex_TestEnd"<<vIndex_;   
										//cout<<" x0="<<vectorBase2_[vIndex_].x0<<" x1="<<vectorBase2_[vIndex_].x1;
										//cout<<" y0="<<vectorBase2_[vIndex_].y0<<" y1="<<vectorBase2_[vIndex_].y1<< " testXEnd="<<x<< " testYEnd="<<y<<endl;
										
										if(vectorBase2_[vIndex_].x0<x&&x<vectorBase2_[vIndex_].x1&&
										vectorBase2_[vIndex_].y0<y&&y<vectorBase2_[vIndex_].y1){//cout<<" &"<<"vIndex_Found"<<vIndex_<<" foundXEnd="<<x<<" foundYEnd="<<y<<endl<<endl;
											vectorFound=vectorBase2_[vIndex].length;
											vectorBase1_[i].correlation=100;
										break;	
									        //cout<<"event base"<<vIndex<<endl; 
										}else{ //if end of test vector don't exist in start of next model's vector, we check events one and two and three
										//cout<<"base else"<<vIndex<<endl; 
										//////////////////////////*event ONE. two test vectors means one model vector.   
											x=vectorBase1_[i+1].vEnd.x-letterCentreModel.x; //relative coordinates of test point 
											y=vectorBase1_[i+1].vEnd.y-letterCentreModel.y;
										 if(vectorBase2_[vIndex_].x0<x&&x<vectorBase2_[vIndex_].x1&&
										 vectorBase2_[vIndex_].y0<y&&y<vectorBase2_[vIndex_].y1){
											 /////if event one is true we test vectors triangle
											 if((vectorBase1_[i].length+vectorBase2_[i+1].length)*100/vectorBase2_[vIndex].length<115){											
											 //now we increase correlation value
											 vectorFound=vectorBase2_[vIndex].length;
											  //cout<<"event one"<<vIndex<<endl; 
											 vectorBase1_[i].correlation=150; 
											 vectorBase1_[i+1].correlation=150; break;}										
											 }
										//it's not done :)  if we found event One is false we start check event two
										////////////////////*event TWO. one test vector  means two model vector
											 x=vectorBase1_[i].vEnd.x-letterCentreModel.x; //relative coordinates of test point 
											 y=vectorBase1_[i].vEnd.y-letterCentreModel.y;
										 vIndex1_=vIndex_+1;  //we test start of next vrector in model letter
											 if(vIndex1_==vIndTest+testVectorCount){ vIndex1_=vIndTest;continue;} //cout<<    //border value
											 if(vectorBase2_[vIndex1_].x0<x&&x<vectorBase2_[vIndex1_].x1&&
											 vectorBase2_[vIndex1_].y0<y&&y<vectorBase2_[vIndex1_].y1){
											 /////if event two is true we test vectors triangle
											 if((vectorBase2_[vIndex].length+vectorBase2_[vIndex_].length)*100/vectorBase2_[i].length<115)
											 vectorFound=vectorBase2_[vIndex].length+vectorBase2_[vIndex_].length; 
											 //cout<<"event two"<<vIndex<<endl;
											 vectorBase1_[i].correlation=130; break;												
											 }
										//it's not done :)  if we found event Two is false we start check event three
										////////////////////*event THREE. two test vector  means two model vector
										//need develop
											
										}//end else 	(if end of test vector don't exist in start of next model's vector, we check events )								
						                      
						}//if(vectorBase2_[vIndex]  start of model vector exist in limit 	
						//cout<<endl
						}//for (i=vIndModel
						correlation=correlation+vectorFound;//end for (index


}  //for(vIndex=vIndTest
			
return correlation;

}/////////////////////////////////////////////////////////////////////////////////////////				

