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



#define SKILL_TABLE_ACQUISITION(ValueBase,SkillAttrName) \
float Value = ValueBase; \
for (const auto &Tmp : AdditionalSkillData) \
{ \
	switch (Tmp.Value.SkillType.SkillEffectType)\
	{\
		case  ESkillEffectType::ADD:\
			Value += Tmp.Value.SkillAttrName;\
			break;\
		case  ESkillEffectType::SUBTRACT:\
			Value -= Tmp.Value.SkillAttrName;\
			break;\
	}\
} \
return Value;

#define SKILL_TABLE_ACQUISITION_CD(InCD) \
float Value = InCD; \
for (const auto &Tmp : AdditionalSkillData) \
{ \
	Value -= Tmp.Value.InCD; \
} \
return Value;