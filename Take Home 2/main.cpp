
// OSMAN BERK AN
// 28849
// TAKE HOME 2


#include <iostream>
#include <vector>
#include <string>
#include "feedback.h"

using namespace std;


struct node {
    int digit;
    node * next;
};

node* Possibles[3] = {nullptr, nullptr, nullptr};  // globals
node* Impossibles[3] = {nullptr, nullptr, nullptr};

void sorted_add_node(node*& head, int newData) {  // add node in sorted way to list

    node* newNode = new node();
    newNode->digit = newData;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        return;
    }

    node* prevNode = nullptr;
    node* currNode = head;
    while (currNode != nullptr && currNode->digit < newData) {
        prevNode = currNode;
        currNode = currNode->next;
    }

    if (prevNode == nullptr) {
        newNode->next = head;
        head = newNode;
    } else {
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }
}

void deleteNode(node*& head, int value) {  // delete specific node that chosen its value
    node* current = head;
    node* previous = nullptr;

    while (current != nullptr) {
        if (current->digit == value) {
            if (previous == nullptr) {
                // Node to delete is the head
                head = current->next;
            } else {
                previous->next = current->next;
            }

            delete current;
            return;
        }

        previous = current;
        current = current->next;
    }
}

/* Begin : Code taken from linkedList.cpp */
bool SearchList(node* head, int searchValue)  // if the searched element is in list, it returns true, otherwise false
{
    while (head != nullptr)
    {
        if(head->digit == searchValue) //If the node with the given ID is found
            return true;
        head = head->next;
    }
    //If the code proceeds from here, it means that the whole list is traversed
    //and a node with ID == searchValue could not be found.
    return false;
}
/* End: Code taken from linkedList.cpp*/

