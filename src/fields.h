enum gentity_field_type {
	FIELD_INT,
	FIELD_FLOAT,
	FIELD_STRING,
	FIELD_VEC3,
	FIELD_ARRAY,
	FIELD_ENTITY,
	FIELD_CLIENT,
	FIELD_INT_ARRAY,
	FIELD_FLOAT_ARRAY,
};

enum gentity_field_flag {
	FIELD_FLAG_NONE,
	FIELD_FLAG_READONLY,
	FIELD_FLAG_NOPTR
};

struct gentity_field {
	const char *name;
	size_t offset;
	enum gentity_field_type type;
	enum gentity_field_flag flags;
};
