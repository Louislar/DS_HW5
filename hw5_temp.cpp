#include<iostream>
#include<fstream>

using namespace std;

class chainNode
{
public:
    chainNode(){}
    chainNode(int e, chainNode* l=0)
    {
        data=e;
        link=l;
    }
    int data;
    chainNode* link;
};


int main()
{
    //file input
    cout<<"Input file name: ";
    ifstream ifs;
    char filename[100];
    for(int i=0;i<100;i++) filename[i]='\0';
    int filenameLength=0;
    {
        char temp;
        while(cin.get(temp))
        {
            if(temp=='\n') break;
            else{
                filename[filenameLength]=temp;
                filenameLength++;
            }
        }
    }
    ifs.open(filename, ios::in);

    chainNode* queue=0;
    int queueLength=0;
    string str1;
    while(ifs>>str1)
    {
        /***************ADD*****************/
        if(str1[0]=='A')
        {
            cout<<"ADD ";
            int addNum;
            ifs>>addNum;

            if(queue==0) queue=new chainNode(addNum, 0);
            else
            {
                chainNode* cur=queue;
                for(;cur->link;cur=cur->link);
                cur->link=new chainNode(addNum, 0);
            }
            queueLength++;
        }

        /****************INSERT****************/
        if(str1[0]=='I')
        {
            int insertNum;
            int insertIndex;
            int outOfRange=0;
            cout<<"Insert ";
            ifs>>insertNum;
            ifs>>str1;
            ifs>>insertIndex;

            if(insertIndex>queueLength||insertIndex<0)
                cout<<"Insert index is out of range!! ";
            else if(insertIndex==0)
            {
                chainNode* temp=queue;
                queue=new chainNode(insertNum, temp);
                queueLength++;
            }
            else if(insertIndex!=0)
            {
                int indexCount=1;
                chainNode* cur=queue;
                for(;indexCount<insertIndex;cur=cur->link, indexCount++);
                chainNode* temp=cur->link;
                cur->link=new chainNode(insertNum, temp);
                queueLength++;
            }

        }

        /***************DELETE*******************/
        if(str1[0]=='D')
        {
            int deleteIndex;
            ifs>>deleteIndex;

            if(deleteIndex<=0||deleteIndex>queueLength)
                cout<<"Insert index is out of range!! ";
            else
            {
                int indexCount=1;
                chainNode* cur=queue;
                chainNode* pre=0;
                for(;indexCount<deleteIndex;cur=cur->link, indexCount++) pre=cur;
                if(pre==0)
                {
                    chainNode* deleteNode=queue;
                    queue=queue->link;
                    delete deleteNode;
                    queueLength--;
                }
                else
                {
                    pre->link=cur->link;
                    delete cur;
                    queueLength--;
                }
            }
        }

        /******************REVERSE*****************/

        if(str1[0]=='R')
        {
            chainNode* last=queue;
            for(;last->link;last=last->link);
            chainNode* pre=0;
            chainNode* cur=queue;
            chainNode* nex=queue->link;
            if(queueLength>1){
                for(;nex;pre=cur, cur=nex, nex=nex->link) cur->link=pre;
                cur->link=pre;
                queue=cur;
            }

        }


        /**************output queue*****************/
        chainNode* out=queue;
        for(;out;out=out->link) cout<<out->data<<" ";
        cout<<endl;
    }




}
