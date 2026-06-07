FRotator ToRotator(FVector local, FVector target) {
FVector rotation = UKismetMathLibrary::Subtract_VectorVector(local, target);

float hyp = sqrt(rotation.X * rotation.X + rotation.Y * rotation.Y);

FRotator newViewAngle = {0};
newViewAngle.Pitch = -atan(rotation.Z / hyp) * (180.f / (float) 3.14159265358979323846);
newViewAngle.Yaw = atan(rotation.Y / rotation.X) * (180.f / (float) 3.14159265358979323846);
newViewAngle.Roll = (float) 0.f;

if (rotation.X >= 0.f)
newViewAngle.Yaw += 180.0f;

return newViewAngle;
}

int GetIndex(int currentIndex, int arrayNum) {
    if (arrayNum <= 0) {
        return 0;
    }
    return (currentIndex + 1) % arrayNum;
}

void clampAngles(FRotator &angles)
{
    if (angles.Pitch > 180)
        angles.Pitch -= 360;
    if (angles.Pitch < -180)
        angles.Pitch += 360;
    if (angles.Pitch < -75.f)
        angles.Pitch = -75.f;
    else if (angles.Pitch > 75.f)
        angles.Pitch = 75.f;
    while (angles.Yaw < -180.0f)
        angles.Yaw += 360.0f;
    while (angles.Yaw > 180.0f)
        angles.Yaw -= 360.0f;
}


FRotator VectorToRotator(FVector rotation) {
    float hyp = sqrt(rotation.X * rotation.X + rotation.Y * rotation.Y);
    FRotator newViewAngle = {0};
    newViewAngle.Pitch = -atan(rotation.Z / hyp) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Yaw = atan(rotation.Y / rotation.X) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Roll = (float) 0.f;
    if (rotation.X >= 0.f)
        newViewAngle.Yaw += 180.0f;
    return newViewAngle;
}

FQuat RotatorToQuat(FRotator rotator) {
    // Convert degrees to radians
    float DEG_TO_RAD = (float)(3.14159265358979323846 / 180.f);
    
    float pitch = rotator.Pitch * DEG_TO_RAD * 0.5f;
    float yaw = rotator.Yaw * DEG_TO_RAD * 0.5f;
    float roll = rotator.Roll * DEG_TO_RAD * 0.5f;

    float sinPitch = sin(pitch);
    float cosPitch = cos(pitch);
    float sinYaw = sin(yaw);
    float cosYaw = cos(yaw);
    float sinRoll = sin(roll);
    float cosRoll = cos(roll);

    FQuat quat;
    quat.X = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
    quat.Y = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
    quat.Z = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;
    quat.W = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;

    return quat;
}



FVector CalculateWeaponMuzzlePosition(const FVector& weaponLocation, const FRotator& weaponRotation, float weaponBodyLength) {

    float radPitch = weaponRotation.Pitch * (3.14159265358979323846 / 180.0f);
    float radYaw = weaponRotation.Yaw * (3.14159265358979323846 / 180.0f);


    float forwardX = std::cos(radPitch) * std::cos(radYaw);
    float forwardY = std::cos(radPitch) * std::sin(radYaw);
    float forwardZ = std::sin(radPitch);


    FVector muzzlePosition = {
        weaponLocation.X + forwardX * weaponBodyLength,
        weaponLocation.Y + forwardY * weaponBodyLength,
        weaponLocation.Z + forwardZ * weaponBodyLength
    };

    return muzzlePosition;
}


