CPPFLAGS=-g -D_REENTRANT -I../thirdparty/googletest/include
LDFLAGS=-g 
SRCS=Node.cpp CharStream.cpp FileStream.cpp ParseHtml.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
#TEST_SRCS=FileStreamTest.cpp Main.cpp
TEST_SRCS=FileStreamTest.cpp ParseHtmlTest.cpp Main.cpp
TEST_OBJS=$(subst .cpp,.o,$(TEST_SRCS))

%.o: %.cpp
	    g++ $(CPPFLAGS) -c $< 

test: $(OBJS) $(TEST_OBJS) 
	    g++ $(CPPFLAGS) $(LDFLAGS) $(OBJS) $(TEST_OBJS) -otest 
