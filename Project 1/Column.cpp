#include "Column.h"

// Task 1
Column::Column()
{
    totalRows = 0;
    rowHead = nullptr;
    prev = nullptr;
    next = nullptr;
}

// Task 2
Column::Column(Column *prev)
{
    totalRows = 0;
    rowHead = nullptr;
    Column::prev = prev;
    next = nullptr;
}

// Task 3
Column::Column(const Column &c)
{
    totalRows = c.totalRows;
    prev = nullptr;
    next = nullptr;
    if (c.rowHead == nullptr)
        rowHead = nullptr;

    else
    {
        Cell* search3 = c.rowHead;
        //Column t3 = new Column;
        int cnt = 0;
        //while (search3->next != nullptr)

        while (cnt < c.totalRows)
        {
            Cell* temp;

            if (cnt == 0)
            {
                //cout << "new cell 1" << endl;
                temp = new Cell;
                rowHead = temp;
                temp->prev = nullptr;
            }

            else
            {
                //cout << "new cell 2" << endl;
                temp->next = new Cell;
                temp->next->prev = temp;
                temp = temp->next;
            }
            
            temp->value = search3->value;        //assign value  
            temp->next = nullptr;
            search3 = search3->next;
            cnt++;
        }
    }
}

// Task 4
Column::~Column()
{
    //cout << "Call destructor" << endl;
    if (rowHead != nullptr)
    {
        while (rowHead->next != nullptr)
        {
            //cout << "searching" << rowHead->value << endl;
            rowHead = rowHead->next;
        }

        while (rowHead->prev != nullptr)
        {
            //cout << "destroy" << rowHead->value << endl;
            rowHead = rowHead->prev;
            rowHead->next->prev = nullptr;
            //cout << "cell del 1" << endl;
            delete rowHead->next;
            rowHead->next = nullptr;
        }
       // cout << "cell del 2" << endl;
        //cout << rowHead->value << endl;
        delete rowHead;
        rowHead = nullptr;
    }
    //rowHead = nullptr;
}

// Task 5
Cell *Column::findCell(int rowNum)
{    
    if (rowHead == nullptr || rowNum > (totalRows - 1))
        return nullptr;
    
    else
    {
        int temp = 0;
        Cell* ptrtemp = rowHead;

        while (ptrtemp != nullptr)
        {
            if (rowNum == temp)
                return ptrtemp;
            
            else if (rowNum > temp)
            {
                ptrtemp = ptrtemp->next;
                temp++;
            }

            else        //extreme case
            {
                break;
            }
        }
        return nullptr;
    }
}

// Task 6
void Column::modifyCell(int rowNum, const string &value)
{
    if (rowNum < totalRows) //no creation of new cell
    {
        if (rowNum == 0)    //insert at rowNum = 0
            rowHead->value = value;

        else
        {
            int temp = 0;
            Cell* search = rowHead;
            for (temp; temp < rowNum; temp++)
                search = search->next;
            search->value = value;
        }
    }

    else  //create new cell
    { 
        Cell* search = rowHead;
        
        int cnt = 0;
        while (search != nullptr)
        {
            if (search->next == nullptr)
            {
                cnt++;
                break;
            }
            else
            {
                search = search->next;
                cnt++;
            }
        }

        //new boxes need to be created:
        if (cnt == 0 && rowNum == 0)    // 0 < (0 - 0) extreme case
        {
            //cout << "new cell 3" << endl;
            search = new Cell;
            search->value = value;
            search->prev = nullptr;
            search->next = nullptr;
            rowHead = search;
            totalRows++;
        }

        //else if (cnt != rowNum)         //consider cnt = 1 and rowNum = 1 -> just change value
        else
        {
            totalRows = rowNum + 1;
            if (cnt == 0)
            {
                //cout << "new cell 4" << endl;
                search = new Cell;
                search->value = "";
                search->prev = nullptr;
                search->next = nullptr;
                rowHead = search;
                cnt++;
            }

            for (int i = 0, temp = 1; i <= (rowNum-cnt); i++)     //consider cnt = 1 and rowNum = 2, then create 2 boxes
            {
                //cout << "new cell 5" << endl;
                search->next = new Cell;
                search->next->prev = search;
                search = search->next;   
                
                if ((totalRows) == (temp + cnt)) //assign value
                    search->value = value;
                else    //skip
                    search->value = "";

                search->next = nullptr;
                temp++;
            }
        }
    }
}

