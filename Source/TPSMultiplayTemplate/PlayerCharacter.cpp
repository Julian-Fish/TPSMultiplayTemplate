//---------------------------------------------------------------------------------
// ファイル		：PlayerCharacter.cpp
// 概要			：キャラ作成
// 作成者		：19CU0236 林雲暉
// 作成日		：2021/05/02
// 更新日		：
//---------------------------------------------------------------------------------


#include "PlayerCharacter.h"
#include "BallProjectile.h"
#include "Camera/CameraComponent.h"
#include "Sound/SoundClass.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine.h"
#include "Components/ArrowComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
	: playerStaticMesh(NULL)
	, ThirdPersonSpringArm(NULL)
	, attackMode(0)
	, onClickFire(false)
	, isShooting(false)
	, bowChargeTime(0.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(150.f, 300.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 10.f;

	// スプリングアームのオブジェクトを生成
	ThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonSpringArm"));
	
	// スプリングアームにRootComponentをアタッチ
	ThirdPersonSpringArm->SetupAttachment(RootComponent);

	// カメラとプレイヤーの距離
	ThirdPersonSpringArm->TargetArmLength = 450.f;

	// カメラの子リジョンテストを行うかを設定
	ThirdPersonSpringArm->bDoCollisionTest = false;

	// カメラ追従ラグを使うかを設定
	ThirdPersonSpringArm->bEnableCameraLag = false;


	// Create a CameraComponent	
	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCameraComponent->SetupAttachment(ThirdPersonSpringArm);
	ThirdPersonCameraComponent->SetRelativeLocation(FVector(-500.f, 0.f, 500.f)); // Position the camera
	ThirdPersonCameraComponent->bUsePawnControlRotation = true;

	// 角色Static Mesh
	playerStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("playerStaticMesh"));
	playerStaticMesh->SetupAttachment(RootComponent);


	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	//Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	//Mesh1P->SetOnlyOwnerSee(true);
	//Mesh1P->SetupAttachment(ThirdPersonCameraComponent);
	//Mesh1P->bCastDynamicShadow = false;
	//Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	//Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	//FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	//FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	//FP_Gun->bCastDynamicShadow = false;
	//FP_Gun->CastShadow = false;
	//// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	//FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(RootComponent);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	ArcDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("ArcDirection"));
	ArcSpline = CreateDefaultSubobject<USplineComponent>(TEXT("ArcSpline"));
	ArcEndPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArcEndPoint"));


}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	UCharacterMovementComponent* pCharMoveComp = GetCharacterMovement();
	if (pCharMoveComp != NULL)
	{
		pCharMoveComp->JumpZVelocity = 600.f;
	} // end if()

	this->SetActorScale3D(FVector(0.3f, 0.3f, 0.3f));

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (onClickFire == true)
	{
		bowChargeTime += DeltaTime;
	} // end if()
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::FirePressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::OnFire);


}


void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

// 曲線射撃模擬
void APlayerCharacter::TraceArcSimulationCVer(float targetDistance, FVector targetLocation)
{





} // void TraceArcSimulationCVer()

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::FirePressed()
{
	onClickFire = true;
} // void FirePressed()

void APlayerCharacter::OnFire()
{
	if (onClickFire == true)
	{
		if (attackMode == 0)
		{
			// try and fire a projectile
			if (ProjectileClass != NULL)
			{
				UWorld* const World = GetWorld();
				if (World != NULL)
				{
					// Debug用
					// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("===== %s"), *GetActorLocation().ToString()));

					const FRotator SpawnRotation = GetControlRotation();
					// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
					// const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
					const FVector SpawnLocation = ( GetActorLocation() + FVector(0.f, 0.f, 100.f));

					// Set Spawn Collision Handling Override
					FActorSpawnParameters ActorSpawnParams;
					ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

					// Spawn the projectile at the muzzle
					World->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
					
				} // end if()
			} // end if()

			//// try and play the sound if specified
			//if (FireSound != NULL)
			//{
			//	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			//}

			//// try and play a firing animation if specified
			//if (FireAnimation != NULL)
			//{
			//	// Get the animation object for the arms mesh
			//	UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			//	if (AnimInstance != NULL)
			//	{
			//		AnimInstance->Montage_Play(FireAnimation, 1.f);
			//	}
			//}
		} // end if()
	} // end if()

	onClickFire = false;
	bowChargeTime = 0.f;

} // void OnFire()

// デストラクタ
APlayerCharacter::~APlayerCharacter()
{

}
