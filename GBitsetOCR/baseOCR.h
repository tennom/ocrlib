int intSortY(id num1, id num2, void *context){
    int v1 =[[num1 objectForKey:@"YMCenter"]intValue];
    int v2 =[[num2 objectForKey:@"YMCenter"]intValue];
    if (v1 < v2)
        return NSOrderedAscending;
    else if (v1 > v2)
        return NSOrderedDescending;
    else
        return NSOrderedSame;
}

int intSortX(id num1, id num2, void *context){
    int v1 =[[num1 objectForKey:@"XMCenter"]intValue];
    int v2 =[[num2 objectForKey:@"XMCenter"]intValue];
    if (v1 > v2)
        return NSOrderedAscending;
    else if (v1 < v2)
        return NSOrderedDescending;
    else
        return NSOrderedSame;
}

-(void)readLineOCR{

short baseCount;
baseCount=vectorBase[0].allContourCount;
	NSArray *srtStrArray;	
	mainGrammarBase=[[NSMutableArray new]retain];
for(lineNum=0;lineNum<=lineCount;lineNum++){//for all strokes		
	strokeArray=[[NSMutableArray alloc]init];
		        for(record=0;record<baseCount;record++){
			dl=vectorBase[record].stringNum;
					if(dl==lineNum){//cout<<" dl"<<dl<<" rec"<<record;
					//now we convert C-Structure in NSObject
					   dictRecord = [NSMutableDictionary dictionaryWithObjectsAndKeys:
					   [NSNumber numberWithShort:vectorBase[record].letterCenter.x], @"XMCenter",
					   [NSNumber numberWithShort:vectorBase[record].letterCenter.y], @"YMCenter",
					   [NSNumber numberWithShort:vectorBase[record].xMin], @"xMin",
					   [NSNumber numberWithShort:vectorBase[record].xMax], @"xMax",
					   [NSNumber numberWithShort:vectorBase[record].yMax], @"yMax",	
					   [NSNumber numberWithShort:vectorBase[record].yMin], @"yMin",
					   [NSNumber numberWithShort:vectorBase[record].correlation], @"cVal",
					   [NSNumber numberWithShort:0], @"status",  //status for grammar recognition
					   [NSNumber numberWithShort:vectorBase[record].angLength], @"angLength",
					   [NSNumber numberWithShort:vectorBase[record].contourIndex], @"contourIndex",
					   [NSString stringWithFormat:@"%s",vectorBase[record].name], @"name",					    	   	   
					   nil];    		   
                                          [strokeArray addObject:dictRecord];										
					}
        
	                }   // for(record=0;record<[vectorBase count]-1;record++)
					//cout<<"[strokeArray]"<<[strokeArray count]<<endl;
	   if ([strokeArray count]>0){
			srtStrArray=[[NSArray alloc]init];
			srtStrArray=[strokeArray sortedArrayUsingFunction:intSortX context:NULL];  //now vectorBase sorted by X
			//cout<<"[srtStrArray]"<<[srtStrArray count]<<endl;
						for (n=[srtStrArray count]-1;n>=0;n--){
						[mainGrammarBase addObject:[srtStrArray objectAtIndex:n]];
					}
                         lt =(char)rint(10);  //make new line
			//str=(@"newline");
			str=[NSString stringWithFormat:@"%c", lt];
			dictRecord = [NSMutableDictionary dictionaryWithObjectsAndKeys:
						   //[NSNumber numberWithShort:[vectorBase count]], @"idNum",
						   //[NSNumber numberWithShort:angLength], @"angLength",
					   //[NSNumber numberWithShort:startDirection], @"stDir",
					   [[srtStrArray objectAtIndex:0] objectForKey:@"XMCenter"], @"XMCenter",
					   [[srtStrArray objectAtIndex:0] objectForKey:@"YMCenter"], @"YMCenter",
					   [[srtStrArray objectAtIndex:0] objectForKey:@"xMin"], @"xMin",
					   [[srtStrArray objectAtIndex:0] objectForKey:@"xMax"], @"xMax",
					   [[srtStrArray objectAtIndex:0] objectForKey:@"yMax"], @"yMax",	
					   [[srtStrArray objectAtIndex:0] objectForKey:@"yMin"], @"yMin",
					   [NSNumber numberWithShort:1], @"cVal",
					   [NSNumber numberWithShort:0], @"angLength",
					   //strRecInt, @"recInt", 	   
					   //strRecIns, @"recDif", 
					   str, @"name", 	   	   
					   nil];    		   
		        [mainGrammarBase addObject:dictRecord];
		}// if ([strokeArray count]>0){
}//for(lineNum=0;lineNum<lineCount;lineNum++){

}///////////////////////////////////*//end method

-(void)setStroke{
//cout<<"line1="<<textOCRData.tLine[0]<<" line2="<<textOCRData.tLine[1]<<" line3="<<textOCRData.Line[2]<<endl;
deltaX=textOCRData.deltaX; lineCount=textOCRData.lineCount; direction=textOCRData.direction; //cout<<"deltaX="<<deltaX<<" lineCount="<<lineCount<<" direction="<<direction<<" firstY="<<textOCRData.tLine[0]<<endl;	
for(record=0;record<vectorBase[0].allContourCount;record++){
XMCenter=vectorBase[record].letterCenter.x;
YMCenter=vectorBase[record].letterCenter.y;
//cout<<"YMCenter1="<<YMCenter<<endl;
YMCenter=YMCenter-XMCenter/deltaX*direction;
//cout<<"YMCenter2="<<YMCenter<<endl;

dl=0;
while((YMCenter>(textOCRData.tLine[dl]-10))&&dl<lineCount){dl++;}
//cout<<YMCenter<<" ";cout<<"dl "<<dl<<endl;
vectorBase[record].stringNum=dl;
}

}///////////////////////////////////////////////////////////////////////

-(void)readTextOCR{   //read stroke from original Image in new array


}//end method//////////////////////////////////////////////////////**
