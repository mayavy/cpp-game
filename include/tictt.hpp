// game tic-tac-toe
// std = c++17
// inputs allowed e:exit, u:up,d:down, l:left, r:right, 
// o:O, x:X

# include <iostream>
# include <cstdlib>
# include <tuple>
#include <map>

class Line{
/* 
Every row printed on the console during
/ gameplay is a Line object.
/ size: size of each block.
/ p0: start of second block.
/ p1: start of third block.
/ mid: mid point of first block.
/ lst: array to be printed as row.
*/
    static const int size=12,
    p0 = size, p1 = p0*2+1, 
    len = p0*3+3, mid = p0/2;
    char lst[len];
    public:
        Line(){};
        Line( char chr , char state=' ' );
        void print();// print the whole row on console
        Line* show_cursor(const std::tuple<int, int>& 
        cursor_loc, int count);
        // to show cursor on selected rows
        void char_toline(int col, char arr[6], int size);
/*
Update Line.lst with a array of char to
/ display marks X or O.
*/


};



class Segment{
/* line-segment
For every same kind mark(X or O) 
/ line segment is constructed using row<=2, col<=2.
*/

    int y1,x1,y2,x2; // row~y, col~x
    int slope[2]; // slope of the segment
    public:
        Segment(){  };  
        Segment(int y1_, int x1_, int y2_, int x2_);
        bool straight_with( const Segment& segment);
/*
Bool if passed Segment is with current segment.
*/

        bool operator==(const Segment &seg );
/*
Bool: Current segment has same parameters
/ as those of Segment passed.
 */
};


void modify_o( Line (&row)[7], int col );
/* 
Modify array of Line to render 'O' mark.
col: x-coordinate of block to render in.
*/


void modify_x(Line (&row)[7], int col);
/*
Modify array of Line to render 'X' mark.
col: x-coordinate of block to render in.
*/


void welcome(int atstart);
// Welcome screen, runs only once, at start.

void draw_row( Line (&row)[7], Line& below, int count,
 int &atstart, const std::tuple<int, int> cursor_loc );
/*
renders array 'row' and cursor Line below it, 
count: row count , behaves as y.
*/


void make_segment( const  std::tuple <int, int>  & coord, 
char m, const  std::tuple <int, int>& cursor_loc,
Segment (&x_segment)[10],  Segment (&o_segment)[10],
 int &xc, int &oc,
std::map<std::tuple<int, int>, char > &marked_dict );
/*
m: mark O or X
constructs a Segment with two coords for block of same mark
*/


void check_m( Segment (&m_segment)[10], char m, int imc,
std::map<std::tuple<int, int>, char > &marked_dict, 
int &run);
/*
checks mark-segment array for Win or draw
*/


void ox_pressed( char m , std::tuple <int, int>&cursor_loc,
std::map<std::tuple<int, int>, char > &marked_dict,
 char& previous,
Line (&row0)[7], Line (&row1)[7], Line (&row2)[7] );
/*
registers pressed mark into marked_dict.
calls modify_x or modify_o to render X or O.
assigns previous mark.
*/


