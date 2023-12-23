#pragma once

#ifndef __cplusplus
#error this header requires a C++ compiler
#endif

#define _FILE_OFFSET_BITS 64  
#define FUSE_USE_VERSION  314

#include <errno.h>
#include "fuse/include/fuse.h"
#include <string>

namespace Fuse{
    
    class FileSystemBase
    {
        public:
            FileSystemBase()
            {
                m_fuseOperations.init = FuseInit;
                m_fuseOperations.destroy = FuseDestory;
                m_fuseOperations.chmod = FuseChmod;
                m_fuseOperations.chown = FuseChown;
                m_fuseOperations.flush = FuseFlush;
                m_fuseOperations.fsync = FuseFsync;
                m_fuseOperations.getattr = FuseGetattr;
                m_fuseOperations.link = FuseLink;
                m_fuseOperations.mkdir = FuseMkdir;
                m_fuseOperations.mknod = FuseMknod;
                m_fuseOperations.open = FuseOpen;
                m_fuseOperations.read = FuseRead;
                m_fuseOperations.readlink = FuseReadlink;
                m_fuseOperations.release = FuseRelease;
                m_fuseOperations.rename = FuseRename;
                m_fuseOperations.rmdir = FuseRmdir;
                m_fuseOperations.statfs = FuseStatfs;
                m_fuseOperations.symlink = FuseSymlink;
                m_fuseOperations.truncate = FuseTruncate;
                m_fuseOperations.unlink = FuseUnlink;
                m_fuseOperations.utimens = FuseUtimens;
                m_fuseOperations.write = FuseWrite;
                m_fuseOperations.opendir = FuseOpendir;
                m_fuseOperations.readdir = FuseReaddir;
                m_fuseOperations.releasedir = FuseReleasedir;
                m_fuseOperations.access = FuseAccess;
                m_fuseOperations.create = FuseCreate;
                
            }
            virtual ~FileSystemBase(){}
            void MainLoop(const std::string &mountPoint)
            {
                int   ret = 0;
                int   fuse_argc = 1;
                char  fuse_program[] = "fusefs";
                char  *fuse_argv[]={fuse_program};
                struct fuse_args args = FUSE_ARGS_INIT(fuse_argc, fuse_argv);
                bool   mount_flag = false;

                do
                {
                    m_fuse = fuse_new(&args, &m_fuseOperations,sizeof(struct fuse_operations), this);
                    if( !m_fuse )
                    {
                        break;
                    }

                    ret = fuse_mount(m_fuse,mountPoint.c_str());
                    if( ret < 0 )
                    {
                        break;
                    }
                    mount_flag = true;

                    ret = fuse_daemonize(1);
                    if( ret < 0 )
                    {
                        break;
                    }

                    struct fuse_loop_config *loop_config = NULL;
                    loop_config = fuse_loop_cfg_create();
                    if( !loop_config ){
                        break;
                    }
                    ret = fuse_loop_mt(m_fuse,loop_config);
                    return;
                }while(0);

                if( mount_flag )
                {
                    fuse_unmount(m_fuse);
                }

                if( m_fuse )
                {
                    fuse_destroy(m_fuse);
                    m_fuse = nullptr;
                }
            }
        protected:
            virtual void* Init(struct fuse_conn_info *conn)
            {
                return this;
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
            static void* FuseInit(struct fuse_conn_info *conn,struct fuse_config *cfg)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return nullptr;
                }

                return pSelf->Init(conn);
            }

            static void FuseDestory(void *private_data)
            {

            }

            static int   FuseGetattr(const char *path,struct stat *stbuf, struct fuse_file_info *fi)
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

            static int   FuseReaddir(const char *path,void *dbuf,fuse_fill_dir_t filler,off_t offset,struct fuse_file_info *fi,enum fuse_readdir_flags)
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

            static int   FuseRename(const char *from,const char *to,unsigned int flags)
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

            static int   FuseChmod(const char *path,mode_t mode,struct fuse_file_info *fi)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Chmod(path,mode);
            }

            static int   FuseChown(const char *path,uid_t uid,gid_t gid, struct fuse_file_info *fi)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Chown(path,uid,gid);
            }

            static int   FuseTruncate(const char *path,off_t size, struct fuse_file_info *fi)
            {
                FileSystemBase  *pSelf = static_cast<FileSystemBase*>(fuse_get_context()->private_data);
                if( !pSelf ){
                    return -EINVAL;
                }

                return pSelf->Truncate(path,size);
            }

            static int   FuseUtimens(const char *path,const struct timespec tv[2],struct fuse_file_info *fi)
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
            fuse_operations        m_fuseOperations;    
            struct fuse            *m_fuse;
    };

}
