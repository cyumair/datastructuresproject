#include <iostream>
#include <string.h>
#include <climits>
#include <cmath>
#include <sstream>
using namespace std;

//FA19-BCS-057
//MUHAMMAD UMAIR

//-----------------------------------------------------------------------------------------------
//-----------------------------Data structures to be used---------------------------------------

struct Weapon {
    string name;
    int damage;
    int cost;
    Weapon* next = NULL;
};

struct Bounty{
    string name;
    int reward ;
    int health ;
    string location;
    int distance;
    Bounty* next = NULL;
};



//-----------------------------------------------------------------------------------------------
//--------------------------------------HASH TABLE--------------------------------------------
//-----------------------------------------------------------------------------------------------

class HashTable {
    public:
    int size;
    Weapon** arr;

    HashTable(){
        size = 10;
        arr = new Weapon*[size]{}; //these {} initializes the array with null values
    }

    HashTable(int len){
        size = len;
        arr = new Weapon*[size]{};

    }

    int hashFunction(string name){
        //our key will be the sum of ASCII code values of first two characters of name
        //if name has only one character then ASCII code value of first character will be the key
        
        int key;
        if(name.length() > 1){
            key = (((int)name[0]) + ((int)name[1])) % size;
        }
        else{
            key = (int)name[0];
        }
        return key;
    }

    void insert(string name, int damage, int cost){
        Weapon* weapon = new Weapon;

        weapon->cost = cost;
        weapon->damage = damage;
        weapon->name = name;

        int key = hashFunction(name);
        int i = 0;

        //if the space is empty or if the hastable is full
        // key + i mod size so to move in circle 
        while(arr[(key + i) % size] != NULL && i < size){
            
            i++;
        }

        //if our hash table is full
        if(i == size){
            cout << "Hash Table is Full" << endl;
        }
        else{
            arr[(key + i) % size] = weapon;
        }
    
    }

    void remove(string name) {
        int key = hashFunction(name);
        int i = 0;

        //find the key to be deleted
        while(i < size){

            //if that index is not null then check its name
            //if it is null then it breaks the program as there is no ->name of null pointer
            if(arr[(key + i) % size] != NULL){
                if(arr[(key + i) % size]->name == name){
                    break;
                }
            }
            i++;
        }

        //if not found
        if(i == size){
            cout << "Weapon you want to remove not found" << endl;
        }
        //if found then delete
        else{
            delete arr[(key+i) % size];
            arr[(key+i) % size] = NULL;
        }
    }

    Weapon* getWeapon(string name) {
        int key = hashFunction(name);
        int i = 0;

        //find the key to be deleted
        while(i < size){

            //if that index is not null then match its name
            //if it is null then it breaks the program as there is no ->name of null pointer
            if(arr[(key + i) % size] != NULL){
                if(arr[(key + i) % size]->name == name){
                    break;
                }
            }
            i++;
        }

        //if not found
        if(i == size){
            // cout << "Weapon you want to find not found" << endl;
            return NULL;
        }
        //if found then return
        else{
            return arr[(key + i) % size];
        }
    }

    void display(){
        cout << "Name \t\t\t\t Damage \t\t Cost " << endl; 
        for(int i = 0; i < size; i++){
            if(arr[i] != NULL){
                cout << arr[i]->name << " \t\t\t " << arr[i]->damage << " \t\t\t " << arr[i]->cost << endl;
            }
            else{
                cout << 0 << endl;
            }
        }
    }

};


//------------------------------------------------------------------------------------------
// LINKED LIST OF WEAPONS TO STORE WEAPON DATA //

class WeaponsList {
    public:

    Weapon* first = NULL;
    Weapon* last = NULL;

    //inserts a new weapon at the end of the list
    void addWeapon(string name, int damage, int cost){
    
        Weapon* weapon = new Weapon;
        weapon->damage = damage;
        weapon->name = name;
        weapon->cost = cost;
        
        if(first == NULL){
            first = last = weapon;    
        }
        else{
            last->next = weapon;
            last = weapon;
        }
    }

