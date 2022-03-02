package mainPack;

import java.awt.Color;
import java.awt.Graphics;
//import java.awt.Graphics2D;
import java.awt.Rectangle;

public class FastEnemy extends GameObject{

	private Handler handler;
	
	public FastEnemy(float x, float y, ID id, Handler handler) {
		super(x, y, id);
		this.handler = handler;
		velY = 9;
		velX = 9;
	}

	public void tick() {
		x += velX;
		y += velY;
		
		if (y <= 0 || y >= Game.HEIGHT - 64) velY *= -1;
		if (x <= 0 || x >= Game.WIDTH - 32) velX *= -1;
		
		handler.addObject(new Trail(x, y, 16, 16, 0.06f, ID.Trail, Color.cyan, handler));
		
	}

	public void render(Graphics g) {
		
		//Graphics2D g2d = (Graphics2D) g;
		
		g.setColor(Color.cyan);
		g.fillRect((int)x, (int)y, 16, 16);
		
	}
	
	public Rectangle getBounds(){
		return new Rectangle((int)x, (int)y, 16, 16);
	}
}
