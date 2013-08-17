/*Copyright Somnambulant Studios 2012-2013*/
#include "auxil.h"
#include "gl-compat.h"
#include "interface.h"
#include "session.h"
#include "thing.h"
#include <SDL/SDL_opengl.h>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

using std::to_string;

void interface::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		glScalef(scalingFactor, scalingFactor, 0.0f);
		glViewport(0, 0, screenWidth*scalingFactor, screenHeight*scalingFactor);
		if(!select[0] || !select[1]) drawCSelect();
		else drawGame();
		if(rMenu != 0) drawRematchMenu();
		else if(pMenu != 0) drawPauseMenu();
	glPopMatrix();
	SDL_GL_SwapBuffers();
}

void interface::drawCSelect()
{
	char buffer[20];
	int x, y;
	glColor4f(0.1f, 0.1f, 0.1f, 1.0f);
	glRectf(0.0f, 0.0f, (GLfloat)screenWidth, (GLfloat)screenHeight);

	for(int i = 0; i < 2; i++){
		if(configMenu[i]) drawConfigMenu(i);
		else if (menu[i]) drawMainMenu(i);
	}
	glEnable( GL_TEXTURE_2D );

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, selectScreen);
	glBegin(GL_QUADS);
		glTexCoord2i(0, 0);
		glVertex3f(350.0f, 0.0f, 0.f);

		glTexCoord2i(1, 0);
		glVertex3f(1250.0f, 0.0f, 0.f);

		glTexCoord2i(1, 1);
		glVertex3f(1250.0f, 900.0f, 0.f);

		glTexCoord2i(0, 1);
		glVertex3f(350.0f, 900.0f, 0.f);
	glEnd();

	for(int i = 0; i < 2; i++){
		if(!menu[i]){
			sprintf(buffer, "P%i", i+1);
			x = ((float)screenWidth/2.0 + ((float)screenHeight/3.0) * cos(((M_PI*2.0)/(float)numChars)*(float)selection[i]+M_PI/4.0+M_PI/2.0)) - 100.0;
			y = ((float)screenHeight/2.0 + ((float)screenHeight/3.0) * sin(((M_PI*2.0)/(float)numChars)*(float)selection[i]+M_PI/4.0+M_PI/2.0));
			glColor4f(0.0, 0.3+i*0.3, 0.3+(1-i)*0.3, 1.0-select[i]*0.5);
			drawGlyph(buffer, x, 200, y, 50, i*2);
		}
	}

	glDisable( GL_TEXTURE_2D );

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void interface::drawMainMenu(int ID)
{
	glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
	char buffer[200];
	glRectf(0.0f + 800.0 * ID, 0.0, (screenWidth/2*ID) + (GLfloat)screenWidth/2.0, (GLfloat)screenHeight);
	glEnable( GL_TEXTURE_2D );
	glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(menu[ID] == 1)*0.4);
	if(analytics) sprintf(buffer, "Replay");
	else sprintf(buffer, "No Replay");
	drawGlyph(buffer, 20 + 1260*ID, 300, 290, 40, 2*ID);

	glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(menu[ID] == 2)*0.4);
	drawGlyph("Key Config", 20 + 1260*ID, 300, 330, 40, 2*ID);
	glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(menu[ID] == 3)*0.4);
	drawGlyph("Exit Menu", 20 + 1260*ID, 300, 370, 40, 2*ID);

	glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(menu[ID] == 4)*0.4);
	if(shortcut) sprintf(buffer, "Rematch");
	else sprintf(buffer, "Reselect");
	drawGlyph(buffer, 20 + 1260*ID, 300, 410, 40, 2*ID);

	glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(menu[ID] == 5)*0.4);
	if(scripting) sprintf(buffer, "Scripts on");
	else sprintf(buffer, "Scripts off");
	drawGlyph(buffer, 20 + 1260*ID, 300, 450, 40, 2*ID);

	glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(menu[ID] == 6)*0.4);
	if(pauseEnabled) sprintf(buffer, "Pause on");
	else sprintf(buffer, "Pause off");
	drawGlyph(buffer, 20 + 1260*ID, 300, 490, 40, 2*ID);

	glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(menu[ID] == 7)*0.4);
	if(P[ID]->boxen && P[ID]->sprite) sprintf(buffer, "Both");
	else if(P[ID]->boxen) sprintf(buffer, "Boxen");
	else sprintf(buffer, "Sprites");
	drawGlyph(buffer, 20 + 1260*ID, 300, 530, 40, 2*ID);

	glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(menu[ID] == 8)*0.4);
	drawGlyph("Quit Game", 20 + 1260*ID, 300, 570, 40, 2*ID);
	glDisable( GL_TEXTURE_2D );
	glColor4f(1.0, 1.0, 1.0, 1.0f);
}

