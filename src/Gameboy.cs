class Gameboy
{
    static void Main(string[] args)
    {
        bool running = true;
        Cpu cpu = new Cpu();

        while (running)
        {
            cpu.Fetch();
            cpu.Execute();
        }
    }
}