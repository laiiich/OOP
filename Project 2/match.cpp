#include "match.h"

bool Match::outOfBound(int row, int col) const {
    // Task 4.1: Check whether a given position is out of bound.
    if (row <= BOARD_SIZE && col <= BOARD_SIZE && row >= 0 && col >= 0)
        return false;
    else
        return true; //out of bound return true
}

bool Match::setPlayer(Player* p, int index){
    // Task 4.2: Set the player with the given index.
    // Case 1: Wrong index.
    if (index != 1 && index != 0)
        return false;

    // Case 2: Player already exists.
    if (players[index] != nullptr)
        return false;
    
    /*for (int i = 0; i < p->row; i++)
    {
        for (int j = 0; j < p->col; j++)
        {
            if (board[i][j] == nullptr)
                continue;
            
            if (board[i][j]->getSymbol() == p->getSymbol())
                return false;
        }
    }*/

    // Case 3: Out of bound or the position is already occupied.
    if (outOfBound(p->row, p->col) == true || board[p->row][p->col] != nullptr)
        return false;

    // Case 4: Otherwise, the player can be set.
    board[p->row][p->col] = p;
    players[index] = p;
    return true;

}

bool Match::addItem(Item* item, int row, int col){
    // Task 4.3: Add the item to the board.
    // Case 1: Out of bound or the position is already occupied.
    if (outOfBound(row, col) == true || board[row][col] != nullptr)
        return false;
    
    // Case 2: Scan the whole board to check whether there exists any item with the same name.
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == nullptr)
                continue;
            if (item->getName() == board[i][j]->getName()) //error
                return false;
        }
    }
    
    // Case 3: Otherwise, the item can be added.
    board[row][col] = item;
    return true;
    
}

