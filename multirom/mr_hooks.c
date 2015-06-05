#include <unistd.h>
#include <log.h>
#include <trampoline/devices.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <pthread.h>
#include <fcntl.h>
#include <util.h>

#if MR_DEVICE_HOOKS >= 1
#define PID_TOUCH "/touch.pid"

static void write_pid(const char* path, int pid) {
	FILE* f = fopen(path, "w");
	int num = fprintf(f, "%d\n", pid);
	fclose(f);
	ERROR("Wrote PID %d (%d chars) to %s\n", pid, num, path);
}

static void kill_pid(const char* path) {
	int pid;
	FILE *f = fopen(path, "r");
	if (f == NULL)
		return;
	fscanf(f, "%d", &pid);
	fclose(f);
	kill(pid, SIGKILL);
	unlink(path);
}

void mrom_hook_before_fb_close() {
	kill_pid(PID_TOUCH);
}

int mrom_hook_after_android_mounts(__attribute__((unused))const char *busybox_path, __attribute__((unused))const char *base_path, __attribute__((unused))int type) {
	mrom_hook_before_fb_close();
	return 0;
}
#endif

#if MR_DEVICE_HOOKS >= 3
static void ts_thread() {
	symlink("/realdata/media/0/multirom/touchscreen", "/sbin/touchscreen");
	mkdir ("/system/lib", 0666);
	mkdir ("/system/bin", 0666);
	symlink("/sbin/touchscreen/librm31080.so", "/system/lib/librm31080.so");
	symlink("/sbin/touchscreen/linker", "/system/bin/linker");
	wait_for_file("/dev/raydium_ts", 10);
	wait_for_file("/realdata/media/0/multirom", 10);

	ERROR("Starting rm-wrapper...\n");
	char* argv[] = {"/sbin/touchscreen/rm-wrapper", NULL};
	char* envp[] = {"LD_LIBRARY_PATH=/sbin/touchscreen", "TOUCH_DATA_DIR=/realdata/touchscreen", NULL};
	execve(argv[0], &argv[0], envp);
}

void tramp_hook_before_device_init() {
	signal(SIGCHLD, SIG_IGN);

	// Touch doesn't really work, so disable for now
	/*if (fork() == 0) {
		write_pid(PID_TOUCH, getpid());
		ts_thread();
		_exit(0);
	}*/
}
#endif
