void GBitsetContour::readInnerContour(){ //algorithm for reading contour of OCR Letter
    short dir=startDir;
    short x,y;
        angLength=0;
	//ang.resize(0); angX.resize(0); angY.resize(0);
	xMax=0; yMax=0;xMin=5000;yMin=5000;
	//int print=0;

    //
    //     7  6  5
    //      \ | /
    //    0- dir -4
    //      / | \
    //     1  2  3
    //


    x=xL; y=yL; //read start position
    //DP("xL="<<xL<<" yL="<<yL<<END);
    d=0;//ang=0;
	//ang[1]=0;ang[2]=0;ang[3]=0;
	//angX[0]=xL-3;angY[0]=yL;angX[1]=xL-2;angY[1]=yL;angX[2]=xL-1;angY[2]=yL;angX[3]=xL;angY[3]=yL;
    i=-1;

	while (endContour!=1&&i<19999){i++; //if (i>1000)//{cout<<"really long contour";}
		angX[i]=x; angY[i]=y;  ang[i]=11;  DP("x="<<x<<" y="<<y<<" i"<<i<<"\n");
		//if(i==1){line[0][angY[0]][angX[0]]=150;}  //restore start point

		if(x>xMax)xMax=x;if(x<xMin)xMin=x;if(y>yMax)yMax=y;if(y<yMin)yMin=y;
		DP("ang["<<i-1<<"]"<<(short)ang[i-1]<<"  line["<<angY[i-1]<<"]["<<angX[i-1]<<"]"<<(short)line[0][angY[i-1]][angX[i-1]]<<"\n");
		if (dir==0){
			if(line[0][y-1][x]>0 ){ang[i]=2;y=y-1;dir=2; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x+1]>0 ){ang[i]=1;y=y-1;x=x+1;dir=1; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue; }
			if(line[0][y][x+1]>0 ){ang[i]=0;x=x+1;dir=0; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x+1]>0 ){ang[i]=7;x=x+1;y=y+1;dir=7; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x]>0 ){ang[i]=6;y=y+1;dir=6; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x-1]>0 ){ang[i]=5;x=x-1;y=y+1;dir=5; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y][x-1]>0 ){ang[i]=4;x=x-1;dir=4; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x-1]>0 ){ang[i]=3;x=x-1;y=y-1;dir=3; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}

        }
        if (dir==1){
			if(line[0][y-1][x-1]>0 ){ang[i]=3;x=x-1;y=y-1;dir=3; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x]>0 ){ang[i]=2;y=y-1;dir=2; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x+1]>0 ){ang[i]=1;y=y-1;x=x+1;dir=1; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue; }
			if(line[0][y][x+1]>0 ){ang[i]=0;x=x+1;dir=0; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x+1]>0 ){ang[i]=7;x=x+1;y=y+1;dir=7; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x]>0 ){ang[i]=6;y=y+1;dir=6; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x-1]>0 ){ang[i]=5;x=x-1;y=y+1;dir=5; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y][x-1]>0 ){ang[i]=4;x=x-1;dir=4; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}

	}
		if (dir==2){
			if(line[0][y][x-1]>0 ){ang[i]=4;x=x-1;dir=4; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x-1]>0 ){ang[i]=3;x=x-1;y=y-1;dir=3; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x]>0 ){ang[i]=2;y=y-1;dir=2; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x+1]>0 ){ang[i]=1;y=y-1;x=x+1;dir=1; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue; }
			if(line[0][y][x+1]>0 ){ang[i]=0;x=x+1;dir=0; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x+1]>0 ){ang[i]=7;x=x+1;y=y+1;dir=7; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x]>0 ){ang[i]=6;y=y+1;dir=6; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x-1]>0 ){ang[i]=5;x=x-1;y=y+1;dir=5; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}

        }
        if (dir==3){
			if(line[0][y+1][x-1]>0 ){ang[i]=5;x=x-1;y=y+1;dir=5; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y][x-1]>0 ){ang[i]=4;x=x-1;dir=4; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x-1]>0 ){ang[i]=3;x=x-1;y=y-1;dir=3; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x]>0 ){ang[i]=2;y=y-1;dir=2; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x+1]>0 ){ang[i]=1;y=y-1;x=x+1;dir=1; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue; }
			if(line[0][y][x+1]>0 ){ang[i]=0;x=x+1;dir=0; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x+1]>0 ){ang[i]=7;x=x+1;y=y+1;dir=7; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x]>0 ){ang[i]=6;y=y+1;dir=6; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}

	}
        if (dir==4){
			if(line[0][y+1][x]>0 ){ang[i]=6;y=y+1;dir=6; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x-1]>0 ){ang[i]=5;x=x-1;y=y+1;dir=5; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y][x-1]>0 ){ang[i]=4;x=x-1;dir=4; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x-1]>0 ){ang[i]=3;x=x-1;y=y-1;dir=3; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x]>0 ){ang[i]=2;y=y-1;dir=2; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x+1]>0 ){ang[i]=1;y=y-1;x=x+1;dir=1; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue; }
			if(line[0][y][x+1]>0 ){ang[i]=0;x=x+1;dir=0; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x+1]>0 ){ang[i]=7;x=x+1;y=y+1;dir=7; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}

        }
        if (dir==5){
			if(line[0][y+1][x+1]>0 ){ang[i]=7;x=x+1;y=y+1;dir=7; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x]>0 ){ang[i]=6;y=y+1;dir=6; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x-1]>0 ){ang[i]=5;x=x-1;y=y+1;dir=5; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y][x-1]>0 ){ang[i]=4;x=x-1;dir=4; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x-1]>0 ){ang[i]=3;x=x-1;y=y-1;dir=3; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x]>0 ){ang[i]=2;y=y-1;dir=2; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x+1]>0 ){ang[i]=1;y=y-1;x=x+1;dir=1; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue; }
			if(line[0][y][x+1]>0 ){ang[i]=0;x=x+1;dir=0; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}

        }
        if (dir==6){
			if(line[0][y][x+1]>0 ){ang[i]=0;x=x+1;dir=0; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x+1]>0 ){ang[i]=7;x=x+1;y=y+1;dir=7; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x]>0 ){ang[i]=6;y=y+1;dir=6; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x-1]>0 ){ang[i]=5;x=x-1;y=y+1;dir=5; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y][x-1]>0 ){ang[i]=4;x=x-1;dir=4; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x-1]>0 ){ang[i]=3;x=x-1;y=y-1;dir=3; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x]>0 ){ang[i]=2;y=y-1;dir=2; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x+1]>0 ){ang[i]=1;y=y-1;x=x+1;dir=1; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue; }

		}
        if (dir==7){
			if(line[0][y-1][x+1]>0 ){ang[i]=1;y=y-1;x=x+1;dir=1; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue; }
			if(line[0][y][x+1]>0 ){ang[i]=0;x=x+1;dir=0; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x+1]>0 ){ang[i]=7;x=x+1;y=y+1;dir=7; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x]>0 ){ang[i]=6;y=y+1;dir=6; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y+1][x-1]>0 ){ang[i]=5;x=x-1;y=y+1;dir=5; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y][x-1]>0 ){ang[i]=4;x=x-1;dir=4; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x-1]>0 ){ang[i]=3;x=x-1;y=y-1;dir=3; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}
			if(line[0][y-1][x]>0 ){ang[i]=2;y=y-1;dir=2; if(line[0][y][x]>=150){ endContour=1; break;}  line[0][y][x]=20;  continue;}

        }

		//_//_DC("angOuterContour["<<i<<"]="<<(short)ang[i]<<END);
		if(ang[i]==11){ endContour=1; break;}
    }    //end while
	angLength=i+1;
	angX[i]=x;angY[i]=y; //join contour

		line[0][angY[0]][angX[0]]=20;}  //set start point in all contour value

	//angX[i-1]=xL;angY[i-1]=yL; //join contour
	xL=x; yL=y; startDir=dir; //save end position
	//for(i=1;i<angLength;i++)cout<<line[0][angX[i]][angY[i]]<<endl;
	//_//_DC("xMin="<<xMin<<" "<<"xMax="<<xMax<<" "<<"yMin="<<yMin<<""<<"yMax="<<yMax<<" angLength="<<angLength<<"\n");
}///////////////////////////////////*
