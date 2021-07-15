#include <iostream>
#include <string>
using namespace std;
class bookCopy //book copy details
{
protected:
    string copyDate;
    string Borrower;
    string borrowDate;
    int returnDate = 15;
    string Flag;


public:
    bookCopy() {};
    bookCopy(string cd, string f, string b, string bdate, int rdate = 15)
    {
        copyDate = cd;
        Flag = f;
        Borrower = b;
        borrowDate = bdate;
        returnDate = rdate;
    }

    friend ostream& operator<<(ostream& out, bookCopy obj)
    {
        out << "Copy Date: " << obj.copyDate << endl;
        out << "availability: " << obj.Flag << endl;
        out << "Borrower Name: " << obj.Borrower << endl;
        out << "Borrow Date: " << obj.borrowDate << endl;
        out << "Return Date: " << obj.returnDate << endl;

        return out;
    }
    //operator overloading to enter bookcopy
    friend istream& operator>>(istream& input, bookCopy& obj)
    {
        cout << "Enter Copy Data Please:__" << endl;
        input >> obj.copyDate;
        cout << "availability (available,notAvailable):__";
        input >> obj.Flag;


        while (!(obj.Flag == "available" || obj.Flag == "notAvaila-ble"))
        {
            cout << "Invalid choice, Enter Again." << endl;
            cout << "availability:__";
            input >> obj.Flag;
        }
        if (obj.Flag == "available") {
            obj.Borrower = "no-name";
            obj.borrowDate = "no-date";
            obj.returnDate = 0;
        }
        else if (obj.Flag == "notAvailable")
        {
            cout << "Enter Borrower Name Please:__" << endl;
            input >> obj.Borrower;
            cout << "Enter Borrow Date Please:__" << endl;
            input >> obj.borrowDate;
            cout << "Enter return days Please:__" << endl;
            input >> obj.returnDate;


        }
        return input;
    }
    friend class Books;
    friend class BookList;
    friend class bookQueue;
};
struct node
{
    string CopyDate;
    string flag;
    string borrower;
    string BorrowDate;
    int noOfDays = 15;
    bookCopy copyy;
    node* Next_Node = NULL;

};

class bookQueue    // Queue functions
{
protected:
    node* first;
    node* last;
    int Size;
public:
    bookQueue()
    {
        first = last = NULL;
        Size = 0;
    }
    bookQueue(node* head, node* tail)
    {
        first = head;
        last = tail;
    }

    node* getHead()
    {
        return first;
    }
    node* getTail()
    {
        return last;
    }


    void push(bookCopy element)
    {
        node* container = new node;
        container->BorrowDate = element.borrowDate;
        container->borrower = element.Borrower;
        container->CopyDate = element.copyDate;
        container->flag = element.Flag;
        container->noOfDays = element.returnDate;
        container->Next_Node = NULL;
        if (first == NULL && last == NULL) //if the Queue is Empty
        {
            first = last = container;
            Size++;
            return;
        }
        last->Next_Node = container; //new link to th next node by put-ting the address of the new node in the second part of the previous node
        last = container;   // make the last node pointer points to the newly created node
        Size++;
    }
    void pop()
    {
        node* container = first;
        if (first == NULL && last == NULL) // in case of empty queue
        {
            cout << "This Queue is Empty !!!";
            return;
        }
        if (first == last) // in case of one element
        {
            first = last = NULL;
        }
        else
        {
            first = first->Next_Node;
        }
        delete container;
        Size--;
    }
    void Display()
    {
        node* container = first;
        if (first == NULL && last == NULL)
        {
            cout << "This Queue is Empty!!!";
            return;
        }
        else
        {
            while (container != NULL)
            {
                cout << "Copy date: " << container->CopyDate << endl
                    << "Availability: " << container->flag << endl
                    << "Borrower name: " << container->borrower << endl
                    << "Borrow date: " << container->BorrowDate << endl
                    << "Number of days: " << container->noOfDays << endl;
                container = container->Next_Node;
            }
        }
    }
    bool isEmpty()
    {
        return Size == 0;
    }
    friend class Books;
    friend class BookList;
    friend class bookCopy;
};


