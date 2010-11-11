#include "aarot.h"
using namespace std;



namespace ocr{
	
double aarot::coss;
double aarot::sins;
aar_pnt * aarot::polyoverlap;
int aarot::polyoverlapsize;
aar_pnt * aarot::polysorted;
int aarot::polysortedsize;
aar_pnt * aarot::corners;




//Prevent Float Errors with Cos and Sin
double aarot::aar_cos(double degrees)
{
    double ret;
    double off = (degrees / 30 - round(degrees / 30));
    if (off < .0000001 && off > -.0000001)
    {
        int idegrees = (int)round(degrees);
        idegrees = (idegrees < 0) ? (360 - (-idegrees % 360))  : (idegrees % 360);
        switch (idegrees)
        {
            case 0: ret=1.0; break;
            case 30: ret=0.866025403784439; break;
            case 60: ret=0.5; break;
            case 90: ret=0.0; break;
            case 120: ret=-0.5; break;
            case 150: ret=-0.866025403784439; break;
            case 180: ret=-1.0; break;
            case 210: ret=-0.866025403784439; break;
            case 240: ret=-0.5; break;
            case 270: ret=0.0; break;
            case 300: ret=0.5; break;
            case 330: ret=0.866025403784439; break;
            case 360: ret=1.0; break;
            default: ret=cos(degrees * 3.14159265358979 / 180);  // it shouldn't get here
        }
        return ret;
    }
    else
        return cos(degrees * 3.14159265358979 / 180);
}//_____________________________________________________________________________

double aarot::aar_sin(double degrees)
{
    return aar_cos(degrees + 90.0);
}//_____________________________________________________________________________

double aarot::area()
{
    double ret = 0.0;
    //Loop through each triangle with respect to (0, 0) and add the cross multiplication
    for (int i = 0; i + 1 < polysortedsize; i++)
        ret += polysorted[i].x * polysorted[i + 1].y - polysorted[i + 1].x * polysorted[i].y;
    //Take the absolute value over 2
    return aar_abs(ret) / 2.0;
}//_____________________________________________________________________________

void aarot::sortpoints()
{
    if (polyoverlapsize < 3)
        return;
	
    if (polyoverlapsize == 3)
    {
        polysortedsize = polyoverlapsize - 1;
        polysorted[0].x = polyoverlap[1].x - polyoverlap[0].x;
        polysorted[0].y = polyoverlap[1].y - polyoverlap[0].y;
        polysorted[1].x = polyoverlap[2].x - polyoverlap[0].x;
        polysorted[1].y = polyoverlap[2].y - polyoverlap[0].y;
        return;
    }
	
    aar_indll * root = new aar_indll;
    root->next = NULL;
	
    for (int i = 1; i < polyoverlapsize; i++)
    {
        polyoverlap[i].x = polyoverlap[i].x - polyoverlap[0].x;
        polyoverlap[i].y = polyoverlap[i].y - polyoverlap[0].y;
		
        aar_indll * node = root;
        while (true)
        {
            if (node->next)
            {
                if (polyoverlap[i].x * polyoverlap[node->next->ind].y - polyoverlap[node->next->ind].x * polyoverlap[i].y < 0)
                {
                    aar_indll * temp = node->next;
                    node->next = new aar_indll;
                    node->next->ind = i;
                    node->next->next = temp;
                    break;
                }
            }
            else
            {
                node->next = new aar_indll;
                node->next->ind = i;
                node->next->next = NULL;
                break;
            }
            node = node->next;
        }
    }
	
    //We can leave out the first point because it's offset position is going to be (0, 0)
    polysortedsize = 0;
	
    aar_indll * node = root;
    aar_indll * temp;
    while (node)
    {
        temp = node;
        node = node->next;
        if (node)
            polysorted[polysortedsize++] = polyoverlap[node->ind];
        delete temp;
    }
}//_____________________________________________________________________________

bool aarot::isinsquare(aar_pnt r, aar_pnt & c)
{
    //Offset r
    r.x -= c.x;
    r.y -= c.y;
	
    //rotate r
    aar_pnt nr;
    nr.x = r.x * coss + r.y * sins;
    nr.y = r.y * coss - r.x * sins;
	
    //Find if the rotated polygon is within the square of size 1 centerd on the origin
    nr.x = aar_abs(nr.x);
    nr.y = aar_abs(nr.y);
    return (nr.x < 0.5 && nr.y < 0.5);
}//_____________________________________________________________________________

double aarot::pixoverlap(aar_pnt * p, aar_pnt c)
{
    polyoverlapsize = 0;
    polysortedsize = 0;
	
    int ja [] = {1, 2, 3, 0};
    double minx, maxx, miny, maxy;
    int j;
	
    double z;
	
    for (int i = 0; i < 4; i++)
    {
        //Search for source points within the destination square
        if (p[i].x >= 0 && p[i].x <= 1 && p[i].y >= 0 && p[i].y <= 1)
            polyoverlap[polyoverlapsize++] = p[i];
		
        //Search for destination points within the source square
        if (isinsquare(corners[i], c))
            polyoverlap[polyoverlapsize++] = corners[i];
		
        //Search for line intersections
        j = ja[i];
        minx = aar_min(p[i].x, p[j].x);
        miny = aar_min(p[i].y, p[j].y);
        maxx = aar_max(p[i].x, p[j].x);
        maxy = aar_max(p[i].y, p[j].y);
		
        if (minx < 0.0 && 0.0 < maxx)
        {//Cross left
            z = p[i].y - p[i].x * (p[i].y - p[j].y) / (p[i].x - p[j].x);
            if (z >= 0.0 && z <= 1.0)
            {
                polyoverlap[polyoverlapsize].x = 0.0;
                polyoverlap[polyoverlapsize++].y = z;
            }
        }
        else if (minx < 1.0 && 1.0 < maxx)
        {//Cross right
            z = p[i].y + (1 - p[i].x) * (p[i].y - p[j].y) / (p[i].x - p[j].x);
            if (z >= 0.0 && z <= 1.0)
            {
                polyoverlap[polyoverlapsize].x = 1.0;
                polyoverlap[polyoverlapsize++].y = z;
            }
        }
        if (miny < 0.0 && 0.0 < maxy)
        {//Cross bottom
            z = p[i].x - p[i].y * (p[i].x - p[j].x) / (p[i].y - p[j].y);
            if (z >= 0.0 && z <= 1.0)
            {
                polyoverlap[polyoverlapsize].x = z;
                polyoverlap[polyoverlapsize++].y = 0.0;
            }
        }
        else if (miny < 1.0 && 1.0 < maxy)
        {//Cross top
            z = p[i].x + (1 - p[i].y) * (p[i].x - p[j].x) / (p[i].y - p[j].y);
            if (z >= 0.0 && z <= 1.0)
            {
                polyoverlap[polyoverlapsize].x = z;
                polyoverlap[polyoverlapsize++].y = 1.0;
            }
        }
    }
	
    //Sort the points and return the area
    sortpoints();
    return area();
}//_____________________________________________________________________________

void aarot::dorotate(GBitmap* src, double rotation, int bgcolor, bool autoblend)
{
    //Calculate some index values so that values can easily be looked up
    int indminx = ((int)rotation / 90 + 0) % 4;
    int indminy = (indminx + 1) % 4;
    int indmaxx = (indminx + 2) % 4;
    int indmaxy = (indminx + 3) % 4;
	
    //Load the source bitmaps information
    short wSrc,hSrc;
	
    wSrc=src->columns(); hSrc=src->rows();
	
    //Calculate the sources x and y offset
    double srcxres = (double)wSrc / 2.0;
    double srcyres = (double)hSrc / 2.0;
	
    //Calculate the x and y offset of the rotated image (half the width and height of the rotated image)
    int mx[] = {-1, 1, 1, -1};
    int my[] = {-1, -1, 1, 1};
    double xres = mx[indmaxx] * srcxres * coss - my[indmaxx] * srcyres * sins;
    double yres = mx[indmaxy] * srcxres * sins + my[indmaxy] * srcyres * coss;
	
    //Get the width and height of the image
    int width = roundup(xres * 2);
    int height = roundup(yres * 2);
	
	GBitmap* dest;
	dest=GBitmap::create(width,height);
    //dest->fill(255);
    // int dt[500][500];
	
    aar_pnt * p = new aar_pnt[4];
    aar_pnt * poffset = new aar_pnt[4];
    aar_pnt c(0, 0);
	
	
    //Loop through the source's pixels
    double xtrans;
    double ytrans;
    for (int x = 0; x < wSrc; x++)
    {
        for (int y = 0; y < hSrc; y++)
        {
            //Construct the source pixel's rotated polygon
			
            xtrans = (double)x - srcxres;
            ytrans = (double)y - srcyres;
			
            p[0].x = xtrans * coss - ytrans * sins + xres;
            p[0].y = xtrans * sins + ytrans * coss + yres;
            p[1].x = (xtrans + 1.0) * coss - ytrans * sins + xres;
            p[1].y = (xtrans + 1.0) * sins + ytrans * coss + yres;
            p[2].x = (xtrans + 1.0) * coss - (ytrans + 1.0) * sins + xres;
            p[2].y = (xtrans + 1.0) * sins + (ytrans + 1.0) * coss + yres;
            p[3].x = xtrans * coss - (ytrans + 1.0) * sins + xres;
            p[3].y = xtrans * sins + (ytrans + 1.0) * coss + yres;
			
            //Caculate center of the polygon
            c.x = 0;
            c.y = 0;
            for (int i = 0; i < 4; i++)
            {
                c.x += p[i].x / 4.0;
                c.y += p[i].y / 4.0;
            }
			
            //Find the scan area on the destination's pixels
            int mindx = (int)p[indminx].x;
            int mindy = (int)p[indminy].y;
            int maxdx = roundup(p[indmaxx].x);
            int maxdy = roundup(p[indmaxy].y);
			
            //int SrcIndex = x + y * wSrc;
            //loop through the scan area to find where source(x, y) overlaps with the destination pixels
			
            for (int xx = mindx; xx < maxdx; xx++)
            {
                for (int yy = mindy; yy < maxdy; yy++)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        poffset[i].x = p[i].x - xx;
                        poffset[i].y = p[i].y - yy;
                    }
					
                    //Calculate the area of the source's rotated pixel (polygon p) over the destinations pixel (xx, yy)
                    //The function actually calculates the are&a of poffset over the square (0,0)-(1,1)
                    double dbloverlap = pixoverlap(poffset, aar_pnt(c.x - xx, c.y - yy));
                    if (dbloverlap)
                    {
                        //int DstIndex = xx + yy * width;
                        //Add the rgb and alpha values in proportion to the overlap area
                        dest[0][yy][xx]+=(double)src[0][y][x]*dbloverlap;
					}
                }
            }
			
        }
		
    }
	
    //for (int x = 0; x < wSrc; x++){
    //    for (int y = 0; y < hSrc; y++){
    //	src[0][y][x]=dest[0][y][x]/2;		
   //}}
    src->init(dest);	
    delete [] p;
    delete [] poffset;
    dest->destroy();
    delete  dest;	
	
}//_____________________________________________________________________________

