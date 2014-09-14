#ifndef __CHARSTREAM_H__
#define __CHARSTREAM_H__

class CharStream
{
public:
  /// Returns EOF if at end of stream.
  virtual int GetChar() = 0;
  virtual void UngetChar(int c) = 0;
  virtual ~CharStream();
};

#endif

