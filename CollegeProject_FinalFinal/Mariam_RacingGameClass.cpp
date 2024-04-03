//#include "RacingGameClass.h"
//// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//#include<iostream>
//#include<vector>
//using namespace std;
//#include "olcConsoleGameEngine.h"
//
//class OneLoneCoder_FormulaOLC : public olcConsoleGameEngine {
//public:
//	OneLoneCoder_FormulaOLC() {
//		m_sAppName = L"Formula OLC";
//	}
//
//private:
//	/*fCarPos is to store the car position as
//	- 1 is on the left and  +1 is on the right so 0.0 is the middle of road */
//	float fCarPos = 0.0f;
//
//	//the distance the car drived in the track
//	float fDistance = 0.0f;
//
//	float fSpeed = 0.0f;
//
//	float fCurvature = 0.0f;
//	float fPlayerCurvature = 0.0f;
//	float fTrackDistance = 0.0f;
//
//	float fCurrentLapTime = 0.0f;
//
//
//	// 1st float is the curve of the one part shown to player , 2nd float is the distance of the part
//	vector<pair<float, float>> vecTrack;
//protected:
//	virtual bool OnUserCreate() {
//
//		vecTrack.push_back(make_pair(0.0f, 10.0f));
//		vecTrack.push_back(make_pair(0.0f, 200.0f));
//		vecTrack.push_back(make_pair(1.0f, 10.0f));
//		vecTrack.push_back(make_pair(0.0f, 400.0f));
//		vecTrack.push_back(make_pair(-1.0f, 100.0f));
//		vecTrack.push_back(make_pair(0.0f, 200.0f));
//		vecTrack.push_back(make_pair(-1.0f, 200.0f));
//		vecTrack.push_back(make_pair(1.0f, 200.0f));
//		vecTrack.push_back(make_pair(0.2f, 500.0f));
//		vecTrack.push_back(make_pair(0.0f, 200.0f));
//
//		for (auto t : vecTrack)
//			fTrackDistance += t.second;
//
//
//
//		return true;
//	}
//	virtual bool OnUserCreate(float fElapsedTime) {
//
//		if (m_keys[VK_UP].bHeld)
//			fSpeed += 2.0f * fElapsedTime;
//		else
//			fSpeed -= 1.0f * fElapsedTime;
//
//
//		if (m_keys[VK_RIGHT].bHeld)
//			fPlayerCurvature -= 0.7f * fElapsedTime;
//
//		if (m_keys[VK_LEFT].bHeld)
//			fPlayerCurvature -= 0.7f * fElapsedTime;
//
//		if (fabs(fPlayerCurvature - fTrackCurvature) >= 0.8f)
//			fSpeed -= 5.0f * fElapsedTime;
//
//		if (fSpeed < 0.0f)   fSpeed = 0.0f;
//		if (fSpeed > 1.0f)   fSpeed = 1.0f;
//
//		fDistance += (70.0f * fSpeed) * V;
//
//		//get point on track
//		float fOffset = 0;
//		int nTrackSection = 0;
//
//		fCurrentLapTime += fElapsedTime;
//
//		if (fDistance >= fTrackDistance)
//		{
//			fDistance -= fTrackDistance;
//			fCurrentLapTime = 0.0f;
//		}
//
//		//get your position on the track
//		while (nTrackSection < vecTrack.size() && fOffset <= fDistance)
//		{
//			fOffset += vecTrack[nTrackSection].second;
//			nTrackSection++;
//		}
//
//		//this will angle the track of to give feel of curves in track and not linear
//		float fTargetCurvature = vecTrack[nTrackSection - 1].first;
//
//		float fTrackCurveDiff = (fTargetCurvature - fCurvature) * fElapsedTime * fSpeed;
//		fCurvature += fTrackCurveDiff
//
//			fTrachCurvature += (fCurvature)*fElapsedTime * fSpeed;
//
//		Fill(0, 0, ScreenWidth(), ScreenWidth(), L' ', 0);
//
//		// creating the track at the botton half of the screen
//		for (int y = 0; y < ScreenHeight() / 2; y++) {
//			for (int x = 0; x < ScreenWidth(); x++) {
//
//				// for better drawn car (adding prespective to the car)
//				//here the prespective will inc be inc of y and vice verse
//				float fPerspective = (float)y / (ScreenHeight() / 2.0f);
//
//				/*dividing the screen so that the left is 0 and right is 1
//				and this formula is to link the curves to the perspective and the track all together
//				to make better sense of road*/
//				float fMiddlePoint = 0.5f + fCurvature * powf((1.0f - fPerspective), 3);
//
//				// to make the road more realistic not linear
//				float fRoadWidth = 0.1f + fPerspective * 0.8f;
//
//				// the frames of the road is designed to be 15% of the road width
//				float fClipWidth = fRoadWidth * 0.15f;
//
//				fRoadWidth *= 0.5f;
//
//				int nLeftGrass = (fMiddlePoint - fRoadWidth - fClipWidth) * ScreenWidth();
//				int nLeftClip = (fMiddlePoint - fRoadWidth) * ScreenWidth();
//				int nRightClip = (fMiddlePoint + fRoadWidth) * ScreenWidth();
//				int nRightGrass = (fMiddlePoint + fRoadWidth + fClipWidth) * ScreenWidth();
//
//				int nRow = ScreenHeight() / 2 = y;
//				/*to give the feeling of moving forward,
//				I added some colours to create a feel of moving */
//				//THE FORMULA 
//				//sin(2(1-x)^2 - 0.1distance on x
//				//NEW SYNTAX 
//				//condition ? consequent : alternative
//				int nGrassColour = sinf(20.0f * powf(1.0f - fPerspective, 3) + fDistance * 0.1f) > 0.0f ? FG_GREEN : FG_DARK_GREEN;
//				int nClipColour = sinf(80.0f * powf(1.0f - fPerspective, 3) + fDistance * 0.1f) > 0.0f ? FG_RED : FG_WHITE;
//				int nRoadColour = (nTrackSection - 1) == 0 ? FG_WHITE : FG_GREY;
//				if (x > 0 && x < nLeftGrass)
//					Draw(x, nROW, PIXEL_SOLID, nGrassColour);
//
//				if (x >= nLeftGrass && x < nLeftClip)
//					Draw(x, nROW, PIXEL_SOLID, nClipColour);
//
//				if (x >= nLeftClip && x < nRightClip)
//					Draw(x, nROW, PIXEL_SOLID, FG_GREY);
//
//				if (x >= nRightClip && x < nRightGrass)
//					Draw(x, nROW, PIXEL_SOLID, nClipColour);
//
//				if (x >= nRightGrass && x < ScreenWidth()
//					Draw(x, nROW, PIXEL_SOLID, nGrassColour);
//			}
//		}
//		fCarPos = fPlayerCurvature - fTrackCurvature;
//			// the car body
//			// Drawing the car to be offset of the center by casting the ratio to an integer
//			// 7 is the width of the of car
//			int nCarPos = ScreenWidth() / 2 + ((int)(ScreenWidth() * fCarPos / 2.0f) - 7);
//
//			// draw the car's body
//			//DrawStringAlpha takes any space but doesn't draw it in the background
//			//so it pretends that spaces are transparent
//			//80-86 is the y-axis position and nCarPos is the x-axis position
//
//			DrawStringAlpha(nCarPos, 80, L"   ||####||   ");
//		DrawStringAlpha(nCarPos, 81, L"      ##      ");
//		DrawStringAlpha(nCarPos, 82, L"     ####     ");
//		DrawStringAlpha(nCarPos, 83, L"     ####     ");
//		DrawStringAlpha(nCarPos, 84, L"|||  ####  |||");
//		DrawStringAlpha(nCarPos, 85, L"|||########|||");
//		DrawStringAlpha(nCarPos, 86, L"|||  ####  |||");
//
//		auto disp_time = [](float t)
//		{
//			int nMinutes = t / 60.0f;
//			int nSeconds = t - (nMinutes * 60.0f);
//			int nMilliSeconds = (t - (float)nSeconds * 1000.0f;
//			return to_wstring(nMinutes) + L "." + to_wstring(nSeconds) + L ":" + to_wstring(nMilliSeconds);
//
//				};
//
//		DrawString(10, 8, disp_time(fCurrentLapTime));
//
//		return true;
//	}
//};
//int main() {
//	// creates an  object derived from OneloneCoder_FormulaOLC
//	OneLoneCoder_FormulaOLC game;
//
//	//console is 160 width and 100 height and each is 8x8 pixcels
//	game.ConstructConsole(160, 100, 8, 8);
//	game.Start();
//	return 0;
//}