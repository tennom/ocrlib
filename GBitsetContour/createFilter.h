-(void)createFilter:(vector<GP<vectorOCR> >&)vectorBase :(NSString *)srcString :(NSString *)filterString{

 //cout<<[srcString length]<<" "<<[filterString length];

char *angDiffRecord;
const char *strData=[srcString cStringUsingEncoding:1];
const char *strLetter;
short angLength=0;
char sign=-1;
short indexLetter=0;

i=0;
while(i<[srcString length]){
strLetter=strData+i;
if(*strLetter=='-'){sign=1;}
if(*strLetter!=' '&&(*strLetter!='-')){angDiff[indexLetter]=((char)*strLetter-48)*sign; sign=-1;angLength++;indexLetter++;}
i++;
//angDiffRecord[i]=angDiff[i]; //cout<<(short)angDiff[i]<<" ";
}
//cout<<[srcString length]<<"source length "<<index
//cout<<"contourCount"<<contourCount;
contourCount++;
//vectorBase[contourCount]->angLength=indexLetter;  //###

//for (i=0;i<indexLetter;i++){cout <<(short)angDiff[i]<<" ";}
//cout <<angLength<<"angLength";
//now angDiff  contain srcStrind data
//now me start make letterX, letterY array;

//short *letterX;
//short *letterY;

//letterX=vectorBase[contourCount].letterX;
//letterY=vectorBase[contourCount].letterY;
//angDiffRecord=vectorBase[contourCount].angDiff;
//angDiffSumRecord=vectorBase[contourCount].angDiffSum;

short dir=0;
//short res=0;
angX[0]=0;
angY[0]=0;
for (i=1;i<angLength-1;i++){
//letterX[i-1]=angX[i-1];
//letterY[i-1]=angY[i-1];
angDiffRecord[i-1]=angDiff[i]*-1; //pack data for drawing
//cout<<"angDiff[i] "<<(short)angDiff[i]<<" dir "<<dir<<" "<<letterX[i-1]<<" | "<<letterY[i-1]<<endl;
if (dir==0){
if(angDiff[i]==4){dir=4;angX[i]=angX[i-1]-1;angY[i]=angY[i-1];continue;}  
if(angDiff[i]==3){dir=3;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==2){dir=2;angX[i]=angX[i-1];angY[i]=angY[i-1]-1; continue;}
if(angDiff[i]==1){dir=1;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==0){dir=0;angX[i]=angX[i-1]+1;angY[i]=angY[i-1];continue;}
if(angDiff[i]==-1){dir=7;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==-2){dir=6;angX[i]=angX[i-1];angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==-3){dir=5;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==-4){dir=4;angX[i]=angX[i-1]-1;angY[i]=angY[i-1];continue;} 
}
if (dir==1){
if(angDiff[i]==4){dir=5;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==3){dir=4;angX[i]=angX[i-1]-1;angY[i]=angY[i-1];continue;}   
if(angDiff[i]==2){dir=3;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==1){dir=2;angX[i]=angX[i-1];angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==0){dir=1;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==-1){dir=0;angX[i]=angX[i-1]+1;angY[i]=angY[i-1];continue;} 
if(angDiff[i]==-2){dir=7;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==-3){dir=6;angX[i]=angX[i-1];angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==-4){dir=5;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]+1;continue;} 
}

if (dir==2){
if(angDiff[i]==4){dir=6;angX[i]=angX[i-1];angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==3){dir=5;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==2){dir=4;angX[i]=angX[i-1]-1;angY[i]=angY[i-1];continue;}   
if(angDiff[i]==1){dir=3;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==0){dir=2;angX[i]=angX[i-1];angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==-1){dir=1;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==-2){dir=0;angX[i]=angX[i-1]+1;angY[i]=angY[i-1];continue;} 
if(angDiff[i]==-3){dir=7;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==-4){dir=6;angX[i]=angX[i-1];angY[i]=angY[i-1]+1;continue;} 
}
if (dir==3){
if(angDiff[i]==4){dir=7;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==3){dir=6;angX[i]=angX[i-1];angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==2){dir=5;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==1){dir=4;angX[i]=angX[i-1]-1;angY[i]=angY[i-1];continue;}   
if(angDiff[i]==0){dir=3;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==-1){dir=2;angX[i]=angX[i-1];angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==-2){dir=1;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==-3){dir=0;angX[i]=angX[i-1]+1;angY[i]=angY[i-1];continue;} 
if(angDiff[i]==-4){dir=7;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]+1;continue;} 
}
if (dir==4){
if(angDiff[i]==4){dir=0;angX[i]=angX[i-1]+1;angY[i]=angY[i-1];continue;} 
if(angDiff[i]==3){dir=7;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==2){dir=6;angX[i]=angX[i-1];angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==1){dir=5;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==0){dir=4;angX[i]=angX[i-1]-1;angY[i]=angY[i-1];continue;}   
if(angDiff[i]==-1){dir=3;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==-2){dir=2;angX[i]=angX[i-1];angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==-3){dir=1;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==-4){dir=0;angX[i]=angX[i-1]+1;angY[i]=angY[i-1];continue;} 
}
if (dir==5){
if(angDiff[i]==4){dir=1;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==3){dir=0;angX[i]=angX[i-1]+1;angY[i]=angY[i-1];continue;} 
if(angDiff[i]==2){dir=7;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==1){dir=6;angX[i]=angX[i-1];angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==0){dir=5;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==-1){dir=4;angX[i]=angX[i-1]-1;angY[i]=angY[i-1];continue;}   
if(angDiff[i]==-2){dir=3;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==-3){dir=2;angX[i]=angX[i-1];angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==-4){dir=1;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]-1;continue;}
}
if (dir==6){
if(angDiff[i]==4){dir=2;angX[i]=angX[i-1];angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==3){dir=1;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==2){dir=0;angX[i]=angX[i-1]+1;angY[i]=angY[i-1];continue;} 
if(angDiff[i]==1){dir=7;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==0){dir=6;angX[i]=angX[i-1];angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==-1){dir=5;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==-2){dir=4;angX[i]=angX[i-1]-1;angY[i]=angY[i-1];continue;}   
if(angDiff[i]==-3){dir=3;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==-4){dir=2;angX[i]=angX[i-1];angY[i]=angY[i-1]-1;continue;}
}
if (dir==7){
if(angDiff[i]==4){dir=3;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==3){dir=2;angX[i]=angX[i-1];angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==2){dir=1;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]-1;continue;}
if(angDiff[i]==1){dir=0;angX[i]=angX[i-1]+1;angY[i]=angY[i-1];continue;} 
if(angDiff[i]==0){dir=7;angX[i]=angX[i-1]+1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==-1){dir=6;angX[i]=angX[i-1];angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==-2){dir=5;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]+1;continue;} 
if(angDiff[i]==-3){dir=4;angX[i]=angX[i-1]-1;angY[i]=angY[i-1];continue;}   
if(angDiff[i]==-4){dir=3;angX[i]=angX[i-1]-1;angY[i]=angY[i-1]-1;continue;}
}
}//end for
angX[i]=angX[i-1];
angY[i]=angY[i-1];

//letterX[i]=angX[i];
//letterY[i]=angY[i]; 

////////////////////////////////////////////////
[self baseFilter];   //main point for letter nice shape. Fitness and sayna;  
////////////////////////////////////////////////

//angDiffRecord=vectorBase[0].angDiffSum;
//for (i=1;i<angLength-1;i++){
//angDiffRecord[i-1]=angDiffSum[i]*-1;  //pack data for drawing
//cout<<(short)angDiffSum[i];
//}
////////////////////////////////////////////////////////////////
	[self setVector:vectorBase: 0]; //reading atributes 
////////////////////////////////////////////////////////////////


}/////////////////////////////////////////////////////////////////////////////////////////**
