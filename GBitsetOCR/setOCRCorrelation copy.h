-(void)setOCRCorrelation
			:(OCRLetterData *)letterBase1_ 
			:(OCRVectorData *)vectorBase1_ 
			:(OCRLetterData *)letterBase2_ 
			:(OCRVectorData *)vectorBase2_ 
			:(short)currentRecord_{
//compare all letter on pecha with letter in OCRBase. Main point for letter recognition
//cout<<"start correlation"<<endl;
//******************************************set data**********************************************************************
short vIndTest, correlation,i,record,testVectorCount;
short maxCorrelationRecord=0;
short maxCorrelation=0;
OCRPoint letterCentreTest;

						//letterBase1_[record] model letter
						//letterBase2__[currentRecord_] test letter
						vIndTest=letterBase2_[currentRecord_].vInd;
						testVectorCount=letterBase2_[currentRecord_].vectorCount;
						letterCentreTest=letterBase2_[currentRecord_].letterCentre;
						//cout<<"testVectorCount"<<testVectorCount<<endl;
						//***************************************** actual correlation************************************************************

						//************first we compare test letter with all root model letters in base
	if(letterBase2_[currentRecord_].correlation<150){

for(record=0;record<=letterBase1_[0].allLettersCount;record++){  //for all letters in OCR base
//cout<<"letterBase1_[record].contour"<<(short)letterBase1_[record].contour<<endl;
			if(letterBase1_[record].contour==3){// first we must recognise root letter                               
				// if model letter length adequate test letter length 
								
				if(letterBase1_[record].angLength>=letterBase2_[currentRecord_].angLength-letterBase2_[currentRecord_].angLength/4&&
				letterBase1_[record].angLength<=letterBase2_[currentRecord_].angLength+letterBase2_[currentRecord_].angLength/4){


						correlation=[self setLimitCorrelation //first correlation method is correlation by limit around model letter points
									:letterBase1_ 
									:vectorBase1_ 
									:letterBase2_ 
									:vectorBase2_ 
									:record
									:currentRecord_];
				correlation=correlation*100/letterBase2_[currentRecord_].vectorSum;  //cout<<"OCRcorrelation="<<correlation<<endl; //percent all vectors in limit with sum of all vector's length in test letter						
                               
				if (correlation >70&&letterBase1_[record].letterSetCount>1){// we found correlation with root letter.  we start method for recognition all members of letterSet this root letter
						correlation=correlation+[self letterSetCorrelation
									:letterBase1_ 
									:vectorBase1_ 
									:letterBase2_ 
									:vectorBase2_ 
									:record
									:currentRecord_];
				} 
				//if(correlation>=70){  //if correlation more then limit we start more accurat correlation method
								  //correlation=[self setContourCorrelation
										//:letterBase1_ 
										//:vectorBase1_ 
										//:letterBase2_ 
										//:vectorBase2_ 
										//:record 
										//:currentRecord_
										//:0];}
						if(correlation >maxCorrelation){maxCorrelation=correlation;  //if we found better correlation with letter in base
						maxCorrelationRecord=record;
						}
									   
				//cout <<"maxCorrelationRecord="<<maxCorrelationRecord<<" maxCorrelation="<<maxCorrelation<<endl;
				 //cout<<" vInd"<<letterBase2_[record].vInd<<" indexLen"<<indexLen<<endl;
                                }//end if(letterBase2_[record].angLength
								
}//if(letterBase1_[record].contour==3)
				
}//end for(record=;
for(i=0;i<20;i++)letterBase2_[currentRecord_].name[i]=letterBase1_[maxCorrelationRecord].name[i];
letterBase2_[currentRecord_].correlation=maxCorrelation; //test letter now has max correlation value with letters in OCR base
				}// if(letterBase2_[currentRecord_].correlation<95)

}//end method********************************************************
