 short GBitsetOCR::testCassidyMatch (OCRMatch *matchPoint,OCRMatch *matchOCR){
/*
short max1;
short i,index;
short print=0;

index=0;

short matchLenTest,matchAngTest, matchCenterTest,  matchSumTest;
short vIndModel, vIndTest;

DC("//TEST_MATCH_______matchPoint[0].allMatchCount="<<matchPoint[0].allMatchCount<<END);


for(i=0;i<matchPoint[0].allMatchCount;i++){
	DC("	matchPoint["<<i<<"].matchCount="<<matchPoint[i].matchCount<<END);
	DC("	matchPoint["<<i<<"].vectorIndexModel="<<matchPoint[i].vectorIndexModel<<END);
	DC("	matchPoint["<<i<<"].vectorIndexTest="<<matchPoint[i].vectorIndexTest<<END);
	DC("	matchPoint["<<i<<"].status="<<matchPoint[i].status<<END<<END<<END);
        max1=0;

	vIndModel=matchPoint[i].vectorIndexModel; vIndTest=matchPoint[i].vectorIndexTest;

	//_______________match Length for test
	if(matchPoint[i].matchCount<glyph->v[vIndModel].length){
	matchLenTest=(matchPoint[i].matchCount*100)/glyph->v[vIndModel].length;}else{
	matchLenTest=(glyph->v[vIndModel].length*100)/matchPoint[i].matchCount;}
	if(matchLenTest>85)matchLenTest=100;

		DC("matchLenTest="<<matchLenTest<<" gSrc.v["<<vIndTest<<"].length="<<gSrc.v[vIndTest].length<<END);
		//DC("glyph[0].v["<<vIndModel<<"].length="<<glyph.v[vIndModel].length<<END);
	if(matchLenTest>85)matchLenTest=100;
	if(matchLenTest<15)matchLenTest=0;

			DC("matchLenTest="<<matchLenTest<<END);
        //_______________match angle for test
	matchAngTest=abs(gSrc.v[vIndTest].vectorAngle-glyph->v[vIndModel].vectorAngle);
	if(matchAngTest>315)matchAngTest=360-matchAngTest;
	matchAngTest=(85-matchAngTest)*100/85; //(% from angle limit)
	if(matchAngTest>85)matchAngTest=100;
	if(matchAngTest<65)matchAngTest/=4;
			DC("matchAngTest="<<matchAngTest<<END);
	//_______________match endAngle for test
	matchCenterTest=matchPoint[i].centerDist;
	if(matchCenterTest>85)matchCenterTest=100;
			DC("matchCenterTest="<<matchCenterTest<<END);
	//_______________sum all match for test
	DC(" vIndModel="<<vIndModel<<" vIndTest="<<vIndTest<<END);

	if(matchCenterTest>0&&matchAngTest>0){
		matchSumTest=(short)sqrt((float)matchAngTest*matchCenterTest); DC(" matchSumTest1="<<matchSumTest<<END);
	    //matchSumTest=(short)((matchAngTest+matchCenterTest)/2); //DC(" matchSumTest1="<<matchSumTest<<END);

	}else{
		matchSumTest=0;
	}
	if(matchLenTest>0&&matchSumTest>0){
	    matchSumTest=(short)sqrt((float)matchLenTest*matchSumTest);
	    //matchSumTest=(short)((matchLenTest+matchSumTest)/2); //DC(" matchSumTest2="<<matchSumTest<<END);
	}
	if(matchSumTest>90)matchSumTest=100;

	if(matchAngTest==100&&matchCenterTest==100&&matchLenTest>65)matchSumTest=100;
	if(matchLenTest==100&&matchCenterTest==100&&matchAngTest>65)matchSumTest=100;
	if(matchLenTest==100&&matchAngTest==100&&matchCenterTest>65)matchSumTest=100;
	if(matchAngTest<20)matchSumTest=0;
	if(matchLenTest<20)matchSumTest=0;
	if(matchCenterTest<20)matchSumTest=0;


	DC(" matchSumTest2="<<matchSumTest<<END);

		//matchSumTest=(matchAngTest+matchCenterTest+matchLenTest)/3;
	DC("i="<<i<<END);
	if(matchPoint[i].matchCount)DC("@@@@@@////////matchPoint["<<i<<"].matchCount="<<matchPoint[i].matchCount<<END);
	matchOCR[matchOCR[0].allMatchCount].vectorIndexModel=vIndModel;
		DC("matchOCR["<<matchOCR[0].allMatchCount<<"].vIndModel"<<matchOCR[matchOCR[0].allMatchCount].vectorIndexModel<<END);
	matchOCR[matchOCR[0].allMatchCount].vectorIndexTest=vIndTest;
		DC("matchOCR["<<matchOCR[0].allMatchCount<<"].vIndTest"<<matchOCR[matchOCR[0].allMatchCount].vectorIndexTest<<END);
	matchOCR[matchOCR[0].allMatchCount].matchCount=matchPoint[i].matchCount;
		DC("matchOCR["<<matchOCR[0].allMatchCount<<"].matchCount"<<matchOCR[matchOCR[0].allMatchCount].matchCount<<END);
	matchOCR[matchOCR[0].allMatchCount].matchSumTest=matchSumTest;
		DC("matchOCR["<<matchOCR[0].allMatchCount<<"].matchSumTest"<<matchOCR[matchOCR[0].allMatchCount].matchSumTest<<END);
	matchOCR[matchOCR[0].allMatchCount].status=0;
	matchOCR[0].allMatchCount++;
	DC("i1="<<i<<END);
}

   DC("////////////////////////////////////////////////////////matchOCR[0].allMatchCount="<<matchOCR[0].allMatchCount<<END);
*/
 return 1;
}////////////////////////////////////////////////////////////////////////////////////////////////////////////