// Task 7
void Column::clearCell(int rowNum)
{
    //cout << "love story" << endl;
    if ((rowNum > totalRows) || totalRows == 0)
    {
        return;
    }

    else if (rowNum < (totalRows - 1))  //middle
    {
        Cell* search7 = rowHead;
        for (int i = 0; i < rowNum; i++)
        {
            search7 = search7->next;
        }
        search7->value = "";
    }

    else if (rowNum == 0 && totalRows == 1)
    {
        //cout << "cell del 3" << endl;
        rowHead->value = "";
        delete rowHead;
        rowHead = nullptr;
        //cout << "deekekeke" << endl;
        totalRows--;
    }

    else if (rowNum == (totalRows - 1))    //at the end
    {
        //cout << "at the end" << endl;
        Cell* search7 = rowHead;
        for (int i = 0; i < rowNum; i++)
        {
            search7 = search7->next;
        }

        search7->value = "";
        
        if (search7->prev != nullptr)   
        {
            search7 = search7->prev;
            //cout << "cell del 4" << endl;
            search7->next->prev = nullptr;
            delete search7->next;             //added on 2:20am
            search7->next = nullptr;
            totalRows--;
            //cout << "ended" << endl;


            while (search7->value == "")    //check if above cells are empty
            {
                //cout << "inside while" << endl;
                search7->next = nullptr;
                if (search7->prev == nullptr)   //very last row
                    {
                        //cout << "cell del 5" << endl;
                        rowHead = nullptr;
                        delete search7;
                        search7 = nullptr;
                        totalRows--;
                        break;
                    }
                //cout << "cell del 6" << endl;
                search7 = search7->prev;
                search7->next->prev = nullptr;
                delete search7->next;
                search7->next = nullptr;
                totalRows--;
            }
            //cout << "siuu" << endl;
        }

        else    //only one row left
        {
            //cout << "cell del 7" << endl;
            rowHead = nullptr;
            delete search7;
            search7 = nullptr;
            totalRows--;
        }
    }
}

// Task 8
void Column::clearAllCells()
{
    if (rowHead == nullptr)
        return;
    
    Cell* search = rowHead;

    while (search->next != nullptr)
    {
        search = search->next;
        search->value = "";
    }

    while (search->prev != nullptr)
    {
        search = search->prev;
        search->next->prev = nullptr;
        //cout << "cell del 8" << endl;
        delete search->next;
        search->next = nullptr;
    }
   // cout << "cell del 9" << endl;
    delete search;
    rowHead = nullptr;
    totalRows = 0;
}

// ---------------------- provided functions: DO NOT MODIFY --------------------------
void Column::printColumn() const
{
    // string styles
    string line(12, '-');
    string doubleline(12, '=');
    string space(12, ' ');



    cout << "totalRows: " << totalRows << endl;

    // table header
    cout << doubleline + doubleline << endl;
    cout << " " << std::setw(10) << "" << " ";
    cout << "|" << std::setw(10)  << "column " << "|" <<endl;   
    cout << doubleline + doubleline << endl;

    // table body (row by row)
    Cell* current = rowHead;
    for (int i =0 ; i < totalRows; ++i){
        cout << " " << std::setw(10) << "row " + to_string(i) + " " << " " ;
        cout << "|" << std::setw(10) << current->value << "|" << endl;
        current = current->next;
        cout << doubleline + line << endl;
    }

    cout << endl;

}
