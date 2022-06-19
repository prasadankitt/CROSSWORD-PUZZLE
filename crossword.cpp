#include<bits/stdc++.h>
using namespace std;

void seperate(string words,vector<string> &vect)
{
    string temp="";
    for(int i=0;i<words.size();i++)
    {
        if(words[i]!=';')
        {
            temp.push_back(words[i]);
        }
        else
        {
            vect.push_back(temp);
            temp="";
        }
    }
}

void printer(vector<string> p)
{
    for(int i=0;i<p.size();i++)
    {
        cout<<p[i]<<" ";
    }
}

bool can_we_place_horizontally(vector<string> &crossword,string curr_word,int row,int col);
bool can_we_place_vertically(vector<string> &crossword,string curr_word,int row,int col);
vector<bool> place_my_word_horizontally(vector<string> &crossword,string curr_word,int row,int col);
vector<bool> place_my_word_vertically(vector<string> &crossword,string curr_word,int row,int col);
void unplace_horizontally(vector<string> &crossword,vector<bool> wePlaced,int row,int col);
void unplace_vertically(vector<string> &crossword,vector<bool> wePlaced,int row,int col);

vector<string> crosswordPuzzle(vector<string> &crossword, vector<string> vect,int index) 
{
    if(index==vect.size())
    {
        printer(crossword);
        return;
    }

    string curr_word=vect[index];

    for(int row=0;row<crossword.size();row++)
    {
        for(int col=0;col<crossword[0].size();col++)
        {
            if(crossword[row][col]==curr_word[0] || crossword[row][col]=='-')
            {
                if(can_we_place_horizontally(crossword,curr_word,row,col))
                {
                    vector<bool> wePlaced = place_my_word_horizontally(crossword,curr_word,row,col);
                    crosswordPuzzle(crossword,vect,index+1);
                    unplace_horizontally(crossword,wePlaced,row,col);
                }
    
                if(can_we_place_vertically(crossword,curr_word,row,col))
                {
                    vector<bool> wePlaced = place_my_word_vertically(crossword,curr_word,row,col);
                    crosswordPuzzle(crossword,vect,index+1);
                    unplace_vertically(crossword,wePlaced,row,col);
                }
            }
        }
    }
}


int main()
{
    string words="LONDON;DELHI;ICELAND;ANKARA";
    words=words+';';
    vector<string> vect;
    seperate(words,vect);
    vector<string> crossword={"+-++++++++",
                              "+-++++++++",
                              "+-++++++++",
                              "+-----++++",
                              "+-+++-++++",
                              "+-+++-++++",
                              "+++++-++++",
                              "++------++",
                              "+++++-++++",
                              "+++++-++++"};
    crosswordPuzzle(crossword,vect,0);
    return 0;
}