auto GetTargetByPussy() {
    ASTExtraPlayerCharacter *result = 0;
    float max = std::numeric_limits<float>::infinity();
    auto Actors = GetNecessaryActors();
    auto localPlayer = g_LocalPlayer;
    auto localController = g_LocalController;
   
    FVector ViewPosY{0, 0, 0};
    if (localPlayer)
    {
        ViewPosY = localPlayer->GetBonePos("Head", {});
        ViewPosY.Z += -15.0f;
    }
    
    if (localPlayer)
    {
        for (int i = 0; i < Actors.size(); i++)
        {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())){

                auto Player = (ASTExtraPlayerCharacter *)Actor;
              
                float Distance = localPlayer->GetDistanceTo(Player) / 100.0f;

                if (Distance > KaushikSettings::BtDis)
                    continue;

                if (Player->PlayerKey == localPlayer->PlayerKey)
                    continue;

                if (Player->TeamID == localPlayer->TeamID)
                    continue;

                if (Player->bDead)
                    continue;

                if (Player->bHidden)
                    continue;

                if (!g_LocalController->LineOfSightTo(
                        g_LocalController->PlayerCameraManager,
                        Player->GetBonePos("Head", {0, 0, 0}),
                        false))
                {
                    continue;
                }
                
           /*    if (KaushikSettings::BulletTrack)
{
    auto CurrentWeaponReplicated = (ASTExtraShootWeapon*)
        g_LocalPlayer->WeaponManagerComponent->CurrentWeaponReplicated;

    if (CurrentWeaponReplicated && Player)
    {
        int WeaponId = CurrentWeaponReplicated
            ->WeaponEntityComp->WeaponId;

        // Weapon filter (2nd code wala)
        if (WeaponId != 602001 && WeaponId != 602002 &&
            WeaponId != 602003 && WeaponId != 602004 &&
            WeaponId != 0)
        {
            FVector WeaponLocation =
                CurrentWeaponReplicated->K2_GetActorLocation();

            FRotator WeaponRotation =
                CurrentWeaponReplicated->K2_GetActorRotation();

            float WeaponLength =
                CurrentWeaponReplicated->GetWeaponBodyLength();

            FVector MuzzlePosition =
                CalculateWeaponMuzzlePosition(
                    WeaponLocation,
                    WeaponRotation,
                    WeaponLength / 1.5f
                );

            // Muzzle LOS check
            if (!localController->LineOfSightTo(Player, MuzzlePosition, true))
                continue;
        }
        else
        {
            // Fallback LOS
            if (!localController->LineOfSightTo(Player, FVector(0, 0, 0), true))
                continue;
        }
    }
}*/
                

                auto Root = Player->GetBonePos("Root", {0, 0, 0});
                auto Head = Player->GetBonePos("Head", {0, 0, 0});

                FVector2D RootSc, HeadSc;
                if (W2S(Root, &RootSc) && W2S(Head, &HeadSc)) {
                    float height = abs(HeadSc.Y - RootSc.Y);
                    float width = height * 0.65f;

                    FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2), 0};
                    if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) &&
                        (middlePoint.Y >= 0 && middlePoint.Y <= glHeight)) {

                        FVector2D v2Middle(glWidth / 2.0f, glHeight / 2.0f);
                        FVector2D v2Loc(middlePoint.X, middlePoint.Y);

                        float dist = FVector2D::Distance(v2Middle, v2Loc);

                        if (dist < max) {
                            max = dist;
                            result = Player;
                        }
                    }
                }
            }
        }
    }
    return result;
}


