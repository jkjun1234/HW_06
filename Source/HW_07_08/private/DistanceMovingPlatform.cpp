// Target ��ġ���� �Դ� ���� �ϴ� �÷���

#include "DistanceMovingPlatform.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ADistanceMovingPlatform::ADistanceMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//����ƽ �޽� ������Ʈ ���� �� ��Ʈ������Ʈ�� ����
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComp);

	//�̵��� �Ÿ�
	DistanceMoved = 0;
}

// Called when the game starts or when spawned
void ADistanceMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	//������, ������ġ �ʱ�ȭ
	StartLocation = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("StartLocation : %s "), *StartLocation.ToString())	// ���� ��ġ Ȯ�� �α�
	CurrentLocation = StartLocation;
	MoveDirection = MoveVelocity.GetSafeNormal();	// �̵� �ʱ� ���� ���ϱ�

	// ������ ������ ���� �� �ش� ���͸� ���밪���� �ٲ� ���� ��ġ �� ������Ʈ �� ���� ���� * Velocity�� ������������
	MoveVelocity = FVector(
		FMath::Abs(MoveVelocity.X),
		FMath::Abs(MoveVelocity.Y),
		FMath::Abs(MoveVelocity.Z)	
		);	// �̵� �ӵ��� ���밪���� ����
}

// Called every frame
void ADistanceMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);	// �̵��� �Ÿ� ���ϱ�

	if (DistanceMoved >= MoveDistance)	// �̵��� �Ÿ��� �̵��� �Ÿ����� ũ�ų� ������~ 
	{
		// �������� �̵��� �Ÿ� �������� ������Ʈ
				         //0,0,0		0,0,-1          1500
		StartLocation = StartLocation + (MoveDirection * MoveDistance);

		// ���� ��ȯ
		MoveDirection = MoveDirection * (-1);
	}
			             // -1           0,0,500
	CurrentLocation += (MoveDirection * MoveVelocity * DeltaTime);	// ���� ��ġ ������Ʈ
	SetActorLocation(CurrentLocation);
}

