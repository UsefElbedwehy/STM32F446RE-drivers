<h1>     CRC Calculation unit     </h1>

<h3>CRC introduction:</h3>

The CRC (cyclic redundancy check) calculation unit is used to get a CRC code from a 32-bit data word and a fixed generator polynomial.

Among other applications, CRC-based techniques are used to verify data transmission or storage integrity.

The CRC calculation unit helps compute a signature of the 
software during runtime, to be compared with a reference signature generated at link-time and stored at a given memory location.

<h3>CRC main features:</h3>

- Single input/output 32-bit data register.
 
- CRC computation done in four AHB clock cycles (HCLK).

- General-purpose 8-bit register (can be used for temporary storage).

<h3>CRC functional description:</h3>

The CRC calculation unit mainly consists of a single 32-bit data register, which:

- is used as an input register to enter new data in the CRC calculator (when writing into 
the register).

- holds the result of the previous CRC calculation (when reading the register).

Each write operation into the data register creates a combination of the previous CRC value 
and the new one (CRC computation is done on the whole 32-bit data word, and not byte per 
byte).

The write operation is stalled until the end of the CRC computation, thus allowing back-to-back write accesses or consecutive write and read access.

The CRC calculator can be reset to 0xFFFF FFFF with the RESET control bit in the 
CRC_CR register. This operation does not affect the contents of the CRC_IDR register.
