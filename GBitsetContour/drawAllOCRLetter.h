NSImage& drawAllOCRLetter(){
//struct timezone dontcare = { 0, 0 }; struct timeval before, after;  //timing of program implementation
//			gettimeofday(&before, &dontcare);
short x,y;

hL=h+1;  wL=w+1; //pecha size

NSImage *letterImageHandler = [[NSImage alloc] initWithSize:NSMakeSize(wL, hL)];
NSBitmapImageRep   *letterImageRep = [[[NSBitmapImageRep alloc] 
				    initWithBitmapDataPlanes:NULL
				    pixelsWide:wL
				    pixelsHigh:hL
				    bitsPerSample:8 
				    samplesPerPixel:1
				    hasAlpha:NO
				    isPlanar:NO
				    colorSpaceName:NSCalibratedWhiteColorSpace
				    bytesPerRow:wL 
				    bitsPerPixel:0] retain];
	    unsigned char *letterDataHandler = [letterImageRep bitmapData];   
				
			
			m=0;n=0;				
			for(y = 0; y < hL; y++ ) {
			for(x = 0; x < wL; x++){
			p1= letterDataHandler+y*wL+x;
				if(line[x][y]>1){res=180;} //contour
				if(line[x][y]==0){res=255;} //white
				if(line[x][y]==1){res=230;} //fcontour fill
				if(line[x][y]==1025){res=70;} //vectorPoint
			*p1=res;}}

[letterImageHandler addRepresentation:letterImageRep];
//			gettimeofday(&after, &dontcare); printf("%dsec. %lld micr.sec ///** drawAllOCRLetter\n ",(after.tv_sec - before.tv_sec), (after.tv_usec - before.tv_usec));
return letterImageHandler;

}//////////////////////////////////////////////////////////////////////////////////////
