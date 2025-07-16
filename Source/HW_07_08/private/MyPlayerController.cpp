#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"	// Enhanced Input �ý����� ����ϱ� ���� ��� ����

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

	if (ULocalPlayer* LocalPlaer = GetLocalPlayer()) // �����÷��̾� �ִ��� Ȯ��
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlaer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())	// Enhanced Input ����ý��� ��������
		{
			if (InputMappingContext) // �Է� ���� ���ؽ�Ʈ�� �����Ǿ� �ִٸ�
			{
				Subsystem->AddMappingContext(InputMappingContext, 0); // Enhanced Input �ý��ۿ� �Է� ���� ���ؽ�Ʈ �߰�
			}
		}
	}
}