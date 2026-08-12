
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlashCharacter.generated.h"
class USpringArmComponent;
class UCameraComponent;
class AItem;
class UAnimMontage;
class AWeapon;
UENUM(BlueprintType)
enum class ECharacterState :UINT8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_EquippedOneHandedWeapon UMETA(DisplayName = "Equipped One-Handed Weapon"),
	ECS_EquippedTwoHandedWeapon UMETA(DisplayName = "Equipped Two-Handed Weapon")

};
UENUM(BlueprintType)
enum class EActionState :UINT8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	EAS_EquippingWeapon UMETA(DisplayName = "Equipping Weapon")
};
UCLASS()
class FIRSTSLASH_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
protected:
	virtual void BeginPlay() override;
	//Callbacks for input
	void MoveForward(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void MoveRight(float Value);
	void EKeyPressed();
	void Attack();
	//play montage functions
	void PlayAttackMontage();
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	bool CanAttack();
	void PlayEquipMontage(FName SectionName);
	bool CanDisarm();
	bool CanArm();
	UPROPERTY(BlueprintReadWrite)
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	UPROPERTY(BlueprintReadWrite)
	EActionState ActionState = EActionState::EAS_Unoccupied;
	//Animation Montages
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AttackMontage;
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* EquipMontage;
	UPROPERTY(BlueprintReadOnly)
	AWeapon* EquippedWeapon;
	UFUNCTION(BlueprintCallable)
	void Disarm();
	UFUNCTION(BlueprintCallable)
	void Arm();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();


private:


	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraView;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

};
