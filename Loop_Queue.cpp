


class Loop_Queue
{
    public:
        Loop_Queue( int sz = 100 ) : MaxSize(sz) {

            vec.resize(MaxSize);

        }

        void EnQueue( int val )
        {

            if( size >= MaxSize )
            {
                cout << "the Queue is full";
                return;
            }

            top = (top+1) % MaxSize;
            vec[top] = val;
            size++;

        }

        int DeQueue()
        {

            if( top == -1 )
            {
                cout << "the Queue is Empty";
                return INT_MAX;
            }

            int tmp = vec[top];

            top = ( top-1 ) % MaxSize;
            size--;
            return tmp;

        } 

    private:
        int MaxSize = 100;  // 最大个数
        int size = 0;
        int top = -1;
        vector<int> vec;

} ;

 