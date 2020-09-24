// Fill out your copyright notice in the Description page of Project Settings.


#include "TileMap.h"

// Sets default values
ATileMap::ATileMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	StartX = RootComponent->GetComponentLocation().X - (100 * Row / 2);
	StartY = RootComponent->GetComponentLocation().Y - (100 * Column / 2);
	StartZ = RootComponent->GetComponentLocation().Z;

	CurrentTileLocation = FVector(StartX, StartY, StartZ);	
}

// Called when the game starts or when spawned
void ATileMap::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	FActorSpawnParameters spawnParms;

	if (world)
	{
		for (int c = 0; c < Column; c++)
		{
			for (int r = 0; r < Row; r++)
			{

				//Grid.Add(NewObject<ATile>(this, ATile::StaticClass()));
				Grid.Add(world->SpawnActor<ATile>(ATile::StaticClass(), CurrentTileLocation, FRotator(0.f, 0.f, 0.f), spawnParms));

				CurrentTileLocation.X += 100;

				if (r % 2 == 0)
					Grid.Last()->Hazzard = true;

				else if (r % 7 == 0)
					Grid.Last()->Obstacle = true;
			
			}
			
			CurrentTileLocation.X = StartX;
			CurrentTileLocation.Y += 100;
		}
	}
}

// Called every frame
void ATileMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

