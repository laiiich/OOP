#include "item.h"

Item::Item(const string &name, char symbol, PieceType pieceType, int defaultPower) : Piece(name, symbol, pieceType), defaultPower(defaultPower){
    // Task 2.1: Implement the constructor of Item.

}

AttackItem::AttackItem(const string &name, char symbol, int defaultPower, int usageTimes) : Item(name, symbol, PieceType(ATTACK_ITEM), defaultPower), usageTimes(usageTimes){
    // Task 2.2: Implement the constructor of AttackItem.
    //cout << this << " is also " << name << endl;
}

DefenseItem::DefenseItem(const string &name, char symbol, int defaultPower, int remainingDefensePower) : Item(name, symbol, PieceType(DEFENSE_ITEM), defaultPower), remainingDefensePower(remainingDefensePower){
    // Task 2.3: Implement the constructor of DefenseItem.
}