void interface::drawConfigMenu(int ID)
{
	int i;
	glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
	char buffer[200];
	glRectf(0.0f + 800.0 * ID, 0.0, (screenWidth/2*ID) + (GLfloat)screenWidth/2.0, (GLfloat)screenHeight);
	glEnable( GL_TEXTURE_2D );
	switch(p[ID]->input[0]->trigger.type){
	case SDL_KEYDOWN:
		sprintf(buffer, "Keyboard");
		break;
	case SDL_JOYBUTTONDOWN:
		sprintf(buffer, "Joy %i", p[ID]->input[0]->trigger.jaxis.which);
		break;
	case SDL_JOYAXISMOTION:
		sprintf(buffer, "Joy %i", p[ID]->input[0]->trigger.jbutton.which);
		break;
	case SDL_JOYHATMOTION:
		sprintf(buffer, "Joy %i", p[ID]->input[0]->trigger.jhat.which);
		break;
	}
	glColor4f(1.0, 1.0, 0.0, 0.4 + (float)(configMenu[ID] == 1)*0.4);
	drawGlyph(buffer, 20 + 1260*ID, 300, 310, 40, 2*ID);
	for(i = 2; i < 7; i++){
		sprintf(buffer, "%s", p[ID]->inputName[i+2].c_str());
		glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(configMenu[ID] == i)*0.4);
		drawGlyph(buffer, 20 + 1230*ID, 300, 310+40*(i-1), 40, 0);
		int a = 0;
		for(unsigned int j = 0; j < p[ID]->input.size(); j++)
			if(p[ID]->input[j]->effect == 1 << (i+2)){
				switch(p[ID]->input[j]->trigger.type){
				case SDL_KEYDOWN:
					sprintf(buffer, "%s", SDL_GetKeyName(p[ID]->input[j]->trigger.key.keysym.sym));
					a = 1;
					break;
				case SDL_JOYBUTTONDOWN:
					sprintf(buffer, "B%i", p[ID]->input[j]->trigger.jbutton.button);
					a = 2;
					break;
				case SDL_JOYAXISMOTION:
					a = 3;
					sprintf(buffer, "Axis %i %i", p[ID]->input[j]->trigger.jaxis.axis,
						p[ID]->input[j]->trigger.jaxis.value);
					break;
				case SDL_JOYHATMOTION:
					a = 4;
					sprintf(buffer, "Hat %i %i", p[ID]->input[j]->trigger.jhat.hat,
						p[ID]->input[j]->trigger.jhat.value);
					break;
			}
		}
		if(!a){ 
			sprintf(buffer, "Not Set");
			glColor4f(1.0, 0.0, 0.0, 0.4 + (float)(configMenu[ID] == i)*0.4);
		} else glColor4f(1.0, 1.0, 0.0, 0.4 + (float)(configMenu[ID] == i)*0.4);
		drawGlyph(buffer, 70 + 1230*ID, 300, 310+40*(i-1), 40, 0);
	}
	glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(configMenu[ID] == 7)*0.4);
	drawGlyph("Exit Menu", 20 + 1260*ID, 300, 310+40*(i-1), 40, 2*ID);
	glDisable( GL_TEXTURE_2D );
	glColor4f(1.0, 1.0, 1.0, 1.0f);
}

void interface::drawLoadingScreen()
{
	glPushMatrix();
		glScalef(scalingFactor, scalingFactor, 0.0f);
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glRectf(0.0f, 0.0f, (GLfloat)screenWidth, (GLfloat)screenHeight);
		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		drawGlyph("Loading", 0, screenWidth, (screenHeight - 64)/2, 64, 1);
	glPopMatrix();
}

void interface::drawGame()
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable( GL_TEXTURE_2D );
	glBindTexture(GL_TEXTURE_2D, background);
	glPushMatrix();
		glTranslatef(-bg.x, bg.y, 0);
		glBegin(GL_QUADS);
		glTexCoord2i(0, 0);
		glVertex3f(0.0f, 0.0f, 0.f);

		glTexCoord2i(1, 0);
		glVertex3f((GLfloat)(bg.w), 0.0f, 0.f);

		glTexCoord2i(1, 1);
		glVertex3f((GLfloat)(bg.w), (GLfloat)(bg.h), 0.f);

		glTexCoord2i(0, 1);
		glVertex3f(0.0f, (GLfloat)(bg.h), 0.f);
		glEnd();
	glPopMatrix();
	drawHUD();
	glPushMatrix();
		glTranslatef(-bg.x, (bg.y+bg.h), 0);
		for(instance *i:things){ 
			i->draw();
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}
		for(player *i:P) i->drawHitParticle();
		glEnable( GL_TEXTURE_2D );
		glDisable( GL_TEXTURE_2D );
	glPopMatrix();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glEnable( GL_TEXTURE_2D );
	glDisable( GL_TEXTURE_2D );

	if(freeze > 0){
		glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
		glRectf(0.0f, 0.0f, (GLfloat)screenWidth, (GLfloat)screenHeight);
	}
}

