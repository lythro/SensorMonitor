class CRC8Calc {
private:
	char table[256];
public:
	char checksum(char* values, int size) const
	{
		char c = 0;
		for (int i = 0; i < size; i++)
		{
			c = table[c^values[i]];
		}

		return c;
	}


	enum CRC8_POLY
	{
		CRC8 = 0xd5,
		CRC_CCITT = 0x07,
		CRC_DALLAS_MAXIM = 0x32,
		SMBUS = 0b00000111
	};

	void setPolynomial(CRC8_POLY poly)
	{
		for (int i = 0; i < 256; i++)
		{
			int curr = i;
			for (int j = 0; j < 8; j++)
			{
				if ((curr & 0x80) != 0)
				{
					curr = (curr << 1)^(int)poly;
				}
				else
				{
					curr <<= 1;
				}
			}
			table[i] = (char) curr;
		}
	}
};
