class Memory
{
    byte[] Wram = new byte[8 * 1024];
    byte[] Vram = new byte[8 * 1024];

    public byte ReadWram(UInt16 address)
    {
        return Wram[address];
    }

    public byte ReadVram(UInt16 address)
    {
        return Vram[address];
    }

    public void ReadFile(string filePath)
    {
        FileStream file = File.Open(filePath, FileMode.Open);
        if (file == null)
        {
            throw new FileNotFoundException("Error: File not found! Ensure file path is correct.");
        }
        else if (file.Length > 0x7FFF)
        {
            throw new Exception("Error: ROM file too large.");
        }
        else
        {
            for (int i = 0; i < file.Length; i++)
            {
                Wram[i] = (byte)file.ReadByte();
            }
        }
    }
}