void interface::drawHint(int i)
{
	if(blockFail[i]){
		if(blockFail[i] & 1){
			if(!(blockFail[i] & 2)){
				glColor4f(0.0, 1.0, 0.0, 0.7);
				drawGlyph("low", 0, 400, 300, 55, 2*i);
			}
		} else if(blockFail[i] & 2){
			glColor4f(1.0, 0.6, 0.6, 0.7);
			drawGlyph("high", 0, 400, 300, 55, 2*i);
		} else if(blockFail[i] & 4){
			if(blockFail[i] & 8) glColor4f(1.0, 0.0, 0.0, 0.7);
			else glColor4f(0.0, 0.0, 1.0, 0.7);
			drawGlyph("air", 0, 400, 300, 55, 2*i);
		} else if(blockFail[i] & 8){
			glColor4f(1.0, 0.0, 0.0, 0.7);
			drawGlyph("unblock", 0, 300, 500, 55, 2*i);
		}
	}
}

void interface::drawHUD()
{
	char buffer[200];
	if(timer / 60 > 99) sprintf(buffer, "99");
	else if(timer / 60 < 10){
		glColor4f(1.0, 0.0, 0.0, 1.0);
		sprintf(buffer, "0%i", timer / 60);
	}
	else sprintf(buffer, "%i", timer / 60);

	drawGlyph(buffer, 700, 200, 0, 90, 1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	for(unsigned int i = 0; i < P.size(); i++){
		if(P[i]->name.size()) drawGlyph(P[i]->name, 100+800*i, 600, 30, 40, 0+2*i);
		else drawGlyph(things[i]->pick()->name, 100+800*i, 600, 30, 40, 0+2*i);
		if(P[i]->reversalPossible()){
			glDisable( GL_TEXTURE_2D );
			glPushMatrix();
				glTranslatef(50+i*1470, 860, 0);
				glColor4f(0.0, 1.0, 0.0, 1.0);
				glRectf(0.0, 0.0, 30.0, 30.0);
			glPopMatrix();
			glEnable( GL_TEXTURE_2D );
		}
		glPushMatrix();
			glTranslatef(100+i*1000, 0, 0);
			drawHint(i);
		glPopMatrix();
		if(counterHit[i] > 0){
			glColor4f(1.0, 1.0, 0.5, 0.7);
			drawGlyph("Counter", 100+1000*i, 400, 200, 55, 2*i);
		} else if(punish[i] > 0){
			glColor4f(0.0, 0.0, 0.6, 0.7);
			drawGlyph("Counter", 100+1000*i, 400, 200, 55, 2*i);
		}
		glColor4f(1.0, 1.0, 1.0, 1.0);
		if(P[i]->record){
			glColor4f(0.5, 1.0, 1.0, 0.7);
			drawGlyph("Recording", 100+1000*i, 600, 200, 55, 2*i);
			glColor4f(1.0, 1.0, 1.0, 1.0);
		}
		/*
		if(P[i]->current.reversalFlag && P[i]->current.frame + 5 < P[i]->current.move->frames){
			glColor4f(1.0, 0.0, 0.0, 1.0);
			drawGlyph("Autolink", 100+800*i, 600, 600, 35, 0+2*i);
			glColor4f(1.0, 1.0, 1.0, 1.0);
		}
		//*/
		if(combo[i] > 1){
			glColor4f(1.0, 1.0-.5*illegit[i], 1.0-.5*illegit[i], 1.0);
			sprintf(buffer, "%i hits", combo[i]);
			drawGlyph(buffer, 100+800*i, 600, 400, 75, 0+2*i);
			sprintf(buffer, "%i damage", damage[i]);
			drawGlyph(buffer, 100+800*i, 600, 475, 35, 0+2*i);
			glColor4f(1.0, 1.0, 1.0, 1.0);
		}
	}

	if(timer > 100 * 60 && timer < 100 * 60 + 31){ 
		int l = P[0]->rounds + P[1]->rounds + 1;
		sprintf(buffer, "Round %i", l);
		if(timer == 100 * 60 + 30){
			play(1);
			play(0);
			//Mix_PlayChannel(3, announceRound[l - 1], 0);
		}
		drawGlyph(buffer, 0, 1600, 375, 150, 1);
	}
	if(timer > 99 * 60 && timer < 99 * 60 + 31){ 
		drawGlyph("FIGHT", 0, 1600, 375, 150, 1);
		if(timer == 99 * 60 + 30)
			Mix_PlayChannel(3, announceFight, 0);
	}
	if(roundEnd && endTimer > 5 * 60 - 31){ 
		if(things[0]->current.meter[0] > 0 && things[1]->current.meter[0] > 0){
			drawGlyph("TIME OUT", 0, 1600, 300, 200, 1);
			if(endTimer == 5 * 60 - 1)
				Mix_PlayChannel(3, announceEnd[0], 0);
		} else {
			drawGlyph("DOWN", 0, 1600, 375, 150, 1);
			if(endTimer == 5 * 60 - 1)
				Mix_PlayChannel(3, announceEnd[1], 0);
		}
	}
	if(endTimer > 3 * 60 + 29 && endTimer < 4 * 60){ 
		if(things[0]->current.meter[0] > things[1]->current.meter[0]){ 
			sprintf(buffer, "%s", things[0]->pick()->name.c_str());
			drawGlyph(buffer, 0, 1600, 300, 150, 1);
			drawGlyph("Wins", 0, 1600, 450, 150, 1);
			if(endTimer == 4 * 60 - 1)
				Mix_PlayChannel(3, announceWinner[selection[0]], 0);
		} else if(things[1]->current.meter[0] > things[0]->current.meter[0]){
			sprintf(buffer, "%s", things[1]->pick()->name.c_str());
			drawGlyph(buffer, 0, 1600, 300, 150, 1);
			drawGlyph("Wins", 0, 1600, 450, 150, 1);
			if(endTimer == 4 * 60 - 1)
				Mix_PlayChannel(3, announceWinner[selection[1]], 0);
		} else if(things[0]->current.meter[0] <= 0){ 
			sprintf(buffer, "Double KO");
			drawGlyph(buffer, 0, 1600, 375, 150, 1);
			if(endTimer == 4 * 60 - 1)
				Mix_PlayChannel(3, announceDraw[0], 0);
		} else {
		sprintf(buffer, "Draw");
		drawGlyph(buffer, 0, 1600, 375, 150, 1);
		if(endTimer == 4 * 60 - 1)
			Mix_PlayChannel(3, announceDraw[1], 0);
		}
	}
	glDisable( GL_TEXTURE_2D );
	for(unsigned int i = 0; i < P.size(); i++){
/*		glColor4f(1.0*(P[i]->current.mode == 1), 0.0f, 1.0*(P[i]->current.mode == 2), 1.0f);
		string grv("");
		grv += 'A' - 1 + P[i]->current.mode;
		glEnable( GL_TEXTURE_2D );
		drawGlyph(grv, 1550*i, 50, 850, 50, 2*i);
		glDisable( GL_TEXTURE_2D );
*/		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		P[i]->drawMeters(numRounds);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	glEnable( GL_TEXTURE_2D );
}

void interface::drawPauseMenu()
{
	glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
	glRectf(0.0, 0.0, (GLfloat)screenWidth, (GLfloat)screenHeight);
	glEnable( GL_TEXTURE_2D );
	glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(pMenu == 1)*0.4);
	drawGlyph("Unpause", 0, 1600, 360, 60, 1);
	glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(pMenu == 2)*0.4);
	drawGlyph("Character Select", 0, 1600, 420, 60, 1);
	glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(pMenu == 3)*0.4);
	drawGlyph("Quit Game", 0, 1600, 480, 60, 1);
	glDisable( GL_TEXTURE_2D );
	glColor4f(1.0, 1.0, 1.0, 1.0f);
}

