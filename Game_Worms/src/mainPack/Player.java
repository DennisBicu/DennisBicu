package mainPack;

import java.awt.Color;
import java.awt.Graphics;
//import java.awt.Graphics2D;
//import java.util.Random;
import java.awt.Rectangle;

public class Player extends GameObject {

	//private Random r;
	private Handler handler;
	
	public Player (int x, int y, ID id, Handler handler){
		super(x, y, id);
		this.handler = handler;
		velX = 0;
		velY = 0;
	}

	@Override
	public void tick() {
		//X and Y coordinates are being moved with the offset of the velocity
		x = x + velX;
		x = Game.clamp(x, 0, Game.WIDTH - 50);
		y = y + velY;
		y = Game.clamp(y, 1, Game.HEIGHT - 79);
		
		//handler.addObject(new Trail(x, y, 32, 32, 0.1f, ID.Trail, Color.white, handler));
		
		this.collision();
	}

	public void collision(){
		GameObject tempObject = null;
		for (int i = 0; i < handler.objectList.size(); i++){
			tempObject = handler.objectList.get(i); 
			if (tempObject.getID() == ID.BasicEnemy || tempObject.getID() == ID.FastEnemy ||
					tempObject.getID() == ID.SmartEnemy || tempObject.getID() == ID.BossEnemy||
						tempObject.getID() == ID.BossMissile){ //dealing with the interaction with the Enemies
				//collision code
				if (this.getBounds().intersects(tempObject.getBounds())){
//					if (tempObject.getID() == ID.BossEnemy){
//						HUD.HEALTH -= 1.5;
//						if(HUD.HEALTH == 0){
//							handler.clearWave();
//							Game.setAlive(false);
//						}
//						break;
//					}
					HUD.HEALTH -= 1;
					
					if(HUD.HEALTH == 0){
						handler.clearWave();
						Game.setAlive(false);
					}
					
				}
			}
		}
	}
	
	@Override
	public void render(Graphics g) {
		g.setColor(Color.white);
		g.fillRect((int)x, (int)y, 32, 32);
		//g.fillRoundRect(x, y, 32, 32, 16, 16);
		
	}
	
	public Rectangle getBounds(){
		return new Rectangle((int)x, (int)y, 32, 32);
	}
	
}
