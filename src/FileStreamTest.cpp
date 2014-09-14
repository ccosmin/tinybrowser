#include "Testing.h"
#include "FileStream.h"

TEST(FileStreamTest, ReadWithBufferSizeOfOne)
{
  FileStream fs("../testfiles/T0.html", 1);
  int c;
  while ( (c = fs.GetChar()) != EOF )
    putchar(c);
  EXPECT_EQ(EOF, c);
}

TEST(FileStreamTest, ReadWithBufferSizeOfOneUnget)
{
  FileStream fs("../testfiles/T0.html", 1);
  int c1 = fs.GetChar();
  int c2 = fs.GetChar();
  fs.UngetChar(c2);
  fs.UngetChar(c1);
  EXPECT_EQ(c1, fs.GetChar());
}

TEST(FileStreamTest, ReadWholeFile)
{
  FileStream fs("../testfiles/T0.html", 8);
  int c;
  while ( (c = fs.GetChar()) != EOF )
    putchar(c);
  EXPECT_EQ(EOF, c);
}

TEST(FileStreamTest, GetUnget)
{
  FileStream fs("../testfiles/T0.html", 8);
  int c = fs.GetChar();
  fs.UngetChar(c);
  EXPECT_EQ(c, fs.GetChar());
}

