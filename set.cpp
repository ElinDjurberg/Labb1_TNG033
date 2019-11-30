#include "set.hpp"

// skapar ny nod i ett set
void Set::insert(Node* p, int value) const {

	auto newNode = new Node(value, nullptr);

	// uppdaterar pekarna
	//insertar efter p
	newNode->next = p->next;
	p->next = newNode;
}

void Set::remove(Node* p) {
	//deletar noden som p pekar på.
	delete p;
	p = nullptr;

}


// Default constructor
Set::Set()
{
	//I set.hpp class Node finns en constructor som behöver en int samt en pointer för initalizering

	head = new Node(0, nullptr); 
	//Detta är en nod med en tom efterföljare
	// kan inte deleta här för då finns inget att skicka vidare 
}

// Constructor for creating a set from an int
Set::Set(int v) : Set()
{	
	head->next = new Node(v, nullptr);
}

// Constructor creating a set
// a non-sorted array of n intgers
Set::Set(const int a[], int n) :Set()
{
	//Vi måste peka på array för den är constant så vi kan ej ändra den
	int *newArray = new int[n];

	//Använder pekaren för att lägga in värden från a i den nya arrayn vi har skapat. Nu kan vi komma åt dem
	for (int i = 0; i < n; i++) {
		newArray[i] = a[i];
	}

	//sortering
	int temp = 0;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (newArray[i] > newArray[j]) {

				temp = newArray[j];
				newArray[j] = newArray[i];
				newArray[i] = temp;

			}
		}
	}


	Node* dummy = head;

	// tar värdena från den nya arrayen och sätter som values i ett nytt sett av noder ( singled linked list)
	for (int i = 0; i < n; i++) {
		int value = newArray[i];

		insert(dummy, value);

		// uppdatera dummy, annars hamnar noderna som bakvänt, man lägger in åt fel håll
		dummy = dummy->next;
	}
	// om vi deletar newArray med hake [] tar vi bort hela arrayen som pekren newArray pekar på
	delete[] newArray;
	newArray = nullptr;

	/*
	Köra delete manuellt för remove funktionen tar bara bort noder
	*/
}



//Kopiera från S och lägga in i R
// copy constructor
Set::Set(const Set& source) : Set()
{
	Node* temp = source.head; // head till S
	temp = temp->next; // pekar på första riktiga noden, hoppar över dummyNode

	Node* tail = head; // denna ska följa med längs hela R, head till R

	while (temp != nullptr) {

		/*Node* newNode = new Node(temp->value, nullptr);*/
		/*tail->next = newNode; // knyter ihop R*/

		insert(tail, temp->value);

		tail = tail->next; // samma som tail=newNode;
		temp = temp->next; // pekar på nästa nod i S, som ska kopieras
	}
}

// Destructor: deallocate all nodes
Set::~Set()
{
	//gå node för node och delete p;
	// är redan inne i set, så vi når head
	Node* current = head;
	
	//delete head;
	while (current != nullptr) {

		//börjar framifrån och går igenom hela listan
		//finns dummy next så hoppa fram ett steg tills man kommit till slutet. 

		Node* soon = current->next;

		// delete current;
		remove(current);

		// sätter om current från nullptr i remove funktionen till soon
		current = soon;
	}
}


/*
Sätter man const efter en funktion skaobjektet INTE ändras
In: A
Ut: A

dvs INGA borttagna/tillagda noder, ändrande av pointer eller value i noderna

t.ex en person in (namn, ålder)
kontrollera nmanet och ålder, INTE ändra något, endast kontrollera
*/


// Test if set is empty
bool Set::empty() const
{
	return head->next == nullptr;
	// returnerar true eller false om
	// true om head -> next==nullptr;
	//false om head -> next!=nullptr;
}

// Return number of elements in the set
// number of nodes in the set
int Set::cardinality() const
{
	//whileloop och räkna antal
	int counter = 0;
	//ta head->next för att inte räkna med dummyNode
	Node* dummy = head->next;


	while (dummy != nullptr) {
		counter++;
		dummy = dummy->next;
	}

	return counter;
}

// Test if x is an element of the set
bool Set::member(int x) const
{
	Node* search = head->next;

	while (search != nullptr) {
		//om man hittar värdet man söker efter return true och avsluta
		if (search->value == x) {
			return true;
		}
		search = search->next;
	}

	return false; 
}

// Assignment operator
Set& Set::operator=(Set s)
{  //s.head no copy
	//copy and swap idiom
	//Set copy(s);
	std::swap(head, s.head);
	// hela objektet returneras
	//delocate automatiskt
	return *this; 
	
}

//Kollar om det är ett subset/delmmängd
bool Set::operator<=(const Set& b) const
{
	bool isSubset = false;
	Node* dummy = head->next;//hoppar över till första tal
	Node* dummyB = b.head->next;
	int counter = 0;

	//Kollar om vi är i en tom för då kommer det alltid vara sant
	if (this->empty()) {
		isSubset = true;
		return isSubset;
	}

	while (dummy != nullptr) {

		while (dummyB != nullptr) {

			if (dummyB->value == dummy->value) {
				counter++;
			}
			dummyB = dummyB->next;

		}
		//resetta dummy 
		dummyB = b.head->next;
		dummy = dummy->next;

	}
	//om den har hittat lika många element som finns i listan som den är lång så är det en delmängd
	//alla talen i det lilla settet ska finnas i det större. Countern ökar varje gång det lilla settet->value är samma som stora settets value
	if (counter == this->cardinality()) {
		isSubset = true;
	}

	return isSubset;
}

