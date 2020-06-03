#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <sys/time.h>
 
#include "data_type.h"
#include "cube.h"
#include "cube_define.h"
#include "cube_record.h"
#include "user_define.h"
#include "record_define.h"
#include "label_define.h"

// add para lib_include
int record_acl_init(void * sub_proc, void * para)
{
	int ret;
	// add yorself's module init func here
	return 0;
}
int record_acl_start(void * sub_proc, void * para)
{
	int ret;
	void * recv_msg;
	int type;
	int subtype;
	// add yorself's module exec func here
	while(1)
	{
		usleep(time_val.tv_usec);
		ret=ex_module_recvmsg(sub_proc,&recv_msg);
		if(ret<0)
			continue;
		if(recv_msg==NULL)
			continue;
		type=message_get_type(recv_msg);
		subtype=message_get_subtype(recv_msg);
		if(!memdb_find_recordtype(type,subtype))
		{
			printf("message format (%d %d) is not registered!\n",
			message_get_type(recv_msg),message_get_subtype(recv_msg));
			continue;
		}
		if((type==TYPE(RECORD_DEFINE))&&(subtype==SUBTYPE(RECORD_DEFINE,WRITE)))
		{
			ret=proc_access_write(sub_proc,recv_msg);
		}
		else if((type==TYPE(RECORD_DEFINE))&&(subtype==SUBTYPE(RECORD_DEFINE,RECORD)))
		{
			ret=proc_access_read(sub_proc,recv_msg);
		}
	}
	return 0;
}

