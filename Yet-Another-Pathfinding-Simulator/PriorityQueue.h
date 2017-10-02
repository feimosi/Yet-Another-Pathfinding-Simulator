#pragma once
#include <vector>
#include <algorithm>

namespace yaps
{

    template <class T> class PriorityQueue
    {
    public:
        class Node
        {
        public:
            double prior;
            T item;
            Node() {};
            Node(T value, double priority)
            {
                item = value;
                prior = priority;
            }
        };

        std::vector<Node> heap;
        int NextFree;

        PriorityQueue()
        {
            NextFree = 0;
        }

        void add(T it, double prior)
        {
            heap.push_back(Node(it, prior));
            restoreUp(NextFree);
            NextFree++;
        }


        bool isEmpty()
        {
            if (NextFree < 1) return true;
            return false;
        }

        bool contains(T item)
        {
            for (int i = 0; i < NextFree; i++)
            {
                if (heap[i].item == item) return true;
            }
            return false;
        }

        void changePrior(T item, double prior)
        {
            if (remove(item) != Coordinates(-1, -1)) add(item, prior);
        }

        T remove(T rem)
        {
            for (int i = 0; i < NextFree; i++)
            {
                if (heap[i].item == rem)
                {
                    heap[i] = heap[--NextFree];
                    heap.erase(heap.begin() + NextFree);
                    restoreDown(0);
                    return rem;
                }
            }
            return Coordinates(-1, -1);
        }

        T removeHighestPrior()
        {
            if (NextFree == 0) throw std::exception();
            T returnVal = heap[0].item;

            heap[0] = heap[--NextFree];
            heap.erase(heap.begin() + NextFree);
            restoreDown(0);

            return returnVal;
        }



    private:

        void restoreUp(int index)
        {
            int parent = (index - 1) / 2;
            Node zmienna;
            if (heap[parent].prior > heap[index].prior)
            {
                std::swap(heap[parent], heap[index]);

                restoreUp(parent);
            }
        }

        void restoreDown(int index)
        {
            int largest = index;
            int left = index * 2 + 1;
            int right = index * 2 + 2;
            if (left < NextFree && heap[left].prior < heap[largest].prior) largest = left;
            if (right < NextFree && heap[right].prior < heap[largest].prior) largest = right;

            if (largest != index)
            {
                std::swap(heap[index], heap[largest]);
                restoreDown(largest);
            }

        }
    };
}