    //searches for a weapon name and if found, deletes it.
    void removeWeapon(string name){
    
        if(first == NULL){
            cout << "Weapon List is empty No weapons needed to be removed" << endl;
        }
    
        else{
            //delete from start
            if(name == first->name){
                Weapon* temp = first;
                first = first->next;
                delete temp;
            }

            //delete from end
            else if(name == last->name){
                Weapon* current = weaponbeforevalue(name);
                delete current->next;
                current->next = NULL;
                //last = current;

            }

            else{
                Weapon* current = weaponbeforevalue(name);
                if(current == NULL){
                    cout << "Weapon you are looking to delete not found in List." << endl;
                }
                else{
                    Weapon* temp = current->next;
                    current->next = temp->next;
                    delete temp;
                }
                
            }
        }
    }

    //displays the list from start to end
    void display(){

        if(first == NULL){
            cout << "No Weapons" << endl;
        }
        else {

            Weapon* current = first;

            while(current != NULL){
                cout << "Name: " + current->name + ", Damage: " << current->damage << endl;
                current = current->next;
            }
        }
    }

    //returns the weapon if found else returns null
    Weapon* getWeapon(string name) {
        Weapon* current = first;
        while(current != NULL) {
            if(current->name == name) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    //returns the maximum damage that any weapon in the list has...
    int findMaxDamage(){
        if(first == NULL){
            return 0;
        }
        Weapon* current = first;
        int maxdmg = first->damage;
        while(current != NULL){
            if(current->damage > maxdmg){
                maxdmg = current->damage;
            }
            current = current->next;
        }
        return maxdmg;
    }

    //returns the node before the name passed to function, returns null if there is not any
    Weapon* weaponbeforevalue(string name) {
        Weapon* currentnode = first;
        bool found = false;
        while(!(currentnode->next == NULL)){
            if(currentnode->next->name == name){
                found = true;
                break;
            }
            currentnode = currentnode->next;
        }
        if (found){
            return currentnode;
        }
        else{
            return NULL;
        }
    }

};

class AchievedBounties { 
        
    public:
    Bounty* first = NULL;
    Bounty* last = NULL;

    //size
    int size(){
        Bounty* current = first;
        int len = 0;
        while(current != NULL){
            len++;
            current = current->next;
        }
        return len;
    }      
        
    //adds a new bounty at the end of the list
    void addBounty(string name, int reward, int health, string location, int distance){
       
        Bounty* bounty = new Bounty;
        bounty->reward = reward;
        bounty->name = name;
        bounty->health = health;
        bounty->location = location;
        bounty->distance = distance;
        
        //if the list is empty
        if(first == NULL){
            first = last = bounty;    
        }
        //else if not empty insert at end
        else{
            last->next = bounty;
            last = bounty;
        }
    }   

    //displays the from start to end node.       
    void display(){

        if(first == NULL){
            cout << "No Bounties Achieved" << endl;
        }
        else {

            Bounty* current = first;

            while(current != NULL){
                cout << "Name: " + current->name + ", Reward: " << current->reward << ", Location: " << current->location << endl;
                current = current->next;
            }
        }
    }

};

//---------------------------------------------------------------------------------------------
//----------------------------PRIORITY QUEUE FOr TOP PRIORITY BOUNTY FIRST---------------------
//---------------------------------------------------------------------------------------------


class Bounties{
    public:
    int size;
    Bounty** queue;
    int front;
    int last;

    public:
    Bounties(){
        size = 5;
        queue = new Bounty*[size];
        front = -1;
        last = -1;
    }

    Bounties(int len){
        size = len;
        queue = new Bounty*[size];
        front = -1;
        last = -1;
    }
  
    //priority is based to reward to distance ratio
    void priorityEnqueue(string name, int reward, int health, string location, int distance){

        Bounty* bounty = new Bounty;
        bounty->name = name;
        bounty->reward = reward;
        bounty->health = health;
        bounty->location = location;
        bounty->distance = distance;

        if(isFull()){
            cout << "Queue is Full, cannot Insert" << endl;
        }

        else if(isEmpty()){
            front = last = 0;
            queue[last] = bounty;
        }

        else{
            if((double)bounty->reward/bounty->distance < (double)queue[last]->reward/queue[last]->distance){
                last++;
                queue[last] = bounty;
            }

            //Half part of insertion sort algorithm is being used here
            else{
                for(int i = last; i >= front; i--){
                    if((double)bounty->reward/bounty->distance > queue[i]->reward/queue[i]->distance){
                        queue[i+1] = queue[i];
                        queue[i] = bounty                                                                                                                                                                                                                                                                               ;
                    }
                    else{
                        break;
                    }
                }
                last++;
            }
        }
    }

 

    Bounty* dequeue(){

        if(isEmpty()){
            cout << "Queue is Empty, Nothing to Delete" << endl;
            return NULL;
        }

        else{
            Bounty* returnvalue = queue[front];
            if(front == last){
                front = last = -1;
            }
            else{ 
                for(int i = 0; i < size-1; i++){
                    queue[i] = queue[i+1];
                }
                last--; 
            }
            return returnvalue;
        }
    }

    //returns the first element in the queue
    Bounty* first() {
        return queue[front];
    }


    bool isFull(){
        if(front == 0 && last == size - 1){
            return true;
        }
        return false;
    }

    bool isEmpty(){
        if(front == -1 && last == -1){
            return true;
        }
        return false;
    }

    //displays the queue from start to end
    void display(){

        if(isEmpty()){
            cout << "Bounty list is empty" << endl;
        }
        else{
            for(int i = front; i <= last; i++){
                cout << "Name: " << queue[i]->name << ", Reward: " << queue[i]->reward << ", Location: " << queue[i]->location << ", Health: " << queue[i]->health << endl;
            }
        }
    }


};


//-------------------------------------------------------------------------------------
//---------------------------------ARRAY LIST.........................................
//------------------------------------------------------------------------------------

class Planets{
    public:
    string arr[11];
    int size = 11;
    int startindex = -1;
    int endindex = -1;


    public:
    void insertAtEnd(string planet){
        //if there is no space
        if(isFull()){
            cout << "List is full cannot insert more items \n";
        }
        else{
            //if array is empty
            if(isEmpty()){
                arr[0] = planet;
                startindex = 0;
                endindex = 0;
            }
            //if there is space in the end
            else{
                arr[endindex + 1] = planet;
                endindex ++;  
            }

        }
    }

    //returns item at a specific index
    string get(int index){
        return arr[index];
    }

    //displats the array
    void display(){
        if (isEmpty()){
            cout << "list is Empty\n";
        }
        else{
            int currentIndex = startindex;
            while(currentIndex <= endindex){
                cout << arr[currentIndex] << ", "; 
                currentIndex++;
            }
            cout << endl;
        }
    }

    bool isFull(){
       if(startindex == 0 && endindex == size - 1){
            return true;
        }
        return false;
        }

    bool isEmpty(){
        if (startindex == -1){
            return true;
        }
        return false;
    }

    //LINEAR SEARCH
    //searches for an item and returns its index
    int searchLocation(string planetname){
        int currentIndex = startindex;
        int indexofItem = -1;
        while(currentIndex <= endindex){
            if(arr[currentIndex] == planetname){
                indexofItem = currentIndex;
                break;
            }
            currentIndex++;
        }
        return indexofItem;
    }

 
};

//-------------------------------------------------------------------------------------
//-------------------------------DIJKSTRA ALGORITHM------------------------------------
//--------------------------------------------------------------------------------------

void DijkstraAlgorithm(int graph[11][11], int size, int startpoint, int* Distance, string* PathArray) {
    bool checked[size];
    // string path = "0 ";
    Distance[startpoint] = {0};
    checked[startpoint] = true;
    
    for(int i = 1; i < size; i++){
        if(graph[startpoint][i] != -1){
        Distance[i] = graph[startpoint][i];
        }
        else{
            Distance[i] = INT_MAX;
        }
        checked[i] = false; 
        PathArray[i] = "0 " + to_string(i); 
        // path += "0 " + graph[0][i];
    }

    for(int i = 1; i < size; i++){

        int shortestpathindex;
        int shortestpathvalue = INT_MAX;
        for(int j = 1; j < size; j++){
            if(!checked[j] && Distance[j] <= shortestpathvalue){
                shortestpathindex = j;
                shortestpathvalue = Distance[j];   
            }
        }
        checked[shortestpathindex] = true;
        for(int k = 1; k < size; k++){
            if(graph[shortestpathindex][k] != -1){      
                if(Distance[shortestpathindex] + graph[shortestpathindex][k] < Distance[k]){
                    Distance[k] = graph[shortestpathindex][k] + Distance[shortestpathindex];
                    PathArray[k] = PathArray[shortestpathindex] + " " + to_string(k);
                }

            }
        }
  
    }
    
}

//-----------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------

struct Mandalorian{
    int health = 100;
    WeaponsList weaponslist;
    Bounties bounties;
    int distancecovered = 0;
    int credits = 500;
    AchievedBounties achievedBounties;
};

//tells us if the string contains only digits or not
bool isDigits(string text){
    for(int i = 0; i < text.length(); i++){
        if(!(isdigit(text[i]))){
            return false;
        }
    }
    return true;
}

//this method splits a string with some deliminator.
string* split(string expression, char deliminator, int &size) {

    for(int i = 0; i < expression.length(); i++){
        if(expression[i] == deliminator){
            size++;
        }
    }
    size++;
    string* splitString = new string[size];
    // int startindex = 0;

    // int count = 0;
    // while(count < size){
    //     splitString[count] = expression.substr(startindex, expression.find(deliminator, count));
    //     startindex = expression.find(deliminator, count) + 1;
    //     count++;
    // }
 
    stringstream ss (expression);
    string item;
    int index = 0;
    while (getline (ss, item, deliminator)) {
        splitString[index] = item;
        index++;
    }

    return splitString;
}

int main(){

//----------------------------------Making of the graph------------------------------------------------

    Planets planets;
    planets.insertAtEnd("Bounty Hunter's Guild");
    planets.insertAtEnd("Nevarro");
    planets.insertAtEnd("Arvala-7");
    planets.insertAtEnd("Sorgan");
    planets.insertAtEnd("Naboo");
    planets.insertAtEnd("Kashyyk");
    planets.insertAtEnd("Hoth");
    planets.insertAtEnd("Mustafar");
    planets.insertAtEnd("Yavin");
    planets.insertAtEnd("Corellia");
    planets.insertAtEnd("Ryloth");

    // string Planets[] = {"Bounty Hunter's Guild","Nevarro", "Arvala-7", "Sorgan", "Naboo", "Hoth", "Mustafar", "Yavin", "Corellia", "Ryloth", "Kashyyk"};                
  
    int Graph[11][11] = {{-1, 3, 6, 5, -1, -1, -1, -1, -1, -1, -1},
                     {3, -1, 4, -1, -1, -1, -1, -1, -1, -1, -1},
                     {6, 4, -1, -1, -1, 4, -1, -1, -1, -1, -1},
                     {5, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1},
                     {-1, -1, -1, 4, -1, 4, 4, 5, -1, -1, -1},
                     {-1, -1, 4, -1, 4, -1, 3, -1, -1, -1, 6},
                     {-1, -1, -1, -1, 4, 3, -1, 3, 1, 4, 5},
                     {-1, -1, -1, -1, 5, -1, 3, -1, 2, -1, -1},
                     {-1, -1, -1, -1, -1, -1, 1, 2, -1, 1, -1},
                     {-1, -1, -1, -1, -1, -1, 4, -1, 1, -1, 2},
                     {-1, -1, -1, -1, -1, 6, 5, -1, -1, 2, -1}};

    string* PathArray = new string[11];
    int* Distance = new int[11];
    DijkstraAlgorithm(Graph, 11, 0, Distance, PathArray);


    ///// ------------------------Adding the availble weapons on market..........................

    HashTable weapons;
    Mandalorian Mando;
    weapons.insert("Light Saber", 700, 1000);
    weapons.insert("Th Denotator", 150, 100);
    weapons.insert("Blaster Rifle", 170, 200);
    weapons.insert("Electrostaff", 300, 330);
    weapons.insert("Carbine Rifle", 120, 90);
    weapons.insert("Rotator Canon", 320, 350);
    weapons.insert("Bowcaster", 290, 310);
    weapons.insert("Wrist Rockets", 60, 70);
    weapons.insert("Ray Blaster", 100, 80);
    weapons.insert("Bareskar Spear", 400, 400);  
    string choice;

    //---------------------------------Main menu.....................................
    cout << "THE MANDALORIAN" << endl;

    while (true) {

        cout << "\n";
        cout << "1. Go to Store \n";
        cout << "2. Take down bounties\n"; 
        cout << "3. View Our Status \n";
        cout << "4. Exit.\n";
        

        cout << "Your Choice: ";
        getline(cin, choice);

        string input;
        if(choice == "1") {

            while(true) {

                cout << "\n";
                cout << "1. View Available Weapons\n";
                cout << "2. Buy A Weapon\n";
                cout << "3. Sell A Weapon\n";
                cout << "4. Buy Healing \n";
                cout << "5. View our Weapons\n"; 
                cout << "6. Go back\n";
                cout << "Enter your Choice: ";

                getline(cin, input);
                if(input == "1") {
                    weapons.display();
                }

                else if(input == "2") {

                    cout << "Enter name of Weapon you want to buy: ";
                    string name;
                    getline(cin, name);

                    if(Mando.weaponslist.getWeapon(name) == NULL){

                        Weapon* boughtWeapon = weapons.getWeapon(name);
                        if(boughtWeapon != NULL) {

                            if(boughtWeapon->cost <= Mando.credits) {              

                                Mando.weaponslist.addWeapon(boughtWeapon->name, boughtWeapon->damage, boughtWeapon->cost);
                                cout << boughtWeapon->name << ", damage: " << boughtWeapon->damage << " bought for " << boughtWeapon->cost << endl;
                                Mando.credits = Mando.credits - boughtWeapon->cost;
                                cout << "Remaining Credits: " << Mando.credits << endl;
                            }
                            else {
                                cout << "You dont have enough credits to buy this weapon " << endl;
                                cout << "Your Credits: " << Mando.credits << endl;
                            }
                        }

                        else {
                            cout << "This weapon is not available, please check the list to see available weapons\n";
                        }
                    }
                    else{
                        cout << "You already bought this weapon." << endl;
                    }
                }

                else if(input == "3") {

                    cout << "Enter name of weapon you want to sell: ";
                    string name;
                    getline(cin, name);
                    Weapon* sellWeapon = Mando.weaponslist.getWeapon(name);

                    if(sellWeapon != NULL) {
                        Mando.weaponslist.removeWeapon(name);
                        Mando.credits = Mando.credits + sellWeapon->cost / 2;
                        cout << "You have successfully sold the weapon for " << (sellWeapon->cost)/2 << endl;
                        cout << "Your Credits: " << Mando.credits << endl;
                    }

                    else {
                        cout << "You do not have this weapon." << endl;
                    }
                }

                else if(input == "4") {   

                    if(Mando.health == 100){
                        cout << "Your Health is Full" << endl;
                    }
                    else if(Mando.credits < 100 - Mando.health) {
                        Mando.health += Mando.credits;
                        Mando.credits = 0;
                        cout << "Health Increased to " << Mando.health << " according to the credits you had\n";
                    }
                    else{
                        Mando.credits = Mando.credits - (100 - Mando.health);
                        Mando.health = 100; 
                        cout << "Fully Healed to 100.\n";
                        cout << "Remaining Credits: " << Mando.credits << endl;
                    }
                }

                else if(input == "5") {
                    cout << "Our Weapons: " << endl;
                    Mando.weaponslist.display();
                }

                else if(input == "6") {
                    break;
                }

                else {
                    cout << "Invalid Input !" << endl;
                }
            }
            
        }

        else if(choice == "2") {

            while(true) {

                cout << "\n";
                cout << "1. Add Bounty.\n";
                cout << "2. View Bounties\n";
                cout << "3. Hunt for a Bounty\n";
                cout << "4. View Map\n";
                cout << "5. Go Back \n";
                cout << "Enter your Choice: ";

                string inputchoice;

                getline(cin, inputchoice);

                    if(inputchoice == "1"){
                        
                        if(Mando.bounties.isFull()){
                            cout << "Complete Previous ones to add more Bounties." << endl;
                            continue;
                        }

                        string name;
                        string reward;
                        string health;
                        string location;

                        cout << "Enter name of the bounty: ";                
                        getline(cin, name);
                        
                        if(name == ""){
                            cout << "Invalid Name Input." << endl;
                            continue;
                        }

                        cout << "Enter Reward: ";
                        getline(cin, reward);

                        if(!isDigits(reward)){
                            cout << "Reward must contain only digits" << endl;
                            continue;
                        }

                        cout << "Enter Health: ";
                        getline(cin, health);
                        
                        if(!isDigits(health)){
                            cout << "Health can only contain digits" << endl;
                            continue;
                        }

                        cout << "Select Location of the bounty: ";
                        getline(cin, location);
                        
                        if(location == ""){
                            cout << "Invalid Location Input." << endl;
                            continue;
                        }

                        int indexoflocation = planets.searchLocation(location);
                        if(indexoflocation == -1) {
                            cout << "Location not found on map, Please view the locations on map. " << endl;
                            continue;
                        }

                        int healthh = stoi(health);
                        int rewardd = stoi(reward);


                        Mando.bounties.priorityEnqueue(name, rewardd, healthh, location, Distance[indexoflocation]);

                    }

                    else if(inputchoice == "2"){
                        cout << "Bounties: \n";
                        Mando.bounties.display();
                    }

                    else if(inputchoice == "3"){

                        if(Mando.bounties.isEmpty()){
                            cout << "No bounties are there to hunt. " << endl;
                            continue;
                        }
                        
                        if(Mando.bounties.first()->health > Mando.weaponslist.findMaxDamage()){
                            cout << "We do not have enough damage to take this guy down, get more damage !\n";
                            continue;
                        }
                        
                        int healthloss = Mando.bounties.first()->distance*2 + (Mando.bounties.first()->reward/100) * 2;
                        
                        if(Mando.health - healthloss <= 0){
                            cout << "You donot have enough health, heal back from store before going there. \n";
                            continue;
                        }

                        Bounty* huntbounty = Mando.bounties.dequeue(); 

                        Mando.health = Mando.health - healthloss;
                        cout << "Bounty Obtained, " << huntbounty->name << endl;

                        int sizeofarray = 0;
                        string* patharray = split(PathArray[planets.searchLocation(huntbounty->location)], ' ', sizeofarray);
                        cout << "Travelled Path: From ";
                        for(int i = 0; i < sizeofarray; i++){
                            int indexofplanet = stoi(patharray[i]);
                            if(i == sizeofarray - 1){
                                cout << planets.get(indexofplanet) << " ";    
                            }
                            else{
                                cout << planets.get(indexofplanet) << " to ";    
                            }
                        }
                        cout << "and back to Bounty Hunter's Guild" << endl;
                        
                        cout << "Distance Travelled: " << huntbounty->distance * 2 << endl; 

                        Mando.distancecovered = Mando.distancecovered + huntbounty->distance * 2;
                        Mando.credits = Mando.credits + huntbounty->reward;
                        cout << "Credits Rewarded: " << huntbounty->reward << endl;
                        cout << "Health Remaining: " << Mando.health << endl;
                        Mando.achievedBounties.addBounty(huntbounty->name, huntbounty->reward, huntbounty->health, huntbounty->location, huntbounty->distance);

                    }

                    else if(inputchoice == "4"){
                        
                        cout << "PLANETS: " << endl;
                        for(int i = 0; i < planets.size; i++) {
                            cout << "Planet: " << planets.get(i) << ", Distance: " << Distance[i] << endl;
                        }

                    }

                    else if(inputchoice == "5"){
                        break;
                    }

                    else{
                        cout << "Invalid Input" << endl;
                    }
            } 


        }

        else if(choice == "3") {

            cout << "\n";
            cout << "Health Remaining: " << Mando.health << endl;
            cout << "Total Credits: " << Mando.credits << endl;
            cout << "Total Distance Travelled: " << Mando.distancecovered << endl;

            cout << "\nWeapons: " << endl;
            
            Mando.weaponslist.display();
            cout << "\nBounties Achieved: " << Mando.achievedBounties.size() << endl;
            Mando.achievedBounties.display();

        }

        else if(choice == "4") {
            break;
        }

        else {
            cout << "Invalid Choice !" << endl;
        }
        
    }
}
    

