#include "img_read.h"
#include <stdio.h>

int main()
{
    file_session* session = session_init("./t10k-images-idx3-ubyte");
    session->get_pic(session,3);
    session->print_pic(session);
    session->session_deinit(session);
    return 0;
}
