void RestartAppJNI()
{
    if (!g_App || !g_App->activity || !g_App->activity->vm)
        return;

    JavaVM* vm = g_App->activity->vm;
    JNIEnv* env = nullptr;
    bool detach = false;

    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK)
    {
        if (vm->AttachCurrentThread(&env, nullptr) != JNI_OK)
            return;
        detach = true;
    }

    jobject activity = g_App->activity->clazz;
    jclass activityClass = env->GetObjectClass(activity);

    // getPackageManager
    jmethodID getPM = env->GetMethodID(
        activityClass,
        "getPackageManager",
        "()Landroid/content/pm/PackageManager;"
    );
    jobject pm = env->CallObjectMethod(activity, getPM);

    // getPackageName
    jmethodID getPkg = env->GetMethodID(
        activityClass,
        "getPackageName",
        "()Ljava/lang/String;"
    );
    jstring pkgName = (jstring)env->CallObjectMethod(activity, getPkg);

    // getLaunchIntentForPackage
    jclass pmClass = env->GetObjectClass(pm);
    jmethodID getLaunchIntent = env->GetMethodID(
        pmClass,
        "getLaunchIntentForPackage",
        "(Ljava/lang/String;)Landroid/content/Intent;"
    );
    jobject intent = env->CallObjectMethod(pm, getLaunchIntent, pkgName);

    if (intent)
    {
        jclass intentClass = env->GetObjectClass(intent);

        jfieldID flagField = env->GetStaticFieldID(
            intentClass,
            "FLAG_ACTIVITY_NEW_TASK",
            "I"
        );
        jint flag = env->GetStaticIntField(intentClass, flagField);

        jmethodID addFlags = env->GetMethodID(
            intentClass,
            "addFlags",
            "(I)Landroid/content/Intent;"
        );
        env->CallObjectMethod(intent, addFlags, flag);

        jmethodID startActivity = env->GetMethodID(
            activityClass,
            "startActivity",
            "(Landroid/content/Intent;)V"
        );
        env->CallVoidMethod(activity, startActivity, intent);
    }

    // finish current activity
    jmethodID finish = env->GetMethodID(activityClass, "finish", "()V");
    env->CallVoidMethod(activity, finish);

    if (detach)
        vm->DetachCurrentThread();
}
bool IsPackageInstalled(JNIEnv* env, jobject activity, const char* packageName)
{
    jclass activityClass = env->GetObjectClass(activity);
    jmethodID getPM = env->GetMethodID(
        activityClass,
        "getPackageManager",
        "()Landroid/content/pm/PackageManager;"
    );
    jobject pm = env->CallObjectMethod(activity, getPM);

    jclass pmClass = env->GetObjectClass(pm);
    jmethodID getPkgInfo = env->GetMethodID(
        pmClass,
        "getPackageInfo",
        "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;"
    );

    jstring jPkg = env->NewStringUTF(packageName);
    jobject pkgInfo = env->CallObjectMethod(pm, getPkgInfo, jPkg, 0);

    bool installed = true;
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
        installed = false;
    }

    env->DeleteLocalRef(jPkg);
    env->DeleteLocalRef(pmClass);
    env->DeleteLocalRef(pm);
    env->DeleteLocalRef(activityClass);

    return installed;
}

