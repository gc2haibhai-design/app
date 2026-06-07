std::unordered_set<std::string> dumpedPickups;     // Pickup names
std::unordered_set<std::string> dumpedAllPickups;  // All pickup names (full list)
std::unordered_set<std::string> dumpedGrenades;    // Grenade names
std::unordered_set<int> dumpedItemIDs;             // Item IDs
std::unordered_set<std::string> dumpedAllVehicles;    // All Vehicles

if (Actor->IsA(APickUpWrapperActor::StaticClass())) {
        auto PickUp = (APickUpWrapperActor*)Actor;
        if (!PickUp->RootComponent) return;

        std::string className = PickUp->GetName();
        if (dumpedPickups.find(className) == dumpedPickups.end()) {
            dumpedPickups.insert(className);
            std::string logLine = "[Pickup] " + className;
            logToFile("Pickups.txt", logLine.c_str());
        }
    }


// Dump *all* unique pickups list (separate file)
// DumpAllPickupsList(AActor *Actor) {
    if (Actor->IsA(APickUpWrapperActor::StaticClass())) {
        auto PickUp = (APickUpWrapperActor*)Actor;
        if (!PickUp->RootComponent) return;

        std::string className = PickUp->GetName();
        if (dumpedAllPickups.find(className) == dumpedAllPickups.end()) {
            dumpedAllPickups.insert(className);
            std::string logLine = "[PickupList] " + className;
            logToFile("AllPickups.txt", logLine.c_str());
        }
    }


// Dump unique grenade name
// DumpAllGrenades(AActor *Actor) {
    if (Actor->IsA(ASTExtraGrenadeBase::StaticClass())) {
        auto Throw = (ASTExtraGrenadeBase *)Actor;
        if (!Actor->RootComponent) return;

        std::string className = Throw->GetName();
        if (dumpedGrenades.find(className) == dumpedGrenades.end()) {
            dumpedGrenades.insert(className);
            std::string logLine = "[Grenade] " + className;
            logToFile("Grenades.txt", logLine.c_str());
        }
    }


// For storing dumped item names
std::unordered_set<std::string> dumpedAllItems;

// Dump unique item name into Items.txt
//void DumpAllItems(AActor *Actor) {
    if (Actor->IsA(APickUpWrapperActor::StaticClass())) {
        auto PickUp = (APickUpWrapperActor*)Actor;
        if (!PickUp->RootComponent) return;

        std::string className = PickUp->GetName();
        if (dumpedAllItems.find(className) == dumpedAllItems.end()) {
            dumpedAllItems.insert(className);

            std::string logLine = "[Item] " + className;
            logToFile("Items.txt", logLine.c_str()); // Writing to Items.txt
        }
    }
    
  if (Actor->IsA(ASTExtraVehicleBase::StaticClass())) {
    auto Vehicle = (ASTExtraVehicleBase*)Actor;
    if (!Vehicle->Mesh) return;

    std::string className = Vehicle->GetName();
    if (dumpedAllVehicles.find(className) == dumpedAllVehicles.end()) {
        dumpedAllVehicles.insert(className);
        std::string logLine = "[VehicleList] " + className;
        logToFile("AllVehicles.txt", logLine.c_str());
    }
}