// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationMovingPlatform.h"

ARotationMovingPlatform::ARotationMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	
	//스태틱 메시 컴포넌트 생성
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComp);	// 루트 컴포넌트를 StaticMeshComp로 지정
}

void ARotationMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARotationMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(RotationSpeed*DeltaTime);	// 액터 회전
}

