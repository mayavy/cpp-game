// game tic-tac-toe
//std = c++17
#include "tictt.hpp"

Line::Line( char chr , char state ){
            /*
            chr = ' ', '_', '=', '-'
            state = 'v', 'b'
            */
            for (int j=1; j< len; j++){
            lst[j]= chr; 
            }
            lst[0] = '|';
            lst[len-1]= '|';
            if ( state=='v' ){//rows with saperated with ||
                lst[p0] = '|';
                lst[p0+1]= '|';
                lst[p1]= '|';
                lst[p1+1] ='|';
            }
            if (state=='b'){//blank rows
            lst[0]=' ';
            lst[len-1]=' ';
            }

}
void Line::print(){// print the whole row on console
            for (int i=0; i< len; i++){
                std::cout << lst[i];
            }
            std::cout<<std::endl;
}

Line* Line::show_cursor(const std::tuple<int, int>& 
cursor_loc, int count){ // to show cursor on selected rows
            int y=99,x=99;
            std::tie(y,x) = cursor_loc;
            if (y==count){
                lst[ (p0*x )+mid+x] = '^';  
            }
            return this;
}

        
void Line::char_toline(int col, char arr[6], 
int size){ 
        /*
        update Line.lst with a array of char to 
        / display marks X or O.
        */ 
           for (int i=0; i<size; i++ ){
                lst[p0*col+(mid/2)+col+i]  = arr[i];
            }
}



Segment::Segment(int y1_, int x1_, int y2_, int x2_){
        
        y1= y1_; y2= y2_;
        x1= x1_; x2=x2_;
        slope[0] = y2-y1; 
        slope[1] = x2-x1;
}
   
bool Segment::straight_with( const Segment& segment){
        /*
        Bool if passed Segment is with current segment.
        */
            return (slope[0] == segment.slope[0] && 
            slope[1] == segment.slope[1]) && 
        (y2==segment.y1 && x2 == segment.x1);
}

bool Segment::operator==(const Segment &seg ){
        /*
        Bool: Current segment has same parameters 
        / as those of Segment passed.
        */
            return (y1==seg.y1 && y2==seg.y2 && x1==seg.x1
            && x2== seg.x2 && slope[0]==seg.slope[0] && 
            slope[1]==seg.slope[1]   );
}
   



void modify_o( Line (&row)[7], int col ){
    //Line line0, line1, line2, line3, line4, line5, line6;
    auto &[line0, line1, line2, line3, line4,line5,line6] 
    = row;
    int sz=6;
    {char arr[sz] = " ____ ";
    line1.char_toline(col, arr, sz);}
    {char arr[sz]= "/    \\";
    line2.char_toline( col, arr, sz);}
    {char arr[sz]= "|    |";
    line3.char_toline(col, arr, sz );}
    {char arr[sz]= "\\____/";
    line4.char_toline( col, arr, sz );}
}

void modify_x(Line (&row)[7], int col){
    //Line line0, line1, line2, line3, line4, line5, line6;
    auto &[line0, line1, line2, line3, line4, line5, line6] 
    = row;
    int sz=6;
    {char arr[sz]= " \\  / ";
    line1.char_toline( col, arr, sz);}
    {char arr[sz]= "  \\/  ";
    line2.char_toline( col, arr, sz );}
    {char arr[sz]= "  /\\  ";
    line3.char_toline( col, arr, sz);}
    {char arr[sz]= " /  \\ ";
    line4.char_toline( col, arr, sz);}


}

void welcome(int atstart){ 
   if (atstart){ std::system("clear");
    std::cout <<"Welcome"<<'\n'<<"to"<<'\n'
    <<"Tic-Tac-Toe"<<'\n'<<"To move cursor use"<<'\n'
    <<"\"U\": Up, \"D\": Down"<<'\n'
    <<"\"L\": Left, \"R\": Right" <<'\n'<<'\n'
    <<"\"O\": for O, \"X\": for X"<<'\n'<<'\n'
    <<"Use \"E\": to EXIT the game"<<std::endl;   
    char d;
    std::cin.get();     std::system("clear");
    }
}


void draw_row( Line (&row)[7], Line& below, int count,
int &atstart, const std::tuple<int, int> cursor_loc ){
    for (int i=0;i<7; i++){ 
        if (atstart){ row[i] = Line(' ', 'v');}
        row[i].print();

    }
    below.show_cursor(cursor_loc, count)->print();
    
}

void make_segment( const  std::tuple <int, int>  & coord, 
char m, const  std::tuple <int, int>& cursor_loc,
Segment (&x_segment)[10],  Segment (&o_segment)[10],
int &xc, int &oc,
std::map<std::tuple<int, int>, char > &marked_dict ){

    if(marked_dict[cursor_loc]== m and cursor_loc != coord){
        std::tuple <int, int>loc0 = coord;
        std::tuple <int, int>loc1 = cursor_loc;

        if (coord > cursor_loc){
            loc0 = cursor_loc;
            loc1 = coord;
        }
        auto[y1,x1] = loc0; auto[y2,x2] = loc1;
        if (m=='x'){
        x_segment[xc] = Segment(y1,x1,y2,x2); xc++;
        }
        if (m=='o'){
        o_segment[oc] = Segment(y1,x1,y2,x2); oc++;
        }
    }
}

void check_m( Segment (&m_segment)[10], char m, int mc, 
std::map<std::tuple<int, int>, char > &marked_dict, int &run
){
    Segment segment, new_segment;
    for (int i=0;i<mc;i++){
        segment = m_segment[i];
        for(int j=0; j<mc; j++){
        new_segment = m_segment[j];

        if ( !(new_segment == segment) && segment.straight_with(new_segment)){
            std::cout<< m<<" won !!"<<std::endl; run = 0;
        } 
        else if (marked_dict.size() == 9 && run){
        std::cout << "Game drawn!!"<<std::endl; run = 0; 
        }
        } 
    }

}

void ox_pressed( char m , std::tuple <int, int>&cursor_loc, 
std::map<std::tuple<int, int>, char > &marked_dict, 
 char & previous,
Line (&row0)[7], Line (&row1)[7], Line (&row2)[7]
 ){
    int y=99,x=99;
    std::tie(y,x) = cursor_loc;
    if (y==0){
         m == 'x'? modify_x(row0, x):modify_o(row0,x);
}
    if (y==1){
         m == 'x'? modify_x(row1, x): modify_o(row1,x);
}
    if (y==2){
         m == 'x'? modify_x(row2, x): modify_o(row2,x);
}
    marked_dict[cursor_loc] = m;

    previous = m;

}
