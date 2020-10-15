#ifndef CLASS_UTILS
#define CLASS_UTILS

#define DEFAULT_MOVE_CTOR(ClassName) ClassName(ClassName&&) = default
#define DEFAULT_MOVE_EQUAL(ClassName) ClassName& operator=(ClassName&&) = default

#define DEFAULT_MOVE_OPERATIONS(ClassName) \
	DEFAULT_MOVE_CTOR(ClassName);		   \
	DEFAULT_MOVE_EQUAL(ClassName) 

#define DISALLOW_COPY_CTOR(ClassName) ClassName(const ClassName&) = delete
#define DISALLOW_COPY_EQUAL(ClassName) ClassName& operator=(const ClassName&) = delete

#define DISALLOW_COPY_OPERATIONS(ClassName) \
	DISALLOW_COPY_CTOR(ClassName);			\
	DISALLOW_COPY_EQUAL(ClassName)			

#endif