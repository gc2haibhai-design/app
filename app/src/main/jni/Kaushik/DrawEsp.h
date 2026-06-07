struct sRegion
{
	uintptr_t start, end;
};

std::vector<sRegion> trapRegions;

bool isEqual(std::string s1, const char* check) {
    std::string s2(check);
    return (s1 == s2);
}

bool isObjectInvalid(UObject *obj)
{
	if (!Tools::IsPtrValid(obj))
	{
		return true;
	}
	if (!Tools::IsPtrValid(obj->ClassPrivate))
	{
		return true;
	}
	if (obj->InternalIndex <= 0)
	{
		return true;
	}
	if (obj->NamePrivate.ComparisonIndex <= 0)
	{
		return true;
	}
	if ((uintptr_t)(obj) % sizeof(uintptr_t) != 0x0 && (uintptr_t)(obj) % sizeof(uintptr_t) != 0x4)
	{
		return true;
	}
	if (std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t)obj) >= region.start && ((uintptr_t)obj) <= region.end; }) ||
		std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t)obj->ClassPrivate) >= region.start && ((uintptr_t)obj->ClassPrivate) <= region.end; }))
	{
		return true;
	}
	return false;
}

std::string getObjectPath(UObject *Object) {
    std::string s;
    for (auto super = Object->ClassPrivate; super; super = (UClass *) super->SuperStruct) {
        if (!s.empty())
            s += ".";
        s += super->GetName();
    }
    return s;
}


UObject *GetObjectByClass(UClass *Class, bool Default)
{
    auto objects = UObject::GetGlobalObjects();
    const std::string defaultStr = "Default";

    for (int i = 0; i < objects.Num(); i++)
    {
        auto object = objects.GetByIndex(i);
        if (!object || !object->IsA(Class))
        {
            continue;
        }

        auto objectName = object->GetFullName();
        bool hasDefault = objectName.find(defaultStr) != std::string::npos;

        if ((Default && hasDefault) || (!Default && !hasDefault))
        {
            return object;
        }
    }
    return nullptr;
}

UWorld *GEWorld;
int GWorldNum = 0;
TUObjectArray gobjects;
UWorld *GetFullWorld()
{
    if(GWorldNum == 0) {
        gobjects = UObject::GUObjectArray->ObjObjects;
        for (int i=0; i< gobjects.Num(); i++)
            if (auto obj = gobjects.GetByIndex(i)) {
                if(obj->IsA(UEngine::StaticClass())) {
                    auto GEngine = (UEngine *) obj;
                    if(GEngine) {
                        auto ViewPort = GEngine->GameViewport;
                        if (ViewPort)
                        {
                            GEWorld = ViewPort->World;
                            GWorldNum = i;
                            if (!GEWorld || !GEWorld->NetDriver) {
                              g_LocalPlayer = nullptr;
                              g_LocalController = nullptr;
                              return nullptr;
                              }
                            return ViewPort->World;
                        }
                    }
                }
            }
    }else {
        auto GEngine = (UEngine *) (gobjects.GetByIndex(GWorldNum));
        if(GEngine) {
            auto ViewPort = GEngine->GameViewport;
            if(ViewPort) {
                GEWorld = ViewPort->World;
                                            if (!GEWorld || !GEWorld->NetDriver) {
                              g_LocalPlayer = nullptr;
                              g_LocalController = nullptr;
                              return nullptr;
                              }
                return ViewPort->World;
            }
        }
    }
    return 0;
}


std::vector<AActor *> GetNecessaryActors() {
    auto World = GetFullWorld();
    if (!World)
    return std::vector<AActor *>();
    auto PersistentLevel = World->PersistentLevel;
    if (!PersistentLevel)
    return std::vector<AActor *>();
    struct GovnoArray {
    uintptr_t base;
    int32_t count;
    int32_t max;
    };
    static thread_local GovnoArray Actors{};
    Actors = *(((GovnoArray*(*)(uintptr_t))(UE4 + GetActorArray_Offset))(reinterpret_cast<uintptr_t>(PersistentLevel)));
    if (Actors.count <= 0) {
    return {};
    }
    std::vector<AActor *> actors;
    for (int i = 0; i < Actors.count; i++) {
    auto Actor = *(uintptr_t *) (Actors.base + (i * sizeof(uintptr_t)));
    if (Actor) {
    actors.push_back(reinterpret_cast<AActor *const>(Actor));
    }
    }
  return actors;
}



TNameEntryArray *GetGNames()
{
	return ((TNameEntryArray * (*)()) (UE4 + GNames_Offset))();
}

template <class T>
void GetAllActors(std::vector<T *> &Actors)
{
	UGameplayStatics *gGameplayStatics = (UGameplayStatics *)gGameplayStatics->StaticClass();
	auto GWorld = GetFullWorld();
	if (GWorld)
	{
		TArray<AActor *> Actors2;
		gGameplayStatics->GetAllActorsOfClass((UObject *)GWorld, T::StaticClass(), &Actors2);
		for (int i = 0; i < Actors2.Num(); i++)
		{
			Actors.push_back((T *)Actors2[i]);
		}
	}
}

bool WriteAddr(void *addr, void *buffer, size_t length) {
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long size = page_size * sizeof(uintptr_t);
    return mprotect((void *) ((uintptr_t) addr - ((uintptr_t) addr % page_size) - page_size), (size_t) size, PROT_EXEC | PROT_READ | PROT_WRITE) == 0 && memcpy(addr, buffer, length) != 0;
}

template<typename T>
void Write(uintptr_t addr, T value) {
    WriteAddr((void *) addr, &value, sizeof(T));
}

int Write_Float(long int addr, float value) {
    Tools::WriteAddr((void *) (addr), (void *) &value, 4);
    return 0;
}


#define CREATE_COLOR(r, g, b, a) new float[4] {(float)r, (float)g, (float)b, (float)a};

int32_t ToColor(float *col) {
    return ImGui::ColorConvertFloat4ToU32(*(ImVec4 *) (col));
}

FVector GetBoneLocationByName(ASTExtraPlayerCharacter *Actor, const char *BoneName)
{
	return Actor->GetBonePos(BoneName, FVector());
}


