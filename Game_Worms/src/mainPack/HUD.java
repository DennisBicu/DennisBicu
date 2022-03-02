package mainPack;

import java.awt.Color;
import java.awt.Graphics;

public class HUD {
	
	public static float HEALTH = 100;
	
	private float greenValue = 255;
	
	private int score = 0;
	private int level = 1;
	
	public void tick(){
		HEALTH = Game.clamp(HEALTH, 0, 100);
		greenValue = Game.clamp(greenValue, 0, 255);
		greenValue = HEALTH * 2;
		if (Game.getAlive() && !Game.isVictory()) score++;
	}
	
	public void render(Graphics g){
		g.setColor(Color.gray);
		g.fillRect(10, Game.HEIGHT - 80, 200, 24);
		g.setColor(new Color(100, (int)greenValue, 0)); //new Color (redValue, greenValue, blueValue) 0-255 RGB
		g.fillRect(10, Game.HEIGHT - 80, (int)HEALTH * 2, 24);
		g.setColor(Color.white);
		g.drawRect(10, Game.HEIGHT - 80, 200, 24);
		
		g.drawString("Score: " + score, Game.WIDTH - 130, Game.HEIGHT - 67);
		g.drawString("Level: " + level, Game.WIDTH/2 - 10, Game.HEIGHT - 67);
		
		if(!Game.getAlive()){
			g.drawString("GAME OVER!", Game.WIDTH/2 - 40, Game.HEIGHT/2 - 40);
			g.drawString("Final score: " + score, Game.WIDTH/2 - 47, Game.HEIGHT/2 - 21);
			g.drawString("Press ESC to close.", Game.WIDTH/2 - 57, Game.HEIGHT/2 - 3);
		}
		
		if(Game.isVictory()){
			g.drawString("VICTORY!", Game.WIDTH/2 - 40, Game.HEIGHT/2 - 40);
			g.drawString("Final score: " + score, Game.WIDTH/2 - 47, Game.HEIGHT/2 - 21);
			g.drawString("Press ESC to close.", Game.WIDTH/2 - 57, Game.HEIGHT/2 - 3);
		}
	}

	public int getScore() {
		return score;
	}

	public void setScore(int score) {
		this.score = score;
	}

	public int getLevel() {
		return level;
	}

	public void setLevel(int level) {
		this.level = level;
	}
	
}
