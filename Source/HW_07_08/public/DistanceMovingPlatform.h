// Target 위치까지 왔다 갔다 하는 플랫폼
// 시작 위치 -> MoveSpeed*Movedirection 로 MoveRange 까지 움직임
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
	//방향은 에디터에서 수정 불가, 외부에서도 수정 불가
	FVector MoveDirection = FVector(0.0f, 0.0f, 0.0f);	//움직일 방향 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector StartLocation;	// 시작위치
	FVector CurrentLocation; // 현재 위치
	float DistanceMoved;	// 이동한 거리
	


	UPROPERTY(EditAnywhere, Category = "DistanceMovingPlatform")
	FVector MoveVelocity;	//속도 
	

	UPROPERTY(EditAnywhere, Category = "DistanceMovingPlatform")
	float MoveDistance = 100.0f; // 이동할 거리

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "DistanceMovingPlatform")
	UStaticMeshComponent* StaticMeshComp;	//움직일 메쉬 컴포넌트 선언
};
