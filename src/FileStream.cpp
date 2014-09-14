#include <assert.h>
#include <stdexcept>
#include "FileStream.h"

FileStream::FileStream(const std::string& fileName, int allocatedSize)
  : m_current(0), m_bufferSize(0), m_allocatedSize(allocatedSize)
{
  m_file = fopen(fileName.c_str(), "rb");
  if ( ! m_file )
  {
    fprintf(stderr, "Unable to open file %s\n", fileName.c_str());
    throw std::runtime_error("Unable to open file");
  }
  m_buffer = new char[m_allocatedSize];
}

int FileStream::GetChar()
{
  assert(m_file);
  
  // At end of file.
  if ( m_current == m_bufferSize && feof(m_file) )
   return EOF;

  // Still characters in current buffer.
  if ( m_current < m_bufferSize )
   return m_buffer[m_current++]; 

  if ( m_current >= m_allocatedSize || ! m_bufferSize )
  {
    m_bufferSize = fread(m_buffer, 1, m_allocatedSize, m_file);
    m_current = 0;
    if ( m_bufferSize == 0 && feof(m_file) )
      return EOF;
  }

  return m_buffer[m_current++];
}

void FileStream::UngetChar(int c)
{
  if ( m_current > 0 )
  {
    --m_current;
    return;
  }

  long posInFile = ftell(m_file);
  int toRead = 0;
  if ( m_allocatedSize > posInFile )
    toRead = posInFile;
  else
    toRead = m_allocatedSize;

  assert(toRead > 0);

  int offset = - m_bufferSize - toRead;
  fseek(m_file, offset, SEEK_CUR);

  m_bufferSize = fread(m_buffer, 1, toRead, m_file);

  assert(m_bufferSize > 0);
  m_current = m_bufferSize - 1;
}

FileStream::~FileStream()
{
  delete[] m_buffer;
  fclose(m_file);
}

