#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h> 


using namespace std; 

string hexCharToBin(char c) {
    switch (c) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'a': return "1010";
        case 'B': return "1011";
        case 'b': return "1011";
        case 'C': return "1100";
        case 'c': return "1100";
        case 'D': return "1101";
        case 'd': return "1101";
        case 'E': return "1110";
        case 'e': return "1110";
        case 'F': return "1111";
        case 'f': return "1111";
    }
    return "";
}

string hexToBin(const string& hexStr) {
    string binStr;
    if(hexStr.size()!=8){
        for (int i = 0; i < 8 - hexStr.size();i++){
            binStr += "0000";
        }
    }
    for (char c : hexStr) {
        binStr += hexCharToBin(c);
    }
    return binStr;
}

pair<long long int,long long int> extract_bits(string n,int offset,int index){
    string bin=hexToBin(n);
    string ind="";
    string tag="";
    for (int i = 32-(offset + index); i < 32-offset; i++){
        ind.push_back(bin[i]);
    }
    for (int i = 0; i < 32-(offset + index); i++){
        tag.push_back(bin[i]);
    }
    long long int r2;
    if(ind==""){
        r2=0;
    }
    else{
        r2=stol(ind, 0, 2);
    }
    return make_pair(stol(tag, 0, 2),r2);
}

long long int HexToDec(string n) { return stol(n, 0, 16); } 

class node{
    public:
    int key=-1;
    int val=-1;
    node* next=nullptr;
    node* prev=nullptr;
};

class LRUCache {
public:
    int capacity;
    int size;
    unordered_map<int,node*> m;
    node* head = new node();
    node* tail = new node();

    LRUCache(int c) {
        capacity=c;
        size=0; 
        tail->prev=head;
        head->next=tail;
    }
    ~LRUCache() {
        node* current = head->next;
        while (current != tail) {
            node* temp = current;
            current = current->next;
            delete temp;
        }
        delete head;
        delete tail;
    }
    
    int get(int key) {
        auto it = m.find(key);
        if (it == m.end()) {
            return -1; 
        } 
        else{ 
            return it->second->val;
            // node* temp=m[key];
            // node* newnode = new node();
            // newnode->key=key;
            // newnode->val=temp->val;
            // temp->next->prev=temp->prev;
            // temp->prev->next=temp->next;
            // delete temp;

            // head->next->prev=newnode;
            // newnode->next=head->next;
            // head->next=newnode;
            // newnode->prev=head;
            // m[key]=newnode;
            // return newnode->val;
        }      
    }
    
    bool put(int key, int value , int& write_backs){
        bool ret=0;
        //ret is 1 if there is a miss and 0 for a hit
        auto it = m.find(key);
        if(it == m.end()){
            ret=1;
            // value=0;
            // so this is a miss and this key was not already present
            if(size<capacity){
                // we just add to the head of the list the new key
                node* newnode = new node();
                newnode->key=key;
                newnode->val=value;
                head->next->prev=newnode;
                newnode->next=head->next;
                head->next=newnode;
                newnode->prev=head;
                m[key]=newnode;
                size++;
            }
            else{
                // we first evict one and check for the dirty bit 
                if(tail->prev->val==1){
                    write_backs++;
                }
                m.erase(tail->prev->key);
                node* temp=tail->prev;
                tail->prev=temp->prev;
                tail->prev->next=tail;
                delete temp;
                // then we add the new key 
                node* newnode = new node();
                newnode->key=key;
                newnode->val=value;
                head->next->prev=newnode;
                newnode->next=head->next;
                head->next=newnode;
                newnode->prev=head;
                m[key]=newnode;
            }
        }
        else{
            // since the key was already present we first remove it from its original loacation and update its priority for the lru
            node* temp=m[key];
            int prev_val=temp->val;
            temp->next->prev=temp->prev;
            temp->prev->next=temp->next;
            delete temp;
            node* newnode = new node();
            newnode->key=key;
            // this step is if there is the dirty bit was already 1 then we don not change it
            if(prev_val==1){
                newnode->val=1;
            }
            else{
                newnode->val=value;
            }
            head->next->prev=newnode;
            newnode->next=head->next;
            head->next=newnode;
            newnode->prev=head;
            m[key]=newnode;
        }
        return ret;
    }
};

class FIFOCache {
public:
    int capacity;
    int size;
    unordered_map<int,int> m;
    queue<int> q;

    FIFOCache(int c) {
        capacity=c;
        size=0; 
    }
    ~FIFOCache() {
    }
    
    int check(int key) {
        auto it = m.find(key);
        if (it == m.end()) {
            return -1; 
        } 
        else{
            return it->second;
        }
    }
    