int OpenURL(const char* username)
{
    if (!g_App || !g_App->activity || !g_App->activity->vm)
        return -1;

    JavaVM* vm = g_App->activity->vm;
    JNIEnv* env = nullptr;
    bool needDetach = false;

    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        if (vm->AttachCurrentThread(&env, nullptr) != JNI_OK)
            return -2;
        needDetach = true;
    }

    jobject activity = g_App->activity->clazz;

    // 🔥 Clean username (@ remove)
    std::string cleanUser = username ? username : "";
    if (!cleanUser.empty() && cleanUser[0] == '@')
        cleanUser.erase(0, 1);

    bool hasTelegram = IsPackageInstalled(env, activity, "org.telegram.messenger");

    std::string url;
    if (hasTelegram)
        url = "tg://resolve?domain=" + cleanUser;
    else
        url = "https://t.me/" + cleanUser;

    // Intent & Uri
    jclass intentClass = env->FindClass("android/content/Intent");
    jclass uriClass = env->FindClass("android/net/Uri");

    jmethodID parse = env->GetStaticMethodID(
        uriClass,
        "parse",
        "(Ljava/lang/String;)Landroid/net/Uri;"
    );

    jstring jUrl = env->NewStringUTF(url.c_str());
    jobject uri = env->CallStaticObjectMethod(uriClass, parse, jUrl);

    jfieldID actionViewField = env->GetStaticFieldID(
        intentClass,
        "ACTION_VIEW",
        "Ljava/lang/String;"
    );
    jobject actionView = env->GetStaticObjectField(intentClass, actionViewField);

    jmethodID ctor = env->GetMethodID(
        intentClass,
        "<init>",
        "(Ljava/lang/String;Landroid/net/Uri;)V"
    );
    jobject intent = env->NewObject(intentClass, ctor, actionView, uri);

    // 🔥 REQUIRED FLAG (native → activity)
    jfieldID flagField = env->GetStaticFieldID(
        intentClass,
        "FLAG_ACTIVITY_NEW_TASK",
        "I"
    );
    jint flag = env->GetStaticIntField(intentClass, flagField);

    jmethodID addFlags = env->GetMethodID(
        intentClass,
        "addFlags",
        "(I)Landroid/content/Intent;"
    );
    env->CallObjectMethod(intent, addFlags, flag);

    // Start activity
    jclass activityClass = env->GetObjectClass(activity);
    jmethodID startActivity = env->GetMethodID(
        activityClass,
        "startActivity",
        "(Landroid/content/Intent;)V"
    );
    env->CallVoidMethod(activity, startActivity, intent);

    // Cleanup
    env->DeleteLocalRef(jUrl);
    env->DeleteLocalRef(uri);
    env->DeleteLocalRef(intent);
    env->DeleteLocalRef(intentClass);
    env->DeleteLocalRef(uriClass);
    env->DeleteLocalRef(activityClass);

    if (needDetach)
        vm->DetachCurrentThread();

    return 0;
}
    std::string getClipboardText() {
    if (!g_App)
        return "";

    auto activity = g_App->activity;
    if (!activity)
        return "";

    auto vm = activity->vm;
    if (!vm)
        return "";

    auto object = activity->clazz;
    if (!object)
        return "";

    std::string result;

    JNIEnv *env;
    vm->AttachCurrentThread(&env, 0);
    {
        auto ContextClass = env->FindClass("android/content/Context");
        auto getSystemServiceMethod = env->GetMethodID(ContextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");

        auto str = env->NewStringUTF("clipboard");
        auto clipboardManager = env->CallObjectMethod(object, getSystemServiceMethod, str);
        env->DeleteLocalRef(str);

        auto ClipboardManagerClass = env->FindClass("android/content/ClipboardManager");
        auto getText = env->GetMethodID(ClipboardManagerClass, "getText", "()Ljava/lang/CharSequence;");

        auto CharSequenceClass = env->FindClass("java/lang/CharSequence");
        auto toStringMethod = env->GetMethodID(CharSequenceClass, "toString", "()Ljava/lang/String;");

        auto text = env->CallObjectMethod(clipboardManager, getText);
        if (text) {
            str = (jstring) env->CallObjectMethod(text, toStringMethod);
            result = env->GetStringUTFChars(str, 0);
            env->DeleteLocalRef(str);
            env->DeleteLocalRef(text);
        }

        env->DeleteLocalRef(CharSequenceClass);
        env->DeleteLocalRef(ClipboardManagerClass);
        env->DeleteLocalRef(clipboardManager);
        env->DeleteLocalRef(ContextClass);
    }
    vm->DetachCurrentThread();

    return result;
}



const char *GetAndroidID(JNIEnv *env, jobject context) {
    jclass contextClass = env->FindClass(/*android/content/Context*/ StrEnc("`L+&0^[S+-:J^$,r9q92(as", "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07", 23).c_str());
    jmethodID getContentResolverMethod = env->GetMethodID(contextClass, /*getContentResolver*/ StrEnc("E8X\\7r7ys_Q%JS+L+~", "\x22\x5D\x2C\x1F\x58\x1C\x43\x1C\x1D\x2B\x03\x40\x39\x3C\x47\x3A\x4E\x0C", 18).c_str(), /*()Landroid/content/ContentResolver;*/ StrEnc("8^QKmj< }5D:9q7f.BXkef]A*GYLNg}B!/L", "\x10\x77\x1D\x2A\x03\x0E\x4E\x4F\x14\x51\x6B\x59\x56\x1F\x43\x03\x40\x36\x77\x28\x0A\x08\x29\x24\x44\x33\x0B\x29\x3D\x08\x11\x34\x44\x5D\x77", 35).c_str());
    jclass settingSecureClass = env->FindClass(/*android/provider/Settings$Secure*/ StrEnc("T1yw^BCF^af&dB_@Raf}\\FS,zT~L(3Z\"", "\x35\x5F\x1D\x05\x31\x2B\x27\x69\x2E\x13\x09\x50\x0D\x26\x3A\x32\x7D\x32\x03\x09\x28\x2F\x3D\x4B\x09\x70\x2D\x29\x4B\x46\x28\x47", 32).c_str());
    jmethodID getStringMethod = env->GetStaticMethodID(settingSecureClass, /*getString*/ StrEnc("e<F*J5c0Y", "\x02\x59\x32\x79\x3E\x47\x0A\x5E\x3E", 9).c_str(), /*(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;*/ StrEnc("$6*%R*!XO\"m18o,0S!*`uI$IW)l_/_knSdlRiO1T`2sH|Ouy__^}%Y)JsQ:-\"(2_^-$i{?H", "\x0C\x7A\x4B\x4B\x36\x58\x4E\x31\x2B\x0D\x0E\x5E\x56\x1B\x49\x5E\x27\x0E\x69\x0F\x1B\x3D\x41\x27\x23\x7B\x09\x2C\x40\x33\x1D\x0B\x21\x5F\x20\x38\x08\x39\x50\x7B\x0C\x53\x1D\x2F\x53\x1C\x01\x0B\x36\x31\x39\x46\x0C\x15\x43\x2B\x05\x30\x15\x41\x43\x46\x55\x70\x0D\x59\x56\x00\x15\x58\x73", 71).c_str());

    auto obj = env->CallObjectMethod(context, getContentResolverMethod);
    auto str = (jstring) env->CallStaticObjectMethod(settingSecureClass, getStringMethod, obj, env->NewStringUTF(/*android_id*/ StrEnc("ujHO)8OfOE", "\x14\x04\x2C\x3D\x46\x51\x2B\x39\x26\x21", 10).c_str()));
    return env->GetStringUTFChars(str, 0);
}

const char *GetDeviceModel(JNIEnv *env) {
    jclass buildClass = env->FindClass(/*android/os/Build*/ StrEnc("m5I{GKGWBP-VOxkA", "\x0C\x5B\x2D\x09\x28\x22\x23\x78\x2D\x23\x02\x14\x3A\x11\x07\x25", 16).c_str());
    jfieldID modelId = env->GetStaticFieldID(buildClass, /*MODEL*/ StrEnc("|}[q:", "\x31\x32\x1F\x34\x76", 5).c_str(), /*Ljava/lang/String;*/ StrEnc(".D:C:ETZ1O-Ib&^h.Y", "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62", 18).c_str());

    auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
    return env->GetStringUTFChars(str, 0);
}

const char *GetDeviceBrand(JNIEnv *env) {
    jclass buildClass = env->FindClass(/*android/os/Build*/ StrEnc("0iW=2^>0zTRB!B90", "\x51\x07\x33\x4F\x5D\x37\x5A\x1F\x15\x27\x7D\x00\x54\x2B\x55\x54", 16).c_str());
    jfieldID modelId = env->GetStaticFieldID(buildClass, /*BRAND*/ StrEnc("@{[FP", "\x02\x29\x1A\x08\x14", 5).c_str(), /*Ljava/lang/String;*/ StrEnc(".D:C:ETZ1O-Ib&^h.Y", "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62", 18).c_str());

    auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
    return env->GetStringUTFChars(str, 0);
}

const char *GetPackageName(JNIEnv *env, jobject context) {
    jclass contextClass = env->FindClass(/*android/content/Context*/ StrEnc("`L+&0^[S+-:J^$,r9q92(as", "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07", 23).c_str());
    jmethodID getPackageNameId = env->GetMethodID(contextClass, /*getPackageName*/ StrEnc("YN4DaP)!{wRGN}", "\x3E\x2B\x40\x14\x00\x33\x42\x40\x1C\x12\x1C\x26\x23\x18", 14).c_str(), /*()Ljava/lang/String;*/ StrEnc("VnpibEspM(b]<s#[9cQD", "\x7E\x47\x3C\x03\x03\x33\x12\x5F\x21\x49\x0C\x3A\x13\x20\x57\x29\x50\x0D\x36\x7F", 20).c_str());

    auto str = (jstring) env->CallObjectMethod(context, getPackageNameId);
    return env->GetStringUTFChars(str, 0);
}

const char *GetDeviceUniqueIdentifier(JNIEnv *env, const char *uuid) {
    jclass uuidClass = env->FindClass(/*java/util/UUID*/ StrEnc("B/TxJ=3BZ_]SFx", "\x28\x4E\x22\x19\x65\x48\x47\x2B\x36\x70\x08\x06\x0F\x3C", 14).c_str());

    auto len = strlen(uuid);

    jbyteArray myJByteArray = env->NewByteArray(len);
    env->SetByteArrayRegion(myJByteArray, 0, len, (jbyte *) uuid);

    jmethodID nameUUIDFromBytesMethod = env->GetStaticMethodID(uuidClass, /*nameUUIDFromBytes*/ StrEnc("P6LV|'0#A+zQmoat,", "\x3E\x57\x21\x33\x29\x72\x79\x67\x07\x59\x15\x3C\x2F\x16\x15\x11\x5F", 17).c_str(), /*([B)Ljava/util/UUID;*/ StrEnc("sW[\"Q[W3,7@H.vT0) xB", "\x5B\x0C\x19\x0B\x1D\x31\x36\x45\x4D\x18\x35\x3C\x47\x1A\x7B\x65\x7C\x69\x3C\x79", 20).c_str());
    jmethodID toStringMethod = env->GetMethodID(uuidClass, /*toString*/ StrEnc("2~5292eW", "\x46\x11\x66\x46\x4B\x5B\x0B\x30", 8).c_str(), /*()Ljava/lang/String;*/ StrEnc("P$BMc' #j?<:myTh_*h0", "\x78\x0D\x0E\x27\x02\x51\x41\x0C\x06\x5E\x52\x5D\x42\x2A\x20\x1A\x36\x44\x0F\x0B", 20).c_str());

    auto obj = env->CallStaticObjectMethod(uuidClass, nameUUIDFromBytesMethod, myJByteArray);
    auto str = (jstring) env->CallObjectMethod(obj, toStringMethod);
    return env->GetStringUTFChars(str, 0);
}



int LoginAnnouncementBykaushik(const char* url) {
    JavaVM* java_vm = g_App->activity->vm;
    JNIEnv* java_env = NULL;
    jint jni_return = java_vm->GetEnv((void**)&java_env, JNI_VERSION_1_6);
    if (jni_return == JNI_EDETACHED) {
        if (java_vm->AttachCurrentThread(&java_env, NULL) != JNI_OK) {
            return -1;
        }
    } else if (jni_return == JNI_EVERSION) {
        return -1;
    }
	jclass KAUSHIK = java_env->FindClass("android/media/MediaPlayer");
    if (KAUSHIK == NULL) {
        return -3;
    }

    jmethodID create_method_id = java_env->GetMethodID(KAUSHIK, "<init>", "()V");
    if (create_method_id == NULL) {
        return -4;
    }

    jobject media_player_obj = java_env->NewObject(KAUSHIK, create_method_id);
    if (media_player_obj == NULL) {
        return -5;
    }

    jmethodID set_data_source_method_id = java_env->GetMethodID(KAUSHIK, "setDataSource", "(Ljava/lang/String;)V");
    if (set_data_source_method_id == NULL) {
        return -6;
		}

    jstring url_str = java_env->NewStringUTF(url);
    java_env->CallVoidMethod(media_player_obj, set_data_source_method_id, url_str);

    jmethodID prepare_method_id = java_env->GetMethodID(KAUSHIK, "prepare", "()V");
    if (prepare_method_id == NULL) {
        return -7;
    }
    java_env->CallVoidMethod(media_player_obj, prepare_method_id);

    jmethodID start_method_id = java_env->GetMethodID(KAUSHIK, "start", "()V");
    if (start_method_id == NULL) {
        return -8;
    }
   
    java_env->CallVoidMethod(media_player_obj, start_method_id);

    java_env->DeleteLocalRef(KAUSHIK);
    java_env->DeleteLocalRef(media_player_obj);
    java_env->DeleteLocalRef(url_str);

    if (java_vm->DetachCurrentThread() != JNI_OK) {
        return -1;
    }

    return 0;
}
struct MemoryStruct
{
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL)
    {
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

std::string FetchText(const std::string &url)
{
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        return "Error";
    }

    CURLcode res;
    struct MemoryStruct chunk;
    chunk.memory = (char *)malloc(1);
    chunk.size = 0;

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "");

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {

            curl_easy_cleanup(curl);
            free(chunk.memory);
            return "Error";
        }

        std::string text(chunk.memory);
        curl_easy_cleanup(curl);
        free(chunk.memory);
        return text;
    }

    return "Error";
}


