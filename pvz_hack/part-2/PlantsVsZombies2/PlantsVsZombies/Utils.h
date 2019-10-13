#pragma once

#define MSG_BUFFER_SIZE 8192

void WriteMemoryBYTES(unsigned int uAddress, void* bytes, unsigned int len);
void WriteMemoryQWORD(unsigned int uAddress, unsigned __int64 value);
void WriteMemoryDWORD(unsigned int uAddress, unsigned int value);
void WriteMemoryWORD(unsigned int uAddress, unsigned short value);
void WriteMemoryBYTE(unsigned int uAddress, unsigned char value);
void NOPMemory(unsigned int uAddress, unsigned int len);
void NULLMemory(unsigned int uAddress, unsigned int len);
void WriteInstruction(unsigned int uAddress, unsigned int uDestination, unsigned char uFirstByte);
void WriteInstructionCallJmpEax(unsigned int uAddress, unsigned int uDestination, unsigned int uNopEnd = NULL);
void WriteInstructionCall(unsigned int uAddress, unsigned int uDestination, unsigned int uNopEnd = NULL);
void WriteInstructionJmp(unsigned int uAddress, unsigned int uDestination, unsigned int uNopEnd = NULL);

void Msg(const char* title, const char* format, ...);
void Msg(const wchar_t* title, const wchar_t* format, ...);

template <typename Type, int Size, int RequiredSize>
struct TypeSizeCheck;

template <typename Type, int Size>
struct TypeSizeCheck<Type, Size, Size>
{};

#define UniqueSizeCheckName2(c) TypeSizeCheck__##c
#define UniqueSizeCheckName1(c) UniqueSizeCheckName2(c)
#define UniqueSizeCheckName     UniqueSizeCheckName1(__COUNTER__)

#define CompileTimeSizeCheck(Type, Size)									\
	struct UniqueSizeCheckName : TypeSizeCheck<Type, sizeof(Type), Size>	\
	{}

template <typename Type, typename Member, int Offset, int RequiredOffset>
struct MemberOffsetCheck;

template <typename Type, typename Member, int Offset>
struct MemberOffsetCheck<Type, Member, Offset, Offset>
{};

#define CompileTimeOffsetCheck(Type, Member, Offset)								\
	typedef size_t Type##__##Member##__;											\
	struct Type##__##Member##__OffsetCheck :										\
	MemberOffsetCheck<Type, Type##__##Member##__, offsetof(Type, Member), Offset>	\
	{}