//add elements to the linked lists if they are not exist in that slot before. Check & add
void add_to_linked_lists(string secret_str, int ID, string guess)   // most important function be careful
{
    char str_digit1, str_digit2, str_digit3;
    int int_digit1, int_digit2, int_digit3;
    str_digit1 = guess[0];
    str_digit2 = guess[1];  //f.e guess = 952
    str_digit3 = guess[2];
    int_digit1 = str_digit1 - '0';  // integer values of digits to add to linked list
    int_digit2 = str_digit2 - '0';
    int_digit3 = str_digit3 - '0';

    secret_str = get_the_feedback(guess,ID);  // RRY RRG GRY RYG...

    if(secret_str[0] == 'R'){   // for first digit of guess
        if(!SearchList(Impossibles[0],int_digit1)){
            sorted_add_node(Impossibles[0],int_digit1);
        }
        if(!SearchList(Impossibles[1],int_digit1)){
            sorted_add_node(Impossibles[1],int_digit1);
        }
        if(!SearchList(Impossibles[2],int_digit1)){
            sorted_add_node(Impossibles[2],int_digit1);
        }

    }
    else if(secret_str[0] == 'Y'){
        if(SearchList(Possibles[0], int_digit1)){  // if there exist
            deleteNode(Possibles[0],int_digit1);
        }
        // inserted to the impossible list of slot t
        if(!SearchList(Impossibles[0],int_digit1)){
            sorted_add_node(Impossibles[0], int_digit1);
        }

        // inserted to the possible linked lists of the other two slots if it wasn't in the corresponding slot's impossible linked list.
        if(!SearchList(Impossibles[1],int_digit1)){
            if(!SearchList(Possibles[1],int_digit1)){
                sorted_add_node(Possibles[1],int_digit1);
            }

        }
        if(!SearchList(Impossibles[2],int_digit1)){
            if(!SearchList(Possibles[2],int_digit1)){
                sorted_add_node(Possibles[2],int_digit1);
            }

        }
        if(!SearchList(Impossibles[0],int_digit1)){
            sorted_add_node(Possibles[1], int_digit1);
            sorted_add_node(Possibles[2],int_digit1);

        }

    }
    else if(secret_str[0]== 'G'){
        // inserted to the possible link list of slot t
        if(!SearchList(Possibles[0],int_digit1)){
            sorted_add_node(Possibles[0],int_digit1);
        }
        // inserted to the impossible linked lists of other two slots
        if(!SearchList(Impossibles[1],int_digit1)){
            sorted_add_node(Impossibles[1],int_digit1);
        }
        if(!SearchList(Impossibles[2],int_digit1)){
            sorted_add_node(Impossibles[2], int_digit1);
        }
        //removed from the possible linked lists of the other two slots (other than 𝑡), if any.
        if(SearchList(Possibles[1], int_digit1)){
            deleteNode(Possibles[1],int_digit1);
        }
        if(SearchList(Possibles[2], int_digit1)){
            deleteNode(Possibles[2],int_digit1);
        }

        /* all digits except 𝑛 (i.e. from zero to nine except 𝑛) should be inserted to the
        impossible list of slot 𝑡. Also, all other digits (from zero to nine except 𝑛) should be removed, if any, from the possible list of slot 𝑡.*/
        for(int i=0; i<=9; i++){
            if(i != int_digit1){
                if(!SearchList(Impossibles[0],i)){
                    sorted_add_node(Impossibles[0],i);
                }
                if(SearchList(Possibles[0],i)){
                    deleteNode(Possibles[0],i);
                }
            }
        }

    }  // end of first digit's operations

    if(secret_str[1] == 'R'){  // for second digit of guess
        if(!SearchList(Impossibles[0],int_digit2)){
            sorted_add_node(Impossibles[0],int_digit2);
        }
        if(!SearchList(Impossibles[1],int_digit2)){
            sorted_add_node(Impossibles[1],int_digit2);
        }
        if(!SearchList(Impossibles[2],int_digit2)){
            sorted_add_node(Impossibles[2],int_digit2);
        }
    }
    else if(secret_str[1] == 'Y'){
        if(SearchList(Possibles[1], int_digit2)){  // if there exist
            deleteNode(Possibles[1],int_digit2);
        }
        // inserted to the impossible list of slot t
        if(!SearchList(Impossibles[1],int_digit2)){
            sorted_add_node(Impossibles[1], int_digit2);
        }
        // inserted to the possible linked lists of the other two slots if it wasn't in the corresponding slot's impossible linked list.
        if(!SearchList(Impossibles[0],int_digit2)){
            if(!SearchList(Possibles[0],int_digit2)){
                sorted_add_node(Possibles[0], int_digit2);
            }
            //sorted_add_node(Possibles[0], int_digit2);
        }
        if(!SearchList(Impossibles[2],int_digit2)){
            if(!SearchList(Possibles[2],int_digit2)){
                sorted_add_node(Possibles[2], int_digit2);
            }

        }
        if(!SearchList(Impossibles[1],int_digit2)){
            if(!SearchList(Possibles[0],int_digit2)){
                sorted_add_node(Possibles[0], int_digit2);
            }
            if(!SearchList(Possibles[2],int_digit2)){
                sorted_add_node(Possibles[2], int_digit2);
            }
        }


    }
    else if(secret_str[1] == 'G'){
        if(!SearchList(Possibles[1],int_digit2)){
            sorted_add_node(Possibles[1],int_digit2);
        }
        if(!SearchList(Impossibles[0],int_digit2)){
            sorted_add_node(Impossibles[0], int_digit2);
        }
        if(!SearchList(Impossibles[2],int_digit2)){
            sorted_add_node(Impossibles[2], int_digit2);
        }
        if(SearchList(Possibles[0], int_digit2)){
            deleteNode(Possibles[0],int_digit2);
        }
        if(SearchList(Possibles[2], int_digit2)){
            deleteNode(Possibles[2],int_digit2);
        }
        for(int i=0; i<=9; i++){
            if(i != int_digit2){
                if(!SearchList(Impossibles[1],i)){
                    sorted_add_node(Impossibles[1],i);
                }
                if(SearchList(Possibles[1],i)){
                    deleteNode(Possibles[1],i);
                }
            }
        }
    } // end of second digit of guess

    if(secret_str[2] == 'R'){   // for third digit of guess
        if(!SearchList(Impossibles[0],int_digit3)){
            sorted_add_node(Impossibles[0],int_digit3);
        }
        if(!SearchList(Impossibles[1],int_digit3)){
            sorted_add_node(Impossibles[1],int_digit3);
        }
        if(!SearchList(Impossibles[2],int_digit3)){
            sorted_add_node(Impossibles[2],int_digit3);
        }
    }

    else if(secret_str[2] == 'Y'){
        if(SearchList(Possibles[2], int_digit3)){  // if there exist
            deleteNode(Possibles[2],int_digit3);
        }
        // inserted to the impossible list of slot t
        if(!SearchList(Impossibles[2],int_digit3)){
            sorted_add_node(Impossibles[2], int_digit3);
        }
        // inserted to the possible linked lists of the other two slots if it wasn't in the corresponding slot's impossible linked list.
        if(!SearchList(Impossibles[0],int_digit3)){
            if(!SearchList(Possibles[0],int_digit3)){
                sorted_add_node(Possibles[0], int_digit3);
            }

        }
        if(!SearchList(Impossibles[1],int_digit3)){
            if(!SearchList(Possibles[1],int_digit3)){ // check all the time before add
                sorted_add_node(Possibles[1], int_digit3);
            }

        }
        if(!SearchList(Impossibles[2],int_digit3)){
            if(!SearchList(Possibles[0],int_digit3)){
                sorted_add_node(Possibles[0], int_digit3);
            }
            if(!SearchList(Possibles[1],int_digit3)){ // check all the time before add
                sorted_add_node(Possibles[1], int_digit3);
            }

        }

    }

    else if(secret_str[2] == 'G'){
        if(!SearchList(Possibles[2],int_digit3)){
            sorted_add_node(Possibles[2],int_digit3);
        }
        if(!SearchList(Impossibles[0],int_digit3)){
            sorted_add_node(Impossibles[0], int_digit3);
        }
        if(!SearchList(Impossibles[1],int_digit3)){
            sorted_add_node(Impossibles[1], int_digit3);
        }
        if(SearchList(Possibles[0], int_digit3)){
            deleteNode(Possibles[0],int_digit3);
        }
        if(SearchList(Possibles[1], int_digit3)){
            deleteNode(Possibles[1],int_digit3);
        }
        for(int i=0; i<=9; i++){
            if(i != int_digit3){
                if(!SearchList(Impossibles[2],i)){
                    sorted_add_node(Impossibles[2],i);
                }
                if(SearchList(Possibles[2],i)){
                    deleteNode(Possibles[2],i);
                }
            }
        }

    }

}
int sumNodes(node* head) {
    node* temp = head;
    int sum = 0;
    while(temp != nullptr) {
        sum += temp->digit;
        temp = temp->next;

    }
    return sum;
}


