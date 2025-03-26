#include "Table.h"

// Task 9
Table::Table()
{
totalColumns = 0;
columnHead = nullptr;
}

// Task 10
Table::~Table()
{
    //cout << "Destroyy lu " << endl;
    if (columnHead != nullptr)
    {
        while (columnHead->next != nullptr)
        {
            columnHead = columnHead->next;
        }

        while (columnHead->prev != nullptr)
        {
            //cout << "aa" << endl;
            columnHead->clearAllCells();
            //cout << "bb " << endl;
            columnHead = columnHead->prev;
            //cout << "cc" << endl;
            columnHead->next->prev = nullptr;
            //cout << "1st del" << endl;
            delete columnHead->next;
            //cout << "ee" << endl;
            columnHead->next = nullptr;
        }
        columnHead->clearAllCells();
        //cout << "2nd del" << endl;
        delete columnHead;
        columnHead = nullptr;
    }
}

// Task 11
Column* Table::findColumn(int colNum) const
{
    if (colNum > totalColumns)
        return nullptr;
    else
    {
        Column* find = columnHead;
        for (int i = 0; i < colNum; i++)
        {
            find = find->next;
        }
        return find;
    }
}

// Task 12
void Table::copyInsertColumn(int fromColNum, int toColNum)
{
    if (fromColNum > (totalColumns - 1))  //non-existing, empty from
    {
        //cout << "not existing" << endl;
        if (toColNum > (totalColumns - 1))  //no need do anything
            return;
        
        else    //perform insertion
        {
            //cout << "1st new" << endl;
            Column* search12 = findColumn(toColNum); 
            Column* obj12 = new Column;
            if (search12->prev == nullptr)   //insert at 1st col
            {
                //cout << "1111111" << endl;
                columnHead = obj12;
                obj12->prev = nullptr;
                obj12->next = search12;
                obj12->next->prev = obj12;
                totalColumns++;
            }
            else
            {
                //cout << "Not first snow" << endl;
                search12->prev->next = obj12;
                //cout << "AAA" << endl;
                obj12->prev = search12->prev;
                //cout << "bbb" << endl;                
                search12->prev = obj12;
                //cout << "ccc" << endl;                
                obj12->next = search12;
                totalColumns++;
                //cout << "siuu" << endl;
            }
        }
    }

    else  //existing from
    {
        //cout << "Copy from existing thing" << endl;
        Column* from = findColumn(fromColNum);


        if (from->getRowHead() == nullptr && (toColNum > (totalColumns - 1))){
            //cout << "Lets leave now " << endl;
            return;
            
            }

        else if (toColNum > (totalColumns - 1))  //create new columns until there
        {
            //cout << "need some new boxes" << endl;
            Column* search12 = columnHead;
            for (int i = 0; i < (totalColumns - 1); i++)
            {
                //cout << "searching existing boxes " << i << endl;  
                search12 = search12->next;
            }
            /*if (totalColumns == 1)
            {
                search12 = search12->next;
            }*/
            for (int i = 0; i < (toColNum - totalColumns); i++)
            {
                //cout << "2nd new" << endl;
                search12->next = new Column;
                //cout << "aaa" << endl;
                search12->next->prev = search12;
                //cout << "bbb" << endl;
                search12 = search12->next;
                //cout << "ccc" << endl;
                search12->next = nullptr;
                //cout << "ddd" << endl;                
                totalColumns++;
                //cout << "no need create more" << endl;
            }

            //cout << "Start insertion " << endl;
            //cout << "3rd new" << endl;
            Column* obj12 = new Column(*from);
            if (from->getRowHead() != nullptr)
            {
                //cout << "Here not nullrow"<< endl;
                search12->next = obj12;
                obj12->next = nullptr;
                obj12->prev = search12;
                if (obj12->next != nullptr)
                    obj12->next->prev = obj12;
                totalColumns++;
            }

            else
                totalColumns--;
        }

        else
        {
            //cout << "Just insertion " << endl;
            Column* search12 = findColumn(toColNum);
            
            if (toColNum == 0)   //insert at 1st col
            {
                //cout << "4th new" << endl;
                Column* obj12 = new Column(*from);
                //cout << "At 1st " << endl;
                columnHead = obj12;
                obj12->prev = nullptr;
                obj12->next = search12;
                obj12->next->prev = obj12;
                totalColumns++;
                //cout << "End of 1st " << endl;
            }

            else if (toColNum > 0)  //insert not at 1st col
            {
                Column* obj12;
                //cout << "Not at beginning" << endl;
                
                if (from->getRowHead() != nullptr)
                {
                    //cout << "5th new" << endl;
                    obj12 = new Column(*from);
                    search12->prev->next = obj12;
                    obj12->prev = search12->prev;
                    obj12->next = search12;
                    search12->prev = obj12;
                                    
                    totalColumns++;
                    //cout << "1yo, insertion finished" << endl;
                }
                
                else
                {
                   // cout << "6th new" << endl;
                    obj12 = new Column;
                    search12->prev->next = obj12;
                    obj12->prev = search12->prev;
                    obj12->next = search12;
                    search12->prev = obj12;
                                    
                    totalColumns++;
                    //cout << "2woo, insertion finished" << endl;
                }

            }

            else
                return;
        }
    }
}

