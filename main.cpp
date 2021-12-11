#include "Solutions.cpp"
int main(){
    DoublyLinkedList <int> a;
    // a.insert(1);
    // a.insert(10);
    // a.insert(8);
    // a.insert(152);
    // a.insert(63);
    // a.insert(74);
    // a.insert(38);
    // a.insert(13);
    // a.insert(19);
    // a.insert(72);
    // a.insert(12);
    // a.insert(65);
    a.insert(26);
    a.insert(80);
    a.insert(44);
    a.insert(51);
    a.display();
    std::cout<<"size: "<<a.getSize()<<'\n';
    solutions::mergeSort(a,std::greater<int>{});
    a.display();
    
}