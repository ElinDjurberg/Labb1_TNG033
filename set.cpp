#include "set.hpp"
/*
void Set::insert(Node* p, int value) const {
	//Kolla alla fallen, sist, mellan efter, dummynode före
	auto newNode = new Node(value, nullptr);

	newNode->value = value;
	newNode->next = p->next;

	p->next = newNode;
}

void Set::remove(Node* p) {
	//stämmer detta?? Funkar detta
	if (empty()) {
		return;
	}
	Node* remove = p.head;
}
*/

// Default constructor
Set::Set()
//: head(new Node(0, nullptr))
{
	// Add code
	// implement before HA session week 46

	//Hur vet man hur man ska göra? Det är väll dålig program practise att göra en egen default.
	//Men vi behöver en default nu för vi har flera constructorer med samma namn.

	//Node* ptr = new Node(0, nullptr);
	head = new Node(0, nullptr);


	//head = new Node(0, nullptr);  //Denna


	//head = nullptr;
	// vi har en pointer som pekar på en node som innehåller värdet 0 och har en nullpointer som pekar på ingenting
	//I set.hpp class Node finns en constructor som behöver en int samt en pointer för initalizering


}

// Constructor for creating a set from an int
Set::Set(int v): Set()
{

	//Node* NewNode = new Node(v, nullptr);
	//head = NewNode;

	head->next = new Node(v, nullptr);


	//Känns som detta är fel? Memoary leak? Använder vi set() någongång?
	//Node* newNode = new Node(v, nullptr);

	//Node* dummy = new Node(0, nullptr);

	//head = newNode(0, nullptr);
	//head = new Node(v, nullptr);

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
	/* // Add code
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

		 }*/
	head = new Node(a[0], nullptr);
	Node* dummy = head;

	for (int i = 1; i < n; i++) {
		int value = a[i];

		Node* newNode = new Node(value, nullptr);//Repetera ej den koden
		dummy->next = newNode;
		dummy = dummy->next;
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



// copy constructor
Set::Set(const Set& source) {
	// Add code
	// implement before HA session week 46

	//måste man göra något om det är en tom lista?

	//Pekar head aotomatiskt på den första eller måste man skriva den
	Node* temp = source.head;//skriv inte Node* temp = new Node(0, nullptr);   temp = head.source; då får vi en memory leak
	Node* head2 = new Node(temp->value, nullptr);
	temp = temp->next;
	Node* dummy = head2;

	//Behövs kolla temp next !=  nullptr?

	while (temp != nullptr) {

		Node* newNode = new Node(temp->value, nullptr);
		dummy->next = newNode;//Kopplar vi ihop dem här?
		temp = temp->next;
		dummy = dummy->next;

	}
}

// Destructor: deallocate all nodes
Set::~Set()
{
	// Add code
	// implement before HA session week 46
	//gå node för node och delete p;
	// måste man göra något om det är en tom lista??
	//Obs glöm ej radera dummy nodes också?

	Node* current = head;//Når jag headen från listan jag får in? Kommer jag åt headen?//current pekar där head pekar?
	//behöver jag kolla båda?
	//delete head;
	while (current != nullptr) {

		//går längst bak i listan
		//Vad betyder ; i detta fall?
		//finns dummy next så hoppa fram ett steg tills man kommit till slutet. 
		//Kan denna råka peka på en nullpointer?
		/*
		for (; dummy->next; dummy = dummy->next) {
			delete dummy;
		}
		*/
		Node* soon = current->next;//Kan jag skapa en ny här varje gång?
		delete current;//tar vi bort objectet eller pekarn?

		current = soon;

	}
	//Måste radera något här men vad
	//Kan vi sätta head till nullptr;
	//delete head;//Raderar jag nu dummynoden jag skapade för det vill jag?
	//måste deleta den sista noden på något sätt har jag gjort det?
}

// Test if set is empty
bool Set::empty() const
{
	// Add code
	// implement before HA session week 46
	//vat den var head är?
	//if (head == nullptr) {
	//return true;  // to be deleted
	//}
	bool isEmpty = false;

	if (head->next == nullptr) {
		isEmpty = true;

	}

	//return (head->next == nullptr);//Har vi implementerat dummynode först?
	return isEmpty;

}

// Return number of elements in the set
int Set::cardinality() const
{
	// Add code
	// implement before HA session week 46
	//whileloop och räkna antal
	int counter = 0;
	Node* dummy = head;
	//Dummy->next är också fel
	while (dummy->next != nullptr) {
		counter++;
		dummy = dummy->next;
	}

	return counter; // to be deleted
}

// Test if x is an element of the set
bool Set::member(int x) const
{
	// Add code
	// implement before HA session week 46
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
	bool exist = false;

	while (search != nullptr) {

		if (search->value != x) {
			search = search->next;
		}

		else {
			exist = true;
			break;
			
		}
	}



	return exist;
	//return false; //to be deleted


}

// Assignment operator
Set& Set::operator=(Set s)
{
	// Add code
	//copy and swap, radera den du gör innan
	
	Node* ptrS = s.head;
	Node* temp = ptrS;
	Node* R = new Node(0, nullptr);

	ptrS = R;
	R = temp;






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

		//vad händer om den ena är längre än den andra eller kortare?
		//Vad ska returneras
		//radera den vi har?
	
	return *this;
	//return *this;  // to be deleted raderas vår automatisk? Kallar den på delocate automatiskt?. Står ju att vi ska radera
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
