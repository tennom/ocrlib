-(void)fillContour{   //fill contour of OCR Letter
short downLimit=50; //grey level
short startY, startX;
for(x=xMin ;x<=xMax;x++){
for(y=yMin ;y<=yMax;y++){
                
                if(line[x][y]>=1000){startY=y; //found  contour
		while(line[x][y-1]>downLimit){line[x][y]=1000;y--;}line[x][y]=1000; //remove all points before
		y=startY;
		while(line[x][y+1]>downLimit){line[x][y]=1000;y++;}line[x][y]=1000;  //remove all points after
		}//y++; 
		
	}}

for(y=yMin ;y<=yMax;y++){
for(x=xMin ;x<=xMax;x++){
                
	     if(line[x][y]>=1000){startX=x; //found  contour
	       while(line[x-1][y]>downLimit){line[x][y]=1000;x--;}line[x][y]=1000; //remove all points before
	       x=startX;
	       while(line[x+1][y]>downLimit){line[x][y]=1000;x++;}line[x][y]=1000;  //remove all points after
	       } 
	}}
        
}////////////////////////////////**
