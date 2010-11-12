-(void)textReaderOCR{

///////////////////////////////////////////////////////////////this file is main point for grammar text normalisation
//////////////////////////////////////////////// strOCR; //structure contain indexes in OCR Contour base sorted by line

/////////////////////////////////////////////////Vowel normalisation//////////////////////////////////////////////////////
for (record=0;record<strOCR.count;record++){
	//cout<<"vectorBase["<<strOCR.letter[record]<<"].contour="<<(short)vectorBase[strOCR.letter[record]].contour<<endl;
	//cout<<"strOCR.letter["<<record<<"].recordFlag="<<vectorBase[strOCR.letter[record]].recordFlag<<endl;
	if(vectorBase[strOCR.letter[record]].OCRStatus==1&&vectorBase[strOCR.letter[record]].recordFlag!=5){
	vectorBase[strOCR.letter[record]].recordFlag=5;
	//cout<<"||||||||||"<<record<<"||||||||||||"<<vectorBase[strOCR.letter[record]].name<<endl;
	[self setVowelLetter:record];
	}
}

for (record=0;record<strOCR.count;record++){
	//cout<<"vectorBase["<<strOCR.letter[record]<<"].contour="<<(short)vectorBase[strOCR.letter[record]].contour<<endl;
	if(vectorBase[strOCR.letter[record]].contour==3){
	//cout<<"||||||||||"<<record<<"||||||||||||"<<vectorBase[strOCR.letter[record]].name<<endl;
	[mainString appendString:[NSString stringWithFormat:@"%s", vectorBase[strOCR.letter[record]].name] ];
	//for(i=0;i<5;i++)cout<<(short) vectorBase[strOCR.letter[record]].name[i]; //cout<<endl;
	}
}//for (record=0

}//end method/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

