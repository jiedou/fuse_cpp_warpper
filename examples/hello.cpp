#include "fuse_wrapper.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class HelloFileSystem:public Fuse::FileSystemBase
{
 public:
    virtual int  Getattr(const char *path,struct stat *stbuf)
    {
        int res = 0;

        memset(stbuf, 0, sizeof(struct stat));
        if (strcmp(path, "/") == 0) {
            stbuf->st_mode = S_IFDIR | 0755;
            stbuf->st_nlink = 2;
        } else if (strcmp(path+1, filename) == 0) {
            stbuf->st_mode = S_IFREG | 0444;
            stbuf->st_nlink = 1;
            stbuf->st_size = strlen(content);
        } else
            res = -ENOENT;

        return res;
    }

    virtual int   Readdir(const char *path,void *dbuf,fuse_fill_dir_t filler,off_t offset,struct fuse_file_info *fi)
    {
        if (strcmp(path, "/") != 0)
		    return -ENOENT;

        filler(dbuf, ".", NULL, 0);
        filler(dbuf, "..", NULL, 0);
        filler(dbuf, filename, NULL, 0);
        return 0;
    }

    virtual int   Open(const char *path,struct fuse_file_info *fi)
    {
        if (strcmp(path+1, filename) != 0)
            return -ENOENT;

        if ((fi->flags & O_ACCMODE) != O_RDONLY)
            return -EACCES;

        return 0;
    }

    virtual int Read(const char *path,char *rbuf,size_t size,off_t offset,struct fuse_file_info *fi)
    {
        size_t len;
        (void) fi;
        if(strcmp(path+1, filename) != 0)
            return -ENOENT;

        len = strlen(content);
        if (offset < len) {
            if (offset + size > len)
                size = len - offset;
            memcpy(rbuf, content + offset, size);
        } else
            size = 0;

        return size;
    }

private:
    char *filename="hello";
    char *content="hello,world";
};


int main()
{
    HelloFileSystem hello;
    string str="/home/astute/tmp";
    hello.MainLoop(str);
    cout<<"hello,world\n";
    return 0;
}
