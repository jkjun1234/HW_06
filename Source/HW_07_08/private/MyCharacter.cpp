#include "MyCharacter.h"

#include "EnhancedInputComponent.h"	// Enhanced Input ������Ʈ ��� ����
#include "GameFramework/Controller.h"
#include "MyPlayerController.h"	// �÷��̾� ��Ʈ�ѷ� ��� ����
// ĸ��	������Ʈ, ���̷�Ż �޽� ������Ʈ, ī�޶� ������Ʈ, ������ �� ������Ʈ ��� ���� ����
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"	
#include "GameFramework/SpringArmComponent.h"
//#include "GameFramework/CharacterMovementComponent.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));	// �浹 ������Ʈ�� ĸ�� ������Ʈ ����
	SetRootComponent(CapsuleComp);	// ��Ʈ ������Ʈ�� ����
	CapsuleComp->SetSimulatePhysics(false);	// ���� �ùķ��̼� ��Ȱ��ȭ

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));	// ���̷�Ż �޽� ������Ʈ ����
	SkeletalMeshComp->SetupAttachment(RootComponent);	// ��Ʈ ������Ʈ�� ���̷�Ż �޽� ������Ʈ ����
	SkeletalMeshComp->SetSimulatePhysics(false);	// ���̷�Ż �޽� ������Ʈ�� ���� �ùķ��̼� ��Ȱ��ȭ
	

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));	// ������ �� ������Ʈ ����
	SpringArmComp->SetupAttachment(RootComponent);	// ��Ʈ ������Ʈ�� ������ �� ������Ʈ ����
	SpringArmComp->TargetArmLength = 300.0f;	// ������ ���� ���� ����
	SpringArmComp->bUsePawnControlRotation = true;	// �� ��Ʈ�ѷ� ȸ�� ��� ����

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));	// ī�޶� ������Ʈ ����
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);	// ������ �� ������Ʈ�� ī�޶� ������Ʈ ����
	CameraComp->bUsePawnControlRotation = false;	// �� ��Ʈ�ѷ� ȸ�� ������� ����
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController())) // �÷��̾� ��Ʈ�ѷ� ��������
		{
			if (PlayerController->MoveAction)	// �̵� �׼��� �����Ǿ� �ִٸ�
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AMyCharacter::Move
				);	// �̵� �׼� ���ε�
			}

			if (PlayerController->LookAction)	// ���� ���� �׼��� �����Ǿ� �ִٸ�
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AMyCharacter::Look
				);	// ���� ���� �׼� ���ε�
			}

			if (PlayerController->JumpAction)	// ���� �׼��� �����Ǿ� �ִٸ�
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Started,
					this,
					&AMyCharacter::StartJump
				);	// ���� ���� �׼� ���ε�

				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&AMyCharacter::StopJump
				);	// ���� ���� �׼� ���ε�
			}
		}
	}
}

void AMyCharacter::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>()) // ���� �׼��� ���۵Ǹ�
	{
		UE_LOG(LogTemp, Warning, TEXT("Jump started!")); // �α� ���
	}
}

void AMyCharacter::StopJump(const FInputActionValue& value)
{
	if (value.Get<bool>()) // ���� �׼��� �����Ǹ�
	{
		UE_LOG(LogTemp, Warning, TEXT("Jump stopped!")); // �α� ���
	}
}

void AMyCharacter::Move(const FInputActionValue& value)
{
	const FVector2D MoveInput = value.Get<FVector2D>(); // �Է� ������ 2D ���� ��������
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()); // �÷��̾� ��Ʈ�ѷ� ��������

	if (!MoveInput.IsNearlyZero())
	{
		// ��Ʈ�ѷ��� ȸ�������� Yaw�� ����
		const FRotator ControlRot = PlayerController->GetControlRotation();
		const FRotator YawRot(0, ControlRot.Yaw, 0);
		
		// ��Ʈ�ѷ�(ī�޶�) ���� Forward/Right ����
		const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
	

		FVector MoveDirection = Forward * MoveInput.X + Right * MoveInput.Y; // �̵� ���� ���
		MoveDirection.Normalize(); // �̵� ���� ����ȭ

		float DeltaTime = GetWorld()->GetDeltaSeconds(); // ��Ÿ �ð� ��������

		// �̵� ����(�ӵ� * ���� * ��ŸŸ��)
		FVector Movement = MoveDirection * MoveSpeed * DeltaTime;
		AddActorWorldOffset(Movement); // dnjfem ���������� �̵� ����

		if (!MoveDirection.IsNearlyZero())
		{
			FRotator TargetRot = MoveDirection.Rotation(); // �̵� ������ ȸ�� ���
			TargetRot.Pitch = 0.0f; // ��ġ ���� 0���� �����Ͽ� ���� ȸ���� ����
			TargetRot.Roll = 0.0f; // �� ���� 0���� �����Ͽ� ���� ȸ���� ����

			SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRot, DeltaTime, 5.0f)); // ���� ȸ������ ��ǥ ȸ������ ����
		}
	}

}

void AMyCharacter::Look(const FInputActionValue& value)
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()); // �÷��̾� ��Ʈ�ѷ� ��������
	FRotator ControlRot = PlayerController->GetControlRotation(); // ��Ʈ�ѷ� ȸ�� ��������

	const FVector2D LookInput = value.Get<FVector2D>(); // �Է� ������ 2D ���� ��������
	if (!FMath::IsNearlyZero(LookInput.X))
	{
		ControlRot.Yaw += LookInput.X; // �Է� ���� X�� ����Ͽ� Yaw ȸ�� �߰�
		PlayerController->SetControlRotation(ControlRot); // ��Ʈ�ѷ� ȸ�� ����
		UE_LOG(LogTemp, Warning, TEXT("Looking horizontally: %f"), ControlRot.Yaw); // �¿� ���� ���� �α� ���
	}
	if (!FMath::IsNearlyZero(LookInput.Y))
	{
		ControlRot.Pitch += LookInput.Y; // �Է� ���� Y�� ����Ͽ� Pitch ȸ�� �߰�
		PlayerController->SetControlRotation(ControlRot); // ��Ʈ�ѷ� ȸ�� ����
		UE_LOG(LogTemp, Warning, TEXT("Looking vertically: %f"), ControlRot.Pitch); // ���� ���� ���� �α� ���
	}
}


