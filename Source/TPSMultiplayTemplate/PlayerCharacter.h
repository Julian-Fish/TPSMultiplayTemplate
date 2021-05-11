//---------------------------------------------------------------------------------
// ファイル		：PlayerCharacter.h
// 概要			：キャラ作成
// 作成者		：19CU0236 林雲暉
// 作成日		：2021/05/02
// 更新日		：
//
// Function & 變數 導入網路後 權限可能要調整
//  
//---------------------------------------------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class TPSMULTIPLAYTEMPLATE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	// 角色Static Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* playerStaticMesh;

	// 角色骨骼 Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	// Gun mesh
	class USkeletalMeshComponent* FP_Gun;


	// 弾の生成場所
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* FP_MuzzleLocation;

	// プレイヤーのカメラ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* ThirdPersonCameraComponent;

	// スプリングアーム
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* ThirdPersonSpringArm;

	// Projectile class to spawn
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABallProjectile> ProjectileClass;

	//// 射擊時的聲音
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//	class USoundBase* FireSound;

	//// 射擊動作
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//	class UAnimMontage* FireAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Spline", meta = (AllowPrivateAccess = "true"))
		class UStaticMesh* BeamMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Spline", meta = (AllowPrivateAccess = "true"))
		class UMaterial* BeamMaterial;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Variables", meta = (AllowPrivateAccess = "true"))
		float CurveModeFireRange;				// 曲線射撃最大距離




public:
	// コンストラクタ
	APlayerCharacter();

	// デストラクタ
	~APlayerCharacter();

protected:
	// 実行時に一度呼ばれる
	virtual void BeginPlay() override;

public:
	// 毎フレーム呼ばれる
	virtual void Tick(float DeltaTime) override;

	// 各入力関係メソッドとのバインド処理
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	// 基礎左右回転比率(deg/sec)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	// 基礎上下回転比率(deg/sec)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	// 武器の先端部位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;

	/** Projectile class to spawn */
	//UPROPERTY(EditDefaultsOnly, Category = Projectile)
	//	TSubclassOf<class ABalloonFPSProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	// 攻撃アニメーション
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Variables", meta = (AllowPrivateAccess = "true"))
		TArray<class USplineMeshComponent*> SplineMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Components", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* ArcDirection;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Components", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ArcEndPoint;


	void FirePressed();

	// 弾を撃つ
	void OnFire();

	// 前後移動
	void MoveForward(float Val);

	// 左右移動
	void MoveRight(float Val);

	// 拋射模擬
	void TraceArcSimulationCVer(float targetDistance, FVector targetLocation);


	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// 變數之後可能要移動
	int attackMode;					// 暫訂 0一般  1高空  2 item
	bool onClickFire;
	bool isShooting;
	float bowChargeTime;


public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns ThirdPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetThirdPersonCameraComponent() const { return ThirdPersonCameraComponent; }


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Components", meta = (AllowPrivateAccess = "true"))
		class USplineComponent* ArcSpline;

};