bool Match::move(char c){
    // Task 4.4: Move the player.
    if (c != 'w' && c != 'a' && c != 's' && c != 'd')
        return false;
    
    if (c == 'a') //left
    {
        if (players[curRound]->col == 0)
            return false;
        

        if (board[players[curRound]->row][players[curRound]->col - 1] == nullptr)
        {
            board[players[curRound]->row][players[curRound]->col - 1] = players[curRound];
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->col -= 1;
        }

        else if (board[players[curRound]->row][players[curRound]->col - 1]->getPieceType() == BOMB)
        {
            Item* itemptr = dynamic_cast<Item*>(board[players[curRound]->row][players[curRound]->col - 1]);
            players[curRound]->hp -= itemptr->getDefaultPower();
            delete board[players[curRound]->row][players[curRound]->col - 1];
            board[players[curRound]->row][players[curRound]->col - 1] = players[curRound];
            
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->col -= 1;
            if (players[curRound]->hp <= 0)  //GG
            {
                curRound = -1;
                return true;
                //board[players[curRound]->row][players[curRound]->col - 1] = nullptr;
            }
        }

        else if (board[players[curRound]->row][players[curRound]->col - 1]->getPieceType() == ATTACK_ITEM)
        {
            AttackItem* atkptr = dynamic_cast<AttackItem*>(board[players[curRound]->row][players[curRound]->col - 1]);
            players[curRound]->insertAttackItem(atkptr);
            board[players[curRound]->row][players[curRound]->col - 1] = players[curRound];
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->col -= 1;
        }

        else if (board[players[curRound]->row][players[curRound]->col - 1]->getPieceType() == DEFENSE_ITEM)
        {
            DefenseItem* dfptr = dynamic_cast<DefenseItem*>(board[players[curRound]->row][players[curRound]->col - 1]);
            players[curRound]->insertDefenseItem(dfptr);
            board[players[curRound]->row][players[curRound]->col - 1] = players[curRound];
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->col -= 1;
        }

        else  //players meet
        {
            battle();
            curRound = -1;
        }
    }
    
    if (c == 'd') //right
    {
        if (players[curRound]->col == BOARD_SIZE - 1)
            return false;

        if (board[players[curRound]->row][players[curRound]->col + 1] == nullptr)
        {
            board[players[curRound]->row][players[curRound]->col + 1] = players[curRound];
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->col += 1;
        }

        else if (board[players[curRound]->row][players[curRound]->col + 1]->getPieceType() == BOMB)
        {
            Item* itemptr = dynamic_cast<Item*>(board[players[curRound]->row][players[curRound]->col + 1]);
            players[curRound]->hp -= itemptr->getDefaultPower();

            delete board[players[curRound]->row][players[curRound]->col + 1];
            board[players[curRound]->row][players[curRound]->col + 1] = players[curRound];
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->col += 1;
            if (players[curRound]->hp <= 0)  //GG
            {
                curRound = -1;
                return true;
                //board[players[curRound]->row][players[curRound]->col + 1] = nullptr;
            }
        }

        else if (board[players[curRound]->row][players[curRound]->col + 1]->getPieceType() == ATTACK_ITEM)
        {
            AttackItem* atkptr = dynamic_cast<AttackItem*>(board[players[curRound]->row][players[curRound]->col + 1]);
            players[curRound]->insertAttackItem(atkptr);
            board[players[curRound]->row][players[curRound]->col + 1] = players[curRound];
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->col += 1;
        }

        else if (board[players[curRound]->row][players[curRound]->col + 1]->getPieceType() == DEFENSE_ITEM)
        {
            DefenseItem* dfptr = dynamic_cast<DefenseItem*>(board[players[curRound]->row][players[curRound]->col + 1]);
            players[curRound]->insertDefenseItem(dfptr);
            board[players[curRound]->row][players[curRound]->col + 1] = players[curRound];
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->col += 1;
        }

        else  //players meet
        {
            battle();
            curRound = -1;
        }

    }
    
    if (c == 'w')
    {
        if (players[curRound]->row == 0)
            return false;

        if (board[players[curRound]->row - 1][players[curRound]->col] == nullptr)
        {
            board[players[curRound]->row - 1][players[curRound]->col] = players[curRound];
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->row -= 1;
        }

        else if (board[players[curRound]->row - 1][players[curRound]->col]->getPieceType() == BOMB)
        {
            Item* itemptr = dynamic_cast<Item*>(board[players[curRound]->row - 1][players[curRound]->col]);
            players[curRound]->hp -= itemptr->getDefaultPower();

            delete board[players[curRound]->row - 1][players[curRound]->col];
            board[players[curRound]->row - 1][players[curRound]->col] = players[curRound];
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->row -= 1;
            if (players[curRound]->hp <= 0)  //GG
            {
                curRound = -1;
                return true;
                //board[players[curRound]->row - 1][players[curRound]->col] = nullptr;
            }
        }

        else if (board[players[curRound]->row - 1][players[curRound]->col]->getPieceType() == ATTACK_ITEM)
        {
            AttackItem* atkptr = dynamic_cast<AttackItem*>(board[players[curRound]->row - 1][players[curRound]->col]);
            players[curRound]->insertAttackItem(atkptr);
            board[players[curRound]->row - 1][players[curRound]->col] = players[curRound];
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->row -= 1;
        }

        else if (board[players[curRound]->row - 1][players[curRound]->col]->getPieceType() == DEFENSE_ITEM)
        {
            DefenseItem* dfptr = dynamic_cast<DefenseItem*>(board[players[curRound]->row - 1][players[curRound]->col]);
            players[curRound]->insertDefenseItem(dfptr);
            board[players[curRound]->row - 1][players[curRound]->col] = players[curRound];
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->row -= 1;
        }

        else  //players meet
        {
            battle();
            curRound = -1;
        }

    }
    
    if (c == 's')
    {
        if (players[curRound]->row== BOARD_SIZE - 1 )
            return false;

        if (board[players[curRound]->row + 1][players[curRound]->col] == nullptr)
        {
            board[players[curRound]->row + 1][players[curRound]->col] = players[curRound];
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->row += 1;
        }

        else if (board[players[curRound]->row + 1][players[curRound]->col]->getPieceType() == BOMB)
        {
            Item* itemptr = dynamic_cast<Item*>(board[players[curRound]->row + 1][players[curRound]->col]);
            players[curRound]->hp -= itemptr->getDefaultPower();
            delete board[players[curRound]->row + 1][players[curRound]->col];
            
            board[players[curRound]->row + 1][players[curRound]->col] = players[curRound];
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->row += 1;
            if (players[curRound]->hp <= 0)  //GG
            {
                curRound = -1;
                return true;
                //board[players[curRound]->row][players[curRound]->col] = nullptr;
            }
        }

        else if (board[players[curRound]->row + 1][players[curRound]->col]->getPieceType() == ATTACK_ITEM)
        {
            AttackItem* atkptr = dynamic_cast<AttackItem*>(board[players[curRound]->row + 1][players[curRound]->col]);
            players[curRound]->insertAttackItem(atkptr);
            board[players[curRound]->row + 1][players[curRound]->col] = players[curRound];
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->row += 1;
        }

        else if (board[players[curRound]->row + 1][players[curRound]->col]->getPieceType() == DEFENSE_ITEM)
        {
            DefenseItem* dfptr = dynamic_cast<DefenseItem*>(board[players[curRound]->row + 1][players[curRound]->col]);
            players[curRound]->insertDefenseItem(dfptr);
            board[players[curRound]->row + 1][players[curRound]->col] = players[curRound];
            board[players[curRound]->row][players[curRound]->col] = nullptr;
            players[curRound]->row += 1;
        }

        else  //players meet
        {
            battle();
            curRound = -1;
        }

    }

    if (curRound == -1)
        return true;
    else
        curRound = (curRound == 1) ? 0 : 1;
    return true;
}

