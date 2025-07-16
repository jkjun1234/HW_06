// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationMovingPlatform.h"

// Sets default values
ARotationMovingPlatform::ARotationMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//스태틱 메시 컴포넌트 생성
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComp);	// 루트 컴포넌트를 StaticMeshComp로 지정
}

// Called when the game starts or when spawned
void ARotationMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotationMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(RotationSpeed*DeltaTime);	// 액터 회전
}