std::string Login(const char *user_key) {
    if (!g_App)
        return "Internal Error";

    auto activity = g_App->activity;
    if (!activity)
        return "Internal Error";

    auto vm = activity->vm;
    if (!vm)
        return "Internal Error";

    auto object = activity->clazz;
    if (!object)
        return "Internal Error";

    JNIEnv *env;
    vm->AttachCurrentThread(&env, 0);

    std::string hwid = user_key;
    hwid += GetAndroidID(env, object);
    hwid += GetDeviceModel(env);
    hwid += GetDeviceBrand(env);

    std::string UUID = GetDeviceUniqueIdentifier(env, hwid.c_str());

    vm->DetachCurrentThread();

    std::string errMsg;

    struct MemoryStruct chunk{};
    chunk.memory = (char *) malloc(1);
    chunk.size = 0;

        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, /*POST*/ StrEnc(",IL=", "\x7C\x06\x1F\x69", 4).c_str());
                
       
		curl_easy_setopt(curl, CURLOPT_URL, (api_key.c_str()));
		

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, /*https*/ StrEnc("!mLBO", "\x49\x19\x38\x32\x3C", 5).c_str());
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, /*Content-Type: application/x-www-form-urlencoded*/ StrEnc("@;Ls\\(KP4Qrop`b#d3094/r1cf<c<=H)AiiBG6i|Ta66s2[", "\x03\x54\x22\x07\x39\x46\x3F\x7D\x60\x28\x02\x0A\x4A\x40\x03\x53\x14\x5F\x59\x5A\x55\x5B\x1B\x5E\x0D\x49\x44\x4E\x4B\x4A\x3F\x04\x27\x06\x1B\x2F\x6A\x43\x1B\x10\x31\x0F\x55\x59\x17\x57\x3F", 47).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        char data[4096];
        sprintf(data, /*game=PUBG&user_key=%s&serial=%s*/ StrEnc("qu2yXK,YkJyGD@ut0.u~Nb'5(:.:chK", "\x16\x14\x5F\x1C\x65\x1B\x79\x1B\x2C\x6C\x0C\x34\x21\x32\x2A\x1F\x55\x57\x48\x5B\x3D\x44\x54\x50\x5A\x53\x4F\x56\x5E\x4D\x38", 31).c_str(), user_key, UUID.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            try {
                json result = json::parse(chunk.memory);
                if (result[/*status*/ StrEnc("(>_LBm", "\x5B\x4A\x3E\x38\x37\x1E", 6).c_str()] == true) {
                
                    
                      rng = result[/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][/*rng*/ StrEnc("+n,", "\x59\x00\x4B", 3).c_str()].get<time_t>();
                      std::string token = result[/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][/*token*/ StrEnc("{>3Lr", "\x0F\x51\x58\x29\x1C", 5).c_str()].get<std::string>();
                      rng = result[/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][/*rng*/ StrEnc("+n,", "\x59\x00\x4B", 3).c_str()].get<time_t>();
				        if (rng + 30 > time(0)) {
                        std::string auth = /*PUBG*/ StrEnc("Q*) ", "\x01\x7F\x6B\x67", 4).c_str();;
                        auth += "-";
                        auth += user_key;
                        auth += "-";
                        auth += UUID;
                        auth += "-";
						auth += licanse.c_str();				
						std::string outputAuth = Tools::CalcMD5(auth);
                        g_Token = token;
                        g_Auth = outputAuth;

                        KaushikSettings::bValid = g_Token == g_Auth;
				         
                    }
                } else {
                    errMsg = result[/*reason*/ StrEnc("LW(3(c", "\x3E\x32\x49\x40\x47\x0D", 6).c_str()].get<std::string>();
                }
            } catch (json::exception &e) {
                errMsg = "{";
                errMsg += e.what();
                errMsg += "}\n{";
                errMsg += chunk.memory;
                errMsg += "}";
            }
        } else {
            errMsg = curl_easy_strerror(res);
        }
    }
    curl_easy_cleanup(curl);

    return KaushikSettings::bValid ? "OK" : errMsg;
}