-(void)setVowelLetter:(short)letterIndex{
OCRPoint letterCenterVowel, letterCenterTest;
short resIndex;

letterCenterVowel=vectorBase[strOCR.letter[letterIndex]].letterCenter;
resMin=1024;

if(vectorBase[strOCR.letter[letterIndex]].name[0]=='u'){ //down letter

//cout <<"record="<<strOCR.letter[letterIndex]<<" letterCenterVowel.y="<<letterCenterVowel.y<<" letterCenterVowel.x="<<letterCenterVowel.x<<" name="<<vectorBase[strOCR.letter[letterIndex]].name<<endl;
				for(i=0;i<strOCR.count;i++){
					if (vectorBase[strOCR.letter[i]].OCRStatus==3||vectorBase[strOCR.letter[i]].OCRStatus==5||
					vectorBase[strOCR.letter[i]].OCRStatus==6||vectorBase[strOCR.letter[i]].OCRStatus==0
					&&vectorBase[strOCR.letter[i]].contour==3){//letter/root/sanskrit/ not set
					letterCenterTest=vectorBase[strOCR.letter[i]].letterCenter;
							if(letterCenterTest.y<letterCenterVowel.y){
							res=(letterCenterVowel.y-letterCenterTest.y)/2+abs(letterCenterTest.x-letterCenterVowel.x);
										if( res<resMin){
										resMin=res;
										resIndex=i;   //now we found root letter for  "o" (may be:)
										}
							}//if(YMCenter1>YMCenter)
					}//if (vectorBase
				}//for(i=0;i<[textArray count]-1;i++)
	//cout <<"resIndex="<<resIndex<<" resMin="<<resMin<<" y="<<vectorBase[strOCR.letter[resIndex]].letterCenter.y
	//<<" x="<<vectorBase[strOCR.letter[resIndex]].letterCenter.x<<" name"<<vectorBase[strOCR.letter[resIndex]].name<<endl;
	[self deleteVowel:resIndex]; 
	if(letterIndex<resIndex){[self insertLetter:strOCR.letter[letterIndex] :resIndex]; [self deleteLetter:letterIndex];}else{
	[self insertLetter:strOCR.letter[letterIndex] :resIndex]; [self deleteLetter:letterIndex+1]; }

}else{ //upper letter
//cout <<"record="<<strOCR.letter[letterIndex]<<" letterCenterVowel.y="<<letterCenterVowel.y<<" letterCenterVowel.x="<<letterCenterVowel.x<<" name="<<vectorBase[strOCR.letter[letterIndex]].name<<endl;
				for(i=0;i<strOCR.count;i++){
				//cout<<" vectorBase["<<strOCR.letter[i]<<"].name[0]="<<"|"<<vectorBase[strOCR.letter[i]].name[0]<<"|"<<endl;
					if (vectorBase[strOCR.letter[i]].OCRStatus==3||vectorBase[strOCR.letter[i]].OCRStatus==5||
					vectorBase[strOCR.letter[i]].OCRStatus==6||vectorBase[strOCR.letter[i]].OCRStatus==0
					&&vectorBase[strOCR.letter[i]].contour==3&&vectorBase[strOCR.letter[i]].name[0]!=' '){//letter/root/sanskrit/ not set
					//cout<<" vectorBase["<<strOCR.letter[i]<<"].name[0]="<<"|"<<(short)vectorBase[strOCR.letter[i]].name[0]<<"|"<<endl;
					letterCenterTest=vectorBase[strOCR.letter[i]].letterCenter;
							if(letterCenterTest.y>letterCenterVowel.y){
							res=(letterCenterTest.y-letterCenterVowel.y)/2+abs(letterCenterTest.x-letterCenterVowel.x);
										if( res<resMin){
										resMin=res;
										resIndex=i;   //now we found root letter for  "o" (may be:)
										}
							}//if(YMCenter1>YMCenter)
					}//if (vectorBase
				}//for(i=0;i<[textArray count]-1;i++)
	//cout <<"resIndex="<<resIndex<<" resMin="<<resMin<<" y="<<vectorBase[strOCR.letter[resIndex]].letterCenter.y
	//<<" x="<<vectorBase[strOCR.letter[resIndex]].letterCenter.x<<" name"<<vectorBase[strOCR.letter[resIndex]].name<<endl;
	//cout<<"strOCR.letter["<<letterIndex<<"].recordFlag="<<vectorBase[strOCR.letter[letterIndex]].recordFlag<<endl;
        [self deleteVowel:resIndex]; 
	if(letterIndex<resIndex){[self insertLetter:strOCR.letter[letterIndex] :resIndex]; [self deleteLetter:letterIndex];}else{
	[self insertLetter:strOCR.letter[letterIndex] :resIndex]; [self deleteLetter:letterIndex+1]; }
}
}////////////////////////////////////////////////////////////////////////////////////////////////////////end method////////////////////////////////////////////////*

-(void)insertLetter:(short)value :(short)letterIndex{
					//cout<<"////////////////insert_letterIndex="<<letterIndex<<" value="<<value<<" strOCR.count="<<strOCR.count<<endl;
					for(i=strOCR.count;i>letterIndex;i--){
					//cout<<"i="<<i<<" strOCR.letter[i-1]="<<strOCR.letter[i-1]<<endl;				
					strOCR.letter[i]=strOCR.letter[i-1];
					}strOCR.count++;
					strOCR.letter[letterIndex+1]=value;
					
					//for(i=strOCR.count;i>=0;i--){				
					//cout<<"strOCR.letter["<<i<<"]="<<strOCR.letter[i]<<
					//" vectorBase[strOCR.letter[i]].name="<<vectorBase[strOCR.letter[i]].name<<endl;
					//}
					//cout<<"/////////////"<<endl;	

}//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

-(void)deleteLetter:(short)letterIndex{
					//cout<<"////////////////delete_letterIndex="<<letterIndex<<endl;
					for(i=letterIndex;i<strOCR.count;i++){				
					strOCR.letter[i]=strOCR.letter[i+1];
					}strOCR.count--;
					
					//for(i=strOCR.count;i>=0;i--){				
					//cout<<"strOCR.letter["<<i<<"]="<<strOCR.letter[i]<<
					//" vectorBase[strOCR.letter[i]].name="<<vectorBase[strOCR.letter[i]].name<<endl;
					//}	
        				
}//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