float Random[11] = {0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.9f, 2.0f};
void (*BulletInner)(uintptr_t Weapon, FVector StartLoc, FRotator StartRot, int ShootID);
void xBulletInner(uintptr_t Weapon, FVector StartLoc, FRotator StartRot, int ShootID)
{
    if (!KaushikSettings::BulletTrack) {
        return BulletInner(Weapon, StartLoc, StartRot, ShootID);
    }

    auto Target = GetTargetByPussy();
    if (!Target) {
        return BulletInner(Weapon, StartLoc, StartRot, ShootID);
    }

    FVector targetAimPos = Target->GetBonePos("Head", {});

    auto WeaponManagerComponent = g_LocalPlayer->WeaponManagerComponent;
    if (!WeaponManagerComponent) {
        return BulletInner(Weapon, StartLoc, StartRot, ShootID);
    }

    auto CurrentWeaponReplicated = (ASTExtraShootWeapon*)WeaponManagerComponent->CurrentWeaponReplicated;
    if (!CurrentWeaponReplicated) {
        return BulletInner(Weapon, StartLoc, StartRot, ShootID);
    }

    float distance = g_LocalPlayer->GetDistanceTo(Target);
    float BulletFireSpeed = CurrentWeaponReplicated->GetBulletFireSpeedFromEntity();

    if (BulletFireSpeed < 1.0f) BulletFireSpeed = 1.0f;

    float timeToTravel = distance / BulletFireSpeed;

    FVector LinearVelocity = Target->CurrentVehicle
        ? Target->CurrentVehicle->ReplicatedMovement.LinearVelocity
        : Target->GetVelocity();

    FVector Velocity = UKismetMathLibrary::Multiply_VectorFloat(LinearVelocity, timeToTravel * 0.9f);
    targetAimPos.X += Velocity.X;
    targetAimPos.Y += Velocity.Y;
    targetAimPos.Z += Velocity.Z;

    targetAimPos.Z += 3.5f;

    static int index = 0;
    index = GetIndex(index, 11);
    float Smoothing = Random[index];

    FRotator gunRotation = StartRot;
    FRotator aimRotation = ToRotator(StartLoc, targetAimPos);

    aimRotation.Pitch -= gunRotation.Pitch;
    aimRotation.Yaw -= gunRotation.Yaw;
    aimRotation.Roll = 0.0f;

    clampAngles(aimRotation);

     #include <algorithm> 
    aimRotation.Pitch = std::max(-89.0f, std::min(89.0f, aimRotation.Pitch));
    aimRotation.Yaw   = std::max(-180.0f, std::min(180.0f, aimRotation.Yaw));

    gunRotation.Pitch += aimRotation.Pitch / Smoothing;
    gunRotation.Yaw += aimRotation.Yaw / Smoothing;
    gunRotation.Roll = 0.0f;
    

    return BulletInner(Weapon, StartLoc, gunRotation, ShootID);
}
/*

void (*BulletInner)(uintptr_t Weapon, FVector StartLoc, FRotator StartRot, int ShootID);
void xBulletInner(uintptr_t Weapon, FVector StartLoc, FRotator StartRot, int ShootID)
{
    if (KaushikSettings::BulletTrack) {
        ASTExtraPlayerCharacter* Target = GetTargetByPussy();
    if (Target != 0)
    {
        FVector targetAimPos = Target->GetBonePos("neck_01", {});
        if (auto WeaponManagerComponent = g_LocalPlayer->WeaponManagerComponent)
        {
            if (auto CurrentWeaponReplicated = (ASTExtraShootWeapon*)WeaponManagerComponent->CurrentWeaponReplicated)
            {

                float distance = g_LocalPlayer->GetDistanceTo(Target);
                float BulletFireSpeed = CurrentWeaponReplicated->GetBulletFireSpeedFromEntity();
                float timeToTravel = distance / BulletFireSpeed;
                auto CurrentVehicle = Target->CurrentVehicle;

                if (CurrentVehicle)
                {
                    FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;
FVector Velocity= UKismetMathLibrary::Multiply_VectorFloat(LinearVelocity, timeToTravel);
                    targetAimPos = targetAimPos + Velocity;
                }
                else
                {
                    FVector LinearVelocity = Target->GetVelocity();
FVector Velocity= UKismetMathLibrary::Multiply_VectorFloat(LinearVelocity, timeToTravel);
                    targetAimPos = targetAimPos + Velocity;
                }
                static int index = 0;
                index = GetIndex(index, 11);
                float Smoothing = Random[index];
                FRotator gunrotaton = StartRot;
                FRotator aimrotation = ToRotator(StartLoc, targetAimPos);
                aimrotation.Pitch -= gunrotaton.Pitch;
                aimrotation.Yaw -= gunrotaton.Yaw;
                aimrotation.Roll = 0.0f;
                clampAngles(aimrotation);
                gunrotaton.Pitch += aimrotation.Pitch / Smoothing;
                gunrotaton.Yaw += aimrotation.Yaw / Smoothing;
                gunrotaton.Roll = 0.0f;
                return BulletInner(Weapon, StartLoc, gunrotaton, ShootID);
            }
        }
    }
}
    return BulletInner(Weapon, StartLoc, StartRot, ShootID);
}*/