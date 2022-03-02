package mainPack;

import java.awt.Color;
import java.awt.Graphics;
//import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.util.Random;

public class BossMissile extends GameObject {

	private Handler handler;
	private Random r = new Random();
	
	public BossMissile(float x, float y, ID id, Handler handler) {
		super(x, y, id);
		this.handler = handler;
		velX = r.nextInt(5 - -5) + -5; //velX = [-5;5]
		velY = 5;
		
	}

	public void tick() {
		x += velX;
		y += velY;
		
		if (y >= Game.HEIGHT - 64) handler.removeObject(this);
		if (x <= 0 || x >= Game.WIDTH - 32) velX *= -1;
		
		handler.addObject(new Trail(x, y, 16, 4, 0.08f, ID.Trail, Color.orange, handler));
		
	}

	public void render(Graphics g) {
		
		//Graphics2D g2d = (Graphics2D) g;
		
		g.setColor(Color.red);
		g.fillRect((int)x, (int)y, 16, 16);
		
	}
	
	public Rectangle getBounds(){
		return new Rectangle((int)x, (int)y, 16, 16);
	}

}

