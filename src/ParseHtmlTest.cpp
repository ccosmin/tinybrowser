#include "Testing.h"
#include "FileStream.h"
#include "ParseHtml.h"

TEST(ParseHtmlTest, Read0)
{
  FileStream fs("../testfiles/T0.html", 8);
  ParseHtml p(fs);
  p.Start();
}

TEST(ParseHtmlTest, Read1)
{
  FileStream fs("../testfiles/T1.html", 8);
  ParseHtml p(fs);
  p.Start();
}

TEST(ParseHtmlTest, Read2)
{
  FileStream fs("../testfiles/T2.html", 8);
  ParseHtml p(fs);
  p.Start();
}

TEST(ParseHtmlTest, Read3)
{
  FileStream fs("../testfiles/T3.html", 8);
  ParseHtml p(fs);
  p.Start();
}

