
void triggerCrash() {
    volatile char* crash = (char*)0xDEAD;
    *crash = 1;
}

// Run shell command and return output
std::string runCommand(const char* cmd) {
    std::string result;
    char buffer[128];
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "";

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}
__attribute__((constructor(101)))
void ultraHardenedAntiTamper() {
    const char* suspiciousPaths[] = {
        "/data/data/com.vmos/",
        "/data/data/com.lbe.parallel/",
        "/data/data/com.excean.masaid/",
        "/data/data/com.gameguardian/",
        "/sbin/.magisk/",
        "/dev/com.koushikdutta.superuser.daemon/",
        "/dev/magisk/",
        "/proc/self/root/sbin/su"
    };
    for (const char* path : suspiciousPaths) {
        if (access(path, F_OK) == 0) triggerCrash();
    }

    // ✅ Process scan (renamed GG or Frida)
    std::string psOutput = runCommand("ps -A");
    if (psOutput.find("frida") != std::string::npos ||
        psOutput.find("catch_.me_.if_.you_.can_") != std::string::npos ||
        psOutput.find("gameguardian") != std::string::npos ||
        psOutput.find("vmos") != std::string::npos) {
        triggerCrash();
    }

    // ✅ getprop checks
    std::string props = runCommand("getprop");
    if (props.find("ro.build.tags=test-keys") != std::string::npos ||
        props.find("ro.debuggable=1") != std::string::npos ||
        props.find("ro.secure=0") != std::string::npos ||
        props.find("frida") != std::string::npos) {
        triggerCrash();
    }

    // ✅ Magisk mounts
    std::string mounts = runCommand("cat /proc/mounts");
    if (mounts.find("magisk") != std::string::npos) {
        triggerCrash();
    }

    // ✅ MagiskHide (fake process names)
    std::string hideCheck = runCommand("ls /sbin | grep magiskhide");
    if (!hideCheck.empty()) {
        triggerCrash();
    }

    // ✅ Installed package list (GameGuardian spoofed package)
    std::string pkgList = runCommand("pm list packages");
    if (pkgList.find("gameguardian") != std::string::npos ||
        pkgList.find("catch_.me_.if_.you_.can_") != std::string::npos ||
        pkgList.find("vmos") != std::string::npos){
        triggerCrash();
    }
}