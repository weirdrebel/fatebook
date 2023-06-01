#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <Windows.h>
using namespace std;

template <class T>
class stacknode // Stack
{
public:

	// Attributes
	T value;
	stacknode* next;

	// Constructors
	stacknode()
	{
		value = NULL;
		next = NULL;
	}

	stacknode(T tv)
	{
		value = tv;
		next = NULL;
	}
};

template <class T>
class stack
{
public:

	// Attributes
	stacknode<T>* head;
	stacknode<T>* tail;

	// Constructors
	stack()
	{
		head = tail = NULL;
	}

	// Other Functions
	bool isempty() // Check if stack is empty or not
	{
		if (head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void push(T tv) // Push into stack
	{
		stacknode<T>* mynode = new stacknode<T>(tv);

		if (head == NULL)
		{
			head = mynode;
			tail = mynode;
		}
		else
		{
			tail->next = mynode;
			tail = mynode;
		}
	}

	T pop() // Remove from tail - pop up
	{
		stacknode<T>* temp = head;
		stacknode<T>* previous = NULL;
		T val;

		if (tail != head)
		{
			val = tail->value;
			while (temp != tail)
			{
				previous = temp;
				temp = temp->next;
			}
			tail = previous;
			previous->next = NULL;
			delete temp;
		}
		else
		{
			val = head->value;
			delete head;
			head = tail = NULL;
		}
		return val;
	}
};

class timee // Current time
{
public:

	// Attributes
	int hours;
	int mins;
	int secs;

	// Constructors
	timee() :hours(0), mins(0), secs(0)
	{
	}

	timee(int th, int tm, int ts) :hours(th), mins(tm), secs(ts)
	{
	}

	// Other Functions
	void setTime(int th, int tm, int ts)
	{
		hours = th;
		mins = tm;
		secs = ts;
	}

	void display()
	{
		cout << "Time : " << hours << ":" << mins << ":" << secs << endl << endl;
	}
};

class date // Current date
{
public:

	// Attributes
	int day;
	int month;
	int year;

	// Constructors
	date() : day(0), month(0), year(0)
	{
	}

	date(int td, int tm, int ty) :day(td), month(tm), year(ty)
	{
	}

	// Other Functions
	void setDate(int td, int tm, int ty)
	{
		day = td;
		month = tm;
		year = ty;
	}

	void display()
	{
		cout << "Date : " << day << "/" << month << "/" << year << "          ";
	}
};

class mnode // Message node
{
public:

	// Attributes
	string m; // Message
	date d; // Message date
	timee t; // Message time
	string s; // Sender's username
	string r; // Receipient's username

	mnode* next; // next node

	// Constructors
	mnode()
	{
		next = NULL;
	}

	mnode(string ts, string tr)
	{
		s = ts;
		r = tr;
		next = NULL;
	}

	mnode(string tm, string ts, string tr)
	{
		m = tm;
		s = ts;
		r = tr;
		next = NULL;
	}

	mnode(string tm, string ts, string tr, date td, timee tt)
	{
		m = tm;
		s = ts;
		r = tr;
		d = td;
		t = tt;
		next = NULL;
	}

	// Other Functions
	void emts()// Enter message to send
	{
		cout << "Enter message : ";
		cin.ignore();
		getline(cin, m);

		time_t tt = time(NULL);
		tm* now = localtime(&tt);

		t.setTime(now->tm_hour, now->tm_min, now->tm_sec);
		d.setDate(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
	}

	void mdisplay() // A single mesage display
	{
		cout << "From : " << s << "          " << "To : " << r << endl;
		cout << "Message : " << m << endl;
		d.display();
		t.display();
	}
};

class message // Chat ( Messages List )
{
public:

	// Attributes
	mnode* head;
	mnode* tail;

	// Constructors
	message()
	{
		head = NULL;
		tail = NULL;
	}

	// Other Functions
	void Insert(string ts, string tr) // To send a message
	{
		mnode* mynode = new mnode(ts, tr);
		mynode->emts();

		if (head == NULL)
		{
			head = mynode;
			tail = mynode;
		}
		else
		{
			tail->next = mynode;
			tail = tail->next;
		}
	}

	void Insertcopy(mnode* a)
	{
		mnode* mynode = new mnode(a->m, a->s, a->r, a->d, a->t);

		if (head == NULL)
		{
			head = mynode;
			tail = mynode;
		}
		else
		{
			tail->next = mynode;
			tail = tail->next;
		}
	}

	void mdisplayall() // Display all messages
	{
		mnode* temp = head;
		while (temp != NULL)
		{
			temp->mdisplay();
			temp = temp->next;
		}
	}

	void emptylistm() // Delete chat
	{
		mnode* temp = head;
		tail = NULL;

		while (temp != NULL)
		{
			head = head->next;
			temp->next = NULL;
			delete temp;

			temp = head;;
		}
	}
};

class rnode // Reply node
{
public:

	// Attributes
	string r; // Reply
	string un; // Username
	date d; // Reply date
	timee t; // Reply time
	int rn; // Reply no.

	rnode* next; // next node

	// Constructors
	rnode()
	{
		rn = 0;
		next = NULL;
	}

	rnode(string tun, int trn)
	{
		un = tun;
		rn = trn;
		next = NULL;
	}

	// Other functions
	void rtc() // Enter reply to a comment
	{
		cout << "Enter reply : ";
		cin.ignore();
		getline(cin, r);

		time_t tt = time(NULL);
		tm* now = localtime(&tt);

		t.setTime(now->tm_hour, now->tm_min, now->tm_sec);
		d.setDate(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
	}

	void rdisplay() // Display a single reply
	{
		cout << "Reply no : " << rn << endl;
		cout << "Username : " << un << endl;
		cout << "Reply : " << r << endl;
		d.display();
		t.display();
	}
};

class reply // Reply list
{
public:

	// Attributes
	rnode* head;
	rnode* tail;
	int counter;

	// Constructors
	reply()
	{
		head = NULL;
		tail = NULL;
		counter = 0;
	}

	// Other Functions
	void Insert(string tun) // To add a reply
	{
		counter++;
		rnode* mynode = new rnode(tun, counter);
		mynode->rtc();

		if (head == NULL)
		{
			head = mynode;
			tail = mynode;
		}
		else
		{
			tail->next = mynode;
			tail = tail->next;
		}

		cout << "Your reply has been added successfully. " << endl;
	}

	void rdisplayall() // Display all replies
	{
		rnode* temp = head;
		while (temp != NULL)
		{
			temp->rdisplay();
			temp = temp->next;
		}
	}

	bool remover(int replyno) // Delete a reply
	{
		rnode* temp = head;
		rnode* previous = NULL;
		if (replyno == head->rn)
		{
			head = head->next;
			temp->next = NULL;
			delete temp;
			return true;
		}
		else if (replyno == tail->rn)
		{
			while (temp != tail)
			{
				previous = temp;
				temp = temp->next;
			}
			previous->next = NULL;
			tail = previous;
			delete temp;
			return true;
		}
		else
		{			
			while (temp != NULL)
			{
				if (replyno != temp->rn)
				{
					previous = temp;
					temp = temp->next;
				}
				else
				{
					previous->next = temp->next;
					temp->next = NULL;
					delete temp;
					return true;
				}
			}
		}
		return false;
	}

	string searchr(int replyno) // Search username who made a reply and return
	{
		rnode* temp = head;
		if (replyno == head->rn)
		{
			return head->un;
		}
		else if (replyno == tail->rn)
		{
			return tail->un;
		}
		else
		{
			while (temp != NULL)
			{
				if (replyno != temp->rn)
				{
					temp = temp->next;
				}
				else
				{
					return temp->un;
				}
			}
		}
		return "NULL";
	}

	void emptylistr() // Delete all replies
	{
		rnode* temp = head;
		tail = NULL;

		while (temp != NULL)
		{
			head = head->next;
			temp->next = NULL;
			delete temp;

			temp = head;
		}
		counter = 0;
	}
};

class cnode // Comment node
{
public:

	// Attributes
	string c; // Comment
	string un; // Username
	date d; // Comment date
	timee t; // Comment time
	int cn; // Comment no.
	reply replies;

	cnode* next; // next node

	// Constructors
	cnode()
	{
		cn = 0;
		next = NULL;
	}

	cnode(string tun, int tcn)
	{
		un = tun;
		cn = tcn;
		next = NULL;
	}

	// Other functions
	void cmt() // Enter comment
	{
		cout << "Enter comment : ";
		cin.ignore();
		getline(cin, c);

		time_t tt = time(NULL);
		tm* now = localtime(&tt);

		t.setTime(now->tm_hour, now->tm_min, now->tm_sec);
		d.setDate(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
	}

	void cdisplay() // Display a single reply
	{
		cout << "Comment no : " << cn << endl;
		cout << "Username : " << un << endl;
		cout << "Comment : " << c << endl;
		d.display();
		t.display();
	}
};

class comment // Comment list
{
public:

	// Attributes
	cnode* head;
	cnode* tail;
	int counter;

	// Constructors
	comment()
	{
		head = NULL;
		tail = NULL;
		counter = 0;
	}

	// Other Functions
	void Insert(string tun) // To add a comment
	{
		counter++;
		cnode* mynode = new cnode(tun, counter); // Parameters : username and comment counter
		mynode->cmt();

		if (head == NULL)
		{
			head = mynode;
			tail = mynode;
		}
		else
		{
			tail->next = mynode;
			tail = tail->next;
		}

		cout << "Your comment has been added successfully. " << endl;
	}

	bool removec(int cno) // Delete a comment
	{
		cnode* temp = head;
		cnode* previous = NULL;
		if (cno == head->cn)
		{
			head = head->next;
			temp->replies.emptylistr();
			temp->next = NULL;
			delete temp;
			return true;
		}
		else if (cno == tail->cn)
		{
			while (temp != tail)
			{
				previous = temp;
				temp = temp->next;
			}
			previous->next = NULL;
			tail = previous;
			temp->replies.emptylistr();
			delete temp;
			return true;
		}
		else
		{
			while (temp != NULL)
			{
				if (cno != temp->cn)
				{
					previous = temp;
					temp = temp->next;
				}
				else
				{
					previous->next = temp->next;
					temp->replies.emptylistr();
					temp->next = NULL;
					delete temp;
					return true;
				}
			}
		}
		return false;
	}

	cnode* searchc(int cno) // Search a comment
	{
		cnode* temp = head;
		if (cno == head->cn)
		{
			return head;
		}
		else if (cno == tail->cn)
		{
			return tail;
		}
		else
		{
			while (temp != NULL)
			{
				if (cno != temp->cn)
				{
					temp = temp->next;
				}
				else
				{
					return temp;
				}
			}
		}
		return NULL;
	}

	void cdisplayall() // Display all comments - New one at first
	{
		cnode* temp = head;
		stack<cnode*> st;

		while (temp != NULL)
		{
			st.push(temp);
			temp = temp->next;
		}

		while (!st.isempty())
		{
			temp = st.pop();
			temp->cdisplay();
		}

	}

	void emptylistc() // Delete all comments
	{
		cnode* temp = head;
		tail = NULL;

		while (temp != NULL)
		{
			head = head->next;
			temp->replies.emptylistr();
			temp->next = NULL;
			delete temp;

			temp = head;
		}
		counter = 0;
	}
};

class pnode // Post node
{
public:

	// Attributes
	string p; // Post
	string un; // Username of post maker
	date d; // Post date
	timee t; // Post time
	int pn; // Post number
	comment clist; // Comments on the post

	pnode* next; // next node

	// Constructors
	pnode()
	{
		pn = 0;
		next = NULL;
	}

	pnode(string tun,int tpn) // Parameters : username and post number
	{
		un = tun;
		pn = tpn;
		next = NULL;
	}

	// Other functions
	void makep() // make post
	{
		cout << "Write your post : ";
		cin.ignore();
		getline(cin, p);

		time_t tt = time(NULL);
		tm* now = localtime(&tt);

		t.setTime(now->tm_hour, now->tm_min, now->tm_sec);
		d.setDate(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
	}

	void changep() // Update post
	{
		cout << endl << "Update your post : ";
		cin.ignore();
		getline(cin, p);
	}

	void pdisplay() // Display a single post
	{
		cout << "Post no : " << pn << endl;
		cout << "Username : " << un << endl;
		cout << "Post : " << p << endl;
		d.display();
		t.display();
	}
};

class stacknodeS // Stack
{
public:

	// Attributes
	pnode* value;
	long long int seconds;
	stacknodeS* next;

	// Constructors
	stacknodeS()
	{
		seconds = 0;
		value = NULL;
		next = NULL;
	}

	stacknodeS(pnode* tv, long long int ts)
	{
		value = tv;
		seconds = ts;
		next = NULL;
	}
};

class stackS
{
public:

	// Attributes
	stacknodeS* head;
	stacknodeS* tail;

	// Constructors
	stackS()
	{
		head = tail = NULL;
	}

	// Other Functions
	bool isempty() // Check if stack is empty or not
	{
		if (head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void push(pnode* tv, long long int ts) // Push into stack
	{
		stacknodeS* mynode = new stacknodeS(tv, ts);

		if (head == NULL)
		{
			head = mynode;
			tail = mynode;
		}
		else if (ts < head->seconds)
		{
			mynode->next = head;
			head = mynode;
		}
		else if (ts > tail->seconds)
		{
			tail->next = mynode;
			tail = tail->next;
		}
		else
		{
			stacknodeS* t = head;
			stacknodeS* previous = NULL;

			while (ts > t->seconds)
			{
				previous = t;
				t = t->next;
			}

			previous->next = mynode;
			mynode->next = t;
		}
	}

	pnode* pop() // Remove from tail - pop up
	{
		stacknodeS* temp = head;
		stacknodeS* previous = NULL;
		pnode* val = NULL;

		if (tail != head)
		{
			val = tail->value;
			while (temp != tail)
			{
				previous = temp;
				temp = temp->next;
			}
			tail = previous;
			previous->next = NULL;
			delete temp;
		}
		else if (tail == head)
		{
			val = head->value;
			delete head;
			head = tail = NULL;
		}
		return val;
	}
};

class post // Post list
{
public:

	// Attributes
	pnode* head;
	pnode* tail;
	int counter;

	// Constructors
	post()
	{
		head = tail = NULL;
		counter = 0;
	}

	// Other functions
	void Insert(string tun) // To make a new post
	{
		counter++;
		pnode* mynode = new pnode(tun, counter); // Parameters : username and post counter
		mynode->makep();

		if (head == NULL)
		{
			head = mynode;
			tail = mynode;
		}
		else
		{
			tail->next = mynode;
			tail = tail->next;
		}

		cout << endl << "Your post has been created successfully. " << endl;
	}

	void pdisplayall() // Display all posts - Newly added first
	{
		pnode* temp = head;
		stack<pnode*> st;

		while (temp != NULL)
		{
			st.push(temp);
			temp = temp->next;
		}

		while (!st.isempty())
		{
			temp = st.pop();
			temp->pdisplay();
		}
	}

	bool updatep(int pno) // Update a post // Parameter : post number
	{
		pnode* temp = head;
		if (pno == head->pn)
		{
			head->changep();
			return true;
		}
		else if (pno == tail->pn)
		{
			tail->changep();
			return true;
		}
		else
		{
			while (temp != NULL)
			{
				if (pno == temp->pn)
				{
					temp->changep();
					return true;
				}
				else
				{
					temp = temp->next;
				}
			}
		}
		return false;
	}

	bool removep(int pno) // Remove post // Parameter : post number
	{
		pnode* temp = head;
		pnode* previous = NULL;
		if (pno == head->pn)
		{
			head = head->next;
			temp->clist.emptylistc();
			temp->next = NULL;
			delete temp;
			return true;
		}
		else if (pno == tail->pn)
		{
			while (temp != tail)
			{
				previous = temp;
				temp = temp->next;
			}
			previous->next = NULL;
			tail = previous;
			temp->clist.emptylistc();
			delete temp;
			return true;
		}
		else
		{
			while (temp != NULL)
			{
				if (pno != temp->pn)
				{
					previous = temp;
					temp = temp->next;
				}
				else
				{
					previous->next = temp->next;
					temp->clist.emptylistc();
					temp->next = NULL;
					delete temp;
					return true;
				}
			}
		}
		return false;
	}

	pnode* searchp(int pno) // Search a post // Parameter : post number
	{
		pnode* temp = head;
		if (pno == head->pn)
		{
			return head;
		}
		else if (pno == tail->pn)
		{
			return tail;
		}
		else
		{
			while (temp != NULL)
			{
				if (pno == temp->pn)
				{
					return temp;
				}
				else
				{
					temp = temp->next;
				}
			}
		}
		return NULL;
	}

	void emptylistp() // Delete all posts
	{
		pnode* temp = head;
		tail = NULL;

		while (temp != NULL)
		{
			head = head->next;
			temp->clist.emptylistc();
			temp->next = NULL;
			delete temp;

			temp = head;
		}
		counter = 0;
	}
};

class frnode // Friend request node
{
public:
	string un; // Username
	int reqn; // Request number

	frnode* next; // next node

	// Constructors
	frnode()
	{
		reqn = 0;
		next = NULL;
	}

	frnode(string tun, int treq)
	{
		un = tun;
		reqn = treq;
		next = NULL;
	}

	// Other functions
	void displayfr()
	{
		cout << reqn << ". " << un << endl;
	}

};

class friendreq // List of friend requests
{
public:

	// Attributes
	frnode* head;
	frnode* tail;
	int counter;

	// Constructors
	friendreq()
	{
		head = tail = NULL;
		counter = 0;
	}

	// Other functions
	void Insert(string tun) // To send a friend request
	{
		counter++;
		frnode* mynode = new frnode(tun, counter); // Parameters : username and friend request counter

		if (head == NULL)
		{
			head = mynode;
			tail = mynode;
		}
		else
		{
			tail->next = mynode;
			tail = tail->next;
		}
	}

	void frdisplayall() // Display all friend requests
	{
		frnode* temp = head;
		while (temp != NULL)
		{
			temp->displayfr();
			temp = temp->next;
		}
	}

	void removefr(int frno) // Delete a friend request
	{
		frnode* temp = head;
		frnode* previous = NULL;
		if (frno == head->reqn) // if present at head
		{
			head = head->next;
			temp->next = NULL;
			delete temp;
		}
		else if (frno == tail->reqn) // if present at tail
		{
			while (temp != tail)
			{
				previous = temp;
				temp = temp->next;
			}
			previous->next = NULL;
			tail = previous;
			delete temp;
		}
		else // if present in between head & tail
		{
			while (temp != NULL)
			{
				if (frno != temp->reqn)
				{
					previous = temp;
					temp = temp->next;
				}
				else
				{
					previous->next = temp->next;
					temp->next = NULL;
					delete temp;
					return;
				}
			}
		}
	}

	string searchfr(int frno) // Return username of a friend request
	{
		frnode* temp = head;
		if (frno == head->reqn) // if present at head
		{
			return head->un;
		}
		else if (frno == tail->reqn) // if present at tail
		{
			return tail->un;
		}
		else // if present in between head & tail
		{
			while (temp != NULL)
			{
				if (frno != temp->reqn)
				{
					temp = temp->next;
				}
				else
				{
					return temp->un;
				}
			}
		}
		return "NULL";
	}
};

class fnode // Friend list node
{
public:

	// Attributes
	string un; // Ussername
	int fno; // Friend no. in the list
	message chat;

	fnode* next; // next node

	// Constructors
	fnode()
	{
		fno = 0;
		next = NULL;
	}

	fnode(string tun, int tfno)
	{
		un = tun;
		fno = tfno;
		next = NULL;
	}

	// Other functions
	void displayf()
	{
		cout << fno << ". " << un << endl;
	}
};

class friends
{
public:
	
	// Attributes
	fnode* head;
	fnode* tail;
	int counter;

	// Constructors
	friends()
	{
		head = tail = NULL;
		counter = 0;
	}

	// Other Functions
	void Insert(string tun) // To add a friend
	{
		counter++;
		fnode* mynode = new fnode(tun, counter); // Parameters : username and friends counter

		if (head == NULL)
		{
			head = mynode;
			tail = mynode;
		}
		else
		{
			tail->next = mynode;
			tail = tail->next;
		}
	}

	void frdisplayall() // Display all friends
	{
		fnode* temp = head;
		while (temp != NULL)
		{
			temp->displayf();
			temp = temp->next;
		}
	}

	void removef(int tfno) // To unfriend a friend
	{
		fnode* temp = head;
		fnode* previous = NULL;
		if (tfno == head->fno) // if present at head
		{
			head = head->next;
			temp->next = NULL;
			temp->chat.emptylistm();
			delete temp;
		}
		else if (tfno == tail->fno) // if present at tail
		{
			while (temp != tail)
			{
				previous = temp;
				temp = temp->next;
			}
			previous->next = NULL;
			tail = previous;
			temp->chat.emptylistm();
			delete temp;
		}
		else // if present in between head & tail
		{
			while (temp != NULL)
			{
				if (tfno != temp->fno)
				{
					previous = temp;
					temp = temp->next;
				}
				else
				{
					previous->next = temp->next;
					temp->next = NULL;
					temp->chat.emptylistm();
					delete temp;
					return;
				}
			}
		}
	}

	string searchf(int tfno) // To search a friend
	{
		fnode* temp = head;
		if (tfno == head->fno) // if present at head
		{
			return head->un;
		}
		else if (tfno == tail->fno) // if present at tail
		{
			return tail->un;
		}
		else // if present in between head & tail
		{
			while (temp != NULL)
			{
				if (tfno != temp->fno)
				{
					temp = temp->next;
				}
				else
				{
					return temp->un;
				}
			}
		}
		return "NULL";
	}

	fnode* searchfnode(int tfno) // To search a friend
	{
		fnode* temp = head;
		if (tfno == head->fno) // if present at head
		{
			return head;
		}
		else if (tfno == tail->fno) // if present at tail
		{
			return tail;
		}
		else // if present in between head & tail
		{
			while (temp != NULL)
			{
				if (tfno != temp->fno)
				{
					temp = temp->next;
				}
				else
				{
					return temp;
				}
			}
		}
		return NULL;
	}

	int searchfN(string tun) // To search a friend - return no. in the list
	{
		fnode* temp = head;
		if (tun == head->un) // if present at head
		{
			return head->fno;
		}
		else if (tun == tail->un) // if present at tail
		{
			return tail->fno;
		}
		else // if present in between head & tail
		{
			while (temp != NULL)
			{
				if (tun != temp->un)
				{
					temp = temp->next;
				}
				else
				{
					return temp->fno;
				}
			}
		}
		return -1;
	}

	fnode* searchnodeS(string tun) // To search a friend - return no. in the list
	{
		fnode* temp = head;
		if (tun == head->un) // if present at head
		{
			return head;
		}
		else if (tun == tail->un) // if present at tail
		{
			return tail;
		}
		else // if present in between head & tail
		{
			while (temp != NULL)
			{
				if (tun != temp->un)
				{
					temp = temp->next;
				}
				else
				{
					return temp;
				}
			}
		}
		return NULL;
	}

};

class snode
{
public:

	// Attributes
	string data;
	snode* next;

	// Constructors
	snode()
	{
		next = NULL;
	}

	snode(string tdd)
	{
		data = tdd;
		next = NULL;
	}

	// Other Functions
	void displays()
	{
		cout << "Username : " << data << endl << endl;
	}

};

class slist
{
public:

	// Attriutes
	snode* head;
	snode* tail;

	// Constructors
	slist()
	{
		head = tail = NULL;
	}

	// Other Functions
	void Insert(string ts) // To insert an username to prefix tree
	{
		snode* mynode = new snode(ts);

		if (head == NULL)
		{
			head = mynode;
			tail = mynode;
		}
		else
		{
			tail->next = mynode;
			tail = tail->next;
		}
	}
};

class ptnode 
{
public:

	// Attributes
	char ch; // Dode data
	bool terminal; // Chceking for a complete word
	slist unames; // stores the usernames when terminal is tree
	ptnode* child[27]; // Pointer array of characters

	// Constructors
	ptnode(char c)
	{
		ch = c;
		terminal = false;
		for (int i = 0; i < 27; i++)
		{
			child[i] = NULL;
		}
	}
};

class ptree
{
public:

	// Attributes
	ptnode* root;

	// Constructors
	ptree()
	{
		root = createNode('\0');
	}

	// Other Functions
	ptnode* createNode(char c) // Create node and return
	{
		ptnode* newNode = new ptnode(c);
		return newNode;
	}

	void Insert(string word, string tun) // Insert an alphabet // Prameters : Name & username
	{
		ptnode* temp = root;
		char ch = '\0';
		int pos = 0;

		for (int i = 0; i < word.length(); i++)
		{
			ch = word[i];

			if (ch == ' ')
			{
				pos = 26;
			}
			else
			{
				pos = ch - 'a';
			}

			if (temp->child[pos] == NULL)
			{
				temp->child[pos] = createNode(ch);
			}

			temp = temp->child[pos];
		}

		temp->terminal = true;
		temp->unames.Insert(tun);
	}

	void Display(ptnode* temp, string word) // Display words 
	{
		if (temp == NULL)
		{
			return;
		}

		if (temp != root)
		{
			word = word + temp->ch;
		}

		if (temp->terminal)
		{
			snode* store = temp->unames.head;

			while (store != NULL)
			{
				cout << "Name : " << word << endl;
				store->displays();

				store = store->next;
			}
		}

		for (int i = 0; i < 27; i++)
		{
			Display(temp->child[i], word);
		}
	}

	ptnode* search(ptnode* temp, string key, int index) // Search for wordb(may be by starting alphabets)
	{
		if (temp == NULL)
		{
			return 0;
		}

		char ch = key[index];

		if (index == key.size())
		{
			return temp;
		}

		int i;
		if (ch == ' ')
		{
			i = 26;
		}
		else
		{
			i = ch - 'a';
		}

		return	search(temp->child[i], key, ++index);
	}
};

class user
{
public:

	// Attributes
	string mn; // Mobile number (11 characters)
	string name; // Name of user
	string password; // User password (6 characters)
	string username; // Unique username

	post plist; // Posts
	friendreq requests; // Friend requests
	friends flist; // Friends's list

	//	Constructors
	user()
	{
	}

	user(string tmn, string tn, string tp, string tun)
	{
		mn = tmn;
		name = tn;
		password = tp;
		username = tun;
	}

	// Other Functions
	void setUser(string tmn, string tn, string tp, string tun)
	{
		mn = tmn;
		name = tn;
		password = tp;
		username = tun;
	}

	void setUserO(user temp)
	{
		mn = temp.mn;
		name = temp.name;
		password = temp.password;
		username = temp.username;
	}
};

class node // Tree node
{
public:

	// Attributes
	user data;
	int key;
	node* left;
	node* right;

	// Constructors
	node()
	{
		key = 0;
		left = right = NULL;
	}

	node(user temp, int tkey)
	{
		data = temp;
		key = tkey;
		left = right = NULL;
	}
};

class tree // Tree containg data of all users - Driving class
{
public:

	// Attributes
	node* root; // Root of tree
	ptree pt; // Prefix tree

	// Constructors
	tree()
	{
		root = NULL;
	}

	// Other functions
	int stoic(string a) // String to integer converter - Hashing
	{
		int b = 0;
		for (int i = 0; i < a.length(); i++)
		{
			b = b + a[i];
		}

		b = b % 1000; // Hashing
		return b;
	}

	void signup()
	{
		user temp;

		system("cls");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "SIGN UP" << endl << endl;

		againmn:
		cout << "Enter your mobile number : ";
		cin.ignore();
		getline(cin, temp.mn);

		while (temp.mn.length() < 11 || temp.mn.length() > 11)
		{
			cout << "Invalid : Mobile number must be comprised of 11 digits. " << endl;
			cout << "Enter your mobile number : ";
			getline(cin, temp.mn);
		}

		for (int i = 0; i < 11; i++)
		{
			char c = temp.mn[i];

			if (c < '0' || c > '9')
			{
				cout << "Invalid : Mobile number can be consist only of digits 0 - 9. " << endl;
				goto againmn;
			}
		}

		cout << "Enter your name : ";
		getline(cin, temp.name);

		cout << "Enter your password : ";
		getline(cin, temp.password);

		while (temp.password.length() < 6 || temp.password.length() > 6)
		{
			cout << "Invalid : Password must be comprised of 6 characters. " << endl;
			cout << "Enter your password : ";
			getline(cin, temp.password);
		}

		cout << "Enter your username : ";
		getline(cin, temp.username);

		int tkey = stoic(temp.username); // String to integer converter

		while (search(root, tkey, temp.username))
		{
			cout << "Invalid : This username is already taken, choose another one. " << endl;
			cout << "Enter your username : ";
			getline(cin, temp.username);

			tkey = stoic(temp.username); // String to integer converter
		}

		pt.Insert(temp.name, temp.username); // Enter into prefix tree

		insert(temp, tkey); // Adding a user

		cout << endl << "Your account has been created successfully. " << endl;
		cout << "Returning to main page in 5 seconds. " << endl;
	}

	void insert(user temp, int tkey) // Hash tree - AVL insertion
	{
		node* N = new node(temp, tkey);
		if (root == NULL)
		{
			root = N;
		}
		else
		{
			node* temp = root;
			while (true)
			{
				if (N->key < temp->key)
				{
					if (temp->left == NULL)
					{
						temp->left = N;
						break;
					}
					temp = temp->left;
				}
				else if (N->key == temp->key)
				{
					if (temp->left == NULL)
					{
						temp->left = N;
						break;
					}
					else
					{
						N->left = temp->left;
						temp->left = N;
						break;
					}
				}
				else
				{
					if (temp->right == NULL)
					{
						temp->right = N;
						break;
					}
					temp = temp->right;
				}
			}
		}
	}

	bool search(node* temp, int tkey, string un, bool a = false)
	{
		if (temp != NULL)
		{
			if (tkey == temp->key)
			{
				if (un == temp->data.username)
				{
					a = true;
				}
			}
		}
		else
		{
			return false;
		}
		
		if (temp->left != NULL)
		{
			a = search(temp->left, tkey, un, a);
		}
		
		if (temp->right != NULL)
		{
			a = search(temp->right, tkey, un, a);
		}
		
		return a;
	}

	node* searchN(node* temp, int tkey, string un, node* a = NULL) // Search & return node
	{
		if (tkey == temp->key)
		{
			if (un == temp->data.username)
			{
				return temp;
			}
		}

		if (temp->left != NULL)
		{
			a = searchN(temp->left, tkey, un, a);
		}
		if (temp->right != NULL)
		{
			a = searchN(temp->right, tkey, un, a);
		}

		return a;
	}

	void login() // Log in to application
	{
		if (root != NULL)
		{
			string un, ps;
			node* store = NULL;
			int check = 0;

			system("cls");
			cout << "       ---  FATEBOOK  ---       " << endl << endl;
			cout << "LOG IN" << endl << endl;

			cin.ignore();
			cout << "Username : ";
			getline(cin, un);

			int tkey = stoic(un); // Convert string to integer

			while (!search(root, tkey, un))
			{
				cout << "Invalid : Entered username doesn't exist, try again." << endl;
				cout << "Username : ";
				getline(cin, un);

				tkey = stoic(un); // Convert string to integer
			}

			store = searchN(root, tkey, un);

		loop:
			cout << "Password : ";
			getline(cin, ps);

			while (ps.length() < 6 || ps.length() > 6)
			{
				cout << "Invalid : Password must be comprised of 6 characters. " << endl;
				cout << "Password : ";
				getline(cin, ps);
			}

			if (check < 3)
			{
				if (ps != store->data.password)
				{
					cout << "Invalid : Wrong password, try again. " << endl;
					check++;
					goto loop;
				}
				else
				{
					menuafterlogin(store);
				}
			}
			else
			{
				cout << "Invalid : You've entered wrong password 3 times. " << endl;
				forgotmenu();
			}
		}
		else
		{
			cout << "No user has signed in yet. " << endl;
			cout << "Returing to previous menu in 3 seconds. " << endl;
			Sleep(3000);
			mainmenu();
		}
	}

	void forgotpassword() // Forgot password
	{
		string un, mp;
		node* store = NULL;

		system("cls");
		cout << "FORGOT PASSWORD " << endl;

		cin.ignore();
		cout << "Username : ";
		getline(cin, un);

		int tkey = stoic(un); // Convert string to integer

		while (!search(root, tkey, un))
		{
			cout << "Invalid : Entered username doesn't exist, try again." << endl;
			cout << "Username : ";
			getline(cin, un);

			tkey = stoic(un); // Convert string to integer
		}

		store = searchN(root, tkey, un);

		again:
		cout << "To verify, enter your mobile number : ";
		getline(cin, mp);

		while (mp.length() < 11 || mp.length() > 11)
		{
			cout << "Invalid : Mobile number must be comprised of 11 digits. " << endl;
			cout << "To verify, enter your mobile number : ";
			getline(cin, mp);
		}

		for (int i = 0; i < 11; i++)
		{
			char c = mp[i];

			if (c < '0' || c > '9')
			{
				cout << "Invalid : Mobile number can be consist only of digits 0 - 9. " << endl;
				goto again;
			}
		}

		if (mp == store->data.mn)
		{
			cout << "Enter your new password : ";
			getline(cin, store->data.password);

			while (store->data.password.length() < 6 || store->data.password.length() > 6)
			{
				cout << "Invalid : Password must be comprised of 6 characters. " << endl;
				cout << "Enter your new password : ";
				getline(cin, store->data.password);
			}

			cout << endl << "Your password has been updated successfully. " << endl;
			cout << "Returning to main page in 5 seconds. " << endl;
		}
		else
		{
			cout << "Unauthorized activity detected, returning to main page in 5 seconds. " << endl;
		}
	}

	void deletepost(node* current) // Delete a post
	{
		if (current->data.plist.counter == 0)
		{
			cout << "No posts yet. " << endl;
		}
		else
		{
			if (current->data.plist.head != NULL)
			{
				int i;
				cout << "To delete a post enter the post number : ";
				cin >> i;

			again:
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(256, '\n');
					cout << "Characters not allowed, enter an integer : " << endl;
					cin >> i;
				}

				while (i < 0 || i > current->data.plist.counter)
				{
					cout << "Invalid post number, re-enter : ";
					cin >> i;
					goto again;
				}

				if (current->data.plist.removep(i))
				{
					cout << "The post has been deleted successfully. " << endl;
				}
				else
				{
					cout << "The post is already deleted. " << endl;
				}
			}
			else
			{
				cout << "No posts yet. " << endl;
			}
		}
		cout << "Returning to previous menu in 3 seconds. " << endl;
	}

	void updatepost(node* current) // update a post
	{
		if (current->data.plist.counter == 0 || current->data.plist.head == NULL)
		{
			cout << "No posts yet. " << endl;
		}
		else
		{
			int i;
			cout << "To update a post enter the post number : ";
			cin >> i;

		again:
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Characters not allowed, enter an integer : " << endl;
				cin >> i;
			}

			while (i < 0 || i > current->data.plist.counter)
			{
				cout << "Invalid post number, re-enter : ";
				cin >> i;
				goto again;
			}

			if (current->data.plist.updatep(i))
			{
				cout << endl << "The post has been updated successfully. " << endl;
			}
			else
			{
				cout << "The post doesn't exist. " << endl;
			}
		}
		cout << "Returning to previous menu in 3 seconds. " << endl;
	}

	void openapost(node* current)
	{
		if (current->data.plist.counter == 0 || current->data.plist.head == NULL)
		{
			cout << "No posts yet. " << endl;
			cout << "Returning to previous menu in 3 seconds. " << endl;
			Sleep(3000); // Seconds
			vapmenu(current);
		}
		else
		{
			int i;
			pnode* s;
			cout << "To open a post enter the post number : ";
			cin >> i;

		again:
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Characters not allowed, enter an integer : " << endl;
				cin >> i;
			}

			while (i < 0 || i > current->data.plist.counter)
			{
				cout << "Invalid post number, re-enter : ";
				cin >> i;
				goto again;
			}

			s = current->data.plist.searchp(i);

			if (s == NULL)
			{
				cout << "The post doesn't exist. " << endl;
				cout << "Returning to previous menu in 3 seconds. " << endl;
				Sleep(3000);
				vapmenu(current);
			}
			else
			{
				oapmenu(current, s);
			}
		}
	}

	void deletecomment(node* current, pnode* s) // Delete a comment
	{
		if (s->clist.counter == 0 || s->clist.head == NULL)
		{
			cout << "No comments yet. " << endl;
		}
		else
		{
			int i;
			cout << "To delete a comment enter the comment number : ";
			cin >> i;

			again:
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Characters not allowed, enter an integer : " << endl;
				cin >> i;
			}

			while (i < 0 || i > s->clist.counter)
			{
				cout << "Invalid comment number, re-enter : ";
				cin >> i;
				goto again;
			}

			if (s->clist.removec(i))
			{
				cout << "The comment has been deleted successfully. " << endl;
			}
			else
			{
				cout << "The comment is already deleted. " << endl;
			}
		}
		cout << "Returning to previous menu in 3 seconds. " << endl;
	}

	void openacomment(node* current, pnode* s) // Open a comment
	{
		if (s->clist.counter == 0 || s->clist.head == NULL)
		{
			cout << "No comments yet. " << endl;
			cout << "Returning to previous menu in 3 seconds. " << endl;
			Sleep(3000); // Seconds
			oapmenu(current, s);

		}
		else
		{
			int i;
			cnode* q;
			cout << "To open a comment enter the comment number : ";
			cin >> i;

			again:
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Characters not allowed, enter an integer : " << endl;
				cin >> i;
			}

			while (i < 0 || i > s->clist.counter)
			{
				cout << "Invalid comment number, re-enter : ";
				cin >> i;
				goto again;
			}

			q = s->clist.searchc(i);

			if (q == NULL)
			{
				cout << "The comment doesn't exist. " << endl;
				cout << "Returning to previous menu in 3 seconds. " << endl;
				Sleep(3000);
				oapmenu(current, s);
			}
			else
			{
				oacmenu(current, s, q); // Open a comment menu
			}
		}
	}

	void deletereply(node* current, pnode* s, cnode* q)
	{
		if (q->replies.counter == 0 || q->replies.head == NULL)
		{
			cout << "No replies yet. " << endl;
		}
		else
		{
			int i;
			cout << "To delete a reply enter the reply number : ";
			cin >> i;

			again:
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Characters not allowed, enter an integer : " << endl;
				cin >> i;
			}

			while (i < 0 || i > q->replies.counter)
			{
				cout << "Invalid comment number, re-enter : ";
				cin >> i;
				goto again;
			}

			if (q->replies.remover(i))
			{
				cout << "The reply has been deleted successfully. " << endl;
			}
			else
			{
				cout << "The reply is already deleted. " << endl;
			}
		}
		
		cout << "Returning to previous menu in 3 seconds. " << endl;
	}

	void viewfriendprofile(node* current) // View a friend's profile
	{
		if (current->data.flist.counter == 0 || current->data.flist.head == NULL)
		{
			cout << endl << "No friends yet. " << endl;
			cout << "Returning to previous menu in 3 seconds. " << endl;
			Sleep(3000); // 3 Seconds
			myfriendsmenu(current);
		}
		else
		{
			int i;
			string friendusername;
			cout << endl << "Enter the number associated with friend's username in the list : ";
			cin >> i;

			again:
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Characters not allowed, enter an integer : " << endl;
				cin >> i;
			}

			while (i < 0 || i > current->data.flist.counter)
			{
				cout << "Invalid number, re-enter : ";
				cin >> i;
				goto again;
			}

			if (current->data.flist.head != NULL)
			{
				friendusername = current->data.flist.searchf(i);

				if (friendusername == "NULL")
				{
					cout << "You are not friends. " << endl;
					cout << "Returning to previous menu in 3 seconds. " << endl;
					Sleep(3000); // 3 Seconds
					myfriendsmenu(current);
				}
				else
				{
					int tkey = stoic(friendusername); // Converting string to integer
					node* sfriend = searchN(root, tkey, friendusername);

					vafmenu(current, sfriend);
				}
			}
			else
			{
				cout << endl << "No friends yet. " << endl;
				cout << "Returning to previous menu in 3 seconds. " << endl;
				Sleep(3000); // 3 Seconds
				myfriendsmenu(current);
			}
			}
	}

	void openpostF(node* current, node* sfriend) // Open a friend's post
	{
		if (sfriend->data.plist.counter == 0 || sfriend->data.plist.head == NULL)
		{
			cout << "No posts yet. " << endl;
			cout << "Returning to previous menu in 3 seconds. " << endl;
			Sleep(3000); // 3 Seconds
			vfpmenu(current, sfriend);
		}
		else
		{
			int i;
			pnode* s;
			cout << "To open a post enter the post number : ";
			cin >> i;

		again:
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Characters not allowed, enter an integer : " << endl;
				cin >> i;
			}

			while (i < 0 || i > sfriend->data.plist.counter)
			{
				cout << "Invalid post number, re-enter : ";
				cin >> i;
				goto again;
			}

			s = sfriend->data.plist.searchp(i);

			if (s == NULL)
			{
				cout << "The post doesn't exist. " << endl;
				cout << "Returning to previous menu in 3 seconds. " << endl;
				Sleep(3000); // 3 Seconds
				vfpmenu(current, sfriend);
			}
			else
			{
				oapmenuF(current, sfriend, s); // Open a post menu
			}
		}
	}