void interface::drawRematchMenu()
{
	glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
	glRectf(0.0, 0.0, (GLfloat)screenWidth, (GLfloat)screenHeight);
	glEnable( GL_TEXTURE_2D );
	glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(rMenu == 1)*0.4);
	drawGlyph("Rematch", 0, 1600, 360, 60, 1);
	glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(rMenu == 2)*0.4);
	drawGlyph("Character Select", 0, 1600, 420, 60, 1);
	glColor4f(0.0, 0.0, 1.0, 0.4 + (float)(rMenu == 3)*0.4);
	drawGlyph("Quit Game", 0, 1600, 480, 60, 1);
	glDisable( GL_TEXTURE_2D );
	glColor4f(1.0, 1.0, 1.0, 1.0f);
}

void player::drawMeters(int n)
{
	vector<SDL_Rect> r (n);
	for(int i = 0; i < n; i++){
		r[i].y = 24; r[i].w = 20; r[i].h = 10;
		if(ID == 1) r[i].x = 680 - 24 * i; 
		else r[i].x = 900 + 24 * i;
	}
	for(int i = 0; i < n; i++){
		if(rounds > i) glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
		else glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glRectf((GLfloat)(r[i].x), (GLfloat)(r[i].y), (GLfloat)(r[i].x + r[i].w), (GLfloat)(r[i].y + r[i].h));
	}
	glFlush();
	int h = 0;
	if(current.move){
		if(current.move->hidesMeter) h = current.move->cost;
	}
	pick()->drawMeters(ID, h, current);
	glFlush();
}

