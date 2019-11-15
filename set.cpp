#include "set.hpp"



void Set::insert(Node* p, int value) const {
	//Kolla alla fallen, sist, mellan efter, dummynode före
	auto newNode = new Node(value, nullptr);
	if (p->next == nullptr) {
		p->next = newNode;
		//newNode = nullptr;
	}

	else {

	newNode->next = p->next;
	p->next = newNode;
	}
	
}

void Set::remove(Node* p) {
	/*//stämmer detta?? Funkar detta? Vad händer om det är en tom list?
	if (empty()) {
		return;
	}
	*/
	//Vad är skillnaden mellan dessa? Hur vet man dummy pekar på pekaren p. Eller om den pekar på samma sak som p, pekar på.
	//Node* dummy = p;

	Node* dummy = new Node(0, p->next);
	delete p;
	
	

	/* // 1. Find the node before the node to be removed
    while ((p1->next != nullptr) && (p1->next->value != n)) {
        p1 = p1->next;
    }

    if (p1->next == nullptr)  // n not found in list L
        return;

    // 2. Remove
    Node* p2 = p1->next;  // p2 points to the node to be removed

    p1->next = p2->next;

    // 3. Deallocate the memory of the node pointed by p2
    delete p2;*/
	/*Node* search = head->next;

	while (search != nullptr) {

		if (search->value == x) {
			return true;
		}
		search = search->next;
	}

	return false; //to be deleted*/

	

}


// Default constructor
Set::Set()
{
	//I set.hpp class Node finns en constructor som behöver en int samt en pointer för initalizering

	head = new Node(0, nullptr); // Fö 7, aida skrev det ska vara såhär!!
	//Detta är en nod med en tom efterföljare

	// head = nullptr;
	

}

// Constructor for creating a set from an int
Set::Set(int v) : Set()
{
	head->next = new Node(v, nullptr);
	
	// samma som
	// Node* dummy = new Node(0, nullptr);
	// head = dummy;
}

// Constructor creating a set
// a non-sorted array of n intgers
Set::Set(const int a[], int n):Set()
{
	//Vi måste peka på array för den är constant så vi kan ej ändra den
	int *newArray = new int[n];

	for (int i = 0; i < n; i++) {
		newArray[i] = a[i];
	}

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



	/*
	
	// head pekar bara första
	head = new Node(a[0], nullptr);//ska detta vara en nullptr

	// dummy ska alltid peka på den sista i linked_list
	// om man har tre nodes, head pekar på första och dummy på tredje
	Node* dummy = head; // START: pekar där head pekar på

	for (int i = 1; i < n; i++) {
		int value = a[i];

		dummy->next = new Node(value, nullptr);
		// dummy->next är nya pointern till sista noden (som också är ny)
		// nya noden ska inte peka på något

		dummy = dummy->next; // ny dummy som pekar på sista noden

		// måste deleta nånstans vart?

	}*/

	// head = new Node(a[0], nullptr);
	//detta ska bort etfersom jag skrev Set() i början av funktoinen

	Node* dummy = head;

	for (int i = 0; i < n; i++) {
		int value = newArray[i];

		Node* newNode = new Node(value, nullptr);//Repetera ej den koden
		dummy->next = newNode; //sätter ihop noderna
		dummy = dummy->next;
	}
	//Glöm inte att vi måste deleta på fler ställen!!
	delete[] newArray;
	newArray = nullptr;

}



