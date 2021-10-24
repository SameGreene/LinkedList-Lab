#pragma once
#include <string>
#include "LinkedListInterface.h"
#include <sstream>
#include <stdexcept>

using namespace  std;

template<typename T>
class LinkedList : public LinkedListInterface<T>{
private:
    struct Node{
        Node(T _val){
            value = _val;
            next = NULL;
        }

        T value;
        Node *next;
    };
    Node *head;

public:
    LinkedList(){
        head = NULL;
    }
    ~LinkedList(){
        clear();
    }
    
    bool dupTest(T val){
		if (head == NULL){
			return false;
		}
		else if (head->value == val){
			return true;
		}
        
		Node *test = head;
		while(test->next != NULL || test->value == val){
			if (test->value == val){
				return true;
			}
			test = test->next;
		}
		return false;
	}
    
    void insertHead(T val){
        if(dupTest(val)){
            return;
        }

        Node *n = new Node(val);
        if(head == NULL){
            head = n;
        }
        else{
            n->next = head;
            head = n;
        }
    }

    void insertTail(T val){
        if(dupTest(val)){
            return;
        }

        if(head == NULL){
            insertHead(val);
            return;
        }

        Node *check = head;
        while(check->next != NULL){
            check = check->next;
        }

        Node *temp = new Node(val);
        check->next = temp;
    }

    void insertAfter(T val, T insNode){
        if(dupTest(val)){
            return;
        }

        if(head == NULL){
            return;
        }

        Node *test = head;
        for(int i = 0; i < size(); i++){
            if(test->value == insNode){
                Node *temp = new Node(val);
                temp->next = test->next;
                test->next = temp;
                return;
            }
            else if(test->next == NULL){
                return;
            }

            test = test->next;
        }
    }

    void remove(T val){
        if(head == NULL){
            return;
        }
        else if(head->value == val){
            Node *temp = head;
            head = temp->next;
            delete temp;
        }
        else{
            Node *test = head;

            while((test->next != NULL) && (test->next->value != val)){
                test = test->next;
            }
            
            if(test->next != NULL){
                Node *temp = test->next;
                test->next = temp->next;
                delete temp;
            }
        }
    }

    void clear(){
        while(head != NULL){
            remove(head->value);
        }
    }

    T at(int index){
        if ((index < 0) || (index >= size())) {
    		throw out_of_range("out of range");
		}
		
        Node *temp = head;
		for (int i = 0; i != index; i++){
			temp = temp->next;
		}
		return temp->value;
    }

    int size(){
		int count = 1;
		Node *temp = head;

		if (head == NULL){
			return 0;
		}
		else if (head->next == NULL){
			return count;
		}

		while (temp->next != NULL){
			count++;
			temp = temp->next;
		}
		return count;
	}

    string toString(){
        string retStr;
        stringstream ss;
        Node *temp = head;
        
        while (temp != NULL){
            if (temp != head){
                ss << " ";
            }
            ss << temp->value;
            temp = temp->next;
        }
        
        retStr = ss.str();
        return retStr;
    }
/*
NOTES:
Semicolon after constructor or destructor?
Check for duplicates
*/
};