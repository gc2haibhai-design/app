void DrawLoadingAnimation(ImDrawList* draw_list, ImVec2 center, float size, float thickness, float speed, ImU32 color) {
    int num_segments = 8; // 8-segment loader
    float time = ImGui::GetTime() * speed; // Time-based animation
    float radius = size * 0.5f;
    float angle_step = (2 * IM_PI) / num_segments;

    for (int i = 0; i < num_segments; i++) {
        float angle = angle_step * i;
        float alpha = (sin(time - angle) + 1.0f) * 0.5f; // Smooth fade effect

        // Increase line size for better visibility
        float inner_radius = radius * 0.4f;
        
        ImVec2 p1 = ImVec2(center.x + cos(angle) * radius, center.y + sin(angle) * radius);
        ImVec2 p2 = ImVec2(center.x + cos(angle) * inner_radius, center.y + sin(angle) * inner_radius);

        ImU32 seg_color = IM_COL32(0, 0, 0, (int)(alpha * 255)); // Black color with fade effect
        draw_list->AddLine(p1, p2, seg_color, thickness);
    }
}

void DrawVirtualKeyboard(char* buffer, size_t bufSize)
{

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 8));

    const char* row1 = "1234567890";
    const char* row2 = "QWERTYUIOP";
    const char* row3 = "ASDFGHJKL";
    const char* row4 = "ZXCVBNM";

    auto drawRow = [&](const char* row, float offsetX)
    {
        ImGui::SetCursorPosX(offsetX);
        for (int i = 0; row[i]; i++)
        {
            char key[2] = { row[i], 0 };
            if (ImGui::Button(key, ImVec2(36, 36)))
            {
                size_t len = strlen(buffer);
                if (len < bufSize - 1)
                {
                    buffer[len] = row[i];
                    buffer[len + 1] = '\0';
                }
            }
            ImGui::SameLine(0, 6);
        }
        ImGui::NewLine();
        ImGui::Dummy(ImVec2(0, 2));
    };

    float w = ImGui::GetContentRegionAvail().x;

    drawRow(row1, (w - (10 * 42)) * 0.5f);
    drawRow(row2, (w - (10 * 42)) * 0.5f);
    drawRow(row3, (w - (9 * 42)) * 0.5f);
    drawRow(row4, (w - (7 * 42)) * 0.5f);

    // ===== BACKSPACE + CLEAR =====
    ImGui::SetCursorPosX((w - 260) * 0.5f);

    if (ImGui::Button("Backspace", ImVec2(140, 38)))
    {
        size_t len = strlen(buffer);
        if (len > 0)
            buffer[len - 1] = '\0';
    }

    ImGui::SameLine(0, 10);

    if (ImGui::Button("Clear", ImVec2(100, 38)))
    {
        buffer[0] = '\0';
    }

    ImGui::PopStyleVar(2);
}
///---------------------------MR KAUSHIK HAXOR ---------------------------//
EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
     if (glWidth <= 0 || glHeight <= 0){
        return orig_eglSwapBuffers(dpy, surface);}

    if (!g_App){
        return orig_eglSwapBuffers(dpy, surface);}
		
    screenWidth = ANativeWindow_getWidth(g_App->window);
    screenHeight = ANativeWindow_getHeight(g_App->window);
    density = AConfiguration_getDensity(g_App->config);
    
    
	  if (!KaushikSettings::initImGui) {
       ImGui::CreateContext();
       ImGuiStyle *style = &ImGui::GetStyle();		
      // InitTexture();
	   style->WindowRounding = 2.0f;
       style->FrameRounding = 0.0f;
       style->FramePadding = ImVec2(8, 4);
	   style->TabRounding = 1.0f;
       style->GrabRounding = 2.0f;
	   style->WindowTitleAlign = ImVec2(0.5, 0.5);
	   
	   
	   //---------------------------------------//
    
            
       style->ScaleAllSizes(std::max(1.0f, density / 250.0f));//250
       style->ScrollbarSize *= 0.0f;
       style->Colors[ImGuiCol_Text]                  = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
       style->Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
       style->Colors[ImGuiCol_WindowBg]              = ImColor(170,173,180,255);
       style->Colors[ImGuiCol_PopupBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
     /*style->Colors[ImGuiCol_Border]                = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
       style->Colors[ImGuiCol_BorderShadow]          = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);*/
       style->Colors[ImGuiCol_FrameBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
       style->Colors[ImGuiCol_FrameBgHovered]        = ImColor(0,0,0,100);//ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
       style->Colors[ImGuiCol_FrameBgActive]         = ImColor(0,0,0,100);//ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
       style->Colors[ImGuiCol_TitleBg]               = ImVec4(0.96f, 0.96f, 0.96f, 0.96f);
       style->Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
       style->Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.96f, 0.96f, 0.96f, 0.96f);
       style->Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
       style->Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
       style->Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
       style->Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
       style->Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
       style->Colors[ImGuiCol_CheckMark]             = ImColor( 41, 44, 49, 255);// ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
       style->Colors[ImGuiCol_SliderGrab]            = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
       style->Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
       style->Colors[ImGuiCol_Button]                = ImColor(0,0,0,150);//ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
       style->Colors[ImGuiCol_ButtonHovered]         = ImColor(0,0,0,150);//ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
       style->Colors[ImGuiCol_ButtonActive]          = ImColor(0,0,0,150);//ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
       style->Colors[ImGuiCol_Header]                = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
       style->Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
       style->Colors[ImGuiCol_HeaderActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
       style->Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
       style->Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
       style->Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
       style->Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);

    
	
	        ImGui_ImplAndroid_Init();
            ImGui_ImplOpenGL3_Init(OBFUSCATE("#version 300 es"));  
	  
            ImGuiIO &io = ImGui::GetIO();
		    io.AnimationSpeed = 1;
            io.ConfigWindowsMoveFromTitleBarOnly = true;
            io.IniFilename = NULL;
    
            static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
            ImFontConfig icons_config;
			ImFontConfig CustomFont;
            CustomFont.FontDataOwnedByAtlas = false;

            icons_config.MergeMode = true;
            icons_config.PixelSnapH = true;
            icons_config.OversampleH = 2.5;
            icons_config.OversampleV = 2.5;
            
            static const ImWchar ranges[] = {
            0x0020, 0x007F,  // Basic Latin
            0x00A0, 0x00FF,  // Latin-1 Supplement
            0x0100, 0x024F,  // Latin Extended-A + Extended-B
            0x0400, 0x052F,  // Cyrillic + Supplementary
            0x0600, 0x06FF,  // Arabic
            0x20A0, 0x20CF,  // Currency Symbols
            0x2190, 0x21FF,  // Arrows
            0x2600, 0x26FF,  // Miscellaneous Symbols
            0x1F600, 0x1F64F, // Emojis
            0xE000, 0xF8FF,  // Private Use Area
            0,               // End of range
            };
			
			io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom), sizeof(Custom), 25.f, &CustomFont);
            io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 30.0f, &icons_config, icons_ranges);
			
		    Injector = io.Fonts->AddFontFromMemoryTTF((void *)Injector_data, Injector_size, 20.5f, NULL, ranges);
		    Injector2 = io.Fonts->AddFontFromMemoryTTF((void *)Injector2_data, Injector2_size, 25.0f, NULL, ranges);
            Social = io.Fonts->AddFontFromMemoryTTF((void *)Social_data, Social_size, 30.0f, NULL, io.Fonts->GetGlyphRangesDefault());
            
			ImFontConfig cfg;
            cfg.SizePixels = ((float) density / 20.0f);
            io.Fonts->AddFontDefault(&cfg);
			
            for (auto &i : items_data) {
            for (auto &item : i["Items"]) {
            int r, g, b;
            sscanf(item["itemTextColor"].get<std::string>().c_str(), "#%02X%02X%02X", &r, &g, &b);
            ItemColors[item["itemId"].get<int>()] = CREATE_COLOR(255, 255, 255, 255);
            }
        }
            KaushikSettings::initImGui = true;
        }
    
    
        
    ImGuiIO &io = ImGui::GetIO();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();
	Colors::Text = ImColor(100,103,108,255);
    Colors::TextActive = ImColor(41,44,49,255);
    Colors::TextActiveNew = ImColor(255,255,255);
    Colors::TextNew = ImColor(255,255,255);
    Colors::FrameHovered = ImColor(255,255,255,255);
    Colors::FrameOpened = ImColor(255,255,255,255);


float deltaTime = ImGui::GetIO().DeltaTime;
DrawToasts(deltaTime);

/*
 *  @date   : 2020/02/04
 *  @Creator : @Mrkaushikhaxor
 *  Https://t.me/KaushikCracking
 */

  #include "Kaushik/RGB.h"
  
 DrawESP(ImGui::GetBackgroundDrawList());

