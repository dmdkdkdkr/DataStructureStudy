using DataStructure_CSharp;

internal class Program
{
    static void Main()
    {
        Stack stack = new Stack();
        stack.Push(new CollectionData() { data = 1 });
        stack.Push(new CollectionData() { data = 2 });
        stack.Push(new CollectionData() { data = 3 });
        stack.Push(new CollectionData() { data = 4 });
        stack.Display();

        var popped = stack.Pop();
        Console.WriteLine($"Popped Node => data: {popped?.data.data ?? null}");
        stack.Pop();
        stack.Display();

        stack.Clear();
        stack.Display();

        var data = stack.Peek();
        Console.WriteLine($"Peek data => data: {data?.data ?? null}");
        stack.Push(new CollectionData() { data = 1557 });
        stack.Push(new CollectionData() { data = 1558 });
        data = stack.Peek();
        Console.WriteLine($"Peek data => data: {data?.data ?? null}");
        Console.WriteLine($"Stack count: {stack.Count()}");
        stack.Display();
    }
}
