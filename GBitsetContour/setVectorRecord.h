void memSet::setVectorRecord(){
	//in this method we receive the data about vector, test it and if vector is valid, write it in base.
	//c_out<<"//________________new vector "<<vectorCount<<endl;
	short length,vectXStart,vectXEnd,vectYStart,vectYEnd, vAngXStart,vAngYStart,vIndex, triangleBase,vStartIndex,vEndIndex;
	int lengthSum, hLimit;
	int t1,t2;
	short x1,y1,y3,x3,angLimit;
	short vectorLimitNormal=vectorLimit/4;   //need for small text
	short angLength=ang.size();
	
	vectXStart=angX[vectorMarker[vectorCount-1]];	//c_out<<"vectXStart="<<vectXStart<<endl;
	vectYStart=angY[vectorMarker[vectorCount-1]];	//c_out<<"vectYStart="<<vectYStart<<endl;
	vStartIndex=vectorMarker[vectorCount-1];		//c_out<<"vStartIndex="<<vStartIndex<<endl;
	vectXEnd=angX[vectorMarker[vectorCount]];		//c_out<<"vectXEnd="<<vectXEnd<<endl;
	vectYEnd=angY[vectorMarker[vectorCount]];		//c_out<<"vectYEnd="<<vectYEnd<<endl;
	vEndIndex=vectorMarker[vectorCount];			//cout<<"vEndIndex="<<vEndIndex<<endl;
	//cout<<"vectorCount="<<vectorCount<<endl;
	
	if(vectXStart>xMax)xMax=vectXStart;if(vectXStart<xMin)xMin=vectXStart;if(vectYStart>yMax)yMax=vectYStart;if(vectYStart<yMin)yMin=vectYStart;
	
	length=(short)sqrtA(((vectXStart-vectXEnd)*(vectXStart-vectXEnd)+(vectYStart-vectYEnd)*(vectYStart-vectYEnd))*100); //attention. length*10 increase Accuracy of short
	vIndex=vectorBase->size();
	//cout<<length<<"length"<<" vectorLimit="<<vectorLimit<<endl;
	
	///////////////////////**now we check length of this vector.
	//c_out<<"angLength="<<angLength<<" vectorLimit11="<<vectorLimit<<endl;
	//  need developed
	if(length>vectorLimitNormal||angLength<65||vectorMarker[vectorCount]==angLength-1){
		
		/////////////////////////now we start check angle between this vector and previous vector
		if(vectorCount>1){ 
			//x1,y1 - vector1 start
			//x2,y2 - end vector1, start vector2, zero point
			//x3,y3 -end vector 2
			//first calculate relativ coordinate
			vAngXStart=angX[vectorMarker[vectorCount-2]];
			vAngYStart=angY[vectorMarker[vectorCount-2]];
			
			
			x1=vAngXStart-vectXStart; //c_out<<"x1="<<x1<<endl;
			y1=vAngYStart-vectYStart; //c_out<<"y1="<<y1<<endl;
			x3=vectXEnd-vectXStart; //c_out<<"x3="<<x3<<endl;
			y3=vectYEnd-vectYStart; //c_out<<"y3="<<y3<<endl;
			
			//if((x1*x1+y1*y1)*(x3*x3+y3*y3)<0)c_out<<"x1="<<x1<<" y1="<<y1<<" x3="<<x3<<" y3="<<y3<<" sum="
			//<<(x1*x1+y1*y1)*(x3*x3+y3*y3)<< endl;
			
			t1=(x1*x3+y1*y3)*100+1;
			t2=sqrtA(abs((x1*x1+y1*y1)*(x3*x3+y3*y3))+1);
			angLimit=abs((short)((t1)/(t2)));
			//c_out<<"angLimit"<<angLimit<<endl;
			
			triangleBase = (short)sqrtA(((vAngXStart-vectXEnd)*(vAngXStart-vectXEnd)+(vAngYStart-vectYEnd)*(vAngYStart-vectYEnd))*100);
			lengthSum=(vectorBase[vIndex-1][0]->length+length)*100;  //cout<<"lengthSum="<<lengthSum<<endl;
			if (triangleBase>3) { //if anlge > 0
				hLimit=lengthSum/triangleBase;
			}else{hLimit=200;angLimit=0;}//if triangle base very small it means angle between vectors also small and hLimit is big, we know it already.
			
			//cout<<"vectorCount="<<vectorCount<<"   vAngXStart="<<vAngXStart<<" vAngYStart="<<vAngYStart<<" vectXStart="<<vectXStart<<" vectYStart="<<vectYStart<<" vectXEnd="<<vectXEnd<<" vectYEnd="<<vectYEnd<<endl;
			//cout<<"length1="<<vectorBase[contourIndex].v[vIndex-1].length<<" length2="<<length<<" lengthSum="<<lengthSum<<" hLimit="<<hLimit<<" horda="<< triangleBase<<endl;
			
		}else{hLimit=200;angLimit=0;} //if(vectorCount>1) if it is first vector
		
		if(hLimit<140)angLimit+=100;
		if(vectorMarker[vectorCount]==angLength-1&&length<vectorLimitNormal)angLimit=200; //if end vector is small
		//angLimit=0;  //swich off angLimit
		if(angLimit<185){  //if limit is big enouth it means angle between vectors is sharp.
			//GP<vectorOCR> vectBufer=vectorOCR::create();
			//vectorBase->push_back(vectBufer);
			vectorBase[vIndex]->vStart.x=vectXStart; //cout<<" sX "<<vectXStart;
			vectorBase[vIndex]->vStart.y=vectYStart; //cout<<" sY "<<vectYStart;
			vectorBase[vIndex]->vEnd.x=vectXEnd;   //cout<<" eX "<<vectXEnd;
			vectorBase[vIndex]->vEnd.y=vectYEnd;   //cout<<" eY "<<vectYEnd;
			vectorBase[vIndex]->length=length; 	
			vectorBase[vIndex]->vectorFlag=0; 
			vectorBase[vIndex]->matchSum=0;
			vectorBase[vIndex]->vectorAngle=setVectorAngle(vectXStart,vectYStart,vectXEnd,vectYEnd); //c_out<<"vectorBase["<<contourIndex<<"].v["<<vIndex<<"].vectorAngle="<<vectorBase[contourIndex].v[vIndex].vectorAngle<<endl;
			vectorBase[vIndex]->vCentre.x=(vectXStart+vectXEnd)/2;  //cout<<" x="<<vectorBase[contourIndex].v[vIndex].vCentre.x;
			vectorBase[vIndex]->vCentre.y=(vectYStart+vectYEnd)/2;  //cout<<" y="<<vectorBase[contourIndex].v[vIndex].vCentre.y<<endl;
			vectorBase[vIndex]->contourIndex=contourIndex;

		}else{ //if(hLimit>1007){ //if limit is small it means angle between vectors is flat. we write in base only one result vector between two test vectors      
			angCount++;
			vectorMarker[vectorCount-1]=vectorMarker[vectorCount];
			vectXStart=angX[vectorMarker[vectorCount-2]];		//cout<<"new vectXStart="<<vectXStart;
			vectYStart=angY[vectorMarker[vectorCount-2]];		//cout<<" new vectYStart="<<vectYStart;
			vStartIndex=vectorMarker[vectorCount-2];
			vectXEnd=angX[vectorMarker[vectorCount]];			//cout<<" new vectXEnd="<<vectXEnd;
			vectYEnd=angY[vectorMarker[vectorCount]];			//cout<<" new vectYEnd="<<vectYEnd<<" vIndex"<<vIndex<<endl;
			vEndIndex=vectorMarker[vectorCount];				//cout<<" new vEndIndex="<<vEndIndex<<endl;
			
			
			length=(short)sqrtA(((vectXStart-vectXEnd)*(vectXStart-vectXEnd)+(vectYStart-vectYEnd)*(vectYStart-vectYEnd))*100);  //attention. length*100 increase Accuracy of short
			
			vectorBase[vIndex-1]->vStart.x=vectXStart; ///cout<<" baseX "<<vectXStart;
			vectorBase[vIndex-1]->vStart.y=vectYStart;
			vectorBase[vIndex-1]->vEnd.x=vectXEnd;
			vectorBase[vIndex-1]->vEnd.y=vectYEnd;
			vectorBase[vIndex-1]->length=length; 
			vectorBase[vIndex-1]->matchSum=0; 
			vectorBase[vIndex-1]->vectorFlag=0;   	   
			vectorBase[vIndex-1]->vectorAngle=setVectorAngle(vectXStart, vectYStart, vectXEnd, vectYEnd); //c_out<<"vectorBase["<<contourIndex<<"].v["<<vIndex<<"].vectorAngle="<<vectorBase[contourIndex].v[vIndex].vectorAngle<<endl;
			vectorBase[vIndex-1]->vCentre.x=(vectXStart+vectXEnd)/2; //cout<<" x1="<<vectorBase[contourIndex].v[vIndex-1].vCentre.x;
			vectorBase[vIndex-1]->vCentre.y=(vectYStart+vectYEnd)/2;  //cout<<" y1="<<vectorBase[contourIndex].v[vIndex-1].vCentre.y;
			
		}//end if(hLimit>15
	}else{lenCount++;}//end if if(length>170||angLength>45)
	//c_out<<"complete"<<endl;
	
}/////////////////////////////////////////////////////////////////////////////