void character::drawMeters(int ID, int hidden, status &current)
{
	SDL_Rect m, h, g;
	if(current.meter[0] >= 0) h.w = current.meter[0]; else h.w = 1; 

	if(ID == 1) h.x = 100 + (600 - h.w); 
	else h.x = 900;
	h.h = 10;
	h.y = 10;

	int R = 0, G = 255, B = 0;
	if(current.meter[1] >= 0) m.w = (current.meter[1]+hidden)*2; else m.w = 0;
	if(hidden) g.w = 0; else g.w = current.meter[4]*2;
	if(ID == 1){ 
		m.x = 100;
		g.x = m.x + m.w;
	} else {
		m.x = 900 + (600 - m.w);
		g.x = m.x - g.w;
	}
	m.h = 10; m.y = 860;
	g.h = 10; g.y = 860;

	G = (m.w == 600) ? 255 : ((m.w / 150) % 2);
	if(m.w < 300) R = 191;
	else if(m.w < 600) B = 255;
	glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
	glRectf((GLfloat)(ID == 1 ? 100 : 900), (GLfloat)(h.y), (GLfloat)(ID == 1 ? 700 : 1500), (GLfloat)(h.y + h.h));
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glRectf((GLfloat)(h.x), (GLfloat)(h.y), (GLfloat)(h.x + h.w), (GLfloat)(h.y + h.h));
	glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
	glRectf((GLfloat)(ID == 1 ? 100 : 900), (GLfloat)(m.y), (GLfloat)(ID == 1 ? 700 : 1500), (GLfloat)(m.y + m.h));
	glColor4f((float)R, (float)G, (float)B, 1.0f);
	glRectf((GLfloat)(m.x), (GLfloat)(m.y), (GLfloat)(m.x + m.w), (GLfloat)(m.y + m.h));
	glColor4f((float)R, (float)G, (float)B, 0.6f);
	glRectf((GLfloat)(g.x), (GLfloat)(g.y), (GLfloat)(g.x + g.w), (GLfloat)(g.y + g.h));
}