	void opencommentF(node* current, node* sfriend, pnode* s) // Open a comment
	{
		if (s->clist.counter == 0 || s->clist.head == NULL)
		{
			cout << "No comments yet. " << endl;
			cout << "Returning to previous menu in 3 seconds. " << endl;
			Sleep(3000); // 3 Seconds
			oapmenuF(current, sfriend, s);
		}
		else
		{
			int i;
			cnode* q;
			cout << "To open a comment enter the comment number : ";
			cin >> i;

		again:
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Characters not allowed, enter an integer : " << endl;
				cin >> i;
			}

			while (i < 0 || i > s->clist.counter)
			{
				cout << "Invalid comment number, re-enter : ";
				cin >> i;
				goto again;
			}

			q = s->clist.searchc(i);

			if (q == NULL)
			{
				cout << "The comment doesn't exist. " << endl;
				cout << "Returning to previous menu in 3 seconds. " << endl;
				Sleep(3000); // 3 Seconds
				oapmenuF(current, sfriend, s);
			}
			else
			{
				oacmenuF(current, sfriend, s, q); // Open a comment of friend's post - menu
			}
		}
	}

	void deletethiscommentF(node* current, node* sfriend, pnode* s, cnode* q) // Delete your comment on friend's post
	{
		int i = q->cn;

		if (s->clist.removec(i))
		{
			cout << "The comment has been deleted successfully. " << endl;
		}
		else
		{
			cout << "The comment is already deleted. " << endl;
		}
		cout << "Returning to previous menu in 3 seconds. " << endl;
	}

	void deletereplyF(node* current, node* sfriend, pnode* s, cnode* q) // Delete your reply on friend's post
	{
		if (q->replies.head == NULL)
		{
			cout << "No replies yet. " << endl;
		}
		else
		{
			int i;
			cout << endl << "To delete a reply enter the reply number : ";
			cin >> i;

		again:
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Characters not allowed, enter an integer : " << endl;
				cin >> i;
			}

			while (i < 0 || i > q->replies.counter)
			{
				cout << "Invalid comment number, re-enter : ";
				cin >> i;
				goto again;
			}

			string replierusername = q->replies.searchr(i);

			if (replierusername == "NULL")
			{
				cout << "The reply doesn't exist. " << endl;
			}
			else
			{
				if (replierusername == current->data.username)
				{
					q->replies.remover(i);
					cout << "The reply has been deleted successfully. " << endl;
				}
				else
				{
					cout << "You can't delete comments/replies made by someone else on someone's post. " << endl;
				}
			}
		}

		cout << "Returning to previous menu in 3 seconds. " << endl;
	}

	void unfriend(node* current, node* sfriend) // Unfriend a friend
	{
		int cnumber; // friend no. of current user in other friend's friendlist
		int fnumber; // friend no. of friend in friendlist of current user

		cnumber = sfriend->data.flist.searchfN(current->data.username);
		fnumber = current->data.flist.searchfN(sfriend->data.username);

		sfriend->data.flist.removef(cnumber);
		current->data.flist.removef(fnumber);

		cout << "You're no longer friends. " << endl;
		cout << "Returning to previous menu in 3 seconds. " << endl;
	}

	void openfriendrequest(node* current)
	{
		if (current->data.requests.head == NULL)
		{
			cout << "No pending requests. " << endl;
			cout << "Returning to previous menu in 3 seconds. " << endl;
			Sleep(3000); // 3 Seconds
			friendtab(current);
		}
		else
		{
			int i;
			string requestusername;
			cout << endl << "Enter the number associated with friend request's username in the list : ";
			cin >> i;

		again:
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Characters not allowed, enter an integer : " << endl;
				cin >> i;
			}

			while (i < 0 || i > current->data.requests.counter)
			{
				cout << "Invalid number, re-enter : ";
				cin >> i;
				goto again;
			}

			requestusername = current->data.requests.searchfr(i);

			if (requestusername == "NULL")
			{
				cout << "Friend request doesn't exist. " << endl;
				cout << "Returning to previous menu in 3 seconds. " << endl;
				Sleep(3000); // 3 Seconds
				friendtab(current);
			}
			else
			{
				int tkey = stoic(requestusername); // Convert string to integer
				node* sfriend = searchN(root, tkey, requestusername);
				
				openfrmenu(current, sfriend, i);
			}
		}
	}

	void declinefriendrequest(node* current, int reqno) //	Decline a friend request
	{
		current->data.requests.removefr(reqno);

		cout  << endl << "The request has been declined. " << endl;
		cout << "Returning to previous menu in 3 seconds. " << endl;
	}

	void acceptfriendrequest(node* current, node* sfriend, int reqno) // Accept a friend request
	{
		current->data.flist.Insert(sfriend->data.username);
		sfriend->data.flist.Insert(current->data.username);

		current->data.requests.removefr(reqno); // Remove the request in the list

		cout << endl << "You both are now friends. " << endl;
		cout << "Returning to previous menu in 3 seconds. " << endl;
	}

	void sendfriendrequest(node* current)
	{
		string un;

		cin.ignore();
		cout << "Enter their username to send friend request : ";
		getline(cin, un);

		while (un == current->data.username)
		{
			cout << "You can't send a friend request to your own self. " << endl;
			cout << "Enter their username to send friend request : ";
			getline(cin, un);
		}

		int tkey = stoic(un); // Convert string to integer

		while (!search(root, tkey, un))
		{
			cout << "Invalid : Entered username doesn't exist, try again." << endl;
			cout << "Enter their username to send friend request : ";
			getline(cin, un);

			tkey = stoic(un); // Convert string to integer
		}

		node* sfriend = searchN(root, tkey, un);

		sfriend->data.requests.Insert(current->data.username);

		cout << endl << "Friend request has been sent successfully. " << endl;
		cout << "Returning to previous menu in 3 seconds. " << endl;
	}

	void openfriendchat(node* current)
	{
		if (current->data.flist.head == NULL)
		{
			cout << endl << "No friends yet. " << endl;
			cout << "Returning to previous menu in 3 seconds. " << endl;
			Sleep(3000); // 3 Seconds
			menuafterlogin(current);
		}
		else
		{
			int i;
			cout << endl << "Enter the number associated with friend's username in the list : ";
			cin >> i;

		again:
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Characters not allowed, enter an integer : " << endl;
				cin >> i;
			}

			while (i < 0 || i > current->data.flist.counter)
			{
				cout << "Invalid number, re-enter : ";
				cin >> i;
				goto again;
			}

			fnode * d = current->data.flist.searchfnode(i);

			if (d == NULL)
			{
				cout << "You are not friends. " << endl;
				cout << "Returning to previous menu in 3 seconds. " << endl;
				Sleep(3000); // 3 Seconds
				messagetab(current);
			}
			else
			{
				int tkey = stoic(d->un); // Converting string to integer
				node* sfriend = searchN(root, tkey, d->un);
				
				fnode* h = sfriend->data.flist.searchnodeS(current->data.username);

				openchatmenu(current, sfriend, d, h);
			}
		}
	}

	void changephonenumber(node* current)
	{
		cout << endl;
		string mp, ps;

		cin.ignore();
		again:
		cout << "Enter new mobile number : ";
		getline(cin, mp);

		while (mp.length() < 11 || mp.length() > 11)
		{
			cout << "Invalid : Mobile number must be comprised of 11 digits. " << endl;
			cout << "Enter new mobile number  : ";
			getline(cin, mp);
		}

		for (int i = 0; i < 11; i++)
		{
			char c = mp[i];

			if (c < '0' || c > '9')
			{
				cout << "Invalid : Mobile number can be consist only of digits 0 - 9. " << endl;
				goto again;
			}
		}

		cout << "Enter your password to continue : ";
		getline(cin, ps);

		if (ps == current->data.password)
		{
			current->data.mn = mp;
			cout << "Your mobile number has been updated. " << endl;
		}
		else
		{
			cout << "Your request can't be proceeded at this moment. " << endl;
		}
		cout << "Returning to previous menu in 3 seconds. " << endl;
	}
	
	void changepassword(node* current)
	{
		string ps;

		cin.ignore();
		cout << endl;
		cout << "Enter your old password: ";
		getline(cin, ps);

		if (ps == current->data.password)
		{
			cout << endl;
			cout << "Enter your new password : ";
			getline(cin, current->data.password);
			cout << "Your password has been updated successfully. " << endl;
		}
		else
		{
			cout << "Your request can't be proceeded at this moment. " << endl;
		}
		cout << "Returning to previous menu in 3 seconds. " << endl;
	}

	void hometabpostdisplay(node* current)
	{
		long long int seconds;
		stackS st;
		pnode* temp = current->data.plist.head;
		fnode* store = current->data.flist.head;

		while (temp != NULL)
		{
			seconds = converttime(temp);
			st.push(temp, seconds);

			temp = temp->next;
		}

		while (store != NULL) // Traversing friend list
		{
			int tkey = stoic(store->un); // string to integer converter
			node* sfriend = searchN(root, tkey, store->un);

			temp = sfriend->data.plist.head;

			while (temp != NULL) // Traversing posts of friends
			{
				seconds = converttime(temp);
				st.push(temp, seconds);

				temp = temp->next;
			}

			store = store->next;
		}

		// All the posts are pushed into the stack
		// Now display them

		while (!st.isempty())
		{
			temp = st.pop();
			temp->pdisplay();
		}
	}

	long long int converttime(pnode* r)
	{
		long long int seconds;
		
		seconds = r->t.secs + (((r->t.hours * 60) + r->t.mins) * 60) + (((r->d.year * 365) + (r->d.month * 30) + r->d.day) * 86400);
		return seconds;
	}

	void openposthometab(node* current) // Open a post in the home tab
	{
		string un;

		cin.ignore();
		cout << endl << "Enter the username of post maker : ";
		getline(cin, un);

		if (un == current->data.username)
		{
			openapost(current);
		}
		else
		{
			if (current->data.flist.head == NULL)
			{
				cout << endl << "You don't have any friends yet. " << endl;
				cout << "Returning to previous menu in 3 seconds. " << endl;
				Sleep(3000); // 3 Seconds
				viewposthomemenu(current);
			}
			else
			{
				int i = current->data.flist.searchfN(un);

				if (i == -1)
				{
					cout << "You are not friends. " << endl;
					cout << "Returning to previous menu in 3 seconds. " << endl;
					Sleep(3000); // 3 Seconds
					viewposthomemenu(current);
				}
				else
				{
					int tkey = stoic(un); // Converting string to integer
					node* sfriend = searchN(root, tkey, un);

					openpostF(current, sfriend);
				}
			}
		}
	}

		


	// Menus
	void mainmenu()
	{
		int choice;
		system("cls");
		system("color 97");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "1. Sign-up " << endl;
		cout << "2. Sign-in (Log-in) " << endl;
		cout << "3. Forgot Password " << endl;
		cout << "4. Exit " << endl << endl;
		cout << "Enter your choice from 1-4 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 4)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			signup();
			Sleep(5000);
			mainmenu();
			break;
		}
		case 2:
		{
			login();
			break;
		}
		case 3:
		{
			forgotpassword();
			Sleep(5000);
			mainmenu();
			break;
		}
		case 4:
		{
			exit(0);
		}
		}
	}

	void forgotmenu() // Forgot menu
	{
		int choice;
		cout << endl;
		cout << "1. Forget your password? " << endl;
		cout << "2. Go back to main page " << endl << endl;
		cout << "Enter your choice from 1-2 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 2)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			forgotpassword();
			Sleep(5000);
			mainmenu();
			break;
		}
		case 2:
		{
			mainmenu();
			break;
		}
		}
	}

	void menuafterlogin(node* current)
	{
		int choice;
		system("cls");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;
		cout << "1. Personal tab " << endl;
		cout << "2. Home tab " << endl;
		cout << "3. Friend tab " << endl;
		cout << "4. Messages tab " << endl;
		cout << "5. Account settings " << endl;
		cout << "6. Log out " << endl << endl;
		cout << "Enter your choice from 1-6 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 6)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			system("color 37");
			personaltab(current);
			break;
		}
		case 2:
		{
			system("color F9");
			hometab(current);
			break;
		}
		case 3:
		{
			system("color E0");
			friendtab(current);
			break;
		}
		case 4:
		{
			system("color 27");
			messagetab(current);
			break;
		}
		case 5:
		{
			system("color 40");
			accountsettings(current);
			break;
		}
		case 6:
		{
			cout << endl << "Wait, logging out from your account. " << endl;
			Sleep(5000); // Wait for 5 secs
			mainmenu();
			break;
		}
		}
	}

	// Personal tab
	void personaltab(node* current)
	{
		int choice;
		system("cls");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		cout << "1. Add a new post " << endl;
		cout << "2. View all posts " << endl;
		cout << "3. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-3 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 3)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			current->data.plist.Insert(current->data.username);
			Sleep(3000); // 3 Seconds
			personaltab(current);
			break;
		}
		case 2:
		{
			vapmenu(current);
			break;
		}
		case 3:
		{
			menuafterlogin(current);
			break;
		}
		}
	}

	void vapmenu(node* current) // View all posts menu
	{
		system("cls");
		int choice;
		cout << "       ---  FATEBOOK  ---       " << endl << endl;

		cout << "Username : " << current->data.username << endl << endl;
		current->data.plist.pdisplayall();

		cout << "What to do? " << endl;
		cout << "1. Open a post " << endl;
		cout << "2. Update a post " << endl;
		cout << "3. Delete a post " << endl;
		cout << "4. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-4 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 4)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			openapost(current);
			break;
		}
		case 2:
		{
			updatepost(current);
			Sleep(3000); // 3 seconds
			vapmenu(current);
			break;
		}
		case 3:
		{
			deletepost(current);
			Sleep(3000); // 3 seconds
			vapmenu(current);
			break;
		}
		case 4:
		{
			personaltab(current);
			break;
		}
		}
	}

	void oapmenu(node* current, pnode* s) // Open a post menu
	{
		system("cls");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		s->pdisplay();
		cout << "Comments : " << endl << endl;
		s->clist.cdisplayall();

		int choice;
		cout << "What to do? " << endl;
		cout << "1. Open a comment " << endl;
		cout << "2. Add a comment " << endl;
		cout << "3. Delete a comment " << endl;
		cout << "4. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-4 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 4)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			openacomment(current, s);
			break;
		}
		case 2:
		{	
			s->clist.Insert(current->data.username);
			Sleep(3000); // 3 Seconds
			oapmenu(current, s);
			break;
		}
		case 3:
		{
			deletecomment(current, s);
			Sleep(3000); // 3 Seconds
			oapmenu(current, s);
			break;
		}
		case 4:
		{
			vapmenu(current);
			break;
		}
		}
	}

	void oacmenu(node* current, pnode* s, cnode* q)
	{
		system("cls");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		q->cdisplay();
		cout << "Replies : " << endl << endl;
		q->replies.rdisplayall();

		int choice;
		cout << "What to do? " << endl;
		cout << "1. Reply " << endl;
		cout << "2. Delete a reply " << endl;
		cout << "3. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-3 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 3)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			q->replies.Insert(current->data.username); // Add a reply
			Sleep(3000); // 3 Seconds
			oacmenu(current, s, q);
			break;
		}
		case 2:
		{
			deletereply(current, s, q);
			Sleep(3000); // 3 Seconds
			oacmenu(current, s, q);
			break;
		}
		case 3:
		{
			oapmenu(current, s);
			break;
		}
		}
	}

	// Friend tab
	void friendtab(node* current) // Friends tab
	{
		int choice;
		system("cls");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;
		cout << "1. My friends " << endl;
		cout << "2. Add friend " << endl;
		cout << "3. Friend requests " << endl;
		cout << "4. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-4 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 4)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			myfriendsmenu(current);
			break;
		}
		case 2:
		{
			searchfriendmenu(current);
			break;
		}
		case 3:
		{
			friendrequestmenu(current);
			break;
		}
		case 4:
		{
			menuafterlogin(current);
			break;
		}
		}
	}

	void myfriendsmenu(node* current)
	{
		system("cls");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		cout << " My Friendlist" << endl << endl;
		current->data.flist.frdisplayall();
		cout << endl;

		int choice;
		cout << "What to do? " << endl;
		cout << "1. View friend's profile " << endl;
		cout << "2. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-2 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 2)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			viewfriendprofile(current);
			break;
		}
		case 2:
		{
			friendtab(current);
			break;
		}
		}
	}

	void vafmenu(node* current, node* sfriend) // View all friends
	{
		system("cls");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		cout << "Friends's name : " << sfriend->data.name << endl;
		cout << "Friend's username : " << sfriend->data.username << endl << endl;

		int choice;
		cout << "What to do? " << endl;
		cout << "1. View friend's posts " << endl;
		cout << "2. Unfriend " << endl;
		cout << "3. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-3 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 3)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			vfpmenu(current, sfriend);
			break;
		}
		case 2:
		{
			unfriend(current, sfriend);
			Sleep(3000); // 3 seconds
			myfriendsmenu(current);
			break;
		}
		case 3:
		{
			myfriendsmenu(current);
			break;
		}
		}

	}

	void vfpmenu(node* current, node* sfriend) // View friend's post menu
	{
		system("cls");
		int choice;
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		cout << "Friends's name : " << sfriend->data.name << endl;
		cout << "Friend's username : " << sfriend->data.username << endl << endl;

		cout << "Posts" << endl << endl;

		sfriend->data.plist.pdisplayall();

		cout << "What to do? " << endl;
		cout << "1. Open a post " << endl;
		cout << "2. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-2 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 2)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			openpostF(current, sfriend);
			break;
		}
		case 2:
		{
			vafmenu(current, sfriend);
			break;
		}
		}
	}

	void oapmenuF(node* current, node* sfriend, pnode* s) // Open a post of friend
	{
		system("cls");
		int choice;
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		cout << "Friends's name : " << sfriend->data.name << endl;
		cout << "Friend's username : " << sfriend->data.username << endl << endl;

		s->pdisplay();
		cout << "Comments : " << endl << endl;
		s->clist.cdisplayall();

		cout << "What to do? " << endl;
		cout << "1. Open a comment " << endl;
		cout << "2. Add a public comment " << endl;
		cout << "3. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-3 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 3)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			opencommentF(current, sfriend, s);
			break;
		}
		case 2:
		{
			s->clist.Insert(current->data.username);
			Sleep(3000); // 3 Seconds
			oapmenuF(current, sfriend, s);
			break;
		}
		case 3:
		{
			vfpmenu(current, sfriend); // View all posts of friend - menu
			break;
		}
		}
	}

	void oacmenuF(node* current, node* sfriend, pnode* s, cnode* q) // Open a comment of friend's post - menu
	{
		system("cls");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		q->cdisplay();
		cout << "Replies : " << endl << endl;
		q->replies.rdisplayall();

		int choice;
		if (q->un == current->data.username)
		{
			cout << "What to do? " << endl;
			cout << "1. Delete this comment " << endl;
			cout << "2. Reply to this comment " << endl;
			cout << "3. Delete any of your reply on this comment " << endl;
			cout << "4. Go back to previous menu " << endl << endl;
			cout << "Enter your choice from 1-4 : ";
			cin >> choice;

			again:
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Characters not allowed, enter an integer : " << endl;
				cin >> choice;
			}

			while (choice < 1 || choice > 4)
			{
				cout << "Wrong choice, Choose again : " << endl;
				cin >> choice;
				goto again;
			}

			switch (choice)
			{
			case 1:
			{
				deletethiscommentF(current, sfriend, s, q);
				Sleep(3000); // 3 Seconds
				oapmenuF(current, sfriend, s);
				break;
			}
			case 2:
			{
				q->replies.Insert(current->data.username); // Add a reply
				Sleep(3000); // 3 Seconds
				oacmenuF(current, sfriend, s, q); // Open a comment of friend's post - menu
				break;
			}
			case 3:
			{
				deletereplyF(current, sfriend, s, q);
				Sleep(3000); // 3 Seconds
				oacmenuF(current, sfriend, s, q);
				break;
			}
			case 4:
			{
				oapmenuF(current, sfriend, s);
				break;
			}
			}
		}
		else
		{
			cout << "What to do? " << endl;
			cout << "1. Reply to this comment " << endl;
			cout << "2. Delete any of your reply on this comment " << endl;
			cout << "3. Go back to previous menu " << endl << endl;
			cout << "Enter your choice from 1-3 : ";
			cin >> choice;

			while (choice < 1 || choice > 3)
			{
				cout << "Wrong choice, Choose again : " << endl;
				cin >> choice;
			}

			switch (choice)
			{
			case 1:
			{
				q->replies.Insert(current->data.username); // Add a reply
				Sleep(3000); // 3 Seconds
				oacmenuF(current, sfriend, s, q); // Open a comment of friend's post - menu
				break;
			}
			case 2:
			{
				deletereplyF(current, sfriend, s, q);
				Sleep(3000); // 3 Seconds
				oacmenuF(current, sfriend, s, q);
				break;
			}
			case 3:
			{
				oapmenuF(current, sfriend, s);
				break;
			}
			}
		}
	}

	void friendrequestmenu(node* current) // Friend request menu
	{
		system("cls");
		int choice;
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		cout << " Friend requests " << endl << endl;
		current->data.requests.frdisplayall();

		cout << endl << "What to do? " << endl;
		cout << "1. Open a request and respond " << endl;
		cout << "2. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-2 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 2)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			openfriendrequest(current);
			break;
		}
		case 2:
		{
			friendtab(current);
			break;
		}
		}
	}

	void openfrmenu(node* current, node* sfriend, int reqno) // 3rd parameter is the request no. in the list
	{
		system("cls");
		int choice;
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		cout << sfriend->data.username << " has sent you a friend request. " << endl << endl;

		cout << "1. Accept " << endl;
		cout << "2. Decline " << endl;
		cout << "3. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-3 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 3)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			acceptfriendrequest(current, sfriend, reqno);
			Sleep(3000); // 3 Seconds
			friendrequestmenu(current);
			break;
		}
		case 2:
		{
			declinefriendrequest(current, reqno);
			Sleep(3000); // 3 Seconds
			friendrequestmenu(current);
			break;
		}
		case 3:
		{
			friendrequestmenu(current);
			break;
		}
		}

	}

	void searchfriendmenu(node* current) // Search friend and send request
	{
		system("cls");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		cout << "Add a new a friend" << endl << endl;

		string element; // search element or key

		cin.ignore();
		cout << "Search ( By name ) : "; // By name
		getline(cin, element);

		ptnode* temp = pt.search(pt.root, element, 0);
		element.erase(element.size() - 1);

		if (temp)
		{
			cout << endl << "Available results " << endl << endl;
			pt.Display(temp, element);

			foundmenu(current);
		}
		else
		{
			cout << endl << "No results found for  '" << element << "' " << endl << endl;
			notfoundmenu(current);
		}

	}

	void notfoundmenu(node* current)
	{
		int choice;
		cout << "What to do? " << endl;
		cout << "1. Search again " << endl;
		cout << "2. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-2 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 2)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			searchfriendmenu(current);
			break;
		}
		case 2:
		{
			friendtab(current);
			break;
		}
		}
	}

	void foundmenu(node* current)
	{
		int choice;
		cout << "What to do? " << endl;
		cout << "1. Send a friend request " << endl;
		cout << "2. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-2 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 2)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			sendfriendrequest(current);
			Sleep(3000); // 3 seconds
			friendtab(current);
			break;
		}
		case 2:
		{
			friendtab(current);
			break;
		}
		}
	}

	// Message tab
	void messagetab(node* current)
	{
		system("cls");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		cout << " My Friendlist" << endl << endl;
		current->data.flist.frdisplayall();

		int choice;
		cout << "What to do? " << endl;
		cout << "1. Open a friend's chat " << endl;
		cout << "2. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-2 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 2)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			openfriendchat(current);
			break;
		}
		case 2:
		{
			menuafterlogin(current);
			break;
		}
		}
	}

	void openchatmenu(node* current, node* sfriend, fnode* d, fnode* h) // d = friend position in current's flist // h = vice versa of d
	{
		system("cls");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		cout << "Friend's username : " << sfriend->data.username << endl << endl;
		cout << "Chat" << endl << endl;

		d->chat.mdisplayall();

		int choice;
		cout << "What to do? " << endl;
		cout << "1. Send message " << endl;
		cout << "2. Delete chat for yourself " << endl;
		cout << "3. Delete chat for everyone " << endl;
		cout << "4. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-4 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 4)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			d->chat.Insert(current->data.username, sfriend->data.username);
			h->chat.Insertcopy(d->chat.tail);
			openchatmenu(current, sfriend, d, h);
			break;
		}
		case 2:
		{
			d->chat.emptylistm();
			cout << "The chat has been deleted for you. " << endl;
			cout << "Returning to previous menu in 3 seconds. " << endl;
			Sleep(3000); // 3 Seconds
			messagetab(current);
			break;
		}
		case 3:
		{
			d->chat.emptylistm();
			h->chat.emptylistm();
			cout << "The chat has been deleted for everyone. " << endl;
			cout << "Returning to previous menu in 3 seconds. " << endl;
			Sleep(3000); // 3 Seconds
			messagetab(current);
			break;
		}
		case 4:
		{
			messagetab(current);
			break;
		}
		}
	}

	//	Account settings
	void accountsettings(node* current)
	{
		int choice;
		system("cls");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		cout << "Account settings" << endl << endl;

		cout << "1. Change your mobile number " << endl;
		cout << "2. Change your password " << endl;
		cout << "3. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-3 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 3)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			changephonenumber(current);
			Sleep(3000); // 3 Seconds
			accountsettings(current);
			break;
		}
		case 2:
		{
			changepassword(current);
			Sleep(3000); // 3 Seconds
			accountsettings(current);
			break;
		}
		case 3:
		{
			menuafterlogin(current);
			break;
		}
		}
	}

	// Home tab
	void hometab(node* current)
	{
		int choice;
		system("cls");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		cout << "1. Add a new post " << endl;
		cout << "2. View posts " << endl;
		cout << "3. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-3 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 3)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			current->data.plist.Insert(current->data.username);
			Sleep(3000); // 3 Seconds
			hometab(current);
			break;
		}
		case 2:
		{
			viewposthomemenu(current);
			break;
		}
		case 3:
		{
			menuafterlogin(current);
			break;
		}
		}
	}

	void viewposthomemenu(node* current)
	{
		int choice;
		system("cls");
		cout << "       ---  FATEBOOK  ---       " << endl << endl;
		cout << "Username : " << current->data.username << endl << endl;

		cout << "Posts" << endl << endl;
		hometabpostdisplay(current);

		cout << endl;
		cout << "1. Open a post " << endl;
		cout << "2. Go back to previous menu " << endl << endl;
		cout << "Enter your choice from 1-2 : ";
		cin >> choice;

		again:
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Characters not allowed, enter an integer : " << endl;
			cin >> choice;
		}

		while (choice < 1 || choice > 2)
		{
			cout << "Wrong choice, Choose again : " << endl;
			cin >> choice;
			goto again;
		}

		switch (choice)
		{
		case 1:
		{
			openposthometab(current);
			break;
		}
		case 2:
		{
			hometab(current);
			break;
		}
		}
	}
};


int main()
{
	tree a;
	a.mainmenu();



	system("pause");
	return 0;
}