void SendScreenshotToTelegram(const char* filepath) {
    CURL *curl;
    CURLcode res;
    struct curl_httppost* post = NULL;
    struct curl_httppost* last = NULL;

    

	
    std::string filename(filepath);
    std::string caption = filename.substr(filename.find_last_of("/\\") + 1);  // Extract only the file name
	
    char url[512];
    snprintf(url, sizeof(url), "https://api.telegram.org/bot%s/sendPhoto", bot_token);

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {
        curl_formadd(&post, &last,
                     CURLFORM_COPYNAME, "chat_id",
                     CURLFORM_COPYCONTENTS, chat_id,
                     CURLFORM_END);

        curl_formadd(&post, &last,
                     CURLFORM_COPYNAME, "photo",
                     CURLFORM_FILE, filepath,
					 CURLFORM_END);

					 
        curl_formadd(&post, &last,
                     CURLFORM_COPYNAME, "caption",
                     CURLFORM_COPYCONTENTS, caption.c_str(),  // Set the filename as the caption
                     CURLFORM_END);
					
                     
					 
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // Yeh line add karke pura request/response console me dikhega
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
           ShowInfoToast("FeedBack Send failed!");
        } else {
           // printf("Screenshot sent to Telegram successfully!\n");
            ShowInfoToast("FeedBack Send Successful!");
        }

        curl_easy_cleanup(curl);
        curl_formfree(post);
    }
    curl_global_cleanup();
	
	if (filepath != nullptr) {
        if (remove(filepath) == 0) {
            printf("Temporary screenshot deleted successfully.\n");
        } else {
            printf("Failed to delete screenshot.\n");
        }
    }
}


