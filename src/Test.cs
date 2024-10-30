class Test
{
    static void Main(string[] args)
    {
        Console.WriteLine("--Register Tests--");

        Cpu cpu = new Cpu();
        cpu.AF.val = 0x1234;
        cpu.BC.val = 0x5678;
        cpu.DE.val = 0x90AB;
        cpu.HL.val = 0xCDEF;
        cpu.PrintRegisters();
    }
}