void Match::battle(){
// Task 5.3: Battle when the two players meet.
    while ((players[0]->hp > 0 && players[1]->hp > 0))
    {
//at least one attack item can be used (i.e., 
//there exists at least one usable attackItem in one player's AttackItemsArray).
        if (&players[0]->attackItems == nullptr && &players[1]->attackItems == nullptr)  //no weapon for both players
        {
            //printBattle(nullptr, nullptr);
            //update curRound here later
            break;
        }
    
        AttackItem* attobj = players[curRound]->attack();   //find the most powerful
    
        if (attobj != nullptr)
        {
            int attpower = attobj->getDefaultPower();
            int hehe = -1;
            DefenseItem* defobj = players[(curRound + 1) % 2]->defense(attobj,hehe);
            
            if (defobj != nullptr)
            {
                if (attpower <= hehe)  //defense is stronger
                {
                    players[(curRound + 1) % 2]->hp -= 0;
                    defobj->reduceRemainingDefensePower(min(attpower,hehe));
                }
                else
                {
                    players[(curRound + 1) % 2]->hp -= (attpower - hehe);
                    defobj->reduceRemainingDefensePower(min(attpower,hehe));
                }
                
                if (players[(curRound + 1) % 2]->hp < 0)
                {
                    //curRound = -1;
                    break;
                }
            }

            else
                players[(curRound + 1) % 2]->hp -= attpower;

            printBattle(attobj, defobj);
            if (players[(curRound + 1) % 2]->hp <= 0)
                {
                    break;
                }
            curRound = (curRound == 1) ? 0 : 1; 
            //cout << "Loop ends" << endl;
        }

        else
        {
            AttackItem* oppo = players[(curRound + 1) % 2]->attack();
            if (oppo != nullptr)
            {
                int attpower = oppo->getDefaultPower();
                int hehe = -1;
                DefenseItem* defobj = players[(curRound + 1) % 2]->defense(oppo,hehe);
                
                if (defobj != nullptr)
                {
                    if (attpower <= hehe)  //defense is stronger
                    {
                        players[(curRound + 1) % 2]->hp -= 0;
                        defobj->reduceRemainingDefensePower(min(attpower,hehe));
                    }
                    else
                    {
                        players[(curRound + 1) % 2]->hp -= (attpower - hehe);
                        defobj->reduceRemainingDefensePower(min(attpower,hehe));
                    }

                    if (players[(curRound + 1) % 2]->hp < 0)
                    {
                        break;
                    }
                }

            printBattle(attobj, defobj);
            if (players[(curRound + 1) % 2]->hp <= 0)
                {
                    break;
                }
            curRound = (curRound == 1) ? 0 : 1; 
            //cout << "Loop ends" << endl;
            }

            else
                break;
        }
    }
    //printBattle(nullptr, nullptr);
    curRound = -1;
}