int countNodes(node* head) {
    node* temp = head;
    int count = 0;
    while(temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

void printAllDigits(node* head){   // print all elements
    while (head != nullptr)
    {
        cout << head->digit << " ";
        head = head->next;
    }
}

void printingFormat(){  // printing possibles impossibles

    cout << "Linked lists: " << endl;
    cout << "Slot: 1" << endl;
    cout << "Impossibles: ";
    printAllDigits(Impossibles[0]);
    cout << endl;
    cout << "Possibles: ";
    printAllDigits(Possibles[0]);
    cout << endl<< endl;

    cout << "Slot: 2" << endl;
    cout << "Impossibles: ";
    printAllDigits(Impossibles[1]);
    cout << endl;
    cout << "Possibles: ";
    printAllDigits(Possibles[1]);

    cout << endl<< endl;
    cout << "Slot: 3" << endl;
    cout << "Impossibles: ";
    printAllDigits(Impossibles[2]);
    cout << endl;
    cout << "Possibles: ";
    printAllDigits(Possibles[2]);
    cout << endl;

}

bool check_guess_syntax(string guess){  // check the syntax of guess str
    if( (guess[0]< 48 || guess[0] >57) || (guess[1]< 48 || guess[1] >57) || (guess[2]< 48 || guess[2] >57)){
        return false;
    }
    if(guess.length() != 3){
        return false;
    }
    if( (guess[0] == guess[1]) || (guess[0] == guess[2]) || (guess[1] == guess[2]) )
        return false;

    else
        return true;
}



int main()
{
    string guess , secret_num_str;
    int ID;

    cout << "Please enter a game ID." << endl;
    cin >> ID;
    cout << "Enter your guess." << endl;
    cin >> guess;
    secret_num_str = get_the_feedback(guess, ID);   // RRR, RRG, RRY, RGR, RYR, RYY, RGG...
    while(!check_guess_syntax(guess)){
        cout << "Invalid guess. Enter your guess." << endl;
        cin >> guess;
        if(!check_guess_syntax(guess)){
            cout << "Invalid guess. Enter your guess." << endl;
            cin>> guess;
        }
    }
    while(check_guess_syntax(guess)){

        add_to_linked_lists(secret_num_str,ID, guess);
        printingFormat();
        cout << endl;
        if(countNodes(Impossibles[0])==9 && countNodes(Impossibles[1])==9 && countNodes(Impossibles[2])==9){
            string secretNum;
            for(int i=0; i<3; i++){
                int sum = sumNodes(Impossibles[i]);
                int number = 45 - sum;
                secretNum += to_string(number);
            }

            cout << "The secret number is: " << secretNum << endl;
            cout << "Congrats! Now, deleting the lists...";
            break;
        }
        else{
            cout << "Enter your guess." << endl;
            cin >> guess;
            while(!check_guess_syntax(guess)) {
                cout << "Invalid guess. Enter your guess." << endl;
                cin >> guess;
            }
        }

    }
    //deallocate
    for(int i=0; i<3; i++){
        delete Impossibles[i];
        delete Possibles[i];
    }



    return 0;
}