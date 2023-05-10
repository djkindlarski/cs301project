/*CS 301 Final Project: 
*Implement a simplified version of SELECT 
*for a SQL database, consisting of SELECT,
*FROM, WHERE, and ORDERBY clauses.
*Creator: David Kindlarski
*/

#include <iostream>
#include <string>
#include <random>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <assert.h>
#include <algorithm>
   
    
using namespace std;

string nameConvert(string fileName)     //converts input into proper naming format
    {
        fileName.append(".csv");
        return fileName;
    }

vector<string> openFile(string fileName)    //opens the file
{

    fstream fout;
    string csvFile;
    vector<string> testFile;
    int test = 0;

    fout.open(fileName);
    while(fout.eof() == 0)
        {
            getline(fout, csvFile);
            testFile.push_back(csvFile);
        }

    return testFile;
}   

vector<string> currentFile(string fileName, vector<string> tabFile) //reads in tab_columns for given data
{   
                                                                //takes data row by row from TAB_COLUMNS, working backwards to return them in order
    vector<string> nowFile;
    int v;
    int sz = tabFile.size();
    int substrSz;
    for (v = sz-1; v>-1; v--)  //BACKWARDS
    {

        if(tabFile[v].substr(0,fileName.length()) == fileName)
        {
                nowFile.push_back(tabFile[v]);
        }
    }
    return nowFile;
}

string iterate(string input, int commaNum, int vec) //works through CSV line to get proper data
{

    int pos = 0;
    int counter = 0;
    int end;
    string temp = input;

    string result;
    for(int i = 0; i<= temp.length(); i++)
        {
            
            if (temp[i] == ',')
            {
            pos = i;
            counter++;
            }
            if (counter == commaNum)
            {
                for (int j = i+1; j <= temp.length(); j++)
                {
                    if (temp[j] == ',' || j == temp.length())
                    {
                        end = j;
                        break;
                    }
                }
                break;
            }

        }
        if(commaNum == 0)
         result = temp.substr(pos,end-pos);
        else
        {
            result = temp.substr(pos+2,end-pos-2);
        }

        return result;
}

string iterate(string input, int commaNum) //works through CSV line to get proper data
{

    int pos = 0;
    int counter = 0;
    int end;
    string temp = input;

    string result;
    for(int i = 0; i<= temp.length(); i++)
        {
            
            if (temp[i] == ',')
            {
            pos = i;
            counter++;
            }
            if (counter == commaNum)
            {
                for (int j = i+1; j <= temp.length(); j++)
                {
                    if (temp[j] == ',' || j == temp.length())
                    {
                        end = j;
                        break;
                    }
                }
                break;
            }

        }
        if(commaNum == 0)
         result = temp.substr(pos,end-pos);
        else
        {
            result = temp.substr(pos+1,end-pos-1);
        }

        return result;
}

bool sortCol(const vector<string>& v1,const vector<string>& v2)
{
    return v1[0] < v2[0];
}

