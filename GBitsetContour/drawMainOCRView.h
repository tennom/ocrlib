//draw all Letters on pecha as black contourmainOCRObject.mm

-(NSImage*)drawMainOCRView:(vector<GP<vectorOCR> >)vectorBase{  //just put data from letter array line in image bitmapRep handler
short x,y;
NSImage *letterImageHandler = [[NSImage alloc] initWithSize:NSMakeSize(w, h)];
NSBitmapImageRep   *letterImageRep = [[[NSBitmapImageRep alloc] 
				    initWithBitmapDataPlanes:NULL
				    pixelsWide:w
				    pixelsHigh:h
				    bitsPerSample:8 
				    samplesPerPixel:1
				    hasAlpha:NO
				    isPlanar:NO
				    colorSpaceName:NSCalibratedWhiteColorSpace
				    bytesPerRow:w 
				    bitsPerPixel:0] retain];
                //letterData = [letterImageRep bitmapData];   


for(y = 0; y < h; y++ ) {
for(x = 0; x< w; x++){
//p1=letterData+y*w+x;
//if(line[x][y]>255){res=line[x][y];}else{res=line[x][y];}
*p1=(char)rint(0);
}}
[letterImageHandler addRepresentation:letterImageRep];

return letterImageHandler;


}//end method
///////////////////////////////////*
