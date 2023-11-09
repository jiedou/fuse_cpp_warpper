#ifndef FUSE_WRAPPER_HPP_INCLUDED
#define FUSE_WRAPPER_HPP_INCLUDED

#ifndef __cplusplus
#error this header requires a C++ compiler
#endif

#define _FILE_OFFSET_BITS 64  

#include <errno.h>
#include <fuse.h>

namespace Fuse{
    
    class FileSystemBase
    {
        public:
            FileSystemBase(){}
            virtual ~FileSystemBase(){}
            
        protected:
            virtual void* Init(struct fuse_conn_info *conn)
            {
                return nullptr;
            }

            virtual int  Getattr(const char *path,struct stat *stbuf)
            {
                return 0;
            }

            virtual int  Access(const char *path, int mask)
            {
                return 0;
            }

            virtual int   Opendir(const char *path,struct fuse_file_info *fi)
            {
                return 0;
            }

            virtual int   Readdir(const char *path,void *dbuf,fuse_fill_dir_t filler,off_t offset,struct fuse_file_info *fi)
            {
                return 0;
            }

            virtual int   Releasedir(const char *path,struct fuse_file_info *fi)
            {
                return 0;
            }

            virtual int   Readlink(const char *path,char *linkbuf,size_t size)
            {
                return 0;
            }

            virtual int   Mknod(const char *path,mode_t mode,dev_t rdev)
            {
                return 0;
            }

            virtual int   Mkdir(const char *path,mode_t mode)
            {
                return 0;
            }

            virtual int   Symlink(const char *from,const char *to)
            {
                return 0;
            }

            virtual int   Unlink(const char *path)
            {
                return 0;
            }

            virtual int   Rmdir(const char *path)
            {
                return 0;
            }

            virtual int   Rename(const char *from,const char *to)
            {
                return 0;
            }

            virtual int   Link(const char *from,const char *to)
            {
                return 0;
            }

            virtual int   Chmod(const char *path,mode_t mode)
            {
                return 0;
            }

            virtual int   Chown(const char *path,uid_t uid,gid_t gid)
            {
                return 0;
            }

            virtual int   Truncate(const char *path,off_t size)
            {
                return 0;
            }

            virtual int   Utimens(const char *path,const struct timespec tv[2])
            {
                return 0;
            }

            virtual int   Open(const char *path,struct fuse_file_info *fi)
            {
                return 0;
            }

            virtual int   Flush(const char *path,struct fuse_file_info *fi)
            {
                return 0;
            }

            virtual int   Fsync(const char *path,int isdatasync,struct fuse_file_info *fi)
            {
                return 0;
            }

            virtual int   Release(const char *path,struct fuse_file_info *fi)
            {
                return 0;
            }

            virtual int   Read(const char *path,char *rbuf,size_t size,off_t offset,struct fuse_file_info *fi)
            {
                return 0;
            }

            virtual int   Write(const char *path,const char *wbuf,size_t size,off_t offset,struct fuse_file_info *fi)
            {
                return 0;
            }

            virtual int   Statfs(const char *path,struct statvfs *buf)
            {
                return 0;
            }

            virtual int   Create(const char *path,mode_t mode,struct fuse_file_info *fi)
            {
                return 0;
            }

        private:
            static void* FuseInit(struct fuse_conn_info *conn)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return nullptr;
                }

                return pSelf->Init(conn);
            }

            static int   FuseGetattr(const char *path,struct stat *stbuf)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Getattr(path,stbuf);
            }

            static int   FuseAccess(const char *path, int mask)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Access(path,mask);
            }

            static int   FuseOpendir(const char *path,struct fuse_file_info *fi)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Opendir(path,fi);
            }

            static int   FuseReaddir(const char *path,void *dbuf,fuse_fill_dir_t filler,off_t offset,struct fuse_file_info *fi)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Readdir(path,dbuf,filler,offset,fi);
            }

            static int   FuseReleasedir(const char *path,struct fuse_file_info *fi)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Releasedir(path,fi);
            }

            static int   FuseReadlink(const char *path,char *linkbuf,size_t size)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Readlink(path,linkbuf,size);
            }

            static int   FuseMknod(const char *path,mode_t mode,dev_t rdev)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Mknod(path,mode,rdev);
            }

            static int   FuseMkdir(const char *path,mode_t mode)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Mkdir(path,mode);
            }

            static int   FuseSymlink(const char *from,const char *to)
            {
                 FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Symlink(from,to);
            }

            static int   FuseUnlink(const char *path)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Unlink(path);
            }

            static int   FuseRmdir(const char *path)
            {
                 FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Rmdir(path);
            }

            static int   FuseRename(const char *from,const char *to)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Rename(from,to);
            }

            static int   FuseLink(const char *from,const char *to)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Link(from,to);
            }

            static int   FuseChmod(const char *path,mode_t mode)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Chmod(path,mode);
            }

            static int   FuseChown(const char *path,uid_t uid,gid_t gid)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Chown(path,uid,gid);
            }

            static int   FuseTruncate(const char *path,off_t size)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Truncate(path,size);
            }

            static int   FuseUtimens(const char *path,const struct timespec tv[2])
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Utimens(path,tv);
            }

            static int   FuseOpen(const char *path,struct fuse_file_info *fi)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Open(path,fi);
            }

            static int   FuseFlush(const char *path,struct fuse_file_info *fi)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Flush(path,fi);
            }

            static int   FuseFsync(const char *path,int isdatasync,struct fuse_file_info *fi)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Fsync(path,isdatasync,fi);
            }

            static int   FuseRelease(const char *path,struct fuse_file_info *fi)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Release(path,fi);
            }

            static int   FuseRead(const char *path,char *rbuf,size_t size,off_t offset,struct fuse_file_info *fi)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Read(path,rbuf,size,offset,fi);
            }

            static int   FuseWrite(const char *path,const char *wbuf,size_t size,off_t offset,struct fuse_file_info *fi)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Write(path,wbuf,size,offset,fi);
            }

            static int   FuseStatfs(const char *path,struct statvfs *buf)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Statfs(path,buf);
            }

            static int   FuseCreate(const char *path,mode_t mode,struct fuse_file_info *fi)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Create(path,mode,fi);
            }


        private:
            fuse_operations m_fuseOperations;    
    };

}



#endif