vector<vector<string> > orderMe(vector<vector <string> > finalFile, vector<string> orderBy_Args, int orderFlag, int selectLen, string compare)
{

        int cCount = -1;
        vector<string> subArgs;
        int subStart = -1;
        int subEnd = -1;
        

            if (orderBy_Args.size() > 2)
            {
                for (int subby = 2; subby < orderBy_Args.size(); subby++)
                subArgs.push_back(orderBy_Args[subby]);
            }

            for (int y = 0; y <= finalFile[0].size(); y++)     //for loop iterates through the column list of the final file
            {
                            compare = finalFile[0][y];
                            
                if (orderBy_Args[0] == compare)   //SEES IF ARG MATCHES HEADER
                {
                    cCount = y;
                    break;
                }
            }
            int commaUno, commaDos, commaCur;   //where are commas one and two in the fxn
            string compareSub;                  //substring that will be compared

            vector< vector< string> > orderFile;
            vector<string> loopFile;
            if(orderFlag == 0)
            {
                for (int hh = 1; hh < finalFile.size(); hh+=selectLen) // pushes KEY data from finalFile to loopFile 
            {                                                            // prep to be sorted via KEY data
                for (int w = 0; w < selectLen; w++)
                    {   
                        loopFile.push_back(finalFile[hh+w][0]);

                    }
                    orderFile.push_back(loopFile);                          
                    loopFile.clear();                                       
            }
            }
            
            else
            {
                for (int hh = 1; hh < finalFile.size(); hh++) // pushes KEY data from finalFile to loopFile 
            {                                                               // prep to be sorted via KEY data
                    orderFile.push_back(finalFile[hh]);
                    loopFile.clear();                                       
            }
            }

            //---------------------------
            vector<string> sortVector;
            int save = orderFile.size();
            for(int rr = 0; rr < save; rr++)
            {
                    sortVector.push_back(orderFile[rr][cCount]);    //NOW JUST THE KEY DATA
            }
            vector<vector< string> >midpoint;
            if (orderBy_Args[1] == "ASC")
            {
            sort(sortVector.begin(), sortVector.end());                       //sorts via ASC
            }
            if (orderBy_Args[1] == "DESC")
            {
                sort(sortVector.begin(), sortVector.end(), greater<string>());
            }
            int finSize = finalFile.size()-1;
            for (int xx = 0; xx < finSize; xx++)
            {
                
                finalFile.pop_back();
            }
            int badFlag = 0;
            int pushPt;
            for (int jj = 0; jj < sortVector.size(); jj++)
            {
                for (int aa = 0; aa < sortVector.size(); aa++)
                    {
                       pushPt = aa;
                        if((sortVector[jj] == orderFile[aa][cCount])) 
                        {
                            badFlag = 0;
                            if(midpoint.size() == 0)
                            {
                            midpoint.push_back(orderFile[pushPt]);
                            continue;
                            }
                            
                            else 
                            {
                                for (int xyz = 0; xyz < midpoint.size(); xyz++)
                                {
                                    if(orderFile[aa] == midpoint[xyz])
                                    {
                                        badFlag++;
                                        
                                    }
                                }
                                if (badFlag != 0) break;
                                int sum = aa+badFlag;
                          
                                midpoint.push_back(orderFile[sum]);
                                continue;
                             
                            }
                                                    break;

                        }
                    }
                                finalFile.push_back(midpoint[jj]); 

            }
            if (subArgs.size() > 1)                             //checks for additional orderby
            {
                vector <vector< string> > subVec;
                vector <string> temper;
                for (int fi = 0; fi < finalFile[0].size(); fi++)
                {
                    if (finalFile[0][fi] == subArgs[0])
                    {
                    int cNew = fi;
                    }
                }
                int tempStart = -1;
                int tempEnd = -1;
                for (int q = 1; q < finalFile.size(); q++)      //iterates through first degree sorted final file
                {                                               //STARTS AFTER LABELS
                    if (finalFile[q][cCount] == finalFile[q-1][cCount] && tempStart == -1)
                        {
                            tempStart = q-1;
                        }
                    
                    else if(finalFile[q][cCount] == finalFile[q-1][cCount] && q+1 != finalFile.size())
                    {
                        continue;
                    }
                    else
                    {
                        if (tempStart == -1)
                            continue;
                        if (tempStart != -1 && q+1 == finalFile.size())
                            tempEnd = q+1;
                        else tempEnd = q;
                        int jo = 0;
                        for (int asd = 0 ; asd < finalFile[0].size(); asd++)
                        {
                            temper.push_back(finalFile[0][asd]);
                        }
                        subVec.push_back(temper);
                        temper.clear();
                        

                        for (int subIt = tempStart; subIt < tempEnd; subIt++)
                        {
                            for (int finL = 0; finL < finalFile[0].size(); finL++){
                            temper.push_back(finalFile[subIt][finL]);
                            subVec.push_back(temper);
                            temper.clear();
                            }
                            jo++;

                        }
                        subVec = orderMe(subVec, subArgs, orderFlag, selectLen, compare);
                      
                        int flg = 1;
                        for (int subIt = tempStart; subIt < tempEnd; subIt++)
                        {
                            finalFile.erase(finalFile.begin()+subIt);
                            finalFile.insert(finalFile.begin()+subIt,subVec[flg]);
                            flg++;


                        }
                       
                        tempStart = -1;
                        tempEnd = -1;
                        subVec.clear();

                    }
                    
                }
            }
             orderFile.clear();
             loopFile.clear();
             sortVector.clear();
             midpoint.clear();     
            orderFlag = 1;                                              
        //for} 
 
        return finalFile;
}

vector<string> whereMe(vector<string> csvFile, vector<string> where_Args)
{
    return csvFile;
}

