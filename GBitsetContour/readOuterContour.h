
void GBitsetContour::readOuterContour(int vL){ //algorithm for reading contour of OCR Letter
	short dir=startDir;
	//ang.resize(0); angX.resize(0); angY.resize(0);
        angLength=0;
    xMax=0; yMax=0;xMin=5000;yMin=5000;
    unsigned char *p;
    //
    //     1  2  3
    //      \ | /
    //    0- dir -4
    //      / | \
    //     7  6  5
	//

	//for(int n=0;n<nrows;n++){for(int m=0;m<ncolumns;m++){DP((short)line[0][n][m]<<"\t");}DP(END);}

    short x,y;
	x=xL; y=yL; //read start position
	//DP("//______start xL="<<xL<<" yL="<<yL<<END);
    d=0;//ang[0]=0;
	//ang[1]=0;ang[2]=0;ang[3]=0;
	//angX[0]=xL-3;angY[0]=yL;angX[1]=xL-2;angY[1]=yL;angX[2]=xL-1;angY[2]=yL;angX[3]=xL;angY[3]=yL;
    i=-1;
	while (endContour!=1&&i<19999){i++; //if (i>1000)//cout<<"really long contour";
			//if(i==1){line[0][angY[0]][angX[0]]=150;}  //restore start point
			//DP("x="<<x<<" y="<<y<<END); if(i>10)break;
			angX[i]=x; angY[i]=y;  ang[i]=11;
				//_//_DC("x="<<angX[i]<<" y="<<angY[i]<<" i="<<i<<"angY[0]"<<angY[0]<<"\n");
			//DP("ang["<<i-1<<"]="<<(short)ang[i-1]<<"  line["<<angY[i-1]<<"]["<<angX[i-1]<<"]="<<(short)line[0][angY[i-1]][angX[i-1]]<<"\n");
        	if(x>xMax)xMax=x;if(x<xMin)xMin=x;if(y>yMax)yMax=y;if(y<yMin)yMin=y;  	  //cout<< angX[i-1]<<" "
		//cout<<"angOuterContour["<<i<<"]="<<(short)ang[]<<endl;
	if (dir==0){
			p=&line[0][y-1][x];   if(*p){ang[i]=6;y-=1;     dir=6; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x+1]; if(*p){ang[i]=7;y-=1;x+=1;dir=7; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue; }
			p=&line[0][y][x+1];   if(*p){ang[i]=0;x+=1;     dir=0; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x+1]; if(*p){ang[i]=1;x+=1;y+=1;dir=1; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x];   if(*p){ang[i]=2;y+=1;     dir=2; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x-1]; if(*p){ang[i]=3;x-=1;y+=1;dir=3; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y][x-1];   if(*p){ang[i]=4;x-=1;     dir=4; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
	}
		if (dir==1){
			p=&line[0][y-1][x+1]; if(*p){ang[i]=7;y-=1;x+=1;dir=7; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue; }
			p=&line[0][y][x+1];   if(*p){ang[i]=0;x+=1;     dir=0; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x+1]; if(*p){ang[i]=1;x+=1;y+=1;dir=1; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x];   if(*p){ang[i]=2;y+=1;     dir=2; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x-1]; if(*p){ang[i]=3;x-=1;y+=1;dir=3; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y][x-1];   if(*p){ang[i]=4;x-=1;     dir=4; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x-1]; if(*p){ang[i]=5;x-=1;y-=1;dir=5; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
		}
		if (dir==2){
			p=&line[0][y][x+1];   if(*p){ang[i]=0;x+=1;     dir=0; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x+1]; if(*p){ang[i]=1;x+=1;y+=1;dir=1; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x];   if(*p){ang[i]=2;y+=1;     dir=2; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x-1]; if(*p){ang[i]=3;x-=1;y+=1;dir=3; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y][x-1];   if(*p){ang[i]=4;x-=1;     dir=4; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x-1]; if(*p){ang[i]=5;x-=1;y-=1;dir=5; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x];   if(*p){ang[i]=6;y-=1;     dir=6; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
		}

		if (dir==3){
			p=&line[0][y+1][x+1]; if(*p){ang[i]=1;x+=1;y+=1;dir=1; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x];   if(*p){ang[i]=2;y+=1;     dir=2; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x-1]; if(*p){ang[i]=3;x-=1;y+=1;dir=3; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y][x-1];   if(*p){ang[i]=4;x-=1;     dir=4; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x-1]; if(*p){ang[i]=5;x-=1;y-=1;dir=5; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x];   if(*p){ang[i]=6;y-=1;     dir=6; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x+1]; if(*p){ang[i]=7;y-=1;x+=1;dir=7; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue; }
		}
		if (dir==4){
			p=&line[0][y+1][x];   if(*p){ang[i]=2;y+=1;     dir=2; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x-1]; if(*p){ang[i]=3;x-=1;y+=1;dir=3; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y][x-1];   if(*p){ang[i]=4;x-=1;     dir=4; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x-1]; if(*p){ang[i]=5;x-=1;y-=1;dir=5; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x];   if(*p){ang[i]=6;y-=1;     dir=6; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x+1]; if(*p){ang[i]=7;y-=1;x+=1;dir=7; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue; }
			p=&line[0][y][x+1];   if(*p){ang[i]=0;x+=1;     dir=0; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
		}
		if (dir==5){
			p=&line[0][y+1][x-1]; if(*p){ang[i]=3;x-=1;y+=1;dir=3; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y][x-1];   if(*p){ang[i]=4;x-=1;     dir=4; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x-1]; if(*p){ang[i]=5;x-=1;y-=1;dir=5; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x];   if(*p){ang[i]=6;y-=1;     dir=6; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x+1]; if(*p){ang[i]=7;y-=1;x+=1;dir=7; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue; }
			p=&line[0][y][x+1];   if(*p){ang[i]=0;x+=1;     dir=0; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x+1]; if(*p){ang[i]=1;x+=1;y+=1;dir=1; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
		}
		if (dir==6){
			p=&line[0][y][x-1];   if(*p){ang[i]=4;x-=1;     dir=4; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x-1]; if(*p){ang[i]=5;x-=1;y-=1;dir=5; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x];   if(*p){ang[i]=6;y-=1;     dir=6; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue; }
			p=&line[0][y-1][x+1]; if(*p){ang[i]=7;y-=1;x+=1;dir=7; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue; }
			p=&line[0][y][x+1];   if(*p){ang[i]=0;x+=1;     dir=0; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x+1]; if(*p){ang[i]=1;x+=1;y+=1;dir=1; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x];   if(*p){ang[i]=2;y+=1;     dir=2; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
		}
		if (dir==7){
			p=&line[0][y-1][x-1]; if(*p){ang[i]=5;x-=1;y-=1;dir=5; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x];   if(*p){ang[i]=6;y-=1;     dir=6; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y-1][x+1]; if(*p){ang[i]=7;y-=1;x+=1;dir=7; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue; }
			p=&line[0][y][x+1];   if(*p){ang[i]=0;x+=1;     dir=0; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x+1]; if(*p){ang[i]=1;x+=1;y+=1;dir=1; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x];   if(*p){ang[i]=2;y+=1;     dir=2; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
			p=&line[0][y+1][x-1]; if(*p){ang[i]=3;x-=1;y+=1;dir=3; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]+=vL;  continue;}
		}
		if(ang[i]==11){ endContour=1; break;}
	}    //end while

	line[0][angY[0]][angX[0]]=21;  //set start point in all contour value

	angLength=i+1;
	angX[i]=x;angY[i]=y; //join contour
	//angX[i-1]=xL;angY[i-1]=yL; //join contour
	xL=x; yL=y; startDir=dir; //save end position
	// for(i=1;i<angLength;i++)cout<<line[0][angX[i]][angY[i]]<<endl;
	//_//_DC("xMin="<<xMin<<" "<<"xMax="<<xMax<<" "<<"yMin="<<yMin<<""<<"yMax="<<yMax<<"\n");
    //DP("xL="<<x<<" yL=<<"<<y<<END);

	//for(int n=0;n<nrows;n++){for(int m=0;m<ncolumns;m++){DP((short)line[0][n][m]<<"\t");}DP(END);}


}///////////////////////////////////*