class Books
{
    string BookName;
    int ISBN;
    int noOfCopies;
public:
    Books() {}
    Books(string bn, int isbn, int copies)
    {
        BookName = bn;
        ISBN = isbn;
        noOfCopies = copies;
    }
    friend ostream& operator<<(ostream& out, const Books& obj)
    {
        int i = 1;
        cout << "Name: " << obj.BookName << endl << "ISBN: " << obj.ISBN << endl << "NO of copies: " << obj.noOfCopies << endl;

        cout << "Copy details: " << endl;
        bookQueue* copies = new bookQueue();
        node* current = copies->getHead();
        if (current == NULL)
        {
            cout << "The queue is empty!!" << endl;
        }
        while (current != NULL)
        {
            cout << "copy no_" << i << ": " << endl;
            cout << "Copy date: " << current->CopyDate << endl
                << "Availability: " << current->flag << endl
                << "Borrower name: " << current->borrower << endl
                << "Borrow date: " << current->BorrowDate << endl
                << "Number of days: " << current->noOfDays << endl;
            current = current->Next_Node;
            i++;

        }

        return out;
    }
    //operator overloading to enter book
    friend istream& operator>>(istream& input, Books& obj)
    {
        cout << "Enter Book Name:__";
        input >> obj.BookName;
        cout << "Enter Book ISBN:__";
        input >> obj.ISBN;
        obj.noOfCopies = 0;
        return input;
    }
    friend class BookList;
    friend class bookQueue;

};



struct Node
{
    //Books book;
    string bookName;
    int ISBN;
    int noOfCopies = 0;
    bookQueue* copies = new bookQueue();
    node* firstt = copies->getHead();
    Node* next;
    Node()
    {
        firstt = NULL;
    }
    friend class Books;
};

class BookList
{
protected:
    Node* head = NULL;
    Node* tail = NULL;
    int length;
public:
    BookList()
    {
        length = 0;
    }
    void AddBook(Books b)
    {
        Node* newNode = new Node;
        newNode->bookName = b.BookName;
        newNode->ISBN = b.ISBN;
        newNode->noOfCopies = b.noOfCopies;
        if (length == 0)
        {
            head = tail = newNode;
            newNode->next = NULL;
        }
        else
        {
            tail->next = newNode;
            newNode->next = NULL;
            tail = newNode;
        }
        length++;

    }
    //function to add book
    void addCopyToQue(int bookid, bookCopy newcopy)
    {
        Node* temp = head;
        for (int counter = 0; counter < length; counter++)
        {
            if (temp->ISBN == bookid)
            {
                temp->copies->push(newcopy);
                temp->noOfCopies = temp->copies->Size;
                return;
            }
            else
            {
                temp = temp->next;
            }
        }
        cout << "Error ISBN Dont Match Any BOOK." << endl;
    }
    //function to search about book in list
    bool serach(int bookid)
    {
        Node* temp = head;
        for (int counter = 0; counter < length; counter++)
        {
            if (temp->ISBN == bookid)
            {

                cout << "Book Name Is :" << temp->bookName << endl;
                cout << "Number of copy  is :" << temp->noOfCopies << endl;
                return true;
            }
            else
            {
                temp = temp->next;
            }
        }
        return false;
    }
    //print all book list
    void print()
    {
        Node* curr = head;
        if (curr == NULL)
        {
            cout << "There Is No Book." << endl;
        }
        while (curr != NULL)
        {
            cout << "Book Name: " << curr->bookName << endl << "ISBN: " << curr->ISBN << endl << "Number of copies: " << curr->noOfCopies << endl
                << "Copy details: " << endl;
            if (curr->copies->isEmpty())
            {
                cout << "There Is No Copy" << endl;
            }
            else {

                curr->copies->Display();
            }
            curr = curr->next;

        }

    }
//function to return borrow book
    void deleteBorrow(int inbn, string borrowerName)
    {
        bool found = false;
        Node* temb = head;
        while (temb != NULL)
        {
            if (temb->ISBN == inbn)
            {
                found = true;
                break;
            }
            temb = temb->next;
        }
        if (found == false)
        {
            cout << "There is no Book with This INBN." << endl;
            return;
        }
        else {
            found = false;
            node* copy = temb->copies->getHead();
            while (copy != NULL)
            {
                if (copy->borrower == borrowerName)
                {
                    found = true;
                    copy->flag = "available";
                    copy->borrower = "no_name";
                    copy->BorrowDate = "no-date";
                    copy->noOfDays = 0;
                }
                copy = copy->Next_Node;
            }
            if (found == false)
            {
                cout << "there is no Book with This Borrower Name." << endl;
                return;
            }
        }
    }

