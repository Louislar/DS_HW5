#include<iostream>
#include<fstream>
#include<string>
#include<cstring>

using namespace std;

class chainNode
{
public:
    chainNode()
    {
        data=0;
        link=0;
    }
    chainNode(int a=0, chainNode* b=0)
    {
        data=a;
        link=b;
    }
    int data;
    chainNode* link;
};

class linkedList
{
public:
    linkedList()
    {
        listLength=0;
        first=0;
        last=0;
    }
    chainNode* first;
    chainNode* last;
    int listLength;
    void add(int element)
    {
        if(isEmpty())
        {
            chainNode* temp=new chainNode(element, 0);
            first=temp;
            last=temp;
        }
        else
        {
            chainNode* temp=new chainNode(element, 0);
            last->link=temp;
            last=temp;
        }
        listLength++;
    }
    void insert(int element, int index)
    {
        if(index>listLength)
        {
            cout<<"Insert index is out of range!!"<<endl;
        }
        else if(index==0)
        {
            chainNode* temp=new chainNode(element, first);
            first=temp;
            listLength++;
        }
        else
        {
            chainNode* current=first;
            for(int i=1;i<index;i++)
            {
                current=current->link;
            }
            chainNode* temp=new chainNode(element, current->link);
            if(current==last) last=temp;
            current->link=temp;
            listLength++;
        }
    }
    void deleted(int index)
    {
        if(index>listLength||index<=0)
        {
            cout<<"Insert index is out of range!!"<<endl;
        }
        else
        {
            chainNode* current=first;
            chainNode* pre;
            for(int i=1;i<index;i++)
            {
                pre=current;
                current=current->link;
            }

            /*cout<<"DELETE current data: "<<current->data<<endl;
            cout<<"DELETE pre data: "<<pre->data<<endl;*/

            if(current==first)
            {
                first=first->link;
                delete current;
            }
            else if(current==last)
            {
                last=pre;
                last->link=0;
                delete current;
            }
            else
            {
                pre->link=current->link;
                delete current;
            }
            listLength--;
        }//else end
    }
    void reverse()
    {
        chainNode* pre=0;
        chainNode* cur=first;
        chainNode* next=first->link;
        while(cur!=0)
        {
            cur->link=pre;
            pre=cur;
            cur=next;
            if(next==0) break;
            next=next->link;
        }
        chainNode* temp=first;
        first=last;
        last=temp;
    }
    int isEmpty()
    {
        if(first==0) return 1;
        return 0;
    }
    void print()
    {
        chainNode* cur=first;
        while(cur!=0)
        {
            cout<<cur->data<<" ";
            cur=cur->link;
        }
        cout<<"\n\n";
    }
};

int main()
{
    //file input
    cout<<"Input file name: ";
    string str;
    cin>>str;
    char* cstr = new char [str.length()+1];
    strcpy(cstr, str.c_str());
    ifstream ifs;
    ifs.open(cstr, ios::in);


    linkedList list=linkedList();
    while(1)
    {
        string instruction;
        ifs>>instruction;
        string a;
        a[0]=EOF;
        if(instruction.compare(a)==0) break;

        //ADD
        if(instruction[0]=='A')
        {
            int num;
            ifs>>num;
            list.add(num);

        }

        //INSERT
        if(instruction[0]=='I')
        {
            int num;
            int index;
            string tempstr;
            ifs>>num>>tempstr>>index;
            list.insert(num, index);
        }

        //DELETE
        if(instruction[0]=='D')
        {
            int index;
            ifs>>index;
            list.deleted(index);
        }

        //REVERSE
        if(instruction[0]=='R')
        {
            list.reverse();
        }
        /*cout<<"First point to data: "<<list.first->data<<endl;
        cout<<"Last point to data: "<<list.last->data<<endl;
        cout<<"List Length: "<<list.listLength<<endl;*/
        list.print();

    }
}
