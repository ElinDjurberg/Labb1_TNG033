#include "set.hpp"

// Default constructor
Set::Set() : head(new Node(0, nullptr))
{
    // Add code
    // implement before HA session week 46

	//Hur vet man hur man ska göra? Det är väll dålig program practise att göra en egen default.
	//Men vi behöver en default nu för vi har flera constructorer med samma namn.
	
	//Aida sade detta Node* ptr = new Node(0, nullptr);


	//head = new Node(0, nullptr);  //Denna


	//head = nullptr;
	// vi har en pointer som pekar på en node som innehåller värdet 0 och har en nullpointer som pekar på ingenting
	//I set.hpp class Node finns en constructor som behöver en int samt en pointer för initalizering

	
}

// Constructor for creating a set from an int
Set::Set(int v) 
{

	//Känns som detta är fel? Memoary leak? Använder vi set() någongång?
	//Node* newNode = new Node(v, nullptr);
	Node* NewNode = new Node(v, nullptr);
	//Node* dummy = new Node(0, nullptr);
	head->next = NewNode;

    // Add code
    // implement before HA session week 46
	//Set(&v->value);
	//&Set();
	//ptr = ptr2;
	//Node* ptr2{ Set (ptr) };

	//Node* ptr2->value = v;
	//ptr->value = v;
	//Node this.ptr->value = v;
	//ptr->next;

}

// Constructor creating a set
// a non-sorted array of n intgers
Set::Set(const int a[], int n) 
{
    // Add code
    // implement before HA session week 46
	head = new Node(a[0], nullptr);//ska detta vara en nullptr
	Node* dummy = head;//pekar där head pekar på
	for (int i = 1; i < n ; i++) {
		int value = a[i];

		Node* newNode = new Node(value, head->next);//vad är head next? Var pekar den?
		
		head->next = newNode;
		dummy = head->next;

		//if (i == n) {
			//Nu kommer den ha samma namn??
			//Den sista ska fortfarande ha nullpointer!
			//Node* newNode1 = new Node(value, nullptr);
		
		//}
		
		
		
		}

	}

	










	//Deep copy för vi vill ha en ny array med samma data men i olika minnen
	//Om vi använder new så glöm ej att radera
	//Hon har kopierat hela Copy by value
	//S.21 föreläsning 5 
	//vad gör vi för fel?
	//Dynamic array
	//const int SIZE = n;
	//int b[SIZE] = {0};
	//for (int i = 0; i < n; i++) {
		//b[i] = a[i];

		/*
		std::vector<int> list(3);
		int howMany = n;

		for(int i = 0; i < howMany; i++){
			//int value;
			for (int i = 0; i < n; i++) {
				b[i] = a[i];
			b[i] = a[i];
			list.push_back(value);
		}
	}*/

}

// copy constructor
Set::Set(const Set& source) 
{
    // Add code
    // implement before HA session week 46
}

// Destructor: deallocate all nodes
Set::~Set() 
{
    // Add code
    // implement before HA session week 46
}

// Test if set is empty
bool Set::empty() const 
{
    // Add code
    // implement before HA session week 46

    return true;  // to be deleted
}

// Return number of elements in the set
int Set::cardinality() const 
{
    // Add code
    // implement before HA session week 46

    return 0; // to be deleted
}

// Test if x is an element of the set
bool Set::member(int x) const 
{
    // Add code
    // implement before HA session week 46

    return false; //to be deleted
}

// Assignment operator
Set& Set::operator=(Set s)
{
	// Add code
	return *this;  // to be deleted
}

bool Set::operator<=(const Set& b) const 
{
    // Add code
    return false;  // to be deleted
}

bool Set::operator==(const Set& b) const 
{
    // Add code
    return false;  // to be deleted
}

bool Set::operator!=(const Set& b) const 
{
    // Add code
    return false;  // to be deleted
}

bool Set::operator<(const Set& b) const 
{
    // Add code
    return false;  // to be deleted
}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const 
{
    // Add code
    // implement before HA session week 45

    return *this;  // to be deleted
}

// Set intersection
Set Set::operator*(const Set& b) const 
{
    // Add code
    return *this;  // to be deleted
}

// Set difference
Set Set::operator-(const Set& b) const 
{
    // Add code
    return *this;  // to be deleted
}

// Set union with set {x}
Set Set::operator+(int x) const 
{
    // Add code
    return *this;  // to be deleted
}

// Set difference with set {x}
Set Set::operator-(int x) const 
{
    // Add code
    return *this;  // to be deleted
}



std::ostream& operator<<(std::ostream& os, const Set& theSet) 
{
	if (theSet.empty())
	{
		os << "Set is empty!";
	}
    else
	{
        Set::Node* temp = theSet.head->next;
        os << "{ ";

        while (temp)
		{
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }

    return os;
}