    //function to show all book with
    void libraryInventory()
    {
        int copy = 0, borrow = 0;
        Node* temp = head;
        int counter = 1;
        while (temp != NULL)
        {
            node* copies = temp->copies->getHead();
            while (copies != NULL)
            {
                if (copies->flag == "notAvailable")
                {
                    borrow++;
                }
                copy++;
                copies = copies->Next_Node;
            }
            cout << counter << ")";
            cout << "Book Name : " << temp->bookName << endl << "Number Of Copies = " << copy << endl;
            cout << "Number Of Borrower Copies = " << borrow << endl << endl;
            temp = temp->next;
        }
        if (counter == 0)
        {
            cout << "There Is No Book." << endl;
        }
    }

    //function to borrow book
    void updateCopy(string name, int isbn, string date, int noOfDays)
    {
        bool found = 0;
        Node* cur = head;
        node* curr = cur->copies->getHead();
        while (cur != NULL)
        {
            if (cur->ISBN == isbn)
            {
                for (int i = 0; i < cur->noOfCopies; i++)
                {
                    if (curr->flag == "available")
                    {


                        curr->borrower = name;
                        curr->BorrowDate = date;
                        curr->noOfDays = noOfDays;
                        curr->flag = "notAvailable";
                        cout << "Done" << endl;
                        found = 1;
                        break;

                    }
                    curr = curr->Next_Node;
                }
                if (!found)
                {
                    cout << "Not available :-(" << endl;
                }

            }
            cur = cur->next;
        }
    }
};

void print_options()
{
    cout << "1)Show All Book In The library.." << endl;
    cout << "2)Library Inventory." << endl;
    cout << "3)Add book to list." << endl;
    cout << "4)Add book copy." << endl;
    cout << "5)Borrow a book." << endl;
    cout << "6)Return a book." << endl;
    cout << "7)Show borrow statistics." << endl;
    cout << "8)Search about book." << endl << endl;
    cout << "Select an oPtion:" << endl;
}

int main()
{
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "\t\t\tWelcome To  Library management system" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    string option;
    BookList booklist;
    while (true)
    {
        print_options();
        cin >> option;
        if (option == "1")
        {
            booklist.print();
        }
        else if (option == "2")
        {
            booklist.libraryInventory();
        }
        else if (option == "3")
        {
            Books book;
            cin >> book;
            booklist.AddBook(book);
        }
        else if (option == "4")
        {
            int id;
            bookCopy bookcopy;
            cout << "Enter ISBN:__";
            cin >> id;
            cin >> bookcopy;
            booklist.addCopyToQue(id, bookcopy);
        }
        else if (option == "5")
        {
            int id, numday;
            string name, date;
            bookCopy bookcopy;
            cout << "Enter Borrower Name:__";
            cin >> name;
            cout << "Enter ISBN:__";
            cin >> id;
            cout << "Enter The date:__";
            cin >> date;
            cout << "Enter Number Of Dayes:__";
            cin >> numday;
            booklist.updateCopy(name, id, date, numday);
        }
        else if (option == "6")
        {
            int id;
            string name;
            bookCopy bookcopy;
            cout << "Enter Borrower Name:__";
            cin >> name;
            cout << "Enter ISBN:__";
            cin >> id;
            booklist.deleteBorrow(id, name);
        }
        else if (option == "7")
        {
            booklist.libraryInventory();
        }
        else if (option == "8")
        {
            int id;
            cout << "Enter ISBN:__";
            cin >> id;
            if (!booklist.serach(id))
            {
                cout << "Not Found" << endl;
            }
        }
        else
        {
            cout << "Invalid Choice Enter Again." << endl;
        }
        cout << "--------------------------------------------------------------------------" << endl << endl;
    }
}
