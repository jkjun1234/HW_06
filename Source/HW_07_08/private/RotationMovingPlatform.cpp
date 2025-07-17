// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationMovingPlatform.h"

ARotationMovingPlatform::ARotationMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	
	//����ƽ �޽� ������Ʈ ����
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComp);	// ��Ʈ ������Ʈ�� StaticMeshComp�� ����
}

void ARotationMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARotationMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(RotationSpeed*DeltaTime);	// ���� ȸ��
}