void aarot::rotateFree(GBitmap* src, double rotation)
{
    //Calculate some index values so that values can easily be looked up
    //int indminx = ((int)rotation / 90 + 0) % 4;
    //int indminy = (indminx + 1) % 4;
    //int indmaxx = (indminx + 2) % 4;
    //int indmaxy = (indminx + 3) % 4;
	
    //Load the source bitmaps information
    short wSrc,hSrc;
	
    wSrc=src->columns(); hSrc=src->rows();
	
    //Calculate the src x and y offset
    int xo = wSrc / 2.0;
    int yo = hSrc / 2.0;
	
    //Calculate the x and y offset of the rotated image (half the width and height of the rotated image)
    //int mx[] = {-1, 1, 1, -1};
    //int my[] = {-1, -1, 1, 1};
    //double xres = mx[indmaxx] * xo * coss - my[indmaxx] * yo * sins;
    //double yres = mx[indmaxy] * xo * sins + my[indmaxy] * yo * coss;
	
    //Get the width and height of the image
    //int width = roundup(xres * 2);
    //int height = roundup(yres * 2);
	
	
	GBitmap* dest;
	dest=GBitmap::create(wSrc,hSrc);
    //dest->fill(255);
	
    //Loop through the source's pixels
    //double xtrans;
    //double ytrans;
    double r;
    int x1,y1;
    double s, c, a;
    double ang=M_PI * rotation / 180;
	
    //cout<<"angRad="<<ang<<END;
	
    for (int x = 0; x < wSrc; x++){
        for (int y = 0; y < hSrc; y++){
			r = sqrt((float)((x - xo)*(x - xo)+ (y - yo)*(y - yo)));
			a=atan2((y - yo), (x - xo));
			s=sin(ang+a);
			c=cos(ang+a);
			//DM("y="<<y<<" x="<<x<<" r="<<r<<" s="<<s<<" c="<<c<<" a="<<a<<END);
			x1=round(xo + r * c);
			y1=round(yo + r * s);
			if(x1<0||y1<1||x1>wSrc-1||y1>hSrc-1){dest[0][y][x]=255;
			}else{dest[0][y][x] = src[0][y1][x1];}
        }
		
    }
	
    //for (int x = 0; x < wSrc; x++){
    //    for (int y = 0; y < hSrc; y++){
    //              src[0][y][x]=dest[0][y][x]/2;		
   //}}
	
    src->init(dest);
    dest->destroy();
    delete dest;	
	
}//_____________________________________________________________________________


