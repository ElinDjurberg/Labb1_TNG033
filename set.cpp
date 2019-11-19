#include "set.hpp"



void Set::insert(Node* p, int value) const {
	//Kolla alla fallen, sist, mellan efter, dummynode före
	auto newNode = new Node(value, nullptr);
	if (p->next == nullptr) {
		p->next = newNode;
	}

	else {

		newNode->next = p->next;
		p->next = newNode;
	}
	//borde man deleta här??
}

void Set::remove(Node* p) {
	
	delete p;
	p = nullptr;

}


// Default constructor
Set::Set()
{
	//I set.hpp class Node finns en constructor som behöver en int samt en pointer för initalizering

	head = new Node(0, nullptr); // Fö 7, aida skrev det ska vara såhär!!
	//Detta är en nod med en tom efterföljare
	// kan inte deleta här för då finns inget att skicka vidare //delete head;
}

// Constructor for creating a set from an int
Set::Set(int v) : Set()
{
	head->next = new Node(v, nullptr);
	//deleta ej här heller
}

// Constructor creating a set
// a non-sorted array of n intgers
Set::Set(const int a[], int n) :Set()
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


	Node* dummy = head;

	for (int i = 0; i < n; i++) {
		int value = newArray[i];
		//insert(dummy, i);
		
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

	Node* temp = source.head; // head till S
	temp = temp->next; // pekar på första riktiga noden
	Node* tail = head; // denna ska följa med längs hela R, head till R

	while (temp != nullptr) {

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

	while (dummy != nullptr) {
		counter++;
		dummy = dummy->next;
	}

	return counter; // to be deleted
}

// Test if x is an element of the set
bool Set::member(int x) const
{
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
	std::swap(head, copy.head);

	return *this; // hela objektet returneras
	// to be deleted raderas vår automatisk? Kallar den på delocate automatiskt?. Står ju att vi ska radera
}

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
	
	if (counter == this->cardinality()) {
		isSubset = true;
	}
	
	return isSubset; 
}

bool Set::operator==(const Set& b) const
{
	
	bool isSubset = false;
	Node* dummy = head->next;//hoppar över till första tal
	Node* dummyB = b.head->next;
	int counter = 0;


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
	
	
	/*
	bool isSubset = false;
	bool hej = false;
	bool da = false;

	if (b.cardinality() == this->cardinality()) {
		hej = true;//blir sant
	}
	if ((this <= &b)) {
		da = true;//blir falsk
	}
	*/
	/*
	//(this <= &b)(&b <= this)//får kan väl ej skicka in this som argument
	if ((b.cardinality() == this->cardinality()) && (this <= &b)) {
		//This kan kanske inte skickas som det?
		isSubset = true;

	}*/
	
	
	//kollar att båda setten innehåller lika mycket samt att allt i enna settet även finns i andra
	if ((counter == this->cardinality()) && b.cardinality() == this->cardinality()) {
		isSubset = true;
	}
	
	return isSubset;  // to be deleted

}

bool Set::operator!=(const Set& b) const
{
	//if(this->operator==() != b.operator==())

	bool isSubset = false;
	bool answer = true;
	Node* dummy = head->next;//hoppar över till första tal
	Node* dummyB = b.head->next;
	int counter = 0;
	//bool da = b.empty();//b borde vara tom?//tom är det som skickas in
	//bool hej =this->empty();

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
	//kollar att båda setten innehåller lika mycket samt att allt i enna settet även finns i andra
	if ((counter == this->cardinality()) && b.cardinality() == this->cardinality()) {
		isSubset = true;
	}

	if(isSubset == true){
		answer = false;
	}
	//return answer;  // to be deleted
	return !(isSubset);

}

