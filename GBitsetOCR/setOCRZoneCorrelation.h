-(short)setOCRZoneCorrelation
			:(OCRLetterData *)letterModelBase 
			:(OCRVectorData *)vectorModelBase
			:(short)record
			:(short)correlation{
//in this step we test much in some zone in contour
short i,vIndex;

//////////////////////////////////_nga_//////////////////////////////////////////
if (letterModelBase[record].name[0]=='n'&&letterModelBase[record].name[1]=='g'&&letterModelBase[record].name[2]==0){
//cout<<" compare NGA"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
		
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==4)correlation=correlation-1;
				}
			}	
				
		}
//cout<<"corelation with nga="<<correlation<<endl; 
}//if (letterModelBase[record].name

//////////////////////////////////_ja_//////////////////////////////////////////
if (letterModelBase[record].name[0]=='j'&&letterModelBase[record].name[1]=='a'&&letterModelBase[record].name[2]==0){
//cout<<" compare NGA"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
		
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==5||letterModelBase[record].OCRZone[i]==6)correlation=correlation-1;
				}
			}	
				
		}
//cout<<"corelation with ja="<<correlation<<endl; 
}//if (letterModelBase[record].name

//////////////////////////////////_pa_//////////////////////////////////////////
if (letterModelBase[record].name[0]=='p'&&letterModelBase[record].name[1]=='a'&&letterModelBase[record].name[2]==0){
//cout<<" compare NGA"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
		
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==3)correlation=correlation-1;
				}
			}	
				
		}
//cout<<"corelation with ja="<<correlation<<endl; 
}//if (letterModelBase[record].name


//////////////////////////////////_achung_//////////////////////////////////////////
if (letterModelBase[record].name[0]=='\''&&letterModelBase[record].name[1]==0){
//cout<<" compare ja"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
		
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==5)correlation=correlation-1;
				}
			}	
				
		}
//cout<<"corelation with achung="<<correlation<<endl; 		
}//if (letterModelBase[record].name

//////////////////////////////////ma//////////////////////////////////////////
if (letterModelBase[record].name[0]=='m'&&letterModelBase[record].name[1]==0){
//cout<<" compare _m_"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==6)correlation=correlation-1;
				}
			}	
		}
//cout<<"corelation with ma="<<correlation<<endl; 	
}//if (letterModelBase[record].name

//////////////////////////////////_ra_//////////////////////////////////////////
if (letterModelBase[record].name[0]=='r'&&letterModelBase[record].name[1]==0){
//cout<<" compare _m_"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==5)correlation=correlation-1;
				}
			}	
		}
//cout<<"corelation with ra="<<correlation<<endl; 	
}//if (letterModelBase[record].name

//////////////////////////////////_bra_//////////////////////////////////////////
if (letterModelBase[record].name[0]=='b'&&letterModelBase[record].name[1]=='r'&&letterModelBase[record].name[2]=='a'&&letterModelBase[record].name[3]==0){
//cout<<" compare _m_"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==7)correlation=correlation-1;
				}
			}	
		}
//cout<<"corelation with bra="<<correlation<<endl; 	
}//if (letterModelBase[record].name

//////////////////////////////////_sra_//////////////////////////////////////////
if (letterModelBase[record].name[0]=='s'&&letterModelBase[record].name[1]=='r'&&letterModelBase[record].name[2]=='a'&&letterModelBase[record].name[3]==0){
//cout<<" compare _m_"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==8)correlation=correlation-1;
				}
			}	
		}
//cout<<"corelation with bra="<<correlation<<endl; 	
}//if (letterModelBase[record].name

//////////////////////////////////_s_//////////////////////////////////////////
if (letterModelBase[record].name[0]=='s'&&letterModelBase[record].name[1]==0){
//cout<<" compare _m_"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==4)correlation=correlation-2;
				}
			}	
		}
//cout<<"corelation with bra="<<correlation<<endl; 	
}//if (letterModelBase[record].name


//////////////////////////////////_su_//////////////////////////////////////////
if (letterModelBase[record].name[0]=='s'&&letterModelBase[record].name[1]=='u'&&letterModelBase[record].name[2]==0){
//cout<<" compare _m_"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==8||letterModelBase[record].OCRZone[i]==9)correlation=correlation-1;
				}
			}	
		}
//cout<<"corelation with bra="<<correlation<<endl; 	
}//if (letterModelBase[record].name

//////////////////////////////////_se_//////////////////////////////////////////
if (letterModelBase[record].name[0]=='s'&&letterModelBase[record].name[1]=='e'&&letterModelBase[record].name[2]==0){
//cout<<" compare _m_"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==1||letterModelBase[record].OCRZone[i]==2)correlation=correlation-1;
				}
			}	
		}
//cout<<"corelation with bra="<<correlation<<endl; 	
}//if (letterModelBase[record].name


//////////////////////////////////_a_//////////////////////////////////////////
if (letterModelBase[record].name[0]=='a'&&letterModelBase[record].name[1]==0){
//cout<<" compare _m_"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==1||letterModelBase[record].OCRZone[i]==4)correlation=correlation-1;
				}
			}	
		}
//cout<<"corelation with bra="<<correlation<<endl; 	
}//if (letterModelBase[record].name

//////////////////////////////////_d_//////////////////////////////////////////
if (letterModelBase[record].name[0]=='d'&&letterModelBase[record].name[1]==0){
//cout<<" compare _m_"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==4)correlation=correlation-1;
				}
			}	
		}
//cout<<"corelation with bra="<<correlation<<endl; 	
}//if (letterModelBase[record].name

//////////////////////////////////_m_//////////////////////////////////////////
if (letterModelBase[record].name[0]=='m'&&letterModelBase[record].name[1]==0){
//cout<<" compare _m_"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==4||letterModelBase[record].OCRZone[i]==7)correlation=correlation-1;
				}
			}	
		}
//cout<<"corelation with bra="<<correlation<<endl; 	
}//if (letterModelBase[record].name


//////////////////////////////////_ka_//////////////////////////////////////////
if (letterModelBase[record].name[0]=='k'&&letterModelBase[record].name[1]=='a'&&letterModelBase[record].name[2]==0){
//cout<<" compare _m_"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==1||letterModelBase[record].OCRZone[i]==4)correlation=correlation-1;
				}
			}	
		}
//cout<<"corelation with bra="<<correlation<<endl; 	
}//if (letterModelBase[record].name

//////////////////////////////////_ha_//////////////////////////////////////////
if (letterModelBase[record].name[0]=='h'&&letterModelBase[record].name[1]=='a'&&letterModelBase[record].name[2]==0){
//cout<<" compare _m_"<<" correlation="<<correlation<<endl;
		for(vIndex=letterModelBase[record].vInd;vIndex<letterModelBase[record].vInd+letterModelBase[record].vectorCount;vIndex++){
			//cout<<"vectorModelBase["<<vIndex<<"].pointCassidy="<<(short)vectorModelBase[vIndex].pointCassidy<<endl;
			if(vectorModelBase[vIndex].pointCassidy==0){
				for(i=vectorModelBase[vIndex].vStartIndex;i<vectorModelBase[vIndex].vEndIndex;i++){
				//cout<<"//__letterModelBase["<<record<<"].OCRZone["<<i<<"]="<<(short)letterModelBase[record].OCRZone[i]<<endl;
				if(letterModelBase[record].OCRZone[i]==4)correlation=correlation-1;
				}
			}	
		}
//cout<<"corelation with bra="<<correlation<<endl; 	
}//if (letterModelBase[record].name

return correlation;
}/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
