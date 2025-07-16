// Target 위치까지 왔다 갔다 하는 플랫폼

#include "DistanceMovingPlatform.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ADistanceMovingPlatform::ADistanceMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//스태틱 메쉬 컴포넌트 생성 후 루트컴포넌트로 설정
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComp);

	//이동한 거리
	DistanceMoved = 0;
}

// Called when the game starts or when spawned
void ADistanceMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	//시작점, 현재위치 초기화
	StartLocation = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("StartLocation : %s "), *StartLocation.ToString())	// 시작 위치 확인 로그
	CurrentLocation = StartLocation;
	MoveDirection = MoveVelocity.GetSafeNormal();	// 이동 초기 방향 구하기

	// 벡터의 방향을 구한 후 해당 벡터를 절대값으로 바꿔 현재 위치 값 업데이트 시 순수 방향 * Velocity만 곱해지기위함
	MoveVelocity = FVector(
		FMath::Abs(MoveVelocity.X),
		FMath::Abs(MoveVelocity.Y),
		FMath::Abs(MoveVelocity.Z)	
		);	// 이동 속도는 절대값으로 설정
}

// Called every frame
void ADistanceMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);	// 이동한 거리 구하기

	if (DistanceMoved >= MoveDistance)	// 이동한 거리가 이동할 거리보다 크거나 같으면~ 
	{
		// 시작점을 이동한 거리 지점으로 업데이트
				         //0,0,0		0,0,-1          1500
		StartLocation = StartLocation + (MoveDirection * MoveDistance);

		// 방향 전환
		MoveDirection = MoveDirection * (-1);
	}
			             // -1           0,0,500
	CurrentLocation += (MoveDirection * MoveVelocity * DeltaTime);	// 현재 위치 업데이트
	SetActorLocation(CurrentLocation);
}

