#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include<vector>
#include <iostream>
#include<cmath>
#include<math.h>
#include<fstream>
#include<sstream>

using namespace std;

int xc,yc,x,y;
int xs,ys,xe,ye;
int x11, y11, x22, y22,x33,y33, rx, ry, r;
int tmp=0;
int counter=0;
struct point
{
    int x,y;
    point(int x,int y):x(x),y(y) {}
    point() {}
};
vector <point> v;



void Pixel(HDC hdc,int x, int y, COLORREF c)
{
    SetPixel(hdc, x,y,c);
    point m;
    m.x=x;
    m.y=y;
    v.push_back(m);
}

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


void swapp (int &x1,int &y1,int &x2,int &y2)
{
    int temp =x1;
    x1=x2;
    x2=temp;
    temp =y1;
    y1=y2;
    y2=temp;
}
void DDAalgorithm (HDC hdc, int x1, int y1,int x2, int y2, COLORREF c)
{
    int dx = x2-x1;
    int dy = y2-y1;
    double slope = (double)dy/(double)dx;
    if (abs(dx)>=abs(dy))
    {
        if (x1>x2)
            swapp(x1,y1,x2,y2);
        int x=x1;
        double y =y1;
        Pixel(hdc, x1, y1, c);
        while (x<x2)
        {
            x++;
            y+=slope;
            Pixel(hdc,x, y, c);
        }
    }
    else
    {
        if (y1>y2)
            swapp(x1,y1,x2,y2);
        int y=y1;
        double x =x1;
        Pixel(hdc, x1, y1, c);
        while (y<y2)
        {
            y++;
            x+=1/slope;
            Pixel(hdc,x, y, c);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// Parametric algorithm of line ///////////////////////////////////////////
void Parameticalgorithm (HDC hdc, int x1, int y1,int x2, int y2, COLORREF c)
{
    double dt = 1.0/(max(abs(x2-x1), abs(y2-y1)));
    for(double t =0 ; t<=1 ; t+=dt)
    {
        double x = x1+t*(x2-x1);
        double y = y1+t * (y2-y1);
        Pixel( hdc, x, y, c);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// Bresenham's algorithm of line //////////////////////////////////////////
void Bresenhamalgoritms (HDC hdc, int x1, int y1,int x2, int y2, COLORREF c)
{
    int dx=x2-x1;
    int  dy=y2-y1;
    if(abs(dx)>abs(dy))
    {
        if(dx<=0)
        {
            swap(x1,x2);
            swap(y1,y2);
            dx=-dx;
            dy=-dy;
        }
        if(dy>=0)
        {
            int x=x1;
            int y=y1;
            while(x<x2)
            {
                int d=(2*y+1-(2*y1))*dx-(2*(x+1-x1)*dy);
                if(d<=0)
                {
                    x++;
                    y++;
                    Pixel(hdc,x,y,c);
                }
                else
                {
                    x++;
                    Pixel(hdc,x,y,c);
                }
            }

        }
        else
        {
            int x=x1;
            int y=y1;
            while(x<x2)
            {
                int d=((((2*y)+1)-(2*y1))*dx)-(2*(x+1-x1)*abs(dy));
                if(d<=0)
                {
                    x++;
                    y--;
                    Pixel(hdc,x,y,c);
                }
                else
                {

                    x++;
                    Pixel(hdc,x,y,c);
                }
            }


        }
    }//dy>dx
    else
    {
        if(dy<0)
        {
            swap(x1,x2);
            swap(y1,y2);
            dx=-dx;
            dy=-dy;
        }
        if(dx>=0)
        {
            int x=x1;
            int y=y1;
            while(y<y2)
            {
                int d=2*(((y+1)-y1)*dx)-((((2*x)+1)-(2*x1))*dy);
                if(d>=0)
                {
                    x++;
                    y++;
                    Pixel(hdc,x,y,c);

                }
                else
                {
                    y++;
                    Pixel(hdc,x,y,c);
                }
            }

        }
        else// dx<0
        {
            int x=x1;
            int y=y1;
            while(y<y2)
            {
                int d=2*(y+1-y1)*abs(dx)-(((2*x+1)-(2*x1))*dy);
                if(d>=0)
                {
                    y++;
                    x--;
                    Pixel(hdc,x,y,c);
                }

                else
                {
                    y++;
                    Pixel(hdc,x,y,c);

                }
            }

        }
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////ellipse///////////////////////////////////////////
void draw4point (HDC hdc, int x, int y, int xc, int yc, COLORREF c )
{
    Pixel(hdc, xc+x, yc+y, c);
    Pixel(hdc, xc-x, yc+y, c);
    Pixel(hdc, xc+x, yc-y, c);
    Pixel(hdc, xc-x, yc-y, c);
}
////////////////////////////////Midpoint /////////////////////////////////////
void midpointellipse(HDC hdc, int rx, int ry,int xc, int yc, COLORREF c)
{
    float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;
    draw4point ( hdc,  x,  y,  xc,  yc, c );
    // Initial decision parameter of region 1
    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    // For region 1
    while (dx < dy)
    {
        // Checking and updating value of
        // decision parameter based on algorithm
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
        draw4point ( hdc,  x,  y,  xc,  yc, c );
    }

    // Decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
         ((rx * rx) * ((y - 1) * (y - 1))) -
         (rx * rx * ry * ry);

    // Plotting points of region 2
    while (y >= 0)
    {
        // Checking and updating parameter
        // value based on algorithm
        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
        draw4point ( hdc,  x,  y,  xc,  yc, c );
    }

}
///////////////////////////////////// Direct algorithms //////////////////////////////////////
void  directellipse (HDC hdc,double rx, int ry,int xc, int yc, COLORREF c)
{
    double x =rx;
    int y = 0 ;
    draw4point ( hdc,  x,  y,  xc,  yc, c );

    while(x>=0)
    {
        x-=0.1;
        y = abs(ry*sqrt(1-(pow(x,2.0)/pow(rx,2.0)))) ;
        draw4point ( hdc,  x,  y,  xc,  yc, c );
    }
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Direct  polar /////////////////////////////////
void  polarellipse (HDC hdc,int rx, int ry,int xc, int yc, COLORREF c)
{
    double dtheta = 1.0/max(rx,ry);

    for(double theta=0;  theta < 6.28;  theta+=dtheta)
    {
        double x = xc + rx*cos(theta);
        double y = yc - ry*sin(theta);
        Pixel(hdc, x,y,c);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////Filling///////////////////////////////////////


struct Entry
{
    double xleft=10000,xright=-10000;
    Entry(double xleft, double xright):xleft(xleft),xright(xright) {}
    Entry() {}
};

point p1,p2,p3,p4,p5;
vector <point> vertcies;
Entry Entry_table [1000];


void scanEdge()
{
    int n = vertcies.size();
    point v1=vertcies[n-1];
    for( int i=0; i<n ; i++)
    {
        point v2= vertcies[i];


        if(v1.y == v2.y)
            return;  //slope = zero: horizontal line
        if(v1.y > v2.y)
        {
            swap(v1.x,v2.x);
            swap(v1.y,v2.y);
        }

        double x = v1.x;
        int y = v1.y;
        double m =(double)(v2.x-v1.x)/(double)(v2.y-v1.y);


        while(y < v2.y)
        {
            if (x < Entry_table[y].xleft)
                Entry_table[y].xleft = x;


            if (x > Entry_table[y].xright)
                Entry_table[y].xright = x;

            y++;
            x+=m;
        }
        v1=vertcies[i];

    }
}


void scanLines(HDC hdc, COLORREF c)
{
    for( int i=0 ; i< 1000; i++)
    {
        if(Entry_table[i].xleft < Entry_table[i].xright)
        {
            for(int j=(int)ceil(Entry_table[i].xleft); j<=(int)floor(Entry_table[i].xright) ; j++)
                Pixel(hdc,j,i,c);
        }
    }
}


void mainAlgorithm(HDC hdc, COLORREF c)
{
    scanEdge();
    scanLines(hdc, c);
}



//////////////////////////////////////// clipping///////////////////////////////////////////////////


void draw8point(HDC hdc, int xc,int yc,int x,int y,COLORREF c)
{
    Pixel(hdc,xc+x,yc+y,c);
    Pixel(hdc,xc-x,yc+y,c);
    Pixel(hdc,xc-x,yc-y,c);
    Pixel(hdc,xc+x,yc-y,c);
    Pixel(hdc,xc+y,yc+x,c);
    Pixel(hdc,xc-y,yc+x,c);
    Pixel(hdc,xc-y,yc-x,c);
    Pixel(hdc,xc+y,yc-x,c);

}
void drawcircle(HDC hdc, int xc,int yc, double r,COLORREF c1)
{
    double y=r;
    double x=0;
    double dtheta=1.0/r;
    double c=cos(dtheta);
    double s=sin(dtheta);
    while(y>x)
    {
        double x1=(x*c)-(y*s);
        y=(x*s)+(y*c);
        x=x1;
        draw8point(hdc,xc,yc,(int)(x+0.5),(int)(y+0.5),c1);
    }
}

void clippingLine (HDC hdc, int x1, int y1,int x2, int y2, COLORREF c)
{
    double dt = 1.0/(max(abs(x2-x1), abs(y2-y1)));
    for(double t =0 ; t<=1 ; t+=dt)
    {
        double newx = x1+t*(x2-x1);
        double newy = y1+t * (y2-y1);
        double r;
        r=sqrt(pow(x-xc,2.0)+pow(y-yc,2.0));
        if( pow((newx - xc),2.0 )+ pow((newy -yc),2.0) <r*r)
            Pixel( hdc, newx, newy, c);
    }
}



/////////////////////////////////////////////////////////////////////////////////////

/*void save(string name)
{
    ofstream file;
    file.open(name, std::ofstream::out | std::ofstream::trunc);
    for(int i = 0 ; i <v.size() ; i++)
    {
        file<<v[i].x<<'\n'<<v[i].y<<'\n';
    }
    file.close();

}
void load(string name,HDC hdc,COLORREF c)
{
    ifstream file;
    file.open(name);
    int i = 0;
    vector<string> vect;
    while(!file.eof())
    {
        string x;
        file>>x;
        vect.push_back(x);
        i++;
    }
    point p;
    v.clear();

    for(int i = 0 ; i < vect.size()-1 ; i++)
    {
        int m;
        istringstream(vect[i])>>m;
        p.x = m;
        i++;
        istringstream(vect[i])>>m;
        p.y=m;
        v.push_back(p);
    }
    vect.clear();
    for(int i = 0 ; i <v.size() ; i++)
    {
        SetPixel(hdc,v[i].x,v[i].y,c);
    }
    file.close();

}

*/


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    hdc=GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {
    case WM_COMMAND:
        switch(wParam)
        {
        case 1:
            tmp =1;
            cout<<" Parametric of line "<<endl;
            break;
        case 2:
            tmp=2;
            cout<<"DDA of line"<<endl;
            break;
        case 3:
            tmp=3;
            cout<<"Bresenham's of line"<<endl;
            break;
        case 4:
            tmp=4;
            cout<<"Polar Algorithms of ellipse  "<<endl;
            break;
        case 5:
            tmp=5;
            cout<<"Direct  Algorithms of ellipse  "<<endl;
            break;
        case 6:
            tmp=6;
            cout<<"Mid point Algorithms of ellipse  "<<endl;
            break;
        case 7:
            tmp=7;
            cout<<"Convex Fillings"<<endl;
            break;
        case 8:
            tmp=8;
            cout<<"Clipping "<<endl;
            break;
       /* case 9:
            tmp = 9;
            cout<<"Save "<<endl;
          save("radwa.txt");
            break;
        case 10:
            tmp = 10;
            cout<<"Load "<<endl;
            load("radwa.txt",hdc,RGB(0,0,0));
            break;*/
        }
    case WM_CREATE:
    {
        HICON hIcon;
        HMENU hmenu=CreateMenu();
        HMENU LINE=CreateMenu();
        HMENU CONVEXFILLING=CreateMenu();
        HMENU ELLIPSE=CreateMenu();
        HMENU FILE=CreateMenu();
        /////////////////////////////////////////////////////////////////////////////////
        AppendMenu(hmenu,MF_POPUP,(UINT_PTR)LINE,"Line");
        AppendMenu(LINE,MF_STRING,1,"Parametric");
        AppendMenu(LINE,MF_STRING,2," DDA");
        AppendMenu(LINE,MF_STRING,3,"Bresenham's");
        /////////////////////////////////////////////////////////////////////////////////
        AppendMenu(hmenu,MF_POPUP,(UINT_PTR)ELLIPSE,"Ellipse");
        AppendMenu(ELLIPSE,MF_STRING,4,"Polar");
        AppendMenu(ELLIPSE,MF_STRING,5,"Direct");
        AppendMenu(ELLIPSE,MF_STRING,6,"Mid Point");
        ///////////////////////////////////////////////////////////////////////////////////
        AppendMenu(hmenu,MF_POPUP,7,"Convex Fillings");
//////////////////////////////////////////////////////////////////////////////////////
        AppendMenu(hmenu,MF_POPUP,8,"Clipping");
        ///////////////////////////////////////////////////////////////////////////////////
        AppendMenu(hmenu,MF_POPUP,(UINT_PTR)FILE,"File ");
        AppendMenu (FILE,MF_STRING,9, "Save");
        AppendMenu (FILE,MF_STRING,10, "Load");
        SetMenu(hwnd,hmenu);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    case WM_LBUTTONDOWN:
        x11=LOWORD(lParam);
        y11= HIWORD( lParam);

        if(tmp==4)
        {
            if (counter == 0)
            {
                xc=LOWORD(lParam);
                yc=HIWORD( lParam);
                counter++;
            }
            else if (counter == 1)
            {
                x22=LOWORD(lParam);
                y22=HIWORD( lParam);
                rx=sqrt(pow((x22-xc),2)+pow((y22-yc),2));
                counter++;
            }
            else if (counter == 2)
            {
                x33=LOWORD(lParam);
                y33=HIWORD( lParam);
                ry=sqrt(pow((x33-xc),2)+pow((y33-yc),2));
                polarellipse (hdc, rx, ry, xc, yc, RGB(0,0,0));

                counter=0;
            }

        }
////////////////////////////////////////////////////////////////////////////////
        if(tmp==5)
        {
            if (counter == 0)
            {
                xc=LOWORD(lParam);
                yc=HIWORD( lParam);
                counter++;
            }
            else if (counter == 1)
            {
                x22=LOWORD(lParam);
                y22=HIWORD( lParam);
                rx=sqrt(pow((x22-xc),2)+pow((y22-yc),2));
                counter++;
            }
            else if (counter == 2)
            {
                x33=LOWORD(lParam);
                y33=HIWORD( lParam);
                ry=sqrt(pow((x33-xc),2)+pow((y33-yc),2));
                directellipse (hdc, rx, ry, xc, yc, RGB(0,0,0));

                counter=0;
            }

        }
////////////////////////////////////////////////////////////////////////////////
        if(tmp==6)
        {

            if (counter == 0)
            {
                xc=LOWORD(lParam);
                yc = HIWORD( lParam);
                counter++;
            }
            else if (counter == 1)
            {
                x22=LOWORD(lParam);
                y22 = HIWORD( lParam);
                rx =sqrt(pow((x22-xc),2)+pow((y22-yc),2));
                counter++;
            }
            else if (counter == 2)
            {
                x33=LOWORD(lParam);
                y33 = HIWORD( lParam);
                ry =sqrt(pow((x33-xc),2)+pow((y33-yc),2));
                midpointellipse(hdc, rx, ry, xc, yc, RGB(0,0,0));

                counter=0;
            }

        }
////////////////////////////////////////////////////////////////////////////////
        if(tmp==7)
        {
            if(counter==0)
            {
                p1.x=LOWORD(lParam);
                p1.y=HIWORD(lParam);
                counter++;
                vertcies.push_back(p1);
            }
            else  if(counter==1)
            {
                p2.x=LOWORD(lParam);
                p2.y=HIWORD(lParam);
                counter++;
                vertcies.push_back(p2);

            }
            else  if(counter==2)
            {
                p3.x=LOWORD(lParam);
                p3.y=HIWORD(lParam);
                counter++;
                vertcies.push_back(p3);

            }
            else  if(counter==3)
            {
                p4.x=LOWORD(lParam);
                p4.y=HIWORD(lParam);
                counter++;
                vertcies.push_back(p4);

            }
            else if(counter==4)
            {
                p5.x=LOWORD(lParam);
                p5.y=HIWORD(lParam);
                counter++;
                vertcies.push_back(p5);
                mainAlgorithm(hdc,RGB(0,0,0));
                counter=0;
            }
        }
////////////////////////////////////////////////////////////////////////////////
        if (tmp==8)
        {
            if (counter == 0)
            {
                xc=LOWORD(lParam);
                yc=HIWORD(lParam);
                counter++;
            }
            else if (counter == 1)
            {
                x=LOWORD(lParam);
                y=HIWORD(lParam);
                double r;
                r=sqrt(pow(x-xc,2.0)+pow(y-yc,2.0));
                drawcircle(hdc,xc,yc,(int) (r+0.5),RGB(0,0,0));
                counter++;
            }
            else if (counter == 2)
            {
                xs=LOWORD(lParam);
                ys=HIWORD(lParam);
                counter++;
            }
            else if (counter== 3)
            {
                xe=LOWORD(lParam);
                ye=HIWORD(lParam);
                clippingLine(hdc,xs,ys,xe,ye,RGB(0,0,0));
                counter = 0;

            }
        }

        break;
    case WM_LBUTTONUP:
        x22=LOWORD(lParam);
        y22 = HIWORD( lParam);

        if(tmp==1)
            Parameticalgorithm ( hdc,  x11,  y11, x22, y22, RGB( 0,0,0));
        else if(tmp==2)
            DDAalgorithm ( hdc, x11, y11,x22,  y22, RGB(0,0,0));

        else if(tmp==3)
            Bresenhamalgoritms ( hdc, x11,  y11, x22,  y22,RGB(0,0,0));

        break;

    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