// Task 13
void Table::deleteColumn(int colNum)
{
    //cout << "in t13 column is " << colNum << endl;
    Column* temp13 = findColumn(colNum);
    
    if (colNum > (totalColumns - 1) || totalColumns == 0)
    {
        //cout << "Go back home " << colNum << endl;
        return;
    }

    else if (colNum == 0 && colNum < (totalColumns - 1))
    {
       // cout << "First column" << endl;
        temp13->clearAllCells();
        //cout << "a1111" << endl;
        columnHead = temp13->next;
        //cout << "b222" << endl;
        temp13->next->prev = nullptr;
        temp13->next = nullptr;
        //cout << "21th del" << endl;
        delete temp13;
        temp13 = nullptr;
        totalColumns--;
    }
    else if (colNum > 0 && colNum < (totalColumns - 1))   //middle
    {
        //cout << "At middle columns" << endl;
        temp13 = findColumn(colNum);
        temp13->prev->next = temp13->next;
        temp13->next->prev = temp13->prev;
        temp13->next = nullptr;
        temp13->prev = nullptr;
        temp13->clearAllCells();
        //cout << "20th del" << endl;
        delete temp13;
        temp13 = nullptr;
        totalColumns--;
    }

    else        //end
    {
        //cout << "Inside else now "<< endl;
        temp13 = findColumn(colNum);
        
        totalColumns--;
        if (temp13->prev != nullptr)
        {
            temp13->clearAllCells();
            //cout << " go into if" << endl;
            temp13 = temp13->prev;
            temp13->next->prev = nullptr;
            //cout << "11th del" << endl;
            delete temp13->next;
            temp13->next = nullptr;

            while (temp13->getRowHead() == nullptr)
            {
                //cout << "Recursive check del col " << endl;
                temp13->next = nullptr;
                if (temp13->prev == nullptr)
                {
                    columnHead = nullptr;
                    //cout << "12th del " << endl;
                    delete temp13;
                    temp13 = nullptr;
                    totalColumns--;
                    break;
                }
                //cout << "13th del" << endl;
                temp13 = temp13->prev;
                temp13->next->prev = nullptr;
                delete temp13->next;
                temp13->next = nullptr;
                totalColumns--;
            }
            //cout << "end siu" << endl;
        }
        else
        {
            temp13->clearAllCells();
            columnHead = nullptr;
            //cout << "14th del" << endl;
            delete temp13;
            temp13 = nullptr;
            totalColumns--;
        }
    }

}

// Task 14
Cell *Table::findCell(int colNum, int rowNum) const
{   
    if (colNum >= totalColumns)
        return nullptr;

    else
    {
        Column* address = findColumn(colNum);
        return address->findCell(rowNum);
    }
}

