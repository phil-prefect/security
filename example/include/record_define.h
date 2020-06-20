enum dtype_record_define {
	TYPE(RECORD_DEFINE)=0x3210
};
enum subtype_record_define {
	SUBTYPE(RECORD_DEFINE,RECORD)=0x1,
	SUBTYPE(RECORD_DEFINE,READ),
	SUBTYPE(RECORD_DEFINE,WRITE)
};

typedef struct record_define_record{
	char * record_no;
	char * commodity_news;
	char * number_info;
	char * commodity_prices;
	char * address_info;
	char * payment_info;
	char * application_for_drawback_info;
	char * drawback_info;
	char * a_return_request_info;
	char * return_info;
	char * delivery_info;
	char * take_delivery_info;
	char * complete_info;
	char * evaluate_info;
	
}__attribute__((packed)) RECORD(RECORD_DEFINE,RECORD);

typedef struct record_define_read{
	char * record_no;
}__attribute__((packed)) RECORD(RECORD_DEFINE,READ);

typedef struct record_define_write{
	char * record_no;
	char * segment;
	char * text;
}__attribute__((packed)) RECORD(RECORD_DEFINE,WRITE);
