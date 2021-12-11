/*
Devin Li
devinl7077@gmail.com
CSCI 235
sorting functions and definition.
bubble sort: move up each value until sorted.
insertion sort: add parts to the start of the list to gradually sort
merge sort: split and sort, then recombine. very efficient. very painful to debug
*/
#include "DoublyLinkedList.hpp"
#include <string>
#include <iostream>
namespace solutions
{
    /* Bubblesort */
    template <typename Comparable, typename Comparator>
    void bubbleSort(DoublyLinkedList<Comparable> &a_list, const Comparator &comp)
    {
      DoubleNode<Comparable> *current;
      DoubleNode<Comparable> *next;
      //how do we track if its sorted? use a counter.
      //If all nodes are lined up, then there should be 5 correct comparisons
      //therefore, we shall use a int counter and increment it when no swaps are made
      int sorted=0;
      while(sorted!=a_list.getSize()-1){
        sorted=0;//resets if there is even one off
        for (int i=1;i<a_list.getSize();i++){
          current=a_list.getAtPos(i);
          next=current->getNext();
          
          if(comp(next->getItem(),current->getItem())){//if next is supposed to be before current
            // std::cout<<"swapping "<<current->getItem()<<" with "<<next->getItem()<<'\n';
            //swap
            a_list.swap(i,i+1);
          }
          else{
            sorted++;
          }
        }
      }
    }

    /* Insertionsort */
    template <typename Comparable, typename Comparator>
    void insertionSort(DoublyLinkedList<Comparable> &a_list, const Comparator &comp)
    {
      //plan
      /*
        int sorted is the amount sorted, starts at 1 (assumed)
        check if item (CURR) at (sorted+1) is less than any elements in sorted
        so:
        int index=sorted 
        while(!CURR<item in sorted){
        index--;
        }
        if(index!=-1){//if index is found
        swap by pushing everything forward
          loop back i from sorted to index;
            element at sorted+1's value= element at sorted's value
            //aka move everything over
          then when loop finishes, set index's value to curr value
          sorted++; after every insertion

        }
        repeat for all elements 
      */
      int sorted=1;
      DoubleNode<Comparable> *curr;
      for(int i=2;i<=a_list.getSize();i++){//check all values after sorted
        curr=a_list.getAtPos(i);//this will the adjacent index of sorted.
        //check if curr is already larger
        if(comp(curr->getPrevious()->getItem(),curr->getItem())){
          // std::cout<<"comparing rn: "<<curr->getItem()<<" and "<<curr->getPrevious()->getItem()<<std::endl;
          //if its sorted, then just increase the sorted domain.
        }
        else{//if not sorted, slap it into the thing
          int index=0;

          DoubleNode<Comparable> *compare=a_list.getAtPos(1);

          // std::cout<<"comparing "<<curr->getItem()<<" AND "<<compare->getItem()<<"\n";
          //keep going until curr is less or equal to compare
          //if comp is ascending, comp(a,b) only true if a<b
          while(comp(compare->getItem(),curr->getItem())&&index<sorted){
            compare=compare->getNext();
            index++;
          }
          Comparable hold=curr->getItem();
          compare=curr;
          for(index;index<sorted;index++){
            compare->setItem(compare->getPrevious()->getItem());//copy prev value to here
            compare=compare->getPrevious();//go back
          }
          compare->setItem(hold);
          //get the first index that is smaller than curr
          
        }
          sorted++;
      }
        
        // std::cout<<"head: "<<a_list.getAtPos(sorted-1)->getItem()<<std::endl;

    }

