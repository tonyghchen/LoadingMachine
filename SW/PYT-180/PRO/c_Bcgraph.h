#define _GPSET						0
enum {_GFILLINTERIOR , _GBORDER} ;
#define _getch()	getch()
#define _setcolor(color)			setcolor(color)
#define _putimage(x,y,buf,op)		putimage(x,y,buf,op) ;
#define _getimage(lx,ly,rx,ry,buf)	getimage(lx,ly,rx,ry,buf)
#define _imagesize(lx,ly,rx,ry)		((rx-lx+1)*(ry-ly+1)+4)
#define _lineto(x,y)				lineto(x,y)
#define _moveto(x,y)				moveto(x,y)
#define _setlinestyle(pattern)		setlinestyle(USERBIT_LINE,pattern,NORM_WIDTH)

