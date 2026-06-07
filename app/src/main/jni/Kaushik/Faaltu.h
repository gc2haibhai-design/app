

void VectorAnglesRadar(Vector3 & forward, FVector & angles) {
 if (forward.X == 0.f && forward.Y == 0.f) {
  angles.X = forward.Z > 0.f ? -90.f : 90.f;
  angles.Y = 0.f;
 } else {
  angles.X = RAD2DEG(atan2(-forward.Z, forward.Magnitude(forward)));
  angles.Y = RAD2DEG(atan2(forward.Y, forward.X));
 }
 angles.Z = 0.f;
}

void RotateTriangle(std::array<Vector3, 3> & points, float rotation) {
 const auto points_center = (points.at(0) + points.at(1) + points.at(2)) / 3;
 for (auto & point : points) {
  point = point - points_center;
  const auto temp_x = point.X;
  const auto temp_y = point.Y;
  const auto theta = DEG2RAD(rotation);
  const auto c = cosf(theta);
  const auto s = sinf(theta);
  point.X = temp_x * c - temp_y * s;
  point.Y = temp_x * s + temp_y * c;
  point = point + points_center;
 }
}

void DrawFilledRectangle(int x, int y, int w, int h, ImU32 col, float rounding) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), col, rounding);
}

void DrawRectangle(int x, int y, int w, int h, ImU32 col, float rounding) {
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), col, rounding);
}
bool W2S2(FVector worldPos, FVector2D *screenPos) {
    return g_LocalController->ProjectWorldLocationToScreen(worldPos, true, screenPos);
}

void Line(ImDrawList *draw,FVector2D origin, FVector2D dest, ImColor color)
{
   draw->AddLine({origin.X, origin.Y},{dest.X, dest.Y},color, 2.0f);
}

FVector WorldToRadar(float Yaw, FVector Origin, FVector LocalOrigin, float PosX, float PosY, Vector3 Size, bool &outbuff) {
 bool flag = false;
 double num = (double)Yaw;
 double num2 = num * 0.017453292519943295;
 float num3 = (float)std::cos(num2);
 float num4 = (float)std::sin(num2);
 float num5 = Origin.X - LocalOrigin.X;
 float num6 = Origin.Y - LocalOrigin.Y;
 struct FVector Xector;
 Xector.X = (num6 * num3 - num5 * num4) / 150.f;
 Xector.Y = (num5 * num3 + num6 * num4) / 150.f;
 struct FVector Xector2;
 Xector2.X = Xector.X + PosX + Size.X / 2.f;
 Xector2.Y = -Xector.Y + PosY + Size.Y / 2.f;
 bool flag2 = Xector2.X > PosX + Size.X;
 if (flag2) {
  Xector2.X = PosX + Size.X;
 }else{
  bool flag3 = Xector2.X < PosX;
  if (flag3) {
   Xector2.X = PosX;
  }
 }
 bool flag4 = Xector2.Y > PosY + Size.Y;
 if (flag4) {
  Xector2.Y = PosY + Size.Y;
 }else{
  bool flag5 = Xector2.Y < PosY;
  if (flag5){
   Xector2.Y = PosY;
  }
 }
 bool flag6 = Xector2.Y == PosY || Xector2.X == PosX;
 if (flag6){
  flag = true;
 }
 outbuff = flag;
 return Xector2;
}


struct ToastMessage {
    std::string icon;
    std::string message;
    float lifetime;       // how long to show
    float animProgress;   // 0 to 1
    bool animDone;
};
std::queue<ToastMessage> toastQueue;
ToastMessage* currentToast = nullptr;

void ShowInfoToast(const std::string& message) {
    ToastMessage toast;
    toast.icon = ICON_FA_INFO_CIRCLE; // FontAwesome icon (loaded separately)
    toast.message = message;
    toast.lifetime = 3.0f;
    toast.animProgress = 0.0f;
    toast.animDone = false;
    toastQueue.push(toast);
}
void DrawToasts(float deltaTime) {
    static ToastMessage* activeToast = nullptr;
    static float timer = 0.0f;
    static float slideY = -100.0f;

    if (!activeToast && !toastQueue.empty()) {
        activeToast = new ToastMessage(toastQueue.front());
        toastQueue.pop();
        timer = 0.0f;
        slideY = -100.0f;  // reset slide position to start above screen
    }

    if (activeToast) {
        timer += deltaTime;

        // Animate toast lifetime (for border progress)
        activeToast->animProgress = std::min(1.0f, timer / activeToast->lifetime);

        // Slide-down animation from top to 15% screen height
        float targetY = ImGui::GetIO().DisplaySize.y * 0.15f;
        float slideSpeed = 6.0f;  // higher = faster
        slideY = slideY + (targetY - slideY) * slideSpeed * deltaTime;

        ImGui::SetNextWindowPos(
            ImVec2(ImGui::GetIO().DisplaySize.x / 2.0f, slideY),
            ImGuiCond_Always,
            ImVec2(0.5f, 0)
        );
        ImGui::SetNextWindowBgAlpha(0.4f);

        ImGui::Begin("Toast", nullptr,
                     ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
                     ImGuiWindowFlags_NoNav);
        ImGui::TextColored(ImVec4(1, 1, 1, 1), "%s %s", activeToast->icon.c_str(), activeToast->message.c_str());

        // Border animation
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 p0 = ImGui::GetWindowPos();
        ImVec2 p1 = ImVec2(p0.x + ImGui::GetWindowWidth(), p0.y + ImGui::GetWindowHeight());
        float totalLength = 2 * (p1.x - p0.x + p1.y - p0.y);
        float progressLength = totalLength * activeToast->animProgress;

        ImVec2 a = p0;
        ImVec2 b = p0;
        float remaining = progressLength;

        float w = p1.x - p0.x;
        if (remaining > 0) {
            float len = std::min(remaining, w);
            b.x += len;
            draw_list->AddLine(a, b, IM_COL32(255, 0, 0, 255), 4);
            remaining -= len;
        }
        a = b; b = a;

        float h = p1.y - p0.y;
        if (remaining > 0) {
            float len = std::min(remaining, h);
            b.y += len;
            draw_list->AddLine(a, b, IM_COL32(255, 0, 0, 255), 6);
            remaining -= len;
        }
        a = b; b = a;

        if (remaining > 0) {
            float len = std::min(remaining, w);
            b.x -= len;
            draw_list->AddLine(a, b, IM_COL32(255, 0, 0, 255), 6);
            remaining -= len;
        }
        a = b; b = a;

        if (remaining > 0) {
            float len = std::min(remaining, h);
            b.y -= len;
            draw_list->AddLine(a, b, IM_COL32(255, 0, 0, 255), 6);
        }

        ImGui::End();

        // Remove toast after finished
        if (timer >= activeToast->lifetime) {
            delete activeToast;
            activeToast = nullptr;
        }
    }
}