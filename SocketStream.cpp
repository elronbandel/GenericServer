//
// Created by elronbandel on 1/7/19.
//

#include "SocketStream.h"
#include "Socket.h"

SocketStream::SocketStream(Socket s) : std::iostream(nullptr) {
    skbuf = new sockbuf(s);
    iostream::init(skbuf);
}

sockbuf::sockbuf(Socket sock) {
    s = sock;
    setg(gbuf, gbuf + SOCKBUFSIZE, gbuf + SOCKBUFSIZE); // set get area
    setp(pbuf, pbuf + SOCKBUFSIZE);			// set put area
}
sockbuf::~sockbuf() {
    sync();
}


int sockbuf::underflow()	// get data from socket into get area
{
    int bytes_read = 0;
    bytes_read = s.read(gbuf ,SOCKBUFSIZE);
    if(bytes_read <= 0)return -1;
    setg(gbuf ,gbuf ,gbuf + bytes_read); // set get area pointers
    return 0;
}

int sockbuf::overflow(int c)	// put data from put area into socket
{
    int bytes_written;
    if(c == EOF) return sync();
    bytes_written = s.write(pbuf, SOCKBUFSIZE);
    setp(pbuf,pbuf + bytes_written);	// set put area pointers
    *pptr() = c;				// write out the last one
    pbump(1);				// advance put pointer
    return c;				// no idea why
}


int sockbuf::sync() {
    // check if there's data to flush
    if(pptr() > pbase()) {
        s.write(pbuf, pptr() - pbuf);
    }
    setp(pbuf, pbuf + SOCKBUFSIZE);			// set put area
    return 0;
}

int sockbuf::in_avail(void)
{
    return 0;
    //return gptr() - eback();
}