void instance::drawBoxen()
{
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	glPushMatrix();
		glTranslatef(collision.x, -collision.y, 0);
		glRectf(0.0f, 0.0f, (GLfloat)(collision.w), (GLfloat)(-collision.h));
	glPopMatrix();
	for(unsigned int i = 0; i < hitreg.size(); i++){
		glFlush();
		glColor4f(0.0f, 1.0f, (GLfloat)(ID - 1.0f)/2.0f, 0.5f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glPushMatrix();
			glTranslatef(hitreg[i].x, -hitreg[i].y, 0);
			glRectf(0.0f, 0.0f, (GLfloat)(hitreg[i].w), (GLfloat)(-hitreg[i].h));
		glPopMatrix();
	}
	for(unsigned int i = 0; i < current.move->hitbox[current.frame].size(); i++){
		glFlush();
		glColor4f(1.0f, 0.0f, (GLfloat)(ID - 1.0f)/2.0f, 0.5f);
		glPushMatrix();
			glTranslatef(current.move->hitbox[current.frame][i].x*current.facing + current.posX, -(current.move->hitbox[current.frame][i].y + current.posY), 0);
			glRectf(0.0f, 0.0f, (GLfloat)(current.move->hitbox[current.frame][i].w*current.facing), (GLfloat)(-(current.move->hitbox[current.frame][i].h)));
		glPopMatrix();
	}
	glFlush();
	glDisable( GL_TEXTURE_2D );
}

void instance::draw()
{
	bool sCheck = spriteCheck();
	status * n;
	if(sCheck && save.facing && particleType == 1 && current.freeze && current.counter) n = &save;
	else n = &current;

	if(n == &current){
		n->drawX = n->posX;
		n->drawY = n->posY;

		if(n->move->offX != 0) n->drawX += n->move->offX*n->facing;
		else{
			if(n->facing == 1){
				if(collision.x < n->drawX) n->drawX = collision.x;
				for(unsigned int i = 0; i < hitreg.size(); i++){
					if(hitreg[i].x < n->drawX) n->drawX = hitreg[i].x;
				}
				for(unsigned int i = 0; i < hitbox.size(); i++){
					if(hitbox[i].x < n->drawX) n->drawX = hitbox[i].x;
				}
			} else {
				if(collision.x + collision.w > n->drawX) n->drawX = collision.x + collision.w;
				for(unsigned int i = 0; i < hitreg.size(); i++){
					if(hitreg[i].x + hitreg[i].w > n->drawX) n->drawX = hitreg[i].x + hitreg[i].w;
				}
				for(unsigned int i = 0; i < hitbox.size(); i++){
					if(hitbox[i].x + hitbox[i].w > n->drawX) n->drawX = hitbox[i].x + hitbox[i].w;
				}
			}
		}
		if(n->move->offY != 0) n->drawY += n->move->offY;
		else{
			if(collision.y < n->drawY) n->drawY = collision.y;
			for(unsigned int i = 0; i < hitreg.size(); i++){
				if(hitreg[i].y < n->drawY) n->drawY = hitreg[i].y;
			}
			for(unsigned int i = 0; i < hitbox.size(); i++){
				if(hitbox[i].y < n->drawY) n->drawY = hitbox[i].y;
			}
		}
	}
	glEnable(GL_TEXTURE_2D);
	if(sprite && sCheck){
		if(secondInstance)
			glColor4f(0.75f, 0.5f, 0.85f, 1.0f);
		glPushMatrix();
			glTranslatef(n->drawX, -n->drawY, 0);
			glPushMatrix();
				glScalef((float)n->facing, 1.0, 1.0);
				pick()->draw(n->move, n->frame);
			glPopMatrix();
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
	if(!sCheck || boxen){
		if(!n->move || n->frame > n->move->frames){
			glPushMatrix();
				glTranslatef(current.drawX, -current.drawY, 0);
				glPushMatrix();
					glScalef((float)n->facing, 1.0, 1.0);
					pick()->neutral->drawBoxen(0);
				glPopMatrix();
			glPopMatrix();
		} else drawBoxen();
	}
	if(n == &current) save = current;
}

void player::drawHitParticle()
{
	/*Stand-in for now, just to indicate block type*/
	if(particleLife > 0){
		switch (particleType){
		case 1:
			glColor4f(1.0f, 0.0f, 0.0f, 0.7f);
			break;
		case 0:
			glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
			break;
		case -1:
			glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
			break;
		case -2:
			glColor4f(1.0f, 1.0f, 0.0f, 0.7f);
			break;
		case -5:
			glColor4f(0.4f, 0.4f, 0.4f, 0.5f);
		}
		glPushMatrix();
			glTranslatef(current.posX, 0.0f, 0.0f);
			glPushMatrix();
				glTranslatef(0.0f, -collision.y, 0.0f);
				glRectf((GLfloat)(-10*current.facing), (GLfloat)(-collision.h), (GLfloat)(50 * current.facing), (GLfloat)(-collision.h - 40));
			glPopMatrix();
			for(SDL_Rect i:hitLocation){
				glPushMatrix();
					glTranslatef(i.x, -current.posY - i.y - i.h, 0.0f);
					glRectf(0.0f, 0.0f, i.w, i.h);
				glPopMatrix();
			}
		glPopMatrix();
		particleLife--;
	} else {
		blockType = 0;
		hitLocation.clear();
	}
}

void avatar::draw(action *& cMove, int f)
{
	cMove->draw(f);
}

int gameInstance::drawGlyph(string s, int x, int space, int y, int height, int just)
{
	int w, h, width = 0, padding = 0, totalWidth = 0;
	if(just != 0){
		for(char c : s){
			if(c == ' ') totalWidth += w * sf / 2;
			else if(c == '\0');
			else{
				glBindTexture(GL_TEXTURE_2D, glyph[toupper(c)]);
				glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
				glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
				sf = (float)height / (float)h;
				totalWidth += w * sf;
			}
		}
		if(just == 2) padding = space - totalWidth;
		else padding = (space - totalWidth) / 2;
	}

	float sf;
	for(char c : s){
		if(c == ' ') x += (float)width / 2.0;
		else{
			glBindTexture(GL_TEXTURE_2D,glyph[toupper(c)]);

			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
			sf = (float)height / (float)h;
			width = w * sf;
			glPushMatrix();
				glTranslatef(x + padding, y, 0.f);
				glBegin(GL_QUADS);
				glTexCoord2i(0, 0);
				glVertex3f(0, 0, 0.f);

				glTexCoord2i(1, 0);
				glVertex3f(width, 0, 0.f);

				glTexCoord2i(1, 1);
				glVertex3f(width, height, 0.f);

				glTexCoord2i(0, 1);
				glVertex3f(0, height, 0.f);
				glEnd();
			glPopMatrix();
			x += (float)width;
		}
	}
	return x;
}

void action::draw(int f)
{
	if(modifier && basis.move) basis.move->draw(basis.frame);
	if(sprite[f]){
		glBindTexture(GL_TEXTURE_2D, sprite[f]);
		glBegin(GL_QUADS);
		glTexCoord2i(0, 0);
		glVertex3f(0.0f, (GLfloat)(-height[f]), 0.f);

		glTexCoord2i(1, 0);
		glVertex3f((GLfloat)(width[f]), (GLfloat)(-height[f]), 0.f);

		glTexCoord2i(1, 1);
		glVertex3f((GLfloat)(width[f]), 0.0f, 0.f);

		glTexCoord2i(0, 1);
		glVertex3f(0.0f, 0.0f, 0.f);
		glEnd();
	}
}

bool instance::spriteCheck()
{
	if(current.move) return current.move->spriteCheck(current.frame);
	else return 0;
}
bool avatar::spriteCheck(action *& cMove, int f)
{
	if(cMove == nullptr) return 0;
	else return cMove->spriteCheck(f);
}

bool action::spriteCheck(int f)
{
	if(modifier && basis.move) basis.move->spriteCheck(basis.frame);
	if(sprite.empty()) return 0;
	else if(sprite[f] != 0) {
		return 1;
	}
	else return 0;
}

void interface::writeImage(string movename, int frame, action * move)
{
	int Y = 0;
	int X = 0;
	SDL_Surface * image = nullptr;
	int maxY = move->collision[frame].y + move->collision[frame].h,
	    maxX = move->collision[frame].x + move->collision[frame].w;
	for(unsigned int i = 0; i < move->hitreg[frame].size(); i++){
		if(move->hitreg[frame][i].y < Y)
			Y = move->hitreg[frame][i].y;
		if(move->hitreg[frame][i].x < X)
			X = move->hitreg[frame][i].x;
		if(move->hitreg[frame][i].x + move->hitreg[frame][i].w > maxX)
			maxX = move->hitreg[frame][i].x + move->hitreg[frame][i].w;
		if(move->hitreg[frame][i].y + move->hitreg[frame][i].h > maxY)
			maxY = move->hitreg[frame][i].y + move->hitreg[frame][i].h;
	}
	for(unsigned int i = 0; i < move->hitbox[frame].size(); i++){
		if(move->hitbox[frame][i].y < Y) 
			Y = move->hitbox[frame][i].y;
		if(move->hitbox[frame][i].x < X) 
			X = move->hitbox[frame][i].x;
		if(move->hitbox[frame][i].x + move->hitbox[frame][i].w > maxX)
			maxX = move->hitbox[frame][i].x + move->hitbox[frame][i].w;
		if(move->hitbox[frame][i].y + move->hitbox[frame][i].h > maxY)
			maxY = move->hitbox[frame][i].y + move->hitbox[frame][i].h;
	}
	int w = maxX + X;
	int h = maxY + Y;
	int x = 0;
	int y = 0;
	if(Y < 0){ 
		h -= Y;
		y = -Y;
	}
	if(X < 0){
		w -= X;
		x = -X;
	}
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	Uint32 rmask = 0xff000000;
	Uint32 gmask = 0x00ff0000;
	Uint32 bmask = 0x0000ff00;
	Uint32 amask = 0x000000ff;
#else
	Uint32 rmask = 0x000000ff;
	Uint32 gmask = 0x0000ff00;
	Uint32 bmask = 0x00ff0000;
	Uint32 amask = 0xff000000;
#endif
	image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
				 rmask, gmask, bmask, amask);
	screenInit(w, h);



	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glRectf(0.0f, 0.0f, (GLfloat)w, (GLfloat)h);

	glPushMatrix();
		glTranslatef(-x, -(y - h), 0.0);
		move->drawBoxen(frame);
	glPopMatrix();

	glReadPixels(0, 0, w, h, GL_RGBA, ___gufg_tex_mode, image->pixels);

	SDL_GL_SwapBuffers();

	string f("dump/"+movename+"#"+to_string(frame)+".bmp");
	if(SDL_SaveBMP(image, f.c_str())) printf("You dun fucked up\n");
}

void action::drawBoxen(int frame){
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	glRectf((GLfloat)(collision[frame].x), (GLfloat)(-collision[frame].y), (GLfloat)(collision[frame].x + collision[frame].w), (GLfloat)(-collision[frame].y - collision[frame].h));
	for(unsigned int i = 0; i < hitreg[frame].size(); i++){
		glFlush();
		glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
		glRectf((GLfloat)(hitreg[frame][i].x), (GLfloat)(-hitreg[frame][i].y), (GLfloat)(hitreg[frame][i].x + hitreg[frame][i].w), (GLfloat)(-hitreg[frame][i].y - hitreg[frame][i].h));
	}
	for(unsigned int i = 0; i < hitbox[frame].size(); i++){
		glFlush();
		glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
		glRectf((GLfloat)(hitbox[frame][i].x), (GLfloat)(-hitbox[frame][i].y), (GLfloat)(hitbox[frame][i].x + hitbox[frame][i].w), (GLfloat)(-hitbox[frame][i].y - hitbox[frame][i].h));
	}
	glFlush();
}

bool gameInstance::screenInit(int w, int h)
{
	/*Initialize SDL*/
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
	/*WM stuff*/
	if(window::screen){ 
		SDL_FreeSurface(screen);
		screen = nullptr;
	}
	SDL_WM_SetCaption("GUFG", "GUFG");
	if((screen = SDL_SetVideoMode(w, h, 32, SDL_OPENGL)) == nullptr)
		return false;
	SDL_ShowCursor(SDL_DISABLE);

	/*Set up input buffers and joysticks*/
	for(int i = 0; i < SDL_NumJoysticks(); i++)
		SDL_JoystickOpen(i);
//	glDisable (GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable (GL_BLEND);
	glEnable (GL_POINT_SMOOTH);
	glEnable (GL_LINE_SMOOTH);
	glEnable (GL_POLYGON_SMOOTH);

	glHint (GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0f);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, 1, -1);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	initd = true;
	return true;
}

