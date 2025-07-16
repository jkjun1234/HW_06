// Target ��ġ���� �Դ� ���� �ϴ� �÷���
// ���� ��ġ -> MoveSpeed*Movedirection �� MoveRange ���� ������
// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DistanceMovingPlatform.generated.h"

UCLASS()
class HW_07_08_API ADistanceMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADistanceMovingPlatform();

private:
	//������ �����Ϳ��� ���� �Ұ�, �ܺο����� ���� �Ұ�
	FVector MoveDirection = FVector(0.0f, 0.0f, 0.0f);	//������ ���� 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector StartLocation;	// ������ġ
	FVector CurrentLocation; // ���� ��ġ
	float DistanceMoved;	// �̵��� �Ÿ�
	


	UPROPERTY(EditAnywhere, Category = "DistanceMovingPlatform")
	FVector MoveVelocity;	//�ӵ� 
	

	UPROPERTY(EditAnywhere, Category = "DistanceMovingPlatform")
	float MoveDistance = 100.0f; // �̵��� �Ÿ�

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "DistanceMovingPlatform")
	UStaticMeshComponent* StaticMeshComp;	//������ �޽� ������Ʈ ����
};
