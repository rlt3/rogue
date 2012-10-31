#define QUEUE_MAX 10

template <class Type>
class Queue
{
   public:
      Queue();
      Type next();
      void push(Type item);
      bool isEmpty();
   private:
      int front;
      int size;
      Type items[QUEUE_MAX];
};

template <class Type>
Queue<Type>::Queue()
{
   this->front=0;
   this->size=0;
}

template <class Type>
Type Queue<Type>::next()
{
   Type item = this->items[this->front];
   this->front = ++this->front%this->size;
   return item;
}

template <class Type>
void Queue<Type>::push(Type item)
{
   this->items[this->size++] = item;
}

template <class Type>
bool Queue<Type>::isEmpty()
{
   return (this->size==0);
}