    bool put(int key,int val,int& write_backs){
        bool ret=0;
        int c= check(key);
        // same ret here 1 if there is a miss and 0 for a hit 
        if(c==-1){
            ret=1;
            if(size<capacity){
                q.push(key);
                m[key]=val;
                size++;
            }
            else{
                // before evictting check for the dirty bit 
                int temp=q.front();
                q.pop();
                if(m[temp]==1){
                    write_backs++;
                }
                m.erase(temp);
                m[key]=val;
                q.push(key);
            }
        }
        else{
            // it the dirty bit is 0 change it to the current value else it remains 1 
            if(m[key]==0){
                m[key]=val;
            }  
        }
        return ret;
    }
};


int main(int argc, char *argv[]){
if (argc != 7) {
        std::cerr << "Usage: " << argv[0] << " <cache_size> <block_size> <num_sets> <write_policy> <eviction_policy> <trace_file>" << std::endl;
        return 1;
    }
    int sets = std::stoi(argv[1]);
    int blocks = std::stoi(argv[2]);
    int blocksize = std::stoi(argv[3]);
    std::string write_policy = argv[4];
    std::string write_method = argv[5];
    std::string eviction_policy = argv[6];

    int stores=0;
    int loads=0;
    // int sets=1;
    // int blocks=8;
    // int blocksize=4;
    bool lru=false;
    bool write_allocate=false;
    bool write_through=false;
    int offset=std::log2(blocksize);
    int index=std::log2(sets);
    if(write_policy=="write-allocate"){
        write_allocate=true;
    }
    if(write_method=="write-through"){
        write_through=true;
    }
    if(eviction_policy=="lru"){
        lru=true;
    }

    // file reading

    ofstream outputFile("output.txt");

    string myText;
    ifstream MyReadFile("gcc.txt");
    vector<pair<char,pair<long long int , long long int>>> v;
    while (getline (cin, myText)) {
        string hex_="";
        for (int i = 4; i <12; i++)
        {   
            if(myText[i]==' '){ break;}
            hex_.push_back(myText[i]);
        }
        pair<long long int , long long int> temp= extract_bits(hex_,offset,index);
        
    v.push_back(make_pair(myText[0],temp));
    }
    MyReadFile.close(); 

    // for (const auto& pair : v) {
    //     cout << "Character: " << pair.first << ", tag: " << pair.second.first << ", index: "<<pair.second.second<<endl;
    // }

    // //parameters
    
    // int stores=0;
    // int loads=0;
    // int sets=1;
    // int blocks=8;
    // int blocksize=4;
    // bool lru=true;
    // bool write_allocate=true;
    // bool write_through=false;
    // int offset=std::log2(blocksize);
    // int index=std::log2(sets);



    // // file reading

    // ofstream outputFile("output.txt");

    // string myText;
    // ifstream MyReadFile("testgen.txt");
    // vector<pair<char,pair<long long int , long long int>>> v;
    // while (getline (MyReadFile, myText)) {
    //     string hex_="";
    //     for (int i = 4; i <12; i++)
    //     {   
    //         if(myText[i]==' '){ break;}
    //         hex_.push_back(myText[i]);
    //     }
    //     pair<long long int , long long int> temp= extract_bits(hex_,offset,index);
        
    // v.push_back(make_pair(myText[0],temp));
    // }
    // MyReadFile.close(); 

    // for (const auto& pair : v) {
    //     cout << "Character: " << pair.first << ", tag: " << pair.second.first << ", index: "<<pair.second.second<<endl;
    // }

    
    int load_hits(0),load_miss(0),store_hits(0),store_miss(0),write_backs(0);
    int count = 0;

    if(lru){
        vector<LRUCache*> cacheSets;
        for (int i = 0; i < sets; i++){
            LRUCache* cache=new LRUCache(blocks);
            cacheSets.push_back(cache);
        }
        for (const auto& pair : v) {
            count ++;
            // cout<<count<<endl;
            // outputFile<<count<<"  ";
            // outputFile << "Character: " << pair.first << ", tag: " << pair.second.first << ", index: "<<pair.second.second;

            if(pair.first=='l'){ 
                // for a load in lru we just put it with dirty bit 0 and check for a hit or a miss 
                bool m=cacheSets[pair.second.second]->put(pair.second.first,0,write_backs);
                if(m){
                    load_miss++;
                    // outputFile<<"  load miss"<<endl;
                }
                else{
                    load_hits++;
                    // outputFile<<"  load hit"<<endl;
                }
                loads++;
            } 

            else{
                if(write_allocate){
                    // for a store if write allocate is on the same procedure as that for load but the dirty bit is 1 now
                    bool m=cacheSets[pair.second.second]->put(pair.second.first,1,write_backs);
                    if(m){
                        store_miss++;
                        // outputFile<<"  store miss"<<endl;
                    }
                    else{
                        // outputFile<<"  store hit"<<endl;
                        store_hits++;
                    }
                }
                else{
                    // if no write allocate we just check if the tag was present or not and do not put it 
                    int m=cacheSets[pair.second.second]->get(pair.second.first);
                    if(m==-1){
                        store_miss++;
                        // outputFile<<"  store miss"<<endl;
                    }
                    else{
                        // but if it is a hit then we need to update the priority of the key
                        bool m=cacheSets[pair.second.second]->put(pair.second.first,1,write_backs);
                        store_hits++;
                        // outputFile<<"  store hit"<<endl;
                    }
                }
                stores++;
            }
            // for (int i = 0; i < sets; i++) {
            //     outputFile << "Cache Set " << i << ":" << endl;
            //     node* current = cacheSets[i]->head->next;
            //     while (current != cacheSets[i]->tail) {
            //         outputFile << "Key: " << current->key <<"  Value: "<<current->val<< endl;
            //         current = current->next;
            //     }
            //     outputFile << endl;
            // }
        } 
        // cout <<endl<<"lakdfjaslkafl"<<endl;
        for (int i = 0; i < sets; ++i) {
            delete cacheSets[i];
        }
    }

    else{
        vector<FIFOCache*> cacheSets;
        for (int i = 0; i < sets; i++){
            FIFOCache* cache=new FIFOCache(blocks);
            cacheSets.push_back(cache);
        }

        for (const auto& pair : v) {
            count ++;
            // outputFile<<count<<"  ";
            // cout << "Character: " << pair.first << ", Integer: " << pair.second << endl;
            // cout<<pair.second<<"   "<<pair.second%sets<<endl;

            // outputFile << "Character: " << pair.first << ", tag: " << pair.second.first << ", index: "<<pair.second.second;
            if(pair.first=='l'){
                // same here for a load just put with dirty bit 0 and check hit miss 
                bool m=cacheSets[pair.second.second]->put(pair.second.first,0,write_backs);
                if(m){
                    load_miss++;
                    // outputFile<<"  load miss"<<endl;
                }
                else{
                    load_hits++;
                    // outputFile<<"  load hit"<<endl;
                }
                loads++;
            } 
            else{
                if(write_allocate){
                    // just acts as a load if write allocate is true 
                    bool m=cacheSets[pair.second.second]->put(pair.second.first,1,write_backs);
                    if(m){
                        store_miss++;
                        // outputFile<<"  store miss"<<endl;
                    }
                    else{
                        // outputFile<<"  store hit"<<endl;
                        store_hits++;
                    }
                }
                else{
                    int m=cacheSets[pair.second.second]->check(pair.second.first);
                    if(m==-1){
                        store_miss++;
                        // outputFile<<"  store miss"<<endl;
                    }
                    else{
                        // no priority problem here if there is a miss or a hit doesn;t matter we need not do anything else 
                        store_hits++;
                        // outputFile<<"  store hit"<<endl;
                    }
                }
                stores++;
            }
            // for (int i = 0; i < sets; i++) {
            //     outputFile << "Cache Set " << i << ":" << endl;
            //     node* current = cacheSets[i]->head->next;
            //     while (current != cacheSets[i]->tail) {
            //         outputFile << "Key: " << current->key << endl;
            //         current = current->next;
            //     }
            //     outputFile << endl;
            // }
            // outputFile<<"  write_backs: "<<write_backs<<endl; 
        } 
        for (int i = 0; i < sets; ++i) {
            delete cacheSets[i];
        }
    }


    int mem_time=100*(blocksize/4);
    int load_hit_time,load_miss_time,store_hit_time,store_miss_time;
    load_hit_time=1;
    load_miss_time=mem_time+1;
    if(write_allocate && write_through){
        store_miss_time=mem_time+100;
        store_hit_time=100+1;
        write_backs=0;
    }
    else if(write_allocate && !write_through){
        store_miss_time=mem_time+1;
        store_hit_time=1;
    }
    else if(!write_allocate && write_through){
        store_miss_time=100;
        store_hit_time=100+1;
        write_backs=0;
    }
    else{
        store_miss_time=100;
        store_hit_time=1;
    }
    int cycles=load_hit_time*load_hits + load_miss*load_miss_time + store_hit_time*store_hits + store_miss*store_miss_time + write_backs*mem_time;
    
    outputFile<<"NUMBER of loads are: "<<loads<<endl;
    outputFile<<"NUMBER of stores are: "<<stores<<endl;
    outputFile<<"NUMBER of load hits are: "<<load_hits<<endl;
    outputFile<<"NUMBER of load miss are: "<<load_miss<<endl;
    outputFile<<"NUMBER of store hits are: "<<store_hits<<endl;
    outputFile<<"NUMBER of store miss are: "<<store_miss<<endl;
    outputFile<<"NUMBER of cycles used are: "<<cycles<<endl;

    cout<<"NUMBER of loads are: "<<loads<<endl;
    cout<<"NUMBER of stores are: "<<stores<<endl;
    cout<<"NUMBER of load hits are: "<<load_hits<<endl;
    cout<<"NUMBER of load miss are: "<<load_miss<<endl;
    cout<<"NUMBER of store hits are: "<<store_hits<<endl;
    cout<<"NUMBER of store miss are: "<<store_miss<<endl;
    cout<<"NUMBER of cycles used are: "<<cycles<<endl;
    cout<<"NUMBER of write_backs are: "<<write_backs<<endl;

}

