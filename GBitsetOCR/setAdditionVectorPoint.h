-(void)setAdditionVectorPoint
		:(OCRLetterData *)letterBase_ 
		:(OCRVectorData *)vectorBase_ 
		:(short)record 
		:(short)index 
		:(short)nextBasePoint_{

vectorPoint[0].status=1; //count of points array
short limit=cLimit*10;  //limit equal 4 pix *10

//letterBase_[record].vInd //strart vector
//letterBase_[record].vectorCount=vectorCount; //all vectors count  in letter
short count; 
short kX,kY;
//cout<<"str="<<letterBase_[record].vInd<<" end="<<letterBase_[record].vInd+letterBase_[record].vectorCount<<" record="<<record<<endl;

for(index;index<nextBasePoint_;index++){
//for every vector between base points

	if(vectorBase_[index].length<limit){
	vectorPoint[vectorPoint[0].status]=vectorBase_[index].vStart;
	vectorPoint[vectorPoint[0].status].status=0;
	vectorPoint[0].status++;
	//cout<<"vectorBase_["<<index<<"].length="<<vectorBase_[index].length<<" limit="<<limit<<endl;
	continue;
	}
	if(vectorBase_[index].length<2*limit){
	vectorPoint[vectorPoint[0].status]=vectorBase_[index].vStart;
	vectorPoint[vectorPoint[0].status].status=0;
	vectorPoint[0].status++;
	vectorPoint[vectorPoint[0].status].x=(vectorBase_[index].vStart.x+vectorBase_[index].vEnd.x)/2;
	vectorPoint[vectorPoint[0].status].y=(vectorBase_[index].vStart.y+vectorBase_[index].vEnd.y)/2;
	vectorPoint[vectorPoint[0].status].status=0;
	vectorPoint[0].status++;
	//cout<<"vectorBase_["<<index<<"].length="<<vectorBase_[index].length<<" 2*limit="<<2*limit<<endl;
	continue;
	}
        
	kX=((vectorBase_[index].vEnd.x-vectorBase_[index].vStart.x)*100)/vectorBase_[index].length;
	kY=((vectorBase_[index].vEnd.y-vectorBase_[index].vStart.y)*100)/vectorBase_[index].length;
        //cout<<"vectorBase_["<<index<<"].vStart.x="<<vectorBase_[index].vStart.x<<" vectorBase_["<<index<<"].vEnd.x="<<vectorBase_[index].vEnd.x<<endl;
        //cout<<"vectorBase_["<<index<<"].vStart.y="<<vectorBase_[index].vStart.y<<" vectorBase_["<<index<<"].vEnd.y"<<vectorBase_[index].vEnd.y<<endl;

		count=0;
	while(limit*count<vectorBase_[index].length){
	//cout<<"vectorBase_["<<index<<"].length="<<vectorBase_[index].length<<" limit*count="<<limit*count<<" kX="<<kX<<" kY="<<kY<<endl;	  

        vectorPoint[vectorPoint[0].status].x=vectorBase_[index].vStart.x+limit*count*kX/100;
        vectorPoint[vectorPoint[0].status].y=vectorBase_[index].vStart.y+limit*count*kY/100;
	vectorPoint[vectorPoint[0].status].status=0;
        vectorPoint[0].status++;
	count++;
	}//end while

}//end for(index

//short i;
//for (i=1;i<vectorPoint[0].status;i++)
//cout<<"vectorPoint["<<i<<"].x="<<vectorPoint[i].x<<" vectorPoint["<<i<<"].y="<<vectorPoint[i].y<<endl;
}//////////////////////////////////////////////////////////////////////////////////////**