// copy constructor
Set::Set(const Set& source) : Set()
{
	/*
	// referens

	// är i klassen set, kommer åt privata saker
	// source är en linked-list, objekt
	Node* ptr = source.head;

	
	// ptr->next != nullpt
	// kollar om det finns en ny pekare, finns det, så finns en ny nod
	

	while ((ptr != nullptr) && (ptr->next != nullptr)) {

		// kopior som ska in i egen lista
		// sparar pekare med nodfakta från pekare ptr som pekar på en specifik nod
		Node* myNode = new Node( ptr->value, nullptr);

		ptr = ptr->next;
		// typ j++ i for loop

		// bara om head är nullptr, för då finns bara en nod
		if (head == nullptr){
			head = myNode; // pekar på samma, head ska peka på första
		}
		else {
			
			// ny pekare till första noden, knuffar bak de andra noderna/pekarna
			myNode->next = head;

			head = myNode; // head pekar på nyaste noden som skapats
		}

	}
	*/

	// skriv inte Node* temp = new node(0, nullptr); // i början för det blir memory leak, Aida

	Node* temp = source.head; // head till S
	temp = temp->next; // pekar på första riktiga noden
	Node* tail = head; // denna ska följa med längs hela R, head till R

	while ( temp != nullptr) {

		Node* newNode = new Node(temp->value, nullptr);
		tail->next = newNode; // knyter ihop R
		tail = tail->next; // samma som // tail=newNode;
		temp = temp->next; // pekarp å nästa nod i S, som ska kopieras
	}
}




// Destructor: deallocate all nodes
Set::~Set()
{
	//gå node för node och delete p;
	// måste man göra något om det är en tom lista??
	//Obs glöm ej radera dummy nodes också?

	Node* current = head;
	// är redan inne i set, så vi når head
	
	
	//delete head;
	while (current != nullptr) {

		//går längst bak i listan
		//finns dummy next så hoppa fram ett steg tills man kommit till slutet. 

		Node* soon = current->next;
		
		// delete *current; // för att ta bort noden?
		// sådan man måste deleta själv är sådant man gjort New på, t.ex noder

		delete current;//tar vi bort objectet
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
	// head kan aldrig vara den vi testar, är en dummynode
	// vi är redan inne i set

	/*
	bool isEmpty = false;

	if (head->next == nullptr) {
		isEmpty = true; // den är tom, inga noder finns
	}
	return isEmpty; // to be deleted
	*/

	return head->next == nullptr;
	// returnerar true eller falsetrue om
	// true om head -> next==nullptr;
	//false om head -> next!=nullptr;
}

// Return number of elements in the set
// number of nodes in the set
int Set::cardinality() const
{
	//whileloop och räkna antal
	int counter = 0;
	Node* dummy = head->next;

	/* man kan även räkna hela skiten inklusive head, sedan ta counter-1 innan return */

	//Dummy->next är också fel

	while (dummy != nullptr) {
		counter++;
		dummy = dummy->next;
	}

	return counter; // to be deleted
}

// Test if x is an element of the set
bool Set::member(int x) const
{
	//search
	/*
	bool search(List L, int n) {
		Node* p = L.head->next;  // skip the dummy node. Har vi en dummy node före alla i detta fall?
		while ((p != nullptr) && (p->value != n)) {
			p = p->next;
		}
		return (p != nullptr);
	}*/

	Node* search = head->next;

	while (search != nullptr) {

		if (search->value == x) {
			return true;
		}
		search = search->next;
	}

		return false; //to be deleted
}

// Assignment operator
Set& Set::operator=(Set s)
{

	Set copy(s);
	//byter huvuden?
	//när använda punkt och när använda pil?
	//fråga gör bara head? varför ej s.head?
	std::swap(head, copy.head);

	// vi är inne i set och får in en annan set också
	
	// R head och S head
	//head = s.head;

	// kopia på s, alltå en ny linked list
	// sedan snor den till vår head i (this)

	//head = (new Set(s))->head;

	//return *this;

	/*
	Node* temp = head;
	Node* R = new Node(0, nullptr);

	head = R;
	R = temp;

	*/

	/*
		// två olika linked-list, två olika head
		// hämtar head från linked-list s
	//deletas den andra
		Node* ptrS = s.head;
		Node* ptrThis = head;
		//är det next för att den första är en dummy?
		while (ptrS->next != nullptr) {
			std::swap(ptrThis->value, ptrS->value);
			ptrThis = ptrThis->next;
			ptrS = ptrS->next;
			if (ptrThis == nullptr) {
				//insert
				auto newNode = new Node(ptrS->value, nullptr);
				newNode = ptrThis->next;
				//newNode->value = value;
				newNode->next = p->next;
				p->next = newNode;
			}
		}

		*/

	return *this; // hela objektet returneras
	// to be deleted raderas vår automatisk? Kallar den på delocate automatiskt?. Står ju att vi ska radera
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