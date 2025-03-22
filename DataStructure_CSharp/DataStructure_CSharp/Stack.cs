using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataStructure_CSharp
{
    internal struct CollectionData
    {
        public int data;
    }

    internal class StackNode
    {
        public CollectionData data;
        public StackNode? next = null;

        public StackNode(CollectionData data)
        {
            this.data = data;
            this.next = null;
        }
    }

    internal class Stack
    {
        private int count = 0;
        private StackNode? TopNode = null;

        public bool Push(CollectionData data)
        {
            var newNode = new StackNode(data);
            if (TopNode != null) newNode.next = TopNode;
            TopNode = newNode;
            count++;

            return false;
        }

        public StackNode? Pop()
        {
            if (IsEmpty())
            {
                Console.WriteLine("Stack is empty");
                return null;
            }

            var popped = TopNode;
            TopNode = TopNode?.next ?? null;
            count--;

            return popped;
        }

        public CollectionData? Peek()
        {
            if (IsEmpty())
            {
                Console.WriteLine("Stack is empty");
                return null;
            }

            var data = TopNode?.data ?? null;
            return data;
        }

        public bool Clear()
        {
            if (IsEmpty())
            {
                Console.WriteLine("Stack is empty");
                return true;
            }

            count = 0;
            TopNode = null;
            GC.Collect();

            return true;
        }

        public int Count()
        {
            return count;
        }

        public void Display()
        {
            Console.WriteLine($"Display stack => Count: {count}");

            var node = TopNode;
            int height = count;
            while (node != null)
            {
                Console.WriteLine($"Height: {height} => Data: {node.data.data}");
                node = node.next;
                height--;
            }

            Console.WriteLine("End Display stack\n");
        }

        public bool IsEmpty() => (count == 0);
    }
}
