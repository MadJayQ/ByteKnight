#pragma once
#ifdef GetClassName
#undef GetClassName
#endif
class ObjectMetadata
{
public:
	ObjectMetadata(const char* classname) { _classname = classname; }
	ObjectMetadata() {}
	~ObjectMetadata() {}

	const char* GetClassName() const { return _classname; }
private:
	const char* _classname;

};
#define ENGINE_CLASS(classname) static ObjectMetadata GetObjectMetadata() { \
                                       return ObjectMetadata(#classname); \
                                    }

