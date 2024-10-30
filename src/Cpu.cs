class Cpu
{
    Register AF;
    Register BC;
    Register DE;
    Register HL;
    ushort PC;
    ushort SP;
    byte opcode;
    Memory mem;
    public Cpu()
    {
        AF = new Register();
        BC = new Register();
        DE = new Register();
        HL = new Register();
        mem = new Memory();
    }
    public void PrintRegisters()
    {
        Console.WriteLine("-- Registers --");
        Console.WriteLine($"AF: {AF.val}\nBC: {BC.val}\nDE: {DE.val}\nHL: {HL.val}");
    }

    public void Fetch()
    {
        opcode = mem.ReadWram(PC);
    }

    public void Execute()
    {
        switch (opcode)
        {
            case 0x00: // NOP
                break;

            default:
                Console.WriteLine("Unhandled or Invalid Opcode");
                break;
        }
    }


}