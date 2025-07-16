// 회전을 하는 플랫폼

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

	UPROPERTY(EditAnywhere, Category="RotationPlatform")	// 회전 속도를 에디터에서 변화주기 편하게 하기 위함
	FRotator RotationSpeed;		// 회전 속도 초기값은 0,0,0

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "StaticMeshComponent");
	UStaticMeshComponent* StaticMeshComp;
	
};
