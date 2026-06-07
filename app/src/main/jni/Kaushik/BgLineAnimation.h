                     ImDrawList* pDrawList;
					 const auto& pWindowDrawList = ImGui::GetWindowDrawList();
				     pDrawList = pWindowDrawList;		 
				 	 static const int numParticles = 115;
				     static ImVec2 particlePositions[numParticles];
					 static ImVec2 particleDistance;
					 static ImVec2 particleVelocities[numParticles];
				     static bool initialized = false;
					 if (!initialized){
					 for (int i = 0; i < numParticles; ++i){
					 particlePositions[i] = ImVec2(
					 ImGui::GetWindowPos().x + ImGui::GetWindowSize().x * static_cast<float>(rand()) / RAND_MAX,
					 ImGui::GetWindowPos().y + ImGui::GetWindowSize().y * static_cast<float>(rand()) / RAND_MAX);
		  	         particleVelocities[i] = ImVec2(
				     static_cast<float>((rand() % 150) - 70),
				     static_cast<float>((rand() % 150) - 70));}
				     initialized = true;}
	                 ImVec2 cursorPos = ImGui::GetIO().MousePos;
	                 for (int i = 0; i < numParticles; ++i){
		             for (int j = i + 1; j < numParticles; ++j){
			         float distance = std::hypotf(particlePositions[j].x - particlePositions[i].x, particlePositions[j].y - particlePositions[i].y);
			         float opacity = 1.0f - (distance / 55.0f);  // opacity cahnge
			         if (opacity > 0.0f){
				     ImU32 lineColor = ImGui::GetColorU32(ImVec4(1.0f, 1.f, 1.0f, opacity));
				     pDrawList->AddLine(particlePositions[i], particlePositions[j], lineColor);}}
		             float distanceToCursor = std::hypotf(cursorPos.x - particlePositions[i].x, cursorPos.y - particlePositions[i].y);
		             float opacityToCursor = 1.0f - (distanceToCursor / 52.0f);  // Adjust the divisor to control the opacity change
		             if (opacityToCursor > 0.0f){
			         ImU32 lineColorToCursor = ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, opacityToCursor));
			         pDrawList->AddLine(cursorPos, particlePositions[i], lineColorToCursor);}}
	                 float deltaTime = ImGui::GetIO().DeltaTime;
	                 for (int i = 0; i < numParticles; ++i){
		             particlePositions[i].x += particleVelocities[i].x * deltaTime;
		             particlePositions[i].y += particleVelocities[i].y * deltaTime;	 
		             if (particlePositions[i].x < ImGui::GetWindowPos().x)
			         particlePositions[i].x = ImGui::GetWindowPos().x + ImGui::GetWindowSize().x;
		             else if (particlePositions[i].x > ImGui::GetWindowPos().x + ImGui::GetWindowSize().x)particlePositions[i].x = ImGui::GetWindowPos().x;
		             if (particlePositions[i].y < ImGui::GetWindowPos().y)particlePositions[i].y = ImGui::GetWindowPos().y + ImGui::GetWindowSize().y;
		             else if (particlePositions[i].y > ImGui::GetWindowPos().y + ImGui::GetWindowSize().y)
		          	 particlePositions[i].y = ImGui::GetWindowPos().y;
		             ImU32 particleColour = ImGui::ColorConvertFloat4ToU32(settings::particleColour);
		             pDrawList->AddCircleFilled(particlePositions[i], 1.5f, particleColour);}
					
					
					 
					
					