int main(int argc, char * argv[])
{

    //argument vector declarations
    vector<string> select_Args;
    vector<string> from_Args;
    vector<string> where_Args;      //declarations for each segment of command
    vector<string> orderBy_Args;

    //file vector declarations
    vector<vector<string> > csvData;    
    vector<string> row;


    //initial string & counter declarations
    string input, fName;
    vector<string> csvFile;
    int strlen, i, startSub, endSub, vCount, subLen;
    int csvLen, subCsv;

    vector<string> tabFile;

    tabFile = openFile("TAB_COLUMNS.csv");
    int tabSize = tabFile.size()-1;

    vector<string> nowFile;

    while(1)
    {

        //gets data from user
        getline(cin, input);
       

        //checks if the user wants to exit
        if (input == "exit" || input == "EXIT")
        {
            return 0;
        }
    
        //sets up for loop to remove spaces
        strlen = input.length();
        endSub = 0;
        vCount = 0;
        subLen = 0;

        //for loop to parse string into vectors

        for (i = 0; i <= strlen; i++)            
            {
            //checks if SELECT is used
            if(input.substr(i,6) == "SELECT")
                {
                    vCount = 1;     //semaphore changes to select vector
                    i = 5;          //moves for loop ahead past select
                    continue;
                }
            
            if(input.substr(i,4) == "FROM")
                {
                    vCount = 2;         //semaphore changes to from vector
                    i +=4;              //moves for loop ahead past from
                    continue;
                }

            if(input.substr(i,5) == "WHERE")
                {
                    vCount = 3;         //semaphore changes to where vector
                    i += 5;             //moves for loop ahead past where
                    continue;
                }

            if (input.substr(i,7) == "ORDERBY")
                {
                    vCount = 4;         //semaphore changes to orderby vector
                    i += 7;             //moves for loop ahead past orderby
                    continue;
                }

            if(input[i] == ' ' || input[i] == ',' || input[i] == ';' || input[i] == '\n' || input[i] == '\r' || i == strlen)
            {
                if (subLen == 0)
                    continue;
                
                if (vCount == 1)
                    {
                    select_Args.push_back(input.substr(i-subLen,subLen));
                    }

                if (vCount == 2)
                    {
                    from_Args.push_back(input.substr(i-subLen,subLen));
                    }

                if (vCount == 3)
                    {
                    where_Args.push_back(input.substr(i-subLen,subLen));
                    }

                if (vCount == 4)
                    {
                    orderBy_Args.push_back(input.substr(i-subLen,subLen));
                    }

               subLen = 0;
            }

            else
            {
                subLen++;
            }
            }
        fName = nameConvert(from_Args[0]);
        csvFile = openFile(fName);


        

        csvLen = csvFile.size()-1;

        subCsv = 0;
        nowFile = currentFile(from_Args[0], tabFile);

        
        vector<vector<string > >finalFile;
        int j, u, commaFlag, b, locale, pp;
        vector<string> labelFile;
        vector<string> tempFile;
        int wordLoc;
        string first, last;
        size_t pos;
        int iFirst, iLast;
        int cnt = 0;
        string wordFlag;

        string colName, colNam;

        int selectLen;

        if(select_Args[0][0] == '*')
            {
                selectLen = csvLen;
            }
        else
        {
                selectLen = select_Args.size();
        }
        int localey;
        string tempy;
        string worky;
//--------------------------------------------------------------------------------------------------------------------------
        if (where_Args.size() > 0) //where arg
        {
            for (int itr = 0; itr < where_Args.size(); itr+=3)
            {
            string arg1 = where_Args[itr];
            string op1 = where_Args[itr+1];
            string ref1 = where_Args[itr+2];
            int commaFlagy;

                for (int title = 0; title < nowFile.size(); title++)        //for loop to find matching title to arg1
                {
                    if (arg1 == nowFile[title].substr(from_Args[0].length()+1, arg1.length()))
                    {
                        for (int bbb = nowFile[title].length(); bbb>=0; bbb--)    //looks to find the column number
                            {
                                if(nowFile[title][bbb] == ',')
                                {  
                                commaFlagy = bbb;
                                break;
                                }
                            }
                            for (int eye = 0; eye < csvFile.size()-1; eye++)
                            {
                        localey = stoi(nowFile[title].substr(commaFlagy+1, nowFile[title].length()-commaFlagy));   // file number
                        string commieNum = nowFile[title].substr(commaFlagy+1,1);

                        
                        worky = iterate(csvFile[eye], localey-1, title);
                        if (worky[worky.length()-1] == '\r')
                        {
                            worky.pop_back();
                        }
                        if (op1 == "=")
                        {
                        if (worky != ref1)
                        {
                            csvFile.erase(csvFile.begin()+eye);

                            eye--;
                        }
                        }
                        else if (op1 == ">=")
                        {
                            if (!(worky == ref1 || worky > ref1))
                        {
                            csvFile.erase(csvFile.begin()+eye);
                            eye--;
                        }
                        }

                        else if (op1 == "<=")
                        {
                            if (!(worky == ref1 || worky < ref1))
                            {
                                csvFile.erase(csvFile.begin()+eye);
                                eye--;

                            }
                        }

                        else if (op1 == ">")
                        {
                            if (!(worky > ref1))
                            {
                                 csvFile.erase(csvFile.begin()+eye);
                                eye--;                               
                            }
                        }

                        else if (op1 == "<")
                        {
                            if (!(worky < ref1))
                            {
                                 csvFile.erase(csvFile.begin()+eye);
                                eye--;                               
                            }
                        }

                        else if (op1 == "<>")
                        {
                            if ((worky == ref1))
                            {
                                 csvFile.erase(csvFile.begin()+eye);
                                eye--;                               
                            }
                        }
                            }
                    }
                }
            }
        }
        
//----------------------------------------------------------------------------------------------------------------------------------------
            int pptop;
                int orderFlag = 0;
                    string compare;


        if (select_Args[0][0] == '*')       // IF SELECT ALL IS CALLED 
        {
            string allNames;
            int commaOne, commaTwo;
            int commaCounter = 0;
            vector<string> printFile;


            for ( i = 0; i < nowFile.size(); i++)
            {
                for (j = 0; j < nowFile[i].length(); j++)
                    {
                        if (nowFile[i][j] == ',' && commaCounter > 0)
                        {
                            commaTwo = j;
                            allNames += nowFile[i].substr(commaOne+1, commaTwo-commaOne);
                            commaOne, commaTwo, commaCounter = 0;
                            break;
                        }
                        if (nowFile[i][j] == ',') 
                        {
                            commaOne = j;
                            commaCounter++;
                        }
                    }
            }
            allNames.pop_back();
            labelFile.push_back(allNames);
            printFile.push_back(allNames);

            
            int subStart = 0;
            string fixIt;
            int q;

           for (i = 0; i <csvFile.size(); i++)    //for loop getting all ROWS
           {
            labelFile.push_back(csvFile[i]);
            }
            
            for (j = 0; j < csvFile.size(); j++)
            {
                for (q = 0; q < csvFile[j].length(); q++)
                {
                    if (((csvFile[j][q] == ' ') && (csvFile[j][q-1] == ',')) ||  q+1 == csvFile[j].length())
                    {
                        fixIt += csvFile[j].substr(subStart, q-subStart);
                        subStart = q+1;
                    }
                    
                }
                subStart = 0;
                //subStart = 0;
                printFile.push_back(fixIt);
                fixIt.clear();
            }

            if (orderBy_Args.size() > 0)    //orderBy function
    {
                int comCount = 0;
                vector<string> strVector;
                string work;
    for (int job = 0; job < printFile.size(); job++)
    {
        for (int bog = 0; bog <= printFile[job].length(); bog++)
            {
                if (printFile[job][bog] == ',' || bog == printFile[job].length())
                {
                    
                    work = iterate(printFile[job], comCount);
                        comCount++;
                        //if (finalFile.size() != 0)
                        strVector.push_back(work);
                }
                
            }
       
  
            
            finalFile.push_back(strVector);
            strVector.clear();
            comCount = 0;

    }
    finalFile.pop_back();

        finalFile = orderMe(finalFile,orderBy_Args,2,selectLen,compare); 
        orderFlag = 1;
    }

    if (orderFlag == 0)
    {
           for (int ii = 0; ii < labelFile.size()-1; ii++)
             cout << printFile[ii] << endl;
    }

             if (orderFlag == 1)
             {
                    int jC;
                    int iC = 0;
                        for(i = 0; i < finalFile.size(); i++)       //PRINT FUNCTION FOR GENERAL SELECT
                        {
                            for (j = 0; j < finalFile[i].size(); j++)
                            {
                                jC = j+1;

                                if (i == 0)
                                {
                                    if(jC != finalFile[i].size())
                                    {
                                    cout << finalFile[i][j] << ",";
                                    }
                                    else 
                                    {
                                        cout << finalFile[i][j];
                                        if (orderFlag == 1) cout << endl;
                                    }
                                    continue;
                                }
                            
                                if (orderFlag == 1)
                                {
                                    if(iC != finalFile[0].size()-1)
                                    {
                                        cout << finalFile[i][j] << ",";
                                        iC++;
                                    }
                                    else 
                                    {   
                                    cout << finalFile[i][j] << endl;
                                    iC = 0;
                                    }   

                                continue;

                                }
                            }
                        }
             }




            labelFile.clear();
            select_Args.clear();
            from_Args.clear();
            where_Args.clear();
            orderBy_Args.clear();
            csvData.clear();
            row.clear();
            csvFile.clear();
            nowFile.clear();
            finalFile.clear();
            labelFile.clear();
            tempFile.clear();
            printFile.clear();
        continue;
        }
//---------------------------------------------------------------------------------------------------------------------------------
        for (i = 0; i < selectLen; i++)    //for loop getting all column labels            //ANY OTHER SELECTION
        {
            labelFile.push_back(select_Args[i]);
        }
        finalFile.push_back(labelFile);
        labelFile.clear();
        


        int zztop;
    for (zztop = 0; zztop < csvFile.size()-1; zztop++) //FOR LOOP ITERATES THROUGH ALL OPTIONS IN CSV FILE
    {
    
        for (i = 0; i < selectLen; i++)    //ITERATES THROUGH EACH LINE OF CSV FILE LOOKING FOR PARAMETERS

            {       //
                for(j = 0; j < nowFile.size(); j++) //
                {
              
                    if (select_Args[i] == nowFile[j].substr(from_Args[0].length()+1, select_Args[i].length())) //if the column title matches search
                        {                                                                                      //TAKEN FOR ORDERBY
                            for (b = nowFile[j].length(); b>=0; b--)    //looks to find the column number
                            {
                                if(nowFile[j][b] == ',')
                                {  
                                commaFlag = b;
                                break;
                                }
                            }
                        
                        locale = stoi(nowFile[j].substr(commaFlag+1, nowFile[j].length()-commaFlag));   // file number
                    
                        string temp;
                        string commaNum = nowFile[j].substr(commaFlag+1,1);
                    

                        string work = iterate(csvFile[zztop], locale-1, j);
                        labelFile.push_back(work);
                    }
                    
                    
                }
                    finalFile.push_back(labelFile);
                    labelFile.clear();

            }
            
                
        
    }
    
//------------------------------------------------------------------------------------------------------------------------------------------------------------------


    if (orderBy_Args.size() > 0)    //orderBy function
    {
        finalFile = orderMe(finalFile,orderBy_Args,orderFlag,selectLen,compare); 
        orderFlag = 1;
    }

    int jC;
    int iC = 0;

    //----------------------------------------------------------------------------------------------------------------------------------------

    for(i = 0; i < finalFile.size(); i++)       //PRINT FUNCTION FOR GENERAL SELECT
    {
                {
                    for (j = 0; j < finalFile[i].size(); j++)
                        {
                            jC = j+1;

                            if (i == 0)
                            {
                                if(jC != finalFile[i].size())
                                cout << finalFile[i][j] << ",";
                                else 
                                {cout << finalFile[i][j];
                                if (orderFlag == 1)
                                    cout << endl;
                                }
                                continue;
                                
                            }
                            

                            if (orderFlag == 1)
                            {
                                if(iC != selectLen-1)
                                {
                                cout << finalFile[i][j] << ",";
                                iC++;
                                }
                                else 
                                {cout << finalFile[i][j] << endl;
                                iC = 0;
                                }
                                continue;
                            }

                             if (i%selectLen != 0)
                            {
                                cout << finalFile[i][j] << ",";
                            }
                            else if (i+1%selectLen != 0)
                            {
                            cout << finalFile[i][j] ;
                            }
                        }
                        if (i%selectLen == 0 && orderFlag != 1)
                        {
                        cout << endl;
                        }

                }
                
    }
        select_Args.clear();
        from_Args.clear();
        where_Args.clear();
        orderBy_Args.clear();
        csvData.clear();
        row.clear();
        csvFile.clear();
        nowFile.clear();
        finalFile.clear();
        labelFile.clear();
        tempFile.clear();
    }
            return 0;

        }

