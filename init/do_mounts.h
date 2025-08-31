/* PostmarketOS: Minimal do_mounts.h */
extern int root_mountflags;
static inline void mount_devfs(void) { }
static inline void umount_devfs(char *path) { }
static inline void create_dev(char *name, dev_t dev) { }
