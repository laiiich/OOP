#include "array.h"

bool ItemsArray::find(const string &name) const{
    // Task 3.1: Find an item in the ItemsArray.
    if (arraySize == 0)
        return false;
    else
    {
        for (int i = 0; i < arraySize; i++)
        {
            if (items[i]->getName() == name)
            {
                return true;
            }
        }
        return false;
    }
}

bool ItemsArray::insert(Item* item){
    // Task 3.2: Insert an item into the ItemsArray.
    string temp = item->getName();
    if (find(temp) == true || item == nullptr)
    {
        //cout << "gg false" << endl;
        return false;
    }

    else
    {
        Item** newarr = new Item*[arraySize + 1];
        int cnt = 0;
        while (cnt < arraySize)
        {
            if (items[cnt]->getDefaultPower() > item->getDefaultPower()) //arrayitem > input
            {
                cnt++;
                if (cnt == arraySize) //insertion at the end
                    break;
                //cnt++;
                continue;
            }

            else if (items[cnt]->getDefaultPower() < item->getDefaultPower()) //arrayitem < input
            {
                for (int i = 0; i < cnt; i++)
                {
                    newarr[i] = items[i];
                }
                newarr[cnt] = item;
                for (int j = cnt; j < arraySize; j++)
                {
                    newarr[j + 1] = items[j];
                }
                arraySize++;

                delete [] items;
                //for (int i = 0; i < arraySize - 1; i++)
                //    delete items[i];
                items = newarr;
                return true;
            }

            else if (items[cnt]->getDefaultPower() == item->getDefaultPower()) //arrayitem == input
            {
                cnt++;
                for (int i = 0; i < cnt; i++)
                {
                    //cout << "Inside for " << items[i]->getName() << endl;
                    newarr[i] = items[i];
                }
                newarr[cnt] = item;
                for (int j = cnt; j < arraySize; j++)
                {
                    newarr[j + 1] = items[j];
                }
                arraySize++;
                delete [] items;
                items = newarr;
                //cout << "B true" << item->getName() << endl;
                return true;
            }
        }
        
        if (arraySize != 0)
        {
            for (int i = 0; i < arraySize; i++)
            {
                newarr[i] = items[i];
                
            }
        }
        //cout << "add now " << endl;
        newarr[arraySize++] = item;
        delete [] items;
        items = newarr;
        //cout << "C true" << item->getName() << endl;
        return true;
    }
}

AttackItem* AttackItemsArray::attack(){
    // Task 5.1: Choose the most powerful attack item.
    if (items == nullptr)
        return nullptr;
    for (int i = 0; i < arraySize; i++)
    {
        //cout << items[i]->getName() << "Messi " << endl;
        if (items[i]->getPieceType() == ATTACK_ITEM)
        {
            AttackItem* atitem = dynamic_cast<AttackItem*>(items[i]);
            if (atitem->usable() == false)
                continue;
            else
            {
                atitem->decrementUsageTimes();
                return atitem;
            }
        }

    }
    return nullptr;
}

DefenseItem* DefenseItemsArray::defense(AttackItem* attackItem, int& defense_power){
    // Task 5.2: Choose the best defending item.
    int finalpower = 0, index = -1, dpower;
    for (int i = 0; i < this->arraySize; i++)    //check the largest power
    {
        dpower = 0;
        if (this->items[i] == nullptr)
            continue;
        else
        {
            if (items[i]->getPieceType() == DEFENSE_ITEM)
            {
                if (dynamic_cast<DefenseItem*>(this->items[i])->getRemainingDefensePower() > 0)
                {
                    if (this->items[i]->getDefaultPower() > dpower)     //P1
                    {
                        dpower = dynamic_cast<DefenseItem*>(items[i])->getDefaultPower();
                    }
                    
                    DefenseItem* temp = dynamic_cast<DefenseItem*>(this->items[i]);     //P2
                    Dictionary* address = temp->getDefensePair();
                    int value = address->find(attackItem->getName());
                    if (value != NULL_VALUE)    //can be found
                    {
                        if (value > dpower)
                        {
                            dpower = value;
                        }
                    }

                    if (dynamic_cast<DefenseItem*>(items[i])->getRemainingDefensePower() < dpower)  //P3
                    { 
                        dpower = dynamic_cast<DefenseItem*>(items[i])->getRemainingDefensePower();
                    }
                }
                if (dpower > finalpower)
                {
                    index = i;
                    finalpower = dpower;
                }
            }
        }


    }
    if (index == -1)
        return nullptr;
    else
    {
        defense_power = finalpower;
        //dynamic_cast<DefenseItem*>(items[index])->reduceRemainingDefensePower(finalpower);
        return dynamic_cast<DefenseItem*>(items[index]);
    }

}