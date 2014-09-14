#ifndef __FILESTREAM_H__
#define __FILESTREAM_H__

#include <stdio.h>
#include <string>

#include "CharStream.h"

class FileStream : public CharStream
{
public:
  FileStream(const std::string& fileName, int allocatedSize);
  virtual int GetChar();
  virtual void UngetChar(int c);
  ~FileStream();
private:
  FileStream(const FileStream&);
  FileStream operator=(const FileStream&);

  FILE* m_file;
  int m_allocatedSize;
  int m_bufferSize;
  char* m_buffer;
  int m_current;
};

#endif

