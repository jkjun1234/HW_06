// ȸ���� �ϴ� �÷���

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotationMovingPlatform.generated.h"

UCLASS()
class HW_07_08_API ARotationMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotationMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="RotationPlatform")	// ȸ�� �ӵ��� �����Ϳ��� ��ȭ�ֱ� ���ϰ� �ϱ� ����
	FRotator RotationSpeed;		// ȸ�� �ӵ� �ʱⰪ�� 0,0,0

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "StaticMeshComponent");
	UStaticMeshComponent* StaticMeshComp;
	
};