    /* Merge */
    template <typename Comparable, typename Comparator>
    void merge(DoublyLinkedList<Comparable> &a_list, int left_index, int middle_index, int right_index, const Comparator &comp)
    {
      DoublyLinkedList <Comparable> *tempList=new DoublyLinkedList<Comparable>(a_list);
      //index
      // std::cout<<"merging using list: \n";
      
      // std::cout<<"tempList size: "<<tempList->getSize()<<"\n";
      // a_list.display();
      int start1=left_index;
      int end1=middle_index;
      int start2=middle_index+1;
      int end2=right_index;

      //while not empty, copy small list to tempList
      int index=start1;
      while((start1<=end1)&&(start2<=end2)){
        //comparison of lists. pushing the smaller element
        if(comp (a_list.getAtPos(start1)->getItem() , a_list.getAtPos(start2)->getItem())){
          // std::cout<<"start1 is: "<<start1<<"\tadding s1a: "<<a_list.getAtPos(start1)->getItem()<<" to index "<<index<<"\n";
          
          tempList->getAtPos(index)->setItem(a_list.getAtPos(start1)->getItem());
          // std::cout<<"displaying templist:";
        // tempList->display();
      // std::cout<<"------------------\n";
          start1++;
        }
        else{
          // std::cout<<"start2 is: "<<start2<<"\tadding s2a: "<<a_list.getAtPos(start2)->getItem()<<" to index "<<index<<"\n";
          tempList->getAtPos(index)->setItem(a_list.getAtPos(start2)->getItem());
          // std::cout<<"displaying templist:";
          // tempList->display();
          // std::cout<<"------------------\n";
          start2++;
          
        }
        // std::cout<<"index: "<<index<<"\n";
        index++;
        
      }
      // std::cout<<"comparison done \n"<<start1<<"  "<<start2<<"\n";
      //leftover for first a
      // std::cout<<"tempList size: "<<tempList->getSize()<<"\n";
      while(start1<=end1){
        // std::cout<<"start1 is: "<<start1<<"\tadding s1b: "<<a_list.getAtPos(start1)->getItem()<<" to index "<<index<<"\n";
        tempList->getAtPos(index)->setItem(a_list.getAtPos(start1)->getItem());
        start1++;
        index++;
        // std::cout<<"index: "<<index<<"\n";
        // std::cout<<"displaying templist:";
        // tempList->display();
        // std::cout<<"------------------\n";
      }
      //leftover for second array
      while(start2<=end2){
        // std::cout<<"start2 is: "<<start2<<"\tadding s2b: "<<a_list.getAtPos(start2)->getItem()<<"to index"<<index<<"\n";
        tempList->getAtPos(index)->setItem(a_list.getAtPos(start2)->getItem());
        start2++;
        index++;
        // std::cout<<"index: "<<index<<"\n";
        // std::cout<<"displaying templist:";
        // tempList->display();
        // std::cout<<"------------------\n";
      }
      
      // copy to a_list

      for(index=left_index;index<=right_index;index++){
        a_list.getAtPos(index)->setItem(tempList->getAtPos(index)->getItem());
      }
      // std::cout<<"----------------DONE------------------\n";
    }



    /* Mergesort */
    template <typename Comparable, typename Comparator>
    void mergeSort(DoublyLinkedList<Comparable> &a_list, int left_index, int right_index, const Comparator &comp)
    {
      if(left_index<right_index){
        int mid=(right_index+ left_index)/2;
        // std::cout<<"mergeSort1: "<<left_index<<", "<<mid<<"\n";
        mergeSort(a_list,left_index,mid,comp);
        // std::cout<<"mergeSort2: "<<mid+1<<", "<<right_index<<"\n";
        mergeSort(a_list,mid+1,right_index,comp);
        // std::cout<<"merge: "<<left_index<<", "<<mid<<", "<<right_index<<"\n";
        merge(a_list,left_index,mid,right_index,comp);
  
      }

    }

    /* Mergesort Wrapper */
	//this is what you use to test
    template <typename Comparable, typename Comparator>
    void mergeSort(DoublyLinkedList<Comparable> &a_list, const Comparator &comp)
    {
		  mergeSort(a_list, 1, a_list.getSize(),comp);
    }

}; // namespace solutions