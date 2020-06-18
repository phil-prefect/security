#ifndef SYMM_CRYPT_FUNC_H
#define SYMM_CRYPT_FUNC_H

struct init_struct
{
	int  mode;   // 0 means create a sm2 key pair, 1 means wait to receive a sm2 key pair;
	char * prikeyfile;
	char * pubkeyfile;
};

// plugin's init func and kickstart func
int sm2crypt_init(void * sub_proc,void * para);
int sm2crypt_start(void * sub_proc,void * para);

#endif