size_t WriteMemoryCallbaack(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void* Load_Lib(void*);

void MonitorOnlineStatus()
{
    static bool once = false;
    if (once) return;   // 🔒 CHECK ONLY ONCE

    // 🔥 HARD RESET (MANDATORY)
    KaushikSettings::NetFailed   = false;
    KaushikSettings::ServerOff   = false;
    KaushikSettings::VersionUp   = false;
    KaushikSettings::Online_Same = false;
    KaushikSettings::DownloadLib = false;

    CURL* curl = nullptr;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) {
        KaushikSettings::NetFailed = true;
        return;
    }

    curl_easy_setopt(curl, CURLOPT_URL, jsonUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallbaack);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 6L);

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (res != CURLE_OK || readBuffer.empty()) {
        KaushikSettings::NetFailed = true;
        return;
    }

    try {
        json root = json::parse(readBuffer);

        if (!root["Status"].get<bool>()) {
            KaushikSettings::ServerOff = true;
            return;
        }

        int serverVersion = root["version"].get<int>();
        KaushikSettings::ServerVersion = serverVersion;

        if (serverVersion != localVersion) {
            KaushikSettings::VersionUp = true;
            return;
        }

        // ✅ SERVER OK
        KaushikSettings::Online_Same = true;

        KaushikSettings::DownloadLib = root["Dlib"].get<bool>();
        if (KaushikSettings::DownloadLib)
        {
            KaushikSettings::LibUrl   = root["libs"].get<std::string>();
            KaushikSettings::LibReady = true;

            // 🔥 ADD HERE: START DOWNLOAD + LOAD IN BACKGROUND (ONLY ONCE)
            if (!KaushikSettings::LibThreadStarted  && KaushikSettings::bValid)
            {
                KaushikSettings::LibThreadStarted = true;
                pthread_t t;
                pthread_create(&t, nullptr, Load_Lib, nullptr);
                pthread_detach(t);
            }
        }

        once = true; // 🔒 NEVER CHECK AGAIN
    }
    catch (...) {
        KaushikSettings::NetFailed = true;
    }
}