void session::draw(model & object)
{
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	glPushMatrix(); 
	glPushMatrix(); 
	glMatrixMode( GL_PROJECTION );
	gluPerspective(100.0, 1.5, 1.0, 150.0);
	float modelColor[] = { r, g, b, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, modelColor);
	glMatrixMode( GL_MODELVIEW );
	glTranslatef(camX, camY, camZ);
	glPushMatrix(); 
	glRotatef(spin, 0.0, 0.0, 1.0f);
	glPushMatrix(); 
	glRotatef(pan, 0.0, 1.0, 0.0f);
	glPushMatrix(); 
	glRotatef(tilt, 1.0, 0.0, 0.0f);
	glPushMatrix();
	object.draw();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix(); 
	SDL_GL_SwapBuffers();
}

void model::draw()
{
/* Load the identity matrix into modelmatrix. rotate the model, and move it back 5 */
	vect v;
	for(unsigned int i = 0; i < faces.size(); i ++){
		v.unitNormal( vertices[0][faces[i][0]-1], vertices[1][faces[i][0]-1], vertices[2][faces[i][0]-1],
				vertices[0][faces[i][1]-1], vertices[1][faces[i][1]-1], vertices[2][faces[i][1]-1],
				vertices[0][faces[i][2]-1], vertices[1][faces[i][2]-1], vertices[2][faces[i][2]-1]);
		switch (faces[i].size()){
		case 3:
			glBegin(GL_TRIANGLES);
				glNormal3f(v.x, v.y, v.z);
				glVertex3f(vertices[0][faces[i][0]-1], vertices[1][faces[i][0]-1], vertices[2][faces[i][0]-1]);
				glVertex3f(vertices[0][faces[i][1]-1], vertices[1][faces[i][1]-1], vertices[2][faces[i][1]-1]);
				glVertex3f(vertices[0][faces[i][2]-1], vertices[1][faces[i][2]-1], vertices[2][faces[i][2]-1]);
			glEnd();
			break;
		case 4:
			glBegin(GL_QUADS);
				glNormal3f(v.x, v.y, v.z);
				glVertex3f(vertices[0][faces[i][0]-1], vertices[1][faces[i][0]-1], vertices[2][faces[i][0]-1]);
				glVertex3f(vertices[0][faces[i][1]-1], vertices[1][faces[i][1]-1], vertices[2][faces[i][1]-1]);
				glVertex3f(vertices[0][faces[i][2]-1], vertices[1][faces[i][2]-1], vertices[2][faces[i][2]-1]);
				glVertex3f(vertices[0][faces[i][3]-1], vertices[1][faces[i][3]-1], vertices[2][faces[i][3]-1]);
			glEnd();
			break;
		}
	}
}