-(void)deleteVowel:(short)letterIndex{
					//cout<<"////////////////deleteVowel letterIndex="<<letterIndex<<endl;
					for(i=0;i<10;i++){	
					//cout<<(short)vectorBase[strOCR.letter[letterIndex]].name[i];			
						if(vectorBase[strOCR.letter[letterIndex]].name[i]=='a'){
						vectorBase[strOCR.letter[letterIndex]].name[i]=0;break;}
					}//cout<<endl;
        				
}//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



-(void)setWylieScript{
//NSString *letterStr1;

//for(i=0;i<[mainString length]-1;i++){}
//NSLog(mainString);

//++++++++++++++++vowels

//++++++++++++++++Dots	
[mainString replaceOccurrencesOfString:@"*" withString:@" " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
//
//}

[mainString replaceOccurrencesOfString:@";" withString:@" ; " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"/" withString:@" / " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];

[mainString replaceOccurrencesOfString:@"p'" withString:@"pa'" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"m'" withString:@"ma'" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"b'" withString:@"ba'" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" l/" withString:@" la/" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"dng" withString:@"dang" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];

[mainString replaceOccurrencesOfString:@" ls/" withString:@" las/" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" ls;" withString:@" las;" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" l;" withString:@" la;" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" ns;" withString:@" nas;" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];


[mainString replaceOccurrencesOfString:@" b/" withString:@" ba/" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" ns/" withString:@" nas/" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];

[mainString replaceOccurrencesOfString:@"  ls  " withString:@"  las  " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"  ls  " withString:@"  las  " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"  zb  " withString:@"  zab  " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" pr " withString:@" par " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" ps " withString:@" pas " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" bs " withString:@" bas " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" pr " withString:@" par " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" sm " withString:@" sam " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" ls " withString:@" las " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" lm " withString:@" lam " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"rng " withString:@" rang " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" gns " withString:@" gnas " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" nng " withString:@" nang " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" gng " withString:@" gang " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" gs " withString:@" gas " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" gsng " withString:@" gsang " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" br " withString:@" bar " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" nms " withString:@" nams " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" dbng " withString:@" dbang " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" cd " withString:@" cad " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" yng " withString:@" yang " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" mng " withString:@" mang " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" mr " withString:@" mar " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"dkr " withString:@"dkar " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"bsng" withString:@"bsang" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"mN" withString:@"maN" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"pd+" withString:@"pad+" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" ns " withString:@" nas " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" bzd " withString:@" bzad " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" bcs " withString:@" bcas " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" dg " withString:@" dg " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" yn " withString:@" yan " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" lg " withString:@" lag " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" rb " withString:@" rab " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" bsm " withString:@" bsam " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" bzng " withString:@" bzang " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" srb" withString:@" sarb " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" bdg " withString:@" bdag " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" cn " withString:@" can " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" ln " withString:@" lan " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" kr " withString:@" kar " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" dpg " withString:@" dpag " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" dpl " withString:@" dpal " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"bdz" withString:@"badz" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"sngs" withString:@"sngas" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" dr " withString:@" dar " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" dmr " withString:@" dmar " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" nd " withString:@" nad " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];

[mainString replaceOccurrencesOfString:@" l " withString:@" la " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" m " withString:@" ma " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" n " withString:@" na " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" k " withString:@" ka " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];

[mainString replaceOccurrencesOfString:@" p " withString:@" pa " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" r " withString:@" ra " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" b " withString:@" ba " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" s " withString:@" sa " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" g " withString:@" ga " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];


[mainString replaceOccurrencesOfString:@"khrakhra" withString:@"khra" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"khyakhra" withString:@"khya" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];

[mainString replaceOccurrencesOfString:@";" withString:@"; " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" ;" withString:@";" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"=" withString:@"= " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"  " withString:@" " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"  " withString:@" " options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" /  / " withString:@"/ /" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@" / / " withString:@"/ /" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];
[mainString replaceOccurrencesOfString:@"ng/" withString:@"ng /" options:NSLiteralSearch range: NSMakeRange(0,[mainString length])];

}//end method////////////////////////////////////////////////*