void aarot::rotate(GBitmap* src, double rotation, int bgcolor, bool autoblend)
{
    polyoverlap = new aar_pnt[16];
    polysorted = new aar_pnt[16];
    corners = new aar_pnt[4];
	
    double dx[] = {0.0, 1.0, 1.0, 0.0};
    double dy[] = {0.0, 0.0, 1.0, 1.0};
    for (int i = 0; i < 4; i++)
    {
        corners[i].x = dx[i];
        corners[i].y = dy[i];
    }
	
    //Get rotation between [0, 360)
    int mult = (int)rotation / 360;
    if (rotation >= 0)
        rotation = rotation - 360.0 * mult;
    else
        rotation = rotation - 360.0 * (mult - 1);
	
    //Calculate the cos and sin values that will be used throughout the program
    coss = aar_cos(rotation);
    sins = aar_sin(rotation);
	
	
    dorotate(src, rotation, bgcolor, autoblend);
	
    delete [] polyoverlap;
    delete [] polysorted;
    delete [] corners;
	
	
}//_____________________________________________________________________________




void aarot::rotate(GBitmap* src, double rotation)
{
    rotate(src, rotation, 0x00FFFFFF, true);
}

void aarot::rotate(GBitmap* src, double rotation, int bgcolor)
{
    rotate(src, rotation, bgcolor, true);
}

void aarot::rotate(GBitmap* src, double rotation, bool autoblend)
{
    rotate(src, rotation, 0x00FFFFFF, autoblend);
}


}//_____________________________________________________________________________

