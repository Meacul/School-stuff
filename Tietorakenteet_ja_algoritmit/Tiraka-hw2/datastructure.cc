#include "datastructure.hh"
#include "hashtable.hh"
// Empty implementations for public interface, modify and add your own code here
using namespace std;

Datastructure::Datastructure()
{

}

Datastructure::~Datastructure()
{

}

void Datastructure::add(const string &ID, const string &location,
                        unsigned int amount, const string &name)
{

    string tempID = ID;
    string tempLocation = location;
    int tempAmount = amount;
    string tempName = name;
    Product * temp = new Product;
    temp->ID = tempID;
    temp->location = tempLocation;
    temp->amount = tempAmount;
    temp->name = tempName;
    temp->next = NULL;
    table.insertProduct(temp);
}

void Datastructure::substract(const string &ID, unsigned int amount)
{
    int tempAmount = amount;
    const string &tempID = ID;
    if(table.removeProduct(tempID, tempAmount))
    {
        return;
    }
    else
    {
        cout << NOT_AVAILABLE << endl;
    }
}

void Datastructure::find(const string &ID)
{
    string tempID = ID;
    Product * temp;
    temp = table.getProductbyID(tempID);
    if(temp != NULL){
        cout << temp->name << " " << temp->amount << " " << temp->location << endl;
        return;
    }
    else
    {
        cout << "Product not in warehouse." << endl;
        return;
    }
}

size_t Datastructure::count()
{
    size_t temp = table.getNumberofProducts();
    return temp;
}

void Datastructure::empty()
{
    table.~HashTable();
}