// Task 15
void Table::modifyCell(int colNum, int rowNum, const string &value)
{
    if (colNum < totalColumns) //insert columns
    {
        //cout << "Just insert columns" << endl;
        Column* search15 = columnHead;
        for (int i = 0; i < totalColumns; i++)
        {
            if (i == colNum)
            {
                search15->modifyCell(rowNum, value);
                break;
            }
            search15 = search15->next;
        }
    }
    else    //create new columns and new rows
    {
        Column* create15 = columnHead;
        int cnt = 0;
        while (create15 != nullptr)
        {
            if (create15->next == nullptr)
            {
                cnt++;
                break;
            }
            else
            {
                create15 = create15->next;
                cnt++;
            }
        }

        if (cnt == 0 && colNum == 0)    // 0 < (0 - 0) extreme case
        {
      //      cout << "7th new" << endl;
            create15 = new Column;
            create15->prev = nullptr;
            create15->next = nullptr;
            create15->modifyCell(rowNum, value);
            columnHead = create15;
            totalColumns++;
        }

        //else if (cnt != rowNum)         //consider cnt = 1 and rowNum = 1 -> just change value
        else
        {
            totalColumns = colNum + 1;
            if (cnt == 0)
            {
              //  cout << "8th new" << endl;
                create15 = new Column;
                columnHead = create15;
                create15->prev = nullptr;
                create15->next = nullptr;
                if (colNum == cnt)
                    create15->modifyCell(rowNum, value);
                cnt++;
            }

            for (int i = 0, temp = 1; i <= (colNum-cnt); i++)     //consider cnt = 1 and rowNum = 2, then create 2 boxes
            {
                //cout << "9th new" << endl;
                create15->next = new Column;
                create15->next->prev = create15;
                create15 = create15->next;
                
                if ((colNum) == (i + cnt))
                {
                    create15->modifyCell(rowNum, value);
                    create15->next = nullptr;
                    break;
                }
                create15->next = nullptr;
                temp++;
            }
        }
    }
}


// Task 16
void Table::clearCell(int colNum, int rowNum)
{
    if ((colNum > (totalColumns - 1)) || totalColumns == 0)
    {
        return;   
    }  

    else if (colNum < (totalColumns - 1))  //deletion at middle
    {
        //cout << "Columns at middle" << endl;
        Column* check16 = findColumn(colNum);
        check16->clearCell(rowNum);
    }
    else if (colNum == (totalColumns - 1))  //deletion at the end
    {
        //cout << "Columns at the end" << endl;
        Column* check16 = findColumn(colNum);
        check16->clearCell(rowNum);

        while (check16->getRowHead() == nullptr)
        {
            //cout << "while loop checking" << endl;
            if (check16->prev != nullptr)
            {
                //cout << "prev exists" << endl;
                check16 = check16->prev;
                //cout << "aaa" << endl;
                check16->next->prev = nullptr;
                //cout << "bbb" << endl;
                //cout << "3rd del col" << endl;
                delete check16->next;
                check16->next = nullptr;
                //cout << "ddd " << endl;
                
                totalColumns--;
            }
            else if (check16->prev == nullptr)
            {
                //cout << "4th del col" << endl;
                //check16->next->prev = nullptr;
                delete columnHead;
                columnHead = nullptr;
                totalColumns--;
                //cout << "deleted " << endl;
                break;
            }

        }
    }   
}

// ---------------------- provided functions: DO NOT MODIFY --------------------------
void Table::printTable() const
{

    // find the max number of rows
    int maxRows = 0;
    Column *currCol = columnHead;
    while (currCol != nullptr)
    {
        if (currCol->getTotalRows() > maxRows)
        {
            maxRows = currCol->getTotalRows();
        }
        currCol = currCol->next;
    }

    cout << "totalColumns: " << totalColumns << "\t ";
    cout << "maxRows: " << maxRows << endl;


    // string styles
    string line(12, '-');
    string doubleline(12, '=');
    string space(12, ' ');
    string headerline((totalColumns+1)*12, '=');


    // print table table header
    cout << headerline << endl;
    cout << " " << std::setw(10) << "" << "|";
    for (int i = 0; i < totalColumns; ++i)
    {
        cout<< "|" << std::setw(10) << "column "+to_string(i)+ " " << "|";
    }
    cout << endl;
    cout << headerline << endl;
    

    // print table body (row by row)
    string hline;
    for (int i = 0; i < maxRows; ++i)
    {
        //cout << "squeeze time "<< i << endl;
        hline = doubleline;    
        cout<< " " << std::setw(10) << "row "+to_string(i) + "  "<< " ";


        currCol = columnHead;

        while (currCol != nullptr)
        {
            Cell *currCell = currCol->findCell(i);
            if (currCell == nullptr)
            {
                hline += space;
                cout << " "<< std::setw(10) <<"" << " ";
            }
            else
            {
                hline += line;
                cout << "|" << std::setw(10) << currCell->value << "|";
            }
            currCol = currCol->next;
        }
        cout << endl;
        cout << hline << endl;

    }
    cout << endl;
    return;

}
