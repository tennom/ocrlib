short GBitsetOCR::setCassidyCorrelation(OCRMatch *matchOCR){
/*
short i,letterInd,contourInd,vIndModel,vIndTest,ind, n, maxMatch, maxIndex, matchLength, k, maxMatchTest, maxMatchTestIndex;
short tM_[512];  //testMatchArray
short allMatchCount, vectorEndStatus;  //flag for joined match vectors
//DC("match count= "<<matchOCR[0].allMatchCount<<END);
short correlationCount;
short print=0;
DC(END<<END<<"// SET setCassidyCorrelation  _____________________________"<<END);

	
	for(ind=0;ind<matchOCR[0].allMatchCount;ind++){ //for all match
		DC(" matchOCR["<<ind<<"].vectorIndexModel="<<matchOCR[ind].vectorIndexModel<<" matchOCR["<<ind<<"].vectorIndexTest="<<matchOCR[ind].vectorIndexTest);
		DC(" matchOCR["<<ind<<"].status="<<matchOCR[ind].status<<" matchOCR["<<ind<<"].matchSumTest="<<matchOCR[ind].matchSumTest<<END);
    }	
	
////////////////////////////////////////////////////////_first we calculate match for model letter_/////////////////////////////////////////////////////////////////
for(correlationCount=0;correlationCount<2;correlationCount++){

for(i=0;i<matchOCR[0].allMatchCount;i++){   //for every tested match
DC(END<<"//_______NEW MODEL VECTOR ");
DC(" vIndModel="<<matchOCR[i].vectorIndexModel);
DC(" vectorIndexTest="<<matchOCR[i].vectorIndexTest);
DC(" matchSumTest="<<matchOCR[i].matchSumTest);
DC(" status="<<matchOCR[i].status<<END);
DC(" matchOCR[0].allMatchCount="<<matchOCR[0].allMatchCount<<END);
	
if(matchOCR[i].status>-1){ //if this match is free 
	vIndModel=matchOCR[i].vectorIndexModel; vIndTest=matchOCR[i].vectorIndexTest;
	allMatchCount=0; //matchLength=

////////////////for this model letter vector we check all test vector about more corresponded test vector
	
	DC("//_______glyph[0].v["<<vIndModel<<"].matchSum="<<glyph[0].v[vIndModel].matchSum<<" vIndTest"<<vIndTest<<END<<END);
/////////////////////////_//store all match for model vector in array_////////////////////////////////////////////////////////////////

////////////////for every vector in match
	for(ind=0;ind<matchOCR[0].allMatchCount;ind++){  	
		if(vIndModel==matchOCR[ind].vectorIndexModel
		//&&.vectorFlag==0){ //if vector match in one vector and it is free
		&&matchOCR[ind].status==0){
		//store all match for model vector in array	
		tM_[allMatchCount]=ind;  
		DC("		///________found_vIndTest="<<matchOCR[ind].vectorIndexTest<<" matchOCR[ind].matchSumTest="<<matchOCR[ind].matchSumTest<<" ind="<<ind<<" matchOCR[ind].status="<<matchOCR[ind].status<<END);
		allMatchCount++;
		}//if(matchPoint[ing].contourIndexModel=
	}//for(ind=0;ind
	DC("        //_________ALL_MATCH FOR vIndModel="<<vIndModel<<" ="<<allMatchCount<<END);
/////////////////////////_now set up the best match_////////////////////////////////////////////////////////////////////////////////////////////////////////
	maxMatch=0; 
	for(ind=0;ind<allMatchCount;ind++){
		if(matchOCR[tM_[ind]].matchSumTest>maxMatch){ //we has one biger match for model 
		DC("        //_________now test match tM_["<<ind<<"] "<<tM_[ind]<<END);
			maxMatchTest=0; maxMatchTestIndex=-1;
			for(n=0;n<matchOCR[0].allMatchCount;n++){// for all model match we choose bigest match for test vector		
				if(matchOCR[tM_[ind]].vectorIndexTest==matchOCR[n].vectorIndexTest){
				//DC("        //__________match found. "<<"contourIndexTest"<<matchOCR[tM_[ind]].contourIndexTest<<" vectorIndexTest"<<matchOCR[n].vectorIndexTest<<END);
				//DC("        //_________contourIndexModel="<<matchOCR[n].contourIndexModel<<" vectorIndexModel="<<matchOCR[n].vectorIndexModel<<" matchSumTest="<<matchOCR[n].matchSumTest<<END);
				        if(matchOCR[n].matchSumTest>maxMatchTest){
					maxMatchTestIndex=n;maxMatchTest=matchOCR[n].matchSumTest;}
				}//if(matchOCR[tM_[ind]]
			}//for(n=0;
		if(maxMatchTestIndex==tM_[ind]){
		maxMatch=matchOCR[tM_[ind]].matchSumTest; maxIndex=ind;}
		}//if(matchOCR[tM_[ind]].
	} //for(ind=0;ind<

	//if(maxMatch>0)DC("        //_________FOUND___maxMatch="<<maxMatch<<" maxIndex="<<maxIndex<<END);
if(maxMatch>0){	
	glyph[0].v[vIndModel].matchSum+=maxMatch; //store match in model vector
	if(glyph[0].v[vIndModel].matchSum>90)glyph[0].v[vIndModel].matchSum=100;
	
	DC("        //_________glyph[0].v["<<vIndModel<<"].matchSum="<<glyph[0].v[vIndModel].matchSum<<END);
	matchOCR[tM_[maxIndex]].status=glyph[0].v[vIndModel].matchSum;  //set flag for this match
	
        //DC("              found matchOCR["<<tM_[maxIndex]<<"].vectorIndexTest="<<matchOCR[tM_[maxIndex]].vectorIndexTest<<END);
	//DC("              found matchOCR["<<tM_[maxIndex]<<"].contourIndexTest="<<matchOCR[tM_[maxIndex]].contourIndexTest<<END);
	//DC("              found matchOCR["<<tM_[maxIndex]<<"].matchSumTest="<<matchOCR[tM_[maxIndex]].matchSumTest<<END);
		
/////////////////////////_now we has one test match vector. Does it enouth?_////////////////////////////////////////////////////
	matchLength=glyph[0].v[vIndModel].length;
	matchLength-=gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].length;
	gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].vectorFlag=vIndModel+1; //store for drowing
        gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].vectorInd=letterInd+1; //store for drowing
        gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].matchSum+=maxMatch;
	if(gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].matchSum>100){
	gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].matchSum=100;}	
for(ind=0;ind<matchOCR[0].allMatchCount;ind++){ //for all match
	if(matchOCR[tM_[maxIndex]].vectorIndexTest==matchOCR[ind].vectorIndexTest){
	matchOCR[ind].status+=gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].matchSum;}
}

/////////////////////////_if one vector isn't enouth. we try to found enother one_//////////////////////////////////////////
	
	if(matchLength>0){
		DC("              //____model matchLength="<<matchLength<<END<<END);
		
		DC("//START_SECOND_TEST_LETER_CHECK____/_glyph[0].v["<<vIndModel<<"].matchSum="<<glyph[0].v[vIndModel].matchSum<<END);
		
		vectorEndStatus=0;
		for(ind=0;ind<allMatchCount;ind++){
			if(abs(matchOCR[tM_[maxIndex]].vectorIndexTest-matchOCR[tM_[ind]].vectorIndexTest)==1|| //if it is joined vectors
			abs(matchOCR[tM_[maxIndex]].vectorIndexTest-matchOCR[tM_[ind]].vectorIndexTest)==gSrc.vectorCount-1){
			k=(matchLength*100)/glyph[0].v[vIndModel].length;
			matchLength-=gSrc.v[matchOCR[tM_[ind]].vectorIndexTest].length;	
			glyph[0].v[vIndModel].matchSum+=matchOCR[tM_[ind]].matchSumTest;
				if(glyph[0].v[vIndModel].matchSum>90)glyph[0].v[vIndModel].matchSum=100;	
			DC("matchOCR[tM_[ind]].matchSumTest="<<matchOCR[tM_[ind]].matchSumTest<<END);
			DC("found joined vectorIndexTest="<<matchOCR[tM_[ind]].vectorIndexTest<<"matchOCR["<<tM_[ind]<<"].matchSumTest="<<matchOCR[tM_[ind]].matchSumTest<<" ind="<<ind<<" matchLength="<<matchLength<<END);
			DC("glyph[0].v["<<vIndModel<<"].matchSum="<<glyph[0].v[vIndModel].matchSum<<END);
			gSrc.v[matchOCR[tM_[ind]].vectorIndexTest].vectorFlag=vIndModel+1; //store for drowing
			gSrc.v[matchOCR[tM_[ind]].vectorIndexTest].vectorInd=letterInd; //store for drowing
			gSrc.v[matchOCR[tM_[ind]].vectorIndexTest].matchSum+=
			(glyph[0].v[vIndModel].matchSum*k)/100;
			
			matchOCR[tM_[ind]].status+=matchOCR[tM_[ind]].matchSumTest;
			if(matchLength<=0)break;
			vectorEndStatus=1;
		        }
			DC("matchOCR["<<tM_[ind]<<"].vectorIndexTest="<<matchOCR[tM_[ind]].vectorIndexTest<<" vectorEndStatus="<<vectorEndStatus<<END);
			if(vectorEndStatus==2){//three joined vectors	
				if(abs(matchOCR[tM_[maxIndex]].vectorIndexTest-matchOCR[tM_[ind]].vectorIndexTest)==2|| //if it is joined vectors
				abs(matchOCR[tM_[maxIndex]].vectorIndexTest-matchOCR[tM_[ind]].vectorIndexTest)==gSrc.vectorCount-2){
				k=(matchLength*100)/glyph[0].v[vIndModel].length;	
				matchLength-=gSrc.v[matchOCR[tM_[ind]].vectorIndexTest].length;
				glyph[0].v[vIndModel].matchSum+=(matchOCR[tM_[ind]].matchSumTest*k)/100;
					if(glyph[0].v[vIndModel].matchSum>90)glyph[0].v[vIndModel].matchSum=100;
				DC("matchOCR["<<tM_[ind]<<"].matchSumTest="<<matchOCR[tM_[ind]].matchSumTest<<" ind="<<ind<<END);
				DC("glyph[0].v["<<vIndModel<<"].matchSum="<<glyph[0].v[vIndModel].matchSum<<END);
				gSrc.v[matchOCR[tM_[ind]].vectorIndexTest].vectorFlag=vIndModel+1; //store for drowing
				gSrc.v[matchOCR[tM_[ind]].vectorIndexTest].vectorInd=letterInd+1; //store for drowing
				gSrc.v[matchOCR[tM_[ind]].vectorIndexTest].matchSum+=
				(glyph[0].v[vIndModel].matchSum*k)/100;
				
				matchOCR[tM_[ind]].status+=matchOCR[tM_[ind]].matchSumTest;
				if(matchLength<=0)break;
				vectorEndStatus=1;
			}else{vectorEndStatus=0;}
			}//if(vectorEndStatus==2
			if(vectorEndStatus==1)vectorEndStatus++; //skip one cicle	
		}//for(ind=0;ind<allMatchCount;i
	}//if(matchLength>0

	if(glyph[0].v[vIndModel].matchSum>90)glyph[0].v[vIndModel].matchSum=100;
//DC("//_______start vIndModel="<<vIndModel<<" allMatchCount="<<allMatchCount<<END);

/////////////////////////now we has match for this model vector and this test vector. NEXT we decrease match sum for all match with this model vector/////////////  
	for(ind=0;ind<allMatchCount;ind++){
	
		if(gSrc.v[matchOCR[tM_[ind]].vectorIndexTest].vectorFlag==vIndModel+1)
		gSrc.v[matchOCR[tM_[ind]].vectorIndexTest].matchSum=glyph[0].v[vIndModel].matchSum;
	
	if(matchOCR[tM_[ind]].status==0){matchOCR[tM_[ind]].status=100; //erase all not valid match;
	matchOCR[tM_[ind]].matchSumTest=0;}
	if(matchOCR[tM_[maxIndex]].vectorIndexTest==matchOCR[tM_[ind]].vectorIndexTest){
	matchOCR[tM_[ind]].status=100;matchOCR[tM_[ind]].matchSumTest=0;}
	//DC("erase match vectorIndexTest="<<matchOCR[tM_[ind]].vectorIndexTest<<" vectorIndexModel="<<matchOCR[tM_[ind]].vectorIndexModel<<END);
	}



/////////////////////////_now we has one model match vector. Does it enouth?_////////////////////////////////////////////////////
	matchLength=gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].length;
	matchLength-=glyph[0].v[vIndModel].length;
	DC(" test matchLength="<<matchLength<<END);
/////////////////////////_if one vector isn't enouth. we try to found enother one_//////////////////////////////////////////
	if(matchLength>0){
	DC(" matchOCR[tM_[maxIndex]].vectorIndexModel="<<matchOCR[tM_[maxIndex]].vectorIndexModel<<END);
	vectorEndStatus=0;
		for(ind=0;ind<matchOCR[0].allMatchCount;ind++){ //for all match
		DC(" matchOCR["<<ind<<"].vectorIndexModel="<<matchOCR[ind].vectorIndexModel<<END);
			if(matchOCR[tM_[maxIndex]].vectorIndexTest==matchOCR[ind].vectorIndexTest&&
			(abs(matchOCR[tM_[maxIndex]].vectorIndexModel-matchOCR[ind].vectorIndexModel)==1|| //if it is joined vectors
			abs(matchOCR[tM_[maxIndex]].vectorIndexModel-matchOCR[ind].vectorIndexModel)==glyph[0].vectorCount-1)){
			k=(matchLength*100)/gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].length;
			matchLength-=glyph[0].v[matchOCR[ind].vectorIndexModel].length;	
			gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].matchSum+=matchOCR[ind].matchSumTest;
			DC(" matchOCR[tM_[ind]].matchSumTest="<<matchOCR[ind].matchSumTest<<" matchSum="<<gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].matchSum<<END);
				if(gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].matchSum>100){
				gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].matchSum=100;}
				
			//DC("matchOCR["<<ind<<"].matchSumTest="<<matchOCR[ind].matchSumTest<<" ind="<<ind<<END);
			glyph[0].v[matchOCR[ind].vectorIndexModel].matchSum+=
			(gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].matchSum*k)/100;
			if(glyph[0].v[matchOCR[ind].vectorIndexModel].matchSum>100){
			glyph[0].v[matchOCR[ind].vectorIndexModel].matchSum=100;}
			DC("glyph[0].v["<<matchOCR[ind].vectorIndexModel<<"].matchSum="<<glyph[0].v[matchOCR[ind].vectorIndexModel].matchSum<<END);
			
			matchOCR[ind].status+=glyph[0].v[matchOCR[ind].vectorIndexModel].matchSum;
			if(matchLength<=0)break;
			vectorEndStatus=1;
			}
			if(vectorEndStatus==2){
				if(matchOCR[tM_[maxIndex]].vectorIndexTest==matchOCR[ind].vectorIndexTest&&
				(abs(matchOCR[tM_[maxIndex]].vectorIndexModel-matchOCR[ind].vectorIndexModel)==2|| //if it is joined vectors
				abs(matchOCR[tM_[maxIndex]].vectorIndexModel-matchOCR[ind].vectorIndexModel)==glyph[0].vectorCount-2)){
				k=(matchLength*100)/gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].length;	
				matchLength-=glyph[0].v[matchOCR[ind].vectorIndexModel].length;
				gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].matchSum+=matchOCR[ind].matchSumTest;
					if(gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].matchSum>100){
					gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].matchSum=100;}
					
				//DC("matchOCR["<<ind<<"].matchSumTest="<<matchOCR[ind].matchSumTest<<" ind="<<ind<<END);
				glyph[0].v[matchOCR[ind].vectorIndexModel].matchSum+=
				(gSrc.v[matchOCR[tM_[maxIndex]].vectorIndexTest].matchSum*k)/100;
				if(glyph[0].v[matchOCR[ind].vectorIndexModel].matchSum>90){
				glyph[0].v[matchOCR[ind].vectorIndexModel].matchSum=100;}
				DC("glyph[0].v["<<matchOCR[ind].vectorIndexModel<<"].matchSum="<<glyph[0].v[matchOCR[ind].vectorIndexModel].matchSum<<END);
				
				matchOCR[ind].status+=glyph[0].v[matchOCR[ind].vectorIndexModel].matchSum;
				if(matchLength<=0)break;
				vectorEndStatus=1;
				}else{vectorEndStatus=0;}
			
			}//if(vectorEndStatus==1)
			if(vectorEndStatus==1)vectorEndStatus++; //skip one cicle
		}//for(ind=0;ind<matchOCR[0].allMatchCount;
	}//if(matchLength>0)
	
	
}//if(maxMatch>0){
}//if(matchOCR[i].status==0)	
}//for(i=0;i<matchPoint[0]
}//for(correlationCount=0

	
	//for(ind=0;ind<matchOCR[0].allMatchCount;ind++){ //for all match
		DC(" matchOCR["<<ind<<"].vectorIndexModel="<<matchOCR[ind].vectorIndexModel<<" matchOCR["<<ind<<"].vectorIndexTest="<<matchOCR[ind].vectorIndexTest);
		DC(" matchOCR["<<ind<<"].status="<<matchOCR[ind].status<<" matchOCR["<<ind<<"].matchSumTest="<<matchOCR[ind].matchSumTest<<END);
	//}
	
	
DC(END<<"// END SET setCassidyCorrelation  _____________________________");
*/	
return 1;
}
