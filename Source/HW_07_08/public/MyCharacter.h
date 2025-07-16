#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyCharacter.generated.h"

class UCapsuleComponent;	// ĸ�� ������Ʈ �ӽ� ����
class USpringArmComponent;	//������ �� Ŭ���� �ӽ� ����
class UCameraComponent;	//ī�޶� ������Ʈ �ӽ� ����
struct FInputActionValue;	// �Է� �׼� �� ����ü ����

UCLASS()
class HW_07_08_API AMyCharacter : public APawn
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "RootComponent")	// �����Ϳ��� ������ �� �ֵ���
	UCapsuleComponent* CapsuleComp;	// �浹 ������Ʈ�� ĸ�� ������Ʈ ����

	// ���̷�Ż �޽� ������Ʈ ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="SkeletalMesh")
	USkeletalMeshComponent* SkeletalMeshComp;	// ���̷�Ż �޽� ������Ʈ


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	USpringArmComponent* SpringArmComp;	// ������ �� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	UCameraComponent* CameraComp;	// ī�޶� ������Ʈ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 300.0f;	// �̵� �ӵ�

protected:	
	//�Է� ���ε� �Լ�
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
 
	void StartJump(const FInputActionValue& value);	// ���� ���� �Լ�
	void StopJump(const FInputActionValue& value);	// ���� ���� �Լ�
	void Move(const FInputActionValue& value);	// �̵� �Լ�
	void Look(const FInputActionValue& value);	// ���� ���� �Լ�

	void MoveFoward(float Value);	// ������ �̵� �Լ�
	void MoveRight(float Value);	// ���������� �̵� �Լ�
};