bool Set::operator==(const Set& b) const
{
	
	return !(*this != b);
}

bool Set::operator!=(const Set& b) const
{
	
	bool isSubset = true;

	if ((*this <= b) && (b.cardinality() == this->cardinality())) {
		isSubset = false;
	}
	
	return isSubset;

}

bool Set::operator<(const Set& b) const
{

	bool isSubset = false;

	if ((this <= &b) && (b.cardinality() > this->cardinality())) {
		isSubset = true;
	}

	return isSubset;  
}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const
{
	// Add code
	Set newSet = Set();//Dummy node till vårt nya set

	Node* pointerB = b.head->next;
	Node* pointerR = head->next;	//Når vi setet vi är i sett R//Ja vi når R
	//vi skriver head next för att inte räkna med vår dummynode!

	Node* dummyNew = newSet.head;


	while ((pointerB != nullptr) && (pointerR != nullptr)) {

		if (pointerB->value < pointerR->value) {
			//skapa en ny lista

			insert(dummyNew, pointerB->value);
			//dummyNew->next = new Node(pointerB->value, nullptr);
			pointerB = pointerB->next;
			dummyNew = dummyNew->next;
		}

		else if (pointerR->value < pointerB->value) {
			//lägga till på lista
			insert(dummyNew, pointerR->value);
			//dummyNew->next = new Node(pointerR->value, nullptr);
			pointerR = pointerR->next;
			dummyNew = dummyNew->next;
		}

		else {
			//om de är samma 
			//lägg till i list

		/*Node* newNode = new Node(temp->value, nullptr);*/
		/*tail->next = newNode; // knyter ihop R*/
			insert(dummyNew, pointerR->value);

			//dummyNew->next = new Node(dummyR->value, nullptr);
			pointerR = pointerR->next;
			pointerB = pointerB->next;
			dummyNew = dummyNew->next;
		}


	}

	//Lägg till i listorna
	while (pointerB != nullptr) {
		//Lägg till resterande i listan


		//dummyNew->next = insert
		insert(dummyNew, pointerB->value);
		//dummyNew->next = new Node(dummyB->value, nullptr);
		pointerB = pointerB->next;
		dummyNew = dummyNew->next;

	}

	while (pointerR != nullptr) {
		//Lägg till resten i listan



		insert(dummyNew, pointerR->value);
		//dummyNew->next = new Node(pointerR->value, nullptr);
		pointerR = pointerR->next;
		dummyNew = dummyNew->next;

	}

	return newSet;  // to be deleted
}

// Set intersection
Set Set::operator*(const Set& b) const
{
	
	Set newSet = Set();//Dummy node till vår nya sätt

	Node* dummyB = b.head->next;
	Node* dummyR = head->next;	//Når vi setet vi är i sett R//Ja vi når R
	//vi skriver head next för att inte räkna med vår dummynode!

	Node* dummyNew = newSet.head;


	while (dummyB != nullptr) {

		while (dummyR != nullptr) {

			if (dummyB->value == dummyR->value) {
				//skapa en ny lista

				insert(dummyNew, dummyB->value);
				//dummyNew->next = new Node(dummyB->value, nullptr);
				//de* List = new Node()

				dummyNew = dummyNew->next;
			}

			dummyR = dummyR->next;

		}
		//Detta är för att resetta dummyR annars är den längst bort i arrayn! Detta glömde vi
		dummyR = head->next;

		dummyB = dummyB->next;
	}

	return newSet;  // to be deleted
}

// Set difference
Set Set::operator-(const Set& b) const
{
	Set newSet = Set();

	Node* dummyB = b.head->next;
	Node* dummyR = head->next;
	Node* dummyNew = newSet.head;

	while (dummyR != nullptr) {

		int counter = 0;

		while (dummyB != nullptr) {

			if (dummyR->value == dummyB->value) {

				counter++;
			}

			dummyB = dummyB->next;

		}

		dummyB = b.head->next;//vi måste resetta dummy B till nästa loop

		if (counter == 0) {
			insert(dummyNew, dummyR->value);
			//dummyNew->next = new Node(dummyR->value, nullptr);
			dummyNew = dummyNew->next;
		}

		dummyR = dummyR->next;
	}
	//ska något tas bort här??
	return newSet;  // to be deleted
}

// Set union with set {x}
Set Set::operator+(int x) const
{

	//gör ett nytt sätt med det värdet vi fick in
	Set *newInt = new Set(x);
	//använder vår operator+ som vi skapat.
	const Set combinedSet = *this + *newInt;

	delete newInt;//vi behöver deleta annars memory leaks
	return combinedSet;

}

// Set difference with set {x}
Set Set::operator-(int x) const
{
	// Add code

	//gör ett nytt sätt med det värdet vi fick in
	Set *newInt = new Set(x);
	//använder vår operator- som vi skapat.
	const Set combinedSet = *this - *newInt;
	delete newInt;
	return combinedSet;
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