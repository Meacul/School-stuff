#include "datastructure.hh"
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <vector>


//Initializes the data structure.
Datastructure::Datastructure()
{
    head = NULL;
    best = NULL;
    worst = NULL;
    sorted = false;
    sortedAlph = false;
    size = 0;
}

Datastructure::~Datastructure()
{

}
// Placeholders for functions

// Adds new player
void Datastructure::add(std::string name, unsigned int brokenNysse,
            unsigned int sufferingPeople)
{

    //Create the new player data point.
    sorted = false;
    sortedAlph = false;
    Data* newNode = new Data();
    newNode->playerName = name;
    newNode->brokenNysse = brokenNysse;
    newNode->sufferingPeople = sufferingPeople;
    newNode->place = 0;
    newNode->next = NULL;
    //Adds the new pointer to the end.
    if(head != NULL){
        last->next = newNode;
        last = newNode;
        size++;
        if(best->brokenNysse < newNode->brokenNysse){
            best = newNode;
        }
        else if(best->brokenNysse == newNode->brokenNysse){
            if (best->sufferingPeople < newNode->sufferingPeople){
                best = newNode;
            }
        }
        else if(worst->brokenNysse > newNode->brokenNysse){
            worst = newNode;
        }
        else if(worst->brokenNysse == newNode->brokenNysse){
            if (worst->sufferingPeople < newNode->sufferingPeople){
                worst = newNode;
            }
        }
        else{

        }
    }
    else{
        head = newNode;
        last = newNode;
        best = newNode;
        worst = newNode;
        size++;
    }
}

//Prints the list alphabetically.
void Datastructure::printAlphabetically()
{
    Data* temp = head;
    if(sortedAlph == false){
        alphsort.clear();
        head = SortAlph(head);
        temp = head;
        sorted = false;
        sortedAlph = true;
        while(temp != NULL){
            std::cout << temp->playerName << ": " << temp->brokenNysse << " buses, "
                    << temp->sufferingPeople << " passengers" << std::endl;
            alphsort.push_back(temp);
            temp = temp->next;
        }
    }
    else{
        size_t i = 0;
        while(i < alphsort.size()){
            std::cout << alphsort.at(i)->playerName << ": " << alphsort.at(i)->brokenNysse << " buses, "
                    << alphsort.at(i)->sufferingPeople << " passengers" << std::endl;
            i++;
        }
    }
}


// Finds player with key stored in term
void Datastructure::findPerson(std::string term)
{
    Data* temp = head;
    //Checks if the list is empty
    if(temp == NULL){
        std::cout << "Player " << term << " was not found." << std::endl;
        return;
    }
    if (sorted != true){
        //Sorts the list so we get correct temp->place value
        head = Sort(head);
        temp = head;
    }
    else{}
    int i = 0;

    //Tries to find the correct player.
    while(temp->playerName != term && temp != NULL){
        i++;
        temp->place = i;
        temp = temp->next;
    }
    if (temp != NULL){
        i++;
        temp->place = i;
        std::cout << temp->place << ". " << temp->playerName << ": " << temp->brokenNysse
             << " buses, " << temp->sufferingPeople << " passengers" << std::endl;
    }
    else{
        std::cout << "Player " << term << " was not found" << std::endl;
    }
}


// Print leaderboard. Sorts only if necessary
void Datastructure::printLeaderBoard()
{
    Data *temp = head;
    if (temp == NULL){

    }
    else{
        if(sorted != true){
            head = Sort(head);
            temp = head;
            int i = 0;
            size_t k = 0;
            while(temp != NULL){
                i++;
                numsort.push_back(temp);
                k++;
                temp->place = i;
                std::cout << temp->place << ". " << temp->playerName << ": " << temp->brokenNysse << " buses, "
                          << temp->sufferingPeople << " passengers" << std::endl;
                temp = temp->next;
            }
            sorted = true;
        }
        else{
            size_t j = 0;
            while(j < numsort.size()){
            std::cout << temp->place << ". " << temp->playerName << ": " << temp->brokenNysse << " buses, "
                << temp->sufferingPeople << " passengers" << std::endl;
            j++;
            }
        }

        sortedAlph = false;
    }
}

