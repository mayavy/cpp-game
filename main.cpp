#include "tictt.hpp"
 // array of Line to display 3 rows of blocks.
Line row0[7], row1[7], row2[7];
//currrent location of cursor.
std::tuple <int, int> cursor_loc(0,0);
auto[y,x] = cursor_loc;
// map containg coordinated of maked blocks so far
std::map <std::tuple <int, int> , char > marked_dict;
// Array to contain 10 unique Segments for each mark.
Segment x_segment[10], o_segment[10];
int xc=0, oc =0; // count of X, O segments
int atstart = 1;
// 'n' : None , here
int prev_len=0; // one run back len of marked_dict.
char previous = 'n'; //previous marker 'n' : None.
int run = 1; // game loop running.
char k = 'n'; // key input

       
int main(){
    while (run) {
    if (k == 'e'){break;}
    std::system("clear");
    welcome(atstart);
    Line horz0('='), horz1('='), last('-', 'b');
    Line top('_', 'b');
    top.print();
    
    draw_row( row0, horz0, 0, atstart, cursor_loc );
    draw_row( row1, horz1, 1,atstart, cursor_loc);
    draw_row( row2, last, 2, atstart, cursor_loc); 
 
    if (marked_dict.size() > prev_len){// 1=> new mark
        for ( const auto &coord_m : marked_dict ) {
            std::tuple<int,int> coord=coord_m.first;
            char m = coord_m.second;
            make_segment( coord, m, cursor_loc, x_segment,
            o_segment, xc, oc, marked_dict );
        }     

        check_m( o_segment, 'o', oc, marked_dict, run );
        check_m( x_segment, 'x', xc, marked_dict, run );
    }
    prev_len = marked_dict.size();// assign size as prevous.

    if (marked_dict.find( cursor_loc )== marked_dict.end()){
        if (k == 'x' && previous != 'x'){ox_pressed('x', 
cursor_loc, marked_dict,previous,  row0, row1, row2 );}
        if (k == 'o' && previous != 'o'){ox_pressed('o', 
cursor_loc, marked_dict,previous, row0, row1, row2);}
    }
    atstart = 0;

    if (k=='d'){
        y++; }
    if (k=='u'){
        y--;}
    if (k=='r'){
        x++; }
    if (k=='l'){
        x--; }

    if (y>2){y=0;}
    if (x>2){x=0;}
    if (y<0){y=2;}
    if (x<0){x=2;}
    cursor_loc = std::make_tuple(y,x);
    std::cout << "Enter any 1 out of u,d,l,r,x,o,e "<<std::endl;
    k = getchar(); 

    }
    return 0; 
}
