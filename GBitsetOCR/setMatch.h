short GBitsetOCR::setMatchCircle(short len, int L3, short x1, short y1, short x0, short y0, short x2, short y2){
short x0_,y0_,x2_,y2_,dx,dy,matchCount,iterationCount;
iterationCount=2; matchCount=0;
x2_=x2; y2_=y2; x0_=x0; y0_=y0; //start position
int print=0;
	
//@DC("setMatchCircle"<<END);
//          x0(noMatch)____________x2_(test)_______________x2(match)

while(iterationCount<512){
//@DC(" len="<<len<<" L3="<<L3<<" x1="<<x1<<" y1="<<y1<<" x0_="<<x0_<<" y0_="<<y0_<<" x2_="<<x2_<<" y2_="<<y2_<<"matchCount="<<matchCount<<" iterationCount="<<iterationCount<<END);
	dx=(x2_+x0_)/2; //@DC("dx="<<dx);
	dy=(y2_+y0_)/2; //cout <<" dy="<<dy<<END); 
	if(dx==x2_&&dy==y2_){ //@DC(" len="<<len<<"//__all match="<<matchCount<<" iterationCount="<<iterationCount<<END);
	return matchCount;}
	if((x1-dx)*(x1-dx)+(y1-dy)*(y1-dy)<L3){
	iterationCount*=2;
	matchCount+=len/iterationCount; //@DC(" len="<<len<<END);
        x2_=dx; y2_=dy;
	//@DC("/match/ new x2_="<<x2_<<" y2_="<<y2_<<END);	
	}else{ //not match
	 x0_=dx; y0_=dy; iterationCount*=2;
	 //@DC("/no match/ new x0_="<<x0_<<" y0_="<<y0_<<END);
	 } //shift "no match" position
}//while(iterationCount<16
//@DC(" len="<<len<<"//__all matchCount="<<matchCount<<" iterationCount="<<iterationCount<<END);
return matchCount;
}///////////////////////////////////////////////////////////////////////////////////////////////////

short  GBitsetOCR::setMatchCassidy(short len, int L3, short x1, short y1, short x3, short y3, short x0, short y0, short x2, short y2){
short x0_,y0_,x2_,y2_,dx,dy,matchCount,iterationCount;
iterationCount=2; matchCount=0;
x2_=x2; y2_=y2; x0_=x0; y0_=y0; //start position
	short print=0;
//@DC("setMatchCassidy"<<END);
//          x0(noMatch)____________x2_(test)_______________x2(match)

while(iterationCount<512){
//@DC(" len="<<len<<" L3="<<L3<<" x1="<<x1<<" y1="<<y1<<" x3="<<x3<<" y3="<<y3<<" x0_="<<x0_<<" y0_="<<y0_<<" x2_="<<x2_<<" y2_="<<y2_<<"matchCount="<<matchCount<<" iterationCount="<<iterationCount<<END);
	dx=(x2_+x0_)/2; //@DC("dx="<<dx);
	dy=(y2_+y0_)/2; //@DC(" dy="<<dy<<END); 
	if(dx==x2_&&dy==y2_){ //@DC(" len="<<len<<"//__all match="<<matchCount<<" iterationCount="<<iterationCount<<END);
	return matchCount;}
	if(((x1-dx)*(x1-dx)+(y1-dy)*(y1-dy))*((dx-x3)*(dx-x3)+(dy-y3)*(dy-y3))<L3){
	iterationCount*=2;
	matchCount+=len/iterationCount; 
        x2_=dx; y2_=dy;
	//@DC("/match="<<matchCount<<"/ new x2_="<<x2_<<" y2_="<<y2_<<" len="<<len/iterationCount<<" iterationCount="<<iterationCount<<END);	
	}else{ //not match
	 x0_=dx; y0_=dy; iterationCount*=2;
	 //@DC("/no match/ new x0_="<<x0_<<" y0_="<<(short)y0_<<END);
	 } //shift "no match" position
}//while(iterationCount<512
//@DC(" len="<<len<<"//__all match="<<matchCount<<" iterationCount="<<iterationCount<<END);
return matchCount;
}///////////////////////////////////////////////////////////////////////////////////////////////////






