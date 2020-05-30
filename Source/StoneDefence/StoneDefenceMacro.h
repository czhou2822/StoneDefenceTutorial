#include "StoneDefence.h"

#define SD_print_s(Format, ...)\
{const FString Msg_s = FString::Printf(TEXT(Format), ##__VA_ARGS__);\
GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, Msg_s);}

#define SD_print(Type,Format,...)\
{const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
UE_LOG(LogStoneDefence, Type, TEXT("%S"), *Msg);} 


#if WITH_EDITOR
#define SD_print_r(Type,Format,...)\
{const FString Msg = FString::Printf(TEXT(Format),##__VA_ARGS__); \
GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, Msg); \
UE_LOG(LogStoneDefence, Type, TEXT("%S"), *Msg);}
#else
#define SD_print_r(Type,Format,...)\
SD_print(Type,Format,##__VA_ARGS__)
#endif

