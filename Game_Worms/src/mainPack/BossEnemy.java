package mainPack;

import java.awt.Color;
import java.awt.Graphics;
//import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.util.Random;

public class BossEnemy extends GameObject {

	private Handler handler;
	private int timer = 50;
	private int timer2 = 35;
	
	private Random r = new Random();
	
	public BossEnemy(float x, float y, ID id, Handler handler) {
		super(x, y, id);
		this.handler = handler;	
		velX = 0;
		velY = 2;
		
	}

	public void tick() {
		x += velX;
		y += velY;
		
/*		if (y <= 0 || y >= Game.HEIGHT - 80){
			velY *= -1;
		}*/
		if(timer <= 0){ //time to go down until first position
			velY = 0;
			timer2--;
		}
		else timer--;

		if(timer2 <= 0){ //time to start moving left/right
			if (velX == 0) velX = 2.5f;
			
			if (velX > 0) velX += 0.01f;
			else if (velX < 0) velX -= 0.01f;
			
			velX = Game.clamp(velX, -10, 10);
			
			int spawnMissiles = r.nextInt(8);
			if (spawnMissiles == 0) handler.addObject(new BossMissile(x + 48, y + 80, ID.BossMissile, handler));
		}
		if (x <= 0 || x >= Game.WIDTH - 110){
			velX *= -1;
		}
	}

	public void render(Graphics g) {
		g.setColor(Color.red);
		g.fillRoundRect((int)x, (int)y, 96, 80, 24, 24);
		g.setColor(Color.white);
		g.drawRoundRect((int)x, (int)y, 96, 80, 24, 24);
		g.setColor(Color.white);
		g.drawString("BOSS", (int)x + 33, (int)y + 45);
	}
	
	public Rectangle getBounds(){
		return new Rectangle((int)x, (int)y, 96, 80);
	}

}