// Prints worst player stats
void Datastructure::worstPlayer()
{
    Data *temp = worst;
    if(head == NULL){
        std::cout << "Error: List is empty" << std::endl;
    }
    else if(worst != NULL){
        std::cout << temp->place << ". " << temp->playerName << ": " << temp->brokenNysse << " buses, "
                  << temp->sufferingPeople << " passengers" << std::endl;
    }
    else{
        if(sorted != true){
            //Sorts the list, so we get the correct player and temp->place value.
            head = Sort(head);
            temp = head;
        }
        else{}
        int i = 0;
        while(temp->next != NULL){
            i++;
            temp->place = i;
            temp = temp->next;
        }
        i++;
        temp->place = i;
        std::cout << temp->place << ". " << temp->playerName << ": " << temp->brokenNysse << " buses, "
                  << temp->sufferingPeople << " passengers" << std::endl;
        sorted = true;
    }
}

// Prints best player stats
void Datastructure::bestPlayer()
{
    Data *temp = head;
    if(head == NULL){
        std::cout << "Error: List is empty" << std::endl;
    }
    else{
        if(sorted != true){
            head = Sort(head);
            temp = head;
        }
        else{}
        temp->place = 1;
        std::cout << temp->place << ". " << temp->playerName << ": " << temp->brokenNysse << " buses, "
                  << temp->sufferingPeople << " passengers" << std::endl;
    }
}

// Empties the datastructure
void Datastructure::empty()
{
    head = NULL;
    best = NULL;
    worst = NULL;
    size = 0;
}

//Returns the new head of sorted list.
//If called in other parts of the process, checks if data1 is empty or last item on the list.
//If needed this operation will initialize new splits and merges.
Datastructure::Data* Datastructure::Sort(Data* data1){
    Data* data2;
    //If data1 is null, the sort is unnecessary.
    if(data1 == NULL){
        return NULL;
    }
    //If data1->next is empty there is only one value to sort.
    else if(data1->next == NULL){
        return data1;
    }
    //If there are more than one data point, initialize a new split and merge for that split.
    else{
        data2 = Split(data1);
        return Merge(Sort(data1), Sort(data2));
    }
}
//Merges two datapoints to create an ordered list.
Datastructure::Data* Datastructure::Merge(Data* data1, Data* data2){

    //Checks if the merge is not needed.
    if(data1 == NULL){
        return data2;
    }
    else if(data2 == NULL){
        return data1;
    }
    //Checks way the merge must go.
    else if (data1->brokenNysse >= data2->brokenNysse){
            if(data1->brokenNysse > data2->brokenNysse){
            data1->next = Merge(data1->next, data2);
            return data1;
        }
        else{
            if (data1->sufferingPeople >= data2->sufferingPeople){
                data1->next = Merge(data1->next, data2);
                return data1;
            }
            else{
                data2->next = Merge(data1, data2->next);
                return data2;
            }
        }
    }
    else{
        data2->next = Merge(data1, data2->next);
        return data2;
    }
}
//Splits the list in preparation of a merge and initialises new splits as needed.
Datastructure::Data* Datastructure::Split(Data* data1){
    Data* data2;
    //Check if either node is empty or its next value is null.
    if(data1 == NULL){
        return NULL;
    }

    //If the split is useless, returns null.
    else if (data1->next == NULL){
        return NULL;
    }

    //Initialises a new split.
    else{
        data2 = data1->next;
        data1->next = data2->next;
        if(data2->next != NULL){
        data2->next = Split(data2->next);
        }
        return data2;
    }
}
//These operations do the same things as their numeric counterparts, except they sort alphabetically
//I made this without a parameter for differing sorting ways, because it was easier to ctrl+c, ctrl+v.
//Otherwise I would have had to keep track of the sorting method through all these pieces of code.
Datastructure::Data* Datastructure::SortAlph(Data* data1){
    Data* data2;

    if(data1 == NULL){
        return NULL;
    }
    else if(data1->next == NULL){
        return data1;
    }
    else{
        data2 = SplitAlph(data1);
        return MergeAlph(SortAlph(data1), SortAlph(data2));
    }
}

Datastructure::Data* Datastructure::MergeAlph(Data* data1, Data* data2){
    if(data1 == NULL){
        return data2;
    }
    else if(data2 == NULL){
        return data1;
    }
    else if (data1->playerName.compare(data2->playerName) <= 0){
            data1->next = MergeAlph(data1->next, data2);
            return data1;
    }
    else{
        data2->next = MergeAlph(data1, data2->next);
        return data2;
    }
}

Datastructure::Data* Datastructure::SplitAlph(Data* data1){
    Data* data2;
    if(data1 == NULL){
        return NULL;
    }
    else if (data1->next == NULL){
        return NULL;
    }
    else{
        data2 = data1->next;
        data1->next = data2->next;
        data2->next = SplitAlph(data2->next);
        return data2;
    }
}
