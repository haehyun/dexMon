#include "myclose.h"

int myClose(int flag, Thread* self){
	if(flag == TAMPER_UNKNOWN) {
		ALOGE("msec|TAMPER_UNKNOWN");
		dvmAbort();
	}

	if(flag == TAMPER_CONNECT_FAIL) {
        ALOGE("msec|TAMPER_CONNECT_FAIL");
		dvmAbort();
	}

	if(flag == TAMPER_SERVER_CORECODE) {
		ALOGE("msec|TAMPER_CORECODE_SERVER");
		// //SIGABRT , SIGILL
		sigset_t mask;
		sigfillset(&mask);
		sigdelset(&mask, SIGILL);
		sigprocmask(SIG_SETMASK, &mask, NULL);

		//POSIX requires we flush stdio buffers on abort.
		// if (__cleanup) {
		// (*__cleanup)();
		// }

		raise(SIGILL);

		struct sigaction sa;
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = SA_RESTART;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGILL, &sa, &sa);
		sigprocmask(SIG_SETMASK, &mask, NULL);
		raise(SIGILL);
		dvmAbort();
		_exit(1);
	}

	if(flag == TAMPER_LOCAL_SIGN) {
		ALOGE("msec|TAMPER_SIGN_LOCAL");
		dvmAbort();
	}

	if(flag == TAMPER_DONGLE_SIGN) {
		ALOGE("msec|TAMPER_SIGN_DONGLE");
		// //SIGABRT , SIGILL
		sigset_t mask;
		sigfillset(&mask);
		sigdelset(&mask, SIGILL);
		sigprocmask(SIG_SETMASK, &mask, NULL);

		//POSIX requires we flush stdio buffers on abort.
		// if (__cleanup) {
		// (*__cleanup)();
		// }

		raise(SIGILL);

		struct sigaction sa;
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = SA_RESTART;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGILL, &sa, &sa);
		sigprocmask(SIG_SETMASK, &mask, NULL);
		raise(SIGILL);
	    _exit(1);
	}

	if(flag == TAMPER_LOCAL_HASH) {
		ALOGE("msec|TAMPER_HASH_LOCAL");
		dvmAbort();
	}	

	if(flag == TAMPER_DONGLE_HASH) {
	ALOGE("msec|TAMPER_HASH_DONGLE");
		// //SIGABRT , SIGILL
		sigset_t mask;
		sigfillset(&mask);
		sigdelset(&mask, SIGILL);
		sigprocmask(SIG_SETMASK, &mask, NULL);

		//POSIX requires we flush stdio buffers on abort.
		// if (__cleanup) {
		// (*__cleanup)();
		// }

		raise(SIGILL);

		struct sigaction sa;
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = SA_RESTART;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGILL, &sa, &sa);
		sigprocmask(SIG_SETMASK, &mask, NULL);
		raise(SIGILL);
	    _exit(1);
	}
	
	return 0;
}


