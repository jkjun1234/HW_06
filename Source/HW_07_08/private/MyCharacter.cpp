#include "MyCharacter.h"

#include "EnhancedInputComponent.h"	// Enhanced Input 컴포넌트 헤더 파일
#include "MyPlayerController.h"	// 플레이어 컨트롤러 헤더 파일
// 캡슐	컴포넌트, 스켈레탈 메쉬 컴포넌트, 카메라 컴포넌트, 스프링 암 컴포넌트 헤더 파일 포함
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"	
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));	// 충돌 컴포넌트로 캡슐 컴포넌트 생성
	SetRootComponent(CapsuleComp);	// 루트 컴포넌트로 설정
	CapsuleComp->SetSimulatePhysics(false);	// 물리 시뮬레이션 비활성화

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));	// 스켈레탈 메쉬 컴포넌트 생성
	SkeletalMeshComp->SetupAttachment(RootComponent);	// 루트 컴포넌트에 스켈레탈 메쉬 컴포넌트 연결
	SkeletalMeshComp->SetSimulatePhysics(false);	// 스켈레탈 메쉬 컴포넌트의 물리 시뮬레이션 비활성화
	

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));	// 스프링 암 컴포넌트 생성
	SpringArmComp->SetupAttachment(RootComponent);	// 루트 컴포넌트에 스프링 암 컴포넌트 연결
	SpringArmComp->TargetArmLength = 300.0f;	// 스프링 암의 길이 설정
	SpringArmComp->bUsePawnControlRotation = true;	// 폰 컨트롤러 회전 사용 설정

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));	// 카메라 컴포넌트 생성
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);	// 스프링 암 컴포넌트에 카메라 컴포넌트 연결
	CameraComp->bUsePawnControlRotation = false;	// 폰 컨트롤러 회전 사용하지 않음
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
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController())) // 플레이어 컨트롤러 가져오기
		{
			if (PlayerController->MoveAction)	// 이동 액션이 설정되어 있다면
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AMyCharacter::Move
				);	// 이동 액션 바인딩
			}

			if (PlayerController->LookAction)	// 시점 조정 액션이 설정되어 있다면
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AMyCharacter::Look
				);	// 시점 조정 액션 바인딩
			}

			if (PlayerController->JumpAction)	// 점프 액션이 설정되어 있다면
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Started,
					this,
					&AMyCharacter::StartJump
				);	// 점프 시작 액션 바인딩

				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&AMyCharacter::StopJump
				);	// 점프 중지 액션 바인딩
			}
		}
	}
}

void AMyCharacter::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>()) // 점프 액션이 시작되면
	{
		UE_LOG(LogTemp, Warning, TEXT("Jump started!")); // 로그 출력
	}
}

void AMyCharacter::StopJump(const FInputActionValue& value)
{
	if (value.Get<bool>()) // 점프 액션이 중지되면
	{
		UE_LOG(LogTemp, Warning, TEXT("Jump stopped!")); // 로그 출력
	}
}

void AMyCharacter::Move(const FInputActionValue& value)
{
	const FVector2D MoveInput = value.Get<FVector2D>(); // 입력 값에서 2D 벡터 가져오기

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		UE_LOG(LogTemp, Warning, TEXT("Moving horizontally: %f"), MoveInput.X); // 앞뒤 이동 로그 출력
		AddActorLocalOffset( GetActorForwardVector() * MoveInput.X * MoveSpeed * GetWorld()->GetDeltaSeconds());	// 앞뒤 이동
		AddActorLocalRotation(FRotator(0.0f, MoveInput.X * GetWorld()->GetDeltaSeconds(), 0.0f)); // 앞뒤 이동 시 회전 추가
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		UE_LOG(LogTemp, Warning, TEXT("Moving vertically: %f"), MoveInput.Y); // 좌우 이동 로그 출력
		AddActorLocalOffset(GetActorRightVector() * MoveInput.Y * MoveSpeed * GetWorld()->GetDeltaSeconds());
		AddActorLocalRotation(FRotator(0.0f, MoveInput.Y * GetWorld()->GetDeltaSeconds(), 0.0f)); // 앞뒤 이동 시 회전 추가
	}
}



void AMyCharacter::Look(const FInputActionValue& value)
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()); // 플레이어 컨트롤러 가져오기
	FRotator ControlRot = PlayerController->GetControlRotation(); // 컨트롤러 회전 가져오기

	const FVector2D LookInput = value.Get<FVector2D>(); // 입력 값에서 2D 벡터 가져오기
	if (!FMath::IsNearlyZero(LookInput.X))
	{
		ControlRot.Yaw += LookInput.X; // 입력 값의 X를 사용하여 Yaw 회전 추가
		PlayerController->SetControlRotation(ControlRot); // 컨트롤러 회전 설정
		//PlayerController->AddYawInput(LookInput.X); // 컨트롤러 회전 설정
		UE_LOG(LogTemp, Warning, TEXT("Looking horizontally: %f"), ControlRot.Yaw); // 좌우 시점 조정 로그 출력
	}
	if (!FMath::IsNearlyZero(LookInput.Y))
	{
		ControlRot.Pitch += LookInput.Y; // 입력 값의 Y를 사용하여 Pitch 회전 추가
		PlayerController->SetControlRotation(ControlRot); // 컨트롤러 회전 설정
		//PlayerController->AddPitchInput(LookInput.Y); // 컨트롤러 회전 설정
		UE_LOG(LogTemp, Warning, TEXT("Looking vertically: %f"), ControlRot.Pitch); // 상하 시점 조정 로그 출력
	}
}


