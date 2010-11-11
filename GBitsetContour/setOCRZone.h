-(void)setOCRZone{

short xLimit1,xLimit2,yLimit1,yLimit2,delta;
delta=(xMax-xMin)/3;
xLimit1=xMin+delta;
xLimit2=xMin+delta+delta;
delta=(yMax-yMin)/3;
yLimit1=yMin+delta;
yLimit2=yMin+delta+delta;
//cout<<"xMin="<<xMin<<" xMax="<<xMax<<" xLimit1="<<xLimit1<<" xLimit2="<<xLimit2<<" yLimit1="<<yLimit1<<" yLimit2="<<yLimit2<<endl;

for ( i = 1; i<ang.size()-1; i++ ) {
if(angX[i]<xLimit2){
	if(angX[i]<xLimit1){
		if(angY[i]<yLimit2){
		if(angY[i]<yLimit1){OCRZone[i]=1;}else{OCRZone[i]=4;}
		}else{OCRZone[i]=7;}

	}else{//if(angX[i]<xLimit1)
		if(angY[i]<yLimit2){
		if(angY[i]<yLimit1){OCRZone[i]=2;}else{OCRZone[i]=5;}
		}else{OCRZone[i]=8;}
	}
}else{//if(angX[i]<xLimit2)
	if(angY[i]<yLimit2){
	if(angY[i]<yLimit1){OCRZone[i]=3;}else{OCRZone[i]=6;}
	}else{OCRZone[i]=9;}
}//if(angX[i]<xLimit2)
}//end for
}/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
