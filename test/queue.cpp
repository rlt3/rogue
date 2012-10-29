#include <iostream>
#include <queue>

#define QUEUE_MAX 10

class Queue
{
   public:
      Queue();
      int next();
      void push(int item);
      bool isEmpty();
      int front;
      int back;
      int size;
      int items[QUEUE_MAX];
   private:
};

Queue::Queue()
{
   this->front=0;
   this->size=0;
}

int Queue::next()
{
   int item = this->items[this->front];
   this->front = ++this->front%this->size;
   return item;
}

void Queue::push(int item)
{
   this->items[this->size++] = item;
}

bool Queue::isEmpty()
{
   return (this->size==0);
}

int main()
{
   Queue items;

   items.push(1);
   items.push(2);
   items.push(3);
   items.push(4);

   for(int i=0; i<=10; i++)
      std::cout << items.next() << std::endl;

   items.push(5);
   items.push(6);

   for(int i=0; i<=10; i++)
      std::cout << items.next() << std::endl;
      
   std::cout << "Front: " << items.front << std::endl;
   std::cout << "Back: " << items.back << std::endl;
   std::cout << "Size: " << items.size << std::endl;

   return 0;
}