int proc_access_write(void * sub_proc,void * recv_msg)
{
	int ret;
	RECORD(RECORD_DEFINE,WRITE) * record_write;
	RECORD(LABEL_DEFINE,USER) * user_label;
	RECORD(RECORD_DEFINE,RECORD) * record_data;
	MSG_EXPAND * msg_expand;
	void * new_msg;
	
	ret=message_get_record(recv_msg,&record_write,0);
	if(ret<0)
		return ret;

	ret=message_remove_expand(recv_msg,TYPE_PAIR(LABEL_DEFINE,USER),&msg_expand);
	if(ret<0)
		return ret;
	if(msg_expand==NULL)
	{
		print_cubeerr("can't find user attached!\n");	
		return -EINVAL;
	}
	user_label=msg_expand->expand;

	//read db********************************************************
	DB_RECORD * db_record;

	// find the record
	db_record=memdb_find_first(TYPE_PAIR(RECORD_DEFINE,RECORD),"record_no",record_write->record_no);
	if(db_record==NULL)
	{
		record_data=Talloc0(sizeof(*record_data));
		record_data->record_no = dup_str(record_write->record_no,0);
	}
	else
	{
		record_data=db_record->record;
	}


	//*********************************************************
	
	
	
	if(user_label->role==SKER)
	{
		if(Strncmp(record_write->segment,"commodity_prices",DIGEST_SIZE)==0)
			;
		
		else if(Strncmp(record_write->segment,"drawback_info",DIGEST_SIZE)==0){
				if(Strncmp(record_data->application_for_drawback_info,"yes",DIGEST_SIZE)==0) ;
				else{
					new_msg=message_create(TYPE_PAIR(USER_DEFINE,RETURN),recv_msg);
					RECORD(USER_DEFINE,RETURN) * err_return = Talloc0(sizeof(*err_return));
					if(err_return==NULL)
						return -ENOMEM;
					err_return->return_info=dup_str("write permission denied!",0);
					err_return->return_code=NOACCESS;
					message_add_record(new_msg,err_return);
					ret=ex_module_sendmsg(sub_proc,new_msg);
					return ret;
				}
				}
		else if(Strncmp(record_write->segment,"retrun_info",DIGEST_SIZE)==0){
				if(Strncmp(record_data->a_return_request_info,"yes",DIGEST_SIZE)==0) ;
				else{
					new_msg=message_create(TYPE_PAIR(USER_DEFINE,RETURN),recv_msg);
					RECORD(USER_DEFINE,RETURN) * err_return = Talloc0(sizeof(*err_return));
					if(err_return==NULL)
						return -ENOMEM;
					err_return->return_info=dup_str("write permission denied!",0);
					err_return->return_code=NOACCESS;
					message_add_record(new_msg,err_return);
					ret=ex_module_sendmsg(sub_proc,new_msg);
					return ret;
				}
				}
		else if(Strncmp(record_write->segment,"complete_info",DIGEST_SIZE)==0){
				if(Strncmp(record_data->take_delivery_info,"yes",DIGEST_SIZE)==0) ;
				else{
					new_msg=message_create(TYPE_PAIR(USER_DEFINE,RETURN),recv_msg);
					RECORD(USER_DEFINE,RETURN) * err_return = Talloc0(sizeof(*err_return));
					if(err_return==NULL)
						return -ENOMEM;
					err_return->return_info=dup_str("write permission denied!",0);
					err_return->return_code=NOACCESS;
					message_add_record(new_msg,err_return);
					ret=ex_module_sendmsg(sub_proc,new_msg);
					return ret;
				}
				}
		else
		{
			// permission denied
			new_msg=message_create(TYPE_PAIR(USER_DEFINE,RETURN),recv_msg);
			RECORD(USER_DEFINE,RETURN) * err_return = Talloc0(sizeof(*err_return));
			if(err_return==NULL)
				return -ENOMEM;
			err_return->return_info=dup_str("write permission denied!",0);
			err_return->return_code=NOACCESS;
			message_add_record(new_msg,err_return);
			ret=ex_module_sendmsg(sub_proc,new_msg);
			return ret;
		}	
		
		
	}

	if(user_label->role==ASSISTANT)
	{
		if(Strncmp(record_write->segment,"delivery_info",DIGEST_SIZE)==0)
			{
			if(Strncmp(record_data->payment_info,"yes",DIGEST_SIZE)==0)
				;
			
			else{
				new_msg=message_create(TYPE_PAIR(USER_DEFINE,RETURN),recv_msg);
				RECORD(USER_DEFINE,RETURN) * err_return = Talloc0(sizeof(*err_return));
				if(err_return==NULL)
					return -ENOMEM;
				err_return->return_info=dup_str("write permission denied!",0);
				err_return->return_code=NOACCESS;
				message_add_record(new_msg,err_return);
				ret=ex_module_sendmsg(sub_proc,new_msg);
				return ret;
				}
			}
		else
		{
			// permission denied
			new_msg=message_create(TYPE_PAIR(USER_DEFINE,RETURN),recv_msg);
			RECORD(USER_DEFINE,RETURN) * err_return = Talloc0(sizeof(*err_return));
			if(err_return==NULL)
				return -ENOMEM;
			err_return->return_info=dup_str("write permission denied!",0);
			err_return->return_code=NOACCESS;
			message_add_record(new_msg,err_return);
			ret=ex_module_sendmsg(sub_proc,new_msg);
			return ret;
		}	
	}

	if(user_label->role==CLIENT)
	{
		if(Strncmp(record_write->segment,"record_info",DIGEST_SIZE)==0
			|| Strncmp(record_write->segment,"commodity_news",DIGEST_SIZE)==0
			|| Strncmp(record_write->segment,"number_info",DIGEST_SIZE)==0
			|| Strncmp(record_write->segment,"address_info",DIGEST_SIZE)==0)
			;
		else if(Strncmp(record_write->segment,"application_for_drawback_info",DIGEST_SIZE)==0){
			if(Strncmp(record_data->delivery_info,"no",DIGEST_SIZE)==0);
			else{
				new_msg=message_create(TYPE_PAIR(USER_DEFINE,RETURN),recv_msg);
				RECORD(USER_DEFINE,RETURN) * err_return = Talloc0(sizeof(*err_return));
				if(err_return==NULL)
					return -ENOMEM;
				err_return->return_info=dup_str("write permission denied!",0);
				err_return->return_code=NOACCESS;
				message_add_record(new_msg,err_return);
				ret=ex_module_sendmsg(sub_proc,new_msg);
				return ret;
				}
				}
		else if(Strncmp(record_write->segment,"take_delivery_info",DIGEST_SIZE)==0){
			if(Strncmp(record_data->delivery_info,"yes",DIGEST_SIZE)==0);
			else{
				new_msg=message_create(TYPE_PAIR(USER_DEFINE,RETURN),recv_msg);
				RECORD(USER_DEFINE,RETURN) * err_return = Talloc0(sizeof(*err_return));
				if(err_return==NULL)
					return -ENOMEM;
				err_return->return_info=dup_str("write permission denied!",0);
				err_return->return_code=NOACCESS;
				message_add_record(new_msg,err_return);
				ret=ex_module_sendmsg(sub_proc,new_msg);
				return ret;
				}
				}
		else if(Strncmp(record_write->segment,"evaluate_info",DIGEST_SIZE)==0
			|| Strncmp(record_write->segment,"a_return_request_info",DIGEST_SIZE)==0){
			if(Strncmp(record_data->complete_info,"yes",DIGEST_SIZE)==0);
			else{
				new_msg=message_create(TYPE_PAIR(USER_DEFINE,RETURN),recv_msg);
				RECORD(USER_DEFINE,RETURN) * err_return = Talloc0(sizeof(*err_return));
				if(err_return==NULL)
					return -ENOMEM;
				err_return->return_info=dup_str("write permission denied!",0);
				err_return->return_code=NOACCESS;
				message_add_record(new_msg,err_return);
				ret=ex_module_sendmsg(sub_proc,new_msg);
				return ret;
				}
				}
		else
		{
			// permission denied
			new_msg=message_create(TYPE_PAIR(USER_DEFINE,RETURN),recv_msg);
			RECORD(USER_DEFINE,RETURN) * err_return = Talloc0(sizeof(*err_return));
			if(err_return==NULL)
				return -ENOMEM;
			err_return->return_info=dup_str("write permission denied!",0);
			err_return->return_code=NOACCESS;
			message_add_record(new_msg,err_return);
			ret=ex_module_sendmsg(sub_proc,new_msg);
			return ret;
		}	
	}	

	ret=ex_module_sendmsg(sub_proc,recv_msg);
	return ret;
}

int proc_access_read(void * sub_proc,void * recv_msg)
{
	int ret;
	RECORD(RECORD_DEFINE,RECORD) * record_data;
	RECORD(LABEL_DEFINE,USER) * user_label;
	MSG_EXPAND * msg_expand;
	void * new_msg;
	
	ret=message_get_record(recv_msg,&record_data,0);
	if(ret<0)
		return ret;

	ret=message_remove_expand(recv_msg,TYPE_PAIR(LABEL_DEFINE,USER),&msg_expand);
	if(ret<0)
		return ret;
	if(msg_expand==NULL)
	{
		print_cubeerr("can't find user attached!\n");	
		return -EINVAL;
	}
	user_label=msg_expand->expand;
	
	if(user_label->role==ASSISTANT)
	{
		record_data->evaluate_info="Permission denied";	
		new_msg=message_create(TYPE_PAIR(RECORD_DEFINE,RECORD),recv_msg);
		if(new_msg==NULL)
			return -EINVAL;
		message_add_record(new_msg,record_data);
		ret=ex_module_sendmsg(sub_proc,new_msg);
		return ret;
	}	
	ret=ex_module_sendmsg(sub_proc,recv_msg);
	return ret;
}
