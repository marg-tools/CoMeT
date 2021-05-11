/*BEGIN_LEGAL
  Intel Open Source License

  Copyright (c) 2016 Intel Corporation. All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.  Redistributions
  in binary form must reproduce the above copyright notice, this list of
  conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.  Neither the name of
  the Intel Corporation nor the names of its contributors may be used to
  endorse or promote products derived from this software without
  specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
  ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  END_LEGAL */

/** Create a custom input stream by overriding streambuf's undeflow method
    to use gzip to stream from a compressed gz file. */

#include <iostream>
#include "unistd.h"
#include "zlib.h"

// custom input streambuf that can read from gz compressed files
class intel_gzip_istreambuf : public std::streambuf {
public:
    intel_gzip_istreambuf(const std::string &src, const int sInputBufferSize);

    ~intel_gzip_istreambuf();

    bool constructionCompleted(void);

private:
    gzFile gzFilePointer;
    std::string fileName;
    int error;
    char *streamInputBuffer;
    bool constructionComplete;

    bool CloseFile();
    bool openGzFileForRead();

    const int streamInputBufferSize;
    static const int putbackSize = 1;       // putback buffer size

protected:
    // read de-compressed data into stream buffer
    virtual int_type underflow();
};

/** Create a custom input stream for streaming from a gz compressed file.
    This is achieved by constructing a custom streambuf (intel_gzip_istreambuf) that reads from bz files.
    Then creating an object inheriting from istream and setting its streambuffer (intel_gzip_Stream)
    to use the custom streambuf.
*/
class intel_gzip_istream : public std::istream{
protected:
    intel_gzip_istreambuf ib;
public:
    intel_gzip_istream(std::string name, const int sInputBufferSize) :
        std::istream(0), ib(name, sInputBufferSize){
        rdbuf(&ib);
    }

    bool constructorSuccessful(void){
        return ib.constructionCompleted();
    }
};
