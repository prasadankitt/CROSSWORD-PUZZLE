#include<bits/stdc++.h>
using namespace std;

void seperate(string words,vector<string> &vect)
{
    //as input is given in form of string included with delimiter
    //so we seperate all words and make a vector of strings
    string temp="";
    for(int i=0;i<words.size();i++)
    {
        //if i dont find ';' add characters in temporary string 
        if(words[i]!=';')
        {
            temp.push_back(words[i]);
        }
        //otherwise i found ';' then push it in our vector and vacant the temporary string for
        //next words.
        else
        {
            vect.push_back(temp);
            temp="";
        }
    }
}

void printer(vector<string> p)
{
    //this printer function will simply print all the elements present in our vector
    for(int i=0;i<p.size();i++)
    {
        cout<<p[i]<<endl;
    }
}

bool can_we_place_horizontally(vector<string> &crossword,string curr_word,int row,int col)
{
    //check is it a perfect fit or not
    //if left exist and is not '+' return false
    if(col-1 >= 0 && crossword[row][col-1]!='+')
    {
        return false;
    }
    //if right side exist and is not '+' return false
    else if(col+curr_word.size()<crossword[0].size() && crossword[row][col+curr_word.size()]!='+')
    {
        return false;
    }

   //if we reached here it means word is fitting now check is some words of curr_word is present 
   //or not it may happen while filling other word some word which matches curr_word will present exactly
   //at same position which is good to go but if it is not the case return false.
    for(int i=0;i<curr_word.size();i++)
    {
        //to check whether word is not bigger than available space
        if(col+i>=crossword[0].size())
        {
            return false;
        }
        if(crossword[row][col+i]=='-' || crossword[row][col+i]==curr_word[i])
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
bool can_we_place_vertically(vector<string> &crossword,string curr_word,int row,int col)
{
    //check is it a perfect fit or not
    //if up exist and is not '+' return false
    if(row-1 >= 0 && crossword[row-1][col]!='+')
    {
        return false;
    }
    //if down exist and is not '+' return false
    else if(row+curr_word.size()<crossword.size() && crossword[row+curr_word.size()][col]!='+')
    {
        return false;
    }

   //if we reached here it means word is fitting now check is some words of curr_word is present 
   //or not it may happen while filling other word some word which matches curr_word will present exactly
   //at same position which is good to go but if it is not the case return false.
    for(int i=0;i<curr_word.size();i++)
    {
        //to check whether word is not bigger than available space
        if(row+i>=crossword.size())
        {
            return false;
        }
        if(crossword[row+i][col]=='-' || crossword[row+i][col]==curr_word[i])
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;

}


vector<bool> place_my_word_horizontally(vector<string> &crossword,string curr_word,int row,int col)
{
    //we are creating a boolean vector so that we can track of characters which we are putting
    //and we can remove it when we backtrack otherwise we remove characters which is present 
    //because of other word.
    vector<bool> wePlaced(curr_word.size(),false);
    for(int i=0;i<curr_word.size();i++)
    {
        if(crossword[row][col+i]=='-')
        {
            crossword[row][col+i]=curr_word[i];
            wePlaced[i]=true;
        }
    }
    return wePlaced;
}
vector<bool> place_my_word_vertically(vector<string> &crossword,string curr_word,int row,int col)
{
    //we are creating a boolean vector so that we can track of characters which we are putting
    //and we can remove it when we backtrack otherwise we remove characters which is present 
    //because of other word.
    vector<bool> wePlaced(curr_word.size(),false);
    for(int i=0;i<curr_word.size();i++)
    {
        if(crossword[row+i][col]=='-')
        {
            crossword[row+i][col]=curr_word[i];
            wePlaced[i]=true;
        }
    }
    return wePlaced;
}

void unplace_horizontally(vector<string> &crossword,vector<bool> wePlaced,int row,int col)
{
    //while backtracking we have to remove only characters which we placed not one which was already placed
    //because of other words placement
    for(int i=0;i<wePlaced.size();i++)
    {
        if(wePlaced[i]==true)
        {
            crossword[row][col+i]='-';
        }
    }
}
void unplace_vertically(vector<string> &crossword,vector<bool> wePlaced,int row,int col)
{
    //while backtracking we have to remove only characters which we placed not one which was already placed
    //because of other words placement
    for(int i=0;i<wePlaced.size();i++)
    {
        if(wePlaced[i]==true)
        {
            crossword[row+i][col]='-';
        }
    }
}

void crosswordPuzzle(vector<string> &crossword, vector<string> vect,int index) 
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
    string words="LONDON;DUBAI;ICELAND;ANKARA";
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