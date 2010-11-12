-(void)sheRecognitionSort:(short)record{

short i,n,m,p,k,foundRecord;
short len[20];
short lenSort[20];
short index[20];
char indexLen;
short lenMax;
short lenCurrent=1000;
short vInd=contourRecordBase[record].vInd;
//cout<<"index"<<vInd<<" ";
indexLen=contourRecordBase[record].vectorCount;
//cout<<(short)indexLen<<" ";

if (indexLen>2){

//////////////**symple sort
//cout<<"   __  "<<endl;
for (p=0;p<indexLen;p++){index[p]=p; len[p]=vectorRecordBase[vInd+p].length; //cout<< len[p]<<" ";
} 
//cout<<endl;

for (p=0;p<indexLen;p++){
lenMax=-1;
		   for (n=0;n<indexLen;n++){ //cout <<index[n]<<" ";
		   //cout <<"len[n]"<<len[n]<<" lenMax"<<lenMax<<" "<<" lenCurrent"<<lenCurrent<<" n"<<n<<" index[n]"<<index[n]<<endl;
			if (len[n]<=lenCurrent&&len[n]>lenMax&&index[n]>=0) 
			{foundRecord=n; lenSort[p]=len[n]; lenMax=len[n]; }
		   }
index[foundRecord]=-1;
//cout <<lenCurrent<<" ";
lenCurrent=lenSort[p];
//cout<<endl;
//cout <<"p"<<p<<" lenSort[p]"<<lenSort[p]<<" "<<endl;
}
//cout<<"  _  "; for (p=0;p<indexLen;p++)cout<<lenSort[p]<<" "; ///
//cout<<endl;	 
///////////////////////**

short res=((lenSort[0]+lenSort[1])*100)/(lenSort[indexLen-1]+lenSort[indexLen-2]);  //cout<<" res"<<res<<endl; 		
                        if (res<=190){
                        ///cout<<res<<"res"<<" lenSort[0]"<<lenSort[0]<<" lenSort[1]"<<len[1]<<" lenSort[indexLen-1]"<<lenSort[indexLen-1]
			//<<" lenSort[indexLen-2]"<<lenSort[indexLen-2]; //cout<<"  _  "; //cout <<endl;;

			for(i=vInd;i<vInd+indexLen;i++){vectorRecordBase[i].correlation=1;}
			//cout <<vectorRecordBase[i].length<<" len";
			}//end if

}//end if 



}/////////////////////////////////////////////////////////////////////////////////////////////////////*