bool Set::operator<(const Set& b) const
{
/*
	bool isSubset = false;
	Node* dummy = head->next;//hoppar över till första tal
	Node* dummyB = b.head->next;
	int counter = 0;


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
	//int y = b.cardinality();
	//kan man kalla på cardinality sådär?
	//Vi har ju skrivit om > nu kan jag fortfarande använda den som förut?
	//den vi skickar in måste vara större

	*/
	bool isSubset = false;

	if ((this <= &b) && (b.cardinality() > this->cardinality())) {
		isSubset = true;

	}


	/*
	if ((counter == this->cardinality()) && b.cardinality() > this->cardinality()) {
		isSubset = true;
	}
	*/
	return isSubset;  // to be deleted
	
}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const
{
	// Add code
	//Set copy(s);
	//std::swap(head, copy.head);
	Set newSet = Set();//Dummy node till vår nya sätt

	Node* dummyB = b.head->next;
	Node* dummyR = head->next;	//Når vi setet vi är i sett R//Ja vi når R
	//vi skriver head next för att inte räkna med vår dummynode!

	Node* dummyNew = newSet.head;//???? ska vi ha kvar den eller byta till dummy new direkt?


	//Node* headNew =   //vad ska dessa vara??
	//Node* dummyB = new Node(0, nullptr);


	while ((dummyB != nullptr) && (dummyR != nullptr)) {

		if (dummyB->value < dummyR->value) {
			//skapa en ny lista
			dummyNew->next = new Node(dummyB->value, nullptr);
			//de* List = new Node()

			dummyB = dummyB->next;
			dummyNew = dummyNew->next;
		}

		else if (dummyR->value < dummyB->value) {
			//lägga till på lista
			dummyNew->next = new Node(dummyR->value, nullptr);
			dummyR = dummyR->next;
			dummyNew = dummyNew->next;
		}

		else {
			//om de är samma 
			//lägg till i list
			dummyNew->next = new Node(dummyR->value, nullptr);
			dummyR = dummyR->next;
			dummyB = dummyB->next;
			dummyNew = dummyNew->next;
		}


	}

	//Lägg till i listorna
	while (dummyB != nullptr) {
		//Lägg till i listan
		dummyNew->next = new Node(dummyB->value, nullptr);
		dummyB = dummyB->next;
		dummyNew = dummyNew->next;

	}

	while (dummyR != nullptr) {
		//Lägg till i listan
		dummyNew->next = new Node(dummyR->value, nullptr);
		dummyR = dummyR->next;
		dummyNew = dummyNew->next;

	}

	return newSet;  // to be deleted
}

// Set intersection
Set Set::operator*(const Set& b) const
{
	// Add code


	Set newSet = Set();//Dummy node till vår nya sätt

	Node* dummyB = b.head->next;
	Node* dummyR = head->next;	//Når vi setet vi är i sett R//Ja vi når R
	//vi skriver head next för att inte räkna med vår dummynode!

	Node* dummyNew = newSet.head;//???? ska vi ha kvar den eller byta till dummy new direkt?


	//Node* headNew =   //vad ska dessa vara??
	//Node* dummyB = new Node(0, nullptr);

	while (dummyB != nullptr) {

		while (dummyR != nullptr) {

			if (dummyB->value == dummyR->value) {
				//skapa en ny lista
				dummyNew->next = new Node(dummyB->value, nullptr);
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
			dummyNew->next = new Node(dummyR->value, nullptr);
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
	//är en konstant så vi kan ej ändra den. Så vi kopierar den. Finns det ett bättre sätt?
	//Node* dummyR = newSet.head;//hoppar över dummyNoden??Den har ingen dummyNode?
	//int *newArray = new int[n];
	//varför funkar detta inte????????????????

	//Set newSet = Set();

	//Node* dummyR = head->next;//i den vi är i
	//Node* dummyNew = newSet.head;
	//if (dummyR != nullptr) {
	//	dummyNew->next = new Node(dummyR->value, nullptr);
	//	dummyR = dummyR->next;
	//	dummyNew = dummyNew->next;
	//}


	////dummyNew = newSet.head->next;//hoppa över dummy node. Nollställer
	//dummyR = head->next;
	//int counter = 0;

	//while (dummyR != nullptr) {

	//	if (dummyR->value == x) {

	//		counter++;
	//	}
	//	dummyR = dummyR->next;
	//}

	//if (counter == 0) {
	//	dummyNew->next = new Node(x, nullptr);
	//}

	////dummyNew = dummyNew->next;

	//return newSet;  // to be deleted

	//gör ett nytt sätt med det värdet vi fick in
	Set *newInt = new Set(x);
	//använder vår operator+ som vi skapat.
	const Set combinedSet = *this + *newInt;

	delete newInt;//vi behöver deleta annars memory leaks
	return combinedSet;

	//Set *theOne = new Set(x);

	//const Set s3 = *this + *theOne;

	//// Add code
	//return s3;  // to be deleted
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