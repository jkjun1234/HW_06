#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"	// Enhanced Input 시스템을 사용하기 위한 헤더 파일

AMyPlayerController::AMyPlayerController() :
	InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr),
	JumpAction(nullptr)
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlaer = GetLocalPlayer()) // 로컬플레이어 있는지 확인
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlaer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())	// Enhanced Input 서브시스템 가져오기
		{
			if (InputMappingContext) // 입력 매핑 컨텍스트가 설정되어 있다면
			{
				Subsystem->AddMappingContext(InputMappingContext, 0); // Enhanced Input 시스템에 입력 매핑 컨텍스트 추가
			}
		}
	}
}