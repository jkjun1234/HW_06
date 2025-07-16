#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyCharacter.generated.h"

class UCapsuleComponent;	// 캡슐 컴포넌트 임시 선언
class USpringArmComponent;	//스프링 암 클래스 임시 선언
class UCameraComponent;	//카메라 컴포넌트 임시 선언
struct FInputActionValue;	// 입력 액션 값 구조체 선언

UCLASS()
class HW_07_08_API AMyCharacter : public APawn
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "RootComponent")	// 에디터에서 설정할 수 있도록
	UCapsuleComponent* CapsuleComp;	// 충돌 컴포넌트로 캡슐 컴포넌트 설정

	// 스켈레탈 메쉬 컴포넌트 설정
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="SkeletalMesh")
	USkeletalMeshComponent* SkeletalMeshComp;	// 스켈레탈 메쉬 컴포넌트


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	USpringArmComponent* SpringArmComp;	// 스프링 암 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	UCameraComponent* CameraComp;	// 카메라 컴포넌트

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 300.0f;	// 이동 속도

protected:	
	//입력 바인딩 함수
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
 
	void StartJump(const FInputActionValue& value);	// 점프 시작 함수
	void StopJump(const FInputActionValue& value);	// 점프 중지 함수
	void Move(const FInputActionValue& value);	// 이동 함수
	void Look(const FInputActionValue& value);	// 시점 조정 함수

	void MoveFoward(float Value);	// 앞으로 이동 함수
	void MoveRight(float Value);	// 오른쪽으로 이동 함수
};
